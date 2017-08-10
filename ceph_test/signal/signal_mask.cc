#include <iostream>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

typedef void     (*pFunc)(int);

void handle_signal_action(int sig_num)
{
    switch (sig_num)
    {
        case SIGSYS:
            cout << "signal SIGSYS" << endl;
            break;
        
        case SIGABRT:
            cout << "signal SIGABRT" << endl;
            break;

        case SIGSEGV:
            cout << "signal SIGSEGV" << endl;
            break;

        default:
            cout << "Unknown signal" << endl;
    }

    return;
}

int install_signal_action(int sig_num, pFunc func, int sa_flags)
{
    struct sigaction sa;
    struct sigaction old_sa;
    memset((void *)&sa, sizeof(struct sigaction), 0);

    sa.sa_handler = handle_signal_action;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = sa_flags;
    
    int ret = sigaction(sig_num, &sa, &old_sa);
    if (ret != 0)
    {
        perror("sigaction error");
        return -1;
    }
    
    return 0;
}

int main()
{
    install_signal_action(SIGSEGV, handle_signal_action, SA_RESETHAND | SA_NODEFER);
    install_signal_action(SIGABRT, handle_signal_action, SA_RESETHAND | SA_NODEFER);
    install_signal_action(SIGBUS, handle_signal_action, SA_RESETHAND | SA_NODEFER);

    sleep(1000);

    return 0;
}



