#include <netinet/in.h>
#include <arpa/inet.h>
#include "udp_service.h"
#include <assert.h>

using namespace std;
using namespace util;

int g_total_recv_number = 0;
int g_total_recv_bytes = 0;
int g_total_send_number = 0;
int g_total_send_bytes = 0;

UdpThread::UdpThread(string server_ip, int server_port, int id) 
    : server_ip_(server_ip), server_port_(server_port), id_(id) 
{ 
    in_buffer_len_ = 0;
}

int UdpThread::CreateUdpSocket()
{
    int ret = 0;

    listen_fd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (listen_fd_ < 0)
    {
        LOG_ERROR(g_logger, "create udp socket error, error %d, error msg %s", -errno, strerror(errno));
        return -1;
    }

    int opt = 1;
    ret = ::setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (ret != 0)
    {
        return ret;
    }
    
#ifdef SO_REUSEPORT
    opt = -1;
    ret = ::setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    if (ret != 0)
    {
        return ret;
    }
#endif

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip_.c_str());
    server_addr.sin_port = htons(server_port_);
    
    socklen_t addr_len = sizeof(server_addr);
    ret = ::bind(listen_fd_, (struct sockaddr*)&server_addr, addr_len);
    if (ret < 0)
    {
        LOG_ERROR(g_logger, "bind udp socket error, error %d, error msg %s", -errno, strerror(errno));
        return -1;
    }

    return 0;
}

int UdpThread::Init()
{
    return CreateUdpSocket();
}

int UdpThread::Start()
{
    Create();
    return 0;
}

void* UdpThread::Entry()
{
    LOG_INFO(g_logger, "enter entry, thread id %d, fd %d", id_, listen_fd_);

    int ret = 0;
    while(true)
    {
        struct sockaddr_in client_addr;
        memset((void*)&client_addr, 0, sizeof(client_addr));
        socklen_t addr_len;

        // recv implement
        ret = recvfrom(listen_fd_, in_buffer_, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (ret <= 0)
        {
            LOG_ERROR(g_logger, "recvfrom error, thread id %d, fd %d, error %d, error msg %s", id_, listen_fd_, -errno, strerror(errno));
            break;
        }

        g_total_recv_number++;
        g_total_recv_bytes += ret;

        in_buffer_len_ = ret;

        // pong
        #if 0
        ret = sendto(listen_fd_, in_buffer_, in_buffer_len_, 0, (struct sockaddr*)&client_addr, addr_len);
        if (ret <= 0)
        {
            LOG_ERROR(g_logger, "sendto error, thread id %d, fd %d, error %d, error msg %s", id_, listen_fd_, -errno, strerror(errno));
            break;
        }

        // record
        g_total_send_number++;
        g_total_send_bytes += ret;
        LOG_INFO(g_logger, "g_total_recv_number %d, g_total_recv_bytes %d, g_total_send_number %d, g_total_send_bytes %d", 
            g_total_recv_number, g_total_recv_bytes, g_total_send_number, g_total_send_bytes);
        #endif
	LOG_INFO(g_logger, "recv msg in thread %d, fd %d", id_, listen_fd_);
    }

    LOG_INFO(g_logger, "exit thread %d, fd %d", id_, listen_fd_);
    return 0;
}  

UdpService::UdpService(string server_ip, int server_port, int thread_number)
        :server_ip_(server_ip), server_port_(server_port)
{
#ifdef SO_REUSEPORT
    thread_number_ = thread_number;
#else
    thread_number_ = 1;
#endif
}

UdpService::~UdpService()
{

}

int UdpService::Start()
{
    LOG_INFO(g_logger, "Start %d threads", thread_number_);

    int i = 0;
    for(; i < thread_number_; i++)
    {
        UdpThread *t = new UdpThread(server_ip_, server_port_, i);
        assert(t != NULL);

        t->Init();
        t->Start();

        threads_.push_back(t);
    }

    return 0;
}

int UdpService::Wait()
{
    LOG_INFO(g_logger, "Wait");

    vector<UdpThread*>::iterator iter = threads_.begin();
    while (iter != threads_.end())
    {
        UdpThread *s = *iter;
        s->Join();
        LOG_ERROR(g_logger, "join thread %d", s->GetThreadId());

        iter++;
    }

    return 0;
}

