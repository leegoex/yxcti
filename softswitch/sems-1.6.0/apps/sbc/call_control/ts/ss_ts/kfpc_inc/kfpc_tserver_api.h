#ifndef kfpc_tserver_api_h__
#define kfpc_tserver_api_h__

/************************************************************************

功能：TAPI的定义
作者：Feng yanfa
日期：2012-11-20
说明：
TSAPI的定义.

************************************************************************/

#include "kfpc_id.h"
#include "kfpc_msg.h"
#include "KFPC_ContactCenterPublicDef.h"

/**
 * @def KFPC_TS_INTERFACEVERSION "1.0.0.0"
 * @brief 当前接口版本
 */

#define KFPC_TS_INTERFACEVERSION					"1.0.0.0"

/**
 * @ KFPC_TS_ID
 * @brief TS_ID定义
 */

#define	KFPC_MSG_ID_TS_GetTSVersion						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x01)		/**< 获取TS版本号 */
#define	KFPC_MSG_ID_TS_AcceptCall						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x02)		/**< 接受呼叫(用于呼入) */
#define	KFPC_MSG_ID_TS_AnswerCall						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x03)		/**< 应答呼叫(用于呼入) */
#define	KFPC_MSG_ID_TS_ReleaseCall						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x04)		/**< 释放呼叫(包括主、被叫) */
#define	KFPC_MSG_ID_TS_CallOut							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x05)		/**< 外呼 */
#define	KFPC_MSG_ID_TS_EVT_IncomingCall					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x06)		/**< 呼叫入线 */
#define	KFPC_MSG_ID_TS_EVT_AlertCall					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x07)		/**< 呼出对方响铃，这个事件在叠代收发送被叫号时起用。 */
#define	KFPC_MSG_ID_TS_EVT_AnsweredCall					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x08)		/**< 呼出后对方应答事件 */
#define	KFPC_MSG_ID_TS_EVT_ReleasedCall					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x09)		/**< 呼叫释放 */
#define	KFPC_MSG_ID_TS_Connect							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x0a)		/**< 连接两个呼叫,释放与通道连接的所有资源,除非是全双工录音 */
#define	KFPC_MSG_ID_TS_Disconnect						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x0b)		/**< 断开两个通道 */
#define	KFPC_MSG_ID_TS_CreateConference					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x0c)		/**< 创建会议最少大于3方 */
#define	KFPC_MSG_ID_TS_FreeConference					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x0d)		/**< 释放会议 */
#define	KFPC_MSG_ID_TS_JoinConference					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x0e)		/**< 加入会议,分为全双工加主和半双工加入 */
#define	KFPC_MSG_ID_TS_LeaveConference					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x0f)		/**< 退出会议 */
#define	KFPC_MSG_ID_TS_ChangeConnectMode				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x10)		/**< 改变会议模式只听或听说 */
#define	KFPC_MSG_ID_TS_CollectDTMF						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x11)		/**< 收号 */
#define	KFPC_MSG_ID_TS_StopCollectDTMF					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x12)		/**< 停止收号，判断DSP资源是否空闲，如果空闲则收回DSP资源 */
#define	KFPC_MSG_ID_TS_EVT_CollectDTMFCompleted			KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x13)		/**< 收号完成后判断DSP资源是否空闲，如果空闲则收回DSP资源 */
#define	KFPC_MSG_ID_TS_PlayVoice						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x14)		/**< 放音包括放文件名、文件ID、TTS文本 */
#define	KFPC_MSG_ID_TS_StopPlayVoice					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x15)		/**< 停止放音，判断DSP资源是否空闲，如果空闲则收回DSP资源 */
#define	KFPC_MSG_ID_TS_EVT_PlayVoiceCompleted			KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x16)		/**< 放音完成事件,完后判断DSP资源是否空闲，如果空闲则收回DSP资源 */
#define	KFPC_MSG_ID_TS_RecordFile						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x17)		/**< 录音分为双工录音、单工录音。如果是双工录音那么只有停止收或者挂机才会回收DSP资源 */
#define	KFPC_MSG_ID_TS_StopRecordFile					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x18)		/**< 停止录音，判断DSP资源是否空闲，如果空闲则收回DSP资源 */
#define	KFPC_MSG_ID_TS_EVT_RecordFileCompleted			KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x19)		/**< 录音完成。判断DSP资源是否空闲，如果空闲则收回DSP资源 */
//#define	KFPC_MSG_ID_TS_ConfPlayVoice					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x1a)		/**< 会议放音包括放文件名、文件ID、TTS文本 */
//#define	KFPC_MSG_ID_TS_StopConfPlayVoice				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x1b)		/**< 停止会议放音 */
//#define	KFPC_MSG_ID_TS_EVT_ConfPlayFileCompleted		KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x1c)		/**< 会议放音完成 */
//#define	KFPC_MSG_ID_TS_ConfRecordFile					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x1d)		/**< 会议录音 */
//#define	KFPC_MSG_ID_TS_StopConfRecordFile				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x1e)		/**< 停止会议录音 */
//#define	KFPC_MSG_ID_TS_EVT_ConfRecordFileCompleted		KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x1f)		/**< 会议放音完成 */
#define	KFPC_MSG_ID_TS_SendFax							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x20)		/**< 发送传真 */
#define	KFPC_MSG_ID_TS_StopSendFax						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x21)		/**< 停止发送传真 */
#define	KFPC_MSG_ID_TS_EVT_SendFaxCompleted				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x22)		/**< 发送传真完成 */
#define	KFPC_MSG_ID_TS_RecvFax							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x23)		/**< 接收传真 */
#define	KFPC_MSG_ID_TS_StopRecvFax						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x24)		/**< 停止接收传真 */
#define	KFPC_MSG_ID_TS_EVT_RecvFaxCompleted				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x25)		/**< 收接传真完成 */
#define	KFPC_MSG_ID_TS_ReloadCfg						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x26)		/**< 重新加载配置文件，用于动态配置 */
#define	KFPC_MSG_ID_TS_QueryChStatus					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x27)		/**< 查询通道状态 */
#define KFPC_MSG_ID_TS_UpdateChStatus					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x28)		/**< 查询通道状态 */
#define	KFPC_MSG_ID_TS_SetChStatus						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x29)		/**< 改变通道状态 */
#define	KFPC_MSG_ID_TS_CoreDump							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x2a)		/**< 产生文件所有资源dump文件 */
#define	KFPC_MSG_ID_TS_EVT_Alarm						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x2b)		/**< 告警事件，比如中继告警、资源不足告警、LICENSE不足告警。把事件发送到Monitor */
#define	KFPC_MSG_ID_TS_WatchTrunkGroup					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x2c)		/**< 观察中继组呼叫 */
#define	KFPC_MSG_ID_TS_CancelWatchTrunkGroup			KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x2d)		/**< 取消观察中继组 */
#define	KFPC_MSG_ID_TS_QueryTrunkGroup					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x2e)		/**< 查询中继组 */
#define	KFPC_MSG_ID_TS_EVT_UpdateTrunkGroup				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x2f)		/**< 更新中继组 */
#define KFPC_MSG_ID_TS_MonitorChStatus					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x30)		/**< 监控通道状态 */
//#define KFPC_MSG_ID_TS_WatchNumStatus					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x31)		/**< 观察号码状态 */
#define KFPC_MSG_ID_TS_EVT_ExtNum2CCS					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x32)		/**< 号码动态路由更新 */
#define KFPC_MSG_ID_TS_RequestChannel					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x33)		/**< 请求占用通道 */
#define KFPC_MSG_ID_TS_EVT_HookFlash					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x34)		/**< 拍插事件 */
#define KFPC_MSG_ID_TS_TextToSpeech						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x35)		/**< 拍插事件 */
#define KFPC_MSG_ID_TS_PlayDTMF							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x36)
#define KFPC_MSG_ID_TS_EVT_PassAnswerCall				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x37)
#define	KFPC_MSG_ID_TS_END								KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x38)		/**< 结束ID */

