#ifndef KFPC_ContactCenterPublicDef_h__
#define KFPC_ContactCenterPublicDef_h__

#include "list"
#include <time.h>

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Defines
 *------------------------------------------------------------------------------------------------------------------------------*/

#define KFPC_MAX_FILE_NAME							256			/**< 最大文件名长度 */
#define KFPC_MAX_VERSION_STR_SIZE					64			/**< 版本字符串长度 */
#define KFPC_MAX_NUMBER_SIZE						64			/**< 最大号码长度 */
#define KFPC_MAX_DTMF_SIZE							64			/**< 最大DTMF码长度 */
#define KFPC_TRUNKGROUP_NAME_LEN					64			/**< 中继组名长度 */
#define KFPC_TRUNKGROUP_DESC_LEN					256			/**< 中继组描述 */
#define KFPC_MAX_CHANNEL							32			/**< 单个中继最大的通道数 */
#define KFPC_MAX_PLAY_CONTENT						1024		/**< 最大单个播放文件内容 */
#define KFPC_MAX_CHARSET_TRANS_BUFF_LEN				1024		/**< 字符集转换中间缓冲长度 */
#define KFPC_MAX_ALARM_CONTENT						1024		/**< 最大的告警内容 */
#define KFPC_USER_NAME_LEN							64			/**< 用户名密码 */
#define KFPC_PASSWD_LEN								64			/**< 密码长度 */
#define KFPC_SIGNAL_TYPE_NAME_LEN					16			/**< 信令类型名长度 */
#define KFPC_MAX_SQL_STR							64000		/**< 最大SQL语句长度 */
#define KFPC_MAX_FAX_INFO							64          /**< 最大传真信息长度*/
#define KFPC_MAX_SMS_MSG_LEN						255			/**< 最大短信信息长度*/
#define KFPC_FAX_IP_LEN								64			/**< 最大IP地址长度*/
#define KFPC_MAX_PLAY_FILE_COUNT					128			/**< 最大放音文件个数 */
const unsigned int KFPC_START_TIME				= 1344787200;	/**< KFPC 开始时间2012-8-13 */
#define KFPC_MAX_TIME_STR							20			/**< 最大时间字符串 */
#define KPFC_MAX_WEEKDAY							7			/**< 一周7天 */
#define KFPC_MAX_CALLED_LIST_STR					10240		
#define KFPC_MAX_WORKNO_LIST_STR					10240
#define KFPC_MAX_LOG_STR							10240
#define KFPC_INVALID_AGENTID						(0)		/**< 无效AGENTID */
#define KFPC_INVALID_VDNID							(-1)		/**< 无效VDNID */
/**
 * 收号模式 1为固定收号个数，2为终止符，0xf为不定长收号
 */
#define KFPC_DTMF_MODE_FixedDigits					1			/**< 收固定个数号码 */
#define KFPC_DTMF_MODE_UseTermgChar					2			/**< 使用终止符结束收号 */
#define KFPC_DTMF_MODE_IndefiniteFixedDigits		0xf			/**< 不定长收号 */	

#define KFPC_MAX_CallOutQueueCount					512		/**< 最大呼出队列长度 */

#define KFPC_DEFAULT_ROUTER0						"****"		/**< 默认路由 */
#define KFPC_DEFAULT_ROUTER1						"*****"		/**< 默认路由 */
#define KFPC_DEFAULT_ROUTER2						"******"	/**< 默认路由 */
#define KFPC_DEFAULT_ROUTER_LEN						5

#define WAIT_CALL_RELEASE_TIME						7200		/**< 系统最大通话时间限制 */
#define MAX_PRIVATEINFO_LEN							1024

#define MAX_SIP_BODY								1024
#define CONF_NAME									128
#define MSML_MAX_CONF								128
#define CREATE_CONF_TIMER							60
#define MAX_RECORD_COUNT							10000
#define MAX_CMD_LIVE_TIME							600
#define KFPC_MAX_REGEX_STR								512			/**< 最大正则字符串长 */
#define KFPC_MAX_ROUTERCOUNT						6
/*--------------------------------------------------------------------------------------------------------------------------------
 |  Types
 *------------------------------------------------------------------------------------------------------------------------------*/

