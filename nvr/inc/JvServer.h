#ifndef JVSERVER_H
#define JVSERVER_H
#include "JVNSDKDef.h"
#ifndef WIN32
	//#include "JVNSDKDef.h"
	#ifdef __cplusplus
		#define JVSERVER_API extern "C"
	#else
		#define JVSERVER_API
	#endif
#else
	#define JVSERVER_API extern "C" __declspec(dllexport)
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                     //
//                                      ���ض˽ӿ�                                                     //
//                                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/***************************************�ӿ��嵥********************************************************
JVN_InitSDK -----------------01 ��ʼ��SDK��Դ
JVN_ReleaseSDK---------------02 �ͷ�SDK��Դ
JVN_RegisterCallBack --------03 �������ض˻ص�����
JVN_ActiveYSTNO -------------04 ��������ͨ����
JVN_InitYST -----------------05 ��ʼ������ͨ����
JVN_StartChannel ------------06 ����ĳͨ���������
JVN_StopChannel -------------07 ֹͣĳͨ�����з���
JVN_SendData ----------------08 ��������(ͨ��Ⱥ��)
JVN_SendDataTo --------------09 ��������(������)
JVN_SendChatData ------------10 ����������Ϣ(����������ı�����)
JVN_EnableLog ---------------11 ����д������־�Ƿ���Ч
JVN_RegCard -----------------12 ע���Ʒ
JVN_SetLanguage -------------13 ������־/��ʾ��Ϣ����(Ӣ��/����)
JVN_GetLanguage -------------14 ��ȡ��־/��ʾ��Ϣ����(Ӣ��/����)
JVN_SendAndRecvS ------------15 ��������������
JVN_StartWebServer ----------16 ����web����
JVN_StartSelfWebServer ------17 �����Զ���web����(OEM)
JVN_StopWebServer -----------18 ֹͣweb����
JVN_SetClientLimit ----------19 ���÷ֿ���Ŀ����
JVN_GetClientLimit ----------20 ��ȡ�ֿ���Ŀ��������ֵ
JVN_EnablePCTCPServer -------21 �����ر�PC�ͻ�TCP����(������δʹ��)
JVN_EnableMOServer ----------22 �����ر�ĳͨ�����ֻ�����
JVN_SendMOData --------------23 �����ֻ����ݣ���TYPE_MO_TCP/TYPE_MO_UDP������Ч
JVN_Command -----------------24 �����ض�ָ�Ҫ��SDKִ���ض�����
JVN_StartLANSerchServer -----25 ������������������
JVN_StopLANSerchServer ------26 ֹͣ��������������
JVN_SetLocalNetCard ---------27 ������һ������(IPC)
JVN_SetDeviceName -----------28 ���ñ����豸����
JVN_SetDomainName -----------29 �����µ�������ϵͳ�������ȡ�������б�
JVN_SetLocalFilePath --------30 �Զ��屾���ļ��洢·����������־�����ɵ������ؼ��ļ���
JVN_StartStreamService ------31 ������ý�����
JVN_StopStreamService -------32 ֹͣ��ý�����
JVN_GetStreamServiceStatus --33 ��ѯ��ý�����״̬
JVN_StartBroadcastServer ----34 �����Զ���㲥����(IPC)
JVN_StopBroadcastServer -----35 �ر��Զ���㲥����(IPC)
JVN_BroadcastRSP ------------36 �����Զ���㲥Ӧ��(IPC)
JVN_SendPlay-----------------37 ��ָ��Ŀ�귢��Զ�̻ط�����,������MP4�ļ�Զ�̻ط�
JVN_EnableLANToolServer------38 �����رվ������������߷���
JVN_RegDownLoadFileName------39 ע��ص����������ڵ��������⴦��Զ�������ļ���
JVN_SetIPCWANMode------------40 ����IPC�������⴦��ģʽ
JVN_SetDeviceInfo------------41 �����豸��Ϣ
JVN_GetDeviceInfo------------42 ��ȡ�豸��Ϣ
JVN_SetLSPrivateInfo---------43 ���ñ����Զ�����Ϣ�������豸����
*******************************************************************************************************/                                                                                                     //


