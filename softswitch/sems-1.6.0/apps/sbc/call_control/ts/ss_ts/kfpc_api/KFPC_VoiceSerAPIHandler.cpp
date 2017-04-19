#include "KFPC_VoiceSerAPIHandler.h"
#include "kfpc_voiceser_api.h"
#include "kfpc_logex.h"
#include "kfpc_api.h"

KFPC_VoiceSerAPIHandler::KFPC_VoiceSerAPIHandler(void)
{
	
}


KFPC_VoiceSerAPIHandler::~KFPC_VoiceSerAPIHandler(void)
{
}
void KFPC_VoiceSerAPIHandler::RecvVOICE_FILE_COMPRESS(KFPC_MSG_HEADER* pMsg)
{

	if(pMsg->un32MsgType == KFPC_MSG_TYPE_REQUEST)
	{
		//Ð´ÈÕÖ¾
		KFPC_REQ_API_VOICE_FILE_COMPRESS *pVoiceFileCompress = (KFPC_REQ_API_VOICE_FILE_COMPRESS*)pMsg;


		INFO_LOG(pVoiceFileCompress->CallID,"MsgID:%s,AppID:0x%x,OrgFileName:%s,DstFileName:%s,MsgLen:%d",
		     KFPC_MSG_ID_VOICE_TO_STRING(pVoiceFileCompress->Header.un32MsgId),
			 pVoiceFileCompress->Header.un32SrcAPPId,
			 pVoiceFileCompress->OrgFileName,
			 pVoiceFileCompress->DstFileName,
			 pVoiceFileCompress->Header.un32Length);

		OnREQ_API_VOICE_FILE_COMPRESS(pVoiceFileCompress);
	}
	else if(pMsg->un32MsgType == KFPC_MSG_TYPE_RESPONSE)
	{
		KFPC_RSP_API_VOICE_FILE_COMPRESS* pRspVoiceFileCompress = (KFPC_RSP_API_VOICE_FILE_COMPRESS*)pMsg;
		INFO_LOG(pRspVoiceFileCompress->CallID,"MsgID:%s,AppID:0x%x,Result:%u",
			KFPC_MSG_ID_VOICE_TO_STRING(pRspVoiceFileCompress->Header.un32MsgId),
			pRspVoiceFileCompress->Header.un32SrcAPPId,
			pRspVoiceFileCompress->Result);

		OnRSP_API_VOICE_FILE_COMPRESS(pRspVoiceFileCompress);
	}
}

int KFPC_VoiceSerAPIHandler::SendMsg( KFPC_MSG_HEADER* pMsg )
{
	return KFPC_SendMsg(pMsg,NULL);
}

void KFPC_VoiceSerAPIHandler::RecvMsg(KFPC_MSG_HEADER* pMsg)
{
	if(pMsg->un32MsgId == KFPC_MSG_ID_VOICE_COMPRESS_MSG)
	{
		RecvVOICE_FILE_COMPRESS(pMsg);
	}
	else if(KFPC_MSG_ID_VOICE_EVT_SERVER_INFO == pMsg->un32MsgId)
	{
		RecvVOICE_EVT_SERVER_INFO(pMsg);
	}
	else
	{
		ERROR_LOG(0,"Msg[%u] is invalid\n",pMsg->un32MsgId);
	}
}

void KFPC_VoiceSerAPIHandler::SendREQ_API_VOICE_FILE_COMPRESS(unsigned long long CallID,unsigned int DestAppID,
															  const char *OrgFileName,const char *DstFileName)
{
	KFPC_REQ_API_VOICE_FILE_COMPRESS* pMsg = NULL;

	KFPC_AllocMsg(sizeof(KFPC_REQ_API_VOICE_FILE_COMPRESS),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_VOICE_COMPRESS_MSG,
		KFPC_MSG_TYPE_REQUEST,
		DestAppID,
		KFPC_GetLibParam()->AppInfo.AppID,
		0,
		0);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return;
	}

	pMsg->CallID = CallID;
	strncpy(pMsg->OrgFileName,OrgFileName,KFPC_MAX_FILE_NAME);
	strncpy(pMsg->DstFileName,DstFileName,KFPC_MAX_FILE_NAME);

	unsigned int Ret = SendMsg((KFPC_MSG_HEADER *)pMsg);
	if(Ret != 0)
	{
		ERROR_LOG(CallID,"Failed to send voice file compress request message.OrgFileName:%s,DstFileName:%s",OrgFileName,DstFileName);
	}
	else
	{
		INFO_LOG(CallID,"send voice file compress request message.OrgFileName:%s,DstFileName:%s",OrgFileName,DstFileName);

	}
}

void KFPC_VoiceSerAPIHandler::SendRSP_API_VOICE_FILE_COMPRESS(unsigned long long CallID,unsigned int DestAppID,
															  unsigned int Result)
{
	KFPC_RSP_API_VOICE_FILE_COMPRESS* pMsg = NULL;

	KFPC_AllocMsg(sizeof(KFPC_RSP_API_VOICE_FILE_COMPRESS),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_VOICE_COMPRESS_MSG,
		KFPC_MSG_TYPE_RESPONSE,
		DestAppID,
		KFPC_GetLibParam()->AppInfo.AppID,
		0,
		0);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return;
	}

	pMsg->CallID = CallID;
	pMsg->Result = Result;

	INFO_LOG(pMsg->CallID,"MsgID:%s,SrcAppID:0x%x,DstAppID:0x%x,Result:%u",KFPC_MSG_ID_VOICE_TO_STRING(pMsg->Header.un32MsgId),
		pMsg->Header.un32SrcAPPId,pMsg->Header.un32DstAPPId,pMsg->Result);

	unsigned int Ret = SendMsg((KFPC_MSG_HEADER *)pMsg);
	if(Ret != 0)
	{
		ERROR_LOG(CallID,"Failed to send voice file compress response message.");
	}
}

void KFPC_VoiceSerAPIHandler::RecvVOICE_EVT_SERVER_INFO( KFPC_MSG_HEADER* pMsg )
{
	KFPC_EVT_API_VOICE_SERVER_INFO* pEvt = (KFPC_EVT_API_VOICE_SERVER_INFO*)pMsg;

	INFO_LOG(0,"DstAppID:0x%x,PRD:%u",pMsg->un32SrcAPPId,pEvt->PRDID);
	OnEVT_API_VOICE_SERVER_INFO(pEvt);
}

void KFPC_VoiceSerAPIHandler::SendEVT_API_VOICE_SERVER_INFO( unsigned int DestAppID,unsigned int PRDID )
{
	KFPC_EVT_API_VOICE_SERVER_INFO* pMsg = NULL;

	KFPC_AllocMsg(sizeof(KFPC_EVT_API_VOICE_SERVER_INFO),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_VOICE_EVT_SERVER_INFO,
		KFPC_MSG_TYPE_EVENT,
		DestAppID,
		KFPC_GetLibParam()->AppInfo.AppID,
		0,
		0);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return;
	}

	pMsg->PRDID = PRDID;

	INFO_LOG(0,"DstAppID:0x%x,PRDID:%u",pMsg->Header.un32DstAPPId,pMsg->PRDID);

	unsigned int Ret = SendMsg((KFPC_MSG_HEADER *)pMsg);
	if(Ret != 0)
	{
		ERROR_LOG(0,"Failed to send voice file compress response message.");
	}
}