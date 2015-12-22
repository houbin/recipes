#include "config.h"
#include "config.h"
#include "logger.h"
#include "udp_service.h"
#include "timer.h"

Logger *g_logger = NULL;
Mutex timer_mutex("TimerMutex");
SafeTimer timer(timer_mutex);
uint64_t last_ms = 0;
int g_last_recv_number = 0;

using namespace std;
using namespace util;

extern void NewDumpContext();

class DumpContext : public Context
{
public:
    void Finish(int r)
    {
	struct timeval now_time;
	gettimeofday(&now_time, NULL);
	uint64_t now_ms = now_time.tv_sec * 1000 + now_time.tv_usec /1000;
	int now_recv_number = g_total_recv_number;
	int now_recv_bytes = g_total_recv_bytes;

	if (last_ms != 0)
	{
            uint64_t interval_ms = now_ms - last_ms;
	    int interval_recv_number = now_recv_number - g_last_recv_number;
	    double pps = interval_recv_number / interval_ms * 1000;
            printf("g_total_recv_number %d, g_total_recv_bytes %d, pps %f\n", now_recv_number, now_recv_bytes, pps);
	}
        last_ms = now_ms;
	g_last_recv_number = now_recv_number;

        NewDumpContext();
    }
};

void NewDumpContext()
{
    DumpContext *ct = new DumpContext;
    timer.AddEventAfter(5.0, ct);
}

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
    string log_file("/var/log/jovision/udp_server.log");
    string config_path("/etc/jovision/udp_server/udp_server.conf");

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
    log_file = g_config.Read("log_file", log_file);
    thread_number = g_config.Read("thread_number", thread_number);
    listen_port = g_config.Read("listen_port", listen_port);

    g_logger = new Logger(log_file);
    g_logger->SetLogLevel((util::LogLevel)log_level);

    timer.Init();

    NewDumpContext();

    UdpService udp_service("0.0.0.0", listen_port, thread_number);
    udp_service.Start();
    udp_service.Wait();

    return 0;
}
