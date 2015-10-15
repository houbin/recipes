#ifndef _JVNSDKDEF_H
#define _JVNSDKDEF_H

#ifndef WIN32
	#include <sys/socket.h>
	typedef struct _GUID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[ 8 ];
	} GUID;
    #define MAX_PATH 256
#else
	#include <winsock2.h>
#endif

/*ʵʱ�����������*/
#define JVN_DATA_I           0x01//��ƵI֡
#define JVN_DATA_B           0x02//��ƵB֡
#define JVN_DATA_P           0x03//��ƵP֡
#define JVN_DATA_A           0x04//��Ƶ
#define JVN_DATA_S           0x05//֡�ߴ�
#define JVN_DATA_OK          0x06//��Ƶ֡�յ�ȷ��
#define JVN_DATA_DANDP       0x07//���ػ�ط��յ�ȷ��
#define JVN_DATA_O           0x08//�����Զ�������
#define JVN_DATA_SKIP        0x09//��ƵS֡
#define JVN_DATA_SPEED		 0x64//��������
/*��������*/
#define JVN_REQ_CHECK        0x10//����¼�����
#define JVN_REQ_DOWNLOAD     0x20//����¼������
#define JVN_REQ_PLAY         0x30//����Զ�̻ط�
#define JVN_REQ_CHAT         0x40//������������
#define JVN_REQ_TEXT         0x50//�����ı�����
#define JVN_REQ_CHECKPASS    0x71//���������֤
#define JVN_REQ_RECHECK      0x13//Ԥ��֤
#define JVN_REQ_RATE		 0x63//�ֿ���������
	
/*���󷵻ؽ������*/
#define JVN_RSP_CHECKDATA    0x11//�������
#define JVN_RSP_CHECKOVER    0x12//�������
#define JVN_RSP_DOWNLOADDATA 0x21//��������
#define JVN_RSP_DOWNLOADOVER 0x22//�����������
#define JVN_RSP_DOWNLOADE    0x23//��������ʧ��
#define JVN_RSP_PLAYDATA     0x31//�ط�����
#define JVN_RSP_PLAYOVER     0x32//�ط����
#define JVN_RSP_PLAYE        0x39//�ط�ʧ��
#define JVN_RSP_CHATDATA     0x41//��������
#define JVN_RSP_CHATACCEPT   0x42//ͬ����������
#define JVN_RSP_TEXTDATA     0x51//�ı�����
#define JVN_RSP_TEXTACCEPT   0x52//ͬ���ı�����
#define JVN_RSP_CHECKPASS    0x72//�����֤
#define JVN_RSP_CHECKPASST   0x72//�����֤�ɹ� ΪTCP����
#define JVN_RSP_CHECKPASSF   0x73//�����֤ʧ�� ΪTCP����
#define JVN_RSP_NOSERVER     0x74//�޸�ͨ������
#define JVN_RSP_INVALIDTYPE  0x7A//����������Ч
#define JVN_RSP_OVERLIMIT    0x7B//���ӳ�����������������Ŀ
#define JVN_RSP_DLTIMEOUT    0x76//���س�ʱ
#define JVN_RSP_PLTIMEOUT    0x77//�طų�ʱ
#define JVN_RSP_RECHECK      0x14//Ԥ��֤
#define JVN_RSP_OLD          0x15//�ɰ����ػظ�

