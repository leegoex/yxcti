#ifndef kfpc_tserver_api_h__
#define kfpc_tserver_api_h__

/************************************************************************

���ܣ�TAPI�Ķ���
���ߣ�Feng yanfa
���ڣ�2012-11-20
˵����
TSAPI�Ķ���.

************************************************************************/

#include "kfpc_id.h"
#include "kfpc_msg.h"
#include "KFPC_ContactCenterPublicDef.h"

/**
 * @def KFPC_TS_INTERFACEVERSION "1.0.0.0"
 * @brief ��ǰ�ӿڰ汾
 */

#define KFPC_TS_INTERFACEVERSION					"1.0.0.0"

/**
 * @ KFPC_TS_ID
 * @brief TS_ID����
 */

#define	KFPC_MSG_ID_TS_GetTSVersion						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x01)		/**< ��ȡTS�汾�� */
#define	KFPC_MSG_ID_TS_AcceptCall						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x02)		/**< ���ܺ���(���ں���) */
#define	KFPC_MSG_ID_TS_AnswerCall						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x03)		/**< Ӧ�����(���ں���) */
#define	KFPC_MSG_ID_TS_ReleaseCall						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x04)		/**< �ͷź���(������������) */
#define	KFPC_MSG_ID_TS_CallOut							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x05)		/**< ��� */
#define	KFPC_MSG_ID_TS_EVT_IncomingCall					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x06)		/**< �������� */
#define	KFPC_MSG_ID_TS_EVT_AlertCall					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x07)		/**< �����Է����壬����¼��ڵ����շ��ͱ��к�ʱ���á� */
#define	KFPC_MSG_ID_TS_EVT_AnsweredCall					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x08)		/**< ������Է�Ӧ���¼� */
#define	KFPC_MSG_ID_TS_EVT_ReleasedCall					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x09)		/**< �����ͷ� */
#define	KFPC_MSG_ID_TS_Connect							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x0a)		/**< ������������,�ͷ���ͨ�����ӵ�������Դ,������ȫ˫��¼�� */
#define	KFPC_MSG_ID_TS_Disconnect						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x0b)		/**< �Ͽ�����ͨ�� */
#define	KFPC_MSG_ID_TS_CreateConference					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x0c)		/**< �����������ٴ���3�� */
#define	KFPC_MSG_ID_TS_FreeConference					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x0d)		/**< �ͷŻ��� */
#define	KFPC_MSG_ID_TS_JoinConference					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x0e)		/**< �������,��Ϊȫ˫�������Ͱ�˫������ */
#define	KFPC_MSG_ID_TS_LeaveConference					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x0f)		/**< �˳����� */
#define	KFPC_MSG_ID_TS_ChangeConnectMode				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x10)		/**< �ı����ģʽֻ������˵ */
#define	KFPC_MSG_ID_TS_CollectDTMF						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x11)		/**< �պ� */
#define	KFPC_MSG_ID_TS_StopCollectDTMF					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x12)		/**< ֹͣ�պţ��ж�DSP��Դ�Ƿ���У�����������ջ�DSP��Դ */
#define	KFPC_MSG_ID_TS_EVT_CollectDTMFCompleted			KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x13)		/**< �պ���ɺ��ж�DSP��Դ�Ƿ���У�����������ջ�DSP��Դ */
#define	KFPC_MSG_ID_TS_PlayVoice						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x14)		/**< �����������ļ������ļ�ID��TTS�ı� */
#define	KFPC_MSG_ID_TS_StopPlayVoice					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x15)		/**< ֹͣ�������ж�DSP��Դ�Ƿ���У�����������ջ�DSP��Դ */
#define	KFPC_MSG_ID_TS_EVT_PlayVoiceCompleted			KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x16)		/**< ��������¼�,����ж�DSP��Դ�Ƿ���У�����������ջ�DSP��Դ */
#define	KFPC_MSG_ID_TS_RecordFile						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x17)		/**< ¼����Ϊ˫��¼��������¼���������˫��¼����ôֻ��ֹͣ�ջ��߹һ��Ż����DSP��Դ */
#define	KFPC_MSG_ID_TS_StopRecordFile					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x18)		/**< ֹͣ¼�����ж�DSP��Դ�Ƿ���У�����������ջ�DSP��Դ */
#define	KFPC_MSG_ID_TS_EVT_RecordFileCompleted			KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x19)		/**< ¼����ɡ��ж�DSP��Դ�Ƿ���У�����������ջ�DSP��Դ */
//#define	KFPC_MSG_ID_TS_ConfPlayVoice					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x1a)		/**< ��������������ļ������ļ�ID��TTS�ı� */
//#define	KFPC_MSG_ID_TS_StopConfPlayVoice				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x1b)		/**< ֹͣ������� */
//#define	KFPC_MSG_ID_TS_EVT_ConfPlayFileCompleted		KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x1c)		/**< ���������� */
//#define	KFPC_MSG_ID_TS_ConfRecordFile					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x1d)		/**< ����¼�� */
//#define	KFPC_MSG_ID_TS_StopConfRecordFile				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x1e)		/**< ֹͣ����¼�� */
//#define	KFPC_MSG_ID_TS_EVT_ConfRecordFileCompleted		KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x1f)		/**< ���������� */
#define	KFPC_MSG_ID_TS_SendFax							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x20)		/**< ���ʹ��� */
#define	KFPC_MSG_ID_TS_StopSendFax						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x21)		/**< ֹͣ���ʹ��� */
#define	KFPC_MSG_ID_TS_EVT_SendFaxCompleted				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x22)		/**< ���ʹ������ */
#define	KFPC_MSG_ID_TS_RecvFax							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x23)		/**< ���մ��� */
#define	KFPC_MSG_ID_TS_StopRecvFax						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x24)		/**< ֹͣ���մ��� */
#define	KFPC_MSG_ID_TS_EVT_RecvFaxCompleted				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x25)		/**< �սӴ������ */
#define	KFPC_MSG_ID_TS_ReloadCfg						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x26)		/**< ���¼��������ļ������ڶ�̬���� */
#define	KFPC_MSG_ID_TS_QueryChStatus					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x27)		/**< ��ѯͨ��״̬ */
#define KFPC_MSG_ID_TS_UpdateChStatus					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x28)		/**< ��ѯͨ��״̬ */
#define	KFPC_MSG_ID_TS_SetChStatus						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x29)		/**< �ı�ͨ��״̬ */
#define	KFPC_MSG_ID_TS_CoreDump							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x2a)		/**< �����ļ�������Դdump�ļ� */
#define	KFPC_MSG_ID_TS_EVT_Alarm						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x2b)		/**< �澯�¼��������м̸澯����Դ����澯��LICENSE����澯�����¼����͵�Monitor */
#define	KFPC_MSG_ID_TS_WatchTrunkGroup					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x2c)		/**< �۲��м������ */
#define	KFPC_MSG_ID_TS_CancelWatchTrunkGroup			KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER, 0x2d)		/**< ȡ���۲��м��� */
#define	KFPC_MSG_ID_TS_QueryTrunkGroup					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x2e)		/**< ��ѯ�м��� */
#define	KFPC_MSG_ID_TS_EVT_UpdateTrunkGroup				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x2f)		/**< �����м��� */
#define KFPC_MSG_ID_TS_MonitorChStatus					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x30)		/**< ���ͨ��״̬ */
//#define KFPC_MSG_ID_TS_WatchNumStatus					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x31)		/**< �۲����״̬ */
#define KFPC_MSG_ID_TS_EVT_ExtNum2CCS					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x32)		/**< ���붯̬·�ɸ��� */
#define KFPC_MSG_ID_TS_RequestChannel					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x33)		/**< ����ռ��ͨ�� */
#define KFPC_MSG_ID_TS_EVT_HookFlash					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x34)		/**< �Ĳ��¼� */
#define KFPC_MSG_ID_TS_TextToSpeech						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x35)		/**< �Ĳ��¼� */
#define KFPC_MSG_ID_TS_PlayDTMF							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x36)
#define KFPC_MSG_ID_TS_EVT_PassAnswerCall				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x37)
#define	KFPC_MSG_ID_TS_END								KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_TSERVER,	0x38)		/**< ����ID */

