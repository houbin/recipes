#include "mutex.h"

namespace util
{

Mutex::Mutex(const char* name)
: name_(name), holder_(0)
{
    pthread_mutex_init(&m_, NULL);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&m_);
}

bool IsLockedByThisThread()
{
    return (getpid() == holder_);
}

void AssertLocked()
{
    assert(IsLockedByThisThread());
}

void Mutex::Lock()
{
    pthread_mutex_lock(&m_);
    holder_ = getpid();
}

void Mutex::Unlock()
{
    holder_ = 0;
    pthread_mutex_unlock(&m_);
}

}