/*��������*/
#define JVN_CMD_DOWNLOADSTOP 0x24//ֹͣ��������
#define JVN_CMD_PLAYUP       0x33//���
#define JVN_CMD_PLAYDOWN     0x34//����
#define JVN_CMD_PLAYDEF      0x35//ԭ�ٲ���
#define JVN_CMD_PLAYSTOP     0x36//ֹͣ����
#define JVN_CMD_PLAYPAUSE    0x37//��ͣ����
#define JVN_CMD_PLAYGOON     0x38//��������
#define JVN_CMD_CHATSTOP     0x43//ֹͣ��������
#define JVN_CMD_PLAYSEEK     0x44//���Ŷ�λ		��֡��λ ��Ҫ���� ֡��(1~���֡)
#define JVN_CMD_TEXTSTOP     0x53//ֹͣ�ı�����
#define JVN_CMD_YTCTRL       0x60//��̨����
#define JVN_CMD_VIDEO        0x70//ʵʱ���
#define JVN_CMD_VIDEOPAUSE   0x75//��ͣʵʱ���
#define JVN_CMD_TRYTOUCH     0x78//�򶴰�
#define JVN_CMD_FRAMETIME    0x79//֡����ʱ����(��λms)
#define JVN_CMD_DISCONN      0x80//�Ͽ�����
#define JVN_CMD_MOTYPE		 0x72//UDP�ֻ����� ע����ֵ������һ���Ͷ���ֵ��ͬ����Ӧ���⣬�ݱ�������
#define JVN_CMD_ONLYI        0x61//��ͨ��ֻ���ؼ�֡
#define JVN_CMD_FULL         0x62//��ͨ���ָ���֡
#define JVN_CMD_ALLAUDIO	 0x65//��Ƶȫת��

/*������ͨ�������Ľ�����Ϣ*/
#define JVN_CMD_TOUCH        0x81//̽���
#define JVN_REQ_ACTIVEYSTNO  0x82//�������󼤻�YST����
#define JVN_RSP_YSTNO        0x82//����������YST����
#define JVN_REQ_ONLINE       0x83//������������
#define JVN_RSP_ONLINE       0x84//������������������
#define JVN_CMD_ONLINE       0x84//���ص�ַ����
#define JVN_CMD_OFFLINE      0x85//��������
#define JVN_CMD_KEEP         0x86//���ر���
#define JVN_REQ_CONNA        0x87//�ֿ��������ص�ַ udpʱͣ��
#define JVN_RSP_CONNA        0x87//��������ֿط������ص�ַ
#define JVN_CMD_CONNB        0x87//����������������ֿش�͸
#define JVN_RSP_CONNAF       0x88//��������ֿط��� ����δ����
#define JVN_CMD_RELOGIN		 0x89//֪ͨ�������µ�½
#define JVN_CMD_CLEAR		 0x8A//֪ͨ�������߲����������Ϣ��������ͨ����
#define JVN_CMD_REGCARD		 0x8B//����ע��忨��Ϣ��������


#define JVN_CMD_CONNB2				0xB0        //�ֿ������������� ������


#define JVN_CMD_ONLINES2     0x8C//����������������ת������������/������ת������������(ͣ��)
#define JVN_CMD_CONNS2       0x8D//����������ֿ���ת����������������
#define JVN_REQ_S2           0x8E//�ֿ������������ת��
#define JVN_TDATA_CONN       0x8F//�ֿ���ת����������������(ͣ��)
#define JVN_TDATA_NORMAL     0x90//�ֿ�/������ת��������������ͨ����
#define JVN_TDATA_AOL        0x8E//������ת������������(��)
#define JVN_TDATA_BCON       0x8D//�ֿ���ת����������������(��)

#define JVN_CMD_CARDCHECK    0x91//�忨��֤
#define JVN_CMD_ONLINEEX     0x92//���ص�ַ������չ
#define JVN_CMD_TCPONLINES2  0x93//��������������TCP��ת������������
#define JVN_CMD_CHANNELCOUNT 0x97//�ֿز�ѯ���������е�ͨ����Ŀ
#define JVN_CMD_ONLINE1EX    0x9C//����UDP1������չ(������)
#define JVN_REQ_MOS2		 0x9D//3G�ֻ������������ת��
#define YST_A_NEW_ADDRESS    0x100//�ֿز�ѯNATʹ�� ���ط��ط������µ�NAT

//---------------------------------------v2.0.0.1
#define JVN_CMD_BM           0x94//BM�㲥��Ϣ A->B
#define JVN_CMD_TCP          0x95//�ڵ��TCP���� B->B
#define JVN_CMD_KEEPLIVE     0x96//�ֿغ����ؼ����������
#define JVN_CMD_PLIST        0x98//���Ա�б�       A->B B->A
#define JVN_RSP_BMDBUSY      0x99//�ظ�ĳ����Ƭ����æµ B->B A->B
#define JVN_CMD_CMD          0x9A//����Ҫ��ֿ�ִ��������� A->B
#define JVN_CMD_ADDR         0x9B//�ֿؽڵ���������ַ A->B