#define KFPC_MAX_MSG_ID_TS								KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_END)                                           /**< 最大的TS_ID数*/  

static const char* TSMsgIDToStr(unsigned int MsgID)
{
	switch(MsgID)
	{
	case  KFPC_MSG_ID_TS_GetTSVersion						:								return "GetTSVersion";                                    
	case  KFPC_MSG_ID_TS_AcceptCall						:                 return "AcceptCall";                                      
	case  KFPC_MSG_ID_TS_AnswerCall						:                 return "AnswerCall";                                      
	case  KFPC_MSG_ID_TS_ReleaseCall						:               return "ReleaseCall";                                     
	case  KFPC_MSG_ID_TS_CallOut							:                 return "CallOut";                                         
	case  KFPC_MSG_ID_TS_EVT_IncomingCall					:             return "EVT_IncomingCall";                                
	case  KFPC_MSG_ID_TS_EVT_AlertCall					:               return "EVT_AlertCall";                                   
	case  KFPC_MSG_ID_TS_EVT_AnsweredCall					:             return "EVT_AnsweredCall";                                
	case  KFPC_MSG_ID_TS_EVT_ReleasedCall					:             return "EVT_ReleasedCall";                                
	case  KFPC_MSG_ID_TS_Connect							:                 return "Connect";                                         
	case  KFPC_MSG_ID_TS_Disconnect						:                 return "Disconnect";                                      
	case  KFPC_MSG_ID_TS_CreateConference					:             return "CreateConference";                                
	case  KFPC_MSG_ID_TS_FreeConference					:               return "FreeConference";                                  
	case  KFPC_MSG_ID_TS_JoinConference					:               return "JoinConference";                                  
	case  KFPC_MSG_ID_TS_LeaveConference					:             return "LeaveConference";                                 
	case  KFPC_MSG_ID_TS_ChangeConnectMode				:           return "ChangeConnectMode";                            
	case  KFPC_MSG_ID_TS_CollectDTMF						:               return "CollectDTMF";                                     
	case  KFPC_MSG_ID_TS_StopCollectDTMF					:             return "StopCollectDTMF";                                 
	case  KFPC_MSG_ID_TS_EVT_CollectDTMFCompleted			:         return "EVT_CollectDTMFCompleted";                        
	case  KFPC_MSG_ID_TS_PlayVoice						:                 return "PlayVoice";                                       
	case  KFPC_MSG_ID_TS_StopPlayVoice					:               return "StopPlayVoice";                                   
	case  KFPC_MSG_ID_TS_EVT_PlayVoiceCompleted			:           return "EVT_PlayVoiceCompleted";                          
	case  KFPC_MSG_ID_TS_RecordFile						:                 return "RecordFile";                                      
	case  KFPC_MSG_ID_TS_StopRecordFile					:               return "StopRecordFile";                                  
	case  KFPC_MSG_ID_TS_EVT_RecordFileCompleted			:         return "EVT_RecordFileCompleted";                         
	//case  KFPC_MSG_ID_TS_ConfPlayVoice					:               return "ConfPlayVoice";                                   
	//case  KFPC_MSG_ID_TS_StopConfPlayVoice				:             return "StopConfPlayVoice";                               
	//case  KFPC_MSG_ID_TS_EVT_ConfPlayFileCompleted		:         return "EVT_ConfPlayFileCompleted";                       
	//case  KFPC_MSG_ID_TS_ConfRecordFile					:               return "ConfRecordFile";                                  
	//case  KFPC_MSG_ID_TS_StopConfRecordFile				:             return "StopConfRecordFile";                              
	//case  KFPC_MSG_ID_TS_EVT_ConfRecordFileCompleted		:       return "EVT_ConfRecordFileCompleted";                     
	case  KFPC_MSG_ID_TS_SendFax							:                 return "SendFax";                                         
	case  KFPC_MSG_ID_TS_StopSendFax						:               return "StopSendFax";                                     
	case  KFPC_MSG_ID_TS_EVT_SendFaxCompleted				:           return "EVT_SendFaxCompleted";                            
	case  KFPC_MSG_ID_TS_RecvFax							:                 return "RecvFax";                                         
	case  KFPC_MSG_ID_TS_StopRecvFax						:               return "StopRecvFax";                                     
	case  KFPC_MSG_ID_TS_EVT_RecvFaxCompleted				:           return "EVT_RecvFaxCompleted";                            
	case  KFPC_MSG_ID_TS_ReloadCfg						:                 return "ReloadCfg";                                       
	case  KFPC_MSG_ID_TS_QueryChStatus					:               return "QueryChStatus";                                   
	case  KFPC_MSG_ID_TS_UpdateChStatus					:               return "UpdateChStatus";                                  
	case  KFPC_MSG_ID_TS_SetChStatus						:               return "SetChStatus";                                     
	case  KFPC_MSG_ID_TS_CoreDump							:                 return "CoreDump";                                        
	case  KFPC_MSG_ID_TS_EVT_Alarm						:                 return "EVT_Alarm";                                       
	case  KFPC_MSG_ID_TS_WatchTrunkGroup					:             return "WatchTrunkGroup";                                 
	case  KFPC_MSG_ID_TS_CancelWatchTrunkGroup			:           return "CancelWatchTrunkGroup";                           
	case  KFPC_MSG_ID_TS_QueryTrunkGroup					:             return "QueryTrunkGroup";                                 
	case  KFPC_MSG_ID_TS_EVT_UpdateTrunkGroup				:           return "EVT_UpdateTrunkGroup";                            
	case  KFPC_MSG_ID_TS_MonitorChStatus					:             return "MonitorChStatus";                                 
	//case  KFPC_MSG_ID_TS_WatchNumStatus					:               return "WatchNumStatus";                                  
	case  KFPC_MSG_ID_TS_EVT_ExtNum2CCS				:					return "EVT_ExtNum2CCS";                             
	case  KFPC_MSG_ID_TS_RequestChannel					:               return "RequestChannel";                                  
	case  KFPC_MSG_ID_TS_EVT_HookFlash					:               return "EVT_HookFlash"; 
	case KFPC_MSG_ID_TS_PlayDTMF                        :               return "PlayDTMF";
	case KFPC_MSG_ID_TS_EVT_PassAnswerCall				:				return "PassAnswerCall";
	case  KFPC_MSG_ID_TS_END								:                   return "END";                                             
	default:return "unknow";
	}
}
//#define 