/**
 *	状态											描述									备注
 */
typedef enum KFPC_Ch_Status
{
	KFPC_CH_Status_Unready					= 0x00,				/**<	未就绪	程序初始化 */
	KFPC_CH_Status_CallOffer				= 0x01,				/**< 	呼入初始化状态 */	
	KFPC_CH_Status_CallOut					= 0x02,				/**< 	呼出初始化状态 */	
	KFPC_CH_Status_Accept					= 0x04,				/**< 	呼入响铃状态 */	
	KFPC_CH_Status_Alerting					= 0x08,				/**<  	呼出响铃状态 */	
	KFPC_CH_Status_Connect					= 0x10,				/**< 	应答连接状态 */	
	KFPC_CH_Status_Release					= 0x20,				/**< 	释放状态 */	
	KFPC_CH_Status_Failed					= 0x40,				/**< 	故障状态						模拟外线检测不到拔号音 */
	KFPC_CH_Status_OutofService				= 0x80,				/**< 	服务失效						数字中继为物理连路通的信令不通 */
	KFPC_CH_Status_LocalBlock				= 0x100,			/**< 	本地闭塞状态 */	
	KFPC_CH_Status_Idle						= 0x200,			/**< 	空闭状态 */	
	KFPC_CH_Status_RemoteBlock				= 0x400,			/**< 	远端闭塞 */	
	KFPC_CH_Status_HardwareFailureBlock		= 0x800,			/**< 	硬件故障闭塞 */	
	KFPC_CH_Status_OffHook					= 0x1000,			/**< 	摘机主要是针对模拟线	 */
	KFPC_CH_Status_OnHook					= 0x2000,			/**< 	挂机主要是针对模拟线	 */
	KFPC_CH_Status_WaitMoreInfo				= 0x4000,			/**< 	等待后继信息	 */
}KFPC_Ch_Status;


typedef enum KFPC_Ch_Status_Inx
{
	KFPC_CH_Status_Inx_Unready					,				/**<	未就绪	程序初始化 */
	KFPC_CH_Status_Inx_CallOffer				,				/**< 	呼入初始化状态 */	
	KFPC_CH_Status_Inx_CallOut					,				/**< 	呼出初始化状态 */	
	KFPC_CH_Status_Inx_Accept					,				/**< 	呼入响铃状态 */	
	KFPC_CH_Status_Inx_Alerting					,				/**<  	呼出响铃状态 */	
	KFPC_CH_Status_Inx_Connect					,				/**< 	应答连接状态 */	
	KFPC_CH_Status_Inx_Release					,				/**< 	释放状态 */	
	KFPC_CH_Status_Inx_Failed					,				/**< 	故障状态						模拟外线检测不到拔号音 */
	KFPC_CH_Status_Inx_OutofService				,				/**< 	服务失效						数字中继为物理连路通的信令不通 */
	KFPC_CH_Status_Inx_LocalBlock				,			/**< 	本地闭塞状态 */	
	KFPC_CH_Status_Inx_Idle						,			/**< 	空闭状态 */	
	KFPC_CH_Status_Inx_RemoteBlock				,			/**< 	远端闭塞 */	
	KFPC_CH_Status_Inx_HardwareFailureBlock		,			/**< 	硬件故障闭塞 */	
	KFPC_CH_Status_Inx_OffHook					,			/**< 	摘机主要是针对模拟线	 */
	KFPC_CH_Status_Inx_OnHook					,			/**< 	挂机主要是针对模拟线	 */
	KFPC_CH_Status_Inx_WaitMoreInfo				,			/**< 	等待后继信息	 */
}KFPC_Ch_Status_Inx;

#define KFPC_IDLE_STATUS	(KFPC_CH_Status_Idle |	KFPC_CH_Status_OnHook)	/**< 通道空闲状态 */
#define KFPC_CALL_LIVE		(KFPC_CH_Status_CallOffer | KFPC_CH_Status_CallOut | KFPC_CH_Status_Accept | KFPC_CH_Status_Alerting | KFPC_CH_Status_Connect | KFPC_CH_Status_OffHook | KFPC_CH_Status_WaitMoreInfo)	/**< 呼叫是活的状态 */
#define KFPC_CALL_RING		(KFPC_CH_Status_Accept | KFPC_CH_Status_CallOffer)		/**< 等待摘机 */

