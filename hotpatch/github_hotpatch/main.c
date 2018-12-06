#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stddef.h>

int func(int ret) {
  time_t timep;
  time (&timep);

  printf("time: %s, ret is %d\n\n\n", asctime(gmtime(&timep)), ret);

  return 0;
}

int main() {
  int ret = 0;

  for (ret; ret < 1000; ret++) {
    func(ret);
    sleep(30);
  }

  return 0;
}
