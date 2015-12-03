#include <netinet/in.h>
#include <arpa/inet.h>
#include "udp_service.h"
#include <assert.h>

using namespace std;
using namespace util;

UdpService::UdpService(int thread_number)
: thread_number_(thread_number)
{

}

UdpService::~UdpService()
{

}

int UdpService::CreateUdpSocket()
{
    int ret = 0;

    fd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd_ < 0)
    {
        LOG_ERROR(g_logger, "create udp socket error, error %d, error msg %s", -errno, strerror(errno));
        return -1;
    }

    int opt = 1;
    ret = ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (ret != 0)
    {
        return ret;
    }
    
    #if 0
    if (thread_number_ > 1)
    {
        int opt = -1;
        ret = ::setsockopt(fd_, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
        if (ret != 0)
        {
            return ret;
        }
    }
    #endif
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_);
    
    socklen_t addr_len = sizeof(server_addr);
    ret = ::bind(fd_, (struct sockaddr*)&server_addr, addr_len);
    if (ret < 0)
    {
        LOG_ERROR(g_logger, "bind udp socket error, error %d, error msg %s", -errno, strerror(errno));
        return -1;
    }

    return 0;
}

int UdpService::Listen(string server_ip, int port)
{
    int ret = 0;

    LOG_INFO(g_logger, "Listen, server_ip %s, port %d", server_ip.c_str(), port);

    server_ip_ = server_ip;
    port_ = port;

    ret = CreateUdpSocket();
    if (ret != 0)
    {
        return -1;
    }

    return 0;
}

int UdpService::Start()
{
    LOG_INFO(g_logger, "Start %d threads", thread_number_);

    int i = 0;
    for(; i < thread_number_; i++)
    {
        UdpThread *t = new UdpThread(i, fd_);
        assert(t != NULL);

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