#define JVN_REQ_BMD          0x9D//����ĳ����Ƭ B->A B->B
#define JVN_RSP_BMD          0x9E//�ظ�ĳ����Ƭ A->B B->B
#define JVN_CMD_LADDR        0x9F//�ֿ��ϴ��Լ���������ַ
#define JVN_RSP_BMDNULL      0xA0//�ظ�ĳ����Ƭʧ�� A->B B->B
#define JVN_CMD_TRY          0xA1//A����B �����
#define JVN_DATA_RATE        0xA2//�ಥ��С����ʱ�Ļ������
//---------------------------------------v2.0.0.1

/*������չ*/
#define JVN_CMD_YSTCHECK     0xAC//��ѯ������ĳ�����Ƿ������Լ���������SDK�汾
#define JVN_REQ_EXCONNA      0xAD//�ֿ��������ص�ַ
#define JVN_CMD_KEEPEX       0xAE//����������չ(������+���+ʱ���)
#define JVN_CMD_OLCOUNT      0xAF//��ȡ��ǰ��������������Ŀ

/*�ͻ�����ý����������*/
#define JVN_REQ_CONNSTREAM_SVR    0xD0//����������ý�����������
#define JVN_REQ_CONNSTREAM_CLT    0xD1//����������ý��������ֿ�
#define JVN_RSP_CONNSTREAM_SVR    0xD2//�ظ�
#define JVN_RSP_CONNSTREAM_CLT    0xD3
#define JVN_NOTIFY_ID			  0xD4
#define JVN_RSP_ID				  0xD5
#define JVN_CMD_CONNSSERVER		  0xD6
#define JVN_RSP_NEWCLIENT         0xD9

/*�������豸����*/
#define JVN_REQ_LANSERCH  0x01//�������豸��������
#define JVN_CMD_LANSALL   1//����������������ά�豸
#define JVN_CMD_LANSYST   2//����������ָ������ͨ������豸
#define JVN_CMD_LANSTYPE  3//����������ָ����ϵ���豸
#define JVN_CMD_LANSNAME  4//����������ָ���������豸
#define JVN_RSP_LANSERCH  0x02//�������豸������Ӧ����

#define JVN_DEVICENAMELEN  100//�豸������������

/*�������㲥*/
#define JVN_REQ_BC  0x03//�������㲥����
#define JVN_RSP_BC  0x04//�������㲥��Ӧ����

#define JVN_ALLSERVER     0//���з���
#define JVN_ONLYNET       1//ֻ����������

#define JVN_NOTURN        0//����ͨ��ʽʱ����ת��
#define JVN_TRYTURN       1//����ͨ��ʽʱ����ת��
#define JVN_ONLYTURN      2//����ͨ��ʽʱ����ת��

#define JVN_LANGUAGE_ENGLISH  1
#define JVN_LANGUAGE_CHINESE  2

#define TYPE_PC_UDP      1//�������� UDP ֧��UDP�շ���������
#define TYPE_PC_TCP      2//�������� TCP ֧��TCP�շ���������
#define TYPE_MO_TCP      3//�������� TCP ֧��TCP�շ�������,��ͨ��Ƶ֡�Ȳ��ٷ��ͣ�ֻ�ܲ���ר�ýӿ��շ�����(�������ֻ����)
#define TYPE_MO_UDP      4//�������� UDP 
#define TYPE_3GMO_UDP    5//�������� 3GUDP
/*������������*/
#define CMD_TYPE_CLEARBUFFER    1//���غͷֿ���ջ��棬���½��л���

/*��̨��������*/
#define JVN_YTCTRL_U      1//��
#define JVN_YTCTRL_D      2//��
#define JVN_YTCTRL_L      3//��
#define JVN_YTCTRL_R      4//��
#define JVN_YTCTRL_A      5//�Զ�
#define JVN_YTCTRL_GQD    6//��Ȧ��
#define JVN_YTCTRL_GQX    7//��ȦС
#define JVN_YTCTRL_BJD    8//�佹��
#define JVN_YTCTRL_BJX    9//�佹С
#define JVN_YTCTRL_BBD    10//�䱶��
#define JVN_YTCTRL_BBX    11//�䱶С

