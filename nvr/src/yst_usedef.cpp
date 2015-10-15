#include "yst_usedef.h"
#include "common.h"
#include "src/transform_encode.h"

#include <QObject>
#if defined(Q_OS_WIN32)
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#elif defined(Q_OS_LINUX)
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

// register function
void YST_ClientConnectCallBack(int nLocalChannel, unsigned char uchType, char *pMsg, int nPWData)
{

}

void YST_ClientNormalDataCallBack(int nLocalChannel, unsigned char uchType,
                                  unsigned char *pBuffer, int nSize, int nWidth, int nHeight)
{

}

void YST_ClientCheckResultCallBack(int nLocalChannel, unsigned char *pBuffer, int nSize)
{

}

void YST_ClientChatDataCallBack(int nLocalChannel, unsigned char uchType,
                                unsigned char *pBuffer, int nSize)
{

}

void YST_ClientTextDataCallBack(int nLocalChannel, unsigned char uchType,
                                unsigned char *pBuffer, int nSize)
{

}

void YST_ClientDownloadCallBack(int nLocalChannel, unsigned char uchType,
                                unsigned char *pBuffer, int nSize, int nFileLen)
{

}

void YST_ClientPlayDataCallBack(int nLocalChannel, unsigned char uchType, unsigned char *pBuffer,
                                int nSize, int nWidth, int nHeight, int nTotalFrame)
{

}

// lan search function
void YST_ClientLanSearchCallBack(STLANSRESULT stLSResult)
{
    logger->warn("receive lan search callback");

	if (stLSResult.bTimoOut != 0)
	{
        logger->debug("lan search: timeout");
		return;
	}

    SearchResult *result = new SearchResult();
    result->group = QString::fromLocal8Bit(stLSResult.chGroup);
    result->name = gbk_2_utf8((char *)(stLSResult.chDeviceName));
    result->client_ip = QString::fromLatin1(stLSResult.chClientIP);
    result->client_port = stLSResult.nClientPort;
    result->yst_id = stLSResult.nYSTNO;
    result->protocol_type = QObject::tr("cloudsee");
    result->manufacture = QObject::tr("jovision");

    w->SearchCallBack(result);
    
    return;
}

void YST_ClientBcCallBack(int bc_id, unsigned char *buffer, int size, char ip[], int timeout)
{
    logger->warn("receive bc callback");
    if (timeout != 0)
	{
        logger->debug("bc callback: timeout");

		return;
	}

    SearchResult *result = new SearchResult();
    BCPACKET *packet = (BCPACKET *)buffer;

    in_addr addr;
    char temp[16] = {0};
    addr.S_un.S_addr = packet->nlIP;

    result->group = QString::fromLocal8Bit(packet->acGroup);
    result->yst_id = packet->nYSTNO;
    result->name = gbk_2_utf8(packet->acName);
    result->client_ip = QString::fromLatin1(inet_ntoa(addr));
    result->client_port = packet->nPort;
    result->protocol_type = QObject::tr("cloudsee");
    result->manufacture = QObject::tr("jovision");

    w->SearchCallBack(result);

    return;
}
