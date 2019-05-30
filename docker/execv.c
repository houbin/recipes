#include <stdio.h>
#include <unistd.h>

char * const execv_args[] = {
    "/bin/bash",
    NULL
};

int main()
{
    int ret = 0;
    printf("start execv\n");
    ret = execv(execv_args[0], execv_args);
    if (ret < 0)
    {
        perror("execv error");
        return -1;
    }
    printf("execv ok\n");

    return 0;
}
