#ifndef JVCLIENT_H
#define JVCLIENT_H
#include "JVNSDKDef.h"
#ifndef WIN32

	#ifdef __cplusplus
		#define JVCLIENT_API extern "C"
	#else
		#define JVCLIENT_API
	#endif
#else
#define JVCLIENT_API extern "C" __declspec(dllexport)
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                     //
//                                      �ֿض˽ӿ�                                                     //
//                                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/***************************************�ӿ��嵥********************************************************
JVC_InitSDK -----------------01 ��ʼ��SDK��Դ
JVC_ReleaseSDK --------------02 �ͷ�SDK��Դ��������󱻵���
JVC_RegisterCallBack --------03 ���÷ֿض˻ص�����
JVC_Connect -----------------04 ����ĳͨ���������
JVC_DisConnect --------------05 �Ͽ�ĳͨ����������
JVC_SendData ----------------06 ��������
JVC_EnableLog ---------------07 ����д������־�Ƿ���Ч
JVC_SetLanguage -------------08 ������־/��ʾ��Ϣ����(Ӣ��/����) 
JVC_TCPConnect --------------09 ��ʽ����ĳͨ���������
JVC_GetPartnerInfo ----------10 ��ȡ���ڵ���Ϣ
JVC_RegisterRateCallBack ----11 ע�Ỻ����Ȼص�����
JVC_StartLANSerchServer -----12 �����������������������ά�豸
JVC_StopLANSerchServer ------13 ֹͣ��������
JVC_LANSerchDevice ----------14 ������������ά�豸
JVC_SetLocalFilePath --------15 �Զ��屾���ļ��洢·����������־�����ɵ������ؼ��ļ���
JVC_SetDomainName -----------16 �����µ�������ϵͳ�������ȡ�������б�
JVC_WANGetChannelCount ------17 ͨ��������ȡĳ������ͨ���������е�ͨ������
JVC_StartBroadcastServer ----18 �����Զ���㲥����
JVC_StopBroadcastServer -----19 ֹͣ�Զ���㲥����
JVC_BroadcastOnce -----------20 ���͹㲥��Ϣ
JVC_ClearBuffer -------------21 �����ػ���

JVC_EnableHelp---------------22 ����/ͣ�ÿ������ӷ���(����ͨС����ʹ��)
JVC_SetHelpYSTNO-------------23 ���ö�ĳЩ����ͨ����ĸ���֧��
JVC_GetHelpYSTNO-------------24 ��ȡ��ĳЩ����ͨ����ĸ���֧��
JVC_EnableLANTool------------25 ������������������þ������е��豸
JVC_LANToolDevice------------26 �����������еĿ������豸
JVC_SendCMD------------------27 �����ض˷���һЩ��������
JVC_AddFSIpSection-----------28 �������ȷ��͹㲥��IP��
JVC_MOLANSerchDevice --------29 �ֻ�������������ά�豸
*******************************************************************************************************/


