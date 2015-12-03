#ifndef UDP_SERVICE_H_
#define UDP_SERVICE_H_

#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <errno.h>
#include "thread.h"
#include "common.h"

using namespace std;
using namespace util;

#define BUFFER_SIZE (8*1024)
class UdpThread : public Thread
{
public:
    UdpThread(int id, int fd) : id_(id), fd_(fd) { in_buffer_len_ = 0; }
    ~UdpThread() { }

    int GetThreadId()
    { return id_; }

    int Start()
    {
        Create();
    }

    void* Entry()
    {
        LOG_INFO(g_logger, "enter entry, thread id %d, fd %d", id_, fd_);

        int ret = 0;
        while(true)
        {
            struct sockaddr_in client_addr;
            memset((void*)&client_addr, 0, sizeof(client_addr));
            socklen_t addr_len;

            // ping 
            ret = recvfrom(fd_, in_buffer_, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
            if (ret <= 0)
            {
                LOG_ERROR(g_logger, "recvfrom error, thread id %d, fd %d, error %d, error msg %s", id_, fd_, -errno, strerror(errno));
                break;
            }

            in_buffer_len_ = ret;

            LOG_INFO(g_logger, "recv msg length %d, client ip %s, client port %d", in_buffer_len_, inet_ntoa(client_addr.sin_addr), client_addr.sin_port);

            // pong
            ret = sendto(fd_, in_buffer_, in_buffer_len_, 0, (struct sockaddr*)&client_addr, addr_len);
            if (ret <= 0)
            {
                LOG_ERROR(g_logger, "sendto error, thread id %d, fd %d, error %d, error msg %s", id_, fd_, -errno, strerror(errno));
                break;
            }
        }

        LOG_INFO(g_logger, "exit thread %d, fd %d", id_, fd_);
    }

private:
    int id_;
    int fd_;
    
    char in_buffer_[BUFFER_SIZE];
    int in_buffer_len_;
};

class UdpService
{
public:
    UdpService(int thread_number);
    ~UdpService();

    int CreateUdpSocket();

    int Listen(string server_ip, int port);

    int Start();

    int Wait();

private:
    string server_ip_;
    int port_;
    int fd_;

    int thread_number_;

    vector<UdpThread*> threads_;
};

#endif

