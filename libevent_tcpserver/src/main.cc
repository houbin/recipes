#include "../util/logger.h"
#include "worker.h"

using namespace util;
using namespace tcpserver;

Logger *logger = NULL;

int main()
{
    logger = new Logger("/var/log/tcpserver/");
    logger->SetLogLevel(DEBUG);
    LOG_ERROR(logger, "start log");
    Master *master = new Master(logger, 9999, 2, 1000, 0, 0);
    master->Init();
    master->Start();
    master->Wait();

    return 0;
}
