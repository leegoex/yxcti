#include "kfpc_logex.h"
#include "KFPC_TServerAPIHandlerImp.h"
#include "KFPC_TServerConfigFile.h"
#include "KFPC_CMDMgr.h"
#include "KFPC_EHNode.h"
#include "KFPC_TServerErr.h"
#include "KFPC_CmdMgr.h"
#include "KFPC_Channel.h"

KFPC_TServerAPIHandlerImp::KFPC_TServerAPIHandlerImp(void)
{
}


KFPC_TServerAPIHandlerImp::~KFPC_TServerAPIHandlerImp(void)
{
}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_AcceptCall(KFPC_REQ_TS_AcceptCall* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_AcceptCall(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			Ret);
	}
	else
	{
		//KFPC_CmdMgrInstance->DoREQ_TS_AcceptCall(pCh,pMsg);
	}

}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_AnswerCall(KFPC_REQ_TS_AnswerCall* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);
	
	if(0 != Ret)
	{
		SendRSP_TS_AnswerCall(pMsg->Header.un32SrcAPPId,
								pMsg->Header.un32UserContext1,
								pMsg->Header.un32UserContext2,
								pMsg->CallID,
								Ret);
	}
	else
	{
		//KFPC_CmdMgrInstance->DoREQ_TS_AnswerCall(pCh,pMsg);
	}
	

}


void KFPC_TServerAPIHandlerImp::OnREQ_TS_ReleaseCall(KFPC_REQ_TS_ReleaseCall* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_ReleaseCall(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			Ret);
	}
	else
	{
		//KFPC_CmdMgrInstance->DoREQ_TS_ReleaseCall(pCh,pMsg);
	}
}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_CallOut(KFPC_REQ_TS_CallOut* pMsg)
{
	//KFPC_CmdMgrInstance->DoREQ_TS_CallOut(pMsg);

}	

void KFPC_TServerAPIHandlerImp::OnREQ_TS_Connect(KFPC_REQ_TS_Connect* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID1,&pCh);

	if(0 !=Ret)
	{
		SendRSP_TS_Connect(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID1,
			pMsg->CallID2,
			Ret,0);
		return ;
	}

	KFPC_Channel*	pCh2 = NULL;

	Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID2,&pCh2);

	if(0 !=Ret)
	{
		SendRSP_TS_Connect(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID1,
			pMsg->CallID2,
			Ret,0);
		return ;
	}

	if(pMsg->CallID1 == pMsg->CallID2)
	{
		WARNING_LOG(pMsg->CallID1,"Call id conflict");

		SendRSP_TS_Connect(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID1,
			pMsg->CallID2,
			KFPC_ERR_CallIDConflict,
			0);
		return ;
	}

	//KFPC_CmdMgrInstance->DoREQ_TS_Connect(pCh,pCh2,pMsg);
}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_Disconnect(KFPC_REQ_TS_Disconnect* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_Disconnect(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			Ret);
		return ;
	}

	KFPC_Channel*	pCh2 = NULL;



	//KFPC_CmdMgrInstance->DoREQ_TS_Disconnect(pCh,pMsg);

}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_CreateConference(KFPC_REQ_TS_CreateConference* pMsg)
{
	//KFPC_CmdMgrInstance->DoREQ_TS_CreateConference(pMsg);
}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_FreeConference(KFPC_REQ_TS_FreeConference* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->ConfID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_FreeConference(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->ConfID,
			Ret);
	}
	else
	{
		//if(pCh->GetChType() == CH_TYPE_CONF)
		{
			//KFPC_CmdMgrInstance->DoREQ_TS_FreeConference(pCh,pMsg);
		}
		//else
		//{
		//	SendRSP_TS_FreeConference(pMsg->Header.un32SrcAPPId,
		//		pMsg->Header.un32UserContext1,
		//		pMsg->Header.un32UserContext2,
		//		pMsg->ConfID,
		//		KFPC_ERR_ChannelTypeErr);
		//}
	}
}


