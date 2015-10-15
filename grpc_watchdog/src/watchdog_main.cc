#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../util/logger.h"
#include "../grpc/watchdog.h"
#include "watchdog.h"

using namespace util;
using namespace watchdog;

#define WATCHDOG_SERVE_PORT 6010

Logger *logger = NULL;

int main(int argc, char *argv[])
{
    NewLogger("/var/log/watchdog/", &logger);

    struct sockaddr_in recv_addr;
    memset(&recv_addr, 0, sizeof(struct sockaddr_in));

    recv_addr.sin_family = AF_INET;
    recv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    recv_addr.sin_port = htons(WATCHDOG_SERVE_PORT);

    WatchDog *watchdog = new WatchDog(logger, recv_addr, watchdog_methodList_s);
    assert(watchdog != NULL);

    watchdog->Init();

    watchdog->Wait();
    watchdog->Shutdown();

    return 0;
}