#define MAX_STATUS_COUNT		32	

unsigned int GetExp(unsigned int Val);

typedef enum KFPC_SignalType
{
	KFPC_SignalType_R2_CHINA,					/**< R2 */
	KFPC_SignalType_R2_BASEIC,			/**< R2 */
	KFPC_SignalType_ISDN_N,				/**< ISDN */
	KFPC_SignalType_ISDN_U,				/**< ISDN */
	KFPC_SignalType_SS7_TUP,				/**< SS7 */
	KFPC_SignalType_SS7_ISUP,				/**< SS7 */
	KFPC_SignalType_ClearChannel,		/**< 透明通道 */
	KFPC_SignalType_FXS,				/**< 内线 */
	KFPC_SignalType_SIP,				/**< SIP */
	KFPC_SignalType_FXO,				/**< 外线 */
	KFPC_SignalType_END
}KFPC_SignalType;

KFPC_SignalType IntToSignalType(unsigned int val);

typedef struct SignalType_Info
{
	KFPC_SignalType	SignalType;
	char			SignalTypeName[KFPC_SIGNAL_TYPE_NAME_LEN];
}SignalType_Info;

const SignalType_Info	SignalType_List[]={
	{KFPC_SignalType_R2_CHINA,	"R2_CHINA"},					/**< R2 */
	{KFPC_SignalType_R2_BASEIC,	"R2_BASEIC"},					/**< R2 */
	{KFPC_SignalType_ISDN_N,	"ISDN_N"},						/**< ISDN */
	{KFPC_SignalType_ISDN_U,	"ISDN_U"},						/**< ISDN */
	{KFPC_SignalType_SS7_TUP,	"SS7_TUP"},						/**< SS7 */
	{KFPC_SignalType_SS7_ISUP,	"SS7_ISUP"},					/**< SS7 */
	{KFPC_SignalType_ClearChannel,	"ClearChannel"},			/**< 透明通道 */
	{KFPC_SignalType_FXS,		"FXS"},							/**< 内线 */
	{KFPC_SignalType_SIP,		"SIP"},							/**< SIP */
	{KFPC_SignalType_FXO,		"FXO"}							/**< 外线 */
};




/**
 * @enum KFPC_TS_ID_ConferenceJoinMode
 * @brief 会议模式
 */
typedef enum KFPC_JoinConfMode
{
	KFPC_CJM_ListenAndSpeak	= 0,		/**< 即听又说	*/
	KFPC_CJM_ListenOnly	=	1			/**< 只听		*/
}KFPC_JoinConfMode;

typedef enum KFPC_DEVICE_TYPE
{
	DEVICE_TYPE_TRUNKGROUP = 0,			/**< 中继组 */
	DEVICE_TYPE_CHANNEL	= 1,			/**< 中继 */
	DEVICE_TYPE_ADDRESS = 2				/**< 号码 */
}KFPC_DEVICE_TYPE;



/**
 *	设备信息结构
 */
typedef struct	KFPC_DEVICE
{	
	unsigned int		Type;	
	unsigned short		Span;
	unsigned char		TimeSlot;
	char				TrunkGroup[KFPC_TRUNKGROUP_NAME_LEN];
	char				CallerNO[KFPC_MAX_NUMBER_SIZE];			/**< 主叫号码									*/
	char				CalledNO[KFPC_MAX_NUMBER_SIZE];			/**< 被叫号码									*/	
	char				RedirectingNum[KFPC_MAX_NUMBER_SIZE];		/**< 重定向号码									*/
	char				OriginalCalled[KFPC_MAX_NUMBER_SIZE];		/**< 重定向号码									*/

}KFPC_DEVICE;

/**
 *	收号参数
 */
