/********************************************************************
 * @data:		2012/09/26
 * @details:	26:9:2012   17:50
 * @file: 		D:\MyProgram\通信库\kfpc_com\kfpc_error.h 
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
#define	KFPC_RESULT_OK							0x0000			/**< 成功 */
#define KFPC_RESULT_FAIL						0x0001			/**< 通常失败 */
#define KFPC_RESULT_FATAL_ERROR					0x0002			
#define KFPC_RESULT_TIMEOUT						0x0003			/**< 超时 */
#define KFPC_RESULT_MISMATCH					0x0004			/**< 不匹配 */
#define KFPC_RESULT_ACCESS_DENIED				0x0005			/**< 拒绝访问 */
#define KFPC_RESULT_OUT_OF_RANGE				0x0006			/**< 超出范围 */
#define KFPC_RESULT_OUT_OF_MEMORY				0x0007			/**< 内存溢出 */
#define KFPC_RESULT_OUT_OF_RESOURCE				0x0008			/**< 资源溢出 */
#define KFPC_RESULT_NULL_PARAM					0x0009			/**< 参数为空 */
#define KFPC_RESULT_INVALID_PARAM				0x000A			/**< 无效参数 */
#define KFPC_RESULT_INVALID_CONTEXT				0x000B			/**< 无效上下文 */
#define KFPC_RESULT_INVALID_HANDLE				0x000C			/**< 无效句柄 */
#define KFPC_RESULT_INVALID_ID					0x000D			/**< 无效ID */
#define KFPC_RESULT_INVALID_CONFIG				0x000E			/**< 无效配置 */
#define KFPC_RESULT_INVALID_STATE				0x000F			/**< 无效状态 */
#define KFPC_RESULT_INVALID_MESSAGE				0x0010			/**< 无效消息 */
#define KFPC_RESULT_INVALID_OPERATION			0x0011			/**< 无效操作 */
#define KFPC_RESULT_NOT_ENOUGH_MEMORY			0x0012			/**< 内存不足 */
#define KFPC_RESULT_NOT_SUPPORTED				0x0013			/**< 不支持 */
#define KFPC_RESULT_NOT_INITIALIZED				0x0014			/**< 没有初始化 */
#define KFPC_RESULT_NOT_FOUND					0x0015			/**< 没有找到 */
#define KFPC_RESULT_NOT_READY					0x0016			/**< 没有准备好 */
#define KFPC_RESULT_NOT_ACCESSIBLE				0x0017			/**< 不可访问 */
#define KFPC_RESULT_NOT_RESPONDING				0x0018			/**< 没有返回 */
#define KFPC_RESULT_NOT_IMPLEMENTED				0x0019			/**< 没有执行 */
#define KFPC_RESULT_BUFFER_TOO_SMALL			0x001A			/**< 缓冲太小 */
#define KFPC_RESULT_UNSUPPORTED_VERSION			0x0020			/**< 不支持的版本 */
#define KFPC_RESULT_NOT_SUPPORTED_BY_LICENSE	0x0021			/**< 许可不支持 */
#define KFPC_RESULT_OPERATION_INCOMPLETE		0x0022			/**< 操作未完成 */
#define KFPC_RESULT_QUEUE_EMPTY					0x0023			/**< 队例为空 */
#define KFPC_RESULT_THREADPOOL_ALREADY_OPEN		0x0024			/**< 线程池已经打开 */
#define KFPC_RESULT_THREADPOOL_NOT_OPEN			0x0025			/**< 线程池未打开 */
#define KFPC_RESULT_REQUEST_PASSWD_AUTH			0x0026			/**< 需要密码 */
#define KFPC_RESULT_PASSWD_AUTH_FAIL			0x0027			/**< 密码认证失败 */
#define KFPC_RESULT_FileNotFound				0x0028			/**< 文件没有找到 */
#define KFPC_RESULT_INVALID_LINCENSE			0x0029			/**< 无效许可 */
#define KFPC_RESULT_OVERLOAD_LINCENSE			0x0030			/**< 超出最大许可数 */
#define KFPC_RESULT_OVERTIME_LINCENSE			0x0031			/**< 许可超时 */
#define KFPC_RESULT_BILL_INVALID_TIME			0x0032			/**< 计费错误，无效时间 */
#define KFPC_RESULT_BILL_INVALID_PREFIX			0x0033			/**< 计费错误，无效区号 */
#define KFPC_RESULT_BILL_RATE_NOTSET			0x0034			/**< 计费错误，没有设置费率 */
#define KFPC_RESULT_SEND_SMS_ERROR				0x0035			/**< 发送短信失败 */
#define KFPC_RESULT_OPEN_FILE_ERROR				0x0036			/**< 打开文件失败 */
#define KFPC_RESULT_PARSE_XML_ERROR				0x0037			/**< 解析XML失败 */

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

#define KFPC_OS_ERR(x)		KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_OS_ERROR,0,x)		/**< EH交换机错误代码 */


#ifdef __cplusplus
extern "C" 
{
#endif

	const char* BaseErrorCodeToStr(unsigned int ErrorCode,unsigned int Lang);

#ifdef __cplusplus
}  /* end extern "C" */
#endif



#endif // kfpc_error_h__

