#include "kfpc_error.h"

const char* BaseErrorCodeToStr( unsigned int ErrorCode,unsigned int Lang /*= 0*/ )
{
	switch(ErrorCode)
	{
	case KFPC_RESULT_OK:						return (Lang == 0)?		"OK":"�ɹ�";
	case KFPC_RESULT_FAIL:						return (Lang == 0)?		"FAIL":"ͨ��ʧ��";
	case KFPC_RESULT_FATAL_ERROR:				return (Lang == 0)?		"FATAL_ERROR":"����";			
	case KFPC_RESULT_TIMEOUT:					return (Lang == 0)?		"TIMEOUT":"��ʱ";
	case KFPC_RESULT_MISMATCH:					return (Lang == 0)?		"MISMATCH":"��ƥ��";
	case KFPC_RESULT_ACCESS_DENIED:				return (Lang == 0)?		"ACCESS_DENIED":"�ܾ�����";
	case KFPC_RESULT_OUT_OF_RANGE:				return (Lang == 0)?		"OUT_OF_RANGE":"������Χ";
	case KFPC_RESULT_OUT_OF_MEMORY:				return (Lang == 0)?		"OUT_OF_MEMORY":"�ڴ����";
	case KFPC_RESULT_OUT_OF_RESOURCE:			return (Lang == 0)?		"OUT_OF_RESOURCE":"��Դ���";
	case KFPC_RESULT_NULL_PARAM:				return (Lang == 0)?		"NULL_PARAM":"����Ϊ��";
	case KFPC_RESULT_INVALID_PARAM:				return (Lang == 0)?		"INVALID_PARAM":"��Ч����";
	case KFPC_RESULT_INVALID_CONTEXT:			return (Lang == 0)?		"INVALID_CONTEXT":"��Ч������";
	case KFPC_RESULT_INVALID_HANDLE:			return (Lang == 0)?		"INVALID_HANDLE":"��Ч���";
	case KFPC_RESULT_INVALID_ID:				return (Lang == 0)?		"INVALID_ID	":"��ЧID";
	case KFPC_RESULT_INVALID_CONFIG:			return (Lang == 0)?		"INVALID_CONFIG":"��Ч����";
	case KFPC_RESULT_INVALID_STATE:				return (Lang == 0)?		"INVALID_STATE":"��Ч״̬";
	case KFPC_RESULT_INVALID_MESSAGE:			return (Lang == 0)?		"INVALID_MESSAGE":"��Ч��Ϣ";
	case KFPC_RESULT_INVALID_OPERATION:			return (Lang == 0)?		"INVALID_OPERATION":"��Ч����";
	case KFPC_RESULT_NOT_ENOUGH_MEMORY:			return (Lang == 0)?		"NOT_ENOUGH_MEMORY":"�ڴ治��";
	case KFPC_RESULT_NOT_SUPPORTED:				return (Lang == 0)?		"NOT_SUPPORTED":"��֧��";
	case KFPC_RESULT_NOT_INITIALIZED:			return (Lang == 0)?		"NOT_INITIALIZED":"û�г�ʼ��";
	case KFPC_RESULT_NOT_FOUND:					return (Lang == 0)?		"NOT_FOUND":"û���ҵ�";
	case KFPC_RESULT_NOT_READY:					return (Lang == 0)?		"NOT_READY":"û��׼����";
	case KFPC_RESULT_NOT_ACCESSIBLE:			return (Lang == 0)?		"NOT_ACCESSIBLE":"���ɷ���";
	case KFPC_RESULT_NOT_RESPONDING:			return (Lang == 0)?		"NOT_RESPONDING":"û�з���";
	case KFPC_RESULT_NOT_IMPLEMENTED:			return (Lang == 0)?		"NOT_IMPLEMENTED":"û��ִ��";
	case KFPC_RESULT_BUFFER_TOO_SMALL:			return (Lang == 0)?		"BUFFER_TOO_SMALL":"����̫С";
	case KFPC_RESULT_UNSUPPORTED_VERSION:		return (Lang == 0)?		"UNSUPPORTED_VERSION":"��֧�ֵİ汾";
	case KFPC_RESULT_NOT_SUPPORTED_BY_LICENSE:	return (Lang == 0)?		"NOT_SUPPORTED_BY_LICENSE":"��ɲ�֧��";
	case KFPC_RESULT_OPERATION_INCOMPLETE:		return (Lang == 0)?		"OPERATION_INCOMPLETE":"����δ���";
	case KFPC_RESULT_QUEUE_EMPTY:				return (Lang == 0)?		"QUEUE_EMPTY":"����Ϊ��";
	case KFPC_RESULT_THREADPOOL_ALREADY_OPEN:	return (Lang == 0)?		"THREADPOOL_ALREADY_OPEN":"�̳߳��Ѿ���";
	case KFPC_RESULT_THREADPOOL_NOT_OPEN:		return (Lang == 0)?		"THREADPOOL_NOT_OPEN":"�̳߳�δ��";
	case KFPC_RESULT_REQUEST_PASSWD_AUTH:		return (Lang == 0)?		"REQUEST_PASSWD_AUTH":"��Ҫ����";
	case KFPC_RESULT_PASSWD_AUTH_FAIL:			return (Lang == 0)?		"PASSWD_AUTH_FAIL":"������֤ʧ��";
	case KFPC_RESULT_FileNotFound:				return (Lang == 0)?		"FileNotFound":"�ļ�û���ҵ�";
	case KFPC_RESULT_INVALID_LINCENSE:			return (Lang == 0)?		"INVALID_LINCENSE":"��Ч���";
	case KFPC_RESULT_OVERLOAD_LINCENSE:			return (Lang == 0)?		"OVERLOAD_LINCENSE":"������������";
	case KFPC_RESULT_OVERTIME_LINCENSE:			return (Lang == 0)?		"OVERTIME_LINCENSE":"��ɳ�ʱ";
	case KFPC_RESULT_BILL_INVALID_TIME:			return (Lang == 0)?		"BILL_INVALID_TIME":"�ƷѴ�����Чʱ��";
	case KFPC_RESULT_BILL_INVALID_PREFIX:		return (Lang == 0)?		"BILL_INVALID_PREFIX":"�ƷѴ�����Ч����";
	case KFPC_RESULT_BILL_RATE_NOTSET:			return (Lang == 0)?		"BILL_RATE_NOTSET":"�ƷѴ���û�����÷���";
	case KFPC_RESULT_SEND_SMS_ERROR:			return (Lang == 0)?		"SEND_SMS_ERROR":"���Ͷ���ʧ��";
	case KFPC_RESULT_OPEN_FILE_ERROR:			return (Lang == 0)?		"OPEN_FILE_ERROR":"���ļ�ʧ��";

	default:return (Lang == 0)?		"unknown err":"δ֪����";
	}
}