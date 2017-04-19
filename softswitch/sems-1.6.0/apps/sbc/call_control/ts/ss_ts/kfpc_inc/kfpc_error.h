/********************************************************************
 * @data:		2012/09/26
 * @details:	26:9:2012   17:50
 * @file: 		D:\MyProgram\ͨ�ſ�\kfpc_com\kfpc_error.h 
 * @author:		KFPC
 * @brief:		
*********************************************************************/
#ifndef kfpc_error_h__
#define kfpc_error_h__

/**
 *	Types of error codes
 */ 
#define KFPC_RESULT_TYPE_SUCCESS					0x00
#define KFPC_RESULT_TYPE_WARNING					0x01
#define KFPC_RESULT_TYPE_ERROR						0x02
#define KFPC_RESULT_TYPE_OS_ERROR					0x03

/**
 *	 Generic result identifier
 */
#define	KFPC_RESULT_OK							0x0000			/**< �ɹ� */
#define KFPC_RESULT_FAIL						0x0001			/**< ͨ��ʧ�� */
#define KFPC_RESULT_FATAL_ERROR					0x0002			
#define KFPC_RESULT_TIMEOUT						0x0003			/**< ��ʱ */
#define KFPC_RESULT_MISMATCH					0x0004			/**< ��ƥ�� */
#define KFPC_RESULT_ACCESS_DENIED				0x0005			/**< �ܾ����� */
#define KFPC_RESULT_OUT_OF_RANGE				0x0006			/**< ������Χ */
#define KFPC_RESULT_OUT_OF_MEMORY				0x0007			/**< �ڴ���� */
#define KFPC_RESULT_OUT_OF_RESOURCE				0x0008			/**< ��Դ��� */
#define KFPC_RESULT_NULL_PARAM					0x0009			/**< ����Ϊ�� */
#define KFPC_RESULT_INVALID_PARAM				0x000A			/**< ��Ч���� */
#define KFPC_RESULT_INVALID_CONTEXT				0x000B			/**< ��Ч������ */
#define KFPC_RESULT_INVALID_HANDLE				0x000C			/**< ��Ч��� */
#define KFPC_RESULT_INVALID_ID					0x000D			/**< ��ЧID */
#define KFPC_RESULT_INVALID_CONFIG				0x000E			/**< ��Ч���� */
#define KFPC_RESULT_INVALID_STATE				0x000F			/**< ��Ч״̬ */
#define KFPC_RESULT_INVALID_MESSAGE				0x0010			/**< ��Ч��Ϣ */
#define KFPC_RESULT_INVALID_OPERATION			0x0011			/**< ��Ч���� */
#define KFPC_RESULT_NOT_ENOUGH_MEMORY			0x0012			/**< �ڴ治�� */
#define KFPC_RESULT_NOT_SUPPORTED				0x0013			/**< ��֧�� */
#define KFPC_RESULT_NOT_INITIALIZED				0x0014			/**< û�г�ʼ�� */
#define KFPC_RESULT_NOT_FOUND					0x0015			/**< û���ҵ� */
#define KFPC_RESULT_NOT_READY					0x0016			/**< û��׼���� */
#define KFPC_RESULT_NOT_ACCESSIBLE				0x0017			/**< ���ɷ��� */
#define KFPC_RESULT_NOT_RESPONDING				0x0018			/**< û�з��� */
#define KFPC_RESULT_NOT_IMPLEMENTED				0x0019			/**< û��ִ�� */
#define KFPC_RESULT_BUFFER_TOO_SMALL			0x001A			/**< ����̫С */
#define KFPC_RESULT_UNSUPPORTED_VERSION			0x0020			/**< ��֧�ֵİ汾 */
#define KFPC_RESULT_NOT_SUPPORTED_BY_LICENSE	0x0021			/**< ��ɲ�֧�� */
#define KFPC_RESULT_OPERATION_INCOMPLETE		0x0022			/**< ����δ��� */
#define KFPC_RESULT_QUEUE_EMPTY					0x0023			/**< ����Ϊ�� */
#define KFPC_RESULT_THREADPOOL_ALREADY_OPEN		0x0024			/**< �̳߳��Ѿ��� */
#define KFPC_RESULT_THREADPOOL_NOT_OPEN			0x0025			/**< �̳߳�δ�� */
#define KFPC_RESULT_REQUEST_PASSWD_AUTH			0x0026			/**< ��Ҫ���� */
#define KFPC_RESULT_PASSWD_AUTH_FAIL			0x0027			/**< ������֤ʧ�� */
#define KFPC_RESULT_FileNotFound				0x0028			/**< �ļ�û���ҵ� */
#define KFPC_RESULT_INVALID_LINCENSE			0x0029			/**< ��Ч��� */
#define KFPC_RESULT_OVERLOAD_LINCENSE			0x0030			/**< ������������ */
#define KFPC_RESULT_OVERTIME_LINCENSE			0x0031			/**< ��ɳ�ʱ */
#define KFPC_RESULT_BILL_INVALID_TIME			0x0032			/**< �ƷѴ�����Чʱ�� */
#define KFPC_RESULT_BILL_INVALID_PREFIX			0x0033			/**< �ƷѴ�����Ч���� */
#define KFPC_RESULT_BILL_RATE_NOTSET			0x0034			/**< �ƷѴ���û�����÷��� */
#define KFPC_RESULT_SEND_SMS_ERROR				0x0035			/**< ���Ͷ���ʧ�� */
#define KFPC_RESULT_OPEN_FILE_ERROR				0x0036			/**< ���ļ�ʧ�� */
#define KFPC_RESULT_PARSE_XML_ERROR				0x0037			/**< ����XMLʧ�� */

#define KFPC_RESULT_RESULT_ID_MAX_COUNT			0x200			/**<	Maximum number of result identifiers */


/*--------------------------------------------------------------------------------------------------------------------------------
 |  Macros
 *------------------------------------------------------------------------------------------------------------------------------*/

/* Create result code common to all module class */
#define KFPC_RESULT_CREATE_COMMON(__Type__, __Class__, __Id__)		\
  (unsigned int)((((unsigned int)(__Type__) & 0x000000FF) << 28) |		\
  (((unsigned int)(__Class__) & 0x000000FF) << 16)|					\
  (((unsigned int)(__Id__) & 0x0000FFFF) << 0))

/* Create result code */
#define KFPC_RESULT_CREATE(__Type__, __Class__, __Id__)		\
  KFPC_RESULT_CREATE_COMMON(__Type__, __Class__, (__Id__ + KFPC_RESULT_RESULT_ID_MAX_COUNT))

/* Retrieve the class identifier from result code */
//#define KFPC_RESULT_GET_CLASS(__Result__)		((unsigned int)((__Result__) & 0x3FFF0000) >> 16)
#define KFPC_RESULT_GET_CLASS(__Result__)		((unsigned int)((__Result__) & 0x003F0000) >> 16)

/* Retrieve the ID number from result code */
#define KFPC_RESULT_GET_ID(__Result__)			((__Result__) & 0x0000FFFF)

#define KFPC_OS_ERR(x)		KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_OS_ERROR,0,x)		/**< EH������������� */


#ifdef __cplusplus
extern "C" 
{
#endif

	const char* BaseErrorCodeToStr(unsigned int ErrorCode,unsigned int Lang);

#ifdef __cplusplus
}  /* end extern "C" */
#endif



#endif // kfpc_error_h__

