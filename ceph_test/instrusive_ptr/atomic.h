#ifndef ATOMIC_H_
#define ATOMIC_H_

#include <stdint.h>

using namespace std;

template<typename T>
class AtomicIntegerT
{
public:
    AtomicIntegerT()
    : value_(0)
	{}

    T Get()
    {
        return __sync_val_compare_and_swap(&value_, 0, 0);
    }

    T GetAndAdd(T x)
    {
        return __sync_fetch_and_add(&value_, x);
    }

    T AddAndGet(T x)
    {
        return GetAndAdd(x) + x;
    }

    T IncAndGet()
    {
        return AddAndGet(1);
    }

    T DecAndGet()
    {
        return AddAndGet(-1);
    }

    void Add(T x)
    {
        GetAndAdd(x);
    }

    T Inc()
    {
        return IncAndGet();
    }

    T Dec()
    {
        return DecAndGet();
    }

    T GetAndSet(T new_value)
    {
        return __sync_lock_test_and_set(&value_, new_value);
    }

private:
    T value_;
};

typedef AtomicIntegerT<int32_t> AtomicInt32;
typedef AtomicIntegerT<int64_t> AtomicInt64;

#endif

