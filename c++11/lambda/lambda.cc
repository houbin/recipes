#include <iostream>
#include <algorithm>

using namespace std;

static int intcompare(const void *p1, const void*p2)
{
  int i = *(int*)p1;
  int j = *(int*)p2;

  return (i < j);
}

int scan(int *a, int length, std::function<void(int)> process) {
  for (int i = 0; i < length; i++) {
    process(i);
  }

  return 0;
}

int main(int argc, char* argv[])
{
  auto print_hello = []()
  {
    cout << "hello, world" << endl;
  };

  print_hello();

  int a[10] = {1, 3, 6, 4, 5, 7, 8, 9, 2};
  qsort((void*)a, 10, sizeof(int), intcompare);

  for (int i = 0; i < 10; i++) {
    cout << a[i] << " " << endl;
  }

  int b[10] = {1, 3, 6, 4, 5, 7, 8, 9, 2};
  std::sort(b, &b[10], [](int x, int y) {return x<y;});

  for (int i = 0; i < 10; i++) {
    cout << b[i] << " " << endl;
  }

  cout << "start scan" << endl;
  scan(a, 10, [](int i) -> void { cout << i;});
  cout << endl;
  cout << "end scan" << endl;

  cout << "start scan with threshold" << endl;
  int threshold = 6;
  scan(a, 10, [threshold](int i) -> void { if (i > threshold) cout << i;});
  cout << endl;
  cout << "end scan with threshold" << endl;

  cout << "start scan with threshold&" << endl;
  int sum= 0;
  scan(a, 10, [threshold, &sum](int i) -> void { if (i > threshold) cout << i; sum+=i;});
  cout << "sum is " << sum << endl;
  cout << endl;
  cout << "end scan with threshold&" << endl;
  return 0;
}

