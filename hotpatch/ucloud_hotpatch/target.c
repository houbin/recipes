#include <unistd.h>
#include "old.h"

int main() {
    for (;;) {
        print();
        sleep(1);
    }
}
