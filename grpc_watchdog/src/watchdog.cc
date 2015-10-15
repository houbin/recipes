#include <sys/types.h>
#include <signal.h>
#include "watchdog.h"

namespace watchdog
{

void ProcessInfo::RebootProcess()
{
    char buffer[1024] = {0};
    FILE *fp = NULL;

    kill(pid_, SIGKILL);
    dog_->RemoveProcess(reboot_str_);

    snprintf(buffer, 1023, "nohup %s >/dev/null &", reboot_str_.c_str());
    fp = popen(buffer, "r");
    if (fp == NULL)
    {
        LOG_FATAL(logger_, "popen error, reboot str %s", reboot_str_.c_str());
        return;
    }

#if 0
    char temp_buffer[1024] = {0};
    while(fgets(temp_buffer, 1023, fp) != NULL)
    {
        fprintf(stderr, "temp buffer %s\n", buffer);
    }
    system(buffer);
#endif

    LOG_INFO(logger_, "reboot process, start pclose fp");
    pclose(fp);
    LOG_INFO(logger_, "reboot process ok, and process is %s", reboot_str_.c_str());

    return;
}

void WatchDog::Init()
{
    dog_timer.Init();

    Bind();
    Start();

    LOG_INFO(logger_, "watch dog init ok");

    return;
}

int32_t WatchDog::RemoveProcess(string reboot_path)
{
    map<string, ProcessInfo*>::iterator iter = process_info_map_.find(reboot_path);
    if (iter == process_info_map_.end())
    {
        return 0;
    }

    process_info_map_.erase(iter);

    return 0;
}

void WatchDog::CancelRebootEvent(ProcessInfo *process_info)
{
    if (process_info->reboot_process_event_)
    {
        dog_timer.CancelEvent(process_info->reboot_process_event_);
        process_info->reboot_process_event_ = NULL;
    }

    return;
}

void WatchDog::ResetRebootEvent(double plus, ProcessInfo *process_info)
{
    CancelRebootEvent(process_info);

    process_info->reboot_process_event_ = new C_Reboot_Process(process_info);
    assert(process_info->reboot_process_event_ != NULL);

    dog_timer.AddEventAfter(plus, process_info->reboot_process_event_);

    return;
}

int32_t WatchDog::HandleBeacon(char *reboot_str, int pid, int lost_threshold)
{
    string reboot_path(reboot_str);

    Mutex::Locker lock(mutex_);
    map<string, ProcessInfo*>::iterator iter = process_info_map_.find(reboot_path);
    if (iter == process_info_map_.end())
    {
        // start beacon
        LOG_INFO(logger_, "handle first beacon, reboot path %s, pid %d, lost_threshold %d", reboot_str, pid, lost_threshold);

        ProcessInfo *process_info = new ProcessInfo(logger_, reboot_path, (pid_t)pid, lost_threshold, NULL, this);
        assert(process_info != NULL);

        C_Reboot_Process *event = new C_Reboot_Process(process_info);
        assert(event != NULL);

        process_info->reboot_process_event_ = event;

        process_info_map_.insert(make_pair(reboot_path, process_info));

        dog_timer.AddEventAfter(lost_threshold, event);
    }
    else
    {
        LOG_INFO(logger_, "handle beacon, reboot path %s, pid %d, lost_threshold %d", reboot_str, pid, lost_threshold);

        // routine beacon
        ProcessInfo *process_info = iter->second;
        assert(process_info != NULL);

        process_info->pid_ = (pid_t)pid;
        process_info->lost_threshold_ = lost_threshold;

        // reset timer
        ResetRebootEvent(process_info->lost_threshold_, process_info);
    }

    return 0;
}

int32_t WatchDog::HandleLegalClose(char *reboot_str)
{
    string reboot_path(reboot_str);
    LOG_INFO(logger_, "handle legal close, close path %s", reboot_str);

    Mutex::Locker lock(mutex_);
    map<string, ProcessInfo*>::iterator iter = process_info_map_.find(reboot_path);
    if (iter != process_info_map_.end())
    {
        ProcessInfo *process_info = iter->second;
        assert(process_info != NULL);

        dog_timer.CancelEvent(process_info->reboot_process_event_);
        process_info_map_.erase(iter);
        delete process_info;
        process_info = NULL;
    }

    LOG_INFO(logger_, "handle legal close ok");

    return 0;
}

void WatchDog::Wait()
{
    LOG_INFO(logger_, "wait");
    Join();

    return;
}

void WatchDog::Shutdown()
{
    LOG_INFO(logger_, "shutdown");
    dog_timer.Shutdown();

    return;
}

}

