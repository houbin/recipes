#include <iostream>
#include "mempool.h"

using namespace std;

class TestMalloc {
  private:
    char *c;
  public:
    MEMPOOL_CLASS_HELPER();
    Test() {
      c = (char *)malloc(1024);
    }
};

MEMPOOL_CLASS_DEFINE(Test, test);

int main() {
  Test *t = new Test();

  return 0;
}