/**
 * 网络消息包结构定义，
 * 没特别说明，一个请求包都有一个相应的响应包
 * 消息头：KFPC_MSG_HEADER
 * 见头文件：kfpc_msg.h
 * @code
 */

typedef enum KFPC_VoiceStatus_t
{
	IVR_STATUS_IDLE = 0,				/**< IVR 通道空闲 */
	IVR_STATUS_PLAY_VOICE = 1,			/**< 播放语音 */
	IVR_STATUS_RECORD_FILE = 2,			/**< 录音 */
	IVR_STATUS_COLLECT_DTMF = 4,			/**< 收号中 */
	IVR_STATUS_PLAY_DTMF = 8,			/**< 收号中 */
	IVR_STATUS_INVALID = 0xff             /**< 无效状态 */
}KFPC_VoiceStatus_t;


/**
 * 取得TS版本号的请求包
 */
typedef struct KFPC_REQ_TS_GetTSVersion
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */	
}KFPC_REQ_TS_GetTSVersion;

/**
 * 获取当前联接的TS版本号的响应包
 */
typedef struct KFPC_RSP_TS_GetTSVersion 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */									
	char			Version[KFPC_MAX_VERSION_STR_SIZE];		/**< 版本号，C风格的字符串(以'\0'结尾的字符串)		*/	
}KFPC_RSP_TS_GetTSVersion;

