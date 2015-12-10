#include <stdio.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include "config.h"
#include "thread.h"
#include "logger.h"
#include "context.h"
#include "timer.h"
#include <vector>

using namespace std;
using namespace util;

int epfd  = 0;

struct ClientInfo
{
    int fd;
    int send_number;
    int recv_number;
    int send_bytes;
    int recv_bytes;

    bool is_ok;
};

vector<ClientInfo> clients;

//#define epoll_ctl printf("line %d, epoll op: ", __LINE__);ret=epoll_ctl
Logger *g_logger = NULL;

static int g_total_send_number = 0;
static int g_total_send_bytes = 0;
static int g_total_recv_number = 0;
static int g_total_recv_bytes = 0;
static int g_total_error = 0;
static int g_total_close1 = 0;
static int g_total_close2 = 0;

static int64_t g_use_time = 0;

inline int SetNonBlocking(int fd)
{
    if (fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK) == -1)
    {
        return -1;
    }

    return 0;
}

int CreateUdpSocket(struct sockaddr_in *addr)
{
    int ret = 0;

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        return fd;
    }

    if (addr != NULL)
    {
        socklen_t len = sizeof(struct sockaddr);
        ret = bind(fd, (struct sockaddr*)&addr, len);
        if (ret != 0)
        {
            perror("bind error");
            return -1;
        }
    }

    return fd;
}

void dump_record()
{
    cout << endl;
    cout << endl;
    
    cout << "============================================================" << endl;
    cout << "g_total_send_number: " << g_total_send_number << endl;
    cout << "g_total_send_bytes: " << g_total_send_bytes << " bytes" << endl;
    cout << "g_total_recv_number: " << g_total_recv_number << endl;
    cout << "g_total_recv_bytes: " << g_total_recv_bytes << " bytes" << endl;
    
    cout << endl;
    cout << "g_total_error: " << g_total_error << endl;
    cout << "g_total_close1: " << g_total_close1 << endl;
    cout << "g_total_close2: " << g_total_close2 << endl;

    cout << "g_use_time: " << g_use_time << endl;
    cout << "============================================================" << endl;
    cout << endl;
    cout << endl;
}

Mutex mutex("test");
SafeTimer g_timer(mutex);

char buffer[] = "12345678901234567890";
int buffer_len = strlen(buffer);

extern void NewTick();
class TickContext : public Context
{
public:
    TickContext() {}
    void Finish(int r)
    {
        int ret = 0;
        //send msg
        
        #if 0
        struct timeval start_tv = {0, 0};
        gettimeofday(&start_tv, NULL);

        int count = 0;

        vector<ClientInfo>::iterator iter = clients.begin();
        for(;iter != clients.end(); iter++)
        {
            ClientInfo info = *iter;
            if (info.is_ok)
            {
                continue;
            }

            int fd = info.fd;
            ret = write(fd, buffer, strlen(buffer));
            if (ret <= 0 )
            {
                ++g_total_error;
                perror("write fd error");
                epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                shutdown(fd, SHUT_RDWR);
            }
            else
            {
                ++g_total_send_number;
                g_total_send_bytes += strlen(buffer);

                //printf("send ok, fd %d\n", fd);

                info.send_number++;
                info.send_bytes += strlen(buffer);
            }
 

            count++;
            if (count % 1000 == 0)
            {
                usleep(20*1000);
            }
        }
        
        struct timeval end_tv = {0, 0};
        gettimeofday(&end_tv, NULL);
        
        g_use_time = (end_tv.tv_sec - start_tv.tv_sec) * 1000000 + (end_tv.tv_usec - start_tv.tv_usec);
        #endif
        
        dump_record();

        NewTick();
    }
};

void NewTick()
{
    TickContext *ct = new TickContext;
    g_timer.AddEventAfter(5.0, ct);
}

