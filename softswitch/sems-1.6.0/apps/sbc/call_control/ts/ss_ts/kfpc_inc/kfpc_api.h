#ifndef kfpc_api_h__
#define kfpc_api_h__
/********************************************************************
 * @data:		2012/09/26
 * @details:	26:9:2012   14:52
 * @file: 		D:\MyProgram\通信库\kfpc_com\kfpc_api.h 
 * @author:		KFPC
 * @brief:		通信库API定义
*********************************************************************/


//以下为正确定义，满足C++/C===============
#ifdef KFPC_COM_EXPORTS
	#ifdef WIN32
		#define KFPC_COM_API __declspec(dllexport)
	#else
		#define KFPC_COM_API extern "C" 
	#endif
#else

	#ifdef WIN32
		#define KFPC_COM_API	__declspec( dllimport )
	#else
		#ifdef __cplusplus
			#define KFPC_COM_API extern "C" 
		#else
			#define KFPC_COM_API
		#endif
	#endif
#endif


//=========================================

//下面只能满足C++,或者说不正确
//#ifdef KFPC_COM_EXPORTS
//	#ifdef WIN32
//		#define KFPC_COM_API __declspec(dllexport)
//	#else
//		#define KFPC_COM_API extern "C" 
//	#endif
//#else
//
//	#ifdef WIN32
//		#define KFPC_COM_API	
//	#else
//		#define KFPC_COM_API
//	#endif
//#endif



#include "kfpc_error.h"
#include "kfpc_id.h"
#include "kfpc_msg.h"


/**
 *	API library message IDs 
 */ 
	#define	KFPC_MSG_ID_API_REMOTE_APP_ONLINE						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x01)		/**< 远端应用上线 */
	#define	KFPC_MSG_ID_API_REMOTE_APP_OFFLINE						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x02)		/**< 远端应用下线 */
	#define	KFPC_MSG_ID_API_LOCAL_CONNECTED							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x03)		/**< 本地客户端连接成功*/
	#define	KFPC_MSG_ID_API_REMOTE_CONNECTED						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x04)		/**< 远端应用连接 */
	#define	KFPC_MSG_ID_API_APP_DISCONNECT							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x05)		/**< 应用断开连接,包括远端,本地 */
	#define	KFPC_MSG_ID_API_LOCAL_REDUNDANCE_STATUS_CHANGE			KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x06)		/**< 本地冗余状态改变事件*/
	#define	KFPC_MSG_ID_API_REMOTE_APP_REDUNDANCE_STATUS_CHANGE		KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x07)		/**< 远端冗余状态改变事件*/
	#define	KFPC_MSG_ID_API_TEST_MSG								KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x08)		/**< 测试消息*/
    #define	KFPC_MSG_ID_API_APPID_CONFLICT							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x09)		/**< APP冲突ID*/
	#define	KFPC_MSG_ID_API_END										KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x0a)		/**< 结束ID 非常重要*/
	
	#define KFPC_MAX_MSG_ID_API                                     KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_API_END)          /**< 最大的API_ID数*/
static __inline const char* KFPC_MSG_ID_API_TO_STRING( unsigned int in_un32MsgId )
{
	
	switch( in_un32MsgId )
	{
	case KFPC_MSG_ID_API_REMOTE_APP_ONLINE:										return (const char*)"REMOTE_APP_ONLINE";
	case KFPC_MSG_ID_API_REMOTE_APP_OFFLINE:									return (const char*)"REMOTE_APP_OFFLINE";
	case KFPC_MSG_ID_API_LOCAL_CONNECTED:										return (const char*)"LOCAL_CONNECTED";
	case KFPC_MSG_ID_API_REMOTE_CONNECTED:										return (const char*)"REMOTE_CONNECTED";
	case KFPC_MSG_ID_API_APP_DISCONNECT	:										return (const char*)"APP_DISCONNECT";
	case KFPC_MSG_ID_API_LOCAL_REDUNDANCE_STATUS_CHANGE:						return (const char*)"LOCAL_REDUNDANCE_STATUS_CHANGE";
	case KFPC_MSG_ID_API_REMOTE_APP_REDUNDANCE_STATUS_CHANGE:					return (const char*)"REMOTE_APP_REDUNDANCE_STATUS_CHANGE";
	case KFPC_MSG_ID_API_TEST_MSG:												return (const char*)"TEST_MSG";
	case KFPC_MSG_ID_API_APPID_CONFLICT:										return (const char*)"APPID_CONFLICT";
	}

	return (const char*)"";
}

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Defines
 *------------------------------------------------------------------------------------------------------------------------------*/