/**
 * 接受呼叫
 */
typedef struct KFPC_REQ_TS_AcceptCall
{
	KFPC_MSG_HEADER		Header;								/**< 消息头 */									
	unsigned long long	CallID;								/**< 呼叫ID */
}KFPC_REQ_TS_AcceptCall;

typedef struct KFPC_RSP_TS_AcceptCall
{
	KFPC_MSG_HEADER		Header;								/**< 消息头 */
	unsigned long long	CallID;								/**< 呼叫ID */
	unsigned int		Result;								/**< 执行结果 */	
}KFPC_RSP_TS_AcceptCall;


/**
 * 摘机、呼叫应答
 */
typedef struct KFPC_REQ_TS_AnswerCall
{
	KFPC_MSG_HEADER		Header;								/**< 消息头 */
	unsigned long long	CallID;								/**< 呼叫ID */
}KFPC_TS_AnswerCall;

typedef struct KFPC_RSP_TS_AnswerCall
{
	KFPC_MSG_HEADER		Header;								/**< 消息头 */
	unsigned long long	CallID;								/**< 呼叫ID */
	unsigned int		Result;								/**< 执行结果 */	
}KFPC_RSP_TS_AnswerCall;


/**
 * 函数-挂机、释放通道呼叫
 */
typedef struct KFPC_REQ_TS_ReleaseCall
{
	KFPC_MSG_HEADER		Header;								/**< 消息头 */
	unsigned long long	CallID;								/**< 呼叫ID */
	unsigned int		Cause;								/**< 释放原因值	*/
}KFPC_REQ_TS_ReleaseCall;

typedef struct KFPC_RSP_TS_ReleaseCall
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;								/**< 呼叫ID */
	unsigned int		Result;								/**< 执行结果 */
}KFPC_RSP_TS_ReleaseCall;


/**
 * 外呼请求包
 */
typedef struct KFPC_REQ_TS_CallOut 
{
	KFPC_MSG_HEADER     Header									/**< 消息头 */;
	KFPC_DEVICE			Device;									/**< 呼出设备信息 */	
	char				InTrunkGroup[KFPC_TRUNKGROUP_NAME_LEN]; /**< 入中继组 */	
}KFPC_REQ_TS_CallOut;

/**
 * 外呼响应包
 */
typedef struct KFPC_RSP_TS_CallOut
{
	KFPC_MSG_HEADER     Header									/**< 消息头 */;
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		Result;									/**< 执行结果 */
	unsigned int		Cause;									/**< 外呼失败原因								*/
	KFPC_DEVICE			Device;									/**< 呼出设备信息 */	
	unsigned int		SignalType;
}KFPC_RSP_TS_CallOut;


/**
 * 呼叫入线
 */
typedef struct KFPC_TS_EVT_IncomingCall
{
	KFPC_MSG_HEADER     Header									/**< 消息头 */;
	unsigned long long	CallID;									/**< 呼叫ID */
	KFPC_DEVICE			Device;									/**< 设备信息 */
	unsigned int		SignalType;								/**< 信令类型(和通道模型上的信令类型一致)		*/
}KFPC_TS_EVT_IncomingCall;

/**
 * 被叫接受呼叫
 */
typedef struct KFPC_TS_EVT_AlertCall
{
	KFPC_MSG_HEADER     Header									/**< 消息头 */;
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		Cause;									/**< 外呼失败原因								*/
}KFPC_TS_EVT_AlertCall;

/**
 * 被叫应答
 */
typedef struct KFPC_TS_EVT_AnsweredCall
{
	KFPC_MSG_HEADER     Header									/**< 消息头 */;
	unsigned long long	CallID;									/**< 呼叫ID */
}KFPC_TS_EVT_AnsweredCall;

/**
 * 呼叫释放
 */
typedef struct KFPC_TS_EVT_ReleasedCall
{
	KFPC_MSG_HEADER     Header									/**< 消息头 */;
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		Cause;									/**< 外呼失败原因								*/
}KFPC_TS_EVT_ReleasedCall;

/**
 * 连接两个通道
 */
typedef struct KFPC_REQ_TS_Connect											
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	unsigned long long	CallID1;							/**< 呼叫ID */
	unsigned long long	CallID2;							/**< 呼叫ID */
	unsigned int		ConnectMode;								/**< 会议模式，见KFPC_TS_ID_ConferenceJoinMode			*/
	unsigned int		StopMedia;							/**< 具体参考KFPC_VoiceStatus_t */
}KFPC_REQ_TS_Connect;

typedef struct KFPC_RSP_TS_Connect
{
	KFPC_MSG_HEADER     Header								/**< 消息头 */;
	unsigned long long	CallID1;							/**< 呼叫ID */
	unsigned long long	CallID2;							/**< 呼叫ID */
	unsigned int		Result;								/**< 执行结果 */
	unsigned long long	SessionID;							
}KFPC_RSP_TS_Connect;

/**
 * 断开连接两个通道
 */
typedef struct KFPC_REQ_TS_Disconnect
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	unsigned long long	CallID;							/**< 呼叫ID */
}KFPC_REQ_TS_Disconnect;

