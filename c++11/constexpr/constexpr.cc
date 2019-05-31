#include <iostream>
#include <array>

using namespace std;

constexpr int foo(int i) {
  return i+5;
}

int main() {
  int i = 0;
  std::array<int, foo(5)> arr;

  foo(i);

  std::array<int, foo(i)> arr1;

  return 0;
}

