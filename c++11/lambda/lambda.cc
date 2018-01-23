#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  auto print_hello = []()
  {
    cout << "hello, world" << endl;
  };

  print_hello();

  return 0;
}