/****************************************************************************
*����  : JVC_InitSDK
*����  : ��ʼ��SDK��Դ�����뱻��һ������
*����  : [IN] nLocalStartPort ��������ʹ�õ���ʼ�˿� <0ʱĬ��9200
*����ֵ: TRUE     �ɹ�
         FALSE    ʧ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API int JVC_InitSDK(int nLocStartPort);
#else
	JVCLIENT_API bool __stdcall	JVC_InitSDK(int nLocStartPort);
#endif

/****************************************************************************
*����  : JVC_ReleaseSDK
*����  : �ͷ�SDK��Դ��������󱻵��� 
*����  : ��
*����ֵ: ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API void JVC_ReleaseSDK();
#else
	JVCLIENT_API void __stdcall	JVC_ReleaseSDK();
#endif

/****************************************************************************
*����  : JVC_RegisterSCallBack
*����  : ���÷ֿض˻ص����� 
*����  : [IN] ConnectCallBack   ����������״���ص�����
*����ֵ: ��
*����  : �ֿض˻ص�����������
             �����ض�ͨ��״̬������      (����״̬)
			 ʵʱ��ش���                (�յ�ʵʱ�������)
		     ¼����������������      (�յ�¼��������)
			 ��������/�ı����캯��       (Զ���������ı�����)
			 Զ�����غ�����              (Զ����������)
			 Զ�̻طź�����              (Զ�̻ط�����)
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API void  JVC_RegisterCallBack(FUNC_CCONNECT_CALLBACK ConnectCallBack,
													FUNC_CNORMALDATA_CALLBACK NormalData,
													FUNC_CCHECKRESULT_CALLBACK CheckResult,
													FUNC_CCHATDATA_CALLBACK ChatData,
													FUNC_CTEXTDATA_CALLBACK TextData,
													FUNC_CDOWNLOAD_CALLBACK DownLoad,
													FUNC_CPLAYDATA_CALLBACK PlayData);
#else
	JVCLIENT_API void __stdcall	JVC_RegisterCallBack(FUNC_CCONNECT_CALLBACK ConnectCallBack,
													FUNC_CNORMALDATA_CALLBACK NormalData,
													FUNC_CCHECKRESULT_CALLBACK CheckResult,
													FUNC_CCHATDATA_CALLBACK ChatData,
													FUNC_CTEXTDATA_CALLBACK TextData,
													FUNC_CDOWNLOAD_CALLBACK DownLoad,
													FUNC_CPLAYDATA_CALLBACK PlayData);
#endif

/****************************************************************************
*����  : JVC_Connect
*����  : ����ĳͨ���������
*����  : [IN] nLocalChannel ����ͨ���� >=1
         [IN] nChannel      ����ͨ���� >=1
		 [IN] pchServerIP   ��nYSTNO<0ʱ���ò���ָͨ������IP����nYSTNO>=0ʱ��Ч.
		 [IN] nServerPort   ��nYSTNO<0ʱ���ò���ָͨ������port����nYSTNO>=0ʱ��Ч.
		 [IN] pchPassName   �û���
		 [IN] pchPassWord   ����
		 [IN] nYSTNO        ����ͨ���룬��ʹ��ʱ��-1
		 [IN] chGroup       ����ţ�����"A" "AAAA" ʹ������ͨ����ʱ��Ч
		 [IN] bLocalTry     �Ƿ��������̽��
		 [IN] nTURNType     ת����������(����ת��\����ת��\����ת��)
*����ֵ: ��
*����  : nLocalChannel <= -2 �� nChannel = -1 �����ӷ���˵�����ͨ����
         �ɱܿ���Ƶ���ݣ������շ���ͨ����
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API void JVC_Connect(int nLocalChannel,int nChannel,
											char *pchServerIP,int nServerPort,
											char *pchPassName,char *pchPassWord,
											int nYSTNO,char chGroup[4],
											int bLocalTry,
											int nTURNType,
											int bCache);
#else
	JVCLIENT_API void __stdcall	JVC_Connect(int nLocalChannel,int nChannel,
											char *pchServerIP,int nServerPort,
											char *pchPassName,char *pchPassWord,
											int nYSTNO,char chGroup[4],
											BOOL bLocalTry,
											int nTURNType,
											BOOL bCache);
#endif

/****************************************************************************
*����  : JVC_DisConnect
*����  : �Ͽ�ĳͨ���������� 
*����  : [IN] nLocalChannel ����ͨ���� >=1
*����ֵ: ��
*����  : 
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API void JVC_DisConnect(int nLocalChannel);
#else
	JVCLIENT_API void __stdcall	JVC_DisConnect(int nLocalChannel);
#endif

/****************************************************************************
*����  : JVC_SendData
*����  : �������� 
*����  : [IN] nLocalChannel   ����ͨ���� >=1
         [IN] uchType          �������ͣ��������󣻸��ֿ��ƣ�����Ӧ��
         [IN] pBuffer         ������������
		 [IN] nSize           �������ݳ���
*����ֵ: ��
*����  : ��ͨ�����ӵ����ط�������
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API void JVC_SendData(int nLocalChannel, unsigned char uchType, unsigned char *pBuffer,int nSize);
#else
	JVCLIENT_API void __stdcall	JVC_SendData(int nLocalChannel, unsigned char uchType, unsigned char  *pBuffer,int nSize);
#endif

/****************************************************************************
*����  : JVN_EnableLog
*����  : ����д������־�Ƿ���Ч 
*����  : [IN] bEnable  TRUE:����ʱд��־��FALSE:��д�κ���־
*����ֵ: ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API void JVC_EnableLog(int bEnable);
#else
	JVCLIENT_API void __stdcall	JVC_EnableLog(bool bEnable);
#endif

/****************************************************************************
*����  : JVC_SetLanguage
*����  : ������־/��ʾ��Ϣ����(Ӣ��/����) 
*����  : [IN] nLgType  JVN_LANGUAGE_ENGLISH/JVN_LANGUAGE_CHINESE
*����ֵ: ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API void JVC_SetLanguage(int nLgType);
#else
	JVCLIENT_API void __stdcall	JVC_SetLanguage(int nLgType);
#endif

/****************************************************************************
*����  : JVC_TCPConnect
*����  : TCP��ʽ����ĳͨ���������
*����  : [IN] nLocalChannel ����ͨ���� >=1
         [IN] nChannel      ����ͨ���� >=1
		 [IN] pchServerIP   ��nYSTNO<0ʱ���ò���ָͨ������IP����nYSTNO>=0ʱ��Ч.
		 [IN] nServerPort   ��nYSTNO<0ʱ���ò���ָͨ������port����nYSTNO>=0ʱ��Ч.
		 [IN] pchPassName   �û���
		 [IN] pchPassWord   ����
		 [IN] nYSTNO        ����ͨ���룬��ʹ��ʱ��-1
		 [IN] chGroup       ����ţ�����"A" "AAAA" ʹ������ͨ����ʱ��Ч
		 [IN] bLocalTry     �Ƿ��������̽��
		 [IN] nConnectType  ���ӷ�ʽ��TYPE_PC_TCP/TYPE_MO_TCP
		 [IN] nTURNType     ת����������(����ת��\����ת��\����ת��)
*����ֵ: ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API void JVC_TCPConnect(int nLocalChannel,int nChannel,
									char *pchServerIP,int nServerPort,
									char *pchPassName,char *pchPassWord,
									int nYSTNO,char chGroup[4],
									int bLocalTry,
									int nConnectType,
									int nTURNType);
#else
	JVCLIENT_API void __stdcall	JVC_TCPConnect(int nLocalChannel,int nChannel,
												char *pchServerIP,int nServerPort,
												char *pchPassName,char *pchPassWord,
												int nYSTNO,char chGroup[4],
												BOOL bLocalTry,
												int nConnectType,
												int nTURNType);
#endif


/****************************************************************************
*����  : JVC_GetPartnerInfo
*����  : ��ȡ���ڵ���Ϣ 
*����  : [IN] nLocalChannel   ����ͨ���� >=1
         [OUT] pMsg   ��Ϣ����
		              (�Ƿ�ಥ(1)+�����ܸ���(4)+����������(4)+[IP(16) + port(4)+����״̬(1)+�����ٶ�(4)+��������(4)+�ϴ�����(4)]
					                +[...]...)
		 [OUT] nSize  ��Ϣ�ܳ���
*����ֵ: ��
*����  : ����Ƶ���Ͻ�̫�ߣ������Ӱ����Ƶ�����ٶȣ�
         Ƶ���̶ȶȲ��ܵ���1�룬�����2�����ϻ����ʱ�䣬ʱ��Խ��Ӱ��ԽС��
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API void JVC_GetPartnerInfo(int nLocalChannel, char *pMsg, int *nSize);
#else
	JVCLIENT_API void __stdcall	JVC_GetPartnerInfo(int nLocalChannel, char *pMsg, int &nSize);
#endif

#ifndef WIN32
	JVCLIENT_API void JVC_RegisterRateCallBack(FUNC_CBUFRATE_CALLBACK BufRate);
#else
	JVCLIENT_API void __stdcall	JVC_RegisterRateCallBack(FUNC_CBUFRATE_CALLBACK BufRate);
#endif

/****************************************************************************
*����  : JVC_StartLANSerchServer
*����  : �����������������������ά�豸 
*����  : [IN] nLPort      ���ط���˿ڣ�<0ʱΪĬ��9400
         [IN] nServerPort �豸�˷���˿ڣ�<=0ʱΪĬ��9103,����ͳһ��Ĭ��ֵ������ƥ��
		 [IN] LANSData    ��������ص�����
*����ֵ: TRUE/FALSE
*����  : ��������������ſ��Խ��������������������ͨ��JVC_LANSerchDevice�ӿ�ָ��
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API int JVC_StartLANSerchServer(int nLPort, int nServerPort, FUNC_CLANSDATA_CALLBACK LANSData);
#else
	JVCLIENT_API bool __stdcall	JVC_StartLANSerchServer(int nLPort, int nServerPort, FUNC_CLANSDATA_CALLBACK LANSData);
#endif

/****************************************************************************
*����  : JVC_StopLANSerchServer
*����  : ֹͣ�������� 
*����  : ��
*����ֵ: ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API void JVC_StopLANSerchServer();
#else
	JVCLIENT_API void __stdcall	JVC_StopLANSerchServer();
#endif

/****************************************************************************
*����  : JVC_LANSerchDevice
*����  : ������������ά�豸 
*����  : [IN] chGroup     ����ţ������+nYSTNO��ȷ��Ψһ�豸
         [IN] nYSTNO      ��������ĳ����ͨ������豸��>0��Ч
         [IN] nCardType   ����ĳ�ͺŵ��豸��>0��Ч,��nYSTNO>0ʱ�ò�����Ч
		 [IN] chDeviceName����ĳ���������豸��strlen>0��Ч����nYSTNO>0ʱ��Ч
		 [IN] nVariety    ����ĳ�������豸��1�忨;2DVR;3IPC;>0��Ч,��nYSTNO>0ʱ�ò�����Ч
		 [IN] nTimeOut    ����������Чʱ�䣬��λ���롣������ʱ��Ľ������������
		                  ��ʱʱ�䵽���ص������н��õ���ʱ��ʾ��Ϊ����������־��
						  �������ʹ��SDK��ʱ���������Ϊ0����ʱ���ǿȫ�����ظ������ߡ�
						  
						  ͬ���ε��豸һ������<500��ʱ������������
						  �豸����������������2000��ȷ������������ȫ�棻
						  ���弴�������ɸ�����Ҫ����̣�Խ��Խ������©��ͬ���ε��豸��
		 [IN] unFrequence (��λΪs )ִ��ping ���ص�Ƶ�ʣ�Ĭ��������30s����һ�Σ�Ƕ��ʽ�豸�ɸ�����Ҫ����>20&&<24*3600��Ч.

*����ֵ: ��
*����  : ��������ͬʱΪ0ʱ����������������������ά�豸
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API int  JVC_LANSerchDevice(char chGroup[4], int nYSTNO, int nCardType, int nVariety, char chDeviceName[100], int nTimeOut,unsigned int unFrequence );
#else
	JVCLIENT_API bool __stdcall	JVC_LANSerchDevice(char chGroup[4], int nYSTNO, int nCardType, int nVariety, char chDeviceName[100], int nTimeOut,unsigned int unFrequence );
#endif

/****************************************************************************
*����  : JVC_SetLocalFilePath
*����  : �Զ��屾���ļ��洢·����������־�����ɵ������ؼ��ļ��� 
*����  : [IN] chLocalPath  ·�� ���磺"C:\\jovision"  ����jovision���ļ���
*����ֵ: ��
*����  : ����ʹ���ڴ濽��ʱ��ע���ʼ�����ַ�������'\0'����
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API int JVC_SetLocalFilePath(char chLocalPath[256]);
#else
	JVCLIENT_API bool __stdcall	JVC_SetLocalFilePath(char chLocalPath[256]);
#endif

/****************************************************************************
*����  : JVC_SetDomainName 
*����  : �����µ�������ϵͳ�������ȡ�������б�
*����  : [IN]  pchDomainName     ����
[IN]  pchPathName       �����µ��ļ�·���� ���磺"/down/YSTOEM/yst0.txt"
*����ֵ: TRUE  �ɹ�
FALSE ʧ��
*����  : ϵͳ��ʼ��(JVN_InitSDK)�������
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API int JVC_SetDomainName(char *pchDomainName,char *pchPathName);
#else
	JVCLIENT_API bool __stdcall	JVC_SetDomainName(char *pchDomainName,char *pchPathName);
#endif

/****************************************************************************
*����  : JVC_WANGetChannelCount
*����  : ͨ��������ȡĳ������ͨ���������е�ͨ������
*����  : [IN]  chGroup   �����
         [IN]  nYstNO    ����ͨ����
		 [IN]  nTimeOutS �ȴ���ʱʱ��(��)
*����ֵ: >0  �ɹ�,ͨ����
         -1 ʧ�ܣ�ԭ��δ֪
		 -2 ʧ�ܣ�����δ����
		 -3 ʧ�ܣ����ذ汾�Ͼɣ���֧�ָò�ѯ
*����  : ϵͳ��ʼ��(JVN_InitSDK)��� �ɶ�������
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API int JVC_WANGetChannelCount(char chGroup[4], int nYSTNO, int nTimeOutS);
#else
	JVCLIENT_API int __stdcall	JVC_WANGetChannelCount(char chGroup[4], int nYSTNO, int nTimeOutS);
#endif

/****************************************************************************
*����  : JVC_StartBroadcastServer
*����  : �����Զ���㲥���� 
*����  : [IN] nLPort      ���ط���˿ڣ�<0ʱΪĬ��9500
         [IN] nServerPort �豸�˷���˿ڣ�<=0ʱΪĬ��9106,����ͳһ��Ĭ��ֵ������ƥ��
		 [IN] BroadcastData  �㲥����ص�����
*����ֵ: TRUE/FALSE
*����  : �����˹㲥����ſ��Խ��չ㲥������㲥����ͨ��JVC_BroadcastOnce�ӿ�ָ����
         �˿�������һ��ע����豸������ض˿������𣬷������ݽ��쳣��
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API int JVC_StartBroadcastServer(int nLPort, int nServerPort, FUNC_CBCDATA_CALLBACK BCData);
#else
	JVCLIENT_API bool __stdcall	JVC_StartBroadcastServer(int nLPort, int nServerPort, FUNC_CBCDATA_CALLBACK BCData);
#endif

/****************************************************************************
*����  : JVC_StopBroadcastServer
*����  : ֹͣ�Զ���㲥���� 
*����  : ��
*����ֵ: ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API void JVC_StopBroadcastServer();
#else
	JVCLIENT_API void __stdcall	JVC_StopBroadcastServer();
#endif

/****************************************************************************
*����  : JVC_BroadcastOnce
*����  : ���͹㲥��Ϣ 
*����  : [IN] nBCID       �㲥ID,�ɵ����߶���,�����ڻص�������ƥ�����ֱ��ι㲥
         [IN] pBuffer     �㲥��������,���ݲ�������10k,�����������ಿ��
         [IN] nSize       �㲥�������ݳ���
		 [IN] nTimeOut    ���ι㲥��Чʱ�䣬��λ���롣������ʱ��Ľ������������
		                  ��ʱʱ�䵽���ص������н��õ���ʱ��ʾ��Ϊ����������־��
						  �������ʹ��SDK��ʱ���������Ϊ0����ʱ���ǿȫ�����ظ������ߡ�
*����ֵ: ��
*����  : Ŀǰ�ù����ݲ�֧�ֲ����㲥������������ʱ���һ�ι㲥������֮ǰ�Ĺ㲥
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API int JVC_BroadcastOnce(int nBCID, unsigned char *pBuffer, int nSize, int nTimeOut);
#else
	JVCLIENT_API BOOL __stdcall JVC_BroadcastOnce(int nBCID, unsigned char  *pBuffer, int nSize, int nTimeOut);
#endif

/****************************************************************************
*����  : JVC_ClearBuffer
*����  : ��ձ��ػ��� 
*����  : [IN] nLocalChannel ����ͨ���� >=1
*����ֵ: ��
*����  : ������ͨģʽ������Ч���ಥ���Ӳ�����ӱ������
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API void JVC_ClearBuffer(int nLocalChannel);
#else
	JVCLIENT_API void __stdcall	JVC_ClearBuffer(int nLocalChannel);
#endif 

/****************************************************************************
*����  : JVC_EnableHelp
*����  : ����/ͣ�ÿ������ӷ��� 
*����  : [IN] bEnable TRUE����/FALSE�ر�
         [IN] nType  ��ǰʹ������˭����bEnableΪTRUEʱ��Ч
		             1 ��ǰʹ����������ͨС����(��������)
		             2 ��ǰʹ����������ͨ�ͻ��ˣ�֧�ֶ������̵�С����
		             3 ��ǰʹ����������ͨ�ͻ��ˣ���֧�ֶ������̵�С����
*����ֵ: ��
*����  : ���øù��ܺ�����SDK����趨�ĺ�������������ٵ��Ż���
		 ���øù��ܺ�����SDK��֧��С���ֺͿͻ���֮����н�����
		 ����ֿض�֧��С���ֽ��̣�����С���ֶ�ʹ��nType=1���ͻ���ʹ��nType=2���ɣ�
		 ����ͻ��˲�֧��С���ֽ��̣���ͻ���ʹ��nType=3���ɣ������ֻ��ͻ��ˣ�
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API int JVC_EnableHelp(int bEnable, int nType);
#else
	JVCLIENT_API BOOL __stdcall JVC_EnableHelp(BOOL bEnable, int nType);
#endif

/****************************************************************************
*����  : JVC_SetHelpYSTNO
*����  : ���ö�ĳЩ����ͨ����ĸ���֧��
*����  : [IN] pBuffer ����ͨ���뼯�ϣ���STBASEYSTNO�ṹ��ɣ���������������
                      STBASEYSTNO st1,STBASEYSTNO st1;
					  pBuffer�����ݾ���:
					  memcpy(bBuffer, &st1, sizeof(STBASEYSTNO));
					  memcpy(&bBuffer[sizeof(STBASEYSTNO)], &st2, sizeof(STBASEYSTNO));
         [IN] nSize   pBuffer��ʵ����Ч���ȣ����������������Ϊ��
		              2*sizeof(STBASEYSTNO);
					  
*����ֵ: ��
*����  : ����ͨС���ֶ�ʹ�ã�
         �ͻ��˲�֧��С����ʱ�ͻ���ʹ�ã�

         ��Ӻ�����SDK�����Щ����ͨ��������������ٵ��Ż���
		 ���ǳ�ʼ���ã����������пͻ���Ҳ����Щ�µĺ��룬
		 �ᶯ̬��ӵ��ڲ���
		 STBASEYSTNOS ����ͨ����,STYSTNO����ο�JVNSDKDef.h
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API int JVC_SetHelpYSTNO(unsigned char *pBuffer, int nSize);
#else
	JVCLIENT_API BOOL __stdcall JVC_SetHelpYSTNO(unsigned char  *pBuffer, int nSize);
#endif

/****************************************************************************
*����  : JVC_GetHelpYSTNO
*����  : ��ȡ��ǰ��֪������ͨ�����嵥
*����  : [IN/OUT] pBuffer �ɵ����߿����ڴ棻
                          ��������ͨ���뼯�ϣ���STBASEYSTNO�ṹ��ɣ���������������
                          STBASEYSTNO st1,STBASEYSTNO st1;
                          pBuffer�����ݾ���:
                          memcpy(bBuffer, &st1, sizeof(STBASEYSTNO));
                          memcpy(&bBuffer[sizeof(STBASEYSTNO)], &st2, sizeof(STBASEYSTNO));
         [IN/OUT] nSize   ����ʱ�������pBuffer��ʵ�ʿ��ٳ��ȣ�
		                  ���ú󷵻ص���pBuffer��ʵ����Ч���ȣ����������������Ϊ��
                          2*sizeof(STBASEYSTNO);
*����ֵ: -1  ���󣬲�������pBufferΪ�ջ��Ǵ�С�����Դ洢�����
          0  ����δ����
          1  �ɹ�
*����  : ����ͨС���ֶ�ʹ�ã�
         �ͻ��˲�֧��С����ʱ�ͻ���ʹ�ã�

         ���ǳ�����������֪�����к��룬��С���ֻ����Щ������������Ż�֧�֣�
		 �ýӿڽ����ڲ�ѯ�������ڲ����Զ���ӣ���ѯ������᳤����Ч��
		 STBASEYSTNOS ����ͨ����,STYSTNO����ο�JVNSDKDef.h
*****************************************************************************/
#ifndef WIN32 
	JVCLIENT_API int JVC_GetHelpYSTNO(unsigned char *pBuffer, int *nSize);