#define JVN_YTCTRL_UT     21//��ֹͣ
#define JVN_YTCTRL_DT     22//��ֹͣ
#define JVN_YTCTRL_LT     23//��ֹͣ
#define JVN_YTCTRL_RT     24//��ֹͣ
#define JVN_YTCTRL_AT     25//�Զ�ֹͣ
#define JVN_YTCTRL_GQDT   26//��Ȧ��ֹͣ
#define JVN_YTCTRL_GQXT   27//��ȦСֹͣ
#define JVN_YTCTRL_BJDT   28//�佹��ֹͣ
#define JVN_YTCTRL_BJXT   29//�佹Сֹͣ
#define JVN_YTCTRL_BBDT   30//�䱶��ֹͣ
#define JVN_YTCTRL_BBXT   31//�䱶Сֹͣ
#define JVN_YTCTRL_FZ1    32//����1
#define JVN_YTCTRL_FZ1T   33//����1ֹͣ
#define JVN_YTCTRL_FZ2    34//����2
#define JVN_YTCTRL_FZ2T   35//����2ֹͣ
#define JVN_YTCTRL_FZ3    36//����3
#define JVN_YTCTRL_FZ3T   37//����3ֹͣ
#define JVN_YTCTRL_FZ4    38//����4
#define JVN_YTCTRL_FZ4T   39//����4ֹͣ

#define JVN_YTCTRL_RECSTART  41//Զ��¼��ʼ
#define JVN_YTCTRL_RECSTOP	 42//Զ��¼��ʼ

/*Զ�̿���ָ��(���ֿ�Ӧ�ò�Լ��)*/
#define RC_DISCOVER		0x01 
#define RC_GETPARAM		0x02 
#define RC_SETPARAM		0x03 
#define RC_VERITY		0x04 
#define RC_SNAPSLIST	0x05 
#define RC_GETFILE		0x06 
#define RC_USERLIST		0x07 
#define RC_PRODUCTREG	0X08 
#define RC_GETSYSTIME	0x09 
#define RC_SETSYSTIME	0x0a 
#define RC_DEVRESTORE	0x0b 
#define RC_SETPARAMOK	0x0c 
#define RC_DVRBUSY		0X0d 
#define RC_GETDEVLOG	0x0e 
#define RC_DISCOVER2	0x0f	//zwq20111206,csst����ͨ����ֱ�ӵ�¼���������㲥����

#define JVN_VC_BrightUp			0x10 //��Ƶ����
#define JVN_VC_BrightDown		0x11
#define JVN_VC_ContrastUp		0x12
#define JVN_VC_ContrastDown		0x13
#define JVN_VC_SaturationUp		0x14
#define JVN_VC_SaturationDown	0x15
#define JVN_VC_HueUp			0x16
#define JVN_VC_HueDown			0x17
#define JVN_VC_SharpnessUp		0x18
#define JVN_VC_SharpnessDown	0x19
#define JVN_VC_PRESENT          0x20 //Ԥ��λ����

typedef struct _PLAY_INFO_
{
	unsigned char ucCommand;//������
	int nClientID;//��Ӧ�Żط�
	
	int nConnectionType;
	
	char strFileName[MAX_PATH];//�ļ���
	
	int nSeekPos;//��λʱ��Ҫ��λ��λ�� ֡
	
}PLAY_INFO;//���Żص�ʹ�õĽṹ

typedef struct STLANTOOLINFO 
{
	unsigned char  uchType;      //��Ϣ���ͣ�1���Թ��ߵĹ㲥��2���Թ��ߵ����ã�3�豸��Ӧ��
	
	/*������Ϣ*/
	char chPName[256]; //�û������������IPC��ȫ�ԣ���ֹ��������
	char chPWord[256]; //���룬�������IPC��ȫ�ԣ���ֹ��������
	int nYSTNUM;       //����ͨ���룬���ڹ������豸��������
	char chCurTime[20];//ϵͳʱ�䣬���ڹ������豸�������� xxxx-xx-xx xx:xx:xx
	char *pchData;     //�������ݣ����ڹ������豸��������
	int nDLen;         //�������ݳ��ȣ����ڹ������豸��������
	
	/*Ӧ����Ϣ*/
	int nCardType;     //�豸���ͣ������豸Ӧ��ʱ�ĸ�����Ϣ
	int	nDate;         //�������� ���� 20091011
	int	nSerial;       //�������к�
	GUID guid;         //ΨһGUID
	char chGroup[4];   //�豸����ţ������豸Ӧ��ʱ�ĸ�����Ϣ
	
	char chIP[16];
	int nPort;
	
}STLANTOOLINFO;//����������������Ϣ����

