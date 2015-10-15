#ifndef TCP_SERVER_CONNECTION_H_
#define TCP_SERVER_CONNECTION_H_

#include <event.h>
#include "../util/coding.h"

enum MsgType
{
    MSG_TYPE_PRINT = 0,
    MSG_TYPE_ECHO = 1,
    MSG_TYPE_PINGPONG = 2
};

#define CONN_BUFFER_LEN (2048)
#define MAX_MSG_LENGTH 2048
static const uint32_t kMsgMagicCode = 0x49564f4a;
static const int kMsgHeaderSize = 4 + 4 + 4;

namespace tcpserver
{

typedef struct _ConnectionInfo
{
    uint64_t conn_id;
    int cfd;
    
    uint32_t cip;
    uint16_t cport;

    struct bufferevent *buffer_event;
    char in_buffer[CONN_BUFFER_LEN];
    uint16_t in_buffer_len;
    char out_buffer[CONN_BUFFER_LEN];
    uint16_t out_buffer_len;
}ConnectionInfo;

class MsgHeader
{
public:
    uint32_t magic_code;
    uint32_t tag;
    uint32_t length;
    char value[0];

    void Encode(char *buffer);
    void Decode(char *buffer);
};

}

#endif