#else
	JVCLIENT_API int __stdcall JVC_GetHelpYSTNO(unsigned char  *pBuffer, int &nSize);
#endif

/****************************************************************************
*����  : JVC_GetYSTStatus
*����  : ��ȡĳ������ͨ���������״̬
*����  : [IN] chGroup  ����ͨ����ı���ţ�
         [IN] nYSTNO   ����ͨ����
		 [IN] nTimeOut ��ʱʱ��(��)������>=2��
*����ֵ: -1  ���󣬲�������chGroupΪ�ջ���nYSTNO<=0��
          0  ���ز�ѯ̫Ƶ�����Ժ�����
          1  ��������
		  2  ���벻����
		  3  ��ѯʧ�ܣ��������ж������Ƿ�����
*����  : 1.ע�⣬�ú���Ŀǰ���������ֻ�,pc���ݲ�����ʹ�ã�
         2.�ú�����ͬһ�����벻����Ƶ�����ã����>=10s;
		 3.�ú����Բ�ͬ���벻����Ƶ�����ã����>=1s;
*****************************************************************************/
#ifndef WIN32 
	JVCLIENT_API int JVC_GetYSTStatus(char chGroup[4], int nYSTNO, int nTimeOut);
#else
	JVCLIENT_API int __stdcall JVC_GetYSTStatus(char chGroup[4], int nYSTNO, int nTimeOut);
