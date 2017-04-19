#ifndef KFPC_TServerAPIHandler_h__
#define KFPC_TServerAPIHandler_h__
#include "kfpc_tserver_api.h"

#include "KFPC_TServerAPIPack.h"
class KFPC_TServerAPIHandler :
	public KFPC_TServerAPIPack
{
private:
	typedef void (KFPC_TServerAPIHandler::*MessageProcFun)(KFPC_MSG_HEADER* pMsg);

	MessageProcFun m_MsgProcFunMap[KFPC_MAX_MSG_ID_TS];	

	void RecvTS_GetTSVersion(KFPC_MSG_HEADER* pMsg);
	void RecvTS_AcceptCall(KFPC_MSG_HEADER* pMsg);
	void RecvTS_AnswerCall(KFPC_MSG_HEADER* pMsg);
	void RecvTS_ReleaseCall(KFPC_MSG_HEADER* pMsg);
	void RecvTS_CallOut(KFPC_MSG_HEADER* pMsg);
	void RecvTS_EVT_IncomingCall(KFPC_MSG_HEADER* pMsg);
	void RecvTS_EVT_AlertCall(KFPC_MSG_HEADER* pMsg);
	void RecvTS_EVT_AnsweredCall(KFPC_MSG_HEADER* pMsg);
	void RecvTS_EVT_ReleasedCall(KFPC_MSG_HEADER* pMsg);
	void RecvTS_Connect(KFPC_MSG_HEADER* pMsg);
	void RecvTS_Disconnect(KFPC_MSG_HEADER* pMsg);
	void RecvTS_CreateConference(KFPC_MSG_HEADER* pMsg);
	void RecvTS_FreeConference(KFPC_MSG_HEADER* pMsg);
	void RecvTS_JoinConference(KFPC_MSG_HEADER* pMsg);
	void RecvTS_LeaveConference(KFPC_MSG_HEADER* pMsg);
	void RecvTS_ChangeConnectMode(KFPC_MSG_HEADER* pMsg);
	void RecvTS_CollectDTMF(KFPC_MSG_HEADER* pMsg);
	void RecvTS_StopCollectDTMF(KFPC_MSG_HEADER* pMsg);
	void RecvTS_EVT_CollectDTMFCompleted(KFPC_MSG_HEADER* pMsg);
	void RecvTS_PlayVoice(KFPC_MSG_HEADER* pMsg);
	void RecvTS_StopPlayVoice(KFPC_MSG_HEADER* pMsg);
	void RecvTS_EVT_PlayVoiceCompleted(KFPC_MSG_HEADER* pMsg);
	void RecvTS_RecordFile(KFPC_MSG_HEADER* pMsg);
	void RecvTS_StopRecordFile(KFPC_MSG_HEADER* pMsg);
	void RecvTS_EVT_RecordFileCompleted(KFPC_MSG_HEADER* pMsg);
	void RecvTS_SendFax(KFPC_MSG_HEADER* pMsg);
	void RecvTS_StopSendFax(KFPC_MSG_HEADER* pMsg);
	void RecvTS_EVT_SendFaxCompleted(KFPC_MSG_HEADER* pMsg);
	void RecvTS_RecvFax(KFPC_MSG_HEADER* pMsg);
	void RecvTS_StopRecvFax(KFPC_MSG_HEADER* pMsg);
	void RecvTS_EVT_RecvFaxCompleted(KFPC_MSG_HEADER* pMsg);
	void RecvTS_ReloadCfg(KFPC_MSG_HEADER* pMsg);
	void RecvTS_QueryChStatus(KFPC_MSG_HEADER* pMsg);
	void RecvTS_UpdateChStatus(KFPC_MSG_HEADER* pMsg);
	void RecvTS_SetChStatus(KFPC_MSG_HEADER* pMsg);
	void RecvTS_CoreDump(KFPC_MSG_HEADER* pMsg);
	void RecvTS_EVT_Alarm(KFPC_MSG_HEADER* pMsg);
	void RecvTS_WatchTrunkGroup(KFPC_MSG_HEADER* pMsg);
	void RecvTS_CancelWatchTrunkGroup(KFPC_MSG_HEADER* pMsg);
	void RecvTS_QueryTrunkGroup(KFPC_MSG_HEADER* pMsg);
	void RecvTS_EVT_UpdateTrunkGroup(KFPC_MSG_HEADER* pMsg);
	void RecvTS_MonitorChStatus(KFPC_MSG_HEADER* pMsg);		
	void RecvTS_WatchNumStatus(KFPC_MSG_HEADER* pMsg);		
	void RecvTS_EVT_NumStatusUpdate(KFPC_MSG_HEADER* pMsg);	
	void RecvTS_PlayDTMF(KFPC_MSG_HEADER* pMsg);
	void RecvTS_EVT_HookFlash(KFPC_MSG_HEADER* pMsg);
	void RecvTS_EVT_ExtNum2CCS(KFPC_MSG_HEADER* pMsg);
	void RecvTS_EVT_PassAnswerCall(KFPC_MSG_HEADER* pMsg);
	virtual void RecvMsg(KFPC_MSG_HEADER* pMsg);
	
public:
	KFPC_TServerAPIHandler(void);
	virtual ~KFPC_TServerAPIHandler(void);


	virtual void OnREQ_TS_GetTSVersion(KFPC_REQ_TS_GetTSVersion* pMsg);
	virtual void OnRSP_TS_GetTSVersion(KFPC_RSP_TS_GetTSVersion* pMsg);

	virtual void OnREQ_TS_AcceptCall(KFPC_REQ_TS_AcceptCall* pMsg){}
	virtual void OnRSP_TS_AcceptCall(KFPC_RSP_TS_AcceptCall* pMsg){}

	virtual void OnREQ_TS_AnswerCall(KFPC_REQ_TS_AnswerCall* pMsg){}
	virtual void OnRSP_TS_AnswerCall(KFPC_RSP_TS_AnswerCall* pMsg){}

	virtual void OnREQ_TS_ReleaseCall(KFPC_REQ_TS_ReleaseCall* pMsg){}
	virtual void OnRSP_TS_ReleaseCall(KFPC_RSP_TS_ReleaseCall* pMsg){}

	virtual void OnREQ_TS_CallOut(KFPC_REQ_TS_CallOut* pMsg){}	
	virtual void OnRSP_TS_CallOut(KFPC_RSP_TS_CallOut* pMsg){}

	virtual void OnTS_EVT_IncomingCall(KFPC_TS_EVT_IncomingCall* pMsg){}
	virtual void OnTS_EVT_AlertCall(KFPC_TS_EVT_AlertCall* pMsg){}
	virtual void OnTS_EVT_AnsweredCall(KFPC_TS_EVT_AnsweredCall* pMsg){}
	virtual void OnTS_EVT_ReleasedCall(KFPC_TS_EVT_ReleasedCall* pMsg){}


	virtual void OnREQ_TS_Connect(KFPC_REQ_TS_Connect* pMsg){}
	virtual void OnRSP_TS_Connect(KFPC_RSP_TS_Connect* pMsg){}

	virtual void OnREQ_TS_Disconnect(KFPC_REQ_TS_Disconnect* pMsg){}
	virtual void OnRSP_TS_Disconnect(KFPC_RSP_TS_Disconnect* pMsg){}
	
	virtual void OnREQ_TS_CreateConference(KFPC_REQ_TS_CreateConference* pMsg){}
	virtual void OnRSP_TS_CreateConference(KFPC_RSP_TS_CreateConference* pMsg){}

	virtual void OnREQ_TS_FreeConference(KFPC_REQ_TS_FreeConference* pMsg){}
	virtual void OnRSP_TS_FreeConference(KFPC_RSP_TS_FreeConference* pMsg){}

	virtual void OnREQ_TS_JoinConference(KFPC_REQ_TS_JoinConference* pMsg){}
	virtual void OnRSP_TS_JoinConference(KFPC_RSP_TS_JoinConference* pMsg){}

	virtual void OnREQ_TS_LeaveConference(KFPC_REQ_TS_LeaveConference* pMsg){}
	virtual void OnRSP_TS_LeaveConference(KFPC_RSP_TS_LeaveConference* pMsg){}

	virtual void OnREQ_TS_ChangeConnectMode(KFPC_REQ_TS_ChangeConnectMode* pMsg){}
	virtual void OnRSP_TS_ChangeConnectMode(KFPC_RSP_TS_ChangeConnectMode* pMsg){}

	virtual void OnREQ_TS_CollectDTMF(KFPC_REQ_TS_CollectDTMF* pMsg){}
	virtual void OnRSP_TS_CollectDTMF(KFPC_RSP_TS_CollectDTMF* pMsg){}

	virtual void OnREQ_TS_StopCollectDTMF(KFPC_REQ_TS_StopCollectDTMF* pMsg){}
	virtual void OnRSP_TS_StopCollectDTMF(KFPC_RSP_TS_StopCollectDTMF* pMsg){}

	virtual void OnTS_EVT_CollectDTMFCompleted(KFPC_TS_EVT_CollectDTMFCompleted* pMsg){}

	virtual void OnREQ_TS_PlayVoice(KFPC_REQ_TS_PlayVoice* pMsg){}
	virtual void OnRSP_TS_PlayVoice(KFPC_RSP_TS_PlayVoice* pMsg){}

	virtual void OnREQ_TS_StopPlayVoice(KFPC_REQ_TS_StopPlayVoice* pMsg){}
	virtual void OnRSP_TS_StopPlayVoice(KFPC_RSP_TS_StopPlayVoice* pMsg){}

	virtual void OnTS_EVT_PlayVoiceCompleted(KFPC_TS_EVT_PlayVoiceCompleted* pMsg){}

	virtual void OnReq_TS_RecordFile(KFPC_REQ_TS_StartRecordFile* pMsg){}
	virtual void OnRSP_TS_RecordFile(KFPC_RSP_TS_StartRecordFile* pMsg){}

	virtual void OnREQ_TS_StopRecordFile(KFPC_REQ_TS_StopRecordFile* pMsg){}
	virtual void OnRSP_TS_StopRecordFile(KFPC_RSP_TS_StopRecordFile* pMsg){}

	virtual void OnTS_EVT_RecordFileCompleted(KFPC_TS_EVT_RecordFileCompleted* pMsg){}

	virtual void OnREQ_TS_RecvFax(KFPC_REQ_TS_RecvFax* pMsg){}
	virtual void OnRSP_TS_RecvFax(KFPC_RSP_TS_RecvFax* pMsg){}

	virtual void OnREQ_TS_StopReceiveFax(KFPC_REQ_TS_StopReceiveFax* pMsg){}
	virtual void OnRSP_TS_StopReceiveFax(KFPC_RSP_TS_StopReceiveFax* pMsg){}

	virtual void OnTS_EVT_ReceiveFaxCompleted(KFPC_TS_EVT_ReceiveFaxCompleted* pMsg){}

	virtual void OnREQ_TS_StartSendFax(KFPC_REQ_TS_StartSendFax* pMsg){}
	virtual void OnRSP_TS_StartSendFax(KFPC_RSP_TS_StartSendFax* pMsg){}

	virtual void OnREQ_TS_StopSendFax(KFPC_REQ_TS_StopSendFax* pMsg){}
	virtual void OnRSP_TS_StopSendFax(KFPC_RSP_TS_StopSendFax* pMsg){}
	
	virtual void OnTS_EVT_SendFaxCompleted(KFPC_TS_EVT_SendFaxCompleted* pMsg){}

	virtual void OnREQ_TS_ReloadConfig(KFPC_REQ_TS_ReloadConfig* pMsg){}
	virtual void OnRSP_TS_ReloadConfig(KFPC_RSP_TS_ReloadConfig* pMsg){}

	virtual void OnREQ_TS_QueryChStatus(KFPC_REQ_TS_QueryChStatus* pMsg){}
	virtual void OnRSP_TS_QueryChStatus(KFPC_RSP_TS_QueryChStatus* pMsg){}
	
	virtual void OnTS_EVT_UpdateChStatus(KFPC_TS_EVT_UpdateChStatus* pMsg){}

	virtual void OnREQ_TS_SetChState(KFPC_REQ_TS_SetChState* pMsg){}
	virtual void OnRSP_TS_SetChState(KFPC_RSP_TS_SetChState* pMsg){}

	virtual void OnREQ_TS_CoreDump(KFPC_REQ_TS_CoreDump* pMsg){}
	virtual void OnRSP_TS_CoreDump(KFPC_RSP_TS_CoreDump* pMsg){}

	virtual void OnTS_EVT_AlarmEvent(KFPC_TS_EVT_AlarmEvent* pMsg){}

	virtual void OnREQ_TS_WatchTrunkGroup(KFPC_REQ_TS_WatchTrunkGroup* pMsg){}
	virtual void OnRSP_TS_WatchTrunkGroup(KFPC_RSP_TS_WatchTrunkGroup* pMsg){}

	virtual void OnREQ_TS_CancelWatchTrunkGroup(KFPC_REQ_TS_CancelWatchTrunkGroup* pMsg){}
	virtual void OnRSP_TS_CancelWatchTrunkGroup(KFPC_RSP_TS_CancelWatchTrunkGroup* pMsg){}

	virtual void OnREQ_TS_QueryTrunkGroup(KFPC_REQ_TS_QueryTrunkGroup* pMsg){}
	virtual void OnRSP_TS_QueryTrunkGroup(KFPC_RSP_TS_QueryTrunkGroup* pMsg){}

	virtual void OnTS_EVT_UpdateTrunkGroup(KFPC_TS_EVT_UpdateTrunkGroup* pMsg){}

	virtual void OnREQ_TS_MonitorChStatus(KFPC_REQ_TS_MonitorChStatus* pMsg){}
	virtual void OnRSP_TS_MonitorChStatus(KFPC_RSP_TS_MonitorChStatus* pMsg){}		

	virtual void OnREQ_TS_PlayDTMF(KFPC_REQ_TS_PlayDTMF* pMsg){}	
	virtual void OnRSP_TS_PlayDTMF(KFPC_RSP_TS_PlayDTMF* pMsg){}

	virtual void OnTS_EVT_HookFlash(KFPC_TS_EVT_HookFlash* pMsg){}

	virtual void OnTS_EVT_ExtNum2CCS(KFPC_TS_EVT_ExtNum2CCS* pMsg){}
	virtual void OnTS_EVT_PassAnswerCall(KFPC_TS_EVT_PassAnswerCall* pMsg){}

	//virtual void OnREQ_TS_WatchNumStatus(KFPC_REQ_TS_WatchNumStatus* pMsg){}	
	//virtual void OnRSP_TS_WatchNumStatus(KFPC_RSP_TS_WatchNumStatus* pMsg){}

	//virtual void OnTS_EVT_NumStatusUpdate(KFPC_TS_EVT_WatchNumStatus* pMsg){}

};

#endif // KFPC_TServerAPIHandler_h__
