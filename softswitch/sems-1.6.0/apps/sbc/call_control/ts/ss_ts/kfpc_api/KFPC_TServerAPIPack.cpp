#include "KFPC_TServerAPIPack.h"
#include "kfpc_logex.h"


KFPC_TServerAPIPack::KFPC_TServerAPIPack(void)
{
	m_pLibParam = KFPC_GetLibParam();
}


KFPC_TServerAPIPack::~KFPC_TServerAPIPack(void)
{
}

int KFPC_TServerAPIPack::SendMsg( KFPC_MSG_HEADER* pMsg )
{
	return KFPC_SendMsg(pMsg,NULL);
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_GetTSVersion( unsigned int DstAPPId,unsigned int UserContext1,
	                                                       unsigned int UserContext2 )
{

	KFPC_REQ_TS_GetTSVersion* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_GetTSVersion),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_GetTSVersion,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send get ts version request.DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",
			DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",
			DstAPPId,UserContext1,UserContext2);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_GetTSVersion( unsigned int DstAPPId,unsigned int UserContext1,
	                                                       unsigned int UserContext2,const char *pVersion )
{

	KFPC_RSP_TS_GetTSVersion* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_GetTSVersion),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_GetTSVersion,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	strncpy(pMsg->Version,pVersion,KFPC_MAX_VERSION_STR_SIZE);
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send get ts version response	DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",
			DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",
			DstAPPId,UserContext1,UserContext2);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_AcceptCall( unsigned int DstAPPId,unsigned int UserContext1,
														 unsigned int UserContext2,unsigned long long CallID)
{
	
	KFPC_REQ_TS_AcceptCall* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_AcceptCall),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_AcceptCall,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send accept call request DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",
			DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",
			DstAPPId,UserContext1,UserContext2);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_AcceptCall( unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
														 unsigned long long	CallID,unsigned int Result)
{

	KFPC_RSP_TS_AcceptCall* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_AcceptCall),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_AcceptCall,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send accept call response  DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",
			DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);
		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_AnswerCall(unsigned int DstAPPId,unsigned int UserContext1,
	                                                    unsigned int UserContext2,unsigned long long CallID)
{

	KFPC_REQ_TS_AnswerCall* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_AnswerCall),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_AnswerCall,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send answer call request "
						 "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);
		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_AnswerCall(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
	                                                    unsigned long long	CallID,unsigned int Result)
{

	KFPC_RSP_TS_AnswerCall* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_AnswerCall),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_AnswerCall,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send answer call response DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",
			DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",
			DstAPPId,UserContext1,UserContext2,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_ReleaseCall(unsigned int DstAPPId,unsigned int	UserContext1,
	                                                     unsigned int UserContext2,unsigned long long CallID,unsigned int Cause)
{

	KFPC_REQ_TS_ReleaseCall* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_ReleaseCall),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_ReleaseCall,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Cause = Cause;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send release call request DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Cause:%d",
			DstAPPId,UserContext1,UserContext2,Cause);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Cause:%d",
			DstAPPId,UserContext1,UserContext2,Cause);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_ReleaseCall(unsigned int DstAPPId,unsigned int	UserContext1,
	                                                     unsigned int UserContext2,unsigned long long CallID,unsigned int Result)
{


	KFPC_RSP_TS_ReleaseCall* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_ReleaseCall),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_ReleaseCall,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send release call response DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",
			DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",
			DstAPPId,UserContext1,UserContext2,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_CallOut(unsigned int DstAPPId,unsigned int	UserContext1,
	                                                 unsigned int UserContext2,KFPC_DEVICE &Device,const char* InTrunkGroup)
{

	unsigned int Ret = 0;
	KFPC_REQ_TS_CallOut* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_CallOut),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_CallOut,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	memcpy(&pMsg->Device , &Device, sizeof(KFPC_DEVICE));
	
	strncpy(pMsg->InTrunkGroup,InTrunkGroup,KFPC_TRUNKGROUP_NAME_LEN-1);

	if((Ret =SendMsg((KFPC_MSG_HEADER *)pMsg)) != 0)
	{
		ERROR_LOG(0,"Failed to send call out request DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,"
				"Type:%d,Span:%d,Channel:%d,TrunkGroup:%s,CallerNO:%s,CalledNO:%s,OriginalCalled:%s,RedirectingNum:%s,InTrunkGroup:%s",\
						  DstAPPId,UserContext1,UserContext2,Device.Type,Device.Span,Device.TimeSlot,Device.TrunkGroup,Device.CallerNO,Device.CalledNO,\
						  Device.OriginalCalled,Device.RedirectingNum,InTrunkGroup);

		return Ret;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,"
					"Type:%d,Span:%d,Channel:%d,TrunkGroup:%s,CallerNO:%s,CalledNO:%s,RedirectingNum:%s,OriginalCalled:%s,InTrunkGroup:%s",\
					DstAPPId,UserContext1,UserContext2,Device.Type,Device.Span,Device.TimeSlot,Device.TrunkGroup,Device.CallerNO,Device.CalledNO,\
					Device.RedirectingNum,Device.OriginalCalled,InTrunkGroup);
		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_CallOut(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
													 unsigned long long	CallID,unsigned int	Result,unsigned int Cause,KFPC_DEVICE* pDevice,
													 unsigned int		SignalType)
{


	KFPC_RSP_TS_CallOut* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_CallOut),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_CallOut,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Cause = Cause;
	pMsg->Result = Result;
	memcpy(&pMsg->Device,pDevice,sizeof(KFPC_DEVICE));
	pMsg->SignalType = SignalType;

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send call out response "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Cause:%d,Result:%u,"
					"Device.Span:%u,"
					"Device.Type:%u,"
					"Device.TrunkGroup:%s,"
					"Device.CallerNO:%s,"
					"Device.CalledNO:%s,"
					"Device.Channel:%u,"
					"Device.OriginalCalled:%s,"
					"Device.RedirectingNum:%s,"
					"SignalType:%s",					
					DstAPPId,UserContext1,UserContext2,Cause,Result,
					pMsg->Device.Span,
					pMsg->Device.Type,
					pMsg->Device.TrunkGroup,
					pMsg->Device.CallerNO,
					pMsg->Device.CalledNO,
					pMsg->Device.TimeSlot,
					pMsg->Device.OriginalCalled,
					pMsg->Device.RedirectingNum,
					SignalTypeToStr(IntToSignalType(SignalType)));

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Cause:%d,Result:%u,"
			"Device.Span:%u,"
			"Device.Type:%u,"
			"Device.TrunkGroup:%s,"
			"Device.CallerNO:%s,"
			"Device.CalledNO:%s,"
			"Device.Channel:%u,"
			"Device.OriginalCalled:%s,"
			"Device.RedirectingNum:%s,"
			"SignalType:%s",	
			DstAPPId,UserContext1,UserContext2,Cause,Result,
			pMsg->Device.Span,
			pMsg->Device.Type,
			pMsg->Device.TrunkGroup,
			pMsg->Device.CallerNO,
			pMsg->Device.CalledNO,
			pMsg->Device.TimeSlot,
			pMsg->Device.OriginalCalled,
			pMsg->Device.RedirectingNum,
			SignalTypeToStr(IntToSignalType(SignalType)));

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendTS_EVT_IncomingCall(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
	                                                      unsigned long long CallID,KFPC_DEVICE	&Device,unsigned int SignalType)
{


	KFPC_TS_EVT_IncomingCall* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_IncomingCall),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_EVT_IncomingCall,
		KFPC_MSG_TYPE_EVENT,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Device = Device;
	pMsg->SignalType = SignalType;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(pMsg->CallID,"Failed to send incoming call event "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,SignalType:%d "
					"Type:%d,Span:%d,TimeSlot:%d,TrunkGroup:%s,CallerNO:%s,CalledNO:%s,RedirectingNum:%s,OriginalCalled:%s",
					DstAPPId,UserContext1,UserContext2,SignalType,Device.Type,Device.Span,Device.TimeSlot,Device.TrunkGroup,Device.CallerNO,\
					Device.CalledNO,Device.RedirectingNum,Device.OriginalCalled);

		return -1;
	}
	else
	{
		INFO_LOG(pMsg->CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,SignalType:%d "
					"Type:%d,Span:%d,TimeSlot:%d,TrunkGroup:%s,CallerNO:%s,CalledNO:%s,RedirectingNum:%s,OriginalCalled:%s",
					DstAPPId,UserContext1,UserContext2,SignalType,Device.Type,Device.Span,Device.TimeSlot,Device.TrunkGroup,Device.CallerNO,\
					Device.CalledNO,Device.RedirectingNum,Device.OriginalCalled);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendTS_EVT_AlertCall(unsigned int	DstAPPId,unsigned int UserContext1,unsigned int	UserContext2,
	                                                   unsigned long long CallID,unsigned int Cause)
{


	KFPC_TS_EVT_AlertCall* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_AlertCall),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_EVT_AlertCall,
		KFPC_MSG_TYPE_EVENT,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Cause = Cause;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send alert call event DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Cause:%d",
			DstAPPId,UserContext1,UserContext2,Cause);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Cause:%d",
			DstAPPId,UserContext1,UserContext2,Cause);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendTS_EVT_AnsweredCall(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
	                                                      unsigned long long CallID)
{


	KFPC_TS_EVT_AnsweredCall* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_AnsweredCall),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_EVT_AnsweredCall,
		KFPC_MSG_TYPE_EVENT,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send answered call event "
						  "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);


		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendTS_EVT_ReleasedCall(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
	                                                      unsigned long long CallID,unsigned int Cause)
{


	KFPC_TS_EVT_ReleasedCall* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_ReleasedCall),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_EVT_ReleasedCall,
		KFPC_MSG_TYPE_EVENT,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Cause = Cause;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send released call event "
						 "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Cause:%d",DstAPPId,UserContext1,UserContext2,Cause);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Cause:%d, SerialNumber:0x%x ",DstAPPId,UserContext1,UserContext2,Cause,pMsg->Header.un32SerialNumber);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_Connect(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
	                                                 unsigned long long CallID1,unsigned long long CallID2,unsigned int		ConnectMode,unsigned int StopMedia)
{


	KFPC_REQ_TS_Connect* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_Connect),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_Connect,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID1 = CallID1;
	pMsg->CallID2 = CallID2;
	pMsg->ConnectMode = ConnectMode;
	pMsg->StopMedia = StopMedia;

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID1,"Failed to send connect request "
						 "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,CallID2:0x%llx,ConnectMode:%d,StopMedia:0x%x",
						 DstAPPId,UserContext1,UserContext2,CallID2,ConnectMode,StopMedia);

		return -1;
	}
	else
	{
		INFO_LOG(CallID1,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,CallID2:0x%llx,ConnectMode:%d,StopMedia:0x%x",
			DstAPPId,UserContext1,UserContext2,CallID2,ConnectMode,StopMedia);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_Connect(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
	                                                 unsigned long long CallID1,unsigned long long CallID2,unsigned int Result,unsigned long long Session)
{


	KFPC_RSP_TS_Connect* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_Connect),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_Connect,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID1 = CallID1;
	pMsg->CallID2 = CallID2;
	pMsg->Result = Result;
	pMsg->SessionID = Session;

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID1,"Failed to send connect response "
						  "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,CallID2:0x%llx,Result:%u,Session:0x%llx",\
						  DstAPPId,UserContext1,UserContext2,CallID2,Result,Session);

		return -1;
	}
	else
	{
		INFO_LOG(CallID1,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,CallID2:0x%llx,Result:%u,Session:0x%llx",\
			DstAPPId,UserContext1,UserContext2,CallID2,Result,Session);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_Disconnect(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
	                                                    unsigned long long CallID)
{


	KFPC_REQ_TS_Disconnect* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_Disconnect),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_Disconnect,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send disconnect request "
						  "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",\
						  DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",\
						  DstAPPId,UserContext1,UserContext2);
		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_Disconnect(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
	                                                    unsigned long long CallID,unsigned int Result)
{


	KFPC_RSP_TS_Disconnect* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_Disconnect),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_Disconnect,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(CallID,"Failed to call KFPC_AllocMsg");
		return -1;
	}


	pMsg->CallID = CallID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send disconnect response "
						  "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",\
						  DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",\
						  DstAPPId,UserContext1,UserContext2,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_CreateConference(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
	                                                          unsigned int NodeID,unsigned int MaxMember,unsigned int TserID,unsigned int CCSID)
{


	KFPC_REQ_TS_CreateConference* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_CreateConference),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_CreateConference,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->NodeID = NodeID;
	pMsg->MaxMember = MaxMember;
	pMsg->TserverID = TserID;
	pMsg->CCSID = CCSID;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send create conference request "
						  "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,NodeID:%d,MaxMember:%d, CCSID:%u",\
						  DstAPPId,UserContext1,UserContext2,NodeID,MaxMember,CCSID);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,NodeID:%d,MaxMember:%d,CCSID:%u",\
					DstAPPId,UserContext1,UserContext2,NodeID,MaxMember,CCSID);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_CreateConference(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
	                                                          unsigned long long ConfID,unsigned int CCSID,unsigned int Result)
{


	KFPC_RSP_TS_CreateConference* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_CreateConference),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_CreateConference,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->ConfID = ConfID;
	pMsg->CCSID = CCSID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(ConfID,"Failed to send create conference response "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:0x%llx,Result:%u",\
					DstAPPId,UserContext1,UserContext2,ConfID,Result);

		return -1;
	}
	else
	{
		INFO_LOG(ConfID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:0x%llx,Result:%u",\
					DstAPPId,UserContext1,UserContext2,ConfID,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_FreeConference(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
	                                                        unsigned long long ConfID)
{


	KFPC_REQ_TS_FreeConference* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_FreeConference),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_FreeConference,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->ConfID = ConfID;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(ConfID,"Failed to send free conference request "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:0x%llx",DstAPPId,UserContext1,UserContext2,ConfID);

		return -1;
	}
	else
	{
		INFO_LOG(ConfID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:0x%llx",DstAPPId,UserContext1,UserContext2,ConfID);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_FreeConference(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
	                                                        unsigned long long ConfID,unsigned int Result)
{


	KFPC_RSP_TS_FreeConference* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_FreeConference),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_FreeConference,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->ConfID = ConfID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{

		ERROR_LOG(pMsg->ConfID,"Failed to send free conference response "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:0x%llx,Result:%u",\
					DstAPPId,UserContext1,UserContext2,ConfID,Result);
		return -1;
	}
	else
	{
		INFO_LOG(pMsg->ConfID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:0x%llx,Result:%u",\
					DstAPPId,UserContext1,UserContext2,ConfID,Result);
		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_JoinConference(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
	                                                        unsigned long long CallID,unsigned long long ConfID,unsigned int JoinMode,
															int	DTMFSilence,unsigned int	StopMedia)
{


	KFPC_REQ_TS_JoinConference* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_JoinConference),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_JoinConference,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->ConfID = ConfID;
	pMsg->DTMFSilence = DTMFSilence;
	pMsg->JoinMode = JoinMode;
	pMsg->StopMedia = StopMedia;

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send join conference request "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:0x%llx,DTMFSilence:%d,JoinMode:%d,StopMedia:0x%x",\
					DstAPPId,UserContext1,UserContext2,ConfID,DTMFSilence,JoinMode,StopMedia);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:0x%llx,DTMFSilence:%d,JoinMode:%d,StopMedia:0x%x",\
						 DstAPPId,UserContext1,UserContext2,ConfID,DTMFSilence,JoinMode,StopMedia);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_JoinConference(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
	                                                        unsigned long long CallID,unsigned long long ConfID,unsigned int Result,unsigned long long Session)
{

	KFPC_RSP_TS_JoinConference* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_JoinConference),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_JoinConference,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->ConfID = ConfID;
	pMsg->Result = Result;
	pMsg->Session = Session;

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send join conference response "
						 "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:0x%llx,Result:%u,Session:0x%llx",\
						 DstAPPId,UserContext1,UserContext2,ConfID,Result,Session);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:0x%llx,Result:%u,Session:0x%llx",\
						 DstAPPId,UserContext1,UserContext2,ConfID,Result,Session);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_LeaveConference(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
	                                                         unsigned long long CallID,unsigned long long ConfID)
{


	KFPC_REQ_TS_LeaveConference* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_LeaveConference),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_LeaveConference,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->ConfID = ConfID;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send leave conference request "
						 "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:0x%llx",\
						 DstAPPId,UserContext1,UserContext2,ConfID);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:0x%llx",\
						 DstAPPId,UserContext1,UserContext2,ConfID);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_LeaveConference(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
	                                                         unsigned long long CallID,unsigned long long ConfID,unsigned int Result)
{


	KFPC_RSP_TS_LeaveConference* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_LeaveConference),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_LeaveConference,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->ConfID = ConfID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send leave conference response "
						 "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:0x%llx,Result:%u",\
						 DstAPPId,UserContext1,UserContext2,ConfID,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:0x%llx,Result:%u",\
						 DstAPPId,UserContext1,UserContext2,ConfID,Result);


		return 0;
	}
}


