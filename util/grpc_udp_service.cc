#include <errno.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include "grpc_udp_service.h"
#include "../include/errcode.h"

namespace util
{

GrpcUdpService::GrpcUdpService(Logger *logger, struct sockaddr_in &recv_addr, grpcMethod_t *method_list, void *parent, int recv_timeout_milliseconds)
: logger_(logger), method_list_s_(method_list), parent_(parent), recv_timeout_milliseconds_(recv_timeout_milliseconds), stop_(false)
{
    memcpy(&recv_addr_, &recv_addr, sizeof(recv_addr_));
}

int GrpcUdpService::RecvByUdp(grpc_t *grpc, void *buffer, int len, int *timeout_milliseconds)
{
    int fd = 0;
    int ret = 0;
    struct pollfd pfd;
    Logger *logger = NULL;
    GrpcUdpUserDefInfo *user_info = NULL;

    user_info = (GrpcUdpUserDefInfo*)grpc->userdef;
    logger = user_info->logger;
    fd = user_info->fd;

    pfd.fd = fd;
    pfd.events = POLLIN | POLLERR | POLLNVAL | POLLHUP;
    ret = poll(&pfd, 1, -1);
    if (ret < 0)
    {
        LOG_INFO(logger, "poll error - %s", strerror(errno));
        return -errno;
    }
    else if (ret == 0)
    {
        LOG_INFO(logger, "poll timeout");
        return -ERR_TIMEOUT;
    }

    if (pfd.revents & (POLLERR | POLLNVAL | POLLHUP))
    {
        LOG_INFO(logger, "pdf.revents is POLLERR or POLLNVAL or POLLHUP");
        return -1;
    }

again:
    int addr_len = sizeof(user_info->from_addr);
    ret = recvfrom(fd, buffer, len, 0, (struct sockaddr *)&(user_info->from_addr), (socklen_t *)&addr_len);
    if (ret < 0)
    {
        if (errno == EAGAIN || errno == EINTR)
        {
            goto again;
        }

        LOG_INFO(logger, "recvfrom error - %s", strerror(errno));
        return -errno;
    }

    return ret;
}

int GrpcUdpService::SendByUdp(grpc_t *grpc, void *buffer, int len)
{
    int ret = 0;
    int fd = 0;
    int addr_len = 0;
    Logger *logger = NULL;
    GrpcUdpUserDefInfo *user_info = (GrpcUdpUserDefInfo *)grpc->userdef;

    logger = user_info->logger;
    fd = user_info->fd;

again:
    addr_len = sizeof(user_info->from_addr);
    ret = sendto(fd, buffer, len, 0, (struct sockaddr *)&(user_info->from_addr), addr_len);
    if (ret < 0)
    {
        if (errno == EAGAIN)
        {
            goto again;
        }

        LOG_INFO(logger, "sendto error - %s", strerror(errno));
        return -errno;
    }

    return ret;
}

int32_t GrpcUdpService::Bind()
{
    int optval = 1;
    int32_t ret = 0;;
    
    LOG_INFO(logger_, "bind");

    fd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd_ < 0)
    {
        LOG_FATAL(logger_, "create socket error: %s", strerror(errno));
        return -errno;
    }

    ret = setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if (ret < 0)
    {
        LOG_FATAL(logger_, "setsockopt reuseaddr error: %s", strerror(errno));
        return -errno;
    }

    ret = bind(fd_, (struct sockaddr *)&recv_addr_, sizeof(struct sockaddr_in));
    if (ret < 0)
    {
        LOG_FATAL(logger_, "bind error: %s", strerror(errno));
        return -errno;
    }

    return 0;
}

int32_t GrpcUdpService::Start()
{
    LOG_INFO(logger_, "start");

    Create();

    return 0;
}

void *GrpcUdpService::Entry()
{
    int ret;
    grpcInitParam_t init_param;
    GrpcUdpUserDefInfo user_info = {0};

    user_info.logger = this->logger_;
    user_info.fd = this->fd_;
    user_info.recv_timeout_milliseconds = recv_timeout_milliseconds_;
    user_info.parent = (void *)parent_;

    memset(&init_param, 0, sizeof(init_param));
    init_param.userdef = &user_info;
    init_param.fptr_net.recv = RecvByUdp;
    init_param.fptr_net.send = SendByUdp;
    init_param.methodList_s = method_list_s_;
    
    grpc_t *grpc = grpc_new();
    grpc_init(grpc, &init_param);
    grpc_s_account_clear(grpc);

    // TODO add account manage
    
    while(!stop_)
    {
        ret = grpc_s_serve(grpc);
        if (ret < 0)
        {
            break;
        }

        grpc_end(grpc);
    }

    grpc_delete(grpc);

    if (fd_ > 0)
    {
        close(fd_);
        fd_ = -1;
    }

    return 0;
}

void GrpcUdpService::Stop()
{
    stop_ = true;

    if (fd_ > 0)
    {
        ::close(fd_);
        fd_ = -1;
    }

    if (IsStarted())
    {
        Join();
    }

    stop_ = false;

    return;
}

}