//#define	MAX_FILTER_PARAM_COUNT		8		/**< 最大过滤器参数个数 */
//#define MAX_APPGROUP_COUNT			1024	/**< 最大的APP 组ID个数 */
/*--------------------------------------------------------------------------------------------------------------------------------
 |  Types
 *------------------------------------------------------------------------------------------------------------------------------*/

	/**
	 *	应用信息
	 */
	typedef struct KFPC_AppInfo
	{
		char			AppName[KFPC_API_NAME_MAX_LEN];					/**< 应用程序名称*/
		unsigned int	AppID;											/**< 应用程序ID*/
		unsigned int	AppType;										/**< 应用类型*/
		unsigned int	AppGroupID;										/**< 应用所属组,如果为0不属于任何组*/ 
		unsigned int	MasterFlag;										/**< 主从属性 1为主，0为从，2 就不再参与主从竞争*/
		unsigned int	ListenPort;										/**< 监听端口数 < 65535，0为默认,客户端为-1，不需要监听 */
		char			PeerIp[KFPC_MAX_IP_LEN];						/**< 远程IP长度 */
		unsigned char	UniqueIdentify[KFPC_MAX_GUID_LEN]; 
	}KFPC_AppInfo, *PKFPC_AppInfo;



	/**
	 *	库参数
	 */
	typedef struct KFPC_LIB_PARAMS
	{
		KFPC_AppInfo	AppInfo;						
		unsigned int	MulticastPort;									/**< 多播端口 */
		char			MutticastIP[KFPC_MAX_IP_LEN];					/**< 多播IP */
		char			AuthPassWord[KFPC_MAX_PASSWD_LEN];				/**< 服务端连接密码 */
		unsigned int	ThreadPoolSize;									/**< 线程池数量 最32*/
		unsigned int	KeepLiveTime;									/**< 心跳时长 */
		unsigned int	KeepLiveTimeCount;								/**< 心跳次数,最少是3次 */
		unsigned int	MaxSocketCount;									/**< 最大Socket数 最大65535*/
		unsigned int	MsgFilterCount;									/**< 消息过滤器数量 */
		unsigned int	LogOutputMode;									/**< 日记输出模式 LOM_FILE|LOM_CONSOLE*/
		unsigned int	FileLogLevel;									/**< 文件日记输出级别 参考KFPC_LOG_LEVEL*/
		unsigned int	ConsoleLogLevel;								/**< 控制台输出日记级别 参考KFPC_LOG_LEVEL*/
	}KFPC_LIB_PARAMS,*PKFPC_LIB_PARAMS;

	/**
	 *	 Message filtering selection 
	 */
	typedef enum KFPC_FILTER
	{
		KFPC_FILTER_NONE					= 0,			/**<  No filter criteria (capture all messages) */
		KFPC_FILTER_MSG_SRCAPPID			= (1<<0),		/**< Match source app id */
		KFPC_FILTER_MSG_TYPE				= (1<<1),		/**< Match MsgType (Bitwise ORed) */
		KFPC_FILTER_MSG_ID					= (1<<2),		/**< Match MsgId */
		KFPC_FILTER_MSG_GROUP				= (1<<3),		/**< Match MsgGroup */
		KFPC_FILTER_MSG_SERIAL_NUMBER		= (1<<4),		/**< Match message's serial number (implicit filtering) */
		KFPC_FILTER_MSG_USER_CONTEXT1		= (1<<5),		/**< Match UserContext1 */
		KFPC_FILTER_MSG_USER_CONTEXT2		= (1<<6),		/**< Match UserContext2 */
		KFPC_FILTER_MSG_DSTAPPID			= (1<<7),		/**< Match destination id */

		KFPC_FILTER_ALL						= 0xffffffff,	/**< All positive criteria must match */

		KFPC_FILTER_NOT_MSG_SRCAPPID		= (1<<8),		/**< Does not match Adapter Handle */
		KFPC_FILTER_NOT_MSG_TYPE			= (1<<9),		/**< Does not match MsgType (Bitwise ORed) */
		KFPC_FILTER_NOT_MSG_ID				= (1<<10),		/**< Does not match MsgId */
		KFPC_FILTER_NOT_MSG_GROUP			= (1<<11),		/**< Does not match MsgGroup */
		KFPC_FILTER_NOT_MSG_SERIAL_NUMBER	= (1<<12),		/**< Does not match message's serial number (implicit filtering) */
		KFPC_FILTER_NOT_MSG_USER_CONTEXT1	= (1<<13),		/**< Does not match UserContext1 */
		KFPC_FILTER_NOT_MSG_USER_CONTEXT2	= (1<<14),		/**< Does not match UserContext2 */
		KFPC_FILTER_NOT_MSG_DSTAPPID		= (1<<15),

		KFPC_FILTER_NEGATIVE				= (1<<30)		/* When a filter parameter with this flag set matches an incoming message
																it prevents that message to match the filter */

	} KFPC_FILTER, *PKFPC_FILTER;



	/**
	 *	当一个应用有多个SOCKET连接时，可通下以下发送策略选择SOCKET
	 */
	typedef enum KFPC_SendPolicy
	{
		KFPC_SP_FirstSocket = 1, // 第一个SOCKET
		KFPC_SP_Broadcast =2 // 广播
	}KFPC_SendPolicy;

	/**
	 * 过滤器参数
	 */
	typedef struct KFPC_FILTER_PARAMS 
	{ 
		/*@{*/
		unsigned int        FilterMask; 
		unsigned int		un32MsgId;							/**< Must be kept first */
		unsigned int		un32MsgType;						/**< Message type */
		unsigned int		un32Length;						/**< The total length of the message,不包括消息头 */
		unsigned int		un32SerialNumber;				/**< This buffer's unique serial number */
		unsigned int		un32UserContext1;				/**< User Ctx #1 (filterable) 用户上下文1*/
		unsigned int		un32UserContext2;				/**< User Ctx #2 (filterable) 用户上下文2*/
		unsigned int		un32SrcAPPId;						/**< Unique application identifier 应APP ID*/
		unsigned int		un32DstAPPId;						/**< Unique application identifier 应APP ID*/

		/*@}*/
	} KFPC_FILTER_PARAMS, *PKFPC_FILTER_PARAMS; 


	/**
	 *	通信库统计数据
	 */
	typedef struct KFPC_ComLibStatistics
	{
		unsigned int	AppCount;			/**< App数量 */
		unsigned int	MemAllocCount;		/**< 内存分配数 */
		unsigned int	MsgAllocCount;		/**< 消息分配数 */
		unsigned int	CreateAcceptObjCount;		/**< Accept对象创建数量 */
		unsigned int	CreateClientObjCount;		/**< Client对象创建数量 */
		unsigned int	CreateConnectObjCount;	/**< Connect对象创建数量 */
		unsigned int	TcpSocketCount;		/**< 系统总TcpSocket对象数量 */
		unsigned int	CreateFilterCount;	/**< 过滤器创建数量 */
		unsigned int	SocketHandleCount;		/**< Socket句柄数 */
		unsigned int	MsgMemSN;			/**< 消息内存分配次数 */
	}KFPC_ComLibStatistics;