#define KFPC_MAX_MSG_ID_TS								KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_END)                                           /**< ����TS_ID��*/  

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
 * ������Ϣ���ṹ���壬
 * û�ر�˵����һ�����������һ����Ӧ����Ӧ��
 * ��Ϣͷ��KFPC_MSG_HEADER
 * ��ͷ�ļ���kfpc_msg.h
 * @code
 */

typedef enum KFPC_VoiceStatus_t
{
	IVR_STATUS_IDLE = 0,				/**< IVR ͨ������ */
	IVR_STATUS_PLAY_VOICE = 1,			/**< �������� */
	IVR_STATUS_RECORD_FILE = 2,			/**< ¼�� */
	IVR_STATUS_COLLECT_DTMF = 4,			/**< �պ��� */
	IVR_STATUS_PLAY_DTMF = 8,			/**< �պ��� */
	IVR_STATUS_INVALID = 0xff             /**< ��Ч״̬ */
}KFPC_VoiceStatus_t;


/**
 * ȡ��TS�汾�ŵ������
 */
typedef struct KFPC_REQ_TS_GetTSVersion
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */	
}KFPC_REQ_TS_GetTSVersion;

/**
 * ��ȡ��ǰ���ӵ�TS�汾�ŵ���Ӧ��
 */