typedef struct KFPC_RSP_TS_Disconnect
{
	KFPC_MSG_HEADER     Header									/**< 消息头 */;
	unsigned long long	CallID;							/**< 呼叫ID */
	unsigned int		Result;								/**< 执行结果 */
}KFPC_RSP_TS_Disconnect;

/**
 * 创建会议
 */
typedef struct KFPC_REQ_TS_CreateConference 
{
	KFPC_MSG_HEADER     Header;									/**< 消息头 */
	unsigned int		MaxMember;								/**< 成员数				*/
	unsigned int		NodeID;									/**< 交换机节点ID,默认为0	*/
	unsigned int        TserverID;                              /**< TSID, 告诉Route在哪个TS上建会议*/
	unsigned int        CCSID;                                  /**< CCSID, 告诉Route 如何返回创建的会议, Tserver在RSP中代回该值*/
}KFPC_REQ_TS_CreateConference;
 
typedef struct KFPC_RSP_TS_CreateConference
{
	KFPC_MSG_HEADER     Header;									/**< 消息头 */
	unsigned long long	ConfID;									/**< 会议ID */
	unsigned int        CCSID;                                  /**< CCSID, 告诉Route 如何返回创建的会议*/
	unsigned int		Result;									/**<执行结果 */ 
}KFPC_RSP_TS_CreateConference;

/**
 * 释放会议
 */
typedef struct KFPC_REQ_TS_FreeConference 
{
	KFPC_MSG_HEADER Header;										/**< 消息头 */
	unsigned long long	ConfID;									/**< 会议ID */
}KFPC_REQ_TS_FreeConference;

typedef struct KFPC_RSP_TS_FreeConference
{
	KFPC_MSG_HEADER     Header									/**< 消息头 */;
	unsigned long long	ConfID;									/**< 会议ID */
	unsigned int		Result;									/**<执行结果 */ 
}KFPC_RSP_TS_FreeConference;

/**
 * 加入会议
 */
typedef struct KFPC_REQ_TS_JoinConference 
{
	KFPC_MSG_HEADER     Header									/**< 消息头 */;
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned long long	ConfID;									/**< 会议ID */
	unsigned int		JoinMode;								/**< 会议模式，见KFPC_TS_ID_ConferenceJoinMode			*/
	int					DTMFSilence;							/**< DTMF静音 */
	unsigned int		StopMedia;							/**< 具体参考KFPC_VoiceStatus_t */
}KFPC_REQ_TS_JoinConference;

typedef struct KFPC_RSP_TS_JoinConference 
{
	KFPC_MSG_HEADER     Header									/**< 消息头 */;
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned long long	ConfID;									/**< 会议ID */
	unsigned int		Result;									/**<执行结果 */ 
	unsigned long long Session;
}KFPC_RSP_TS_JoinConference;

/**
 * 退出会议
 */
typedef struct KFPC_REQ_TS_LeaveConference 
{
	KFPC_MSG_HEADER     Header									/**< 消息头 */;
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned long long	ConfID;									/**< 会议ID */
}KFPC_REQ_TS_LeaveConference;

typedef struct KFPC_RSP_TS_LeaveConference
{
	KFPC_MSG_HEADER     Header									/**< 消息头 */;
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned long long	ConfID;									/**< 会议ID */
	unsigned int		Result;									/**<执行结果 */ 
}KFPC_RSP_TS_LeaveConference;

/**
 * 改变会议模式
 */
typedef struct KFPC_REQ_TS_ChangeConnectMode
{
	KFPC_MSG_HEADER     Header									/**< 消息头 */;
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		ConnectMode;								/**< 会议模式，见KFPC_TS_ID_ConferenceJoinMode			*/
}KFPC_REQ_TS_ChangeConnectMode;

typedef struct KFPC_RSP_TS_ChangeConnectMode 
{
	KFPC_MSG_HEADER     Header									/**< 消息头 */;
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		Result;									/**<执行结果 */ 
}KFPC_RSP_TS_ChangeConnectMode;

/**
 * 开始收号
 */
typedef struct KFPC_REQ_TS_CollectDTMF
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
	KFPC_DTMFParam		DTMFParam;								/**< 收号参数 */
	unsigned int        MixCollect;
}KFPC_REQ_TS_CollectDTMF;

typedef struct KFPC_RSP_TS_CollectDTMF 
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		Result;									/**<执行结果 */ 
}KFPC_RSP_TS_CollectDTMF;

/**
 * 手动停止收号
 */
typedef struct KFPC_REQ_TS_StopCollectDTMF 
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */	
	unsigned long long	CallID;									/**< 呼叫ID */
}KFPC_REQ_TS_StopCollectDTMF;

typedef struct KFPC_RSP_TS_StopCollectDTMF 
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		Result;									/**<执行结果 */ 
}KFPC_RSP_TS_StopCollectDTMF;

/**
 * 完成收号消息包
 */
typedef struct KFPC_TS_EVT_CollectDTMFCompleted			
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		DTMFCount;								/**< DTMF个数												*/
	char				DTMF[KFPC_MAX_DTMF_SIZE];				/**< 按键数组，非C字符串									*/
	unsigned int		Result;									/**< 收号结束原因											*/
}KFPC_TS_EVT_CollectDTMFCompleted;


