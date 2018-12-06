#ifndef MEMPOOL_H_
#define MEMPOOL_H_
#include <iostream>
#include <vector>
#include <atomic>
#include <typeinfo>

using namespace std;

template<typename T>
class pool_allocator {
public:
  std::atomic<ssize_t> bytes;

  T* allocate(size_t n, void *p = NULL) {
    size_t total = n * sizeof(T);

    bytes += total;
    cout << __func__ << typeid(T).name() << " allocate " << total << " bytes" << endl;
    return reinterpret_cast<T*>(new char[total]);
  }

  void deallocate(T* p, size_t n) {
    size_t total = sizeof(T) * n;
    bytes -= total;

    cout << __func__ << typeid(T).name() << ", deallocate " << total << " bytes" << endl; 
    delete[] reinterpret_cast<char*>(p);
  }

  pool_allocator(bool b) {}
};

namespace mempool {
  template<typename v>
  using vector = std::vector<v, pool_allocator<v>>;
}

#define MEMPOOL_DEFINE_FACTORY(obj, factoryname) \
  namespace mempool { \
    pool_allocator<obj> alloc_##factoryname = {true}; \
  }

#define MEMPOOL_CLASS_HELPER(factoryname) \
  void *operator new(size_t size); \
  void operator delete(void *); 

#define MEMPOOL_CLASS_DEFINE(obj, factoryname) \
  MEMPOOL_DEFINE_FACTORY(obj, factoryname); \
  void *obj::operator new(size_t size) { \
    return mempool::alloc_##factoryname.allocate(1); \
  } \
  void obj::operator delete(void *p) { \
    return mempool::alloc_##factoryname.deallocate((obj*)p, 1);\
  }
    
#endif