typedef struct STTOOLPACK
{
	int nCardType;//��Ʒ����(4)
	int nPNLen;//�û�����(4)
	int nPWLen;//���볤(4)
	unsigned char  uchCType;//��������(1)
	char chGroup[4];
	int nYSTNUM;//����ͨ����(4)
	char chCurTime[20];//ϵͳʱ��(4)
	int nDLen;//���ó���(4)
}STTOOLPACK;

#define  NET_MOD_UNKNOW 0 // δ��
#define  NET_MOD_WIFI   1 //wifi ģʽ
#define  NET_MOD_WIRED  2 // ����ģʽ

#define  DEV_SET_ALL      0 // ����ȫ��
#define  DEV_SET_NET      1 //�����豸֧�ֵ�����ģʽ
#define  DEV_SET_CUR_NET  2 //�����豸��ǰ����ģʽ
#define  DEV_SET_NAME     3 // ���ñ���

typedef struct  
{
	char chDeviceName[100];//�豸����
	int nCurNetMod;// �豸��ǰ����ģʽ�����ߣ�wifi������
	int nNetMod; //�豸֧�ֵ�����ģʽ��Ϊ ����ģʽ��������ֵ  nNetMod = NET_MOD_WIFI;
}STDEVINFO; //�豸����
typedef struct STBASEYSTNO
{
	char chGroup[4];
	int nYSTNO;
	int nChannel;
	char chPName[MAX_PATH];
	char chPWord[MAX_PATH];
	int nConnectStatus;//����״̬ ����ʱ=0����ѯʱ��ʾ״̬ 0 δ���� 1 ���� 2 ת�� 3����	
}STBASEYSTNO;//����ͨ���������Ϣ�����ڳ�ʼ��С���ֵ�������

typedef struct 
{
	char chGroup[4];
	int nYSTNO;
	int nCardType;
	int nChannelCount;
	char chClientIP[16];
	int nClientPort;
	int nVariety;
	char chDeviceName[100];
#ifndef WIN32
	int bTimoOut;
#else
	BOOL bTimoOut;
#endif
	int nNetMod;//���� �Ƿ����wifi����: nNetMod & NET_MOD_WIFI
	int nCurMod;//���� ��ǰʹ�õ�(wifi������)��nCurMod(NET_MOD_WIFI �� NET_MOD_WIRED)

	int nPrivateSize;//�Զ�������ʵ�ʳ���
	char chPrivateInfo[500];//�Զ�����������
}STLANSRESULT;//�������豸�������

/*���ػص�����*/
#ifndef WIN32//LINUX
	typedef int (*FUNC_SCHECKPASS_CALLBACK)(int nLocalChannel, char chClientIP[16], int nClientPort, char *pName, char *pWord);
	typedef void (*FUNC_SCONNECT_CALLBACK)(int nLocalChannel, int nClientID, unsigned char uchType, char chClientIP[16], int nClientPort, char *pName, char *pWord);
	typedef void (*FUNC_SONLINE_CALLBACK)(int nLocalChannel, unsigned char uchType);
	typedef void (*FUNC_SCHECKFILE_CALLBACK)(int nLocalChannel, int nClientID, char chClientIP[16], int nClientPort, char chStartTime[14], char chEndTime[14], unsigned char *pBuffer, int *nSize);
	typedef void (*FUNC_SCHAT_CALLBACK)(int nLocalChannel, int nClientID, unsigned char uchType, char chClientIP[16], int nClientPort, unsigned char  *pBuffer, int nSize);
	typedef void (*FUNC_STEXT_CALLBACK)(int nLocalChannel, int nClientID, unsigned char uchType, char chClientIP[16], int nClientPort, unsigned char  *pBuffer, int nSize);
	typedef void (*FUNC_SYTCTRL_CALLBACK)(int nLocalChannel, int nClientID, int nType, char chClientIP[16], int nClientPort);
	typedef void (*FUNC_SBCDATA_CALLBACK)(int nBCID, unsigned char *pBuffer, int nSize, char chIP[16], int nPort);
	typedef int (*FUNC_SFPLAYCTRL_CALLBACK)(PLAY_INFO* pData);
	typedef void (*FUNC_DLFNAME_CALLBACK)(char chFilePathName[256]);
	typedef int (*FUNC_LANTOOL_CALLBACK)(STLANTOOLINFO* pData);//0������Ӧ1��Ӧ