typedef struct KFPC_REQ_TS_PlayVoice 
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
	KFPC_DTMFParam		DTMFParam;								/**< 收号参数 */
	char				PlayContent[KFPC_MAX_PLAY_CONTENT];		/**< 播放内容 比如：FileName:test.wav,TTS:测试 同时播放多种格式内容*/
	unsigned int		MixPlay;								/**< 混合录音 */
}KFPC_REQ_TS_PlayVoice;

typedef struct KFPC_RSP_TS_PlayVoice 
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		Result;									/**<执行结果 */ 
}KFPC_RSP_TS_PlayVoice;

/** 
 * 停止放音
 */
typedef struct KFPC_REQ_TS_StopPlayVoice 
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int        CollectDTMF;							/**< 是否停止收号*/
}KFPC_REQ_TS_StopPlayVoice;

typedef struct KFPC_RSP_TS_StopPlayVoice 
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		Result;									/**<执行结果 */ 
}KFPC_RSP_TS_StopPlayVoice;

/**
 * 放音完成事件
 */
typedef struct KFPC_TS_EVT_PlayVoiceCompleted					
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
}KFPC_TS_EVT_PlayVoiceCompleted;


/**
 * 开始录音
 */
typedef struct KFPC_REQ_TS_StartRecordFile
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		TermgChar;	                            /**< 停止录音结束符*/
	char				FileName[KFPC_MAX_FILE_NAME];			/**< 文件名	*/
	unsigned int		RecordTime;								/**< 录音时间长，单位为秒 */
	unsigned int		MixRecord;								/**< 混合录音 */
}KFPC_REQ_TS_StartRecordFile;

typedef struct KFPC_RSP_TS_StartRecordFile
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		Result;									/**<执行结果 */ 
}KFPC_RSP_TS_StartRecordFile;

/**
 * 停止录音
 */
typedef struct KFPC_REQ_TS_StopRecordFile
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */				
}KFPC_REQ_TS_StopRecordFile;

typedef struct KFPC_RSP_TS_StopRecordFile
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */							
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		Result;									/**<执行结果 */ 
}KFPC_RSP_TS_StopRecordFile;

/**
 * 录单完成事件
 */
typedef struct KFPC_TS_EVT_RecordFileCompleted				
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
}KFPC_TS_EVT_RecordFileCompleted;

///**
// * 对会议播放单个文件
// */
//typedef struct KFPC_REQ_TS_ConfPlayVoice 
//{
//	KFPC_MSG_HEADER		Header;									/**< 消息头 */
//	unsigned long long	ConfID;									/**< 会议ID */
//	char				PlayContent[KFPC_MAX_PLAY_CONTENT];		/**< 播放内容 比如：ID:123,FileName:test.wav,TTS:测试 同时播放多种格式内容*/
//}KFPC_REQ_TS_ConfPlayVoice;
//
//typedef struct KFPC_RSP_TS_ConfPlayVoice 
//{
//	KFPC_MSG_HEADER		Header;									/**< 消息头 */
//	unsigned long long	ConfID;									/**< 会议ID */
//	unsigned int		Result;									/**<执行结果 */ 
//}KFPC_RSP_TS_ConfPlayVoice;
//
///**
// * 会议停止放音
// */
//typedef struct KFPC_REQ_TS_ConfStopPlayVoice 
//{
//	KFPC_MSG_HEADER		Header;									/**< 消息头 */
//	unsigned long long	ConfID;									/**< 呼叫ID */
//}KFPC_REQ_TS_ConfStopPlayVoice;
//
//typedef struct KFPC_RSP_TS_ConfStopPlayVoice 
//{
//	KFPC_MSG_HEADER		Header;									/**< 消息头 */
//	unsigned long long	ConfID;									/**< 会议ID */
//	unsigned int		Result;									/**<执行结果 */ 
//}KFPC_RSP_TS_ConfStopPlayVoice;
//
///**
// * 会议放音完成事件
// */
//typedef struct KFPC_TS_EVT_ConfPlayVoiceCompleted			
//{
//	KFPC_MSG_HEADER		Header;									/**< 消息头 */		
//	unsigned long long	ConfID;									/**< 会议ID */
//}KFPC_TS_EVT_ConfPlayVoiceCompleted;
//
//
///**
// * 会议录音
// */
//typedef struct KFPC_REQ_TS_ConfStartRecordFile
//{
//	KFPC_MSG_HEADER		Header;									/**< 消息头 */
//	unsigned long long	ConfID;									/**< 会议ID */
//	char				FileName[KFPC_MAX_FILE_NAME];			/**< 文件名	*/
//	unsigned int		RecordTime;								/**< 录音时间长，单位为秒	*/
//}KFPC_REQ_TS_ConfStartRecordFile;
//
//typedef struct KFPC_RSP_TS_ConfStartRecordFile
//{
//	KFPC_MSG_HEADER		Header;									/**< 消息头 */
//	unsigned long long	ConfID;									/**< 会议ID */
//	unsigned int		Result;									/**<执行结果 */ 
//}KFPC_RSP_TS_ConfStartRecordFile;
//
///**
// * 会议停止录音
// */
//typedef struct KFPC_REQ_TS_ConfStopRecordFile
//{
//	KFPC_MSG_HEADER		Header;									/**< 消息头 */
//	unsigned long long	ConfID;									/**< 会议ID */
//}KFPC_REQ_TS_ConfStopRecordFile;
//
//typedef struct KFPC_RSP_TS_ConfStopRecordFile
//{
//	KFPC_MSG_HEADER		Header;									/**< 消息头 */				
//	unsigned long long	ConfID;									/**< 会议ID */
//	unsigned int		Result;									/**<执行结果 */ 
//}KFPC_RSP_TS_ConfStopRecordFile;
//
///**
// * 会议录音完成事件
// */
//typedef struct KFPC_TS_EVT_ConfRecordFileCompleted			
//{
//	KFPC_MSG_HEADER		Header;									/**< 消息头 */		
//	unsigned long long	ConfID;									/**< 会议ID */
//}KFPC_TS_EVT_ConfRecordFileCompleted;

