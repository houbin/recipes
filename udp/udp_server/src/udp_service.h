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

extern int g_total_recv_number;
extern int g_total_recv_bytes;
extern int g_total_send_number;
extern int g_total_send_bytes;

#define BUFFER_SIZE (1024)
#define BATCH_RECV_MAX 10
class UdpThread : public Thread
{
public:
    UdpThread(string server_ip, int server_port, int id);
    ~UdpThread() {}
    
    int GetThreadId()
    { return id_; }
    
    int CreateUdpSocket();
    int Init();
    int Start();
    void* Entry();

private:
    string server_ip_;
    int server_port_;

    int id_;
    int listen_fd_;
    
    char in_buffer_[BUFFER_SIZE];
    int in_buffer_len_;
};

class UdpService
{
public:
    UdpService(string server_ip, int server_port, int thread_number);
    ~UdpService();

    int Start();
    int Wait();

private:
    string server_ip_;
    int server_port_;

    int thread_number_;
    vector<UdpThread*> threads_;
};

#endif