#else//WINDOWS
	typedef bool (*FUNC_SCHECKPASS_CALLBACK)(int nLocalChannel, char chClientIP[16], int nClientPort, char *pName, char *pWord);
	typedef void (*FUNC_SCONNECT_CALLBACK)(int nLocalChannel, int nClientID, unsigned char uchType, char chClientIP[16], int nClientPort, char *pName, char *pWord);
	typedef void (*FUNC_SONLINE_CALLBACK)(int nLocalChannel, unsigned char uchType);
	typedef void (*FUNC_SCHECKFILE_CALLBACK)(int nLocalChannel, int nClientID, char chClientIP[16], int nClientPort, char chStartTime[14], char chEndTime[14], unsigned char *pBuffer, int &nSize);
	typedef void (*FUNC_SCHAT_CALLBACK)(int nLocalChannel, int nClientID, unsigned char uchType, char chClientIP[16], int nClientPort, unsigned char  *pBuffer, int nSize);
	typedef void (*FUNC_STEXT_CALLBACK)(int nLocalChannel, int nClientID, unsigned char uchType, char chClientIP[16], int nClientPort, unsigned char  *pBuffer, int nSize);
	typedef void (*FUNC_SYTCTRL_CALLBACK)(int nLocalChannel, int nClientID, int nType, char chClientIP[16], int nClientPort);
	typedef void (*FUNC_SBCDATA_CALLBACK)(int nBCID, unsigned char *pBuffer, int nSize, char chIP[16], int nPort);
	typedef bool (*FUNC_SFPLAYCTRL_CALLBACK)(PLAY_INFO* pData);
	typedef void (*FUNC_DLFNAME_CALLBACK)(char chFilePathName[256]);
	typedef int (*FUNC_LANTOOL_CALLBACK)(STLANTOOLINFO* pData);//0������Ӧ1��Ӧ
#endif

/*�ֿػص�����*/
#ifndef WIN32//LINUX
	typedef void (*FUNC_CCONNECT_CALLBACK)(int nLocalChannel, unsigned char uchType, char *pMsg, int nPWData);
	typedef void (*FUNC_CNORMALDATA_CALLBACK)(int nLocalChannel, unsigned char uchType, unsigned char *pBuffer, int nSize, int nWidth, int nHeight);
	typedef void (*FUNC_CCHECKRESULT_CALLBACK)(int nLocalChannel,unsigned char *pBuffer, int nSize);
	typedef void (*FUNC_CCHATDATA_CALLBACK)(int nLocalChannel, unsigned char uchType, unsigned char *pBuffer, int nSize);
	typedef void (*FUNC_CTEXTDATA_CALLBACK)(int nLocalChannel, unsigned char uchType, unsigned char *pBuffer, int nSize);
	typedef void (*FUNC_CDOWNLOAD_CALLBACK)(int nLocalChannel, unsigned char uchType, unsigned char *pBuffer, int nSize, int nFileLen);
	typedef void (*FUNC_CPLAYDATA_CALLBACK)(int nLocalChannel, unsigned char uchType, unsigned char *pBuffer, int nSize, int nWidth, int nHeight, int nTotalFrame);
	typedef void (*FUNC_CBUFRATE_CALLBACK)(int nLocalChannel, unsigned char uchType, unsigned char *pBuffer, int nSize, int nRate);
	typedef void (*FUNC_CLANSDATA_CALLBACK)(STLANSRESULT stLSResult);
	typedef void (*FUNC_CBCDATA_CALLBACK)(int nBCID, unsigned char *pBuffer, int nSize, char chIP[16], int bTimeOut);
	typedef int (*FUNC_CLANTDATA_CALLBACK)(STLANTOOLINFO *pLANTData);
