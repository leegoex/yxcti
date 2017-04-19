#ifndef kfpc_msg_h__
#define kfpc_msg_h__
/********************************************************************
 * @data:		2012/09/26
 * @details:	26:9:2012   11:15
 * @file: 		D:\MyProgram\通信库\kfpc_com\kfpc_msg.h 
 * @author:		KFPC
 * @brief:		基础消息结构定义
*********************************************************************/

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Defines
 *------------------------------------------------------------------------------------------------------------------------------*/
#define MSG_FLAG						0xFEEFEDDE					/**< 消息标识 */
#define	UINTTYPE						(unsigned int) 0XFFFFFFFF	/**< 无效32位值 */
#define ULONGTYPE						(unsigned int)0XFFFFFFFF	/**< 无效32位值 */
#define	USHORTTYPE						(unsigned short)0XFFFF		/**< 无效16位值 */
#define UCHARTYPE						(unsigned char)0XFF			/**< 无效8位值 */
#define KFPC_API_NAME_MAX_LEN			128							/**< 最大应用程序名长度 */
#define KFPC_API_LISTEN_PORT_MAX_COUNT	1							/**< 同时最大监听端口数 */
#define KFPC_MAX_SOCKET_COUNT			65535						/**< 是大可管理的Socket数 */
#define KFPC_MAX_SOCKET_ROACTOR			32							/**< 最大反射器数 */
#define KFPC_MAX_PASSWD_LEN				64							/**< 最大密码长度 */
#define	KFPC_MAX_IP_LEN					32							/**<IP 最大长度 */
#define KFPC_MIN_KEEP_LIVE_COUNT		3	
#define KFPC_DEFAULT_FILTER_COUNT		4							/**< 默认过滤器数量 */
#define KFPC_DEFAULT_SOCKET_COUNT		32							/**< 服务器端最大Socket数量 */
#define KFPC_DEFAULT_KEEPLIVETIME_COUNT	6							/**< 默认心跳次数 */
#define KFPC_DEFAULT_KEEPLIVETIME		15							/**< 默认心跳时长 */
#define KFPC_DEFAULT_THREAD_POOL_SIZE	4							/**< 默认线程池大小 */
#define KFPC_MAX_KEY_LEN				16							/**< 最大的key长度 */
#define KFPC_DEFAULT_LISTEN_PORT		12813						/**< 默认的监听端口 */
#define KFPC_MAX_APP_ID					50000						/**< 最大的APP ID */
#define KFPC_DEFAULT_MUTTICAST_IP		"224.12.8.13"				/**< 默认多播IP */
#define KFPC_CLIENT_SOCKET_COUNT		16							/**< 客户端最大TCP 数 */
#define KFPC_CLIENT_THREAD_POOL_SIZE	4							/**< 客户端线程数 */
#define KFPC_MAX_COM_BUF_SIZE			10240						/**< 最大的通信BUF大小 */
#define KFPC_MAX_GUID_LEN				16
#define KFPC_MAX_INTERFACE_COUNT		64							/**< 最大的网卡数 */
#define KFPC_ONE_LOOP_TIME				5							/**< 单个循环最大5秒 */
#define KFPC_MAX_SEND_COUNT				32							/**< 最大同时发送个数 */
#define	MAX_CONNECT_INDEX				2							/**< 同一个程序的最大连接 */
#define KFPC_RECONNECT_TIMER			5							/**< 重连定时 */	
#define KFPC_DEFAULT_MUTTICAST_PORT		12813						/**< 默认多播端口 */
#define KFPC_MAX_MSG_ID_STR_LEN			128							/**< 最大的字符串长度ID */
#define KFPC_SEMWAITTIMEOUT				5000						/**< 信号量定时器 毫秒*/
/*--------------------------------------------------------------------------------------------------------------------------------
 |  Types
 *------------------------------------------------------------------------------------------------------------------------------*/


/**
 * 消息类型
 */