typedef struct KFPC_RSP_TS_GetTSVersion 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */									
	char			Version[KFPC_MAX_VERSION_STR_SIZE];		/**< �汾�ţ�C�����ַ���(��'\0'��β���ַ���)		*/	
}KFPC_RSP_TS_GetTSVersion;

/**
 * ���ܺ���
 */
typedef struct KFPC_REQ_TS_AcceptCall
{
	KFPC_MSG_HEADER		Header;								/**< ��Ϣͷ */									
	unsigned long long	CallID;								/**< ����ID */
}KFPC_REQ_TS_AcceptCall;

typedef struct KFPC_RSP_TS_AcceptCall
{
	KFPC_MSG_HEADER		Header;								/**< ��Ϣͷ */
	unsigned long long	CallID;								/**< ����ID */
	unsigned int		Result;								/**< ִ�н�� */	
}KFPC_RSP_TS_AcceptCall;


/**
 * ժ��������Ӧ��
 */
typedef struct KFPC_REQ_TS_AnswerCall
{
	KFPC_MSG_HEADER		Header;								/**< ��Ϣͷ */
	unsigned long long	CallID;								/**< ����ID */
}KFPC_TS_AnswerCall;

typedef struct KFPC_RSP_TS_AnswerCall
{
	KFPC_MSG_HEADER		Header;								/**< ��Ϣͷ */
	unsigned long long	CallID;								/**< ����ID */
	unsigned int		Result;								/**< ִ�н�� */	
}KFPC_RSP_TS_AnswerCall;


/**
 * ����-�һ����ͷ�ͨ������
 */
typedef struct KFPC_REQ_TS_ReleaseCall
{
	KFPC_MSG_HEADER		Header;								/**< ��Ϣͷ */
	unsigned long long	CallID;								/**< ����ID */
	unsigned int		Cause;								/**< �ͷ�ԭ��ֵ	*/
}KFPC_REQ_TS_ReleaseCall;

typedef struct KFPC_RSP_TS_ReleaseCall
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;								/**< ����ID */
	unsigned int		Result;								/**< ִ�н�� */
}KFPC_RSP_TS_ReleaseCall;


/**
 * ��������
 */
typedef struct KFPC_REQ_TS_CallOut 
{
	KFPC_MSG_HEADER     Header									/**< ��Ϣͷ */;
	KFPC_DEVICE			Device;									/**< �����豸��Ϣ */	
	char				InTrunkGroup[KFPC_TRUNKGROUP_NAME_LEN]; /**< ���м��� */	
}KFPC_REQ_TS_CallOut;

/**
 * �����Ӧ��
 */
typedef struct KFPC_RSP_TS_CallOut
{
	KFPC_MSG_HEADER     Header									/**< ��Ϣͷ */;
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		Result;									/**< ִ�н�� */
	unsigned int		Cause;									/**< ���ʧ��ԭ��								*/
	KFPC_DEVICE			Device;									/**< �����豸��Ϣ */	
	unsigned int		SignalType;
}KFPC_RSP_TS_CallOut;


/**
 * ��������
 */
typedef struct KFPC_TS_EVT_IncomingCall
{
	KFPC_MSG_HEADER     Header									/**< ��Ϣͷ */;
	unsigned long long	CallID;									/**< ����ID */
	KFPC_DEVICE			Device;									/**< �豸��Ϣ */
	unsigned int		SignalType;								/**< ��������(��ͨ��ģ���ϵ���������һ��)		*/
}KFPC_TS_EVT_IncomingCall;

/**
 * ���н��ܺ���
 */
typedef struct KFPC_TS_EVT_AlertCall
{
	KFPC_MSG_HEADER     Header									/**< ��Ϣͷ */;
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		Cause;									/**< ���ʧ��ԭ��								*/
}KFPC_TS_EVT_AlertCall;

/**
 * ����Ӧ��
 */
