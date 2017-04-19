#ifndef kfpc_logex_h__
#define kfpc_logex_h__
/********************************************************************
 * @data:		2012/10/23
 * @details:	23:10:2012   16:33
 * @file: 		d:\MyProgram\通信库\kfpc_com\kfpc_logex.h 
 * @author:		KFPC
 * @brief:		日记输出模块
*********************************************************************/

#include <string.h>

#define PREFIX_EXPRESSION "| %.*s | CallID:0x%llx | "


inline int GetFunNameLen(const char* pStr)
{
	return (int)(strchr(pStr,'(') - pStr);		
	//printf("%s,%s,Ret:%d\n",pStr,strchr(pStr,'('),Ret);
	//return Ret;
}

inline const char* GetFieldName(const char* pStr)
{
	const char* pFieldName = strchr(pStr,'>');

	return (pFieldName != NULL)?pFieldName+1:pStr;
}

#ifdef LINUX
	#define PREFIX_EXPRESSION_VALUE GetFunNameLen(__PRETTY_FUNCTION__),__PRETTY_FUNCTION__
#else
	#define PREFIX_EXPRESSION_VALUE 128,__FUNCTION__	
#endif 

#ifdef KFPC_LOG_OUTPUT
#include "kfpc_log.h"

KFPC_Log* KFPC_CC_Loger();

#ifdef _DEBUG

	#define DEBUG_LOG(CallID,format, ...) {	\
		unsigned long long ullCallID = CallID;	\
		KFPC_CC_Loger()->Debug(PREFIX_EXPRESSION format,PREFIX_EXPRESSION_VALUE,ullCallID,##__VA_ARGS__);\
	}

	#define DEBUGMEM_LOG(CallID,format, ...)
#else
	#define DEBUG_LOG(CallID,format, ...)
	#define DEBUGMEM_LOG(CallID,format, ...)
#endif

#define INFO_LOG(CallID,format, ...) {\
	unsigned long long ullCallID = CallID;	\
	KFPC_CC_Loger()->Info(PREFIX_EXPRESSION format,PREFIX_EXPRESSION_VALUE,ullCallID,##__VA_ARGS__);\
}

#define WARNING_LOG(CallID,format, ...) {\
	unsigned long long ullCallID = CallID;	\
	KFPC_CC_Loger()->Warning(PREFIX_EXPRESSION format,PREFIX_EXPRESSION_VALUE,ullCallID,##__VA_ARGS__);\
}

#define ERROR_LOG(CallID,format, ...) {\
	unsigned long long ullCallID = CallID;	\
	KFPC_CC_Loger()->Error(PREFIX_EXPRESSION format,PREFIX_EXPRESSION_VALUE,ullCallID,##__VA_ARGS__);\
}

#define FATAL_LOG(CallID,format, ...) {\
	unsigned long long ullCallID = CallID;	\
	KFPC_CC_Loger()->Fatal(PREFIX_EXPRESSION format,PREFIX_EXPRESSION_VALUE,ullCallID,##__VA_ARGS__);\
}

#define BEGIN_MSG_LOG(CallID,format, ...) {	\
	unsigned long long ullCallID = CallID;	\
	KFPC_CC_Loger()->BeginLog(LL_INFO,PREFIX_EXPRESSION format,PREFIX_EXPRESSION_VALUE,ullCallID,##__VA_ARGS__);



#define APPEND_MSG_LOG(Type,Val)			KFPC_CC_Loger()->AppendLog(LL_INFO, "%s:" Type "," , GetFieldName(#Val),Val);

#define END_MSG_LOG()						KFPC_CC_Loger()->EndLog(LL_INFO); \
}

#define LOG_SETOUTPUTMODE(x)				KFPC_CC_Loger()->SetOutputMode(x)
#define LOG_CLOSE()							KFPC_CC_Loger()->Close();
#else
#define DEBUG_LOG(CallID,format, ...)
#define DEBUGMEM_LOG(CallID,format, ...)
#define INFO_LOG(CallID,format, ...)
#define WARNING_LOG(CallID,format, ...)
#define ERROR_LOG(CallID,format, ...)
#define FATAL_LOG(CallID,format, ...)

#define BEGIN_MSG_LOG(CallID,format, ...)	
#define APPEND_MSG_LOG(Type,Val)			
#define END_MSG_LOG()						
#define LOG_SETOUTPUTMODE(x)
#define LOG_CLOSE()

#endif // KFPC_LOG_OUTPUT

#endif // kfpc_logex_h__

