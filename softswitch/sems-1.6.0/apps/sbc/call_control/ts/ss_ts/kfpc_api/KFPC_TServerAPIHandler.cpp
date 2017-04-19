#include "KFPC_TServerAPIHandler.h"
#include "kfpc_logex.h"
#include "KFPC_TServerErr.h"

KFPC_TServerAPIHandler::KFPC_TServerAPIHandler(void)
{
	
	for(int i=0;i<KFPC_MAX_MSG_ID_TS;i++)
	{
		m_MsgProcFunMap[i] = NULL;
	}

	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_GetTSVersion)					] = &KFPC_TServerAPIHandler::RecvTS_GetTSVersion;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_AcceptCall)					] = &KFPC_TServerAPIHandler::RecvTS_AcceptCall;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_AnswerCall)					] = &KFPC_TServerAPIHandler::RecvTS_AnswerCall;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_ReleaseCall)					] = &KFPC_TServerAPIHandler::RecvTS_ReleaseCall;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_CallOut)						] = &KFPC_TServerAPIHandler::RecvTS_CallOut;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_EVT_IncomingCall)				] = &KFPC_TServerAPIHandler::RecvTS_EVT_IncomingCall;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_EVT_AlertCall)					] = &KFPC_TServerAPIHandler::RecvTS_EVT_AlertCall;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_EVT_AnsweredCall)				] = &KFPC_TServerAPIHandler::RecvTS_EVT_AnsweredCall;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_EVT_ReleasedCall)				] = &KFPC_TServerAPIHandler::RecvTS_EVT_ReleasedCall;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_Connect)						] = &KFPC_TServerAPIHandler::RecvTS_Connect;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_Disconnect)					] = &KFPC_TServerAPIHandler::RecvTS_Disconnect;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_CreateConference)				] = &KFPC_TServerAPIHandler::RecvTS_CreateConference;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_FreeConference)				] = &KFPC_TServerAPIHandler::RecvTS_FreeConference;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_JoinConference)				] = &KFPC_TServerAPIHandler::RecvTS_JoinConference;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_LeaveConference)				] = &KFPC_TServerAPIHandler::RecvTS_LeaveConference;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_ChangeConnectMode)				] = &KFPC_TServerAPIHandler::RecvTS_ChangeConnectMode;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_CollectDTMF)					] = &KFPC_TServerAPIHandler::RecvTS_CollectDTMF;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_StopCollectDTMF)				] = &KFPC_TServerAPIHandler::RecvTS_StopCollectDTMF;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_EVT_CollectDTMFCompleted)		] = &KFPC_TServerAPIHandler::RecvTS_EVT_CollectDTMFCompleted;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_PlayVoice)						] = &KFPC_TServerAPIHandler::RecvTS_PlayVoice;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_StopPlayVoice)					] = &KFPC_TServerAPIHandler::RecvTS_StopPlayVoice;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_EVT_PlayVoiceCompleted)		] = &KFPC_TServerAPIHandler::RecvTS_EVT_PlayVoiceCompleted;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_RecordFile)					] = &KFPC_TServerAPIHandler::RecvTS_RecordFile;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_StopRecordFile)				] = &KFPC_TServerAPIHandler::RecvTS_StopRecordFile;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_EVT_RecordFileCompleted)		] = &KFPC_TServerAPIHandler::RecvTS_EVT_RecordFileCompleted;
	/*
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_ConfPlayVoice)					] = &KFPC_TServerAPIHandler::RecvTS_ConfPlayVoice;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_StopConfPlayVoice)				] = &KFPC_TServerAPIHandler::RecvTS_StopConfPlayVoice;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_EVT_ConfPlayFileCompleted)		] = &KFPC_TServerAPIHandler::RecvTS_EVT_ConfPlayFileCompleted;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_ConfRecordFile)				] = &KFPC_TServerAPIHandler::RecvTS_ConfRecordFile;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_StopConfRecordFile)			] = &KFPC_TServerAPIHandler::RecvTS_StopConfRecordFile;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_EVT_ConfRecordFileCompleted)	] = &KFPC_TServerAPIHandler::RecvTS_EVT_ConfRecordFileCompleted;
	*/
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_SendFax)						] = &KFPC_TServerAPIHandler::RecvTS_SendFax;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_StopSendFax)					] = &KFPC_TServerAPIHandler::RecvTS_StopSendFax;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_EVT_SendFaxCompleted)			] = &KFPC_TServerAPIHandler::RecvTS_EVT_SendFaxCompleted;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_RecvFax)						] = &KFPC_TServerAPIHandler::RecvTS_RecvFax;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_StopRecvFax)					] = &KFPC_TServerAPIHandler::RecvTS_StopRecvFax;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_EVT_RecvFaxCompleted)			] = &KFPC_TServerAPIHandler::RecvTS_EVT_RecvFaxCompleted;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_ReloadCfg)						] = &KFPC_TServerAPIHandler::RecvTS_ReloadCfg;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_QueryChStatus)					] = &KFPC_TServerAPIHandler::RecvTS_QueryChStatus;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_UpdateChStatus)				] = &KFPC_TServerAPIHandler::RecvTS_UpdateChStatus;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_SetChStatus)					] = &KFPC_TServerAPIHandler::RecvTS_SetChStatus;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_CoreDump)						] = &KFPC_TServerAPIHandler::RecvTS_CoreDump;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_EVT_Alarm)						] = &KFPC_TServerAPIHandler::RecvTS_EVT_Alarm;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_WatchTrunkGroup)				] = &KFPC_TServerAPIHandler::RecvTS_WatchTrunkGroup;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_CancelWatchTrunkGroup)			] = &KFPC_TServerAPIHandler::RecvTS_CancelWatchTrunkGroup;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_QueryTrunkGroup)				] = &KFPC_TServerAPIHandler::RecvTS_QueryTrunkGroup;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_EVT_UpdateTrunkGroup)			] = &KFPC_TServerAPIHandler::RecvTS_EVT_UpdateTrunkGroup;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_PlayDTMF)						] = &KFPC_TServerAPIHandler::RecvTS_PlayDTMF;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_EVT_HookFlash)					] = &KFPC_TServerAPIHandler::RecvTS_EVT_HookFlash;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_EVT_ExtNum2CCS)				] = &KFPC_TServerAPIHandler::RecvTS_EVT_ExtNum2CCS;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_TS_EVT_PassAnswerCall)			] = &KFPC_TServerAPIHandler::RecvTS_EVT_PassAnswerCall;
	

}


