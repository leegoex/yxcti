#ifndef kfpc_licenseser_api_h__
#define kfpc_licenseser_api_h__
#include "kfpc_api.h"
#include "kfpc_linuxwinapi.h"
#include "KFPC_ContactCenterPublicDef.h"

//#include "kfpc_id.h"

/********************************************************************
 * @data:		2013/04/03
 * @details:	21:11:2012   10:21
 * @file: 		kfpc_licenseser_api.h 
 * @author:		KFPC
 * @brief:		license服务通讯消息定义
 *********************************************************************/

#define  MAX_SWITCH_ID	32
/**
 *	License message IDs 
 */ 	
#define	KFPC_MSG_ID_LIC_TSERVERLIC						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_LIC, 0x01)		/**< TServer许可事件 */
#define	KFPC_MSG_ID_LIC_CCSLIC							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_LIC, 0x02)       /**< CCS许可事件 */
#define	KFPC_MSG_ID_LIC_FAXLIC							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_LIC, 0x03)       /**< FAX许可事件 */
#define	KFPC_MSG_ID_LIC_BASELIC							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_LIC, 0x04)		/**< Base许可事件 */
#define	KFPC_MSG_ID_LIC_IPRECLIC						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_LIC, 0x05)		/**< IPRecord许可事件 */
#define	KFPC_MSG_ID_LIC_END								KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_LIC,	0x06)		/**< 结束ID */
#define KFPC_MAX_MSG_ID_LIC								KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_LIC_END)    
/**
 *	TTS Functions
 */
static __inline const char* KFPC_MSG_ID_LIC_TO_STRING( unsigned int in_un32MsgId )
{

	switch( in_un32MsgId )
	{
	case KFPC_MSG_ID_LIC_TSERVERLIC:										return (const char*)"EVT_TServerLic";
	case KFPC_MSG_ID_LIC_CCSLIC:											return (const char*)"EVT_CCSLic";
	case KFPC_MSG_ID_LIC_FAXLIC:											return (const char*)"EVT_FAXLIC";
	case KFPC_MSG_ID_LIC_BASELIC:											return (const char*)"EVT_BASELIC";
	case KFPC_MSG_ID_LIC_IPRECLIC:											return (const char*)"EVT_IPRECLIC";
	}

	return (const char*)"";
}

#define KFPC_MAX_LIC_COUNT						64		/**< 最大许可数量 */


/**
 *	
 */

typedef struct KFPC_TSERVERLIC_INFO
{
	unsigned long	ValidTime;			//有效时间
	char			SwichID[MAX_SWITCH_ID];		//交换机ID
	unsigned short	AgChCount;			//模拟通道数
	unsigned short	SpanChCount;		//数字中继数
	unsigned short	VoipChCount;		//Voip通道数
	unsigned short	IVRChCount;			//IVR通道数
	unsigned short	AppCount;			//同时运行App个数
}KFPC_TSERVERLIC_INFO;

typedef struct KFPC_CCSLIC_INFO
{
	unsigned long	ValidTime;			//有效时间
	unsigned short	AgentCount;			//坐席数
	unsigned short	AppCount;			//同时运行App个数
}KFPC_CCSLIC_INFO;

typedef struct KFPC_FAXLIC_INFO
{
	unsigned long	ValidTime;			//有效时间
	unsigned short	FaxChCount;			//传真通道数
	unsigned short	AppCount;			//同时运行App个数
}KFPC_FAXLIC_INFO;

typedef struct KFPC_BASELIC_INFO
{
	unsigned long	ValidTime;			//有效时间
}KFPC_BASELIC_INFO;

typedef struct KFPC_IPR_INFO
{
	unsigned long	ValidTime;			//有效时间
	unsigned short	ChCount;			//并发数
	unsigned char	Audio;				//音频开关
	unsigned char	Video;				//视频开关
	unsigned char	Traffic;			//流量分析开关
	unsigned short	AppCount;			//同时运行App个数
}KFPC_IPR_INFO;

typedef struct KFPC_LIC_REQ_TSERVERLIC
{
	KFPC_MSG_HEADER		MsgHead;
	unsigned int		AppType;
	char				SwichID[MAX_SWITCH_ID];		//交换机ID

}KFPC_LIC_REQ_TSERVERLIC;

typedef struct KFPC_LIC_RSP_TSERVERLIC
{
	KFPC_MSG_HEADER				MsgHead;
	KFPC_TSERVERLIC_INFO		TServerLic;
	unsigned int				Result;
	unsigned char				AlignBuf[16];		/**< 对齐Buf */
}KFPC_LIC_RSP_TSERVERLIC;

typedef struct KFPC_LIC_REQ_CCSLIC
{
	KFPC_MSG_HEADER		MsgHead;
	unsigned int		AppType;

}KFPC_LIC_REQ_CCSLIC;

typedef struct KFPC_LIC_RSP_CCSLIC
{
	KFPC_MSG_HEADER		MsgHead;
	KFPC_CCSLIC_INFO	CCSLic;
	unsigned int		Result;
	unsigned char		AlignBuf[16];		/**< 对齐Buf */
}KFPC_LIC_RSP_CCSLIC;

typedef struct KFPC_LIC_REQ_FAXLIC
{
	KFPC_MSG_HEADER		MsgHead;
	unsigned int		AppType;

}KFPC_LIC_REQ_FAXLIC;

typedef struct KFPC_LIC_RSP_FAXLIC
{
	KFPC_MSG_HEADER		MsgHead;
	KFPC_FAXLIC_INFO	FaxLic;
	unsigned int		Result;
	unsigned char		AlignBuf[16];		/**< 对齐Buf */
}KFPC_LIC_RSP_FAXLIC;


typedef struct KFPC_LIC_REQ_BASELIC
{
	KFPC_MSG_HEADER		MsgHead;
	unsigned int		AppType;

}KFPC_LIC_REQ_BASELIC;

typedef struct KFPC_LIC_RSP_BASELIC
{
	KFPC_MSG_HEADER		MsgHead;
	KFPC_BASELIC_INFO	BaseLic;
	unsigned int		Result;
	unsigned char		AlignBuf[16];		/**< 对齐Buf */
}KFPC_LIC_RSP_BASELIC;

typedef struct KFPC_LIC_REQ_IPR
{
	KFPC_MSG_HEADER		MsgHead;
	unsigned int		AppType;

}KFPC_LIC_REQ_IPR;

typedef struct KFPC_LIC_RSP_IPR
{
	KFPC_MSG_HEADER		MsgHead;
	KFPC_IPR_INFO		IPR_INFO;
	unsigned int		Result;
	unsigned char		AlignBuf[16];		/**< 对齐Buf */
}KFPC_LIC_RSP_IPR;



#endif // kfpc_licenseser_api_h__
