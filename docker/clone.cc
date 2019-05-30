#include <sched.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mount.h>

using namespace std;

#define STACK_SIZE (1024*1024)

static char container_stack[STACK_SIZE] = {0};

char * const container_args[] = {
    "/bin/bash",
    NULL
};

int container_func(void *arg)
{
    cout << "Container - inside the container, pid is " << getpid() <<"!" << endl;

    sethostname("container", 10);

    // remount "/proc" to make sure the "top" and "ps" show container's information
    if (mount("proc", "rootfs/proc", "proc", 0, NULL) != 0)
    {
        perror("proc");
    }

    /*
    if (mount("sysfs", "rootfs/sys", "sysfs", 0, NULL) != 0)
    {
        perror("sysfs");
    }
    */

    if (mount("none", "rootfs/tmp", "tmpfs", 0, NULL) != 0)
    {
        perror("none");
    }

    /*
    if (mount("udev", "rootfs/dev", "devtmpfs", 0, NULL) != 0)
    {
        perror("udev");
    }
    */

    if (mount("conf/hosts", "rootfs/etc/hosts", "none", MS_BIND, NULL) != 0 ||
          mount("conf/hostname", "rootfs/etc/hostname", "none", MS_BIND, NULL) != 0||
          mount("conf/resolv.conf", "rootfs/etc/resolv.conf", "none", MS_BIND, NULL) != 0)
    {
        perror("conf");
    }

    if (mount("/tmp/t1", "rootfs/mnt", "none", MS_BIND, NULL) != 0)
    {
        perror("mnt");
    }

    /* chroot目录隔离 */
    if (chdir("./rootfs") != 0 || chroot("./") != 0)
    {
        perror("chdir/root");
    }

    //system("mount --make-private -t proc proc /proc");
    execv(container_args[0], container_args);

    cout << "Something's wrong" << endl;

    return 0;
}

int main()
{
    int pid = -1;

    char *stack_top = container_stack + STACK_SIZE;

    cout << "Parent: start container" << endl;

    pid = clone(container_func, (void *)stack_top, SIGCHLD | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | CLONE_NEWNS, NULL);
    if (pid == -1)
    {
        perror("clone error");
        return -1;
    }

    if (waitpid(pid, NULL, 0) < 0)
    {
        perror("wait pid error");
        return -2;
    }

    cout << "Parent: child has terminated" << endl;

    return 0;
}