unsigned int KFPC_TServerAPIPack::SendREQ_TS_ChangeConnectMode(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
	                                                              unsigned long long CallID,unsigned int ConnectMode)
{


	KFPC_REQ_TS_ChangeConnectMode* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_ChangeConnectMode),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_ChangeConnectMode,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->ConnectMode = ConnectMode;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send change conference mode request "
						 "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConnectMode:%d",\
						 DstAPPId,UserContext1,UserContext2,ConnectMode);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConnectMode:%d",\
						 DstAPPId,UserContext1,UserContext2,ConnectMode);
		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_ChangeConnectMode(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
	                                                              unsigned long long CallID,unsigned int Result)
{


	KFPC_RSP_TS_ChangeConnectMode* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_ChangeConnectMode),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_ChangeConnectMode,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send change conference mode response "
						 "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",\
						 DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",\
						 DstAPPId,UserContext1,UserContext2,Result);
		return 0;
	}
}


unsigned int KFPC_TServerAPIPack::SendREQ_TS_CollectDTMF(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
	                                                     unsigned long long CallID,KFPC_DTMFParam &DTMFParam,unsigned int MixCollect)
{


	KFPC_REQ_TS_CollectDTMF* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_CollectDTMF),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_CollectDTMF,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->DTMFParam = DTMFParam;
	pMsg->MixCollect = MixCollect;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send collect DTMF request "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,MODE:%d,MaxDigits:%d,TermgChar:%d,FirstDigitInform:%d,"
						 "VoiceStopFlag:%d,FirstDigitTimer:%d,InterDigitermer:%d,CompletionTimer:%d",\
						 DstAPPId,UserContext1,UserContext2,DTMFParam.MODE,DTMFParam.MaxDigits,DTMFParam.TermgChar,
						 DTMFParam.FirstDigitInform,DTMFParam.VoiceStopFlag,DTMFParam.FirstDigitTimer,DTMFParam.InterDigitermer,
						 DTMFParam.CompletionTimer);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,MODE:%d,MaxDigits:%d,TermgChar:%d,FirstDigitInform:%d,\
						 VoiceStopFlag:%d,FirstDigitTimer:%d,InterDigitermer:%d,CompletionTimer:%d",\
						 DstAPPId,UserContext1,UserContext2,DTMFParam.MODE,DTMFParam.MaxDigits,DTMFParam.TermgChar,
						 DTMFParam.FirstDigitInform,DTMFParam.VoiceStopFlag,DTMFParam.FirstDigitTimer,DTMFParam.InterDigitermer,
						 DTMFParam.CompletionTimer);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_CollectDTMF(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
														 unsigned long long CallID,unsigned int Result)
{


	KFPC_RSP_TS_CollectDTMF* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_CollectDTMF),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_CollectDTMF,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send collect DTMF response "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_StopCollectDTMF(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
															 unsigned long long CallID)
{


	KFPC_REQ_TS_StopCollectDTMF* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_StopCollectDTMF),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_StopCollectDTMF,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send stop collect DTMF request "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);
		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_StopCollectDTMF(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
															 unsigned long long CallID,unsigned int Result)
{


	KFPC_RSP_TS_StopCollectDTMF* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_StopCollectDTMF),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_StopCollectDTMF,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send stop collect DTMF response "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);
		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendTS_EVT_CollectDTMFCompleted(unsigned int DstAPPId,unsigned int UserContext1,
	                                                              unsigned int UserContext2,unsigned long long CallID,
																  unsigned int DTMFCount,const char * pDTMF,unsigned int Result)
{


	KFPC_TS_EVT_CollectDTMFCompleted* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_CollectDTMFCompleted),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_EVT_CollectDTMFCompleted,
		KFPC_MSG_TYPE_EVENT,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	strncpy(pMsg->DTMF,pDTMF,KFPC_MAX_DTMF_SIZE);
	pMsg->DTMFCount = DTMFCount;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send collect DTMF complete event "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,DTMF:%s,DTMFCount:%d,Result:%u",
						 DstAPPId,UserContext1,UserContext2,pDTMF,DTMFCount,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,DTMF:%s,DTMFCount:%d,Result:%u",
						 DstAPPId,UserContext1,UserContext2,pDTMF,DTMFCount,Result);
		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_PlayVoice(unsigned int	DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
													   unsigned long long CallID,KFPC_DTMFParam &DTMFParam,const char * pPlayContent,unsigned int MixPlay)
{


	KFPC_REQ_TS_PlayVoice* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_PlayVoice),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_PlayVoice,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->DTMFParam = DTMFParam;
	strncpy(pMsg->PlayContent,pPlayContent,KFPC_MAX_PLAY_CONTENT);
	pMsg->MixPlay = MixPlay;

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send play voice request "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,MODE:%d,MaxDigits:%d,TermgChar:%d,FirstDigitInform:%d,"
						 "VoiceStopFlag:%d,FirstDigitTimer:%d,InterDigitermer:%d,CompletionTimer:%d,PlayContent:%s,MixPlay:%d",\
						 DstAPPId,UserContext1,UserContext2,DTMFParam.MODE,DTMFParam.MaxDigits,DTMFParam.TermgChar,
						 DTMFParam.FirstDigitInform,DTMFParam.VoiceStopFlag,DTMFParam.FirstDigitTimer,DTMFParam.InterDigitermer,
						 DTMFParam.CompletionTimer,pPlayContent,MixPlay);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,MODE:%d,MaxDigits:%d,TermgChar:%d,FirstDigitInform:%d,"
						 "VoiceStopFlag:%d,FirstDigitTimer:%d,InterDigitermer:%d,CompletionTimer:%d,PlayContent:%s,MixPlay:%d.",
						 DstAPPId,UserContext1,UserContext2,DTMFParam.MODE,DTMFParam.MaxDigits,DTMFParam.TermgChar,
						 DTMFParam.FirstDigitInform,DTMFParam.VoiceStopFlag,DTMFParam.FirstDigitTimer,DTMFParam.InterDigitermer,
						 DTMFParam.CompletionTimer,pPlayContent,MixPlay);
		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_PlayVoice(unsigned int	DstAPPId,unsigned int UserContext1,unsigned int	UserContext2,
													   unsigned long long CallID,unsigned int Result)
{


	KFPC_RSP_TS_PlayVoice* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_PlayVoice),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_PlayVoice,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send play voice response "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);
		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_StopPlayVoice(unsigned int	DstAPPId,unsigned int UserContext1,unsigned int	UserContext2,
	                                                       unsigned long long CallID,unsigned int CollectDTMF)
{


	KFPC_REQ_TS_StopPlayVoice* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_StopPlayVoice),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_StopPlayVoice,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->CollectDTMF = CollectDTMF;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send stop play voice request "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,CollectDTMF:%u ",DstAPPId,UserContext1,UserContext2,CollectDTMF);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,CollectDTMF:%u",DstAPPId,UserContext1,UserContext2,CollectDTMF);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_StopPlayVoice(unsigned int	DstAPPId,unsigned int UserContext1,unsigned int	UserContext2,
	                                                       unsigned long long CallID,unsigned int Result)
{


	KFPC_RSP_TS_StopPlayVoice* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_StopPlayVoice),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_StopPlayVoice,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send stop play voice response "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return 0;
	}
}


