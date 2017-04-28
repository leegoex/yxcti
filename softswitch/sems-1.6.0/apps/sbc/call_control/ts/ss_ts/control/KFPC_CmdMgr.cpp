#include "kfpc_logex.h"
#include "KFPC_CmdMgr.h"
#include "KFPC_Channel.h"
//#include "KFPC_Cmd_EH_ReleaseCall.h"
#include "kfpc_tserver_api.h"
#include "KFPC_TServerErr.h"
#include "KFPC_TServerConfigFile.h"

KFPC_CmdMgr::KFPC_CmdMgr(void)
{
}


KFPC_CmdMgr::~KFPC_CmdMgr(void)
{
}

EH_Cmd_EVT_IncomingCall* KFPC_CmdMgr::Create_Cmd_EVT_IncomingCall( KFPC_Channel* pCh )
{
	//void* pMem = m_KFPC_MemPool.Alloc(sizeof(EH_Cmd_EVT_IncomingCall));

	//EH_Cmd_EVT_IncomingCall* pCmd = new(pMem)EH_Cmd_EVT_IncomingCall(pCh);
	EH_Cmd_EVT_IncomingCall* pCmd = new EH_Cmd_EVT_IncomingCall(pCh->GetCallID(),0,0,0);

	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());

	return pCmd;
}

//
//
//
//KFPC_Cmd_StopPlay* KFPC_CmdMgr::Create_Cmd_StopPlay( KFPC_Channel* pCh,unsigned int DstAppID,unsigned int UserContext1,unsigned int UserContext2,bool SubCmd )
//{
//	KFPC_Cmd_StopPlay* pCmd =new KFPC_Cmd_StopPlay(pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//
//KFPC_Cmd_StopRecord* KFPC_CmdMgr::Create_Cmd_StopRecord( KFPC_Channel* pCh,		
//	unsigned int DstAppID,
//	unsigned int UserContext1,
//	unsigned int UserContext2,
//	bool SubCmd)
//{
//
//	//void* pMem = m_KFPC_MemPool.Alloc(sizeof(KFPC_Cmd_StopRecord),Pool);
//
//	//KFPC_Cmd_StopRecord* pCmd = new(pMem)KFPC_Cmd_StopRecord(pCh);
//	KFPC_Cmd_StopRecord* pCmd =new KFPC_Cmd_StopRecord(pCh->GetCallID(),DstAppID,UserContext1,UserContext2,SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_Disconnect* KFPC_CmdMgr::Create_Cmd_Disconnect( KFPC_Channel* pCh,unsigned int DstAppID,unsigned int UserContext1,unsigned int UserContext2,bool SubCmd,bool MonitorIVR)
//{
//	//void* pMem = m_KFPC_MemPool.Alloc(sizeof(KFPC_Cmd_Disconnect),Pool);
//
//	//KFPC_Cmd_Disconnect* pCmd = new(pMem)KFPC_Cmd_Disconnect(pCh);
//	KFPC_Cmd_Disconnect* pCmd =new KFPC_Cmd_Disconnect(pCh->GetCallID(),
//														UserContext1,
//														UserContext2,
//														DstAppID,
//														MonitorIVR,
//														SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_CmdSet_ReleaseCall* KFPC_CmdMgr::Create_CmdSet_ReleaseCall( KFPC_Channel* pCh,unsigned int Cause,unsigned int AppID,unsigned int UserContext1,unsigned int UserContext2 )
//{
//	//void* pMem = m_KFPC_MemPool.Alloc(sizeof(KFPC_CmdSet_ReleaseCall));
//
//	//KFPC_CmdSet_ReleaseCall* pCmd = new(pMem)KFPC_CmdSet_ReleaseCall(pCh,																
//	//															pReleaseCall->Cause,
//	//															pReleaseCall->Header.un32SrcAPPId,
//	//															pReleaseCall->Header.un32UserContext1,
//	//															pReleaseCall->Header.un32UserContext2,
//	//															&m_KFPC_MemPool);
//
//
//	KFPC_CmdSet_ReleaseCall* pCmd = new KFPC_CmdSet_ReleaseCall(Cause,
//		pCh->GetCallID(),																		
//		AppID,
//		UserContext1,
//		UserContext2);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_ReleaseCall* KFPC_CmdMgr::Create_Cmd_ReleaseCall( KFPC_Channel* pCh,unsigned int Cause,unsigned int AppID,unsigned int UserContext1,unsigned int UserContext2,bool SubCmd)
//{
//	//void* pMem = m_KFPC_MemPool.Alloc(sizeof(KFPC_Cmd_ReleaseCall),Pool);
//
//	//KFPC_Cmd_ReleaseCall* pCmd = new(pMem)KFPC_Cmd_ReleaseCall(pCh,																
//	//	Cause,
//	//	AppID,
//	//	UserContext1,
//	//	UserContext2,
//	//	&m_KFPC_MemPool);
//
//	KFPC_Cmd_ReleaseCall* pCmd =new KFPC_Cmd_ReleaseCall(
//		Cause,
//		pCh->GetCallID(),
//		
//		AppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_AnswerCall* KFPC_CmdMgr::Create_Cmd_AnswerCall(KFPC_Channel* pCh,unsigned int AppID,unsigned int UserContext1,unsigned int UserContext2)
//{
//	KFPC_Cmd_AnswerCall* pCmd =new KFPC_Cmd_AnswerCall(pCh->GetCallID(),
//		AppID,
//		UserContext1,
//		UserContext2);
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//
//KFPC_Cmd_PlayVoice* KFPC_CmdMgr::Create_Cmd_PlayVoice(KFPC_Channel* pCh,unsigned int AppID,unsigned int UserContext1,
//	unsigned int UserContext2, char* VoiceFile, KFPC_DTMFParam* pDTMFPara,bool SubCmd )
//{
//	KFPC_Cmd_PlayVoice* pCmd =new KFPC_Cmd_PlayVoice(VoiceFile,
//		pDTMFPara,
//		pCh->GetCallID(),
//		AppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_TextToSpeech* KFPC_CmdMgr::Create_Cmd_TextToSpeech(KFPC_Channel* pCh,unsigned int DstAppID, char *pPlayContent,
//												unsigned int& UserContext1, unsigned int& UserContext2,bool SubCmd)
//{
//	KFPC_Cmd_TextToSpeech* pCmd =new KFPC_Cmd_TextToSpeech(pCh->GetCallID(),
//		DstAppID,
//		pPlayContent,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_ConnectToIVR* KFPC_CmdMgr::Create_Cmd_ConnectToIVR(KFPC_Channel* pCh,unsigned int AppID,unsigned int UserContext1,
//	unsigned int UserContext2,
//	bool	MonitorIVR)
//{
//	KFPC_Cmd_ConnectToIVR* pCmd =new KFPC_Cmd_ConnectToIVR(pCh->GetCallID(),	
//		AppID,
//		UserContext1,
//		UserContext2,MonitorIVR);
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//
//KFPC_Cmd_Callout* KFPC_CmdMgr::Create_Cmd_Callout(KFPC_DEVICE& Device,
//	unsigned int DstAppID,
//	unsigned int UserContext1,
//	unsigned int UserContext2,
//	bool SubCmd)
//{
//	KFPC_Cmd_Callout* pCmd =new KFPC_Cmd_Callout(Device,DstAppID,UserContext1,UserContext2,SubCmd);
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(0,"CmdID:%u,CommandMap size:%u.",pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_ChannelInit* KFPC_CmdMgr::Create_Cmd_ChannelInit( KFPC_Channel* pCh,unsigned short Cause,bool SubCmd)
//{
//	KFPC_Cmd_ChannelInit* pCmd = new KFPC_Cmd_ChannelInit(Cause,pCh->GetCallID(),SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//
//KFPC_CmdSet_EVT_ReleasedCall* KFPC_CmdMgr::Create_CmdSet_EVT_ReleasedCall( KFPC_Channel* pCh,unsigned int DstAppID,
//	unsigned int UserContext1,unsigned int UserContext2, unsigned int Cause)
//{
//	//void* pMem = m_KFPC_MemPool.Alloc(sizeof(KFPC_CmdSet_EVT_ReleasedCall),Pool);
//
//	//KFPC_CmdSet_EVT_ReleasedCall* pCmd = new(pMem)KFPC_CmdSet_EVT_ReleasedCall(pCh,Cause);
//
//	KFPC_CmdSet_EVT_ReleasedCall* pCmd = new KFPC_CmdSet_EVT_ReleasedCall(pCh->GetCallID(), DstAppID,
//		 UserContext1, UserContext2,  Cause);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_CmdSet_PlayVoice* KFPC_CmdMgr::Create_CmdSet_PlayVoice(KFPC_Channel* pCh, char* VoiceFile,KFPC_DTMFParam* pDTMFPara,unsigned int DstAppID,
//	unsigned int UserContext1,unsigned int UserContext2,bool SubCmd )
//{
//	KFPC_CmdSet_PlayVoice* pCmd = new KFPC_CmdSet_PlayVoice(VoiceFile,
//															pDTMFPara,
//															pCh,
//															DstAppID,
//															UserContext1,
//															UserContext2,
//															SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_EVT_PlayVoiceCompleted* KFPC_CmdMgr::Create_Cmd_EVT_PlayVoiceCompleted(KFPC_Channel* pCh,unsigned int AppID,
//	unsigned int UserContext1, unsigned int UserContext2)
//{
//	KFPC_Cmd_EVT_PlayVoiceCompleted* pCmd = new KFPC_Cmd_EVT_PlayVoiceCompleted(pCh->GetCallID(),AppID,UserContext1,UserContext2);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}




void KFPC_CmdMgr::ExecuteCmd(KFPC_Channel* pCh, KFPC_BaseCommand* pCmd )
{
	
	if(pCh->GetCmdID() == 0)
	{
		pCh->SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);

		unsigned int Ret = pCmd->Execute2();

		if(KFPC_ERR_CmdWaitAck == Ret)
		{

		}
		else
		{
			KFPC_CmdMgrInstance->FreeCmd(pCmd);
			pCh->SetCmdID(0,PREFIX_EXPRESSION_VALUE);
		}
	}
	else
	{
		pCh->PushCmdID(pCmd->GetID());
	}
}