typedef struct KFPC_TS_EVT_AnsweredCall
{
	KFPC_MSG_HEADER     Header									/**< ��Ϣͷ */;
	unsigned long long	CallID;									/**< ����ID */
}KFPC_TS_EVT_AnsweredCall;

/**
 * �����ͷ�
 */
typedef struct KFPC_TS_EVT_ReleasedCall
{
	KFPC_MSG_HEADER     Header									/**< ��Ϣͷ */;
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		Cause;									/**< ���ʧ��ԭ��								*/
}KFPC_TS_EVT_ReleasedCall;

/**
 * ��������ͨ��
 */
typedef struct KFPC_REQ_TS_Connect											
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	unsigned long long	CallID1;							/**< ����ID */
	unsigned long long	CallID2;							/**< ����ID */
	unsigned int		ConnectMode;								/**< ����ģʽ����KFPC_TS_ID_ConferenceJoinMode			*/
	unsigned int		StopMedia;							/**< ����ο�KFPC_VoiceStatus_t */
}KFPC_REQ_TS_Connect;

typedef struct KFPC_RSP_TS_Connect
{
	KFPC_MSG_HEADER     Header								/**< ��Ϣͷ */;
	unsigned long long	CallID1;							/**< ����ID */
	unsigned long long	CallID2;							/**< ����ID */
	unsigned int		Result;								/**< ִ�н�� */
	unsigned long long	SessionID;							
}KFPC_RSP_TS_Connect;

/**
 * �Ͽ���������ͨ��
 */
typedef struct KFPC_REQ_TS_Disconnect
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;							/**< ����ID */
}KFPC_REQ_TS_Disconnect;

typedef struct KFPC_RSP_TS_Disconnect
{
	KFPC_MSG_HEADER     Header									/**< ��Ϣͷ */;
	unsigned long long	CallID;							/**< ����ID */
	unsigned int		Result;								/**< ִ�н�� */
}KFPC_RSP_TS_Disconnect;

/**
 * ��������
 */
typedef struct KFPC_REQ_TS_CreateConference 
{
	KFPC_MSG_HEADER     Header;									/**< ��Ϣͷ */
	unsigned int		MaxMember;								/**< ��Ա��				*/
	unsigned int		NodeID;									/**< �������ڵ�ID,Ĭ��Ϊ0	*/
	unsigned int        TserverID;                              /**< TSID, ����Route���ĸ�TS�Ͻ�����*/
	unsigned int        CCSID;                                  /**< CCSID, ����Route ��η��ش����Ļ���, Tserver��RSP�д��ظ�ֵ*/
}KFPC_REQ_TS_CreateConference;
 
typedef struct KFPC_RSP_TS_CreateConference
{
	KFPC_MSG_HEADER     Header;									/**< ��Ϣͷ */
	unsigned long long	ConfID;									/**< ����ID */
	unsigned int        CCSID;                                  /**< CCSID, ����Route ��η��ش����Ļ���*/
	unsigned int		Result;									/**<ִ�н�� */ 
}KFPC_RSP_TS_CreateConference;

/**
 * �ͷŻ���
 */
typedef struct KFPC_REQ_TS_FreeConference 
{
	KFPC_MSG_HEADER Header;										/**< ��Ϣͷ */
	unsigned long long	ConfID;									/**< ����ID */
}KFPC_REQ_TS_FreeConference;

typedef struct KFPC_RSP_TS_FreeConference
{
	KFPC_MSG_HEADER     Header									/**< ��Ϣͷ */;
	unsigned long long	ConfID;									/**< ����ID */
	unsigned int		Result;									/**<ִ�н�� */ 
}KFPC_RSP_TS_FreeConference;

/**
 * �������
 */
typedef struct KFPC_REQ_TS_JoinConference 
{
	KFPC_MSG_HEADER     Header									/**< ��Ϣͷ */;
	unsigned long long	CallID;									/**< ����ID */
	unsigned long long	ConfID;									/**< ����ID */
	unsigned int		JoinMode;								/**< ����ģʽ����KFPC_TS_ID_ConferenceJoinMode			*/
	int					DTMFSilence;							/**< DTMF���� */
	unsigned int		StopMedia;							/**< ����ο�KFPC_VoiceStatus_t */
}KFPC_REQ_TS_JoinConference;

typedef struct KFPC_RSP_TS_JoinConference 
{
	KFPC_MSG_HEADER     Header									/**< ��Ϣͷ */;
	unsigned long long	CallID;									/**< ����ID */
	unsigned long long	ConfID;									/**< ����ID */
	unsigned int		Result;									/**<ִ�н�� */ 
	unsigned long long Session;
}KFPC_RSP_TS_JoinConference;