unsigned int KFPC_TServerAPIPack::SendTS_EVT_PlayVoiceCompleted(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
	                                                            unsigned long long CallID)
{


	KFPC_TS_EVT_PlayVoiceCompleted* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_PlayVoiceCompleted),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_EVT_PlayVoiceCompleted,
		KFPC_MSG_TYPE_EVENT,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send play voice complete event "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);


		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_RecordFile(unsigned int	DstAPPId,unsigned int UserContext1,unsigned int	UserContext2,
	                                                   unsigned long long CallID,unsigned int	TermgChar,const char *pFileName,
													   unsigned int RecordTime,unsigned int	MixRecord)
{


	KFPC_REQ_TS_StartRecordFile* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_StartRecordFile),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_RecordFile,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->TermgChar = TermgChar;
	strncpy(pMsg->FileName,pFileName,KFPC_MAX_FILE_NAME);
	pMsg->RecordTime = RecordTime;
	pMsg->MixRecord = MixRecord;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send record file request "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,TermgChar:%d,"
						"FileName:%s,RecordTime:%d",
						 DstAPPId,UserContext1,UserContext2,TermgChar,pFileName,RecordTime);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,TermgChar:%d,"
						"FileName:%s,RecordTime:%d",
						DstAPPId,UserContext1,UserContext2,TermgChar,pFileName,RecordTime);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_RecordFile(unsigned int	DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
													   unsigned long long CallID,unsigned int Result)
{


	KFPC_RSP_TS_StartRecordFile* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_StartRecordFile),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_RecordFile,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send record file response "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_StopRecordFile(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
															unsigned long long CallID)
{


	KFPC_REQ_TS_StopRecordFile* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_StopRecordFile),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_StopRecordFile,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send stop record file request "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_StopRecordFile(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
															unsigned long long CallID,unsigned int Result)
{


	KFPC_RSP_TS_StopRecordFile* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_StopRecordFile),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_StopRecordFile,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendTS_EVT_RecordFileCompleted(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
																 unsigned long long CallID)
{


	KFPC_TS_EVT_RecordFileCompleted* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_RecordFileCompleted),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_EVT_RecordFileCompleted,
		KFPC_MSG_TYPE_EVENT,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send record file complete event "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return 0;
	}
}