/************************************************************************/
/* 消息接口定义                                                         */
/************************************************************************/

	/**
	 *	远程应用上线
	 */
	typedef struct KFPC_EVT_API_REMOTE_APP_ONLINE
	{
		KFPC_MSG_HEADER			Header;				/**< 消息头 */
		KFPC_AppInfo			AppInfo;		
	}KFPC_EVT_API_REMOTE_APP_ONLINE;

	/**
	 *	远程应用下线
	 */
	typedef struct KFPC_EVT_API_REMOTE_APP_OFFLINE
	{
		KFPC_MSG_HEADER			Header;				/**< 消息头 */
		KFPC_AppInfo			AppInfo;
	}KFPC_EVT_API_REMOTE_APP_OFFLINE;

	/**
	 *	本地连接返回
	 */
	typedef struct KFPC_EVT_API_LOCAL_CONNECTED
	{
		KFPC_MSG_HEADER			Header;				/**< 消息头 */
		unsigned int			Result;				/**< 结果 */
		unsigned int			RemoteAppID;		/**< 远程APPID，这主要是为了自动获得ID用 */
		unsigned int			LocalAppID;			/**< 当本地ID为自动获取时，连接到服务时，会被分配 */
		unsigned int			ConnectCount;		/**< 连接次数，如果次数为1说明是第一次，其它为断开重连接 */
		unsigned int			SocketSN;			/**< SocketSN */
		KFPC_AppInfo			AppInfo;
	}KFPC_EVT_API_LOCAL_CONNECTED;

	/**
	 *	远程客户端连接上来
	 */
	typedef struct KFPC_EVT_API_REMOTE_CONNECTED
	{
		KFPC_MSG_HEADER			Header;				/**< 消息头 */
		KFPC_AppInfo			AppInfo;
		unsigned int			SocketSN;			/**< SocketSN */
	}KFPC_EVT_API_REMOTE_CONNECTED;

	/**
	 *	应用断开连接包括本地连接和远程连接
	 */
	typedef struct KFPC_EVT_API_APP_DISCONNECT
	{
		KFPC_MSG_HEADER			Header;				/**< 消息头 */
		unsigned int			LocalConnect;		/**< 1为本地连接，0为远程连接 */
		unsigned int			DiscountCount;		/**< 如果是本地连接，这个参数说明断开连接次数，因为本地连接具有自动连接功能 */
		unsigned int			SocketSN;			/**< SocketSN */
		unsigned int			AppType;			/**< 应用类型*/
		unsigned int			AppGroupID;			/**< 应用所属组,如果为0不属于任何组*/ 
	}KFPC_EVT_API_APP_DISCONNECT;



	/**
	 *	AppID冲突事件,
	 */
	typedef struct KFPC_EVT_APPID_CONFLICTED
	{
		KFPC_MSG_HEADER			Header;				/**< 消息头 */
		unsigned int			ConflictFlag;		/**< 冲突属性, 1- 冲突*/
		char PeerIP[KFPC_MAX_IP_LEN];
	}KFPC_EVT_APPID_CONFLICTED;


	/**
	 *	本地冗余状态改变,比如由原来的从-->主
	 */
	typedef struct KFPC_EVT_LOCAL_REDUNDANCE_STATUS_CHANGE
	{
		KFPC_MSG_HEADER			Header;				/**< 消息头 */
		unsigned int			MasterFlag;			/**< 主从属性*/
	}KFPC_EVT_LOCAL_REDUNDANCE_STATUS_CHANGE;

	/**
	 *	远端应用的主从变化
	 */
	typedef struct KFPC_EVT_API_REMOTE_APP_REDUNDANCE_STATUS_CHANGE
	{
		KFPC_MSG_HEADER			Header;				/**< 消息头 */
		unsigned int			RemoteAppID;		/**< 远程APPID */
		unsigned int			MasterFlag;			/**< 主从属性*/
	}KFPC_EVT_API_REMOTE_APP_REDUNDANCE_STATUS_CHANGE;

	typedef struct KFPC_REQ_API_TEST_MSG
	{
		KFPC_MSG_HEADER			Header;						/**< 消息头 */
		char					StrBuf[KFPC_MAX_MSG_BODY];	/**< 字符串内容 */
	}KFPC_REQ_API_TEST_MSG;

	typedef struct KFPC_RSP_API_TEST_MSG
	{
		KFPC_MSG_HEADER			Header;						/**< 消息头 */
		char					StrBuf[KFPC_MAX_MSG_BODY];	/**< 字符串内容 */
	}KFPC_RSP_API_TEST_MSG;


	typedef struct KFPC_API_MSG
	{
		KFPC_MSG_HEADER			Header;						/**< 消息头 */
		char					StrBuf[KFPC_MAX_MSG_BODY];	/**< 字符串内容 */
	}KFPC_API_MSG;
