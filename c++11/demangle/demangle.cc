#include <iostream>
#include <typeinfo>
#include <string>
#include <cxxabi.h>

using namespace std;
struct Test {
  int a;
  string b;
};

void print_type(const char *name)
{
  cout << "name of type_info " << name << endl;

  char buffer[128] = {0};
  size_t size = sizeof(buffer);
  int status;
  char *ret;
  if (ret = abi::__cxa_demangle(name, buffer, &size, &status)) {
    cout << "after demangle, name is " << std::string(ret) << endl;
  }

  return;
}

int main() {
  string s = "houbin";
  print_type(typeid(s).name());
  print_type(typeid(string).name());
  print_type(typeid(Test).name());


  return 0;
}
