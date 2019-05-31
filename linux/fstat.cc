#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/vfs.h>

using namespace std;

int main() {
  int fd = open("./fstat.cc", O_RDWR);
  if (fd < 0) {
    cout << "open error, ret is " << errno << endl;
    return -1;
  }

  struct stat st;
  int r = fstat(fd, &st);
  if (r < 0) {
    cout << "fstat error" << endl;
    return -1;
  }

  cout << "blksize is " << st.st_blksize << endl;

  struct statfs stfs;
  fstatfs(fd, &stfs);
  cout << "fs type is " << stfs.f_type << endl;
  return 0;
}
