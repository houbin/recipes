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
    pfd.events |= POLLRDHUP;

    if (poll(&pfd, 1, 60) < 0)
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
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("create socket error");
        return -1;
    }

    int on = 1;
    int ret = ::setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (ret < 0)
    {
        perror("setsockopt error");
        return -1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(16000);

    ret = bind(fd, (struct sockaddr*)&addr, sizeof(struct sockaddr));
    if (ret < 0)
    {
        perror("bind error");
        return -1;
    }

    ret = listen(fd, 128);
    if (ret < 0)
    {
        perror("listen error");
        return -1;
    }

    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN | POLLERR | POLLNVAL | POLLHUP;
    ret = poll(&pfd, 1, -1);
    if (ret < 0)
    {
        perror("poll error");
        return -1;
    }

    if (pfd.revents & (POLLERR | POLLNVAL | POLLHUP))
        return -1;

    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    socklen_t addr_len = sizeof(struct sockaddr);

    int client_fd = accept(fd, (struct sockaddr*)&client_addr, &addr_len);
    if (client_fd <= 0)
    {
        perror("accept error");
        return -1;
    }

    cout << "client addr is " << inet_ntoa(client_addr.sin_addr) << endl;

    cout << "sleep 1s, and close client_fd" << endl;
    sleep(1);
    ::shutdown(client_fd, SHUT_RDWR);
    cout << "shutdown client fd, sleep 6s" << endl;

    sleep(6);
    close(client_fd);
    cout << "after shutdown, close fd" << endl;
    sleep(1000);

    char buffer[12] = {0};
    sprintf(buffer, "%s", "000000000000");
    ret = send(client_fd, buffer, 12, MSG_DONTWAIT);
    if (ret != 12)
    {
        cout << "send msg error" << endl;
        return -1;
    }
    cout << "send msg ok" << endl;

    sleep(100);

    return 0;


    return 0;
}