void KFPC_CmdMgr::CancelCmd(KFPC_Channel* pCh, KFPC_BaseCommand* pCmd )
{
	unsigned int Ret = pCmd->Cancel();

	if(KFPC_ERR_CmdWaitAck == Ret)
	{

	}
	else
	{
		KFPC_CmdMgrInstance->FreeCmd(pCmd);
		pCh->SetCmdID(0,PREFIX_EXPRESSION_VALUE);
	}
}
//
//void KFPC_CmdMgr::DoREQ_TS_AnswerCall(KFPC_Channel* pCh, KFPC_REQ_TS_AnswerCall* pMsg )
//{
//	KFPC_Cmd_AnswerCall* pCmd_AnswerCall = KFPC_CmdMgrInstance->Create_Cmd_AnswerCall(pCh,
//		pMsg->Header.un32SrcAPPId,
//		pMsg->Header.un32UserContext1,
//		pMsg->Header.un32UserContext2);
//
//
//	ExecuteCmd(pCh,pCmd_AnswerCall);
//
//}
//
//void KFPC_CmdMgr::DoREQ_TS_ReleaseCall( KFPC_Channel* pCh,KFPC_REQ_TS_ReleaseCall* pMsg )
//{
//	KFPC_CmdSet_ReleaseCall* pCmd = Create_CmdSet_ReleaseCall(pCh,pMsg->Cause,pMsg->Header.un32SrcAPPId,pMsg->Header.un32UserContext1,pMsg->Header.un32UserContext2);
//
//
//	ExecuteCmd(pCh,pCmd);
//
//}
//
//void KFPC_CmdMgr::DoREQ_TS_CallOut( KFPC_REQ_TS_CallOut* pMsg )
//{
//	unsigned int DesAppID = pMsg->Header.un32SrcAPPId;
//
//	KFPC_Cmd_Callout* pCmd = Create_Cmd_Callout(pMsg->Device,
//		DesAppID,
//		pMsg->Header.un32UserContext1,
//		pMsg->Header.un32UserContext2);
//
//	int Ret = pCmd->Execute(KFPC_MSG_ID_EH_CallOut, KFPC_MSG_TYPE_REQUEST);
//
//	if(KFPC_ERR_CmdWaitAck == Ret)
//	{
//
//	}
//	else
//	{
//		KFPC_CmdMgrInstance->FreeCmd(pCmd);
//	}
//	
//}
//
//void KFPC_CmdMgr::DoREQ_TS_Disconnect( KFPC_Channel* pCh,KFPC_REQ_TS_Disconnect* pMsg )
//{
//	KFPC_Cmd_Disconnect* pCmd = KFPC_CmdMgrInstance->Create_Cmd_Disconnect(pCh,pMsg->Header.un32SrcAPPId,pMsg->Header.un32UserContext1,pMsg->Header.un32UserContext2);
//
//
//	ExecuteCmd(pCh,pCmd);
//
//}
//
//KFPC_Cmd_EH_Evt_AnsweredCall* KFPC_CmdMgr::Create_Cmd_EH_Evt_AnsweredCall( KFPC_Channel* pCh )
//{
//	KFPC_Cmd_EH_Evt_AnsweredCall* pCmd = new KFPC_Cmd_EH_Evt_AnsweredCall(pCh->GetCallID(),
//		pCh->GetDstAppID(),
//		0,0);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//void KFPC_CmdMgr::DoREQ_TS_CreateConference( KFPC_REQ_TS_CreateConference* pMsg )
//{
//	if(pMsg->TserverID != pMsg->Header.un32DstAPPId)
//	{
//		WARNING_LOG(0,"TserverID doesn't match,pMsg->TserverID:%u, Header DstID:%u",
//			pMsg->TserverID,pMsg->Header.un32DstAPPId);
//		return;
//	}
//	KFPC_Cmd_EH_CreateConference* pCmd = KFPC_CmdMgrInstance->Create_Cmd_EH_CreateConference(
//		pMsg->CCSID,
//		pMsg->MaxMember,
//		pMsg->NodeID,
//		pMsg->Header.un32SrcAPPId,
//		pMsg->Header.un32UserContext1,
//		pMsg->Header.un32UserContext2);
//
//	unsigned int Ret = pCmd->Execute2();
//
//	if(KFPC_ERR_CmdWaitAck == Ret)
//	{
//		
//	}
//	else
//	{
//		KFPC_CmdMgrInstance->FreeCmd(pCmd);
//		
//	}
//
//}
//
//KFPC_Cmd_EVT_DigitCollected* KFPC_CmdMgr::Create_Cmd_EH_Evt_DigitCollected( KFPC_Channel* pCh, unsigned int AppID, 
//	unsigned int UserContext1, unsigned int UserContext2,unsigned int DigitCount, char* pDigits )
//{
//	KFPC_Cmd_EVT_DigitCollected* pCmd = new KFPC_Cmd_EVT_DigitCollected(pCh->GetCallID(),AppID,UserContext1,
//		UserContext2,DigitCount,pDigits);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//void KFPC_CmdMgr::DoREQ_TS_PlayVoice(KFPC_Channel* pCh,KFPC_REQ_TS_PlayVoice* pMsg )
//{
//	KFPC_BaseCommand* pCmd = NULL;
//	if(pMsg->MixPlay)
//	{
//		pCmd = Create_CmdSet_MixPlayVoice(pCh,
//			pMsg->PlayContent,
//			&pMsg->DTMFParam,
//			pMsg->Header.un32SrcAPPId,
//			pMsg->Header.un32UserContext1,
//			pMsg->Header.un32UserContext2);
//	}
//	else
//	{
//		pCmd = Create_CmdSet_PlayVoice(pCh,
//			pMsg->PlayContent,
//			&pMsg->DTMFParam,
//			pMsg->Header.un32SrcAPPId,
//			pMsg->Header.un32UserContext1,
//			pMsg->Header.un32UserContext2);
//	}	
//
//
//	ExecuteCmd(pCh,pCmd);
//
//
//}
//
//void KFPC_CmdMgr::DoREQ_TS_StopPlayVoice( KFPC_Channel* pCh,KFPC_REQ_TS_StopPlayVoice* pMsg )
//{
//	KFPC_BaseCommand* pCmd = NULL;
//
//	pCmd = Create_CmdSet_StopPlayVoice(pCh,
//		pMsg->Header.un32SrcAPPId,
//		pMsg->Header.un32UserContext1,
//		pMsg->Header.un32UserContext2,
//		(pMsg->CollectDTMF > 0));
//
//	ExecuteCmd(pCh,pCmd);
//
//}
//
//void KFPC_CmdMgr::DoREQ_TS_CollectDTMF( KFPC_Channel* pCh,KFPC_REQ_TS_CollectDTMF* pMsg )
//{
//	KFPC_BaseCommand* pCmd = NULL;
//	if( 0 == pMsg->MixCollect )
//	{
//		pCmd = Create_CmdSet_CollectDTMF(pCh,
//			&pMsg->DTMFParam,
//			pMsg->Header.un32SrcAPPId,
//			pMsg->Header.un32UserContext1,
//			pMsg->Header.un32UserContext2);
//
//
//	}
//	else
//	{
//		pCmd = Create_CmdSet_MixCollect(pCh,
//			&pMsg->DTMFParam,
//			pMsg->Header.un32SrcAPPId,
//			pMsg->Header.un32UserContext1,
//			pMsg->Header.un32UserContext2);
//	}
//
//
//	ExecuteCmd(pCh,pCmd);
//
//}
//
//KFPC_Cmd_CollectDTMF* KFPC_CmdMgr::Create_Cmd_CollectDTMF( KFPC_Channel* pCh,unsigned int DstAppID, unsigned int UserContext1,unsigned int UserContext2,KFPC_DTMFParam* pDTMFPara,bool SubCmd /*= false*/ )
//{
//	KFPC_Cmd_CollectDTMF* pCmd =new KFPC_Cmd_CollectDTMF(pDTMFPara,
//		pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_CmdSet_CollectDTMF* KFPC_CmdMgr::Create_CmdSet_CollectDTMF( KFPC_Channel* pCh, KFPC_DTMFParam* pDTMFPara,unsigned int DstAppID, unsigned int UserContext1,unsigned int UserContext2,bool SubCmd /*= false*/ )
//{
//	KFPC_CmdSet_CollectDTMF* pCmd = new KFPC_CmdSet_CollectDTMF(
//		pDTMFPara,
//		pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_EH_CreateConference* KFPC_CmdMgr::Create_Cmd_EH_CreateConference( unsigned int& CCSID,
//	unsigned int& MaxMember, 
//	unsigned int& NodeID, 
//	unsigned int& DstAppID, 
//	unsigned int& UserContext1, 
//	unsigned int& UserContext2, 
//	bool SubCmd /*= false*/ )
//{
//	KFPC_Cmd_EH_CreateConference* pCmd = new KFPC_Cmd_EH_CreateConference(CCSID,
//		MaxMember,
//		NodeID,
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(0,"CmdID:%u,CommandMap size:%u.",pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_EH_FreeConference* KFPC_CmdMgr::Create_Cmd_EH_FreeConference( KFPC_Channel* pCh,
//	unsigned int& DstAppID, 
//	unsigned int& UserContext1, 
//	unsigned int& UserContext2, 
//	bool SubCmd /*= false*/ )
//{
//	KFPC_Cmd_EH_FreeConference* pCmd = new KFPC_Cmd_EH_FreeConference(
//		pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(0,"CmdID:%u,CommandMap size:%u.",pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//void KFPC_CmdMgr::DoREQ_TS_FreeConference(KFPC_Channel* pCh, KFPC_REQ_TS_FreeConference* pMsg )
//{
//	KFPC_CmdSet_TS_FreeConf* pCmd = Create_CmdSet_FreeConf(pCh,pMsg->Header.un32SrcAPPId,
//		pMsg->Header.un32UserContext1,
//		pMsg->Header.un32UserContext2);
//
//
//	ExecuteCmd(pCh,pCmd);
//
//}
//
//void KFPC_CmdMgr::DoREQ_TS_StopCollectDTMF( KFPC_Channel* pCh,KFPC_REQ_TS_StopCollectDTMF* pMsg )
//{
//	KFPC_Cmd_StopCollectDTMF* pCmd_StopCollectDFTP = Create_Cmd_StopCollectDTMF(pCh,pMsg->Header.un32SrcAPPId,
//		pMsg->Header.un32UserContext1,
//		pMsg->Header.un32UserContext2);
//
//
//	ExecuteCmd(pCh,pCmd_StopCollectDFTP);
//
//}
//
//KFPC_Cmd_StopCollectDTMF* KFPC_CmdMgr::Create_Cmd_StopCollectDTMF( KFPC_Channel* pCh,unsigned int DstAppID, unsigned int UserContext1, unsigned int UserContext2,bool SubCmd /*= false*/ )
//{
//	KFPC_Cmd_StopCollectDTMF* pCmd =new KFPC_Cmd_StopCollectDTMF(pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//void KFPC_CmdMgr::DoREQ_TS_RecordFile( KFPC_Channel* pCh,KFPC_REQ_TS_StartRecordFile* pMsg )
//{
//	KFPC_BaseCommand* pCmd = NULL;
//	if( 0 == pMsg->MixRecord )
//	{
//		pCmd = Create_CmdSet_RecordFile(pCh,
//			pMsg->FileName,
//			pMsg->RecordTime,
//			pMsg->TermgChar,
//			pMsg->Header.un32SrcAPPId,
//			pMsg->Header.un32UserContext1,
//			pMsg->Header.un32UserContext2);
//
//	}
//	else
//	{
//
//
//		pCmd = Create_CmdSet_MixRecordFile(pCh,
//			pMsg->FileName,
//			pMsg->RecordTime,
//			pMsg->TermgChar,
//			pMsg->Header.un32SrcAPPId,
//			pMsg->Header.un32UserContext1,
//			pMsg->Header.un32UserContext2,
//			pMsg->MixRecord);
//
//	}
//
//
//	ExecuteCmd(pCh,pCmd);
//
//}
//
//KFPC_Cmd_RecordFile* KFPC_CmdMgr::Create_Cmd_RecordFile( KFPC_Channel* pCh,unsigned int AppID,unsigned int UserContext1, unsigned int UserContext2, const char* RecordFile,int RecordTime, unsigned int TermChar,bool SubCmd /*= false*/ )
//{
//	KFPC_Cmd_RecordFile* pCmd =new KFPC_Cmd_RecordFile(RecordFile,
//		TermChar,
//		RecordTime,
//		pCh->GetCallID(),
//		AppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_CmdSet_RecordFile* KFPC_CmdMgr::Create_CmdSet_RecordFile( KFPC_Channel* pCh, 
//	char* RecordFile,
//	int RecordTime,
//	unsigned int TermChar, 
//	unsigned int DstAppID,
//	unsigned int UserContext1,
//	unsigned int UserContext2,
//	bool SubCmd /*= false*/ )
//{
//	KFPC_CmdSet_RecordFile* pCmd = new KFPC_CmdSet_RecordFile(RecordFile,
//		TermChar,
//		RecordTime,
//		pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//			
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_EVT_RecordFileCompleted* KFPC_CmdMgr::Create_Cmd_EVT_RecordFileCompleted( KFPC_Channel* pCh,unsigned int AppID, unsigned int UserContext1, unsigned int UserContext2,const char* pFileName,bool TransformMp3,bool SubCmd /*= false*/ )
//{
//	KFPC_Cmd_EVT_RecordFileCompleted* pCmd = new KFPC_Cmd_EVT_RecordFileCompleted(pCh->GetCallID(),AppID,UserContext1,UserContext2,pFileName,TransformMp3);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//void KFPC_CmdMgr::DoREQ_TS_StopRecordFile( KFPC_Channel* pCh,KFPC_REQ_TS_StopRecordFile* pMsg )
//{
//	KFPC_BaseCommand* pCmd = NULL;
//	/*
//	if(CH_IVRType_MIX == pCh->GetIVRType())
//	{
//		pCmd = Create_CmdSet_StopMixRecord(pCh,		
//			pMsg->Header.un32SrcAPPId,
//			pMsg->Header.un32UserContext1,
//			pMsg->Header.un32UserContext2);
//	}
//	else
//	*/
//	{
//		pCmd = Create_Cmd_StopRecord(pCh,		
//			pMsg->Header.un32SrcAPPId,
//			pMsg->Header.un32UserContext1,
//			pMsg->Header.un32UserContext2);
//	}
//
//
//
//	ExecuteCmd(pCh,pCmd);
//
//}
//
//void KFPC_CmdMgr::DoREQ_TS_JoinConference( KFPC_Channel* pCh,KFPC_Channel* pConfCh,KFPC_REQ_TS_JoinConference* pMsg )
//{
//	KFPC_CmdSet_TS_JoinConf* pCmd = Create_CmdSet_TS_JoinConf(pCh,
//		pConfCh,
//		pMsg->JoinMode,
//		pMsg->DTMFSilence,
//		pMsg->Header.un32SrcAPPId,
//		pMsg->Header.un32UserContext1,
//		pMsg->Header.un32UserContext2,
//		pMsg->StopMedia);
//
//
//
//	ExecuteCmd(pCh,pCmd);
//
//}
//
//void KFPC_CmdMgr::DoREQ_TS_LeaveConference( KFPC_Channel* pCh,KFPC_Channel* pConfCh,KFPC_REQ_TS_LeaveConference* pMsg )
//{
//	KFPC_Cmd_EH_LeaveConference* pCmd = Create_Cmd_LeaveConf(pCh,
//		pConfCh,
//		pMsg->Header.un32SrcAPPId,
//		pMsg->Header.un32UserContext1,
//		pMsg->Header.un32UserContext2);
//
//
//
//	ExecuteCmd(pCh,pCmd);
//
//}
//
//KFPC_Cmd_EH_JoinConference* KFPC_CmdMgr::Create_Cmd_JoinConf( KFPC_Channel* pCh, KFPC_Channel* pConfCh, unsigned int JoinMode, int DTMFSilence, unsigned int AppID, unsigned int UserContext1, unsigned int UserContext2, bool SubCmd /*= false */ )
//{
//	KFPC_Cmd_EH_JoinConference* pCmd = new KFPC_Cmd_EH_JoinConference(pCh->GetCallID(),
//																			pConfCh->GetCallID(),
//																			JoinMode,
//																			DTMFSilence,
//																			AppID,																			
//																			UserContext1,
//																			UserContext2,
//																			SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_EH_LeaveConference* KFPC_CmdMgr::Create_Cmd_LeaveConf( KFPC_Channel* pCh, KFPC_Channel* pConfCh, unsigned int AppID, unsigned int UserContext1, unsigned int UserContext2, bool SubCmd /*= false */ )
//{
//	KFPC_Cmd_EH_LeaveConference* pCmd = new KFPC_Cmd_EH_LeaveConference(pCh->GetCallID(),
//		pConfCh->GetCallID(),
//		AppID,																			
//		UserContext1,
//		UserContext2);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_CmdSet_StopPlayVoice* KFPC_CmdMgr::Create_CmdSet_StopPlayVoice( KFPC_Channel* pCh,unsigned int DstAppID,unsigned int UserContext1,unsigned int UserContext2,bool SubCmd /*= false*/ )
//{
//	KFPC_CmdSet_StopPlayVoice* pCmd = new KFPC_CmdSet_StopPlayVoice(pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_Create3PartyConf* KFPC_CmdMgr::Create_Cmd_Setup3PartyConf( KFPC_Channel* pCh, unsigned int DstAppID, unsigned int UserContext1, unsigned int UserContext2, bool SubCmd /*= false*/ )
//{
//	KFPC_Cmd_Create3PartyConf* pCmd = new KFPC_Cmd_Create3PartyConf(pCh->GetCallID(),
//		DstAppID,																			
//		UserContext1,
//		UserContext2);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//void KFPC_CmdMgr::DoREQ_TS_Connect( KFPC_Channel* pCh,KFPC_Channel* pCh2,KFPC_REQ_TS_Connect* pMsg )
//{
//	KFPC_CmdSet_TS_Connect* pCmd = Create_CmdSet_TS_Connect(pCh,
//		pCh2,
//		pMsg->Header.un32SrcAPPId,
//		pMsg->Header.un32UserContext1,
//		pMsg->Header.un32UserContext2,
//		pMsg->ConnectMode,
//		pMsg->StopMedia);
//
//
//	if(pCh->GetCmdID() == 0 &&
//		pCh2->GetCmdID() == 0)
//	{
//		pCh->SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);
//		pCh2->SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);
//
//		unsigned int Ret = pCmd->Execute2();
//
//		if(KFPC_ERR_CmdWaitAck == Ret)
//		{
//
//		}
//		else
//		{
//
//			KFPC_CmdMgrInstance->FreeCmd(pCmd);				
//
//			pCh->SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			pCh2->SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//		}
//
//	}
//	else
//	{
//		if(pCh->GetCmdID() != 0)
//		{
//			pCh->PushCmdID(pCmd->GetID());
//		}
//		else
//		{
//			pCh->SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);
//		}
//
//		if(pCh2->GetCmdID() != 0)
//		{
//			pCh2->PushCmdID(pCmd->GetID());
//		}
//		else
//		{
//			pCh2->SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);
//		}
//	}
//}
//
//KFPC_CmdSet_MixRecordFile* KFPC_CmdMgr::Create_CmdSet_MixRecordFile( KFPC_Channel* pCh, 
//	char* RecordFile, 
//	int RecordTime, 
//	unsigned int TermChar, 
//	unsigned int DstAppID, 
//	unsigned int UserContext1, 
//	unsigned int UserContext2,
//	unsigned int MixRecord,
//	bool SubCmd /*= false*/ )
//{
//	KFPC_CmdSet_MixRecordFile* pCmd = new KFPC_CmdSet_MixRecordFile(RecordFile,
//		TermChar,
//		RecordTime,
//		pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//	pCmd->SetMixRecord(MixRecord);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//
//KFPC_EH_ConnectToCh* KFPC_CmdMgr::Create_Cmd_ConnectToCh( KFPC_Channel* pCh, 
//	KFPC_Channel* pCh2, 
//	unsigned int DstAppID, 
//	unsigned int UserContext1,
//	unsigned int UserContext2,
//	unsigned char ConnectMode,
//	bool SubCmd /*= false*/ )
//{
//	KFPC_EH_ConnectToCh* pCmd = new KFPC_EH_ConnectToCh(pCh, 
//		pCh2, 
//		DstAppID,																			
//		UserContext1,
//		UserContext2,
//		ConnectMode,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//void KFPC_CmdMgr::DoREQ_TS_StartSendFax( KFPC_Channel* pCh,KFPC_REQ_TS_StartSendFax* pMsg )
//{
//	KFPC_CmdSet_TS_StartSendFax *pCmd_SendFax = Create_CmdSet_StartSendFax(pCh,		
//		pMsg->Header.un32SrcAPPId,
//		pMsg->Header.un32UserContext1,
//		pMsg->Header.un32UserContext2,
//		pMsg->FileName,
//		pMsg->SenderIdent,
//		pMsg->SubAddress,
//		pMsg->PageHeaderInfo,
//		pMsg->Identifier
//		);
//
//
//	ExecuteCmd(pCh,pCmd_SendFax);
//
//}
//
//void KFPC_CmdMgr::DoREQ_TS_StartRecvFax( KFPC_Channel* pCh,KFPC_REQ_TS_RecvFax* pMsg )
//{
//	KFPC_CmdSet_TS_StartRecvFax *pCmd_RecvFax = Create_CmdSet_StartRecvFax(pCh,		
//		pMsg->Header.un32SrcAPPId,
//		pMsg->Header.un32UserContext1,
//		pMsg->Header.un32UserContext2,
//		pMsg->FileName
//		);
//
//
//	ExecuteCmd(pCh,pCmd_RecvFax);
//
//}
//
//KFPC_Cmd_TS_StartSendFax* KFPC_CmdMgr::Create_Cmd_StartSendFax( KFPC_Channel* pCh, unsigned int DstAppID, unsigned int UserContext1, unsigned int UserContext2, const char *pFileName,const char *pSenderIdent,const char *pSubAddress,const char *pPageHeaderInfo,const char *pIdentifier, bool SubCmd )
//{
//	KFPC_Cmd_TS_StartSendFax* pCmd = new KFPC_Cmd_TS_StartSendFax(pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		pFileName,
//		pSenderIdent,
//		pSubAddress,
//		pPageHeaderInfo,
//		pIdentifier,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_TS_StartRecvFax* KFPC_CmdMgr::Create_Cmd_StartRecvFax( KFPC_Channel* pCh, unsigned int DstAppID, unsigned int UserContext1, unsigned int UserContext2, char* FaxFileName, bool SubCmd /*= false*/ )
//{
//	KFPC_Cmd_TS_StartRecvFax* pCmd = new KFPC_Cmd_TS_StartRecvFax(pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		FaxFileName,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//
//
//KFPC_Cmd_TS_StopSendFax* KFPC_CmdMgr::Create_Cmd_StopSendFax( KFPC_Channel* pCh, unsigned int DstAppID, unsigned int UserContext1, unsigned int UserContext2, bool SubCmd /*= false*/ )
//{
//	KFPC_Cmd_TS_StopSendFax* pCmd = new KFPC_Cmd_TS_StopSendFax(pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//void KFPC_CmdMgr::DoREQ_TS_StopSendFax( KFPC_Channel* pCh,KFPC_REQ_TS_StopSendFax* pMsg )
//{
//	KFPC_Cmd_TS_StopSendFax *pCmd_StopSendFax = Create_Cmd_StopSendFax(pCh,		
//		pMsg->Header.un32SrcAPPId,
//		pMsg->Header.un32UserContext1,
//		pMsg->Header.un32UserContext2
//		);
//
//
//	ExecuteCmd(pCh,pCmd_StopSendFax);
//
//}
//
//KFPC_CmdSet_TS_Connect* KFPC_CmdMgr::Create_CmdSet_TS_Connect( KFPC_Channel* pCh, 
//	KFPC_Channel* pCh2, 
//	unsigned int DstAppID, 
//	unsigned int UserContext1, 
//	unsigned int UserContext2,
//	unsigned char ConnectMode,
//	unsigned int	StopMedia)
//{
//	KFPC_CmdSet_TS_Connect* pCmd = new KFPC_CmdSet_TS_Connect(pCh,pCh2,
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		ConnectMode,
//		StopMedia);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_DisconnectMixIVR* KFPC_CmdMgr::Create_Cmd_DisconnectMixIVR( KFPC_Channel* pCh, unsigned int DstAppID, unsigned int UserContext1, unsigned int UserContext2, bool SubCmd /*= false*/ )
//{
//	KFPC_Cmd_DisconnectMixIVR* pCmd = new KFPC_Cmd_DisconnectMixIVR(
//		pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//
//KFPC_Cmd_Free3PartyConf* KFPC_CmdMgr::Create_Cmd_Free3PartyConf( KFPC_Channel* pCh, unsigned int DstAppID, unsigned int UserContext1, unsigned int UserContext2, bool SubCmd /*= false*/ )
//{
//	KFPC_Cmd_Free3PartyConf* pCmd = new KFPC_Cmd_Free3PartyConf(
//		pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//
//
//void KFPC_CmdMgr::DoREQ_TS_AcceptCall( KFPC_Channel* pCh,KFPC_REQ_TS_AcceptCall* pMsg )
//{
//	KFPC_Cmd_AcceptCall* pCmd_AcceptCall = KFPC_CmdMgrInstance->Create_Cmd_AcceptCall(pCh,
//		pMsg->Header.un32SrcAPPId,
//		pMsg->Header.un32UserContext1,
//		pMsg->Header.un32UserContext2);
//
//
//	ExecuteCmd(pCh,pCmd_AcceptCall);
//
//	
//}
//
//KFPC_CmdSet_TS_StartSendFax* KFPC_CmdMgr::Create_CmdSet_StartSendFax(KFPC_Channel* pCh,unsigned int DstAppID,
//	unsigned int UserContext1,unsigned int UserContext2,const char *pFileName,const char *pSenderIdent,
//	const char *pSubAddress,const char *pPageHeaderInfo,const char *pIdentifier,bool SubCmd )
//{
//	KFPC_CmdSet_TS_StartSendFax* pCmd = new KFPC_CmdSet_TS_StartSendFax(pCh,
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		pFileName,
//		pSenderIdent,
//		pSubAddress,
//		pPageHeaderInfo,
//		pIdentifier,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_CmdSet_TS_StartRecvFax* KFPC_CmdMgr::Create_CmdSet_StartRecvFax(KFPC_Channel* pCh,unsigned int DstAppID,
//	unsigned int UserContext1,unsigned int UserContext2,char* FaxFileName,bool SubCmd )
//{
//	KFPC_CmdSet_TS_StartRecvFax* pCmd = new KFPC_CmdSet_TS_StartRecvFax(pCh,
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		FaxFileName,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//
//KFPC_Cmd_AcceptCall* KFPC_CmdMgr::Create_Cmd_AcceptCall( KFPC_Channel* pCh, unsigned int DstAppID, unsigned int UserContext1, unsigned int UserContext2, bool SubCmd /*= false*/ )
//{
//	KFPC_Cmd_AcceptCall* pCmd =new KFPC_Cmd_AcceptCall(pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2);
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_EH_StartFaxMedia* KFPC_CmdMgr::Create_Cmd_StartFaxMedia( KFPC_Channel* pCh, unsigned int DstAppID, unsigned int UserContext1, unsigned int UserContext2, bool SubCmd )
//{
//	KFPC_Cmd_EH_StartFaxMedia* pCmd = new KFPC_Cmd_EH_StartFaxMedia(pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_CmdSet_TS_JoinConf* KFPC_CmdMgr::Create_CmdSet_TS_JoinConf( KFPC_Channel* pCh, 
//	KFPC_Channel* pConfCh, 
//	unsigned int JoinMode, 
//	int DTMFSilence, 
//	unsigned int AppID, 
//	unsigned int UserContext1, 
//	unsigned int UserContext2,
//	unsigned int StopMedia)
//{
//	KFPC_CmdSet_TS_JoinConf* pCmd = new KFPC_CmdSet_TS_JoinConf(pCh,
//		pConfCh,
//		JoinMode,
//		DTMFSilence,
//		AppID,																			
//		UserContext1,
//		UserContext2,
//		StopMedia);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//void KFPC_CmdMgr::DoREQ_TS_ChangeConnectMode( KFPC_Channel* pCh,KFPC_REQ_TS_ChangeConnectMode* pMsg )
//{
//	KFPC_Cmd_EH_ChangeConnectMode* pCmd = Create_Cmd_EH_ChangeConnectMode(pCh,
//		pMsg->ConnectMode,
//		pMsg->Header.un32SrcAPPId,
//		pMsg->Header.un32UserContext1,
//		pMsg->Header.un32UserContext2);
//
//	if(pCh->GetCmdID() == 0)
//	{
//		ExecuteCmd(pCh,pCmd);
//	}
//	else
//	{
//		pCh->PushCmdID(pCmd->GetID());
//	}
//}
//
//KFPC_Cmd_EH_ChangeConnectMode* KFPC_CmdMgr::Create_Cmd_EH_ChangeConnectMode( 		
//	KFPC_Channel* pCh,
//	unsigned int ConnectMode, 
//	unsigned int& DstAppID, 
//	unsigned int& UserContext1, 
//	unsigned int& UserContext2, 
//	bool SubCmd /*= false */ )
//{
//	KFPC_Cmd_EH_ChangeConnectMode* pCmd = new KFPC_Cmd_EH_ChangeConnectMode(pCh,
//		ConnectMode,
//		DstAppID,																			
//		UserContext1,
//		UserContext2);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_CmdSet_TS_FreeConf* KFPC_CmdMgr::Create_CmdSet_FreeConf( KFPC_Channel* pCh, unsigned int DstAppID, unsigned int UserContext1, unsigned int UserContext2 )
//{
//	KFPC_CmdSet_TS_FreeConf* pCmd = new KFPC_CmdSet_TS_FreeConf(pCh,
//		DstAppID,																			
//		UserContext1,
//		UserContext2);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_CmdSet_MixPlayVoice* KFPC_CmdMgr::Create_CmdSet_MixPlayVoice( KFPC_Channel* pCh, char* VoiceFile, KFPC_DTMFParam* pDTMFPara, unsigned int DstAppID, unsigned int UserContext1, unsigned int UserContext2, bool SubCmd /*= false*/ )
//{
//	KFPC_CmdSet_MixPlayVoice* pCmd = new KFPC_CmdSet_MixPlayVoice(VoiceFile,
//		pDTMFPara,
//		pCh,
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_EH_ConnectToFAX* KFPC_CmdMgr::Create_Cmd_EH_ConnectToFAX( KFPC_Channel* pCh, 
//	unsigned int AppID, 
//	unsigned int UserContext1, 
//	unsigned int UserContext2 )
//{
//	KFPC_Cmd_EH_ConnectToFAX* pCmd =new KFPC_Cmd_EH_ConnectToFAX(pCh->GetCallID(),	
//		AppID,
//		UserContext1,
//		UserContext2);
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_EH_Voice2Fax* KFPC_CmdMgr::Create_Cmd_EH_Voice2Fax( KFPC_Channel* pCh, 
//	unsigned int AppID, 
//	unsigned int UserContext1,
//	unsigned int UserContext2 )
//{
//	KFPC_Cmd_EH_Voice2Fax* pCmd =new KFPC_Cmd_EH_Voice2Fax(pCh->GetCallID(),	
//		AppID,
//		UserContext1,
//		UserContext2);
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//void KFPC_CmdMgr::DoREQ_TS_StopReceiveFax( KFPC_Channel* pCh,KFPC_REQ_TS_StopReceiveFax* pMsg )
//{
//	KFPC_Cmd_TS_StopReceiveFax *pCmd_StopReceiveFax = Create_Cmd_StopReceiveFax(pCh,		
//		pMsg->Header.un32SrcAPPId,
//		pMsg->Header.un32UserContext1,
//		pMsg->Header.un32UserContext2
//		);
//
//
//	ExecuteCmd(pCh,pCmd_StopReceiveFax);
//}
//
//KFPC_Cmd_TS_StopReceiveFax* KFPC_CmdMgr::Create_Cmd_StopReceiveFax( KFPC_Channel* pCh, unsigned int AppID, unsigned int UserContext1, unsigned int UserContext2,bool SubCmd )
//{
//	KFPC_Cmd_TS_StopReceiveFax* pCmd = new KFPC_Cmd_TS_StopReceiveFax(pCh->GetCallID(),
//		AppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_CmdSet_MixCollectDTMF* KFPC_CmdMgr::Create_CmdSet_MixCollect( KFPC_Channel* pCh, KFPC_DTMFParam* pDTMFPara, unsigned int DstAppID, unsigned int UserContext1, unsigned int UserContext2, bool SubCmd /*= false*/ )
//{
//	KFPC_CmdSet_MixCollectDTMF* pCmd =new KFPC_CmdSet_MixCollectDTMF(pDTMFPara,
//		pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//void KFPC_CmdMgr::DoREQ_TS_PlayDTMF( KFPC_Channel* pCh,KFPC_REQ_TS_PlayDTMF* pMsg )
//{
//	KFPC_CmdSet_PlayDTMF *pCmdSet_PlayDTMF = Create_CmdSet_PlayDTMF(pCh,
//		pMsg->DTMF,
//		pMsg->Header.un32SrcAPPId,
//		pMsg->Header.un32UserContext1,
//		pMsg->Header.un32UserContext2
//		);
//
//	ExecuteCmd(pCh,pCmdSet_PlayDTMF);
//}

unsigned int KFPC_CmdMgr::ExecuteRspCmd( KFPC_BaseCommand* pCmd,unsigned int MsgID )
{
	if(pCmd == NULL)
	{
		ERROR_LOG(0,"Cmd is NULL");
		return KFPC_ERR_GetCmdIDFailed;
	}

	unsigned int Ret = pCmd->Execute(MsgID,KFPC_MSG_TYPE_RESPONSE);

	if(KFPC_ERR_CmdWaitAck == Ret)
	{

	}
	else if(KFPC_ERR_MsgIDNotMatch == Ret)
	{
		DEBUG_LOG(0,"Msg ID:%u doest not match.",MsgID);
	}
	else 
	{
		FreeCmd(pCmd);	
	}

	return Ret;
}

//KFPC_Cmd_PlayDTMF* KFPC_CmdMgr::Create_Cmd_PlayDTMF( KFPC_Channel* pCh, char* pDTMF, unsigned int DstAppID, unsigned int UserContext1, unsigned int UserContext2, bool SubCmd /*= false*/ )
//{
//	KFPC_Cmd_PlayDTMF* pCmd = new KFPC_Cmd_PlayDTMF(pDTMF,
//		pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_CmdSet_PlayDTMF* KFPC_CmdMgr::Create_CmdSet_PlayDTMF( KFPC_Channel* pCh, char* pDTMF, unsigned int DstAppID, unsigned int UserContext1, unsigned int UserContext2, bool SubCmd /*= false*/ )
//{
//	KFPC_CmdSet_PlayDTMF* pCmd = new KFPC_CmdSet_PlayDTMF(pDTMF,
//		pCh,
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_EH_Evt_HookFlash* KFPC_CmdMgr::Create_Cmd_EH_Evt_HookFlash( KFPC_Channel* pCh )
//{
//	KFPC_Cmd_EH_Evt_HookFlash* pCmd = new KFPC_Cmd_EH_Evt_HookFlash(pCh->GetCallID(),
//		pCh->GetDstAppID(),
//		0,0);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_TS_RequestFaxCh* KFPC_CmdMgr::Create_Cmd_TS_RequestFaxCh( KFPC_Channel* pCh, 
//	unsigned int DstAppID, 
//	unsigned int UserContext1, 
//	unsigned int UserContext2, 
//	bool SubCmd /*= false*/ )
//{
//	KFPC_Cmd_TS_RequestFaxCh* pCmd = new KFPC_Cmd_TS_RequestFaxCh(pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//
//KFPC_Cmd_EH_StopMedia* KFPC_CmdMgr::Create_Cmd_EH_StopMedia( 
//	KFPC_Channel* pCh, 
//	unsigned int DstAppID, 
//	unsigned int UserContext1, 
//	unsigned int UserContext2, bool SubCmd /*= false*/ )
//{
//	KFPC_Cmd_EH_StopMedia* pCmd = new KFPC_Cmd_EH_StopMedia(pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}
//
//KFPC_Cmd_EH_Timer* KFPC_CmdMgr::Create_Cmd_EH_Timer( 
//	KFPC_Channel* pCh, 
//	unsigned int DstAppID, 
//	unsigned int UserContext1, 
//	unsigned int UserContext2, 
//	unsigned int TimeOut,
//	bool SubCmd /*= false*/ )
//{
//	KFPC_Cmd_EH_Timer* pCmd = new KFPC_Cmd_EH_Timer(pCh->GetCallID(),
//		DstAppID,
//		UserContext1,
//		UserContext2,
//		TimeOut,
//		SubCmd);
//
//	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
//	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());
//
//	return pCmd;
//}

#ifdef MSML
KFPC_CmdSet_MSML_CreateConf* KFPC_CmdMgr::Create_CmdSet_MSML_CreateConf( KFPC_Channel* pCh, 
	const char* Name, 
	MSML_DeleteWhen MSML_DeleteWhen, 
	unsigned int Mix_N_Loudest, /*		  */
	unsigned int Mix_Asn_Ri, /*minimum reporting interval */ 
	unsigned int SerialNo)
{
	KFPC_CmdSet_MSML_CreateConf* pCmd = new KFPC_CmdSet_MSML_CreateConf(
		pCh, 
		Name, 
		MSML_DeleteWhen, 
		Mix_N_Loudest, /*		  */
		Mix_Asn_Ri,
		SerialNo);

	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());

	return pCmd;
}

KFPC_CmdSet_MSML_JoinConf* KFPC_CmdMgr::Create_CmdSet_MSML_JoinConf( KFPC_Channel* pCh, 
	KFPC_Channel* pConf,
	unsigned int JoinMode, 
	int DTMFSilence,
	unsigned int StopMedia,
	unsigned int SerialNo)
{
	KFPC_CmdSet_MSML_JoinConf* pCmd = new KFPC_CmdSet_MSML_JoinConf(pCh,pConf,JoinMode,DTMFSilence,StopMedia,SerialNo);

	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());

	return pCmd;
}

KFPC_CmdSet_MSML_Modifystream* KFPC_CmdMgr::Create_CmdSet_MSML_Modifystream( KFPC_Channel* pCh,unsigned int JoinMode,unsigned int SerialNo )
{
	KFPC_CmdSet_MSML_Modifystream* pCmd = new KFPC_CmdSet_MSML_Modifystream(pCh,JoinMode,SerialNo);

	m_CommandMap.insert(CommandMapPair_t(pCmd->GetID(),pCmd));
	INFO_LOG(pCh->GetCallID(),"ChID:%u,CmdID:%u,CommandMap size:%u.",pCh->GetID(),pCmd->GetID(),m_CommandMap.size());

	return pCmd;
}


#endif