/**
 * �˳�����
 */
typedef struct KFPC_REQ_TS_LeaveConference 
{
	KFPC_MSG_HEADER     Header									/**< ��Ϣͷ */;
	unsigned long long	CallID;									/**< ����ID */
	unsigned long long	ConfID;									/**< ����ID */
}KFPC_REQ_TS_LeaveConference;

typedef struct KFPC_RSP_TS_LeaveConference
{
	KFPC_MSG_HEADER     Header									/**< ��Ϣͷ */;
	unsigned long long	CallID;									/**< ����ID */
	unsigned long long	ConfID;									/**< ����ID */
	unsigned int		Result;									/**<ִ�н�� */ 
}KFPC_RSP_TS_LeaveConference;

/**
 * �ı����ģʽ
 */
typedef struct KFPC_REQ_TS_ChangeConnectMode
{
	KFPC_MSG_HEADER     Header									/**< ��Ϣͷ */;
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		ConnectMode;								/**< ����ģʽ����KFPC_TS_ID_ConferenceJoinMode			*/
}KFPC_REQ_TS_ChangeConnectMode;

typedef struct KFPC_RSP_TS_ChangeConnectMode 
{
	KFPC_MSG_HEADER     Header									/**< ��Ϣͷ */;
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		Result;									/**<ִ�н�� */ 
}KFPC_RSP_TS_ChangeConnectMode;

/**
 * ��ʼ�պ�
 */
typedef struct KFPC_REQ_TS_CollectDTMF
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
	KFPC_DTMFParam		DTMFParam;								/**< �պŲ��� */
	unsigned int        MixCollect;
}KFPC_REQ_TS_CollectDTMF;

typedef struct KFPC_RSP_TS_CollectDTMF 
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		Result;									/**<ִ�н�� */ 
}KFPC_RSP_TS_CollectDTMF;

/**
 * �ֶ�ֹͣ�պ�
 */
typedef struct KFPC_REQ_TS_StopCollectDTMF 
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */	
	unsigned long long	CallID;									/**< ����ID */
}KFPC_REQ_TS_StopCollectDTMF;

typedef struct KFPC_RSP_TS_StopCollectDTMF 
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		Result;									/**<ִ�н�� */ 
}KFPC_RSP_TS_StopCollectDTMF;

/**
 * ����պ���Ϣ��
 */
typedef struct KFPC_TS_EVT_CollectDTMFCompleted			
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		DTMFCount;								/**< DTMF����												*/
	char				DTMF[KFPC_MAX_DTMF_SIZE];				/**< �������飬��C�ַ���									*/
	unsigned int		Result;									/**< �պŽ���ԭ��											*/
}KFPC_TS_EVT_CollectDTMFCompleted;


typedef struct KFPC_REQ_TS_PlayVoice 
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
	KFPC_DTMFParam		DTMFParam;								/**< �պŲ��� */
	char				PlayContent[KFPC_MAX_PLAY_CONTENT];		/**< �������� ���磺FileName:test.wav,TTS:���� ͬʱ���Ŷ��ָ�ʽ����*/
	unsigned int		MixPlay;								/**< ���¼�� */
}KFPC_REQ_TS_PlayVoice;

typedef struct KFPC_RSP_TS_PlayVoice 
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		Result;									/**<ִ�н�� */ 
}KFPC_RSP_TS_PlayVoice;

/** 
 * ֹͣ����
 */
typedef struct KFPC_REQ_TS_StopPlayVoice 
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
	unsigned int        CollectDTMF;							/**< �Ƿ�ֹͣ�պ�*/
}KFPC_REQ_TS_StopPlayVoice;

typedef struct KFPC_RSP_TS_StopPlayVoice 
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		Result;									/**<ִ�н�� */ 
}KFPC_RSP_TS_StopPlayVoice;

/**
 * ��������¼�
 */
typedef struct KFPC_TS_EVT_PlayVoiceCompleted					
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
}KFPC_TS_EVT_PlayVoiceCompleted;


/**
 * ��ʼ¼��
 */
typedef struct KFPC_REQ_TS_StartRecordFile
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		TermgChar;	                            /**< ֹͣ¼��������*/
	char				FileName[KFPC_MAX_FILE_NAME];			/**< �ļ���	*/
	unsigned int		RecordTime;								/**< ¼��ʱ�䳤����λΪ�� */
	unsigned int		MixRecord;								/**< ���¼�� */
}KFPC_REQ_TS_StartRecordFile;