/**
 * 开始接收传真
 */
typedef struct KFPC_REQ_TS_RecvFax 
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
	char				FileName[KFPC_MAX_FILE_NAME];			/**< 文件名	*/
}KFPC_REQ_TS_RecvFax;

typedef struct KFPC_RSP_TS_RecvFax 
{
	KFPC_MSG_HEADER		Header;										/**< 消息头 */			
	unsigned long long	CallID;										/**< 呼叫ID */
	unsigned int		Result;										/**< 返回结果 */
}KFPC_RSP_TS_RecvFax;

/**
 * 停止接收传真
 */
typedef struct KFPC_REQ_TS_StopReceiveFax 
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
}KFPC_REQ_TS_StopReceiveFax;

typedef struct KFPC_RSP_TS_StopReceiveFax 
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		Result;									/**< 返回结果 */
}KFPC_RSP_TS_StopReceiveFax;

/**
 * 接收传真完成事件
 */
typedef struct KFPC_TS_EVT_ReceiveFaxCompleted				
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */				
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		Result;									/**< 返回结果 */
	unsigned int		PageCount;
}KFPC_TS_EVT_ReceiveFaxCompleted;	

/**
 * 开始发送传真
 */
typedef struct KFPC_REQ_TS_StartSendFax 
{
	KFPC_MSG_HEADER		Header;										/**< 消息头 */
	unsigned long long	CallID;										/**< 呼叫ID */
	char				FileName[KFPC_MAX_FILE_NAME];				/**< 传真文件名	*/
	char				SenderIdent[KFPC_MAX_FAX_INFO];				/**<发送者ID*/	
	char				SubAddress[KFPC_MAX_FAX_INFO];				/**<地址			默认：*/
	char				PageHeaderInfo[KFPC_MAX_FAX_INFO];			/**<页头信息		默认：*/
	char				Identifier[KFPC_MAX_FAX_INFO];				/**<传真ID		默认：*/
}KFPC_REQ_TS_StartSendFax;

typedef struct KFPC_RSP_TS_StartSendFax
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		Result;									/**< 返回结果 */
}KFPC_RSP_TS_StartSendFax;

/**
 * 停止发送传真
 */
typedef struct KFPC_REQ_TS_StopSendFax 
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned long long	CallID;									/**< 呼叫ID */
}KFPC_REQ_TS_StopSendFax;


typedef struct KFPC_RSP_TS_StopSendFax 
{
	KFPC_MSG_HEADER Header;										/**< 消息头 */			
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		Result;									/**< 返回结果 */
}KFPC_RSP_TS_StopSendFax;


/**
 * 发送传真完成
 */
typedef struct KFPC_TS_EVT_SendFaxCompleted					
{
	KFPC_MSG_HEADER Header;										/**< 消息头 */		
	unsigned long long	CallID;									/**< 呼叫ID */
	unsigned int		Result;									/**< 返回结果 */
	unsigned int		PageCount;
}KFPC_TS_EVT_SendFaxCompleted;



/**
 * 重新加载config文件
 */
typedef struct KFPC_REQ_TS_ReloadConfig				
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */				
	//need to define what shall be reloaded

}KFPC_REQ_TS_ReloadConfig;


typedef struct KFPC_RSP_TS_ReloadConfig				
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */				
	unsigned int		Result;									/**< 返回结果 */
}KFPC_RSP_TS_ReloadConfig;


/**
 * 通道状态改变事件
 */
typedef struct KFPC_REQ_TS_QueryChStatus 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
}KFPC_REQ_TS_QueryChStatus;

typedef struct KFPC_RSP_TS_QueryChStatus 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	unsigned int		Result;									/**< 返回结果 */
}KFPC_RSP_TS_QueryChStatus;


typedef struct KFPC_TS_EVT_UpdateChStatus 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	unsigned int	ChannelCount;							/**< 通道数量 */
	unsigned int	State[KFPC_MAX_CHANNEL];				/**< 通道状态 */
	unsigned int	Channel[KFPC_MAX_CHANNEL];				/**< 通道号 */	
}KFPC_TS_EVT_ChStateChanged;

