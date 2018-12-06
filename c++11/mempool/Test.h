#ifndef TEST_H_
#define TEST_H_

#include <iostream>
#include <map>
#include "mempool.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class A {
public:
  A(string s, int a) : s(s), a(a) {}
  string s;
  int a;

  void dump() {
    cout << typeid(*this).name() << ": <" << s << ", " << a << ">" << endl;
  }
};
ostream& operator<<(ostream& out, const A& e) {
  out << e.s;
  return out;
}

class Test {
  public:
    MEMPOOL_CLASS_HELPER(Test);
    Test(string s, int a) : s(s), a(a) {}
    void dump() {
      cout << typeid(*this).name() << ": <" << s << ", " << a << ">" << endl;
    }

    void init() {
      for (int i = 0; i < 10; i++) {
        A a("aa", i);
        aa.push_back(a);
        cout << aa << endl;
      }
    }

private:
  string s;
  int a;
  mempool::vector<A> aa;
};


#endif