typedef struct KFPC_DTMFParam
{
	unsigned int		MODE;									/**< 收号模式 1为固定收号个数，2为终止符，0xf为不定长收号 */
	unsigned int		MaxDigits;								/**< 收号长度 */
	unsigned int		TermgChar;								/**< 终止符	*/
	unsigned int		FirstDigitInform;						/**< 收到第一个号是否通知 */
	unsigned int		VoiceStopFlag;							/**< 收到号是否继续放音,0为停止放音，1为继续放音	*/
	unsigned int		FirstDigitTimer;						/**< 以秒为单位(发送命后与按下第一个按键的最大时间间隔)	*/
	unsigned int		InterDigitermer;						/**< 以秒为单位(两次按键的最大时间间隔)	(当收到第一个按键后才启动该定时间)					*/
	unsigned int		CompletionTimer;						/**< 以秒为单位(收到第一个按键与最后一个按键的时间长度)	(当收到第一个按键后才启动该定时间)	*/
}KFPC_DTMFParam;

typedef union KFPC_CallID
{
	unsigned long long	CallID;
	struct 
	{
		
		unsigned short	ChID;									/**< 通道ID */
		unsigned short	AppID;									/**< 应用ID */		
		unsigned int	Time;									/**< 初始时间 */
	}CallIDInfo;
}KFPC_CallID;

typedef union KFPC_LoginSN
{
	unsigned long long	LoginSN;
	struct 
	{		
		unsigned int	SN;
		unsigned int	AppID;									/**< 应用ID */		
		
	}LoginSNInfo;
}KFPC_LoginSN;

typedef union KFPC_SessionID
{
	unsigned long long	SessionID;
	struct 
	{
		
		unsigned short	ChID1;									/**< 通道ID */
		unsigned short	ChID2;									/**< 通道ID */		
		unsigned int	Time;									/**< 初始时间 */
	}SessionIDInfo;
}KFPC_SessionID;


typedef enum KFPC_VoicePlayType_t
{
	IVR_PLAY_TYPE_FILE = 0,			/**< 播放文件 */
	IVR_PLAY_TYPE_TEXT = 1,			/**< 播放文本 */
}KFPC_VoicePlayType;

typedef struct KFPC_VoiceItem_t
{
	KFPC_VoicePlayType PlayType;
	char BeforeTranContent[KFPC_MAX_PLAY_CONTENT];
}KFPC_VoiceItem;

typedef std::list<KFPC_VoiceItem> VoiceItemList_t;
typedef VoiceItemList_t::iterator VoiceItemListIter_t;	
/*--------------------------------------------------------------------------------------------------------------------------------
 |  Function Prototypes
 *------------------------------------------------------------------------------------------------------------------------------*/
const char* ChStatusToStr(int ID);
const char* SignalTypeToStr(int SignalType);
unsigned short CallIDToChannel(unsigned long long& CallID);
#define ChannelToSpan(x)					((unsigned short)(x/KFPC_MAX_CHANNEL))			/**< 逻辑通道号到中继号 */
#define ChannelToTimeSlot(x)					((unsigned char)(x%KFPC_MAX_CHANNEL))				/**< 逻辑通道号到通道号 */
#define SpanTimeSlotToChannel(Span,TimeSlot)	(Span*KFPC_MAX_CHANNEL+TimeSlot)

const char* MsgIDToStr(unsigned int MsgID,char* MsgIDStr);
unsigned int ParsePlayContent(VoiceItemList_t &VoiceItemList,char *pPlayContent);

//#define KFPC_RESULT_MSG_GET_TYPE(__nResultMsg__)	(unsigned int)(((unsigned int)(__nResultMsg__) & 0xFF000000) >> 28)
#define KFPC_RESULT_MSG_GET_TYPE(__nResultMsg__)	((((unsigned int)(__nResultMsg__) & 0xFF000000) >> 28) & 0x0000FFFF)

#define KFPC_CHANNEL_UNIQUEID(APPID,CHANNELID)	((APPID<<16) + CHANNELID)
#define KFPC_VOIP_UNIQUEID(APPID,NODE,CHANNELID)	((APPID<<16) + NODE*MAX_XIOPCH+CHANNELID)
#define KFPC_IVR_UNIQUEID(APPID,NODE,CHANNELID)	((APPID<<16) + NODE*MAX_IVR_CH+CHANNELID)


const char* GetErrorStr(unsigned int ErrorCode,unsigned int Lang = 0);

const char* GetCauseStr(unsigned int Cause,unsigned int Lang = 0);
const char* GetSIPCauseDes(unsigned int Cause,bool IsChinese);
const char* GetQ850CauseDes(unsigned int Cause,bool IsChinese);

