#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

void foo(char* p){
    memcpy(p, "01234567890", 32);
}

void foo2(char *p) {
  for (int i = 0; i < 100; i++) {
    cout << "start p[" << i << "]" << endl;
    p[i] = 'a';
    cout << "p[" << i << "] ok " << endl;
  }
} 
int main(int argc, char** argv){
    char* p = new char[10];
    //foo(p);
    delete []p;
    foo2(p);
    printf("p=%s\n", p);
    return 0;
}