typedef struct KFPC_RSP_TS_StartRecordFile
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		Result;									/**<ִ�н�� */ 
}KFPC_RSP_TS_StartRecordFile;

/**
 * ֹͣ¼��
 */
typedef struct KFPC_REQ_TS_StopRecordFile
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */				
}KFPC_REQ_TS_StopRecordFile;

typedef struct KFPC_RSP_TS_StopRecordFile
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */							
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		Result;									/**<ִ�н�� */ 
}KFPC_RSP_TS_StopRecordFile;

/**
 * ¼������¼�
 */
typedef struct KFPC_TS_EVT_RecordFileCompleted				
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
}KFPC_TS_EVT_RecordFileCompleted;

///**
// * �Ի��鲥�ŵ����ļ�
// */
//typedef struct KFPC_REQ_TS_ConfPlayVoice 
//{
//	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
//	unsigned long long	ConfID;									/**< ����ID */
//	char				PlayContent[KFPC_MAX_PLAY_CONTENT];		/**< �������� ���磺ID:123,FileName:test.wav,TTS:���� ͬʱ���Ŷ��ָ�ʽ����*/
//}KFPC_REQ_TS_ConfPlayVoice;
//
//typedef struct KFPC_RSP_TS_ConfPlayVoice 
//{
//	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
//	unsigned long long	ConfID;									/**< ����ID */
//	unsigned int		Result;									/**<ִ�н�� */ 
//}KFPC_RSP_TS_ConfPlayVoice;
//
///**
// * ����ֹͣ����
// */
//typedef struct KFPC_REQ_TS_ConfStopPlayVoice 
//{
//	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
//	unsigned long long	ConfID;									/**< ����ID */
//}KFPC_REQ_TS_ConfStopPlayVoice;
//
//typedef struct KFPC_RSP_TS_ConfStopPlayVoice 
//{
//	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
//	unsigned long long	ConfID;									/**< ����ID */
//	unsigned int		Result;									/**<ִ�н�� */ 
//}KFPC_RSP_TS_ConfStopPlayVoice;
//
///**
// * �����������¼�
// */
//typedef struct KFPC_TS_EVT_ConfPlayVoiceCompleted			
//{
//	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */		
//	unsigned long long	ConfID;									/**< ����ID */
//}KFPC_TS_EVT_ConfPlayVoiceCompleted;
//
//
///**
// * ����¼��
// */
//typedef struct KFPC_REQ_TS_ConfStartRecordFile
//{
//	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
//	unsigned long long	ConfID;									/**< ����ID */
//	char				FileName[KFPC_MAX_FILE_NAME];			/**< �ļ���	*/
//	unsigned int		RecordTime;								/**< ¼��ʱ�䳤����λΪ��	*/
//}KFPC_REQ_TS_ConfStartRecordFile;
//
//typedef struct KFPC_RSP_TS_ConfStartRecordFile
//{
//	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
//	unsigned long long	ConfID;									/**< ����ID */
//	unsigned int		Result;									/**<ִ�н�� */ 
//}KFPC_RSP_TS_ConfStartRecordFile;
//
///**
// * ����ֹͣ¼��
// */
//typedef struct KFPC_REQ_TS_ConfStopRecordFile
//{
//	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
//	unsigned long long	ConfID;									/**< ����ID */
//}KFPC_REQ_TS_ConfStopRecordFile;
//
//typedef struct KFPC_RSP_TS_ConfStopRecordFile
//{
//	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */				
//	unsigned long long	ConfID;									/**< ����ID */
//	unsigned int		Result;									/**<ִ�н�� */ 
//}KFPC_RSP_TS_ConfStopRecordFile;
//
///**
// * ����¼������¼�
// */
//typedef struct KFPC_TS_EVT_ConfRecordFileCompleted			
//{
//	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */		
//	unsigned long long	ConfID;									/**< ����ID */
//}KFPC_TS_EVT_ConfRecordFileCompleted;

/**
 * ��ʼ���մ���
 */
typedef struct KFPC_REQ_TS_RecvFax 
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
	char				FileName[KFPC_MAX_FILE_NAME];			/**< �ļ���	*/
}KFPC_REQ_TS_RecvFax;

typedef struct KFPC_RSP_TS_RecvFax 
{
	KFPC_MSG_HEADER		Header;										/**< ��Ϣͷ */			
	unsigned long long	CallID;										/**< ����ID */
	unsigned int		Result;										/**< ���ؽ�� */
}KFPC_RSP_TS_RecvFax;