/*--------------------------------------------------------------------------------------------------------------------------------
 |  Function Prototypes
 *------------------------------------------------------------------------------------------------------------------------------*/
	
	/**
	 * FullName:  	KFPC_InitServerLibParam
	 * @brief 		初始化服务端库参数
	 * @param[in,out] KFPC_LIB_PARAMS * LibParam
	 * @return   	KFPC_COM_API	int
	 */
	KFPC_COM_API	int KFPC_InitServerLibParam( KFPC_LIB_PARAMS* LibParam,const char* pAppName,unsigned int AppID,unsigned int AppGroupID);


	/**
	 * FullName:  	KFPC_InitClientLibParam
	 * @brief 		初始化客户端参数
	 * @param[in,out] KFPC_LIB_PARAMS * LibParam
	 * @return   	KFPC_COM_API	int
	 */
	KFPC_COM_API	int KFPC_InitClientLibParam( KFPC_LIB_PARAMS* LibParam,const char* pAppName);

	/**
	 * FullName:  	InitComLib
	 * @brief 		初始化通信库
	 * @param[in]	KFPC_KFPC_LIB_PARAMS * LibParam
	 * @return   	int 成功返回0
	 */
	KFPC_COM_API	int KFPC_InitComLib( KFPC_LIB_PARAMS* LibParam);

	KFPC_COM_API	KFPC_LIB_PARAMS* KFPC_GetLibParam();

	/**
	 * FullName:  	KFPC_GetComLibStatistics
	 * @brief 		通信库统计
	 * @param[in,out] KFPC_ComLibStatistics * pComLibStatistics
	 * @return   	int
	 */
	KFPC_COM_API	int KFPC_GetComLibStatistics(KFPC_ComLibStatistics* pComLibStatistics);

	/**
	 * FullName:  	CloseComLib
	 * @brief 		关闭通信库
	 * @return   	int 成功返回0
	 */
	KFPC_COM_API	int KFPC_CloseComLib();

	/**
	 * FullName:  	CreateMsgFilter
	 * @brief 		创建过滤器
	 * @param[in]	unsigned int FiltersCount 过滤器参数个数
	 * @param[in]	KFPC_FILTER_PARAMS FilterParams[] 过滤器参数
	 * @param[out]	unsigned int * FilterID	过滤器ID
	 * @return   	int 成功返回0
	 */
	KFPC_COM_API	int KFPC_CreateMsgFilter(KFPC_FILTER_PARAMS*	FilterParams,
						unsigned int*		FilterID  );


	/**
	 * FullName:  	KFPC_GetMsgFilterParam
	 * @brief 		返回过滤器参数
	 * @param[in]	unsigned int FilterID
	 * @param[out]	unsigned int FiltersCount
	 * @param[out]	KFPC_FILTER_PARAMS FilterParams[]
	 * @return   	int
	 */
	KFPC_COM_API	int KFPC_GetMsgFilterParam (unsigned int		FilterID,KFPC_FILTER_PARAMS*	FilterParams);



	/**
	 * FullName:  	KFPC_DestroyMsgFilter
	 * @brief 		消毁过滤器
	 * @param[in]	unsigned int FilterID	过滤器ID
	 * @return   	int
	 */
	KFPC_COM_API	int	KFPC_DestroyMsgFilter (unsigned int	FilterID);

	/**
	 * FullName:  	KFPC_WakeMsgFilter
	 * @brief 		换醒过滤器,
	 * @param[in,out] unsigned int FilterID
	 * @return   	int
	 */
	KFPC_COM_API	int KFPC_WakeMsgFilter (unsigned int	FilterID);

	/**
	 * FullName:  	KFPC_SendMsg
	 * @brief 		发送消息
	 * @param[in]	PKFPC_MSG_HEADER Msg	消息指针
	 * @param[in,out] unsigned int * FilterID	如果这个参数为NULL，就是正常异步发送，它的返回消息将在系统默认的过的滤器里。
	 *											如果这个参数不为NULL，那么发送成功后会返回一个过滤器ID，在接收函数里输入这个过滤器，接收函数将会收到唯一的返回消息用于摸拟同步。
	 *											收到消息后要消毁过滤器，通过KFPC_DestroyMsgFilter。
	 * @return   	int
	 */


	KFPC_COM_API	int KFPC_SendMsg (PKFPC_MSG_HEADER	Msg,
#ifdef __cplusplus		
		unsigned int*	FilterID = NULL
#else
		unsigned int*	FilterID
#endif
		);

	KFPC_COM_API	int KFPC_SendMsgEx (unsigned int SocketSN,PKFPC_MSG_HEADER	Msg,
#ifdef __cplusplus			
		unsigned int*	FilterID = NULL
#else
		unsigned int*	FilterID
#endif
		);


	/**
	 * FullName:  	KFPC_SendMsgToAppGroup
	 * @brief 		发送消息到应用组
	 * @param[in] unsigned int AppGroupID
	 * @param[in] PKFPC_MSG_HEADER Msg
	 * @return   	KFPC_COM_API	int
	 */
	KFPC_COM_API	int KFPC_SendMsgToAppGroup (unsigned int AppGroupID,unsigned int AppType,PKFPC_MSG_HEADER	Msg);

	/**
	 * FullName:  	KFPC_ReceiveMsg
	 * @brief 		消息接收函数
	 * @param[in,out] unsigned int FilterID	过滤器ID ID为-1为默认过滤器
	 * @param[in,out] int TimeoutMSec			超时参数,毫秒
	 * @param[in,out] KFPC_MSG_HEADER * * phMsg	消息
	 * @return   	int
	 */
	KFPC_COM_API	int	KFPC_ReceiveMsg (unsigned int		FilterID,
						int					TimeoutMSec,
						KFPC_MSG_HEADER**	pMsg);

	/**
	 * FullName:  	KFPC_WaitMsg
	 * @brief 		等待过滤器， 主要用于判断是否有消息
	 * @param[in,out] unsigned int FilterID	过滤器ID
	 * @param[in,out] int TimeoutMSec	超时参数,毫秒
	 * @param[in,out] unsigned int * MsgCount	过滤器消息个数
	 * @return   	int	成功返回0
	 *					超时返回 KFPC_RESULT_TIMEOUT
	 */
	KFPC_COM_API	int	KFPC_WaitMsg (	unsigned int		FilterID,
						int					TimeoutMSec,
						unsigned int*		MsgCount);

	/**
	 * FullName:  	KFPC_AllocMsg
	 * @brief 		分配消息
	 * @param[in,out] unsigned int MsgSize	消息大小
	 * @param[out] KFPC_MSG_HEADER * * pMsg	输出消息指针
	 * @param[in] unsigned int MsgID		消息ID
	 * @param[in] KFPC_MSG_TYPE MsgType		消息类型
	 * @param[in] unsigned int DstAppID		目标应用ID
	 * @param[in] unsigned int SrcAPPId		源应用ID
	 * @param[in] unsigned int UserContext1	用户上下文1
	 * @param[in] unsigned int UserContext2	用户上下文2
	 * @param[in] unsigned int SN			消息序号
	 * @return   	KFPC_COM_API	int
	 */
	KFPC_COM_API	int KFPC_AllocMsg ( unsigned int MsgSize,  
		KFPC_MSG_HEADER** pMsg,
		unsigned int MsgID,
		KFPC_MSG_TYPE	MsgType,
		unsigned int DstAppID,
		unsigned int SrcAPPId,
		unsigned int UserContext1,
		unsigned int UserContext2,

#ifdef __cplusplus	
		unsigned int SN = 0
#else
		unsigned int SN
#endif

		);

	/**
	 * FullName:  	KFPC_ReleaseMsg
	 * @brief 		回收消息
	 * @param[in,out] KFPC_MSG_HEADER * pMsg
	 * @return   	int
	 */
	KFPC_COM_API	int	KFPC_ReleaseMsg (KFPC_MSG_HEADER*	pMsg);

	/**
	 * FullName:  	KFPC_GetErrorString
	 * @brief 		返回错误字符串
	 * @param[in]	unsigned int Result
	 * @return   	const char*
	 */
	KFPC_COM_API	const char* KFPC_GetErrorString (unsigned int	Result);

	/**
	 * FullName:  	KFPC_GetAPPList
	 * @brief 		获得当前应用列表
	 * @param[in,out] unsigned int * AppCount	输入最大APPIDs的大小，输出有效APPID个数
	 * @param[out] unsigned int APPIDs[]	并将应用ID填入数组
	 * @return   	int
	 */
	KFPC_COM_API	int	KFPC_GetAPPList (unsigned int*	AppCount,
						unsigned int	APPIDs[]);

	/**
	 * FullName:  	KFPC_GetAppInfo
	 * @brief 		根据ID获得APP信息
	 * @param[in,out] unsigned int APPID
	 * @param[in,out] PKFPC_AppInfo pAppInfo
	 * @return   	int
	 */
	KFPC_COM_API	int KFPC_GetAppInfo (	unsigned int	APPID,
							PKFPC_AppInfo	pAppInfo);


	/**
	 * FullName:  	KFPC_Connect
	 * @brief 		打开远程连接
	 * @param[in]	const char * Ip		远程IP
	 * @param[in]	unsigned short Port	远程端口
	 * @param[in]	const char* pConnectPasswd 连接密码
	 * @param[in]	unsigned int UserContext1 用户上下文1
	 * @param[in]	unsigned int UserContext2
	 * @param[in]	bool SYNC	是否同步，如果同步函数返回时便知连接成功与否，如果是异步就等待远程连接事件
	 * @return  	int
	 */


	KFPC_COM_API	int KFPC_Connect(const char* Ip,
		unsigned short Port,
		const char* pConnectPasswd,
		unsigned int UserContext1,
		unsigned int UserContext2,
		unsigned int* SocketSN,
		
#ifdef __cplusplus	
		bool			AutoReConnect,
		bool			SYNC= false,
		unsigned int	TimeOut = 0,
		unsigned int	ConIndex = 0
#else
		int				AutoReConnect,
		int				SYNC,			/*= false*/
		unsigned int	TimeOut,		/*= 0*/
		unsigned int	ConIndex		/*= 0*/
#endif

		);

	/**
	 * FullName:  	KFPC_CloseAPP
	 * @brief 		关闭APP
	 * @param[in]	unsigned int APPID
	 * @return   	int
	 */
	KFPC_COM_API	int KFPC_CloseAPP(unsigned int APPID);
	

	/**
	 * FullName:  	KFPC_CloseSocket
	 * @brief 		关闭单个SocketID
	 * @param[in]	Socket_t SocketID
	 * @return   	KFPC_COM_API	int
	 */
	KFPC_COM_API	int KFPC_CloseSocket( int SocketID );

	KFPC_COM_API	int KFPC_CheckAppID (	unsigned int	APPID);
	KFPC_COM_API	int KFPC_DupMsg(KFPC_MSG_HEADER* pSrcMsg,KFPC_MSG_HEADER** pNewMsg );

#endif // kfpc_api_h__