KFPC_TServerAPIHandler::~KFPC_TServerAPIHandler(void)
{
}

void KFPC_TServerAPIHandler::RecvTS_GetTSVersion(KFPC_MSG_HEADER* pMsg)
{
	INFO_LOG(0,"");

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_GetTSVersion*	pKFPC_REQ_TS_GetTSVersion = (KFPC_REQ_TS_GetTSVersion*)pMsg;
		OnREQ_TS_GetTSVersion(pKFPC_REQ_TS_GetTSVersion);				
	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_GetTSVersion*	pKFPC_RSP_TS_GetTSVersion = (KFPC_RSP_TS_GetTSVersion*)pMsg;
		OnRSP_TS_GetTSVersion(pKFPC_RSP_TS_GetTSVersion);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);
	}
}
void KFPC_TServerAPIHandler::RecvTS_AcceptCall(KFPC_MSG_HEADER* pMsg)
{
	
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_AcceptCall*	pREQMsg = (KFPC_REQ_TS_AcceptCall*)pMsg;

		INFO_LOG(pREQMsg->CallID,
					"Header.un32SrcAPPId:0x%x,"
					"Header.un32DstAPPId:0x%x,"
					"Header.un32UserContext1:%u,"
					"Header.un32UserContext2:%u",
					Header.un32SrcAPPId,
					Header.un32DstAPPId,
					Header.un32UserContext1,
					Header.un32UserContext2);		

		OnREQ_TS_AcceptCall(pREQMsg);
		
	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_AcceptCall*	pRSPMsg = (KFPC_RSP_TS_AcceptCall*)pMsg;
		
		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_AcceptCall(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);
		
	}
}
void KFPC_TServerAPIHandler::RecvTS_AnswerCall(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_AnswerCall*	pREQMsg = (KFPC_REQ_TS_AnswerCall*)pMsg;

		INFO_LOG(pREQMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);		

		OnREQ_TS_AnswerCall(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_AnswerCall*	pRSPMsg = (KFPC_RSP_TS_AnswerCall*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result
			);		

		OnRSP_TS_AnswerCall(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_ReleaseCall(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_ReleaseCall*	pREQMsg = (KFPC_REQ_TS_ReleaseCall*)pMsg;

		INFO_LOG(pREQMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Release Cause:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->Cause);		

		OnREQ_TS_ReleaseCall(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_ReleaseCall*	pRSPMsg = (KFPC_RSP_TS_ReleaseCall*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_ReleaseCall(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_CallOut(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_CallOut*	pREQMsg = (KFPC_REQ_TS_CallOut*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Device.Span:%u,"
			"Device.Type:%u,"
			"Device.TrunkGroup:%s,"
			"Device.CallerNO:%s,"
			"Device.CalledNO:%s,"
			"Device.Channel:%u,"
			"Device.OriginalCalled:%s,"
			"Device.RedirectingNum:%s",

			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->Device.Span,
			pREQMsg->Device.Type,
			pREQMsg->Device.TrunkGroup,
			pREQMsg->Device.CallerNO,
			pREQMsg->Device.CalledNO,
			pREQMsg->Device.TimeSlot,
			pREQMsg->Device.OriginalCalled,
			pREQMsg->Device.RedirectingNum);		

		OnREQ_TS_CallOut(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_CallOut*	pRSPMsg = (KFPC_RSP_TS_CallOut*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x,"
			"ResultStr:%s,"
			"Cause:%u,"
			"Device.Span:%u,"
			"Device.Type:%u,"
			"Device.TrunkGroup:%s,"
			"Device.CallerNO:%s,"
			"Device.CalledNO:%s,"
			"Device.Channel:%u,"
			"Device.OriginalCalled:%s,"
			"Device.RedirectingNum:%s,"
			"SignalType:%u",

			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result,
			ErrorCodeToStr(pRSPMsg->Result),
			pRSPMsg->Cause,
			pRSPMsg->Device.Span,
			pRSPMsg->Device.Type,
			pRSPMsg->Device.TrunkGroup,
			pRSPMsg->Device.CallerNO,
			pRSPMsg->Device.CalledNO,
			pRSPMsg->Device.TimeSlot,
			pRSPMsg->Device.OriginalCalled,
			pRSPMsg->Device.RedirectingNum,
			pRSPMsg->SignalType);		

		OnRSP_TS_CallOut(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_EVT_IncomingCall(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_IncomingCall*	pEventMsg = (KFPC_TS_EVT_IncomingCall*)pMsg;

		INFO_LOG(pEventMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Device.Span:%u,"
			"Device.Type:%u,"
			"Device.TrunkGroup:%s,"
			"Device.CallerNO:%s,"
			"Device.CalledNO:%s,"
			"Device.Channel:%u,"
			"Device.OriginalCalled:%s,"
			"Device.RedirectingNum:%s,"
			"SignalType:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pEventMsg->Device.Span,
			pEventMsg->Device.Type,
			pEventMsg->Device.TrunkGroup,
			pEventMsg->Device.CallerNO,
			pEventMsg->Device.CalledNO,
			pEventMsg->Device.TimeSlot,
			pEventMsg->Device.OriginalCalled,
			pEventMsg->Device.RedirectingNum,
			pEventMsg->SignalType);		

		OnTS_EVT_IncomingCall(pEventMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_EVT_AlertCall(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_AlertCall*	pEventMsg = (KFPC_TS_EVT_AlertCall*)pMsg;

		INFO_LOG(pEventMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Cause:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pEventMsg->Cause);		

		OnTS_EVT_AlertCall(pEventMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_EVT_AnsweredCall(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_AnsweredCall*	pEventMsg = (KFPC_TS_EVT_AnsweredCall*)pMsg;

		INFO_LOG(pEventMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);		

		OnTS_EVT_AnsweredCall(pEventMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_EVT_ReleasedCall(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_ReleasedCall*	pEventMsg = (KFPC_TS_EVT_ReleasedCall*)pMsg;

		INFO_LOG(pEventMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Cause:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pEventMsg->Cause);		

		OnTS_EVT_ReleasedCall(pEventMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_Connect(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_Connect*	pREQMsg = (KFPC_REQ_TS_Connect*)pMsg;

		INFO_LOG(pREQMsg->CallID1,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"CallID1:0x%llx,"
			"CallID2:0x%llx,"
			"ConnectMode:%d,"
			"StopMedia:0x%x"
			,
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->CallID1,
			pREQMsg->CallID2,
			pREQMsg->ConnectMode,
			pREQMsg->StopMedia);		

		OnREQ_TS_Connect(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_Connect*	pRSPMsg = (KFPC_RSP_TS_Connect*)pMsg;

		INFO_LOG(pRSPMsg->CallID1,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"CallID1:0x%llx,"
			"CallID2:0x%llx,"
			"Result:0x%x,"
			"Session:0x%llx",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->CallID1,
			pRSPMsg->CallID2,
			pRSPMsg->Result,
			pRSPMsg->SessionID);		

		OnRSP_TS_Connect(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_Disconnect(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_Disconnect*	pREQMsg = (KFPC_REQ_TS_Disconnect*)pMsg;

		INFO_LOG(pREQMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			,
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);		

		OnREQ_TS_Disconnect(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_Disconnect*	pRSPMsg = (KFPC_RSP_TS_Disconnect*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_Disconnect(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_CreateConference(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_CreateConference*	pREQMsg = (KFPC_REQ_TS_CreateConference*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"MaxMember:%u,"
			"NodeID:%u,"
			"TserverID:%u,"
			"CCSID:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->MaxMember,
			pREQMsg->NodeID,
			pREQMsg->TserverID,
			pREQMsg->CCSID);		

		OnREQ_TS_CreateConference(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_CreateConference*	pRSPMsg = (KFPC_RSP_TS_CreateConference*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx,"
			"CCSID:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->ConfID,
			pRSPMsg->CCSID,
			pRSPMsg->Result);		

		OnRSP_TS_CreateConference(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_FreeConference(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_FreeConference*	pREQMsg = (KFPC_REQ_TS_FreeConference*)pMsg;

		INFO_LOG(pREQMsg->ConfID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->ConfID);		

		OnREQ_TS_FreeConference(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_FreeConference*	pRSPMsg = (KFPC_RSP_TS_FreeConference*)pMsg;

		INFO_LOG(pRSPMsg->ConfID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->ConfID,
			pRSPMsg->Result);		

		OnRSP_TS_FreeConference(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_JoinConference(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_JoinConference*	pREQMsg = (KFPC_REQ_TS_JoinConference*)pMsg;

		INFO_LOG(pREQMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx,"
			"JoinMode:%u,"
			"DTMFSilence:%d,"
			"StopMedia:0x%x"
			,
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->ConfID,
			pREQMsg->JoinMode,
			pREQMsg->DTMFSilence,
			pREQMsg->StopMedia);		

		OnREQ_TS_JoinConference(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_JoinConference*	pRSPMsg = (KFPC_RSP_TS_JoinConference*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->ConfID,
			pRSPMsg->Result);		

		OnRSP_TS_JoinConference(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_LeaveConference(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_LeaveConference*	pREQMsg = (KFPC_REQ_TS_LeaveConference*)pMsg;

		INFO_LOG(pREQMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx,",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->ConfID);		

		OnREQ_TS_LeaveConference(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_LeaveConference*	pRSPMsg = (KFPC_RSP_TS_LeaveConference*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->ConfID,
			pRSPMsg->Result);		

		OnRSP_TS_LeaveConference(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_ChangeConnectMode(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_ChangeConnectMode*	pREQMsg = (KFPC_REQ_TS_ChangeConnectMode*)pMsg;

		INFO_LOG(pREQMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx,"
			"ConnectMode:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->ConnectMode);		

		OnREQ_TS_ChangeConnectMode(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_ChangeConnectMode*	pRSPMsg = (KFPC_RSP_TS_ChangeConnectMode*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_ChangeConnectMode(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}

void KFPC_TServerAPIHandler::RecvTS_CollectDTMF(KFPC_MSG_HEADER* pMsg)
{

	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_CollectDTMF*	pReqMsg		= (KFPC_REQ_TS_CollectDTMF*)pMsg;
		KFPC_DTMFParam&				DTMFParam	= pReqMsg->DTMFParam;

		INFO_LOG(pReqMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"DTMFParam.MODE:0x%x,"
			"DTMFParam.MaxDigits:%u,"
			"DTMFParam.TermgChar:%u,"
			"DTMFParam.VoiceStopFlag:%u,"
			"DTMFParam.FirstDigitInform:%u,"
			"DTMFParam.FirstDigitTimer:%u,"
			"DTMFParam.InterDigitermer:%u,"
			"DTMFParam.CompletionTimer:%u,"
			"MixCollect:%u"
			,
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,	
			DTMFParam.MODE,
			DTMFParam.MaxDigits,
			DTMFParam.TermgChar,
			DTMFParam.VoiceStopFlag,
			DTMFParam.FirstDigitInform,
			DTMFParam.FirstDigitTimer,
			DTMFParam.InterDigitermer,
			DTMFParam.CompletionTimer,
			pReqMsg->MixCollect
			);


		OnREQ_TS_CollectDTMF(pReqMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_CollectDTMF*	pRSPMsg = (KFPC_RSP_TS_CollectDTMF*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		


		OnRSP_TS_CollectDTMF(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}	
}
void KFPC_TServerAPIHandler::RecvTS_StopCollectDTMF(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_StopCollectDTMF*	pREQMsg = (KFPC_REQ_TS_StopCollectDTMF*)pMsg;

		INFO_LOG(pREQMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);		

		OnREQ_TS_StopCollectDTMF(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_StopCollectDTMF*	pRSPMsg = (KFPC_RSP_TS_StopCollectDTMF*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_StopCollectDTMF(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_EVT_CollectDTMFCompleted(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_CollectDTMFCompleted*	pEventMsg = (KFPC_TS_EVT_CollectDTMFCompleted*)pMsg;

		INFO_LOG(pEventMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"DTMFCount:%u,"
			"DTMF:%s,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pEventMsg->DTMFCount,
			pEventMsg->DTMF,
			pEventMsg->Result);		

		OnTS_EVT_CollectDTMFCompleted(pEventMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_PlayVoice(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_PlayVoice*	pReqMsg		= (KFPC_REQ_TS_PlayVoice*)pMsg;
		KFPC_DTMFParam&				DTMFParam	= pReqMsg->DTMFParam;

		INFO_LOG(pReqMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"DTMFParam.MODE:0x%x,"
			"DTMFParam.MaxDigits:%u,"
			"DTMFParam.TermgChar:%u,"
			"DTMFParam.VoiceStopFlag:%u,"
			"DTMFParam.FirstDigitInform:%u,"
			"DTMFParam.FirstDigitTimer:%u,"
			"DTMFParam.InterDigitermer:%u,"
			"DTMFParam.CompletionTimer:%u,"
			"PlayContent:%s,"
			"MixRecord:%d"
			,
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,	
			DTMFParam.MODE,
			DTMFParam.MaxDigits,
			DTMFParam.TermgChar,
			DTMFParam.VoiceStopFlag,
			DTMFParam.FirstDigitInform,
			DTMFParam.FirstDigitTimer,
			DTMFParam.InterDigitermer,
			DTMFParam.CompletionTimer,
			pReqMsg->PlayContent,
			pReqMsg->MixPlay
			);


		OnREQ_TS_PlayVoice(pReqMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_PlayVoice*	pRSPMsg = (KFPC_RSP_TS_PlayVoice*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		


		OnRSP_TS_PlayVoice(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}	
}
void KFPC_TServerAPIHandler::RecvTS_StopPlayVoice(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_StopPlayVoice*	pREQMsg = (KFPC_REQ_TS_StopPlayVoice*)pMsg;

		INFO_LOG(pREQMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"CollectDTMF:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->CollectDTMF);		

		OnREQ_TS_StopPlayVoice(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_StopPlayVoice*	pRSPMsg = (KFPC_RSP_TS_StopPlayVoice*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_StopPlayVoice(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_EVT_PlayVoiceCompleted(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_PlayVoiceCompleted*	pEventMsg = (KFPC_TS_EVT_PlayVoiceCompleted*)pMsg;

		INFO_LOG(pEventMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			,
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);		

		OnTS_EVT_PlayVoiceCompleted(pEventMsg);

	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_RecordFile(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_StartRecordFile*	pReqMsg		= (KFPC_REQ_TS_StartRecordFile*)pMsg;
		unsigned int &				TermChar	= pReqMsg->TermgChar;

		INFO_LOG(pReqMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"TermChar:%u,"
			"FileName:%s,"
			"RecordTime:%u,"
			"MixRecord:%d",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,	
			TermChar,
			pReqMsg->FileName,
			pReqMsg->RecordTime,
			pReqMsg->MixRecord
			);


		OnReq_TS_RecordFile(pReqMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_StartRecordFile*	pRSPMsg = (KFPC_RSP_TS_StartRecordFile*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		


		OnRSP_TS_RecordFile(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}	
}
void KFPC_TServerAPIHandler::RecvTS_StopRecordFile(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_StopRecordFile*	pREQMsg = (KFPC_REQ_TS_StopRecordFile*)pMsg;

		INFO_LOG(pREQMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);		

		OnREQ_TS_StopRecordFile(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_StopRecordFile*	pRSPMsg = (KFPC_RSP_TS_StopRecordFile*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_StopRecordFile(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_EVT_RecordFileCompleted(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_RecordFileCompleted*	pREQMsg = (KFPC_TS_EVT_RecordFileCompleted*)pMsg;

		INFO_LOG(pREQMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);		

		OnTS_EVT_RecordFileCompleted(pREQMsg);

	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
/*
void KFPC_TServerAPIHandler::RecvTS_ConfPlayVoice(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_ConfPlayVoice*	pReqMsg		= (KFPC_REQ_TS_ConfPlayVoice*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx,"
			"PlayContent:%s",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pReqMsg->ConfID,
			pReqMsg->PlayContent
			);

		OnREQ_TS_ConfPlayVoice(pReqMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_ConfPlayVoice*	pRSPMsg = (KFPC_RSP_TS_ConfPlayVoice*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->ConfID,
			pRSPMsg->Result);		


		OnRSP_TS_ConfPlayVoice(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}	
}
void KFPC_TServerAPIHandler::RecvTS_StopConfPlayVoice(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_ConfStopPlayVoice*	pReqMsg		= (KFPC_REQ_TS_ConfStopPlayVoice*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pReqMsg->ConfID
			);

		OnREQ_TS_ConfStopPlayVoice(pReqMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_ConfStopPlayVoice*	pRSPMsg = (KFPC_RSP_TS_ConfStopPlayVoice*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->ConfID,
			pRSPMsg->Result);		


		OnRSP_TS_ConfStopPlayVoice(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}	
}
void KFPC_TServerAPIHandler::RecvTS_EVT_ConfPlayFileCompleted(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_ConfPlayVoiceCompleted*	pReqMsg		= (KFPC_TS_EVT_ConfPlayVoiceCompleted*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pReqMsg->ConfID
			);

		OnTS_EVT_ConfPlayVoiceCompleted(pReqMsg);

	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}	
}
void KFPC_TServerAPIHandler::RecvTS_ConfRecordFile(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_ConfStartRecordFile*	pReqMsg		= (KFPC_REQ_TS_ConfStartRecordFile*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx,"
			"FileName:%s,"
			"RecordTime:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pReqMsg->ConfID,
			pReqMsg->FileName,
			pReqMsg->RecordTime
			);

		OnREQ_TS_ConfStartRecordFile(pReqMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_ConfStartRecordFile*	pRSPMsg = (KFPC_RSP_TS_ConfStartRecordFile*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->ConfID,
			pRSPMsg->Result);		


		OnRSP_TS_ConfStartRecordFile(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}	
}
void KFPC_TServerAPIHandler::RecvTS_StopConfRecordFile(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_ConfStopRecordFile*	pReqMsg		= (KFPC_REQ_TS_ConfStopRecordFile*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pReqMsg->ConfID
			);

		OnREQ_TS_ConfStopRecordFile(pReqMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_ConfStopRecordFile*	pRSPMsg = (KFPC_RSP_TS_ConfStopRecordFile*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->ConfID,
			pRSPMsg->Result);		


		OnRSP_TS_ConfStopRecordFile(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}	
}
void KFPC_TServerAPIHandler::RecvTS_EVT_ConfRecordFileCompleted(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_ConfRecordFileCompleted*	pEventMsg		= (KFPC_TS_EVT_ConfRecordFileCompleted*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ConfID:0x%llx",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pReqMsg->ConfID
			);

		OnTS_EVT_ConfRecordFileCompleted(pEventMsg);

	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}	
}
*/
void KFPC_TServerAPIHandler::RecvTS_SendFax(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_StartSendFax*	pREQMsg = (KFPC_REQ_TS_StartSendFax*)pMsg;

		INFO_LOG(pREQMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"FileName:%s",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->FileName);		

		OnREQ_TS_StartSendFax(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_StartSendFax*	pRSPMsg = (KFPC_RSP_TS_StartSendFax*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_StartSendFax(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_StopSendFax(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_StopSendFax*	pREQMsg = (KFPC_REQ_TS_StopSendFax*)pMsg;

		INFO_LOG(pREQMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);		

		OnREQ_TS_StopSendFax(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_StopSendFax*	pRSPMsg = (KFPC_RSP_TS_StopSendFax*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_StopSendFax(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_EVT_SendFaxCompleted(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_SendFaxCompleted*	pEventMsg = (KFPC_TS_EVT_SendFaxCompleted*)pMsg;

		INFO_LOG(pEventMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"PageCount:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pEventMsg->PageCount,
			pEventMsg->Result);		

		OnTS_EVT_SendFaxCompleted(pEventMsg);

	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_RecvFax(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_RecvFax*	pREQMsg = (KFPC_REQ_TS_RecvFax*)pMsg;

		INFO_LOG(pREQMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"FileName:%s",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->FileName);		

		OnREQ_TS_RecvFax(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_RecvFax*	pRSPMsg = (KFPC_RSP_TS_RecvFax*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_RecvFax(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_StopRecvFax(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_StopReceiveFax*	pREQMsg = (KFPC_REQ_TS_StopReceiveFax*)pMsg;

		INFO_LOG(pREQMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);		

		OnREQ_TS_StopReceiveFax(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_StopReceiveFax*	pRSPMsg = (KFPC_RSP_TS_StopReceiveFax*)pMsg;

		INFO_LOG(pRSPMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_StopReceiveFax(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_EVT_RecvFaxCompleted(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_ReceiveFaxCompleted*	pEventMsg = (KFPC_TS_EVT_ReceiveFaxCompleted*)pMsg;

		INFO_LOG(pEventMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"PageCount:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pEventMsg->PageCount,
			pEventMsg->Result);		

		OnTS_EVT_ReceiveFaxCompleted(pEventMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_ReloadCfg(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_ReloadConfig*	pREQMsg = (KFPC_REQ_TS_ReloadConfig*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);		

		OnREQ_TS_ReloadConfig(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_ReloadConfig*	pRSPMsg = (KFPC_RSP_TS_ReloadConfig*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_ReloadConfig(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_QueryChStatus(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_QueryChStatus*	pREQMsg = (KFPC_REQ_TS_QueryChStatus*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);		

		OnREQ_TS_QueryChStatus(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_QueryChStatus*	pRSPMsg = (KFPC_RSP_TS_QueryChStatus*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_QueryChStatus(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_UpdateChStatus(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_ChStateChanged*	pEventMsg = (KFPC_TS_EVT_ChStateChanged*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ChannelCount:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pEventMsg->ChannelCount);		

		OnTS_EVT_UpdateChStatus(pEventMsg);

	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_SetChStatus(KFPC_MSG_HEADER* pMsg)
{

}
void KFPC_TServerAPIHandler::RecvTS_CoreDump(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_CoreDump*	pREQMsg = (KFPC_REQ_TS_CoreDump*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);		

		OnREQ_TS_CoreDump(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_CoreDump*	pRSPMsg = (KFPC_RSP_TS_CoreDump*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_CoreDump(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_EVT_Alarm(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_AlarmEvent*	pEventMsg = (KFPC_TS_EVT_AlarmEvent*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"AlarmID:%u,"
			"AlarmContent:%s",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pEventMsg->AlarmID,
			pEventMsg->AlarmContent);		

		OnTS_EVT_AlarmEvent(pEventMsg);

	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_WatchTrunkGroup(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_WatchTrunkGroup*	pREQMsg = (KFPC_REQ_TS_WatchTrunkGroup*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"TrunkGroup:%s",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->TrunkGroup);		

		OnREQ_TS_WatchTrunkGroup(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_WatchTrunkGroup*	pRSPMsg = (KFPC_RSP_TS_WatchTrunkGroup*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_WatchTrunkGroup(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_CancelWatchTrunkGroup(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_CancelWatchTrunkGroup*	pREQMsg = (KFPC_REQ_TS_CancelWatchTrunkGroup*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"TrunkGroup:%s",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->TrunkGroup);		

		OnREQ_TS_CancelWatchTrunkGroup(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_CancelWatchTrunkGroup*	pRSPMsg = (KFPC_RSP_TS_CancelWatchTrunkGroup*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"TrunkGroup:%s,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->TrunkGroup,
			pRSPMsg->Result);		

		OnRSP_TS_CancelWatchTrunkGroup(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
void KFPC_TServerAPIHandler::RecvTS_QueryTrunkGroup(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_QueryTrunkGroup*	pREQMsg = (KFPC_REQ_TS_QueryTrunkGroup*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);		

		OnREQ_TS_QueryTrunkGroup(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_QueryTrunkGroup*	pRSPMsg = (KFPC_RSP_TS_QueryTrunkGroup*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_QueryTrunkGroup(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}

void KFPC_TServerAPIHandler::RecvTS_EVT_UpdateTrunkGroup( KFPC_MSG_HEADER* pMsg )
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_UpdateTrunkGroup*	pREQMsg = (KFPC_TS_EVT_UpdateTrunkGroup*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"TrunkGroup:%s",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->TrunkGroup);		

		OnTS_EVT_UpdateTrunkGroup(pREQMsg);

	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}

void KFPC_TServerAPIHandler::RecvTS_MonitorChStatus(KFPC_MSG_HEADER* pMsg)
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_MonitorChStatus*	pREQMsg = (KFPC_REQ_TS_MonitorChStatus*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);		

		OnREQ_TS_MonitorChStatus(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_MonitorChStatus*	pRSPMsg = (KFPC_RSP_TS_MonitorChStatus*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->Result);		

		OnRSP_TS_MonitorChStatus(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}

void KFPC_TServerAPIHandler::RecvTS_PlayDTMF( KFPC_MSG_HEADER* pMsg )
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_TS_PlayDTMF*	pREQMsg = (KFPC_REQ_TS_PlayDTMF*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"CallID:0x%llx,"
			"DTMF:%s",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->CallID,
			pREQMsg->DTMF);		

		OnREQ_TS_PlayDTMF(pREQMsg);

	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_TS_PlayDTMF*	pRSPMsg = (KFPC_RSP_TS_PlayDTMF*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"CallID:0x%llx,"
			"Result:0x%x",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->CallID,
			pRSPMsg->Result);		

		OnRSP_TS_PlayDTMF(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}

void KFPC_TServerAPIHandler::RecvTS_EVT_HookFlash( KFPC_MSG_HEADER* pMsg )
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_HookFlash*	pREQMsg = (KFPC_TS_EVT_HookFlash*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"CallID:0x%llx",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->CallID);		

		OnTS_EVT_HookFlash(pREQMsg);

	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}


//
//void KFPC_TServerAPIHandler::RecvTS_WatchNumStatus(KFPC_MSG_HEADER* pMsg)
//{
//	KFPC_MSG_HEADER&				Header					= *pMsg;
//
//	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
//	{
//		KFPC_REQ_TS_WatchNumStatus*	pREQMsg = (KFPC_REQ_TS_WatchNumStatus*)pMsg;
//
//		INFO_LOG(0,
//			"Header.un32SrcAPPId:0x%x,"
//			"Header.un32DstAPPId:0x%x,"
//			"Header.un32UserContext1:%u,"
//			"Header.un32UserContext2:%u,"
//			"CallerNO:%s",
//			Header.un32SrcAPPId,
//			Header.un32DstAPPId,
//			Header.un32UserContext1,
//			Header.un32UserContext2,
//			pREQMsg->CallerNO);		
//
//		OnREQ_TS_WatchNumStatus(pREQMsg);
//
//	}
//	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
//	{
//		KFPC_RSP_TS_WatchNumStatus*	pRSPMsg = (KFPC_RSP_TS_WatchNumStatus*)pMsg;
//
//		INFO_LOG(0,
//			"Header.un32SrcAPPId:0x%x,"
//			"Header.un32DstAPPId:0x%x,"
//			"Header.un32UserContext1:%u,"
//			"Header.un32UserContext2:%u,"
//			"Result:0x%x",
//			Header.un32SrcAPPId,
//			Header.un32DstAPPId,
//			Header.un32UserContext1,
//			Header.un32UserContext2,
//			pRSPMsg->Result);		
//
//		OnRSP_TS_WatchNumStatus(pRSPMsg);
//	}
//	else
//	{
//		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);
//
//	}
//}
//
//void KFPC_TServerAPIHandler::RecvTS_EVT_NumStatusUpdate(KFPC_MSG_HEADER* pMsg)
//{
//	KFPC_MSG_HEADER&				Header					= *pMsg;
//
//	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
//	{
//		KFPC_TS_EVT_WatchNumStatus*	pEventMsg = (KFPC_TS_EVT_WatchNumStatus*)pMsg;
//
//		INFO_LOG(0,
//			"Header.un32SrcAPPId:0x%x,"
//			"Header.un32DstAPPId:0x%x,"
//			"Header.un32UserContext1:%u,"
//			"Header.un32UserContext2:%u,"
//			"CallerNO:%s,"
//			"Channel:%u,"
//			"State:%u",
//			Header.un32SrcAPPId,
//			Header.un32DstAPPId,
//			Header.un32UserContext1,
//			Header.un32UserContext2,
//			pEventMsg->CallerNO,
//			pEventMsg->Channel,
//			pEventMsg->State);		
//
//		OnTS_EVT_NumStatusUpdate(pEventMsg);
//
//	}
//	else
//	{
//		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);
//
//	}
//}
void KFPC_TServerAPIHandler::OnREQ_TS_GetTSVersion( KFPC_REQ_TS_GetTSVersion* pMsg )
{
	SendRSP_TS_GetTSVersion(pMsg->Header.un32SrcAPPId,
							pMsg->Header.un32UserContext1,
							pMsg->Header.un32UserContext2,
							"1.0");
}

void KFPC_TServerAPIHandler::OnRSP_TS_GetTSVersion( KFPC_RSP_TS_GetTSVersion* pMsg )
{

}

void KFPC_TServerAPIHandler::RecvMsg( KFPC_MSG_HEADER* pMsg )
{
	unsigned int MsgGroupID = KFPC_MSG_ID_GET_GROUP(pMsg->un32MsgId);

	if(MsgGroupID ==  KFPC_ID_CLASS_COM_TSERVER &&
		KFPC_MSG_ID_TS_END > pMsg->un32MsgId )
	{
		MessageProcFun pFun = m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(pMsg->un32MsgId)];
	
		if(pFun != NULL)
		{
			(this->*(pFun))(pMsg);
		}
	}
}

void KFPC_TServerAPIHandler::RecvTS_EVT_ExtNum2CCS( KFPC_MSG_HEADER* pMsg )
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_ExtNum2CCS*	pREQMsg = (KFPC_TS_EVT_ExtNum2CCS*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"Flag:%u,"
			"ExtNum:%s,"
			"CCSID:%u"
			,
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->Flag,
			pREQMsg->ExtNum,
			pREQMsg->CCS);		

		OnTS_EVT_ExtNum2CCS(pREQMsg);

	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}

void KFPC_TServerAPIHandler::RecvTS_EVT_PassAnswerCall( KFPC_MSG_HEADER* pMsg )
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_EVENT == pMsg->un32MsgType)
	{
		KFPC_TS_EVT_PassAnswerCall*	pEventMsg = (KFPC_TS_EVT_PassAnswerCall*)pMsg;

		INFO_LOG(pEventMsg->CallID,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);		

		OnTS_EVT_PassAnswerCall(pEventMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