#define 	UINT32ToHShort(x)	(unsigned short)((x&0xffff0000) >> 16)
#define 	UINT32ToLShort(x)	(unsigned short)(x&0x0000ffff)
#define		MIN(a,b)	((a<b) ? a:b )
#define		MAX(a,b)	((a>b) ? a:b )
/**< 呼叫类型 */
typedef	enum KFPC_CALL_FLAG
{	
	CALL_FLAG_OUT,					/**< 呼出 */
	CALL_FLAG_IN,					/**< 呼入 */
	CALL_FLAG_CONF					/**< 会议 */
}KFPC_CALL_FLAG;

const char* CallFlag2Str(KFPC_CALL_FLAG	ct);

typedef	enum KFPC_CALL_TYPE
{	
	CALL_TYPE_ONEPART,					/**< One part */
	CALL_TYPE_TWOPART,					/**< two part */
	CALL_TYPE_CONFRENCE,                 /**< Conference */
	CALL_TYPE_END
}KFPC_CALL_TYPE;

static const char* CallTypeToStr(unsigned int val)
{
	switch(val)
	{
		case CALL_TYPE_ONEPART:    return "OnePartCall";
		case CALL_TYPE_TWOPART:    return "TwoPartCall" ;
		case CALL_TYPE_CONFRENCE:  return "ConferenceCall";
		default:                       return "unknown";
	}
}

typedef enum KFPC_EXT_NUM_TYPE
{
	EXT_NUM_ALL_TRANSNUM,
	EXT_NUM_BUSY_TRANSNUM,
	EXT_NUM_NOANSWER_TRANSNUM,	
	EXT_NUM_OUTSIDE_LINE
}KFPC_EXT_NUM_TYPE;

static const char* ExtNumTypeToStr(unsigned int val)
{
	switch(val)
	{
	case EXT_NUM_ALL_TRANSNUM:    return "EXT_NUM_ALL_TRANSNUM";
	case EXT_NUM_BUSY_TRANSNUM:    return "EXT_NUM_BUSY_TRANSNUM" ;
	case EXT_NUM_NOANSWER_TRANSNUM:  return "EXT_NUM_NOANSWER_TRANSNUM";
	case EXT_NUM_OUTSIDE_LINE:		return "EXT_NUM_OUTSIDE_LINE";
	default:                       return "unknown";
	}
}

typedef enum KFPC_LANG_TYPE
{
	LANG_TYPE_CN = 1,
	LANG_TYPE_EN = 2
}KFPC_LANG_TYPE;

/**< 呼出类型 */
typedef	enum KFPC_CALLOUT_TYPE
{	
	CALLOUT_TYPE_AGENTCALL,					/**< 座席手动外呼 */
	CALLOUT_TYPE_AGENTCONFIRMCALL,			/**< 座席确认外呼 */
	CALLOUT_TYPE_AUTOCALL,					/**< 系统自动外呼 */
	CALLOUT_TYPE_TESTCALL,					/**< 系统试呼 */
}KFPC_CALLOUT_TYPE;

/**< 呼出状态 */
typedef	enum KFPC_CALLOUT_STATUS
{	
	CALLOUT_STATUS_READY,				/**< 未呼叫 */
	CALLOUT_STATUS_CALLING,				/**< 正在呼叫 */
	CALLOUT_STATUS_SUCCESS,				/**< 呼叫成功 */
	CALLOUT_STATUS_FAILED,				/**< 呼叫失败 */
	CALLOUT_STATUS_PAUSE				/**< 呼叫暂停 */
}KFPC_CALLOUT_STATUS;


/**< 呼出转接类型 */
typedef	enum KFPC_CALLOUT_TRANSFER_TYPE
{	
	CALLOUT_TRANSFER_TYPE_AGENT,		/**< 座席 */
	CALLOUT_TRANSFER_TYPE_IVR,			/**< IVR */
	CALLOUT_TRANSFER_TYPE_QUEUE,		/**< 排队 */

}KFPC_CALLOUT_TRANSFER_TYPE;



