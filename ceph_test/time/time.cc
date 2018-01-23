#include <iostream>
#include <sys/time.h>
#include <time.h>

using namespace std;

int main()
{
    struct timeval tv;
    struct timespec tp;

    gettimeofday(&tv, NULL);
    clock_gettime(CLOCK_REALTIME, &tp);
    cout << "getimeofday   is " << tv.tv_sec << "." << tv.tv_usec << endl;
    cout << "clock_gettime is " << tp.tv_sec << "." << tp.tv_nsec << endl;



    return 0;
}