//unsigned int KFPC_TServerAPIPack::SendREQ_TS_ConfPlayVoice(unsigned int	DstAPPId,unsigned int UserContext1,unsigned int	UserContext2,
//														   unsigned long long ConfID,char *pPlayContent)
//{
//	if(m_pLibParam == NULL)
//	{
//		ERROR_LOG(0,"Failed to Get lib params");
//		return -1;
//	}
//
//	KFPC_REQ_TS_ConfPlayVoice* pMsg;
//	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_ConfPlayVoice),
//		(KFPC_MSG_HEADER **)&pMsg,
//		KFPC_MSG_ID_TS_ConfPlayVoice,
//		KFPC_MSG_TYPE_REQUEST,
//		DstAPPId,
//		m_pLibParam->AppInfo.AppID,
//		UserContext1,
//		UserContext2);
//
//	if (pMsg == NULL)
//	{
//		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
//		return -1;
//	}
//
//	pMsg->ConfID = ConfID;
//	strncpy(pMsg->PlayContent,pPlayContent,KFPC_MAX_PLAY_CONTENT);
//	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
//	{
//		ERROR_LOG(0,"Failed to send conference play voice request "
//						 "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:%0x%llx,PlayContent:%s",\
//						  DstAPPId,UserContext1,UserContext2,ConfID,pPlayContent);
//
//		return -1;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//unsigned int KFPC_TServerAPIPack::SendRSP_TS_ConfPlayVoice(unsigned int	DstAPPId,unsigned int UserContext1,unsigned int	UserContext2,
//														   unsigned long long ConfID,unsigned int Result)
//{
//	if(m_pLibParam == NULL)
//	{
//		ERROR_LOG(0,"Failed to Get lib params");
//		return -1;
//	}
//
//	KFPC_RSP_TS_ConfPlayVoice* pMsg;
//	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_ConfPlayVoice),
//		(KFPC_MSG_HEADER **)&pMsg,
//		KFPC_MSG_ID_TS_ConfPlayVoice,
//		KFPC_MSG_TYPE_RESPONSE,
//		DstAPPId,
//		m_pLibParam->AppInfo.AppID,
//		UserContext1,
//		UserContext2);
//
//	if (pMsg == NULL)
//	{
//		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
//		return -1;
//	}
//
//	pMsg->ConfID = ConfID;
//	pMsg->Result = Result;
//	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
//	{
//		ERROR_LOG(0,"Failed to send conference play voice response "
//					DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:%0x%llx,Result:%u",\
//					DstAPPId,UserContext1,UserContext2,ConfID,Result);
//
//		return -1;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//
//unsigned int KFPC_TServerAPIPack::SendREQ_TS_ConfStopPlayVoice(unsigned int	DstAPPId,unsigned int UserContext1,unsigned int	UserContext2,
//															   unsigned long long ConfID)
//{
//	if(m_pLibParam == NULL)
//	{
//		ERROR_LOG(0,"Failed to Get lib params");
//		return -1;
//	}
//
//	KFPC_REQ_TS_ConfStopPlayVoice* pMsg;
//	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_ConfStopPlayVoice),
//		(KFPC_MSG_HEADER **)&pMsg,
//		KFPC_MSG_ID_TS_StopConfPlayVoice,
//		KFPC_MSG_TYPE_REQUEST,
//		DstAPPId,
//		m_pLibParam->AppInfo.AppID,
//		UserContext1,
//		UserContext2);
//
//	if (pMsg == NULL)
//	{
//		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
//		return -1;
//	}
//
//	pMsg->ConfID = ConfID;
//	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
//	{
//		ERROR_LOG(0,"Failed to send stop conference play voice request "
//					DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:%0x%llx",DstAPPId,UserContext1,UserContext2,ConfID);
//
//		return -1;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//unsigned int KFPC_TServerAPIPack::SendRSP_TS_ConfStopPlayVoice(unsigned int	DstAPPId,unsigned int UserContext1,unsigned int	UserContext2,
//																unsigned long long ConfID,unsigned int Result)
//{
//	if(m_pLibParam == NULL)
//	{
//		ERROR_LOG(0,"Failed to Get lib params");
//		return -1;
//	}
//
//	KFPC_RSP_TS_ConfStopPlayVoice* pMsg;
//	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_ConfStopPlayVoice),
//		(KFPC_MSG_HEADER **)&pMsg,
//		KFPC_MSG_ID_TS_StopConfPlayVoice,
//		KFPC_MSG_TYPE_RESPONSE,
//		DstAPPId,
//		m_pLibParam->AppInfo.AppID,
//		UserContext1,
//		UserContext2);
//
//	if (pMsg == NULL)
//	{
//		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
//		return -1;
//	}
//
//	pMsg->ConfID = ConfID;
//	pMsg->Result = Result;
//	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
//	{
//		ERROR_LOG(0,"Failed to send stop conference play voice response "
//					DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:%0x%llx,Result:%u",\
//					DstAPPId,UserContext1,UserContext2,ConfID,Result);
//
//		return -1;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//unsigned int KFPC_TServerAPIPack::SendTS_EVT_ConfPlayVoiceCompleted(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
//																  unsigned long long ConfID)
//{
//	if(m_pLibParam == NULL)
//	{
//		ERROR_LOG(0,"Failed to Get lib params");
//		return -1;
//	}
//
//	KFPC_TS_EVT_ConfPlayVoiceCompleted* pMsg;
//	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_ConfPlayVoiceCompleted),
//		(KFPC_MSG_HEADER **)&pMsg,
//		KFPC_MSG_ID_TS_EVT_ConfPlayFileCompleted,
//		KFPC_MSG_TYPE_EVENT,
//		DstAPPId,
//		m_pLibParam->AppInfo.AppID,
//		UserContext1,
//		UserContext2);
//
//	if (pMsg == NULL)
//	{
//		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
//		return -1;
//	}
//
//	pMsg->ConfID = ConfID;
//	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
//	{
//		ERROR_LOG(0,"Failed to send conference play voice complete event "
//					DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:%0x%llx",DstAPPId,UserContext1,UserContext2,ConfID);
//
//		return -1;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//
//unsigned int KFPC_TServerAPIPack::SendREQ_TS_ConfStartRecordFile(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
//																 unsigned long long ConfID,char *pFileName,unsigned int RecordTime)
//{
//	if(m_pLibParam == NULL)
//	{
//		ERROR_LOG(0,"Failed to Get lib params");
//		return -1;
//	}
//
//	KFPC_REQ_TS_ConfStartRecordFile* pMsg;
//	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_ConfStartRecordFile),
//		(KFPC_MSG_HEADER **)&pMsg,
//		KFPC_MSG_ID_TS_ConfRecordFile,
//		KFPC_MSG_TYPE_REQUEST,
//		DstAPPId,
//		m_pLibParam->AppInfo.AppID,
//		UserContext1,
//		UserContext2);
//
//	if (pMsg == NULL)
//	{
//		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
//		return -1;
//	}
//
//	pMsg->ConfID = ConfID;
//	strncpy(pMsg->FileName,pFileName,KFPC_MAX_FILE_NAME);
//	pMsg->RecordTime = RecordTime;
//	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
//	{
//		ERROR_LOG(0,"Failed to send conference record file request "
//					DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:%0x%llx,FileName:%s,RecordTime:%d",\
//					DstAPPId,UserContext1,UserContext2,ConfID,FileName,RecordTime);
//
//		return -1;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//unsigned int KFPC_TServerAPIPack::SendRSP_TS_ConfStartRecordFile(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
//																 unsigned long long ConfID,unsigned int Result)
//{
//	if(m_pLibParam == NULL)
//	{
//		ERROR_LOG(0,"Failed to Get lib params");
//		return -1;
//	}
//
//	KFPC_RSP_TS_ConfStartRecordFile* pMsg;
//	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_ConfStartRecordFile),
//		(KFPC_MSG_HEADER **)&pMsg,
//		KFPC_MSG_ID_TS_ConfRecordFile,
//		KFPC_MSG_TYPE_RESPONSE,
//		DstAPPId,
//		m_pLibParam->AppInfo.AppID,
//		UserContext1,
//		UserContext2);
//
//	if (pMsg == NULL)
//	{
//		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
//		return -1;
//	}
//
//	pMsg->ConfID = ConfID;
//	pMsg->Result = Result;
//	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
//	{
//		ERROR_LOG(0,"Failed to send conference record file response "
//					DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:%0x%llx,Result:%u",\
//					DstAPPId,UserContext1,UserContext2,ConfID,Result);
//
//		return -1;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//unsigned int KFPC_TServerAPIPack::SendREQ_TS_ConfStopRecordFile(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
//																unsigned long long ConfID)
//{
//	if(m_pLibParam == NULL)
//	{
//		ERROR_LOG(0,"Failed to Get lib params");
//		return -1;
//	}
//
//	KFPC_REQ_TS_ConfStopRecordFile* pMsg;
//	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_ConfStopRecordFile),
//		(KFPC_MSG_HEADER **)&pMsg,
//		KFPC_MSG_ID_TS_StopConfRecordFile,
//		KFPC_MSG_TYPE_REQUEST,
//		DstAPPId,
//		m_pLibParam->AppInfo.AppID,
//		UserContext1,
//		UserContext2);
//
//	if (pMsg == NULL)
//	{
//		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
//		return -1;
//	}
//
//	pMsg->ConfID = ConfID;
//	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
//	{
//		ERROR_LOG(0,"Failed to send stop conference record file request "
//					DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:%0x%llx",DstAPPId,UserContext1,UserContext2,ConfID);
//
//		return -1;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//unsigned int KFPC_TServerAPIPack::SendRSP_TS_ConfStopRecordFile(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
//																unsigned long long ConfID,unsigned int Result)
//{
//	if(m_pLibParam == NULL)
//	{
//		ERROR_LOG(0,"Failed to Get lib params");
//		return -1;
//	}
//
//	KFPC_RSP_TS_ConfStopRecordFile* pMsg;
//	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_ConfStopRecordFile),
//		(KFPC_MSG_HEADER **)&pMsg,
//		KFPC_MSG_ID_TS_StopConfRecordFile,
//		KFPC_MSG_TYPE_RESPONSE,
//		DstAPPId,
//		m_pLibParam->AppInfo.AppID,
//		UserContext1,
//		UserContext2);
//
//	if (pMsg == NULL)
//	{
//		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
//		return -1;
//	}
//
//	pMsg->ConfID = ConfID;
//	pMsg->Result = Result;
//	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
//	{
//		ERROR_LOG(0,"Failed to send stop conference record file response "
//					DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:%0x%llx,Result:%u",\
//					DstAPPId,UserContext1,UserContext2,ConfID,Result);
//
//		return -1;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//unsigned int KFPC_TServerAPIPack::SendTS_EVT_ConfRecordFileCompleted(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
//																	 unsigned long long ConfID)
//{
//	if(m_pLibParam == NULL)
//	{
//		ERROR_LOG(0,"Failed to Get lib params");
//		return -1;
//	}
//
//	KFPC_TS_EVT_ConfRecordFileCompleted* pMsg;
//	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_ConfRecordFileCompleted),
//		(KFPC_MSG_HEADER **)&pMsg,
//		KFPC_MSG_ID_TS_EVT_ConfRecordFileCompleted,
//		KFPC_MSG_TYPE_EVENT,
//		DstAPPId,
//		m_pLibParam->AppInfo.AppID,
//		UserContext1,
//		UserContext2);
//
//	if (pMsg == NULL)
//	{
//		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
//		return -1;
//	}
//
//	pMsg->ConfID = ConfID;
//	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
//	{
//		ERROR_LOG(0,"Failed to send conference record file complete event "
//					DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ConfID:%0x%llx%d",DstAPPId,UserContext1,UserContext2,ConfID);
//
//		return -1;
//	}
//	else
//	{
//		return 0;
//	}
//}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_RecvFax(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
													 unsigned long long CallID,const char *pFileName)
{

	KFPC_REQ_TS_RecvFax* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_RecvFax),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_RecvFax,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	strncpy(pMsg->FileName,pFileName,KFPC_MAX_FILE_NAME);
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send receive fax request "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,FileName:%s",DstAPPId,UserContext1,UserContext2,pFileName);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,FileName:%s",DstAPPId,UserContext1,UserContext2,pFileName);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_RecvFax(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
													 unsigned long long CallID,unsigned int Result)
{


	KFPC_RSP_TS_RecvFax* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_RecvFax),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_RecvFax,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send receive fax response "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_StopReceiveFax(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
														    unsigned long long CallID)
{


	KFPC_REQ_TS_StopReceiveFax* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_StopReceiveFax),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_StopRecvFax,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send stop receive fax request "
						 "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_StopReceiveFax(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
														    unsigned long long CallID,unsigned int Result)
{


	KFPC_RSP_TS_StopReceiveFax* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_StopReceiveFax),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_StopRecvFax,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send stop receive fax response "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendTS_EVT_ReceiveFaxCompleted(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
																 unsigned long long CallID,unsigned int PageCount,unsigned int Result)
{


	KFPC_TS_EVT_ReceiveFaxCompleted* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_ReceiveFaxCompleted),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_EVT_RecvFaxCompleted,
		KFPC_MSG_TYPE_EVENT,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->PageCount = PageCount;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send receive fax complete event "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,PageCount:%d,Result:%u",\
						 DstAPPId,UserContext1,UserContext2,PageCount,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,PageCount:%d,Result:%u",\
						 DstAPPId,UserContext1,UserContext2,PageCount,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_StartSendFax(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
														  unsigned long long CallID,const char *pFileName,const char *pSenderIdent,
														  const char *pSubAddress,const char *pPageHeaderInfo,const char *pIdentifier)
{


	KFPC_REQ_TS_StartSendFax* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_StartSendFax),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_SendFax,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	strncpy(pMsg->FileName,pFileName,KFPC_MAX_FILE_NAME);
	strncpy(pMsg->SenderIdent,pSenderIdent,KFPC_MAX_FAX_INFO);
	strncpy(pMsg->SubAddress,pSubAddress,KFPC_MAX_FAX_INFO);
	strncpy(pMsg->PageHeaderInfo,pPageHeaderInfo,KFPC_MAX_FAX_INFO);
	strncpy(pMsg->Identifier,pIdentifier,KFPC_MAX_FAX_INFO);

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send deliver fax request "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,FileName:%s",DstAPPId,UserContext1,UserContext2,pFileName);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,FileName:%s",DstAPPId,UserContext1,UserContext2,pFileName);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_StartSendFax(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
														  unsigned long long CallID,unsigned int Result)
{


	KFPC_RSP_TS_StartSendFax* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_StartSendFax),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_SendFax,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send deliver fax response "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_StopSendFax(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
														 unsigned long long CallID)
{


	KFPC_REQ_TS_StopSendFax* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_StopSendFax),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_StopSendFax,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send stop deliver fax request "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_StopSendFax(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
														 unsigned long long CallID,unsigned int Result)
{

	KFPC_RSP_TS_StopSendFax* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_StopSendFax),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_StopSendFax,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send stop deliver fax response "
						 "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendTS_EVT_SendFaxCompleted(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
															  unsigned long long CallID,unsigned int PageCount,unsigned int Result)
{


	KFPC_TS_EVT_SendFaxCompleted* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_SendFaxCompleted),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_EVT_SendFaxCompleted,
		KFPC_MSG_TYPE_EVENT,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->PageCount = PageCount;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send deliver fax complete event "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,PageCount:%d,Result:%u",\
						 DstAPPId,UserContext1,UserContext2,PageCount,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,PageCount:%d,Result:%u",\
						 DstAPPId,UserContext1,UserContext2,PageCount,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_ReloadConfig(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2)
{


	KFPC_REQ_TS_ReloadConfig* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_ReloadConfig),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_ReloadCfg,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send reload config request "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_ReloadConfig(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
														  unsigned int Result)
{


	KFPC_RSP_TS_ReloadConfig* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_ReloadConfig),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_ReloadCfg,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send reload config response "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_QueryChStatus(unsigned int	DstAPPId,unsigned int UserContext1,unsigned int	UserContext2)
{


	KFPC_REQ_TS_QueryChStatus* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_QueryChStatus),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_QueryChStatus,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send query channel status request "
						 "DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_QueryChStatus(unsigned int	DstAPPId,unsigned int UserContext1,unsigned int	UserContext2,
														   unsigned int Result)
{ 


	KFPC_RSP_TS_QueryChStatus* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_QueryChStatus),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_QueryChStatus,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send query channel status response "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendTS_EVT_UpdateChStatus(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
															unsigned int ChannelCount,unsigned int* Channel,unsigned int* State)
{

	KFPC_TS_EVT_UpdateChStatus* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_UpdateChStatus),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_UpdateChStatus,
		KFPC_MSG_TYPE_EVENT,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}
	pMsg->ChannelCount = ChannelCount;

	for(unsigned int i=0;i<KFPC_MAX_CHANNEL && i< ChannelCount;i++)
	{
		pMsg->Channel[i] = Channel[i];

		pMsg->State[i] = State[i];
	}

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send update channel status event "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ChannelCount:%d",\
						 DstAPPId,UserContext1,UserContext2,ChannelCount);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ChannelCount:%d",\
					DstAPPId,UserContext1,UserContext2,ChannelCount);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_SetChState(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
													    unsigned int ChannelCount,unsigned int* Channel,unsigned int* State)
{


	KFPC_REQ_TS_SetChState* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_SetChState),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_SetChStatus,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}
	
	pMsg->ChannelCount = ChannelCount;

	for(unsigned int i = 0;i<ChannelCount && i<KFPC_MAX_CHANNEL;i++)
	{
		pMsg->Channel[i] = Channel[i];
		
		pMsg->State[i] = State[i];
	}

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send set channel status request "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ChannelCount:%d",\
					DstAPPId,UserContext1,UserContext2,ChannelCount);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,ChannelCount:%d",\
					DstAPPId,UserContext1,UserContext2,ChannelCount);
		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_SetChState(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
													    unsigned int Result)
{


	KFPC_RSP_TS_SetChState* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_SetChState),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_SetChStatus,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send set channel status response "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",\
					DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",\
					DstAPPId,UserContext1,UserContext2,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_CoreDump(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2)
{


	KFPC_REQ_TS_CoreDump* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_CoreDump),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_CoreDump,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send core dump request "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_CoreDump(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
													  unsigned int Result)
{


	KFPC_RSP_TS_CoreDump* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_CoreDump),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_CoreDump,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send core dump response "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendTS_EVT_AlarmEvent(unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,
													    unsigned int AlarmID,char *pAlarmContent)
{


	KFPC_TS_EVT_AlarmEvent* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_AlarmEvent),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_EVT_Alarm,
		KFPC_MSG_TYPE_EVENT,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->AlarmID = AlarmID;
	strncpy(pMsg->AlarmContent,pAlarmContent,KFPC_MAX_ALARM_CONTENT);
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send alarm event "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,AlarmID:%d,AlarmContent:%s",\
					 DstAPPId,UserContext1,UserContext2,AlarmID,pAlarmContent);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,AlarmID:%d,AlarmContent:%s",\
					DstAPPId,UserContext1,UserContext2,AlarmID,pAlarmContent);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_WatchTrunkGroup(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
															 char* pTrunkGroup)
{


	KFPC_REQ_TS_WatchTrunkGroup* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_WatchTrunkGroup),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_WatchTrunkGroup,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	strncpy(pMsg->TrunkGroup,pTrunkGroup,KFPC_TRUNKGROUP_NAME_LEN);
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send watch trunk group request "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,TrunkGroup:%s",DstAPPId,UserContext1,UserContext2,pTrunkGroup);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,TrunkGroup:%s",DstAPPId,UserContext1,UserContext2,pTrunkGroup);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_WatchTrunkGroup(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
															 char* pTrunkGroup,unsigned int Result)
{


	KFPC_RSP_TS_WatchTrunkGroup* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_WatchTrunkGroup),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_WatchTrunkGroup,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->Result = Result;
	strncpy(pMsg->TrunkGroup,pTrunkGroup,KFPC_TRUNKGROUP_NAME_LEN);
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send watch trunk group response "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,TrunkGroup:%s,Result:%u",\
					DstAPPId,UserContext1,UserContext2,pTrunkGroup,Result);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,TrunkGroup:%s,Result:%u",\
					DstAPPId,UserContext1,UserContext2,pTrunkGroup,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_CancelWatchTrunkGroup(unsigned int	DstAPPId,unsigned int UserContext1,unsigned int	UserContext2,
																   char* pTrunkGroup)
{


	KFPC_REQ_TS_CancelWatchTrunkGroup* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_CancelWatchTrunkGroup),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_CancelWatchTrunkGroup,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	strncpy(pMsg->TrunkGroup,pTrunkGroup,KFPC_TRUNKGROUP_NAME_LEN);
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send cancel watch trunk group request "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,TrunkGroup:%s",DstAPPId,UserContext1,UserContext2,pTrunkGroup);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,TrunkGroup:%s",DstAPPId,UserContext1,UserContext2,pTrunkGroup);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_CancelWatchTrunkGroup(unsigned int	DstAPPId,unsigned int UserContext1,unsigned int	UserContext2,
																   char* pTrunkGroup,unsigned int Result)
{

	KFPC_RSP_TS_CancelWatchTrunkGroup* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_CancelWatchTrunkGroup),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_CancelWatchTrunkGroup,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->Result = Result;
	strncpy(pMsg->TrunkGroup,pTrunkGroup,KFPC_TRUNKGROUP_NAME_LEN);
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send cancel watch trunk group response "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,TrunkGroup:%s,Result:%u",\
					DstAPPId,UserContext1,UserContext2,pTrunkGroup,Result);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,TrunkGroup:%s,Result:%u",\
					DstAPPId,UserContext1,UserContext2,pTrunkGroup,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_QueryTrunkGroup(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2)
{


	KFPC_REQ_TS_QueryTrunkGroup* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_QueryTrunkGroup),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_QueryTrunkGroup,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send query trunk group request "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_QueryTrunkGroup(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int UserContext2,
															 unsigned int Result)
{


	KFPC_RSP_TS_QueryTrunkGroup* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_QueryTrunkGroup),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_QueryTrunkGroup,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send query trunk group response "
					"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendTS_EVT_UpdateTrunkGroup(unsigned int DstAPPId,  char* pTrunkGroup)
{

	KFPC_TS_EVT_UpdateTrunkGroup* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_UpdateTrunkGroup),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_EVT_UpdateTrunkGroup,
		KFPC_MSG_TYPE_EVENT,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		0,
		0);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	strncpy(pMsg->TrunkGroup,pTrunkGroup,KFPC_TRUNKGROUP_NAME_LEN);
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send update trunk group event "
					"DstAPPId:0x%x,TrunkGroup:%s",DstAPPId,pTrunkGroup);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,TrunkGroup:%s",DstAPPId,pTrunkGroup);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendREQ_TS_PlayDTMF( unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,unsigned long long CallID,char *pDTMF )
{
	KFPC_REQ_TS_PlayDTMF* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_REQ_TS_PlayDTMF),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_PlayDTMF,
		KFPC_MSG_TYPE_REQUEST,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	strcpy(pMsg->DTMF,pDTMF);

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send PlayDTMF request "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,DTMF:%s",DstAPPId,UserContext1,UserContext2,pDTMF);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,DTMF:%s",DstAPPId,UserContext1,UserContext2,pDTMF);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendRSP_TS_PlayDTMF( unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,unsigned long long CallID,unsigned int Result )
{
	KFPC_RSP_TS_PlayDTMF* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_RSP_TS_PlayDTMF),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_PlayDTMF,
		KFPC_MSG_TYPE_RESPONSE,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;
	pMsg->Result = Result;
	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send playDTMF response "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Result:%u",DstAPPId,UserContext1,UserContext2,Result);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendTS_EVT_HookFlash( unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,unsigned long long CallID )
{
	KFPC_TS_EVT_HookFlash* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_HookFlash),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_EVT_HookFlash,
		KFPC_MSG_TYPE_EVENT,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send HookFlash event "
						"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendTS_EVT_ExtNum2CCS( unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,unsigned int Flag,const char* ExtNum,unsigned int CCS )
{
	KFPC_TS_EVT_ExtNum2CCS* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_ExtNum2CCS),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_EVT_ExtNum2CCS,
		KFPC_MSG_TYPE_EVENT,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->Flag = Flag;
	pMsg->CCS = CCS;
	strncpy(pMsg->ExtNum,ExtNum,KFPC_MAX_NUMBER_SIZE-1);

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(0,"Failed to send ExtNum2CCS event "
			"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Flag:%u,ExtNum:%s,CCSID:%u",DstAPPId,UserContext1,UserContext2,pMsg->Flag,pMsg->ExtNum,pMsg->CCS);

		return -1;
	}
	else
	{
		INFO_LOG(0,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u,Flag:%u,ExtNum:%s,CCSID:%u",DstAPPId,UserContext1,UserContext2,pMsg->Flag,pMsg->ExtNum,pMsg->CCS);

		return 0;
	}
}

unsigned int KFPC_TServerAPIPack::SendTS_EVT_PassAnswerCall( unsigned int DstAPPId,unsigned int UserContext1,unsigned int UserContext2,unsigned long long CallID )
{
	typedef struct KFPC_TS_EVT_PassAnswerCall
	{
		KFPC_MSG_HEADER Header;									/**< ÏûÏ¢Í· */
		unsigned long long	CallID;								/**< ºô½ÐID */
	}KFPC_TS_EVT_PassAnswerCall;

	KFPC_TS_EVT_PassAnswerCall* pMsg;
	KFPC_AllocMsg(sizeof(KFPC_TS_EVT_ExtNum2CCS),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_TS_EVT_PassAnswerCall,
		KFPC_MSG_TYPE_EVENT,
		DstAPPId,
		m_pLibParam->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg");
		return -1;
	}

	pMsg->CallID = CallID;

	if(SendMsg((KFPC_MSG_HEADER *)pMsg) != 0)
	{
		ERROR_LOG(CallID,"Failed to send answered call event "
			"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);

		return -1;
	}
	else
	{
		INFO_LOG(CallID,"DstAPPId:0x%x,UserContext1:%u,UserContext2:%u",DstAPPId,UserContext1,UserContext2);


		return 0;
	}
}

