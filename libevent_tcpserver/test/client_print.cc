#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include "../src/connection.h"

using namespace tcpserver;

int create_socket()
{
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd <= 0)
    {
        perror("create socket failed");
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(9999);

    socklen_t len = sizeof(struct sockaddr_in);
    int ret = connect(client_fd, (struct sockaddr *)&server_addr, len);
    if (ret != 0)
    {
        perror("connect error");
        return -1;
    }

    return client_fd;
}

int send_msg(int fd, char *msg, int size)
{
    int length = kMsgHeaderSize + size;
    MsgHeader header;
    header.magic_code = kMsgMagicCode;
    header.tag = MSG_TYPE_PRINT;
    header.length = size;

    char *buffer = (char*)malloc(length);
    header.Encode(buffer);
    memcpy(buffer + kMsgHeaderSize, msg, size);

    int ret = send(fd, buffer, length, 0);
    if (ret < 0)
    {
        perror("send error");
        return -1;
    }
    free(buffer);

    return 0;
}

int main()
{
    int ret = 0;
    int count = 0;
    int client_fd = create_socket();
    if (client_fd < 0)
    {
        perror("create socket error");
        return -1;
    }

    printf("client fd %d\n", client_fd);
    
    for (count; count < 100; count++)
    {
        char msg[100] = {0};
        sprintf(msg, "hello, i am %d", count);

        ret = send_msg(client_fd, msg, strlen(msg));
        if (ret < 0)
        {
            printf("send msg error, ret %d\n", ret);
            return -1;
        }

        printf("send msg %d", count);
        sleep(2);
    }
    
    close(client_fd);

    return 0;
}
