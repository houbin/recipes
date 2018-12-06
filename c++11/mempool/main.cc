#include <iostream>
#include "Test.h"

using namespace std;

MEMPOOL_CLASS_DEFINE(Test, test);

int main() {
  Test* t = new Test("houbin", 1);
  t->init();
  
  return 0;
}
