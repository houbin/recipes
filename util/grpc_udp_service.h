#ifndef STORAGE_GRPC_UDP_SERVICE_H_
#define STORAGE_GRPC_UDP_SERVICE_H_

#include <stdbool.h>
#include <netinet/in.h>
#include "thread.h"
#include "logger.h"
#include "../grpc/watchdog.h"
#include "../grpc/grpc.h"

namespace util
{

typedef struct grpc_udp_user_define_info
{
    Logger *logger;
    int fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in from_addr;
    int recv_timeout_milliseconds;

    void *parent;
}GrpcUdpUserDefInfo;

class GrpcUdpService : public Thread
{
private:
    int fd_;
    Logger *logger_;
    struct sockaddr_in recv_addr_;
    grpcMethod_t *method_list_s_;
    void *parent_;
    int recv_timeout_milliseconds_;

    bool stop_;

    static int RecvByUdp(grpc_t *grpc, void *buffer, int len, int *timeout);
    static int SendByUdp(grpc_t *grpc, void *buffer, int len);

public:
    GrpcUdpService(Logger *logger, struct sockaddr_in &recv_addr, grpcMethod_t *method_list, void *parent, int recv_timeout_milliseconds = -1); 
    int32_t Bind();
    int32_t Start();
    void *Entry();
    void Stop();
};

}

#endif