#else//WINDOWS
	typedef void (*FUNC_CCONNECT_CALLBACK)(int nLocalChannel, unsigned char uchType, char *pMsg, int nPWData);
	typedef void (*FUNC_CNORMALDATA_CALLBACK)(int nLocalChannel, unsigned char uchType, unsigned char *pBuffer, int nSize, int nWidth, int nHeight);
	typedef void (*FUNC_CCHECKRESULT_CALLBACK)(int nLocalChannel,unsigned char *pBuffer, int nSize);
	typedef void (*FUNC_CCHATDATA_CALLBACK)(int nLocalChannel, unsigned char uchType, unsigned char *pBuffer, int nSize);
	typedef void (*FUNC_CTEXTDATA_CALLBACK)(int nLocalChannel, unsigned char uchType, unsigned char *pBuffer, int nSize);
	typedef void (*FUNC_CDOWNLOAD_CALLBACK)(int nLocalChannel, unsigned char uchType, unsigned char *pBuffer, int nSize, int nFileLen);
	typedef void (*FUNC_CPLAYDATA_CALLBACK)(int nLocalChannel, unsigned char uchType, unsigned char *pBuffer, int nSize, int nWidth, int nHeight, int nTotalFrame);
	typedef void (*FUNC_CBUFRATE_CALLBACK)(int nLocalChannel, unsigned char uchType, unsigned char *pBuffer, int nSize, int nRate);
	typedef void (*FUNC_CLANSDATA_CALLBACK)(STLANSRESULT stLSResult);
	typedef void (*FUNC_CBCDATA_CALLBACK)(int nBCID, unsigned char *pBuffer, int nSize, char chIP[16], BOOL bTimeOut);
	typedef int (*FUNC_CLANTDATA_CALLBACK)(STLANTOOLINFO *pLANTData);
#endif

/************���ػص�������������***************/
/*FUNC_SCONNECT_CALLBACK*/
#define JVN_SCONNECTTYPE_PCCONNOK  0X01//��PC�ֿ����ӳɹ�
#define JVN_SCONNECTTYPE_DISCONNOK 0X02//�зֿضϿ����ӳɹ�
#define JVN_SCONNECTTYPE_DISCONNE  0X03//�����쳣�Ͽ�
#define JVN_SCONNECTTYPE_MOCONNOK  0X04//���ƶ��豸�ֿ����ӳɹ�
/*FUNC_SONLINE_CALLBACK*/
#define JVN_SONLINETYPE_ONLINE     0x01//����
#define JVN_SONLINETYPE_OFFLINE    0x02//����
#define JVN_SONLINETYPE_CLEAR      0x03//YST������Ч��Ӧ�����������

/************�ֿػص�������������***************/
/*FUNC_CCONNECT_CALLBACK*/
#define JVN_CCONNECTTYPE_CONNOK    0X01//���ӳɹ�
#define JVN_CCONNECTTYPE_DISOK     0X02//�Ͽ����ӳɹ�
#define JVN_CCONNECTTYPE_RECONN    0X03//�����ظ�����
#define JVN_CCONNECTTYPE_CONNERR   0X04//����ʧ��
#define JVN_CCONNECTTYPE_NOCONN    0X05//û����
#define JVN_CCONNECTTYPE_DISCONNE  0X06//�����쳣�Ͽ�
#define JVN_CCONNECTTYPE_SSTOP     0X07//����ֹͣ�����ӶϿ�
#define JVN_CCONNECTTYPE_DISF      0x08//�Ͽ�����ʧ��


/*����ֵ*/
#define JVN_RETURNOK    0//�ɹ�
#define JVN_PARAERROR   1//��������
#define JVN_RETURNERROR 2//ʧ��
#define JVN_NOMEMERROR  3//�ڴ��Ӳ�̿ռ䲻��

//����IP�Σ������������豸ʱ���á�
typedef struct
{
	char startip[16];//��ʼIP
	char endip[16];//��ֹIP
}IPSECTION;

