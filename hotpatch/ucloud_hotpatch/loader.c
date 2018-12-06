#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <dlfcn.h>

void usage() {
  printf("Usage: loader -p [pid]\n");
}

// Take a hint and find start addr in /proc/pid/maps 
static unsigned long find_lib_base(pid_t pid, char *so_hint)
{
  FILE *fp;
  char maps[4096], mapbuf[4096], perms[32], libpath[4096];
  char *libname;
  unsigned long start, end, file_offset, inode, dev_major, dev_minor;
  
  sprintf(maps, "/proc/%d/maps", pid);
  fp = fopen(maps, "rb");
  if (!fp) {
          fprintf(stderr, "Failed to open %s: %s\n", maps, strerror(errno));
          return 0;
  }
  
  while (fgets(mapbuf, sizeof(mapbuf), fp)) {
          sscanf(mapbuf, "%lx-%lx %s %lx %lx:%lx %lu %s", &start,
                  &end, perms, &file_offset, &dev_major, &dev_minor, &inode, libpath);
  
          libname = strrchr(libpath, '/');
          if (libname)
                  libname++;
          else
                  continue;
  
          if (!strncmp(perms, "r-xp", 4) && strstr(libname, so_hint)) {
                  fclose(fp);
                  return start;
          }
  }
  
  fclose(fp);   
  return 0; 
}

static int ptrace_attach(pid_t pid) {
  int status;

  if (ptrace(PTRACE_ATTACH, pid, NULL, NULL)) {
    fprintf(stderr, "Failed to ptrace attach: %s\n", strerror(errno));
    return 1;
  }

  if (waitpid(pid, &status, __WALL) < 0) {
    fprintf(stderr, "Failed to wait for PID %d, %s\n", pid, strerror(errno));
    return 1;
  }

  return 0;
}

static int ptrace_getregs(pid_t pid, struct user_regs_struct* regs) {
  if (!regs) {
    return -1;
  }

  memset(regs, 0, sizeof(struct user));
  if (ptrace(PTRACE_GETREGS, pid, NULL, regs) < 0) {
    int err = errno;
    fprintf(stderr, "[%s:%d], ptrace getregs for PID %d failed with error:%s\n", __func__, __LINE__, pid, strerror(err));
    return -1;
  }

  return 0;
}

static int ptrace_setregs(pid_t pid, struct user_regs_struct* regs) {
  if (!regs) {
    return -1;
  }

  if (ptrace(PTRACE_SETREGS, pid, NULL, regs) < 0) {
    int err = errno;
    fprintf(stderr, "[%s:%d], ptrace setregs for PID %d failed with error:%s\n", __func__, __LINE__, pid, strerror(err));
    return -1;
  }

  return 0;
}

static int ptrace_poketext(pid_t pid, unsigned long long int rsp, void *addr, size_t len) {
  long ret = 0;

  ret = ptrace(PTRACE_POKETEXT, pid, addr, (void *)len);
  if (ret != 0) {
    fprintf(stderr, "ptrace poketext error, ret is %s\n", strerror(errno));
    return -1;
  }

  return 0;
}

static int ptrace_detach(pid_t pid) {
  long ret = 0;

  ret = ptrace(PTRACE_DETACH, pid, NULL, NULL);
  if (ret != 0) {
    fprintf(stderr, "ptrace poketext error\n");
    return -1;
  }

  return 0;
}

static int ptrace_cont(pid_t pid) {
  int status;

  if (ptrace(PTRACE_CONT, pid, NULL, 0)) {
    fprintf(stderr, "Failed to ptrace_cont: %s\n", strerror(errno));
    return -1;
  }
  
  if (waitpid(pid, &status, __WALL) < 0) {
    fprintf(stderr, "Failed to wait for PID %d, %s\n", pid, strerror(errno));
    return -1;
  }
  
  return 0;
}

static int ptrace_call(pid_t pid, unsigned long long int func_addr, unsigned long arg1, unsigned long arg2, unsigned long *func_ret) {
  int ret = 0;
  struct user_regs_struct regs;
  struct user_regs_struct saved_regs;
  char filename[64] = "./libnew.so";
  unsigned long invalid = 0x00;
  unsigned long long int dlopen_ret = 0;

  memset(&saved_regs, 0, sizeof(struct user_regs_struct));
  ret = ptrace_getregs(pid, &saved_regs);
  if (ret != 0) {
    printf("ptrace_getregs error, ret is %d\n", ret);
    return -1;
  }

  memcpy(&regs, &saved_regs, sizeof(struct user_regs_struct));
  regs.rsp -= sizeof(invalid);
  ret = ptrace_poketext(pid, regs.rsp, (void*)&invalid, sizeof(invalid));
  if (ret != 0) {
    return -1;
  }
  ptrace_poketext(pid, regs.rsp+512, filename, strlen(filename) + 1);
  regs.rip = func_addr;
  regs.rdi = regs.rsp + 512;
  regs.rsi = RTLD_NOW;
  ptrace_setregs(pid, &regs);

  ptrace_cont(pid);

  ptrace_getregs(pid, &regs);
  dlopen_ret = regs.rax;
  ptrace_setregs(pid, &saved_regs);

  return 0;
}

int main(int argc, char *argv[]) 
{
  int c = 0;
  int ret = 0;
  pid_t t_pid = 0;
  unsigned long long int loader_libc;
  unsigned long long int loader_dlopen;

  // target libc and dlopen address
  unsigned long long int T_libc;
  unsigned long long int T_dlopen;
  struct user_regs_struct saved_regs;

  while ((c = getopt(argc, argv, "p:h")) != -1)
  {
      switch (c)
      {
          case 'p':
              t_pid = atoi(optarg);
              break;
          case 'h':
          default:
              usage();
              return 0;
      }
  }
  printf("target pid: %d\n", t_pid);

  // loader libc and dlopen address
  loader_libc = find_lib_base(getpid(), "libc-");
  loader_dlopen = (unsigned long)dlsym(NULL, "__libc_dlopen_mode");

  // target libc and dlopen address
  T_libc = find_lib_base(t_pid, "libc-");
  T_dlopen = T_libc + (loader_dlopen - loader_libc); 
  
  printf("loader_libc is %lx\n", loader_libc);
  printf("T_libc is %lx\n", T_libc);
  printf("loader_dlopen is %lx\n", loader_dlopen);
  printf("T_dlopen is %lx\n", T_dlopen);

  // attach target pid
  ret = ptrace_attach(t_pid);
  if (ret != 0) {
    printf("ptrace_attach error, ret is %d\n", ret);
    return -1;
  }

  ret = ptrace_call(t_pid, T_dlopen, 0, 0, 0);
  if (ret != 0) {
    printf("ptrace_call dlopen error, ret is %d\n", ret);
    return -1;
  }

  ptrace_detach(t_pid);

  return 0;
}

