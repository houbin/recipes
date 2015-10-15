#ifndef STORAGE_MUTEX_H_
#define STORAGE_MUTEX_H_

#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

namespace util {

class Mutex
{
private:
    const char *name_;
    pthread_mutex_t m_;
    pid_t holder_;

    // no copying
    Mutex(const Mutex &);
    void operator=(const Mutex &);

public:
    Mutex(const char *name);
    ~Mutex();

    bool IsLockedByThisThread();
    void AssertLocked();

    void Lock();
    void Unlock();

    friend class Cond;

    class Locker
    {
    private:
        Mutex &m_;

    public:
        Locker(Mutex& m) : m_(m) { m_.Lock(); }
        ~Locker() { m_.Unlock(); }
    };
};

}

#endif

