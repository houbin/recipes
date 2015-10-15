#include <unistd.h>
#include <errno.h>
#include "../util/common.h"
#include "worker.h"
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include "connection.h"
#include "global.h"

using namespace util;

namespace tcpserver
{

void RecvNotifiedCb(int fd, short event, void *arg)
{
    assert(arg != NULL);
    Worker *worker = (Worker *)arg;
    worker->RecvNotifiedCb(fd, event, arg);

    return;
}

void CloseConn(ConnectionInfo *conn_info)
{
    conn_info->in_buffer_len = 0;

    bufferevent_free(conn_info->buffer_event);
    safe_close(conn_info->cfd);

    delete conn_info;
}

void CloseErrorConn(ConnectionInfo *conn_info)
{
    assert(conn_info != NULL);
    CloseConn(conn_info);
}

int32_t Dispatch(ConnectionInfo *conn_info, uint32_t tag, uint32_t length, char *value)
{
    if (tag == MSG_TYPE_PRINT)
    {
        LOG_DEBUG(logger, "[print]: %s\n", value);
    }

    return 0;
}

void ClientTcpReadCb(struct bufferevent *bev, void *arg)
{
    int ret = 0;
    uint32_t msg_length = 0;

    ConnectionInfo *conn_info = (ConnectionInfo *)arg;
    assert(conn_info != NULL);

    struct in_addr client_addr;
    client_addr.s_addr = conn_info->cip;
    LOG_DEBUG(logger, "client read tcp data, conn id %" PRIu64 ", cfd %d, ip %s, port %u", 
                    conn_info->conn_id, conn_info->cfd, inet_ntoa(client_addr), conn_info->cport);

    while (true)
    {
        uint16_t left_size;
        while(true)
        {
            left_size = CONN_BUFFER_LEN - conn_info->in_buffer_len;
            if (left_size == 0)
                break;

            ret = bufferevent_read(bev, conn_info->in_buffer + conn_info->in_buffer_len, left_size);
            if (ret <= 0)
                break;
            conn_info->in_buffer_len += ret;
        }

        while (true)
        {
            if (conn_info->in_buffer_len < kMsgHeaderSize)
            {
                if (left_size == 0)
                    break;
                else
                    return;
            }

            MsgHeader msg_header;
            msg_header.Decode(conn_info->in_buffer);
            if (msg_header.magic_code != kMsgMagicCode || msg_header.length >= MAX_MSG_LENGTH - kMsgHeaderSize)
            {
                LOG_ERROR(logger, "pkg error, recv magic code %x, length %d", msg_header.magic_code, msg_header.length);
                CloseErrorConn(conn_info);
                return;
            }

            if (conn_info->in_buffer_len - kMsgHeaderSize < msg_header.length)
            {
                if (left_size == 0)
                    break;
                else
                    return;
            }

            // dispatch this message
            ret = Dispatch(conn_info, msg_header.tag, msg_header.length, conn_info->in_buffer + kMsgHeaderSize);
            if (ret != 0)
            {
                LOG_ERROR(logger, "dispatch error");
                CloseErrorConn(conn_info);
                return;
            }

            uint16_t msg_sum_len = kMsgHeaderSize + msg_header.length;
            conn_info->in_buffer_len -= msg_sum_len;
            memmove(conn_info->in_buffer, conn_info->in_buffer + msg_sum_len, conn_info->in_buffer_len);
            if (conn_info->in_buffer_len == 0)
            {
                if (left_size == 0)
                    break;
                else
                    return;
            }
        }
    }

    return;
}

void ClientTcpErrorCb(struct bufferevent *bev, short event, void *arg)
{
    assert(arg != NULL);
    ConnectionInfo *conn_info = (ConnectionInfo *)arg;

    struct in_addr client_addr;
    client_addr.s_addr = conn_info->cip;
    LOG_DEBUG(logger, "client tcp error, conn id %" PRIu64 ", cfd %d, ip %s, port %u", conn_info->conn_id, conn_info->cfd,
                            inet_ntoa(client_addr), conn_info->cport);

    if (event & BEV_EVENT_TIMEOUT)
    {
        LOG_DEBUG(logger, "client tcp timeout, conn id %" PRIu64 ", cfd %d, ip %s, port %u", conn_info->conn_id, conn_info->cfd,
                            inet_ntoa(client_addr), conn_info->cport);
    }
    else if (event & BEV_EVENT_EOF)
    {
    
    }
    else if (event & BEV_EVENT_ERROR)
    {
        int error_code = EVUTIL_SOCKET_ERROR();
        LOG_DEBUG(logger, "client tcp error, error code %d, msg %s, conn id %" PRIu64 ", cfd %d, ip %s, port %u", 
                    error_code, evutil_socket_error_to_string(error_code), conn_info->conn_id, conn_info->cfd, 
                    inet_ntoa(client_addr), conn_info->cport);
    }

    bufferevent_free(conn_info->buffer_event);
    safe_close(conn_info->cfd);

    return;
}

Worker::Worker(Logger *logger, int i, uint32_t worker_conn_count, int read_timeout, int write_timeout, Master *master)
: logger_(logger), id_(i), worker_conn_count_(worker_conn_count), read_timeout_(read_timeout), write_timeout_(write_timeout),
    master_(master), conn_info_queue_mutex_("Worker::ConnectionInfoQueueMutex")
{
    base_ = NULL;
    notified_wfd_ = -1;
    notified_rfd_ = -1;
    notified_event_ = NULL;
}

Worker::~Worker()
{
    
}

int32_t Worker::Init()
{
    int ret = 0;
    int fds[2];

    ret = pipe(fds);
    if (ret != 0)
    {
        LOG_ERROR(logger_, "create pipe error, error %d, msg %d", -errno, strerror(errno));
        return -1;
    }

    notified_rfd_ = fds[0];
    notified_wfd_ = fds[1];

    base_ = event_base_new();
    if(base_ == NULL)
    {
        LOG_ERROR(logger_, "event_base_new error");
        return -1;
    }

    notified_event_ = event_new(base_, notified_rfd_, EV_READ|EV_PERSIST, tcpserver::RecvNotifiedCb, (void *)this);
    if (notified_event_ == NULL)
    {
        LOG_ERROR(logger_, "event_new error");
        return -1;
    }

    ret = event_add(notified_event_, NULL);
    if (ret != 0)
    {
        LOG_ERROR(logger_, "event_add error");
        return -1;
    }

    return 0;
}

int32_t Worker::Start()
{
    Create();
    return 0;
}

void* Worker::Entry()
{
    int ret = 0;
    
    event_base_dispatch(base_);

    LOG_INFO(logger_, "event_base_dispatch return");

    return NULL;
}

int Worker::GetId()
{
    return id_;
}

int Worker::GetNotifiedWFd()
{
    return notified_wfd_;
}

void Worker::RecvNotifiedCb(int fd, short event, void *arg)
{
    int ret = 0;
    char buf[1] = {0};

    if (read(fd, buf, 1) != 1)
    {
        LOG_ERROR(logger_, "read master -> worker notify error");
        return;
    }

    ConnectionInfo *conn_info = NULL;
    {
        Mutex::Locker lock(conn_info_queue_mutex_);
        conn_info = conn_info_queue_.front();
        conn_info_queue_.pop_front();
        assert(conn_info != NULL);
        assert(conn_info->cfd > 0);
    }

    struct in_addr client_addr;
    client_addr.s_addr = conn_info->cip;
    LOG_DEBUG(logger_, "pop conn info, conn id %" PRIu64 ", cfd %d, ip %s, port %u", conn_info->conn_id, conn_info->cfd,
                inet_ntoa(client_addr), conn_info->cport);

    conn_info->buffer_event = bufferevent_socket_new(base_, conn_info->cfd, BEV_OPT_CLOSE_ON_FREE);
    if (conn_info->buffer_event == NULL)
    {
        int error_code = EVUTIL_SOCKET_ERROR();
        LOG_ERROR(logger_, "bufferevent_socket_new error, error %d, msg %s", error_code, evutil_socket_error_to_string(error_code));
        return;
    }
    bufferevent_setcb(conn_info->buffer_event, tcpserver::ClientTcpReadCb, NULL, ClientTcpErrorCb, (void *)conn_info);
    bufferevent_enable(conn_info->buffer_event, EV_READ|EV_PERSIST);

    conn_info->in_buffer_len = 0;
    memset(conn_info->in_buffer, 0, sizeof(conn_info->in_buffer));
    conn_info->out_buffer_len = 0;
    memset(conn_info->out_buffer, 0, sizeof(conn_info->out_buffer));

    //test sleep 10s
    //sleep(10);
    LOG_DEBUG(logger_, "add client to worker, conn id %" PRIu64 ", cfd %d, ip %s, port %u", conn_info->conn_id, conn_info->cfd, 
                        inet_ntoa(client_addr), conn_info->cport);
    
    return;
}

int32_t Worker::PutConnInfo(ConnectionInfo *conn_info)
{
    LOG_DEBUG(logger_, "put conn info, conn id %" PRIu64 "", conn_info->conn_id);
    Mutex::Locker lock(conn_info_queue_mutex_);
    conn_info_queue_.push_back(conn_info);

    return 0;
}

}

