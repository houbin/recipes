#include "config.h"
#include "config.h"
#include "logger.h"
#include "udp_service.h"

Logger *g_logger = NULL;

using namespace std;
using namespace util;

void run_daemon()
{
    pid_t pid;

    pid = fork();
    if (pid > 0)
    {
        // this is parent process
        exit(1);
    }
    else if (pid != 0)
    {
        exit(0);
    }

    // this is child process
    setsid();
    return;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    int listen_port = 15060;
    int thread_number = 1;
    int32_t log_level = 2;
    string log_file("/var/log/alarm/udp_service.log");
    string config_path("/etc/jovision/alarm/conf/udp_service.conf");

    if (argc == 2)
    {
        if (strcmp(argv[1], "-v") == 0)
        {
            printf("%s\n", "v0.0.1.0");
            return 0;
        }
    }

    Config g_config(config_path);

    log_level = g_config.Read("log_level", log_level);
    log_file = g_config.Read("log_path", log_file);
    thread_number = g_config.Read("thread_number", thread_number);
    listen_port = g_config.Read("listen_port", listen_port);

    g_logger = new Logger(log_file);
    g_logger->SetLogLevel((util::LogLevel)log_level);

    UdpService udp_service(thread_number);
    ret = udp_service.Listen("0.0.0.0", listen_port);
    if (ret != 0)
    {
        printf("udp service listen error\n");
        return -1;
    }

    udp_service.Start();

    udp_service.Wait();

    return 0;
}