/**
 * ֹͣ���մ���
 */
typedef struct KFPC_REQ_TS_StopReceiveFax 
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
}KFPC_REQ_TS_StopReceiveFax;

typedef struct KFPC_RSP_TS_StopReceiveFax 
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		Result;									/**< ���ؽ�� */
}KFPC_RSP_TS_StopReceiveFax;

/**
 * ���մ�������¼�
 */
typedef struct KFPC_TS_EVT_ReceiveFaxCompleted				
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */				
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		Result;									/**< ���ؽ�� */
	unsigned int		PageCount;
}KFPC_TS_EVT_ReceiveFaxCompleted;	

/**
 * ��ʼ���ʹ���
 */
typedef struct KFPC_REQ_TS_StartSendFax 
{
	KFPC_MSG_HEADER		Header;										/**< ��Ϣͷ */
	unsigned long long	CallID;										/**< ����ID */
	char				FileName[KFPC_MAX_FILE_NAME];				/**< �����ļ���	*/
	char				SenderIdent[KFPC_MAX_FAX_INFO];				/**<������ID*/	
	char				SubAddress[KFPC_MAX_FAX_INFO];				/**<��ַ			Ĭ�ϣ�*/
	char				PageHeaderInfo[KFPC_MAX_FAX_INFO];			/**<ҳͷ��Ϣ		Ĭ�ϣ�*/
	char				Identifier[KFPC_MAX_FAX_INFO];				/**<����ID		Ĭ�ϣ�*/
}KFPC_REQ_TS_StartSendFax;

typedef struct KFPC_RSP_TS_StartSendFax
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		Result;									/**< ���ؽ�� */
}KFPC_RSP_TS_StartSendFax;

/**
 * ֹͣ���ʹ���
 */
typedef struct KFPC_REQ_TS_StopSendFax 
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;									/**< ����ID */
}KFPC_REQ_TS_StopSendFax;


typedef struct KFPC_RSP_TS_StopSendFax 
{
	KFPC_MSG_HEADER Header;										/**< ��Ϣͷ */			
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		Result;									/**< ���ؽ�� */
}KFPC_RSP_TS_StopSendFax;


/**
 * ���ʹ������
 */
typedef struct KFPC_TS_EVT_SendFaxCompleted					
{
	KFPC_MSG_HEADER Header;										/**< ��Ϣͷ */		
	unsigned long long	CallID;									/**< ����ID */
	unsigned int		Result;									/**< ���ؽ�� */
	unsigned int		PageCount;
}KFPC_TS_EVT_SendFaxCompleted;



/**
 * ���¼���config�ļ�
 */
typedef struct KFPC_REQ_TS_ReloadConfig				
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */				
	//need to define what shall be reloaded

}KFPC_REQ_TS_ReloadConfig;


typedef struct KFPC_RSP_TS_ReloadConfig				
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */				
	unsigned int		Result;									/**< ���ؽ�� */
}KFPC_RSP_TS_ReloadConfig;


/**
 * ͨ��״̬�ı��¼�
 */
typedef struct KFPC_REQ_TS_QueryChStatus 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
}KFPC_REQ_TS_QueryChStatus;

typedef struct KFPC_RSP_TS_QueryChStatus 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	unsigned int		Result;									/**< ���ؽ�� */
}KFPC_RSP_TS_QueryChStatus;


typedef struct KFPC_TS_EVT_UpdateChStatus 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	unsigned int	ChannelCount;							/**< ͨ������ */
	unsigned int	State[KFPC_MAX_CHANNEL];				/**< ͨ��״̬ */
	unsigned int	Channel[KFPC_MAX_CHANNEL];				/**< ͨ���� */	
}KFPC_TS_EVT_ChStateChanged;

typedef struct KFPC_REQ_TS_SetChState 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	unsigned int	ChannelCount;							/**< ͨ������ */
	unsigned int	State[KFPC_MAX_CHANNEL];				/**< ͨ��״̬ */
	unsigned int	Channel[KFPC_MAX_CHANNEL];				/**< ͨ���� */	
}KFPC_REQ_TS_SetChState;


typedef struct KFPC_RSP_TS_SetChState 
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned int		Result;									/**< ���ؽ�� */
}KFPC_RSP_TS_SetChState;

/**
* �����¼�
*/
typedef struct KFPC_REQ_TS_CoreDump 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
}KFPC_REQ_TS_CoreDump;


typedef struct KFPC_RSP_TS_CoreDump
{
	KFPC_MSG_HEADER		Header;									/**< ��Ϣͷ */
	unsigned int		Result;									/**< ���ؽ�� */
}KFPC_RSP_TS_CoreDump;