typedef enum KFPC_SYS_OBJ_TYPE
{
	OBJ_TYPE_VDN,
	OBJ_TYPE_ACD_SPLIT,
	OBJ_TYPE_ACD_AGENT,
	OBJ_TYPE_ACD_EXTNUM
}KFPC_SYS_OBJ_TYPE;

typedef	enum KFPC_VDN_STATUS
{
	AGENT_VDN_STATUS_NORMAL = 0,				//正常状态
	AGENT_VDN_STATUS_INSUFFICIENTBALANCE = 1,	//余额不足
	AGENT_VDN_STATUS_LOCKED = 2,				//欠费上锁
	AGENT_VDN_STATUS_MANUAL_LOCKED = 3,			//手动上锁
	AGENT_VDN_STATUS_STOP = 8,					//停用
}KFPC_VDN_STATUS;

typedef struct TS_RedirectingAttr
{
	unsigned char	NOA;//Nature of address indicator
	unsigned char	NumPlanInd;//Numbering plan Ind
	unsigned char	PresentInd;//Present.Ind
	unsigned char	Original_redirection_reasons;	//0为不知道原因，1为用户忙,２为无应答，3为无条件
	unsigned char   Redirecting_reason;				//0为不知道原因，1为用户忙,２为无应答，3为无条件,4，５，６用户不可到达
}TS_RedirectingAttr;	

typedef struct TS_CallingNumAttr
{
	unsigned char	NOA;//Nature of address indicator
	unsigned char	INNInd;	//
	unsigned char	NumPlanInd;//Numbering plan Ind
	unsigned char	PresentInd;//Present.Ind
	unsigned char	Screening;//Screening
}TS_CallingNumAttr;

typedef	enum KFPC_CHANNEL_RELMODE
{
	CHANNEL_RELMODE_REL = 0,				//释放
	CHANNEL_RELMODE_PARK = 1				//保持
}KFPC_CHANNEL_RELMODE;

typedef enum MSML_DeleteWhen
{
	MSML_DelMode_NoMedia,
	MSML_DelMode_NoControl,
	MSML_DelMode_Never
}MSML_DeleteWhen;

//等待类型1为排队，2为响铃，3为保持
typedef enum CallWaitType_t
{
	CWT_NULL,
	CWT_QUEUE,	
	CWT_RING,
	CWT_HOLD,
	CWT_ROUTEING
}CallWaitType_t;


typedef enum ConfType_t
{
	ConfType_NULL,
	ConfType_Monitor,
	ConfType_ForceInsert,
	ConfType_MultiParty
}ConfType_t;

const char* CallWaitTypeToStr(CallWaitType_t cwt);
#define RingBackMusic	"ringback.wav"
#define DefaultAgentAnswerTimeOut	60
#define DefaultAppDisconnectTimeOut 60
time_t GetCallID_TIME(unsigned long long CallID);
#define MAX_RECALL_TIMES	0
#define MAX_RECALL_TIMEOUT	3
#define MAX_LOGIN_TIMEOUT	60

typedef enum EXT_TYPE_t
{
	EXT_TYPE_NULL,
	EXT_TYPE_GENERAL,
	EXT_TYPE_VIRTUAL	//虚拟分机
	
}EXT_TYPE_t;

const char* ExtTypeToStr(EXT_TYPE_t et);
EXT_TYPE_t	IntToExtType(unsigned int val);

enum KFPC_DB_OPERATE_TYPE
{
	KFPC_Operate_Initialize,
	KFPC_Operate_Insert,
	KFPC_Operate_Update,
	KFPC_Operate_Delete
};

const char* OperateTypeToStr(KFPC_DB_OPERATE_TYPE t);

typedef enum KFPC_QUEUE_END_CAUSE_t
{
	KFPC_EQT_CallReleased,
	KFPC_EQT_CallTimeOut,
	KFPC_EQT_CallOverLen,
	KFPC_EQT_CallAlloced,
	KFPC_EQT_CallManual
}KFPC_QUEUE_END_CAUSE_t;

typedef enum KFPC_ExtNumCallOutFail_t
{
	KFPC_ExtNum_Null,
	KFPC_ExtNum_Busy,
	KFPC_ExtNum_CallReleased,
	KFPC_ExtNum_NoAnswer
}KFPC_ExtNumCallOutFail_t;


#endif // KFPC_ContactCenterPublicDef_h__