void KFPC_TServerAPIHandlerImp::OnREQ_TS_JoinConference(KFPC_REQ_TS_JoinConference* pMsg)
{
	KFPC_Channel*	pCh = NULL;
	KFPC_Channel*	pConfCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->ConfID,&pConfCh);

	if(0 != Ret)
	{
		SendRSP_TS_JoinConference(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			pMsg->ConfID,
			Ret,0);
		return;		
	}
	
	Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_JoinConference(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			pMsg->ConfID,
			Ret,0);
		return;		
	}

	
	//KFPC_CmdMgrInstance->DoREQ_TS_JoinConference(pCh,pConfCh,pMsg);
}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_LeaveConference(KFPC_REQ_TS_LeaveConference* pMsg)
{
	KFPC_Channel*	pCh = NULL;
	KFPC_Channel*	pConfCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->ConfID,&pConfCh);

	if(0 != Ret)
	{
		SendRSP_TS_LeaveConference(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			pMsg->ConfID,
			Ret);
		return;		
	}

	Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_LeaveConference(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			pMsg->ConfID,
			Ret);
		return;		
	}


	//KFPC_CmdMgrInstance->DoREQ_TS_LeaveConference(pCh,pConfCh,pMsg);
}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_ChangeConnectMode(KFPC_REQ_TS_ChangeConnectMode* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_ChangeConnectMode(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			Ret);

		return;		
	}


	//KFPC_CmdMgrInstance->DoREQ_TS_ChangeConnectMode(pCh,pMsg);

}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_CollectDTMF(KFPC_REQ_TS_CollectDTMF* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_CollectDTMF(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			Ret);
	}
	else
	{
		//KFPC_CmdMgrInstance->DoREQ_TS_CollectDTMF(pCh,pMsg);
	}
}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_StopCollectDTMF(KFPC_REQ_TS_StopCollectDTMF* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_StopCollectDTMF(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			Ret);
	}
	else
	{
		//KFPC_CmdMgrInstance->DoREQ_TS_StopCollectDTMF(pCh,pMsg);
	}
}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_PlayVoice(KFPC_REQ_TS_PlayVoice* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_PlayVoice(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			Ret);
	}
	else
	{
		//KFPC_CmdMgrInstance->DoREQ_TS_PlayVoice(pCh,pMsg);
	}
}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_StopPlayVoice(KFPC_REQ_TS_StopPlayVoice* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_StopPlayVoice(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			Ret);
	}
	else
	{
		//KFPC_CmdMgrInstance->DoREQ_TS_StopPlayVoice(pCh,pMsg);
	}
}

void KFPC_TServerAPIHandlerImp::OnReq_TS_RecordFile(KFPC_REQ_TS_StartRecordFile* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_RecordFile(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			Ret);
	}
	else
	{
		//KFPC_CmdMgrInstance->DoREQ_TS_RecordFile(pCh,pMsg);
	}
}


void KFPC_TServerAPIHandlerImp::OnREQ_TS_StopRecordFile(KFPC_REQ_TS_StopRecordFile* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_StopRecordFile(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			Ret);
	}
	else
	{
		//KFPC_CmdMgrInstance->DoREQ_TS_StopRecordFile(pCh,pMsg);
	}
}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_RecvFax(KFPC_REQ_TS_RecvFax* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_RecvFax(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			Ret);
	}
	else
	{
		//KFPC_CmdMgrInstance->DoREQ_TS_StartRecvFax(pCh,pMsg);
	}
}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_StopReceiveFax(KFPC_REQ_TS_StopReceiveFax* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_StopReceiveFax(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			Ret);
	}
	else
	{
		//KFPC_CmdMgrInstance->DoREQ_TS_StopReceiveFax(pCh,pMsg);
	}
}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_StartSendFax(KFPC_REQ_TS_StartSendFax* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_StartSendFax(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			Ret);
	}
	else
	{
		//KFPC_CmdMgrInstance->DoREQ_TS_StartSendFax(pCh,pMsg);
	}

}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_StopSendFax(KFPC_REQ_TS_StopSendFax* pMsg)
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_StopSendFax(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			Ret);
	}
	else
	{
		//KFPC_CmdMgrInstance->DoREQ_TS_StopSendFax(pCh,pMsg);
	}
}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_ReloadConfig(KFPC_REQ_TS_ReloadConfig* pMsg)
{
	unsigned int result = SSTServerCfgInstance->ReLoadConfigFile(SS_TSERVER_CFG);

	SSTServerCfgInstance->GetTrunkGroupMgr()->UpdateTrunkGroup();


	SendRSP_TS_ReloadConfig(pMsg->Header.un32SrcAPPId,
		pMsg->Header.un32UserContext1,
		pMsg->Header.un32UserContext2,
		result);
	
}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_QueryChStatus(KFPC_REQ_TS_QueryChStatus* pMsg){}