typedef struct KFPC_REQ_TS_SetChState 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	unsigned int	ChannelCount;							/**< 通道数量 */
	unsigned int	State[KFPC_MAX_CHANNEL];				/**< 通道状态 */
	unsigned int	Channel[KFPC_MAX_CHANNEL];				/**< 通道号 */	
}KFPC_REQ_TS_SetChState;


typedef struct KFPC_RSP_TS_SetChState 
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned int		Result;									/**< 返回结果 */
}KFPC_RSP_TS_SetChState;

/**
* 其它事件
*/
typedef struct KFPC_REQ_TS_CoreDump 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
}KFPC_REQ_TS_CoreDump;


typedef struct KFPC_RSP_TS_CoreDump
{
	KFPC_MSG_HEADER		Header;									/**< 消息头 */
	unsigned int		Result;									/**< 返回结果 */
}KFPC_RSP_TS_CoreDump;

typedef struct KFPC_TS_EVT_AlarmEvent 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	unsigned int	AlarmID;								/**< 告警ID */
	char			AlarmContent[KFPC_MAX_ALARM_CONTENT];	/**< 告警内容 */
}KFPC_TS_EVT_AlarmEvent;


typedef struct KFPC_REQ_TS_WatchTrunkGroup
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	char			TrunkGroup[KFPC_TRUNKGROUP_NAME_LEN];	/**< 中继组名 */

}KFPC_REQ_TS_WatchTrunkGroup;

typedef struct KFPC_RSP_TS_WatchTrunkGroup 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	char			TrunkGroup[KFPC_TRUNKGROUP_NAME_LEN];	/**< 中继组名 */
	unsigned int	Result;									/**< 返回结果 */
}KFPC_RSP_TS_WatchTrunkGroup;


typedef struct KFPC_REQ_TS_CancelWatchTrunkGroup 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	char			TrunkGroup[KFPC_TRUNKGROUP_NAME_LEN];	/**< 中继组名 */
}KFPC_REQ_TS_CancelWatchTrunkGroup;

typedef struct KFPC_RSP_TS_CancelWatchTrunkGroup 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	char			TrunkGroup[KFPC_TRUNKGROUP_NAME_LEN];	/**< 中继组名 */
	unsigned int	Result;									/**< 返回结果 */
}KFPC_RSP_TS_CancelWatchTrunkGroup;



typedef struct KFPC_REQ_TS_QueryTrunkGroup 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
}KFPC_REQ_TS_QueryTrunkGroup;

typedef struct KFPC_RSP_TS_QueryTrunkGroup 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	unsigned int	Result;									/**< 返回结果 */
}KFPC_RSP_TS_QueryTrunkGroup;

typedef struct KFPC_TS_EVT_UpdateTrunkGroup 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	char			TrunkGroup[KFPC_TRUNKGROUP_NAME_LEN];	/**< 中继组名 */
}KFPC_TS_EVT_UpdateTrunkGroup;

typedef struct KFPC_REQ_TS_MonitorChStatus 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
}KFPC_REQ_TS_MonitorChStatus;

typedef struct KFPC_RSP_TS_MonitorChStatus 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	unsigned int	Result;									/**< 返回结果 */
}KFPC_RSP_TS_MonitorChStatus;

typedef struct KFPC_REQ_TS_WatchNumStatus 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	char			CallerNO[KFPC_MAX_NUMBER_SIZE];			/**< 主叫号码 */
}KFPC_REQ_TS_WatchNumStatus;

typedef struct KFPC_RSP_TS_WatchNumStatus 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	unsigned int	Result;									/**< 返回结果 */
}KFPC_RSP_TS_WatchNumStatus;

typedef struct KFPC_TS_EVT_WatchNumStatus 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	char			CallerNO[KFPC_MAX_NUMBER_SIZE];			/**< 主叫号码 */
	unsigned int	State;									/**< 通道状态 */
	unsigned int	Channel;								/**< 通道号 */	
}KFPC_TS_EVT_WatchNumStatus;

typedef struct KFPC_REQ_TS_PlayDTMF 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	char			DTMF[KFPC_MAX_DTMF_SIZE];			    /**< 要放音的DTMF */
	unsigned long long	CallID;	                            /**<  呼叫ID*/
}KFPC_REQ_TS_PlayDTMF;

typedef struct KFPC_RSP_TS_PlayDTMF 
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	unsigned long long	CallID;	                            /**<  呼叫ID*/
	unsigned int	Result;									/**< 返回结果 */
}KFPC_RSP_TS_PlayDTMF;

typedef struct KFPC_TS_EVT_HookFlash
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	unsigned long long	CallID;	                            /**<  呼叫ID*/
}KFPC_TS_EVT_HookFlash;

typedef struct KFPC_TS_EVT_ExtNum2CCS
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	unsigned int	Flag;									/**< 0为删除，1为添加*/
	char			ExtNum[KFPC_MAX_NUMBER_SIZE];			/**< 主叫号码 */
	unsigned int	CCS;
}KFPC_TS_EVT_ExtNum2CCS;

typedef struct KFPC_TS_EVT_PassAnswerCall
{
	KFPC_MSG_HEADER Header;									/**< 消息头 */
	unsigned long long	CallID;								/**< 呼叫ID */
}KFPC_TS_EVT_PassAnswerCall;


#endif // kfpc_tserver_api_h__
