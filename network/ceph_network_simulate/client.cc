#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>

using namespace std;

int tcp_read_wait(int fd)
{
    if (fd < -1)
        return -1;

    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;
    cout << "before POOL pfd.events is " << pfd.events << endl;
    pfd.events |= POLLRDHUP;
    cout << "pfd.events is " << pfd.events << endl;

    if (poll(&pfd, 1, 60*1000) <= 0)
        return -2;

    short evmask = 0;
    evmask = POLLERR | POLLRDHUP | POLLHUP | POLLNVAL;
    if (pfd.revents & evmask)
        return -3;

    if (!(pfd.revents & POLLIN))
        return -4;

    return 0;
}
int tcp_read(int fd, char *buffer, int length)
{
    while (length > 0)
    {
        int ret = tcp_read_wait(fd);
        if (ret < 0)
            return ret;

        sleep(20);
        ret = recv(fd, buffer, length, MSG_DONTWAIT);
        if (ret < 0)
        {
            perror("recv error");
            return -errno;
        }

        buffer += ret;
        length -= ret;
    }

    return 0;
}

int main()
{
    int ret = 0;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("create socket error");
        return -1;
    }

    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//client_addr.sin_port = htons(12345);

    ret = bind(fd, (struct sockaddr*)&client_addr, sizeof(struct sockaddr));
    if (ret != 0) {
      perror("bind error");
      return -1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(16000);

    ret = connect(fd, (struct sockaddr*)&addr, sizeof(struct sockaddr));
    if (ret < 0)
    {
        perror("connect error");
        return -1;
    }


#define BANNER_SIZE 12
    char buffer[BANNER_SIZE] = {0};
    memset(buffer, 'a', 11);
    ret = send(fd, buffer, 12, 0);
    if (ret < 0)
    {
        cout << "tcp_read error, ret " << ret << endl;
        return -1;
    }
    cout << "read msg " << buffer << endl;
    sleep(100);

    close(fd);

    return 0;
}
