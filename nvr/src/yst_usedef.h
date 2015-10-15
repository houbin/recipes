#ifndef YST_DEFINE_H
#define YST_DEFINE_H

#include <QtGlobal>
#include <QString>
#include "inc/JvClient.h"
#include "inc/JVNSDKDef.h"

typedef enum
{
    BC_SEARCH = 0x01,
    BC_GET,
    BC_SET,
    BC_NOPOWER,
    BC_GET_ERRORCODE,
    BC_MAX,
}BC_CMD_E;

class SearchResult
{
public:
   QString group;
   qint32 yst_id;
   quint32 type;
   QString name;
   QString client_ip;
   qint32 client_port;
   QString protocol_type; // cloudsee or onvif
   QString manufacture;
};

typedef struct tagBCPACKET
{
    quint32 nCmd;
    char acGroup[8];
    quint32 nYSTNO;

    quint32 nPort;
    char acName[100];
    quint32 nType;
    quint32 nChannel;

    char acID[32];
    char acPW[32];

    int bDHCP;
    quint32 nlIP;
    quint32 nlNM;
    quint32 nlGW;
    quint32 nlDNS;
    char		acMAC[20];

    quint32 nErrorCode;

    int nPrivateSize;
    char chPrivateInfo[500];

    int sw_flag;
}BCPACKET;

#if defined(Q_OS_WIN32)
void YST_ClientConnectCallBack(int nLocalChannel, unsigned char uchType, char *pMsg, int nPWData);
void YST_ClientNormalDataCallBack(int nLocalChannel, unsigned char uchType,
                                  unsigned char *pBuffer, int nSize, int nWidth, int nHeight);
void YST_ClientCheckResultCallBack(int nLocalChannel, unsigned char *pBuffer, int nSize);
void YST_ClientChatDataCallBack(int nLocalChannel, unsigned char uchType,
                                unsigned char *pBuffer, int nSize);
void YST_ClientTextDataCallBack(int nLocalChannel, unsigned char uchType,
                                unsigned char *pBuffer, int nSize);
void YST_ClientDownloadCallBack(int nLocalChannel, unsigned char uchType,
                                unsigned char *pBuffer, int nSize, int nFileLen);
void YST_ClientPlayDataCallBack(int nLocalChannel, unsigned char uchType, unsigned char *pBuffer,
                                int nSize, int nWidth, int nHeight, int nTotalFrame);

// lan search callback
void YST_ClientLanSearchCallBack(STLANSRESULT stLSResult);

// lan broadcast search callback
void YST_ClientBcCallBack(int bc_id, unsigned char *buffer, int size, char ip[16],  int timeout);

#elif defined(Q_OS_LINUX)

#endif

#endif // end YST_DEFINE_H
