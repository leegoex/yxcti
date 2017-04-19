#include "kfpc_error.h"

const char* BaseErrorCodeToStr( unsigned int ErrorCode,unsigned int Lang /*= 0*/ )
{
	switch(ErrorCode)
	{
	case KFPC_RESULT_OK:						return (Lang == 0)?		"OK":"成功";
	case KFPC_RESULT_FAIL:						return (Lang == 0)?		"FAIL":"通常失败";
	case KFPC_RESULT_FATAL_ERROR:				return (Lang == 0)?		"FATAL_ERROR":"错误";			
	case KFPC_RESULT_TIMEOUT:					return (Lang == 0)?		"TIMEOUT":"超时";
	case KFPC_RESULT_MISMATCH:					return (Lang == 0)?		"MISMATCH":"不匹配";
	case KFPC_RESULT_ACCESS_DENIED:				return (Lang == 0)?		"ACCESS_DENIED":"拒绝访问";
	case KFPC_RESULT_OUT_OF_RANGE:				return (Lang == 0)?		"OUT_OF_RANGE":"超出范围";
	case KFPC_RESULT_OUT_OF_MEMORY:				return (Lang == 0)?		"OUT_OF_MEMORY":"内存溢出";
	case KFPC_RESULT_OUT_OF_RESOURCE:			return (Lang == 0)?		"OUT_OF_RESOURCE":"资源溢出";
	case KFPC_RESULT_NULL_PARAM:				return (Lang == 0)?		"NULL_PARAM":"参数为空";
	case KFPC_RESULT_INVALID_PARAM:				return (Lang == 0)?		"INVALID_PARAM":"无效参数";
	case KFPC_RESULT_INVALID_CONTEXT:			return (Lang == 0)?		"INVALID_CONTEXT":"无效上下文";
	case KFPC_RESULT_INVALID_HANDLE:			return (Lang == 0)?		"INVALID_HANDLE":"无效句柄";
	case KFPC_RESULT_INVALID_ID:				return (Lang == 0)?		"INVALID_ID	":"无效ID";
	case KFPC_RESULT_INVALID_CONFIG:			return (Lang == 0)?		"INVALID_CONFIG":"无效配置";
	case KFPC_RESULT_INVALID_STATE:				return (Lang == 0)?		"INVALID_STATE":"无效状态";
	case KFPC_RESULT_INVALID_MESSAGE:			return (Lang == 0)?		"INVALID_MESSAGE":"无效消息";
	case KFPC_RESULT_INVALID_OPERATION:			return (Lang == 0)?		"INVALID_OPERATION":"无效操作";
	case KFPC_RESULT_NOT_ENOUGH_MEMORY:			return (Lang == 0)?		"NOT_ENOUGH_MEMORY":"内存不足";
	case KFPC_RESULT_NOT_SUPPORTED:				return (Lang == 0)?		"NOT_SUPPORTED":"不支持";
	case KFPC_RESULT_NOT_INITIALIZED:			return (Lang == 0)?		"NOT_INITIALIZED":"没有初始化";
	case KFPC_RESULT_NOT_FOUND:					return (Lang == 0)?		"NOT_FOUND":"没有找到";
	case KFPC_RESULT_NOT_READY:					return (Lang == 0)?		"NOT_READY":"没有准备好";
	case KFPC_RESULT_NOT_ACCESSIBLE:			return (Lang == 0)?		"NOT_ACCESSIBLE":"不可访问";
	case KFPC_RESULT_NOT_RESPONDING:			return (Lang == 0)?		"NOT_RESPONDING":"没有返回";
	case KFPC_RESULT_NOT_IMPLEMENTED:			return (Lang == 0)?		"NOT_IMPLEMENTED":"没有执行";
	case KFPC_RESULT_BUFFER_TOO_SMALL:			return (Lang == 0)?		"BUFFER_TOO_SMALL":"缓冲太小";
	case KFPC_RESULT_UNSUPPORTED_VERSION:		return (Lang == 0)?		"UNSUPPORTED_VERSION":"不支持的版本";
	case KFPC_RESULT_NOT_SUPPORTED_BY_LICENSE:	return (Lang == 0)?		"NOT_SUPPORTED_BY_LICENSE":"许可不支持";
	case KFPC_RESULT_OPERATION_INCOMPLETE:		return (Lang == 0)?		"OPERATION_INCOMPLETE":"操作未完成";
	case KFPC_RESULT_QUEUE_EMPTY:				return (Lang == 0)?		"QUEUE_EMPTY":"队例为空";
	case KFPC_RESULT_THREADPOOL_ALREADY_OPEN:	return (Lang == 0)?		"THREADPOOL_ALREADY_OPEN":"线程池已经打开";
	case KFPC_RESULT_THREADPOOL_NOT_OPEN:		return (Lang == 0)?		"THREADPOOL_NOT_OPEN":"线程池未打开";
	case KFPC_RESULT_REQUEST_PASSWD_AUTH:		return (Lang == 0)?		"REQUEST_PASSWD_AUTH":"需要密码";
	case KFPC_RESULT_PASSWD_AUTH_FAIL:			return (Lang == 0)?		"PASSWD_AUTH_FAIL":"密码认证失败";
	case KFPC_RESULT_FileNotFound:				return (Lang == 0)?		"FileNotFound":"文件没有找到";
	case KFPC_RESULT_INVALID_LINCENSE:			return (Lang == 0)?		"INVALID_LINCENSE":"无效许可";
	case KFPC_RESULT_OVERLOAD_LINCENSE:			return (Lang == 0)?		"OVERLOAD_LINCENSE":"超出最大许可数";
	case KFPC_RESULT_OVERTIME_LINCENSE:			return (Lang == 0)?		"OVERTIME_LINCENSE":"许可超时";
	case KFPC_RESULT_BILL_INVALID_TIME:			return (Lang == 0)?		"BILL_INVALID_TIME":"计费错误，无效时间";
	case KFPC_RESULT_BILL_INVALID_PREFIX:		return (Lang == 0)?		"BILL_INVALID_PREFIX":"计费错误，无效区号";
	case KFPC_RESULT_BILL_RATE_NOTSET:			return (Lang == 0)?		"BILL_RATE_NOTSET":"计费错误，没有设置费率";
	case KFPC_RESULT_SEND_SMS_ERROR:			return (Lang == 0)?		"SEND_SMS_ERROR":"发送短信失败";
	case KFPC_RESULT_OPEN_FILE_ERROR:			return (Lang == 0)?		"OPEN_FILE_ERROR":"打开文件失败";

	default:return (Lang == 0)?		"unknown err":"未知错误";
	}
}