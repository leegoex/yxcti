#pragma once
#include "KFPC_TServerAPIHandler.h"
#include "KFPC_TServerAPIHandlerImp.h"
class KFPC_Channel;

class KFPC_TServerAPIHandlerImp :
	public KFPC_TServerAPIHandler
{
private:
	//unsigned int CheckCallID( unsigned long long& CallID,KFPC_Channel** ppCh );

	virtual void OnREQ_TS_AcceptCall(KFPC_REQ_TS_AcceptCall* pMsg);

	virtual void OnREQ_TS_AnswerCall(KFPC_REQ_TS_AnswerCall* pMsg);

	
	virtual void OnREQ_TS_ReleaseCall(KFPC_REQ_TS_ReleaseCall* pMsg);

	virtual void OnREQ_TS_CallOut(KFPC_REQ_TS_CallOut* pMsg);	

	virtual void OnREQ_TS_Connect(KFPC_REQ_TS_Connect* pMsg);

	virtual void OnREQ_TS_Disconnect(KFPC_REQ_TS_Disconnect* pMsg);
	
	virtual void OnREQ_TS_CreateConference(KFPC_REQ_TS_CreateConference* pMsg);

	virtual void OnREQ_TS_FreeConference(KFPC_REQ_TS_FreeConference* pMsg);

	virtual void OnREQ_TS_JoinConference(KFPC_REQ_TS_JoinConference* pMsg);

	virtual void OnREQ_TS_LeaveConference(KFPC_REQ_TS_LeaveConference* pMsg);

	virtual void OnREQ_TS_ChangeConnectMode(KFPC_REQ_TS_ChangeConnectMode* pMsg);

	virtual void OnREQ_TS_CollectDTMF(KFPC_REQ_TS_CollectDTMF* pMsg);

	virtual void OnREQ_TS_StopCollectDTMF(KFPC_REQ_TS_StopCollectDTMF* pMsg);

	virtual void OnREQ_TS_PlayVoice(KFPC_REQ_TS_PlayVoice* pMsg);

	virtual void OnREQ_TS_StopPlayVoice(KFPC_REQ_TS_StopPlayVoice* pMsg);

	virtual void OnReq_TS_RecordFile(KFPC_REQ_TS_StartRecordFile* pMsg);

	virtual void OnREQ_TS_StopRecordFile(KFPC_REQ_TS_StopRecordFile* pMsg);

	virtual void OnREQ_TS_RecvFax(KFPC_REQ_TS_RecvFax* pMsg);

	virtual void OnREQ_TS_StopReceiveFax(KFPC_REQ_TS_StopReceiveFax* pMsg);
	virtual void OnREQ_TS_StartSendFax(KFPC_REQ_TS_StartSendFax* pMsg);

	virtual void OnREQ_TS_StopSendFax(KFPC_REQ_TS_StopSendFax* pMsg);

	virtual void OnREQ_TS_ReloadConfig(KFPC_REQ_TS_ReloadConfig* pMsg);

	virtual void OnREQ_TS_QueryChStatus(KFPC_REQ_TS_QueryChStatus* pMsg);
	
	virtual void OnTS_EVT_UpdateChStatus(KFPC_TS_EVT_UpdateChStatus* pMsg);

	virtual void OnREQ_TS_SetChState(KFPC_REQ_TS_SetChState* pMsg);

	virtual void OnREQ_TS_CoreDump(KFPC_REQ_TS_CoreDump* pMsg);

	virtual void OnREQ_TS_WatchTrunkGroup(KFPC_REQ_TS_WatchTrunkGroup* pMsg);

	virtual void OnREQ_TS_CancelWatchTrunkGroup(KFPC_REQ_TS_CancelWatchTrunkGroup* pMsg);

	virtual void OnREQ_TS_QueryTrunkGroup(KFPC_REQ_TS_QueryTrunkGroup* pMsg);

	virtual void OnREQ_TS_MonitorChStatus(KFPC_REQ_TS_MonitorChStatus* pMsg);

	//virtual void OnREQ_TS_WatchNumStatus(KFPC_REQ_TS_WatchNumStatus* pMsg);	
	virtual void OnREQ_TS_PlayDTMF(KFPC_REQ_TS_PlayDTMF* pMsg);
	

public:
	KFPC_TServerAPIHandlerImp(void);
	~KFPC_TServerAPIHandlerImp(void);

	static KFPC_TServerAPIHandlerImp* GetInstance()
	{
		static KFPC_TServerAPIHandlerImp TServerAPIHandlerImpInstance;
		return &TServerAPIHandlerImpInstance;
	}
};

#define  KFCPTServerAPIHandlerImpInstance	KFPC_TServerAPIHandlerImp::GetInstance()