/****************************************************************************
*����  : JVN_InitSDK
*����  : ��ʼ��SDK��Դ�����뱻��һ������
*����  : [IN] nYSTPort    ����������ͨ����ͨ�ŵĶ˿�,0ʱĬ��9100
         [IN] nLocPort    �����ṩ���ط���ͨ�ŵĶ˿�,0ʱĬ��9101
		 [IN] nSPort      ����������ͨ����������(������룬ע���)�Ķ˿�,0ʱĬ��9102
		 [IN] nVersion    ���ذ汾�ţ���������ͨ��������֤
		 [IN] lRSBuffer   ���ض������շ���֡���ݵ���С���棬Ϊ0ʱĬ��150K��
		                  IPC�������ݵ�֡���ܴܺ󣬿ɸ������֡ȷ����ֵ�����������Ӧ�ֿض�Ҳ��Ҫ��Ӧ����.
						  �ò�����������IPC��
		 [IN] bLANSpeedup �Ƿ�����������Ż�����(IPC�������������������⴦��,������ͨ������Ʒ������ΪFALSE)
		 [IN] stDeviceType ��Ʒ���� ���JVNSDKDef.h �� STDeviceType
		                   ��ͨ�忨������stDeviceType.nType = 1;stDeviceType.nMemLimit = 1;
						   ��ͨIPC������ stDeviceType.nType = 3;stDeviceType.nMemLimit = 1;
						   �ڴ����ز���DVR������stDeviceType.nType = 2;stDeviceType.nMemLimit = 3;
		 [IN] nDSize       ������sizeof(STDeviceType),����У�鴫��ṹ�Ϸ���
*����ֵ: TRUE     �ɹ�
         FALSE    ʧ��
*����  : ���ض˳���ռ�������˿ڣ�һ������������ͨ������ͨ�ţ�һ��������ֿ�ͨ��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_InitSDK(int nYSTPort, int nLocPort, int nSPort, int nVersion, long lRSBuffer, int bLANSpeedup, STDeviceType stDeviceType, int nDSize);
#else
	JVSERVER_API bool __stdcall	JVN_InitSDK(int nYSTPort, int nLocPort, int nSPort, int nVersion, long lRSBuffer, BOOL bLANSpeedup, STDeviceType stDeviceType, int nDSize);
#endif

/****************************************************************************
*����  : JVN_ReleaseSDK
*����  : �ͷ�SDK��Դ��������󱻵��� 
*����  : ��
*����ֵ: ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_ReleaseSDK();
#else
	JVSERVER_API void __stdcall	JVN_ReleaseSDK();
#endif

/****************************************************************************
*����  : JVN_RegisterSCallBack
*����  : �������ض˻ص����� 
*����  : [IN] ConnectCallBack   �ֿ�����״���ص�����
         ...
*����ֵ: ��
*����  : ���ض˻ص�����������
             �ֿ������֤����            (�����֤)
             ������ͨ������ͨ��״̬������(����״̬)
		     ��ֿض�ͨ��״̬������      (����״̬)
		     ¼�����������              (¼���������)
			 Զ����̨���ƺ�����          (Զ����̨����)
			 ��������/�ı����캯��       (Զ���������ı�����)
			 �طſ���       (Ŀǰ�Ļطſ���mp4�ļ�)
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_RegisterCallBack(FUNC_SCHECKPASS_CALLBACK CheckPassCallBack,
											FUNC_SONLINE_CALLBACK OnlineCallBack,
											FUNC_SCONNECT_CALLBACK ConnectCallBack,
											FUNC_SCHECKFILE_CALLBACK CheckFileCallBack,
											FUNC_SYTCTRL_CALLBACK YTCtrlCallBack,
											FUNC_SCHAT_CALLBACK ChatCallBack,
											FUNC_STEXT_CALLBACK TextCallBack,
											FUNC_SFPLAYCTRL_CALLBACK FPlayCtrlCallBack);
#else
	JVSERVER_API void __stdcall	JVN_RegisterCallBack(FUNC_SCHECKPASS_CALLBACK CheckPassCallBack,
												  FUNC_SONLINE_CALLBACK OnlineCallBack,
												  FUNC_SCONNECT_CALLBACK ConnectCallBack,
												  FUNC_SCHECKFILE_CALLBACK CheckFileCallBack,
												  FUNC_SYTCTRL_CALLBACK YTCtrlCallBack,
												  FUNC_SCHAT_CALLBACK ChatCallBack,
												  FUNC_STEXT_CALLBACK TextCallBack,
												  FUNC_SFPLAYCTRL_CALLBACK FPlayCtrlCallBack);
#endif

/****************************************************************************
*����  : JVN_ActiveYSTNO
*����  : ��������ͨ����
*����  : [IN]  pchPackGetNum  ����Ϣ(STGetNum�ṹ)
         [IN]  nLen           ��Ϣ����(sizeof(STGetNum))
         [OUT] nYSTNO         �ɹ����������ͨ����
*����ֵ: TRUE  �ɹ�
         FALSE ʧ��
*����  : ����ͨ��������ַ���ڲ���ȡ��
         ��������ʹ�ã�ֻ���ؼ����YST���룬�����ڲ����κμ�¼��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_ActiveYSTNO(char *pchPackGetNum, int nLen, int *nYSTNO);
#else
	JVSERVER_API bool __stdcall	JVN_ActiveYSTNO(char *pchPackGetNum, int nLen, int &nYSTNO);
#endif

/****************************************************************************
*����  : JVN_InitYST
*����  : ��ʼ������ͨ����
*����  : [IN] ����ͨ�������Ϣ(STOnline�ṹ)
         [IN] ��Ϣ����
*����ֵ: ��
*����  : �ú�����������ͨ������ͨ����ǰ���ã�����ͨ������ͨ��������ʧ�ܣ�
         
		 �ú���ֻ�����һ�Σ�����������ͨ����ֻҪ����Ҫ��������ͨ����ģ�
		 ����������ǰ����һ�θýӿڼ��ɣ�
         
		 �ú�����¼����ͨ���뼰����������ʱʹ����Щ������
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_InitYST(char *pchPackOnline, int nLen);
#else
	JVSERVER_API void __stdcall	JVN_InitYST(char *pchPackOnline, int nLen);
#endif

/****************************************************************************
*����  : JVN_StartChannel
*����  : ����ĳͨ���������
*����  : [IN] nChannel  ����ͨ���� >=1  
                        �ر�:nChannel=-1ʱ����ͨ���������ڱܿ���Ƶͨ����������ͨ����

         [IN] nType     �����������ͣ�0����������������1ֻ��������������

		 [IN] bJVP2P    ������ά����ֱ�����ڴ治�������û��Ӳ��ʱ�ù��ܲ������ã�
		                ��ΪTRUEʱΪ�ಥ��ʽ��ΪFALSEʱΪ��ͳ��ʽ��
						������û�չ��ʱ��Ӧ������ѡ�����ģʽ(����ʱ)�ʹ�������ģʽ(С����ʱ)��
						Ĭ��Ϊ����ģʽ���ɣ�
						û��������Ҫ,�ɽ��ù�����ΪFALSE,����չ�ָ��û���

		 [IN] lBufLen   ͨ����Ƶ֡��������С����λ�ֽ�, 
		                ��ͨ��ʽʱ�����Сָ����֡����������(��>400*1024,Ӧ�������������)��
						JVP2P��ʽʱ������Ϊ>=8M����СΪ1024000��
						�����ֵ���ò��㣬���ܲ���ÿ��֡����ĩβ��֡��ʧ��ɿ��ٵ�����

		 [IN] chBufPath �����ļ�·������ʹ���ļ�����ʱ��Ϊ""; 

*����ֵ: TRUE  �ɹ�
         FALSE ʧ��
*����  : ÿ��ͨ������Ƶ֡�ߴ粻ͬ��������軺����Ҳ��ͬ����Ӧ�ò����ã�
         �ú������ظ����ã������б仯ʱ�Ž���ʵ�ʲ������ظ��ĵ��ûᱻ���ԣ�
		 Ӧ�ò��ڸ�����ĳЩ���ú󣬿����µ��øýӿ����÷���

         ��������jvp2p���������ַ�ʽ���л��棺�ڴ淽ʽ���ļ���ʽ
		 ��lbuflen �� chBufPath������һ������Ч�ģ����ͬʱ��Ч�����Ȳ����ڴ淽ʽ�����߶���Ч��ʧ��

		 ���飺1.�ڴ淽ʽʱÿ��ͨ������>=8M�ڴ棬Ч����ѣ��ڴ���������������ڴ淽ʽ��
		       2.DVR���ڴ�ǳ����ŵ��豸���԰�װӲ�̲��Ҳ����ļ��洢��ʽʹ��jvp2p��
			     DVR�ڴ�ϳ�����豸��������ÿ��ͨ������>=1M����Ƶ�����������򲻽���ʹ�ã�
				 DVR�ڴ�����豸�޷�ʹ��jvp2p������չ�ָ��û�����Ĭ���ṩ'����ģʽ'���ɣ�
			   3.ÿ��ͨ�������Ե�������jvp2p���ܣ�������Ӧ�ò����ļ���Լ���ͨ�����������ľ�����
			     ��������ͨ��ͳһ������رոù��ܣ�����ʹ��jvp2p��������ͨ����ʹ�ã����򶼲��ã�

         bJVP2P=TRUEʱ������"���������ͱ�֤����"��ģʽ���У��������ض�ֻҪ�ṩ�˱�Ҫ�Ļ����ϴ���������2M��
		 �������㼸ʮ�ϰ���ͬʱ���ӣ�����Ͽ�ͨ��άVIPת��������ȷ��������������ʵʱ���Բ
		 Զ�̻�����ʵ�ʻ��������ʱ2s-7s��
		 bJVP2P=FALSEʱ������"����������ʱ"��ģʽ���У�����������ȫȡ���ڴ�����豸��Դ����һ�ִ�ͳ���䷽ʽ��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_StartChannel(int nChannel, int nType, int bJVP2P, long lBufLen, char chBufPath[256]);
#else
	JVSERVER_API bool __stdcall	JVN_StartChannel(int nChannel, int nType, BOOL bJVP2P, long lBufLen, char chBufPath[MAX_PATH]);
#endif

/****************************************************************************
*����  : JVN_StopChannel
*����  : ֹͣĳͨ�����з��� 
*����  : [IN] nChannel ����ͨ���� >=1
*����ֵ: ��
*����  : ֹͣĳ������Ҳ��ͨ���ظ�����JVN_StartChannelʵ�֣�
         ����ֹͣ���з���ֻ��ͨ���ýӿ�ʵ�֡�
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_StopChannel(int nChannel);
#else
	JVSERVER_API void __stdcall	JVN_StopChannel(int nChannel);
#endif

/****************************************************************************
*����  : JVN_SendData
*����  : �������� 
*����  : [IN] nChannel   ����ͨ���� >=1
         [IN] uchType    �������ͣ���ƵI;��ƵP;��ƵB;��ƵS;��Ƶ;�ߴ�;�Զ�������;֡����ʱ����
         [IN] pBuffer    ������������,��Ƶ/��Ƶ/�Զ�������ʱ��Ч
		 [IN] nSize      �������ݳ���,��Ƶ/��Ƶ/�Զ�������ʱ��Ч
		 [IN] nWidth     uchType=JVN_DATA_Sʱ��ʾ֡��/uchType=JVN_CMD_FRAMETIMEʱ��ʾ֡���(��λms)
		 [IN] nHeight    uchType=JVN_DATA_Sʱ��ʾ֡��/uchType=JVN_CMD_FRAMETIMEʱ��ʾ�ؼ�֡����
*����ֵ: ��
*����  : ��ͨ��Ϊ��λ����ͨ�����ӵ����зֿط�������
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_SendData(int nChannel,unsigned char uchType,unsigned char *pBuffer,int nSize,int nWidth,int nHeight);
#else
	JVSERVER_API void __stdcall	JVN_SendData(int nChannel,unsigned char uchType,BYTE *pBuffer,int nSize,int nWidth,int nHeight);
#endif

/****************************************************************************
*����  : JVN_SendDataTo
*����  : �������� 
*����  : [IN] nChannel   ����ͨ���� >=1
         [IN] uchType    �������ͣ�Ŀǰֻ���ڳߴ緢�ͳߴ�;�Ͽ�ĳ����;�Զ�������
         [IN] pBuffer    ������������
		 [IN] nSize      �������ݳ���
		 [IN] nWidth     uchType=JVN_DATA_Sʱ��ʾ֡��/uchType=JVN_CMD_FRAMETIMEʱ��ʾ֡���(��λms)
		 [IN] nHeight    uchType=JVN_DATA_Sʱ��ʾ֡��/uchType=JVN_CMD_FRAMETIMEʱ��ʾ�ؼ�֡����
*����ֵ: ��
*����  : ��ͨ�����ӵ�ĳ������ֿط�������
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_SendDataTo(int nClientID,unsigned char uchType,unsigned char *pBuffer,int nSize,int nWidth,int nHeight);
#else
	JVSERVER_API void __stdcall	JVN_SendDataTo(int nClientID,unsigned char uchType,BYTE *pBuffer,int nSize,int nWidth,int nHeight);
#endif

/****************************************************************************
*����  : JVN_SendChatData
*����  : ����������Ϣ(����������ı�����)
*����  : [IN] nChannel   ����ͨ���� >=1,�㲥ʽ����ʱ��Ч;
         [IN] nClientID  �ֿ�ID,��ָ���ֿط���,��ʱnChannel��Ч,���ȼ�����nChannel;
         [IN] uchType      �������ͣ���������;
		                             �ı�����;
		                             ͬ����������;
                                     ͬ���ı�����;
								     ��������;
								     �ı�����;
								     �����ر�;
								     �ı��ر�;
         [IN] pBuffer    ������������
         [IN] nSize      �������ݳ���
*����ֵ: true   �ɹ�
         false  ʧ��
*����  : �����߽��������ݷ��͸�������������ķֿض�;
         nChannel��nClientID����ͬʱ<=0,������ͬʱ��Ч;
		 nChannel��nClientIDͬʱ>0ʱ,nClientID���ȼ���,��ʱֻ��ָ���ֿط��͡�
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_SendChatData(int nChannel,int nClientID,unsigned char uchType,unsigned char *pBuffer,int nSize);
#else
	JVSERVER_API bool __stdcall	JVN_SendChatData(int nChannel,int nClientID,unsigned char uchType,BYTE *pBuffer,int nSize);
#endif

/****************************************************************************
*����  : JVN_EnableLog
*����  : ����д������־�Ƿ���Ч 
*����  : [IN] bEnable  TRUE:����ʱд��־��FALSE:��д�κ���־
*����ֵ: ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_EnableLog(int bEnable);
#else
	JVSERVER_API void __stdcall	JVN_EnableLog(bool bEnable);
#endif

/****************************************************************************
*����  : JVN_SetLanguage
*����  : ������־/��ʾ��Ϣ����(Ӣ��/����) 
*����  : [IN] nLgType  JVN_LANGUAGE_ENGLISH/JVN_LANGUAGE_CHINESE
*����ֵ: ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_SetLanguage(int nLgType);
#else
	JVSERVER_API void __stdcall	JVN_SetLanguage(int nLgType);
#endif

/****************************************************************************
*����  : JVN_GetLanguage
*����  : ��ȡ��־/��ʾ��Ϣ����(Ӣ��/����) 
*����  : ��
*����ֵ: JVN_LANGUAGE_ENGLISH/JVN_LANGUAGE_CHINESE
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_GetLanguage();
#else
	JVSERVER_API int __stdcall	JVN_GetLanguage();
#endif

/****************************************************************************
*����  : JVN_SetClientLimit
*����  : ���÷ֿ���Ŀ����
*����  : [IN] nChannel  ͨ����(>0;=0;<0)
         [IN] nMax      ��Ŀ����ֵ <0ʱ��ʾ������
		                nChannel<0 ʱ��ʾ�ֿ�����Ŀ����ΪnMax; 
						nChannel=0 ʱ��ʾ����ͨ��ʹ����ͬ��ͨ���ֿ���Ŀ����ΪnMax; 
						nChannel>0 ʱ��ʾ��ͨ���ֿ���Ŀ����ΪnMax
*����ֵ: ��
*����  : ���ظ�����,�����һ������Ϊ׼;
         �������޺͵�ͨ�����޿�ͬʱ������;
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_SetClientLimit(int nChannel, int nMax);
#else
	JVSERVER_API void __stdcall	JVN_SetClientLimit(int nChannel, int nMax);
#endif

/****************************************************************************
*����  : JVN_GetClientLimit
*����  : ��ȡ�ֿ���Ŀ��������ֵ
*����  : [IN] nChannel  ͨ����(>0;<0)
		                nChannel<0 ʱ��ʾ��ȡ�ֿ�����Ŀ����; 
						nChannel>0 ʱ��ʾ��ȡ��ͨ���ֿ���Ŀ����;
*����ֵ: ��Ŀ����ֵ <=0��ʾ������
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_GetClientLimit(int nChannel);
#else
	JVSERVER_API int __stdcall	JVN_GetClientLimit(int nChannel);
#endif

/****************************************************************************
*����  : JVN_RegCard
*����  : ע���Ʒ
*����  : [IN] chGroup    ����ţ�����"A" "AAAA"
         [IN] pBuffer    ������������(SOCKET_DATA_TRAN�ṹ)
		 [IN] nSize      ���������ܳ���
*����ֵ: TRUE  �ɹ�
         FALSE ʧ��
*����  : ��������������
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_RegCard(char chGroup[4], unsigned char *pBuffer,int nSize);
#else
	JVSERVER_API bool __stdcall	JVN_RegCard(char chGroup[4], BYTE *pBuffer,int nSize);
#endif

/****************************************************************************
*����  : JVN_SendAndRecvS
*����  : ��������������
*����  : [IN] chGroup       ����ţ�����"A" "AAAA"
         [IN] pBuffer       ������������
         [IN] nSize         ���������ܳ���
         [OUT] pRecvBuffer  �������ݻ��壬�ɵ����߷���
         [IN/OUT] &nRecvLen ������ջ��峤�ȣ�����ʵ�����ݳ���
         [IN] nTimeOut      ��ʱʱ��(��)
*����ֵ: TRUE  �ɹ�
FALSE ʧ��
*����  : ��������������
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_SendAndRecvS(char chGroup[4],unsigned char *pBuffer,int nSize, 
		                               unsigned char *pRecvBuffer,int *nRecvLen,int nTimeOut);
#else
	JVSERVER_API bool __stdcall	JVN_SendAndRecvS(char chGroup[4], BYTE *pBuffer,int nSize, 
		                                         BYTE *pRecvBuffer,int &nRecvLen,int nTimeOut);
#endif

/****************************************************************************
*����  : JVN_StartWebServer
*����  : ����web����
*����  : [IN] chHomeDir   Ŀ���ļ����ڱ���·�� ��"D:\\test"
         [IN] chDefIndex  Ŀ���ļ���(����)
		 [IN] chLocalIP   ����ip
         [IN] nPort       web����˿�
*����ֵ: TRUE  �ɹ�
		 FALSE ʧ��
*����  : web�����ܼ�����Ŀ���ļ����ͻ���
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_StartWebServer(char chHomeDir[256], char chDefIndex[256], char chLocalIP[30], int nPort);
#else
	JVSERVER_API bool __stdcall JVN_StartWebServer(char chHomeDir[256], char chDefIndex[256], char chLocalIP[30], int nPort);
#endif

/****************************************************************************
*����  : JVN_StartSelfWebServer
*����  : �����Զ���web����(OEM)
*����  : [IN] chHomeDir   Ŀ���ļ����ڱ���·�� ��"D:\\test"
         [IN] chDefIndex  Ŀ���ļ���(����)
		 [IN] chLocalIP   ����ip
         [IN] nPort       web����˿�
		 [IN] chSelfWebPos   �Զ�����վ�ؼ�index�ļ�λ�� ��"www.afdvr.com/cloudsee"
		 [IN] bOnlyUseLocal  ��ʹ�ñ���web���񣬲�ʹ��������վ
*����ֵ: TRUE  �ɹ�
		 FALSE ʧ��
*����  : web�����ܼ�����Ŀ���ļ����ͻ���
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_StartSelfWebServer(char chHomeDir[256], char chDefIndex[256], 
		                                     char chLocalIP[30], int nPort,
											 char chSelfWebPos[500], int bOnlyUseLocal);
#else
	JVSERVER_API bool __stdcall JVN_StartSelfWebServer(char chHomeDir[256], char chDefIndex[256], 
		                                               char chLocalIP[30], int nPort,
													   char chSelfWebPos[500], BOOL bOnlyUseLocal);
#endif

/****************************************************************************
*����  : JVN_StopWebServer
*����  : ֹͣweb����
*����  : ��
*����ֵ: ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_StopWebServer();
#else
	JVSERVER_API void __stdcall JVN_StopWebServer();
#endif

/****************************************************************************
*����  : JVN_Command
*����  : �����ض�ָ�Ҫ��SDKִ���ض�����
*����  : [IN] nChannel  ����ͨ�� ==0ʱ����������Ƶͨ����Ч(����������ͨ��)
         [IN] nCMD  ָ������
*����ֵ: ��
*����  : ֧�ֵ�ָ��ο����Ͷ���
         Ŀǰ��֧�֣�CMD_TYPE_CLEARBUFFER
		 ���ض˽�����ĳ�����������ϣ���ͻ������������µ���ǰ���µ����ݣ���ִ�и�ָ�
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_Command(int nChannel, int nCMD);
#else
	JVSERVER_API void __stdcall JVN_Command(int nChannel, int nCMD);
#endif
	
/****************************************************************************
*����  : JVN_StartLANSerchServer
*����  : ������������������
*����  : [IN] nChannelCount ��ǰ�豸�ܵ�ͨ����
         [IN] nPort         ����˿ں�(<=0ʱΪĬ��9103,����ʹ��Ĭ��ֵ��ֿض�ͳһ)
*����ֵ: ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_StartLANSerchServer(int nPort);
#else
	JVSERVER_API bool __stdcall JVN_StartLANSerchServer(int nPort);
#endif

/****************************************************************************
*����  : JVN_StopLANSerchServer
*����  : ֹͣ��������������
*����  : ��
*����ֵ: ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_StopLANSerchServer();
#else
	JVSERVER_API void __stdcall JVN_StopLANSerchServer();
#endif
	
/****************************************************************************
*����  : JVN_SetLocalNetCard
*����  : ������һ������ eth0,eth1,... for linux or 0, 1, 2,...for win  
*����  : [IN] strCardName   ����
*����ֵ: �ɹ� TRUE ,ʧ�� FALSE
*����  : 2012 5
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_SetLocalNetCard(char* strCardName);
#else
	JVSERVER_API BOOL __stdcall JVN_SetLocalNetCard(char* strCardName);
#endif

/****************************************************************************
*����  : JVN_EnablePCTCPServer
*����  : ������ر�PC�û���TCP����
*����  : [IN] bEnable ����/�ر�
*����ֵ: TRUE  �ɹ�
		 FALSE ʧ��
*����  : TCP�����ܽ��շֿ���TCP��ʽ���ӣ���TCP��ʽ��ֿط������ݣ�
         Ŀǰ��ά�ֿض�δʹ�ø�TCP����,û��������Ҫ�ɲ�ʹ�øù��ܣ�
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_EnablePCTCPServer(int bEnable);
#else
	JVSERVER_API bool __stdcall JVN_EnablePCTCPServer(BOOL bEnable);
#endif

/****************************************************************************
*����  : JVN_EnableMOServer
*����  : ����/�ر�ĳͨ�����ֻ����� 
*����  : [IN] nChannel   ����ͨ���� >=1 ��=0ʱ������ر�����ͨ�����ֻ�����
         [IN] bEnable    TRUEΪ������FALSEΪ�ر�
		 [IN] nOpenType  ���������ͣ�����Ϊ0;bEnableΪTRUEʱ��Ч��
		 [IN] bSendVSelf  �Ƿ񵥶������ֻ���Ƶ���ݣ����ΪTRUE�����ֻ����ݺ�PC������ȫ���룬
		                 �ֻ����ݱ�����JVN_SendMOData���ͣ������ֻ���Ƶ���ݽ�����Ҫ�������ͣ�
						 ������ֻ����ֿ��ã����ֻ��͸��ֿص�����ͬ��������bSendVSelf=FALSE���ɣ�
		 [IN] bProtocol  �Ƿ����Զ���Э��,��bSendVSelfʱ��Ч��
		                 TRUEʱ��JVN_SendMOData�����ݴ����Ҫ�������ͷβ��ʹ�ֻ���������������ݣ�
						         �ɰ����ط��͵�JPG���ݺͱ�׼H264���ݾ������ַ��ͷ�ʽ��
						 FALSEʱ��JVN_SendMOData�����ݴ����ʽ�ͷֿ�����һ�£���ֿ����ݵ�����������������ݣ�
						         ������ֻ����ֿ��ã������ֻ��������ǵ���������������ʹ�ø÷�ʽ��
								 
*����ֵ: ��
*����  : �ú���ֻ��JVN_StartChannel�����˵�ͨ�������ã�JVN_StopChannel֮����Ҫ���������ֻ�����
         û������ͨ�������ܽ����ֻ����ӣ�
         �ظ����ý������һ�ε���Ϊ׼��
		 ���ھɰ�ֿ�Э�鲻ͬ������ȫ��Ϊ�ֿ�ʹ�ã��ù��ܲ��ܽ������ֺͽ��ã�
		 ʹ�øð�����ʱ��˾��Ʒ�ѿ�����ȫ֧��h264���������ݺͷֿ���ͬ������֧��JGP���ݣ�
		 �����ֻ����������ɣ�
		 <*****ʹ�ý���*****>��
		 1.������ֿص����ݺ͸��ֻ���������ȫ��ͬ��������ʽΪJVN_EnableMOServer(0, TRUE, 0, FALSE, FALSE);
		 2.������ֿص����ݺ͸��ֻ������ݸ�ʽ��ͬ������һ��������������������ʽΪJVN_EnableMOServer(0, TRUE, 0, TRUE, FALSE);
		 3.������ֿص����ݺ͸��ֻ������ݸ�ʽ��ͬ����Ҫ���ֻ��˵�������������ʽΪJVN_EnableMOServer(0, TRUE, 0, TRUE, TRUE);
		 �����ϸ��ֻ���������ֿ����ݷֿ�������С֡��С�������õ�2�ַ�ʽЧ����ѣ�
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_EnableMOServer(int nChannel, int bEnable, int nOpenType, int bSendVSelf, int bProtocol);
#else
	JVSERVER_API BOOL __stdcall	JVN_EnableMOServer(int nChannel, BOOL bEnable, int nOpenType, BOOL bSendVSelf, BOOL bProtocol);
#endif

/****************************************************************************
*����  : JVN_SendMOData
*����  : �����ֻ����ݣ���TYPE_MO_TCP/TYPE_MO_UDP������Ч 
*����  : [IN] nChannel   ����ͨ���� >=1
         [IN] uchType    �������ͣ���Ƶ:�Զ�������;
         [IN] pBuffer    ������������,��Ƶ/�Զ�������ʱ��Ч
		 [IN] nSize      �������ݳ���,��Ƶ/�Զ�������ʱ��Ч
*����ֵ: ��
*����  : ��ͨ��Ϊ��λ����ͨ��TYPE_MO_TCP/TYPE_MO_UDP���ӵ������ֻ�����һЩ�Զ������ݣ�
         ����JGP���ݵ���̭���ֻ����ݺ�PC�ֿ���������ȫ��ͬ���ýӿڲ�֧��JPG���ݣ�
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_SendMOData(int nChannel,unsigned char uchType,unsigned char *pBuffer,int nSize);
#else
	JVSERVER_API void __stdcall	JVN_SendMOData(int nChannel,unsigned char uchType,BYTE *pBuffer,int nSize);
#endif

/****************************************************************************
*����  : JVN_StartStreamService
*����  : ������ý�����
*����  : [IN] nChannel   ����ͨ���� >=1
         [IN] pSServerIP    ��ý�������IP;
         [IN] nPort   ��ý��������˿�
	     [IN] bAutoConnect ��������ʧ���Ƿ��Զ�����
*����ֵ: �ɹ�
         ʧ��
*����  : ��ͨ������ͨ��ʽ����ʱ����ý���������Ч��
         ��ͨ������ά����ֱ����ʽ����ʱ����ý���������Ч��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_StartStreamService(int nChannel,char *pSServerIP,int nPort,int bAutoConnect);
#else
	JVSERVER_API BOOL __stdcall JVN_StartStreamService(int nChannel,char *pSServerIP,int nPort,BOOL bAutoConnect);
#endif

/****************************************************************************
*����  : JVN_StopStreamService
*����  : ֹͣ��ý�����
*����  : [IN] nChannel   ����ͨ���� >=1
*����ֵ: ��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_StopStreamService(int nChannel);
#else
	JVSERVER_API void __stdcall JVN_StopStreamService(int nChannel);
#endif

/****************************************************************************
*����  : JVN_GetStreamServiceStatus
*����  : ��ѯ��ý�����״̬
*����  : [IN] nChannel   ����ͨ���� >=1
         [OUT] pSServerIP    ��ý�������IP;
         [OUT] nPort   ��ý��������˿�
		 [OUT] bAutoConnect ��ý������Ƿ������Զ�����
*����ֵ: ��ý������Ƿ�ɹ�����
*����  : 2012 2
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_GetStreamServiceStatus(int nChannel,char *pSServerIP,int *nPort,int *bAutoConnect);
#else
	JVSERVER_API BOOL __stdcall JVN_GetStreamServiceStatus(int nChannel,char *pSServerIP,int *nPort,BOOL *bAutoConnect);
#endif

/****************************************************************************
*����  : JVN_SetDomainName 
*����  : �����µ�������ϵͳ�������ȡ�������б�
*����  : [IN]  pchDomainName     ����
         [IN]  pchPathName       �����µ��ļ�·���� ���磺"/down/YSTOEM/yst0.txt"
*����ֵ: TRUE  �ɹ�
         FALSE ʧ��
*����  : ϵͳ��ʼ��(JVN_InitSDK)�������
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_SetDomainName(char *pchDomainName,char *pchPathName);
#else
	JVSERVER_API BOOL __stdcall	JVN_SetDomainName(char *pchDomainName,char *pchPathName);
#endif

/****************************************************************************
*����  : JVN_SetDeviceName
*����  : ���ñ����豸���� 
*����  : [IN] chDeviceName   �豸����
*����ֵ: ��
*����  : Ϊ�豸��һ���������������豸�����п�����������ʾʹ�ã�
         �ظ����������һ�ε���Ϊ��Ч��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_SetDeviceName(char chDeviceName[100]);
#else
	JVSERVER_API void __stdcall	JVN_SetDeviceName(char chDeviceName[100]);
#endif

/****************************************************************************
*����  : JVN_SetLocalFilePath
*����  : �Զ��屾���ļ��洢·����������־�����ɵ������ؼ��ļ��� 
*����  : [IN] chLocalPath  ·�� ���磺"C:\\jovision"  ����jovision���ļ���
*����ֵ: ��
*����  : ����ʹ���ڴ濽��ʱ��ע���ʼ�����ַ�������'\0'����
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_SetLocalFilePath(char chLocalPath[256]);
#else
	JVSERVER_API BOOL __stdcall	JVN_SetLocalFilePath(char chLocalPath[256]);
#endif

/****************************************************************************
*����  : JVN_StartBroadcastServer
*����  : �����������㲥����
*����  : [IN] nPort    ����˿ں�(<=0ʱΪĬ��9106,����ʹ��Ĭ��ֵ��ֿض�ͳһ)
         [IN] BCData   �㲥���ݻص�����
*����ֵ: �ɹ�/ʧ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_StartBroadcastServer(int nPort, FUNC_SBCDATA_CALLBACK BCData);
#else
	JVSERVER_API BOOL __stdcall JVN_StartBroadcastServer(int nPort, FUNC_SBCDATA_CALLBACK BCData);
#endif

/****************************************************************************
*����  : JVN_StopBroadcastServer
*����  : ֹͣ�������㲥����
*����  : ��
*����ֵ: ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_StopBroadcastServer();
#else
	JVSERVER_API void __stdcall JVN_StopBroadcastServer();
#endif

/****************************************************************************
*����  : JVN_BroadcastRSP
*����  : �������㲥��Ӧ
*����  : [IN] nBCID  �㲥��ʶ��ȡ�Իص�����
         [IN] pBuffer �㲥��������
		 [IN] nSize   �㲥�������ݳ���
		 [IN] nDesPort �㲥Ŀ��˿ڣ�ȡ�Իص�������������ֿ�Լ���̶�
*����ֵ: �ɹ�/ʧ��
*����  : ��
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_BroadcastRSP(int nBCID, unsigned char *pBuffer, int nSize, int nDesPort);
#else
	JVSERVER_API BOOL __stdcall JVN_BroadcastRSP(int nBCID, BYTE *pBuffer, int nSize, int nDesPort);
#endif

/****************************************************************************
*����  : JVN_SendPlay
*����  : ���ͻط�MP4���� 
*����  : [IN] nClientID   ���Ӻ�
         [IN] uchType     ����
		 [IN] nConnectionType     ��������
		 [IN] ucFrameType    ֡����	JVN_DATA_I JVN_DATA_S...
         [IN] pBuffer    ������������,����
		 [IN] nSize      �������ݳ���,����
         [IN] nWidth    ���
		 [IN] nHeight      �߶�
		 [IN] nTotalFram      ��֡��
*����ֵ: ��
*����  : ��ͨ�����ӵ�ĳ������ֿط�������
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_SendPlay(int nClientID,unsigned char uchType,int nConnectionType,unsigned char ucFrameType,unsigned char *pBuffer,int nSize,int nWidth,int nHeight,int nTotalFram);
#else
	JVSERVER_API void __stdcall	JVN_SendPlay(int nClientID,BYTE uchType,int nConnectionType,BYTE ucFrameType,BYTE *pBuffer,int nSize,int nWidth,int nHeight,int nTotalFram);
#endif

/****************************************************************************
*����  : JVN_EnableLANToolServer
*����  : ������رվ������������߷���
*����  : [IN] bEnable         ����/�ر�
         [IN] nPort           ����ʹ�õĶ˿ڣ�=0ʱĬ��Ϊ9104
         [IN] LanToolCallBack ���߻ص�����
*����ֵ: TRUE  �ɹ�
		 FALSE ʧ��
*����  : �������������߻��򱾵�ѯ�ʺ�����Ϣ�����ҷ���������صĸ�����Ϣ
         ��Ϣ��ϸ˵����ο��ص�����˵����
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_EnableLANToolServer(int bEnable, int nPort, FUNC_LANTOOL_CALLBACK LanToolCallBack);
#else
	JVSERVER_API bool __stdcall JVN_EnableLANToolServer(BOOL bEnable, int nPort, FUNC_LANTOOL_CALLBACK LanToolCallBack);
#endif

/****************************************************************************
*����  : JVN_RegDownLoadFileName
*����  : ע��ص����������ڵ��������⴦��Զ�������ļ���
*����  : [IN] DLFNameCallBack Զ�������ļ�������ص�����
*����ֵ: ��
*����  : ��ͨ��Ʒ����ʹ�ã�������Ҫ��ĿɶԿͻ��˵������ļ��������δ���
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_RegDownLoadFileName(FUNC_DLFNAME_CALLBACK DLFNameCallBack);
#else
	JVSERVER_API bool __stdcall JVN_RegDownLoadFileName(FUNC_DLFNAME_CALLBACK DLFNameCallBack);
#endif

/****************************************************************************
*����  : JVN_SetIPCWANMode
*����  : ����IPC�������⴦��ģʽ
*����  : ��
*����ֵ: ��
*����  : ��ͨ��Ʒ����ʹ�ã�������Ҫ��Ĵ�������Ʒ����ʹ�ã�
         ���ú��������佫�����ر��������ٶ��������ӵĸ��ţ�
		 ��JVN_InitSDK��JVN_StartChannelǰ���ü��ɣ�
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_SetIPCWANMode();
#else
	JVSERVER_API void __stdcall JVN_SetIPCWANMode();
#endif

/****************************************************************************
*����  : JVN_SetDeviceInfo
*����  : �����豸��Ϣ
*����  : [IN] pstInfo �豸��Ϣ�ṹ��
      	 [IN] nSize   �豸��Ϣ�ṹ���С,����ǰ�����
	     [IN] nflag   ����ѡ���־ 
*����ֵ: �ɹ�����0��ʧ�ܷ���-1
*����  : �������豸֧�ֵ�����ģʽΪ����+wifi����ǰ����ʹ�õ���wifi���������: 
		 nflag = DEV_SET_NET;//�����豸֧�ֵ�����ģʽ
		 pstInfo->nNetMod= NET_MOD_WIFI | NET_MOD_WIRED;
         pstInfo->nNetMod= NET_MOD_WIFI;//�豸��ǰʹ�õ���wifi
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_SetDeviceInfo(STDEVINFO *pstInfo, int nSize,int nflag);
#else
	JVSERVER_API int JVN_SetDeviceInfo(STDEVINFO *pstInfo, int nSize,int nflag);
#endif
	
/****************************************************************************
*����  : JVNS_GetDeviceInfo
*����  : ��ȡ�豸��Ϣ
*����  : [OUT] pstInfo �豸��Ϣ�ṹ��
	     [IN]  nSize   �豸��Ϣ�ṹ���С,����ǰ�����
*����ֵ: �ɹ�����0��ʧ�ܷ���-1
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_GetDeviceInfo(STDEVINFO *pstInfo,int nSize);
#else
	JVSERVER_API int JVN_GetDeviceInfo(STDEVINFO *pstInfo,int nSize);
#endif

/****************************************************************************
*����  : JVN_GetNetSpeedNow
*����  : ��ȡ��ǰ����״��
*����  : [IN]	nChannel	ͨ����
		 [IN]	nClientID	���Ӻ�		 
		 [IN]	nInterval	������, �ò���С��16ʱ��Ч��Ĭ����СΪ16��
*����ֵ: �ɹ�����ֵ>0��ʧ�ܷ���-1
*����  : ���ص�ǰ����״��ֵ��λBps��ʧ��ʱԭ����Ҫ����Ƶ����û�п��������߲�������
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API int JVN_GetNetSpeedNow(int nChannel, int nClientID, int nInterval);
#else
	JVSERVER_API int __stdcall JVN_GetNetSpeedNow(int nChannel, int nClientID, int nInterval = 16);
#endif

/****************************************************************************
*����  : JVN_SetLSPrivateInfo
*����  : ���ñ����Զ�����Ϣ�������豸����
*����  : [IN]	chPrivateInfo  �Զ�����Ϣ
		 [IN]	nSize          �Զ�����Ϣ����		 
*����ֵ: ��
*����  : ���ظ����ã������һ�ε���Ϊ׼��֮ǰ�����ݻᱻ���ǣ�
*****************************************************************************/
#ifndef WIN32
	JVSERVER_API void JVN_SetLSPrivateInfo(char chPrivateInfo[500], int nSize);
#else
	JVSERVER_API void __stdcall JVN_SetLSPrivateInfo(char chPrivateInfo[500], int nSize);
#endif

#endif