void KFPC_TServerAPIHandlerImp::OnTS_EVT_UpdateChStatus(KFPC_TS_EVT_UpdateChStatus* pMsg){}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_SetChState(KFPC_REQ_TS_SetChState* pMsg){}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_CoreDump(KFPC_REQ_TS_CoreDump* pMsg){}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_WatchTrunkGroup(KFPC_REQ_TS_WatchTrunkGroup* pMsg)
{
	if (NULL!=pMsg)
	{
		KFPC_TrunkGroup* pTrunkGroup = SSTServerCfgInstance->GetTrunkGroupMgr()->GetTrunkGroupByName(pMsg->TrunkGroup);
		if (NULL!=pTrunkGroup)
		{
			pTrunkGroup->AddWatchAppID(pMsg->Header.un32SrcAPPId);

			SendRSP_TS_WatchTrunkGroup(pMsg->Header.un32SrcAPPId,
				pMsg->Header.un32UserContext1,
				pMsg->Header.un32UserContext2,
				pMsg->TrunkGroup,
				0);
		}
	}
}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_CancelWatchTrunkGroup(KFPC_REQ_TS_CancelWatchTrunkGroup* pMsg){}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_QueryTrunkGroup(KFPC_REQ_TS_QueryTrunkGroup* pMsg){}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_MonitorChStatus(KFPC_REQ_TS_MonitorChStatus* pMsg){}

void KFPC_TServerAPIHandlerImp::OnREQ_TS_PlayDTMF( KFPC_REQ_TS_PlayDTMF* pMsg )
{
	KFPC_Channel*	pCh = NULL;

	unsigned int Ret = KFPC_ChMgrInstance->CheckCallID(pMsg->CallID,&pCh);

	if(0 != Ret)
	{
		SendRSP_TS_PlayDTMF(pMsg->Header.un32SrcAPPId,
			pMsg->Header.un32UserContext1,
			pMsg->Header.un32UserContext2,
			pMsg->CallID,
			Ret);
	}
	else
	{
		//KFPC_CmdMgrInstance->DoREQ_TS_PlayDTMF(pCh,pMsg);
	}
}


//void KFPC_TServerAPIHandlerImp::OnREQ_TS_WatchNumStatus(KFPC_REQ_TS_WatchNumStatus* pMsg){}	
//
//unsigned int KFPC_TServerAPIHandlerImp::KFPC_ChMgrInstance->CheckCallID(unsigned long long& CallID,KFPC_Channel** ppCh )
//{
//
//	if(CallID == 0)
//	{
//		WARNING_LOG(CallID,"CallID must be not 0 ");
//		return KFPC_ERR_CallIDInvalid;
//	}
//
//	KFPC_CallID* kfpc_CallID = (KFPC_CallID*)&CallID;
//
//	unsigned short	ChID = kfpc_CallID->CallIDInfo.ChID;
//
//	*ppCh = KFPC_ChMgrInstance->GetChannel(ChID);
//
//	if(NULL == (*ppCh))
//	{
//		WARNING_LOG(CallID,"Failed to get Channel from ID ChID%u",ChID);
//		return KFPC_ERR_ChIDInvalid;
//	}
//
//	if((*ppCh)->GetCallID() != CallID)
//	{
//		WARNING_LOG(CallID,"ChID:%u CallID err",(*ppCh)->GetID());
//
//		return KFPC_ERR_CallIDInvalid;
//	}
//
//	return 0;
//}