typedef enum KFPC_MSG_TYPE
{
	KFPC_MSG_TYPE_FIRST			= 0,
	KFPC_MSG_TYPE_REQUEST		= 1,		/* Bits field so values can be ORed in filters */
	KFPC_MSG_TYPE_RESPONSE		= 2,
	KFPC_MSG_TYPE_EVENT			= 4,
	KFPC_MSG_TYPE_LAST			= 5

} KFPC_MSG_TYPE, *PKFPC_MSG_TYPE;

static const char* MsgTypeToStr(KFPC_MSG_TYPE MsgType)
{
	switch(MsgType)
	{
	case KFPC_MSG_TYPE_REQUEST	:	return "REQUEST";
	case KFPC_MSG_TYPE_RESPONSE	:	return "RESPONSE";
	case KFPC_MSG_TYPE_EVENT	:	return "EVENT";	
	default: return "unknow";
	}
}

//KFPC_MSG_TYPE	IntToMsgType(unsigned int MsgType);
static KFPC_MSG_TYPE IntToMsgType( unsigned int MsgType )
{
	switch(MsgType)
	{
	case 1:return KFPC_MSG_TYPE_REQUEST;
	case 2:return KFPC_MSG_TYPE_RESPONSE;
	case 3:return KFPC_MSG_TYPE_EVENT;
	default: return KFPC_MSG_TYPE_REQUEST;
	}
}

/**
 * 基础消息头 
 */ 
typedef struct KFPC_MSG_HEADER
{
	/*@{*/
	unsigned int		un32MsgFlag;							/**< 消息标识，通过这个标识识别是我们的消息，防水网络上的攻击 */
	unsigned int		un32MsgId;							/**< Must be kept first */
	unsigned int		un32MsgType;						/**< Message type */
	unsigned int		un32Length;							/**< The total length of the message,不包括消息头 */
	unsigned int		un32SerialNumber;					/**< This buffer's unique serial number */
	unsigned int		un32UserContext1;					/**< User Ctx #1 (filterable) 用户上下文1*/
	unsigned int		un32UserContext2;					/**< User Ctx #2 (filterable) 用户上下文2*/
	unsigned int		un32SrcAPPId;						/**< Unique application identifier 应APP ID*/
	unsigned int		un32DstAPPId;						/**< Unique application identifier 应APP ID*/
	/*@}*/
} KFPC_MSG_HEADER, *PKFPC_MSG_HEADER;

typedef struct	KFPC_MSG
{
	KFPC_MSG_HEADER	Header;
	unsigned char	Buf[1];
}KFPC_MSG;

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Global variables
 *------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Macros
 *------------------------------------------------------------------------------------------------------------------------------*/
#define		KFPC_FORMAT_HEADER(__pHeader, __MsgId, __MsgType, __Length, __UserContext1, __UserContext2)		\
{                                                                                                           \
    (__pHeader)->un32MsgFlag = MSG_FLAG;                                                                      \
	(__pHeader)->un32MsgId = (__MsgId);																		\
	(__pHeader)->un32MsgType = (KFPC_MSG_TYPE)(__MsgType);													\
	(__pHeader)->un32Length = (__Length);																	\
	(__pHeader)->un32SerialNumber = 0;																		\
	(__pHeader)->un32SrcAPPId = 0;																			\
	(__pHeader)->un32DstAPPId = 0;																			\
	(__pHeader)->un32UserContext1 = (__UserContext1);														\
	(__pHeader)->un32UserContext2 = (__UserContext2);														\
}                                                                                                           \

#define KFPC_HEAD_SIZE							sizeof(KFPC_MSG_HEADER)  /**<size of message head */
#define KFPC_MAX_MSG_BODY						KFPC_MAX_COM_BUF_SIZE - KFPC_HEAD_SIZE						/**< 最大消息体大小 */
/*--------------------------------------------------------------------------------------------------------------------------------
 |  Function Prototypes
 *------------------------------------------------------------------------------------------------------------------------------*/
#endif // kfpc_msg_h__

