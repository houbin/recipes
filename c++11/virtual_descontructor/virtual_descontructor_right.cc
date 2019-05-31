#include <iostream>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

class Base {
  private:
    uint64_t a;
    uint64_t b;
  public:
    Base() { cout << "Base()" << endl; }
    virtual ~Base() { cout << "~Base()" << endl; }
};

class Derive : public Base {
  private:
    char *a;
  public:
    Derive() : Base() 
    {
      cout << "Derive" << endl; 
      a = (char *)malloc(1024);
      memset(a, 'a', 1024);
    }
    virtual ~Derive() 
    {
      cout << "~Derive" << endl;
      delete a;
    }
};

int main() {
  Base *base = NULL;

  for (int i = 0; i < 10000000; i++) {
    base = new Derive();
    delete base;
  }

  usleep(100*1000*1000);

  return 0;
}