typedef struct 
{
	char chIP[16];
	int nPort;
	unsigned char uchStatus;// 0 1
	unsigned char uchType;
	unsigned char uchProcType;
	int nDownSpeed;// KB/s
	float fDownTotal;// M
	float fUpTotal;// M
}STPTINFO;

/*��ʼ��SDKʱ�����豸��ص�һЩ��Ϣ�������ڲ����ݲ�ͬ��Ʒ���ò�ͬ�Ĵ���*/
typedef struct 
{
	int nType;//��Ʒ���� 0��ͨĬ�ϲ�Ʒ��1�忨; 2DVR; 3IPC; 4JNVR; 5NVR; 6���ð�СIPC;
	int nMemLimit;//�ڴ����� 0��ͨĬ�ϲ�Ʒ��1�ڴ����(����������20M����)��2�ڴ��������(����Լ20M����)��3�ڴ����(����С��15M����)��
	              //�ڴ������ǰ���£��ڴ�����Խ�ã���������Ч����Խ�ã������ȷ��������Ϊ0��
}STDeviceType;

/*�������ʱ�����ߴ���ṹ*/
typedef struct 
{
	char chGroup[4];//����ţ�����"A" "AAAA"
	int nCardType;  //��ϵ
	int	nDate;      //�������� ���� 20091011
	int	nSerial;    //�������к�
	GUID guid;      //ΨһGUID MAPIGUID.H
}STGetNum;
/*��ʼ��ʱ�����ߴ���Ľṹ*/
typedef struct
{
	char chGroup[4];//����ţ�����"A" "AAAA"
	int  nChannelCount; //����ͨ������Ŀ
	int nCardType; //��ϵ
	int	nDate;     //��������
	int	nSerial;   //�������к�
	GUID gLoginKey;//�忨GUID
	int  nYstNum;  //����ͨ����
}STOnline;



/*���ݰ�:����YST����*/
typedef struct
{
	int nCardType;  //��ϵ
	int	nDate;      //�������� ���� 20091011
	int	nSerial;    //�������к�
	GUID guid;      //ΨһGUID MAPIGUID.H
}Pak_GetNum;

/*���ݰ�:����*/
typedef struct
{
	int nCardType; //��ϵ
	int	nDate;     //��������
	int	nSerial;   //�������к�
	GUID gLoginKey;//�忨GUID
	int  nYstNum;  //����ͨ����
}Pak_Online1; 

typedef struct
{
	int		nCardType;//�忨����
	int		nDate; //��������
	int		nSerial; //�������к�
	GUID	gLoginKey; //��½����
	int     nYstNum;   //����ͨ����
	char    chGroup[4];//����� �ݲ�ʹ��
	int     nNSDKVer;//��������SDK�汾(Э��汾)
	int     nChannelCount; //����ͨ������Ŀ
}Pak_Online1Ex; //YST_AS_ONLINE1  ���ݽṹ

/*���ݰ�:����Ӧ��*/
typedef struct
{
	int	nIndex;     //˳���
	GUID gLoginKey; //��½����
}Pak_LoginKey; 

/*���ݰ�: ��ַ����*/
typedef struct
{
	int nYstNum;       //����ͨ����
	int	nIndex;        //˳���
	GUID gLoginKey;    //��½����
#ifndef WIN32
	struct sockaddr InAddress;//������ַ
#else
	SOCKADDR InAddress;//������ַ
#endif
	int nVer;          //���صİ汾
}Pak_Online2;

/*���ݰ�: ��ַ����*/
typedef struct
{
	int nYstNum;       //����ͨ����
	int	nIndex;        //˳���
	GUID gLoginKey;    //��½����
#ifndef WIN32
	struct sockaddr InAddress;//������ַ
#else
	SOCKADDR InAddress;//������ַ
#endif
	int nVer;          //���صİ汾
	int nTCPSerPort;   //TCP����˿�
}Pak_Online2Ex;

/*���ݰ�: ����*/
typedef struct
{
	int	nYstNum;
	int	nIndex;
	GUID gLoginKey;//��½����
}Pak_Logout;

typedef struct
{
	unsigned int nTypeLens; //YST_AS_REGCARD	
	//��������
	int nSize;
	char *pacData;
}SOCKET_DATA_TRAN;

#endif