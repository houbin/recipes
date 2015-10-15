#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include <map>
#include "../util/grpc_udp_service.h"
#include "../util/timer.h"

using namespace std;
using namespace util;

namespace watchdog
{

class C_Reboot_Process;
class WatchDog;

class ProcessInfo
{
public:
    Logger *logger_;

    string reboot_str_;
    pid_t pid_;
    int lost_threshold_;

    C_Reboot_Process *reboot_process_event_;
    WatchDog *dog_;

    ProcessInfo(Logger *logger, string reboot_str, pid_t pid, int lost_threshold, C_Reboot_Process *reboot_process_event, WatchDog *dog)
    : logger_(logger), reboot_str_(reboot_str), pid_(pid), lost_threshold_(lost_threshold), reboot_process_event_(reboot_process_event), dog_(dog)
    {
    
    }

    void RebootProcess();
};

class C_Reboot_Process : public Context
{
private:
    ProcessInfo *process_info_;

public:
    C_Reboot_Process(ProcessInfo *info) : process_info_(info)
    {
    
    }

    void Finish(int r)
    {
        process_info_->RebootProcess();
        return;
    }
};

class WatchDog: public GrpcUdpService
{
private:
    Logger *logger_;

    Mutex mutex_;
    SafeTimer dog_timer;
    map<string, ProcessInfo*> process_info_map_;

public:
    WatchDog(Logger *logger, struct sockaddr_in &recv_addr, grpcMethod_t *method_list)
    : GrpcUdpService(logger, recv_addr, method_list, (void *)this), logger_(logger), mutex_("WatchDog::Mutex"), dog_timer(logger, mutex_)
    {
    
    }

    void Init();

    int32_t RemoveProcess(string reboot_path);

    void CancelRebootEvent(ProcessInfo *info);
    void ResetRebootEvent(double plus, ProcessInfo *info);

    int32_t HandleBeacon(char *reboot_str, int pid, int lost_threshold);
    int32_t HandleLegalClose(char *reboot_str);

    void Wait();
    void Shutdown();
};

}

#endif