int main(int argc, char *argv[])
{
    int ret = 0;
    string server_ip;
    int server_port;
    int request_number;
    int concurrency;
    char recv_buffer[32] = {0};

    int32_t log_level = 2;
    string log_file("/var/log/jovision/udp_client.log");

    if (argc != 5)
    {
        printf("usage: %s <ip> <port> <n> <c>\n");
        return 0;
    }

    server_ip.assign(argv[1]);
    sscanf(argv[2], "%d", &server_port);
    sscanf(argv[3], "%d", &request_number);
    sscanf(argv[4], "%d", &concurrency);

    int request_number_per_client = request_number / concurrency;

    printf("server_ip: %s, server_port: %d, request number: %d, concurrency: %d\n", server_ip.c_str(), server_port, request_number, concurrency);

    g_logger = new Logger(log_file);
    g_logger->SetLogLevel((util::LogLevel)log_level);

    g_timer.Init();

    #define CLIENT_PORT_START 20000
    //int *client_fds = new int[concurrency];
    int i = 0;
    while (i < concurrency)
    {
        int temp_fd;
        temp_fd = CreateUdpSocket(NULL);
        if (temp_fd < 0)
        {
            printf("create udp socket error, i: %d\n", i);
            continue;
        }

        ret = SetNonBlocking(temp_fd);
        if (ret != 0)
        {
            printf("set fd %d non block error\n", temp_fd);
            continue;
        }

        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());
        server_addr.sin_port = htons(server_port);
        ret = connect(temp_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
        if (ret != 0)
        {
            perror("connect server error");
            continue;
        }

        ClientInfo info;
        info.fd = temp_fd;
        info.recv_number = 0;
        info.recv_bytes = 0;
        info.is_ok = false;
        clients.push_back(info);
        i++;
    }
    assert(i == concurrency);

    epfd = epoll_create(1);
    if (epfd < 0)
    {
        perror("epoll_create error");
        return -1;
    }

    struct epoll_event ev;
    for (int i = 0; i < concurrency; i++)
    {
        int fd = clients[i].fd;
        ev.events = EPOLLOUT | EPOLLET;
        ev.data.fd = fd;

        ev.data.ptr = &clients[i];
        ret = 0;
        epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
        if (ret != 0)
        {
            perror("epoll_ctl error");
            printf("epoll_ctl add fd %d error\n", fd);
            return -1;
        }
    }

    // start report thread
    NewTick();

    const int TIMEOUT_MS = 5000;
    #define EPOLL_EVENTS_BATCH_SIZE 4096
    struct epoll_event events[EPOLL_EVENTS_BATCH_SIZE];

    struct timeval start_time;
    gettimeofday(&start_time, NULL);

    while(true)
    {
        if (g_total_recv_number >= request_number)
        {
            break;
        }

        int nfds = epoll_wait(epfd, events, EPOLL_EVENTS_BATCH_SIZE, TIMEOUT_MS);
        if (nfds < 0)
        {
            perror("epoll_wait error");
            return -1;
        }

        int n = 0;
        for (int i = 0; i < nfds; i++)
        {
            ClientInfo *info = (ClientInfo*)events[i].data.ptr;
            int fd = info->fd;
            if (events[i].events & (EPOLLERR | EPOLLHUP))
            {
                ++g_total_error;
                epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &events[i]);
                shutdown(fd, SHUT_RDWR);
            }
            else if (events[i].events & (EPOLLOUT))
            {
                n = send(fd, buffer, strlen(buffer), 0);
                if (n <= 0)
                {
                    ++g_total_error;
                    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &events[i]);
                    shutdown(fd, SHUT_RDWR);
                }
                else
                {
                    ++g_total_send_number;
                    g_total_send_bytes += strlen(buffer);

                    info->send_number++;
                    info->send_bytes += strlen(buffer);
                }
            }
            #if 0
            else if (events[i].events & EPOLLIN)
            {
                n = read(fd, recv_buffer, sizeof(recv_buffer));
                if (n > 0)
                {
                    ++g_total_recv_number;
                    g_total_recv_bytes += n;
                    
                    info->recv_number++;
                    info->recv_bytes += n;

                    if (info->recv_number >= request_number_per_client)
                    {
                        info->is_ok = true;
                        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &events[i]);
                        shutdown(fd, SHUT_RDWR);
                    }
                    #if 0
                    else
                    {
                        events[i].events = EPOLLOUT | EPOLLET;
                        epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &events[i]);
                    }
                    #endif
                }
                else if (n == 0)
                {
                    ++g_total_close1;
                    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &events[i]);
                    shutdown(fd, SHUT_RDWR);
                }
                else if (n == -1)
                {
                    ++g_total_error;
                    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &events[i]);
                    shutdown(fd, SHUT_RDWR);
                }
            }
            #endif
        }
    }

    struct timeval end_time;
    gettimeofday(&end_time, NULL);

    long long time_use_ms = (end_time.tv_sec - start_time.tv_sec) * 1000 + (end_time.tv_usec - start_time.tv_usec) / 1000;
    printf("time use: %lld\n", time_use_ms);

    double qps = 1.0 * request_number / time_use_ms * 1000;
    printf("qps: %f\n", qps);
    printf("translate rate: %f bytes\n", qps * buffer_len);

    g_timer.Shutdown();
    close(epfd);
    
    return 0;
}
