/*
 * grpc.h
 *
 *  Created on: 2014��10��9��
 *      Author: LiuFengxiang
 *		 Email: lfx@jovision.com
 */

#ifndef GRPC_H_
#define GRPC_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>

#include "cJSON.h"


#ifdef __cplusplus
extern "C" {
#endif


#define GRPC_ERR_PARSE_ERROR			-32700	//Parse error	Invalid JSON was received by the server.
												//An error occurred on the server while parsing the JSON text.
#define GRPC_ERR_INVALID_REQUEST		-32600	//Invalid Request	The JSON sent is not a valid Request object.
#define GRPC_ERR_METHOD_NOT_FOUND		-32601	//Method not found	The method does not exist / is not available.
#define GRPC_ERR_INVALID_PARAMS			-32602	//Invalid params	Invalid method parameter(s).
#define GRPC_ERR_INTERNAL_ERROR			-32603	//Internal error	Internal JSON-RPC error.
#define GRPC_ERR_NO_POWER				-32604	//Need Power to Access Function
#define GRPC_ERR_PASSWD_ERR				-32605	//No User or Error Passwd

#define GRPC_ERR_METHOD_NOT_IMPLEMENTED	-32001	//Method not implemented
#define GRPC_ERR_UNKNOWN				-32002	//Unknown error
#define GRPC_ERR_DEVICE_BUSY			-32003	//Device busy
#define GRPC_ERR_FUNC_NOT_SUPPORT		-32004	//Function not support
#define GRPC_ERR_NO_FREE_RESOURCE		-32005	//No free resource
#define GRPC_ERR_NO_FREE_MEMORY			-32006	//No free memory
#define GRPC_ERR_OPERATION_REFUSED		-32007	//Operation refused
#define GRPC_ERR_ALREADY_OPENED			-32008	//Resource already opened
#define GRPC_ERR_ALREADY_CLOSED			-32009	//Resource already closed
#define GRPC_ERR_TIMEOUT				-32010	//Timeout
#define GRPC_ERR_RESOURCE_EXIST			-32011	//Resource already exist


#define GRPC_ERR_SERVER_ERROR_START	-32000
#define GRPC_ERR_SERVER_ERROR_END	-32099	//Server error	Reserved for implementation-defined server-errors.


typedef enum{
	DEBUG_LEVEL_ERRORS,
	DEBUG_LEVEL_DEBUG,
	DEBUG_LEVEL_DEBUG_MORE,
	DEBUG_LEVEL_ALL,
}DebugLevel_e;

typedef enum
{
	GRPC_USER_LEVEL_Administrator,
	GRPC_USER_LEVEL_Operator,
	GRPC_USER_LEVEL_User,
	GRPC_USER_LEVEL_Anonymous,
	GRPC_USER_LEVEL_Extended,
	GRPC_USER_LEVEL_MAX
}GRPCUserLevel_e;

#ifndef GBOOL
#define GBOOL int
#define GTRUE 1
#define GFALSE 0
#endif

#define GRPC_DEBUG_LEVEL DEBUG_LEVEL_DEBUG_MORE

#define __FUNCTION_DBG__(level) \
	do{ \
		if (GRPC_DEBUG_LEVEL >= level) \
			printf("FUNCTION %s =>%4d: called\n", __FUNCTION__, __LINE__); \
	} while(0)

#define __GENERATE_FUNC_DEBUG__() __FUNCTION_DBG__(DEBUG_LEVEL_ALL)

#define __NULL_FUNC_DBG__() \
	do{ \
		if (GRPC_DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG) \
			printf("NOT_FINISHED %s:%s =>%4d: called\n", __FILE__, __FUNCTION__, __LINE__); \
	} while(0)

#define __NULL_FUNC_DBG__FINISHED__() \
	do{ \
		if (GRPC_DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG) \
			printf("FINISHED %s:%s =>%4d: called\n", __FILE__, __FUNCTION__, __LINE__); \
	} while(0)



struct _grpc_t;

/**
 *@brief ���緢�͡����յĽӿ�
 */
typedef struct{
	int (*send)(struct _grpc_t *grpc, void *buffer, int len);
	/**
	 *@param sumTimeoutms �ۼƳ�ʱʱ�䡣���ڿͻ��ˡ����ڣ����յ������ݣ������������ݲ���ʱ���ظ����������ѵ���ʱ�䡣Э��recv��������ʱ.
	 *	��Server��ʱ����ֵΪNull��
	 *	�䵥λΪ����
	 */
	int (*recv)(struct _grpc_t *grpc, void *buffer, int len, int *sumTimeoutms);
}grpcNetFunc_t;

/**
 *@brief Jsonת���ɵĺ����Ľӿ�
 */
typedef struct{
	const char *name;
//	int (*client_method_ptr)(struct _grpc_t *grpc);
//	int (*server_method_ptr)(struct _grpc_t *grpc);
	int (*method_ptr)(struct _grpc_t *grpc);
	GRPCUserLevel_e level; ///< ����Ȩ��
}grpcMethod_t;

/**
 *@brief ��ʼ��
 */
typedef struct{
	void *userdef;	// ����ͨѶ���������û������Զ��塣���ḳֵ��grpc.userfd
	grpcNetFunc_t fptr_net;  //����ͨѶ��Ҫ�Ľӿ�
	grpcMethod_t *methodList_s; //�����
	grpcMethod_t *methodList_c; //�ͻ���
}grpcInitParam_t;

typedef struct{
	char name[32];
	char passwd[32];
	GRPCUserLevel_e level;
}grpcUser_t;

#define PRIVATE
#define PUBLIC

typedef struct _grpc_t{
	PUBLIC void *userdef;// such as connect fd

	PRIVATE int sentcnt; //�ڲ����ͽ��յ�һ������������ȷ�ϻظ��İ汾�Ƿ�ƥ��
	PRIVATE cJSON *root;

	PUBLIC struct{
		int errcode;
		char message[256];
	}error;

//private
	PRIVATE char buffer[128*1024];
	PRIVATE grpcNetFunc_t fptr_net;
	PRIVATE grpcMethod_t *methodList_c;
	PRIVATE grpcMethod_t *methodList_s;
	PRIVATE void *memlist; //malloc list
	PRIVATE grpcUser_t userClient; //���ڵ�½��client.level��Ч
	PRIVATE grpcUser_t userServer[32];//server������֤
	PRIVATE int userCnt; //server��������֤���û���
}grpc_t;

/**
 *@brief ����grpc�����й����Ŀ�ʼ
 */
grpc_t *grpc_new(void);

/**
 *@brief ɾ��grpc�����й����Ľ���
 */
int grpc_delete(grpc_t *grpc);

/**
 *@brief ��Ҫ�ĳ�ʼ��
 *
 *@param initParam ��ʼ������
 */
int grpc_init(grpc_t *grpc, grpcInitParam_t *initParam);

/**
 *@brief ���Server����֤��Ϣ
 */
int grpc_s_account_clear(grpc_t *grpc);

/**
 *@brief ����Server����֤��Ϣ
 */
int grpc_s_account_add(grpc_t *grpc, const grpcUser_t *user);

/**
 *@brief ����Client�˵�½��Ϣ
 */
int grpc_c_account_set(grpc_t *grpc, const grpcUser_t *user);

/**
 *@brief ������ã��ȴ����ݵĵ������������õĺ����������շ�������
 */
int grpc_s_serve(grpc_t *grpc);

/**
 *@brief ������ã�����ȴ����ݣ�ֱ�Ӵ�����������
 */
int grpc_s_serve_direct(grpc_t *grpc, const char *data);

/**
 *@brief ������ã�����ȴ����ݣ�ֱ�Ӵ����������ݣ�ͬʱ�����ݲ����ͣ���ɾ����������grpc->root��
 */
int grpc_s_serve_without_send(grpc_t *grpc, const char *data);
/**
 *@brief �ͻ����ã����ⲿֱ�������ݽ���
 */
int grpc_c_resp_direct(grpc_t *grpc, const char *resp);

/**
 *@brief ���ڷ���ˣ�#grpc_serve֮��������Ϣ�����߶��ڿͻ��ˣ�����REQ֮�������ڴ档���ظ�����
 */
int grpc_end(grpc_t *grpc);

/**
 *@brief ���ڿͻ��ˣ���#grpc_t::root ����ַ������ͳ�ȥ
 */
int grpc_c_send(grpc_t *grpc);

/**
 *@brief ���ڿͻ��ˣ��������ݣ������յ�����Ϣ�����#grpc_t::root
 */
int grpc_c_recv(grpc_t *grpc);



/**
 *@brief ����C++��ptr = #grpc_malloc ʱ�����������ǿ��grpc_malloc�����ͣ���ǿ����ֵ����
 * ������÷��� VOID_PTR_DECLARE(ptr) = grpc_malloc(grpc, size);
 */
#define VOID_PTR_DECLARE(ptr) (*((void **)(&(ptr))))

/**
 *@brief �����ڴ棬��#grpc_end�����ͷ�
 *@note ��������ֵ��Ϊvoid*�����鷳ʱ������ʹ��#VOID_PTR_DECLARE��
 *		VOID_PTR_DECLARE(ptr) = grpc_malloc(grpc, size);
 */
void *grpc_malloc(grpc_t *grpc, int size);

/**
 *@brief �����ڴ棬�����ַ�������#grpc_end�����ͷ�
 */
char *grpc_strdup(grpc_t *grpc, const char *str);

/**
 *@brief ��д������Ϣ
 */
int grpc_s_set_error(grpc_t *grpc, int errcode, const char *message);


#ifdef __cplusplus
}
#endif

#endif /* GRPC_H_ */