typedef struct KFPC_TS_EVT_AlarmEvent 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	unsigned int	AlarmID;								/**< �澯ID */
	char			AlarmContent[KFPC_MAX_ALARM_CONTENT];	/**< �澯���� */
}KFPC_TS_EVT_AlarmEvent;


typedef struct KFPC_REQ_TS_WatchTrunkGroup
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	char			TrunkGroup[KFPC_TRUNKGROUP_NAME_LEN];	/**< �м����� */

}KFPC_REQ_TS_WatchTrunkGroup;

typedef struct KFPC_RSP_TS_WatchTrunkGroup 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	char			TrunkGroup[KFPC_TRUNKGROUP_NAME_LEN];	/**< �м����� */
	unsigned int	Result;									/**< ���ؽ�� */
}KFPC_RSP_TS_WatchTrunkGroup;


typedef struct KFPC_REQ_TS_CancelWatchTrunkGroup 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	char			TrunkGroup[KFPC_TRUNKGROUP_NAME_LEN];	/**< �м����� */
}KFPC_REQ_TS_CancelWatchTrunkGroup;

typedef struct KFPC_RSP_TS_CancelWatchTrunkGroup 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	char			TrunkGroup[KFPC_TRUNKGROUP_NAME_LEN];	/**< �м����� */
	unsigned int	Result;									/**< ���ؽ�� */
}KFPC_RSP_TS_CancelWatchTrunkGroup;



typedef struct KFPC_REQ_TS_QueryTrunkGroup 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
}KFPC_REQ_TS_QueryTrunkGroup;

typedef struct KFPC_RSP_TS_QueryTrunkGroup 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	unsigned int	Result;									/**< ���ؽ�� */
}KFPC_RSP_TS_QueryTrunkGroup;

typedef struct KFPC_TS_EVT_UpdateTrunkGroup 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	char			TrunkGroup[KFPC_TRUNKGROUP_NAME_LEN];	/**< �м����� */
}KFPC_TS_EVT_UpdateTrunkGroup;

typedef struct KFPC_REQ_TS_MonitorChStatus 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
}KFPC_REQ_TS_MonitorChStatus;

typedef struct KFPC_RSP_TS_MonitorChStatus 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	unsigned int	Result;									/**< ���ؽ�� */
}KFPC_RSP_TS_MonitorChStatus;

typedef struct KFPC_REQ_TS_WatchNumStatus 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	char			CallerNO[KFPC_MAX_NUMBER_SIZE];			/**< ���к��� */
}KFPC_REQ_TS_WatchNumStatus;

typedef struct KFPC_RSP_TS_WatchNumStatus 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	unsigned int	Result;									/**< ���ؽ�� */
}KFPC_RSP_TS_WatchNumStatus;

typedef struct KFPC_TS_EVT_WatchNumStatus 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	char			CallerNO[KFPC_MAX_NUMBER_SIZE];			/**< ���к��� */
	unsigned int	State;									/**< ͨ��״̬ */
	unsigned int	Channel;								/**< ͨ���� */	
}KFPC_TS_EVT_WatchNumStatus;

typedef struct KFPC_REQ_TS_PlayDTMF 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	char			DTMF[KFPC_MAX_DTMF_SIZE];			    /**< Ҫ������DTMF */
	unsigned long long	CallID;	                            /**<  ����ID*/
}KFPC_REQ_TS_PlayDTMF;

typedef struct KFPC_RSP_TS_PlayDTMF 
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;	                            /**<  ����ID*/
	unsigned int	Result;									/**< ���ؽ�� */
}KFPC_RSP_TS_PlayDTMF;

typedef struct KFPC_TS_EVT_HookFlash
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;	                            /**<  ����ID*/
}KFPC_TS_EVT_HookFlash;

typedef struct KFPC_TS_EVT_ExtNum2CCS
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	unsigned int	Flag;									/**< 0Ϊɾ����1Ϊ���*/
	char			ExtNum[KFPC_MAX_NUMBER_SIZE];			/**< ���к��� */
	unsigned int	CCS;
}KFPC_TS_EVT_ExtNum2CCS;

typedef struct KFPC_TS_EVT_PassAnswerCall
{
	KFPC_MSG_HEADER Header;									/**< ��Ϣͷ */
	unsigned long long	CallID;								/**< ����ID */
}KFPC_TS_EVT_PassAnswerCall;


#endif // kfpc_tserver_api_h__
