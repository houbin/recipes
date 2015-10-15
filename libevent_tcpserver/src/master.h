#ifndef TCP_SERVER_MASTER_H_
#define TCP_SERVER_MASTER_H_

#include <stdint.h>
#include <vector>
#include <event.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../util/thread.h"
#include "../util/logger.h"
#include "../util/mutex.h"
#include "../util/cond.h"
#include "worker.h"

using namespace util;

namespace tcpserver
{

class Worker;
class Master : public Thread
{
public:
    Master(Logger *logger, int listen_port, uint16_t worker_count, uint32_t worker_conn_count, int read_timeout, int write_timeout);
    ~Master();

    int32_t Init();
    int32_t Start();
    void *Entry();
    void Wait();

    int32_t OpenServerSocket();
    void AcceptCb(int fd, short event, void *arg);
    int AcceptClient(struct sockaddr_in *client_addr);
    int32_t PickOneWorker(Worker **worker);

private:
    Logger *logger_;

    int listen_fd_;
    int listen_port_;

    struct event_base *main_base_;
    struct event *listen_event_;

    uint16_t worker_count_;
    uint32_t worker_conn_count_;
    vector<Worker*> workers_;

    int read_timeout_;
    int write_timeout_;
    uint64_t conn_count_;
};

}

#endif 

