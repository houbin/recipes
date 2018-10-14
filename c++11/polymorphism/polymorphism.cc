#include <typeinfo>
#include <iostream>

using namespace std;

struct A {
  void foo() {
    cout << "print A" << endl;
  }
};

struct Base {
  virtual void foo() {
    
  }
};

struct Derive : public Base { 
  
};

int main(int argc, char *argv[]) {
  int  ret = 0;
  A a;
  A bb;
  cout << "name of A: " << typeid(a).name() << endl;
  cout << "sizeof A: " << sizeof(a) << endl;

  cout << "name of BB: " << typeid(bb).name() << endl;
  cout << "sizeof BB: " << sizeof(bb) << endl;

  {
    Derive b;
    Base &a = b;

	cout << "decltype(a) is " << typeid(decltype(a)).name() << endl;
	cout << "typeid(a) is " << typeid(a).name() << endl;

	cout << "sizeof(a) is " << sizeof(a) << endl;
  
  }
  
  return 0;
}
