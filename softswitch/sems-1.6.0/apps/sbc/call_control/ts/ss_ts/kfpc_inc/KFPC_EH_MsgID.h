#ifndef KFPC_EH_MSGID_H
#define KFPC_EH_MSGID_H


#include "kfpc_id.h"

#define	KFPC_MSG_ID_EH_NULL								KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x00)		/**< 空命令 */
#define	KFPC_MSG_ID_EH_AcceptCall						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x01)		/**< 接受呼叫(用于呼入) */
#define	KFPC_MSG_ID_EH_AnswerCall						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x02)		/**< 应答呼叫(用于呼入) */
#define	KFPC_MSG_ID_EH_ReleaseCall						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x03)		/**< 释放呼叫(包括主、被叫) */
#define	KFPC_MSG_ID_EH_CallOut							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x04)		/**< 外呼 */
#define	KFPC_MSG_ID_EH_EVT_IncomingCall					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x05)		/**< 呼叫入线 */
#define	KFPC_MSG_ID_EH_EVT_AlertCall					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x06)		/**< 呼出对方响铃，这个事件在叠代收发送被叫号时起用。 */
#define	KFPC_MSG_ID_EH_EVT_AnsweredCall					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x07)		/**< 呼出后对方应答事件 */
#define	KFPC_MSG_ID_EH_EVT_ReleasedCall					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x08)		/**< 呼叫释放 */
#define	KFPC_MSG_ID_EH_Connect							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x09)
#define	KFPC_MSG_ID_EH_Disconnect						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x0a)
#define	KFPC_MSG_ID_EH_CreateConference					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x0b)
#define	KFPC_MSG_ID_EH_FreeConference					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x0c)
#define	KFPC_MSG_ID_EH_JoinConference					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x0d)
#define	KFPC_MSG_ID_EH_LeaveConference					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x0e)
#define	KFPC_MSG_ID_EH_ChangeConnectMode				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x0f)
#define	KFPC_MSG_ID_EH_CollectDTMF						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x10)
#define	KFPC_MSG_ID_EH_StopCollectDTMF					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x11)
#define	KFPC_MSG_ID_EH_EVT_CollectDTMFCompleted			KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x12)
#define	KFPC_MSG_ID_EH_PlayVoice						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x13)
#define	KFPC_MSG_ID_EH_StopPlayVoice					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x14)
#define	KFPC_MSG_ID_EH_EVT_PlayVoiceCompleted			KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x15)
#define	KFPC_MSG_ID_EH_RecordFile						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x16)
#define	KFPC_MSG_ID_EH_StopRecordFile					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x17)
#define	KFPC_MSG_ID_EH_EVT_RecordFileCompleted			KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x18)
#define	KFPC_MSG_ID_EH_ConfPlayVoice					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x19)
#define	KFPC_MSG_ID_EH_StopConfPlayVoice				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x1a)
#define	KFPC_MSG_ID_EH_EVT_ConfPlayFileCompleted		KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x1b)
#define	KFPC_MSG_ID_EH_ConfRecordFile					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x1c)
#define	KFPC_MSG_ID_EH_StopConfRecordFile				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x1d)
#define	KFPC_MSG_ID_EH_EVT_ConfRecordFileCompleted		KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x1e)
#define	KFPC_MSG_ID_EH_SendFax							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x1f)
#define	KFPC_MSG_ID_EH_StopSendFax						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x20)
#define	KFPC_MSG_ID_EH_EVT_SendFaxCompleted				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x21)	
#define	KFPC_MSG_ID_EH_RecvFax							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x22)
#define	KFPC_MSG_ID_EH_StopRecvFax						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x23)
#define	KFPC_MSG_ID_EH_EVT_RecvFaxCompleted				KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x24)
#define KFPC_MSG_ID_EH_StartMedia						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x25)
#define KFPC_MSG_ID_EH_Voice2Fax						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x26)
//#define KFPC_MSG_ID_EH_PlayDTMF							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x27)
#define KFPC_MSG_ID_EH_EVT_HookFlash					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x27)
#define KFPC_MSG_ID_EH_EVT_MoreInfo						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x28)
#define KFPC_MSG_ID_EH_SendMoreInfo						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x29)
#define KFPC_MSG_ID_EH_EVT_ReqMoreinfo					KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x2a)
#define KFPC_MSG_ID_EH_EVT_Dial							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x2b)
#define KFPC_MSG_ID_EH_StopMedia						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x2c)
#define KFPC_MSG_ID_EH_Timer							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_EH, 0x2d)

#ifdef __cplusplus
extern "C" 
{
#endif
const char* EHMsgIDToStr(unsigned int MsgID);


#ifdef __cplusplus
}  /* end extern "C" */
#endif


#endif



































