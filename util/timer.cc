#include "clock.h"
#include "logger.h"
#include "timer.h"
#include "context.h"
#include "utime.h"

using namespace std;

namespace util
{

void SafeTimer::Init()
{
    LOG_INFO(logger_, "init");
    thread_ = new SafeTimerThread(this);
    thread_->Create();
}

void SafeTimer::Shutdown()
{
    LOG_INFO(logger_, "shutdown");
    if (thread_ != NULL)
    {
        CancelAllEvents();
        stop_ = true;
        cond_.Signal();

        mutex_.Unlock();
        thread_->Join();
        mutex_.Lock();

        delete thread_;
        thread_ = NULL;
    }

    return;
}

typedef std::multimap<UTime, Context*> scheduled_map_t;
typedef std::map<Context*, scheduled_map_t::iterator> event_lookup_map_t;

void SafeTimer::TimerThread()
{
    LOG_DEBUG(logger_, "TimerThread starting");

    mutex_.Lock();
    while (!stop_)
    {
        UTime t = GetClockNow();

        while (!schedule_.empty())
        {
            scheduled_map_t::iterator iter = schedule_.begin();

            if (iter->first > t)
                break;

            Context *callback = iter->second;
            events_.erase(callback);
            schedule_.erase(iter);

            //mutex_.Unlock();

            LOG_DEBUG(logger_, "TimerThread executing %p", callback);
            callback->Complete(0);

            //mutex_.Lock();
        }

        if (stop_)
        {
            break;
        }

        LOG_DEBUG(logger_, "TimerThread going to sleep");

        if(schedule_.empty())
        {
            cond_.Wait(mutex_);
        }
        else
        {
            cond_.WaitUtil(mutex_, schedule_.begin()->first);
        }

        LOG_DEBUG(logger_, "TimerThread awake");
    }

    LOG_DEBUG(logger_, "TimerThread exiting");
    mutex_.Unlock();

    return;
}

void SafeTimer::AddEventAfter(double seconds, Context *callback)
{
    UTime t = GetClockNow();

    t += seconds;

    AddEventAt(t, callback);

    return;
}

void SafeTimer::AddEventAt(UTime t, Context* callback)
{
    UTime now = GetClockNow();
    LOG_DEBUG(logger_, "AddEventAfter %d.%d -> %p, now is %d.%d", t.tv_sec, t.tv_nsec, callback, now.tv_sec, now.tv_nsec);

    if (stop_)
    {
        delete callback;
        return;
    }

    scheduled_map_t::value_type s_val(t, callback);
    scheduled_map_t::iterator i = schedule_.insert(s_val);

    event_lookup_map_t::value_type e_val(callback, i);
    pair<event_lookup_map_t::iterator, bool> rval(events_.insert(e_val));

    assert(rval.second);

    if (i == schedule_.begin())
    {
        cond_.Signal();
    }

    return;
}

bool SafeTimer::CancelEvent(Context *callback)
{
    map<Context*, multimap<UTime, Context *>::iterator>::iterator p = events_.find(callback);
    if (p == events_.end())
    {
        LOG_WARN(logger_, "CancelEvents %p not found", callback);
        return false;
    }

    LOG_DEBUG(logger_, "CancelEvent %d.%d -> %p", p->second->first.tv_sec, p->second->first.tv_nsec, callback);
    Context *ct = p->first;

    schedule_.erase(p->second);
    events_.erase(p);

    if(ct != NULL)
    {
        delete ct;
    }

    return true;
}

bool SafeTimer::CancelAllEvents()
{
    LOG_INFO(logger_, "cancle all events");

    while(!events_.empty())
    {
        map<Context*, multimap<UTime, Context*>::iterator>::iterator p = events_.begin();
        LOG_INFO(logger_, "cancelled %d.%d -> %p", p->second->first.tv_sec, p->second->first.tv_nsec, p->first);

        Context *ct = p->first;
        schedule_.erase(p->second);
        events_.erase(p);
        if (ct != NULL)
        {
            delete ct;
        }
    }

    return true;
}

}
