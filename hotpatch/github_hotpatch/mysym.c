#include <hotpatch_config.h>
#include <stdio.h>


void init() {
  time_t timep;
  time(&timep);
  printf("time: %s, new patch init\n\n\n", asctime(gmtime(&timep)) );
}

int func(char *data, int len) {
    time_t timep;
      time (&timep);

        printf("time: %s, new patch\n\n\n", asctime(gmtime(&timep)));


  return 0;
}

