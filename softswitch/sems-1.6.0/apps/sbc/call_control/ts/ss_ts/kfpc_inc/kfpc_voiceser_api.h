#ifndef kfpc_voiceser_api_h__
#define kfpc_voiceser_api_h__


#include "kfpc_error.h"
#include "kfpc_id.h"
#include "kfpc_msg.h"
#include "KFPC_ContactCenterPublicDef.h"

/**
 *	voice ser API 
 */ 
	#define	KFPC_MSG_ID_VOICE_COMPRESS_MSG			KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_VOICE, 0x01)		/**< 话音文件压缩接口 */
	#define	KFPC_MSG_ID_VOICE_EVT_SERVER_INFO		KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_VOICE, 0x02)		/**< 服务信息 */
	
static __inline const char* KFPC_MSG_ID_VOICE_TO_STRING( unsigned int in_un32MsgId )
{
	
	switch( in_un32MsgId )
	{
	case KFPC_MSG_ID_VOICE_COMPRESS_MSG:										return (const char*)"VOICE_COMPRESS_MSG";
	case KFPC_MSG_ID_VOICE_EVT_SERVER_INFO:										return "VOICE_EVT_SERVER_INFO";
	}

	return (const char*)"";
}


typedef struct KFPC_REQ_API_VOICE_FILE_COMPRESS
{
	KFPC_MSG_HEADER			Header;							/**< 消息头 */
	unsigned long long		CallID;									
	char					OrgFileName[KFPC_MAX_FILE_NAME];	/**< 字符串内容 */
	char					DstFileName[KFPC_MAX_FILE_NAME];	/**< 字符串内容 */
}KFPC_REQ_API_VOICE_FILE_COMPRESS;

typedef struct KFPC_RSP_API_VOICE_FILE_COMPRESS
{
	KFPC_MSG_HEADER			Header;							/**< 消息头 */
	unsigned long long		CallID;									
	unsigned int			Result;						
}KFPC_RSP_API_VOICE_FILE_COMPRESS;

typedef struct KFPC_EVT_API_VOICE_SERVER_INFO
{
	KFPC_MSG_HEADER			Header;							/**< 消息头 */
	unsigned int			PRDID;							/**< PRD ID */
}KFPC_EVT_API_VOICE_SERVER_INFO;

#endif // kfpc_voiceser_api_h__