#endif

/****************************************************************************
*����  : JVC_EnableLANTool
*����  : ������������������þ������е��豸 
*����  : [IN] nEnable     1���� 0�ر�
         [IN] nLPort      ���ط���˿ڣ�<0ʱΪĬ��9600
         [IN] nServerPort �豸�˷���˿ڣ�<=0ʱΪĬ��9104,����ͳһ��Ĭ��ֵ������ƥ��
		 [IN] LANTData    ��������ص�����
*����ֵ: 0ʧ��/1�ɹ�
*����  : ��������������ſ��Խ��������������������ͨ��JVC_LANToolDevice�ӿ�ָ��
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API int JVC_EnableLANTool(int nEnable, int nLPort, int nServerPort, FUNC_CLANTDATA_CALLBACK LANTData);
#else
	JVCLIENT_API int __stdcall	JVC_EnableLANTool(int nEnable, int nLPort, int nServerPort, FUNC_CLANTDATA_CALLBACK LANTData);
#endif

/****************************************************************************
*����  : JVC_LANToolDevice
*����  : �����������еĿ������豸 
*����  : [IN] chPName     �û���
		 [IN] chPWord     ���룬ʹ���û�����������IPC�İ�ȫ�ԣ�������Ҳ����ҪȨ�޵�
         [IN] nTimeOut    ����������Чʱ�䣬��λ���롣������ʱ��Ľ������������
		                  ��ʱʱ�䵽���ص������н��õ���ʱ��ʾ��Ϊ����������־��
						  �������ʹ��SDK��ʱ���������Ϊ0����ʱ���ǿȫ�����ظ������ߡ�
						  
						  ͬ���ε��豸һ������<500��ʱ������������
						  �豸����������������2000��ȷ������������ȫ�棻
						  ���弴�������ɸ�����Ҫ����̣�Խ��Խ������©��ͬ���ε��豸��
*����ֵ: ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API int JVC_LANToolDevice(char chPName[256], char chPWord[256], int nTimeOut);
#else
	JVCLIENT_API int __stdcall	JVC_LANToolDevice(char chPName[256], char chPWord[256], int nTimeOut);
#endif

/****************************************************************************
*����  : JVC_SendCMD
*����  : �����ض˷���һЩ�������� 
*����  : [IN] nLocalChannel   ����ͨ���� >=1
		 [IN] uchType         ��������
		 [IN] pBuffer         ������������
		 [IN] nSize           �������ݳ���
*����ֵ: 0  ����ʧ��
         1  ���ͳɹ�
		 2  �Է���֧�ָ�����
*����  : ������ͨģʽ������Ч��
         ��ǰ֧�ֵ���:ֻ���ؼ�֡����JVN_CMD_ONLYI
		              �ͻָ���֡����JVN_CMD_FULL
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API int JVC_SendCMD(int nLocalChannel, unsigned char uchType, unsigned char  *pBuffer, int nSize);
#else
	JVCLIENT_API int __stdcall	JVC_SendCMD(int nLocalChannel, unsigned char  uchType, unsigned char  *pBuffer, int nSize);
#endif

/****************************************************************************
*����  : JVC_AddFSIpSection 
*����  : �����Զ���IP�Σ��Թ��������� ,��������ָ����IP�� first search 
*����  : [IN] pStartIp		  IPSECTION�����ַ
		 [IN] nSize           IP����*sizeof(IPSECTION)
*����ֵ: 0���ɹ� -1 ʧ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
 	JVCLIENT_API int JVC_AddFSIpSection( const IPSECTION * pStartIp, int nSize );
#else
 	JVCLIENT_API int __stdcall	JVC_AddFSIpSection( const IPSECTION * pStartIp, int nSize );
 
#endif
 
/****************************************************************************
*����  : JVC_MOLANSerchDevice
*����  : �ֻ�������������ά�豸 
*����  : [IN] chGroup     ����ţ������+nYSTNO��ȷ��Ψһ�豸
         [IN] nYSTNO      ��������ĳ����ͨ������豸��>0��Ч
         [IN] nCardType   ����ĳ�ͺŵ��豸��>0��Ч,��nYSTNO>0ʱ�ò�����Ч
		 [IN] chDeviceName����ĳ���������豸��strlen>0��Ч����nYSTNO>0ʱ��Ч
		 [IN] nVariety    ����ĳ�������豸��1�忨;2DVR;3IPC;>0��Ч,��nYSTNO>0ʱ�ò�����Ч
		 [IN] nTimeOut    ����������Чʱ�䣬��λ���롣������ʱ��Ľ������������
		                  ��ʱʱ�䵽���ص������н��õ���ʱ��ʾ��Ϊ����������־��
						  �������ʹ��SDK��ʱ���������Ϊ0����ʱ���ǿȫ�����ظ������ߡ�
						  
						  ͬ���ε��豸һ������<500��ʱ������������
						  �豸����������������2000��ȷ������������ȫ�棻
						  ���弴�������ɸ�����Ҫ����̣�Խ��Խ������©��ͬ���ε��豸��
		 [IN] unFrequence (��λΪs )ִ��ping ���ص�Ƶ�ʣ�Ĭ��������30s����һ�Σ�Ƕ��ʽ�豸�ɸ�����Ҫ����>20&&<24*3600��Ч.

*����ֵ: ��
*����  : ��������ͬʱΪ0ʱ����������������������ά�豸
*****************************************************************************/
#ifndef WIN32
	JVCLIENT_API int  JVC_MOLANSerchDevice(char chGroup[4], int nYSTNO, int nCardType, int nVariety, char chDeviceName[100], int nTimeOut,unsigned int unFrequence);
#else
	JVCLIENT_API bool __stdcall	JVC_MOLANSerchDevice(char chGroup[4], int nYSTNO, int nCardType, int nVariety, char chDeviceName[100], int nTimeOut,unsigned int unFrequence);
#endif


#endif
