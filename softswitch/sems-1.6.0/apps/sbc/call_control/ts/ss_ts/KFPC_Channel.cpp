#include "kfpc_logex.h"

#include "KFPC_DBThreadPool.h"
//#include "KFPC_DBTaskImp.h"
#include "KFPC_Channel.h"
#include "KFPC_TServerErr.h"
#include "kfpc_api.h"
#include "KFPC_TServerAPIHandlerImp.h"
#//include "KFPC_EH_MsgID.h"
#include "KFPC_TServerErr.h"
#include "KFPC_AppMainThread.h"
#include "KFPC_CmdThreadtask.h"
#include "KFPC_TServerConfigFile.h"
#include "KFPC_StringUtils.h"
#include "KFPC_MonitorRefreshData.h"
#include "KFPC_DBTask.h"
#include "KFPC_DBThreadPool.h"
#include "KFPC_ContactCenterPublicDef.h"
#include "KFPC_StringUtils.h"
#include "KFPC_CmdMgr.h"

KFPC_Log* KFPC_CDR_Loger();

static	unsigned int g_ChannelID_Gen = 0;

static  int g_CallCount = 0;

KFPC_Channel::KFPC_Channel(void):
m_ID(g_ChannelID_Gen++),
//m_ChType(CH_TYPE_DTI),
m_InsertDB(0),
m_CallID(0),
m_RemoteRelease(0),
m_ConfCreator(false)
{
	SetUniqueID();
	Reset(false);	
}


KFPC_Channel::~KFPC_Channel(void)
{
}

unsigned int KFPC_Channel::Init(bool log)
{
	if(log)
	{
		INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u)",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
	}

	//下面主要针对会议
	if(m_ReleaseTime == 0)
	{
		m_ReleaseTime=time(NULL);
	}

	LogCDR();

	memset(&m_Device,0,sizeof(m_Device));
	//m_CmdID = 0;
	
	m_DstAppID = 0;
	SetStatus(KFPC_CH_Status_Idle);

	m_ConType = ConType_CH_NULL;
	//m_ActionType = KFPC_CHActionType_NULL;

	//m_SwitchChRes = NULL;		/**< 与之连接的资源 */

	//ClearCmdQueue();
	//m_IVRType = CH_IVRType_NULL;		/**< IVR资源类型 */
	//m_IVRChListCount = 0;		/**< IVR通道数 */
	
	//memset(m_IVRChList,0,sizeof(m_IVRChList));
	//memset(m_Cdt,0,sizeof(MS_CDT)*KFPC_MAX_CH_IVR_SIZE);		/**< 会议方 */

	//m_ConnectMode = SC_FULLDUP;
	//m_FaxIPMCh = NULL;
	//m_MSML_DeleteWhen = MSML_DelMode_NoMedia;

	
	//if(m_SignalType == KFPC_SignalType_SIP && (NULL != m_CallHandlerRes) )
	//{
	//	m_CallHandlerRes->RecoverResource();

		//unsigned int SIPID = m_CallHandlerRes->GetID();

		//if( SIPID%2 == 0)
		//{
		//	m_pNode->m_SipChMgr.RecoverCallOutSIPCh((KFPC_SipCh*)m_CallHandlerRes);
		//}	


		//if(m_IPMCh != NULL)
		//{
		//	//recover
		//	KFPC_EHNode* pEHNode = GetNode();
		//	pEHNode->m_VOIPMgr.RecoverIPMCh(m_IPMCh);
		//	SetXiopCh(NULL);
		//}
	//}

	//if(NULL != m_CallHandlerRes)
	//{
	//	m_CallHandlerRes->Init(log);
	//}


	//if(m_ChType == CH_TYPE_CONF)
	//{
	//	if(NULL != m_ConfRes )
	//	{
	//		m_ConfRes->Init(log);
	//	}	
	//}
	//else
	//{
	//	m_ConfRes = NULL;			/**< 相关的会议 */
	//}


	//这个放到最后方便log输出
	
	ClearCallID();
	m_RouterTimerID = 0;

	//memset(&m_RedirectingAttr,0,sizeof(m_RedirectingAttr));
	//memset(&m_CallerNumAttr,0,sizeof(m_CallerNumAttr));
	//m_CalledNOA = 0;
	//m_OrgCalledNOA = 0;
	//m_DiaFlag = 0;
	//m_FlowNum = 0;
	//m_AppSpecificData = 0;
	//m_RelMode = CHANNEL_RELMODE_PARK;
	m_Cause = 0;

	//if(m_ChType == CH_TYPE_CONF)
	//{
	//	m_CallFlag = CALL_FLAG_CONF;
	//}
	//else
	{
		m_CallFlag = CALL_FLAG_IN;
	}

	
	//m_MoreInfoTimeOutID = 0;

	//m_OverlapTimeOut = 0;
	//m_MaxCalledNumLength = 0;
	//m_MoreInfoBuf = "";
	//m_MoreInfo = "";
	//m_ReqMoreinfo = false;
	m_InitTime = 0;
	m_AnswerTime = 0;
	m_ConnectTime = 0;
	m_ReleaseTime = 0;

	//m_SAMEvtTimeOut = 0;
	m_RemoteRelease = false;
	m_SessionCallID = 0;
	//m_Ip = "";
	//m_ConfCreator = false;
	m_Cause = 0;
	//m_MonitorIVRCh = NULL;
	//m_PlayApiFlag = 0;
	return 0;
}

void KFPC_Channel::Reset(bool log )
{	
	if(log)
	{
		INFO_LOG(0,"ChID:%u",m_ID);
	}
	m_CmdIDQueue.clear(); 
	//m_CallHandlerRes = NULL;
	//m_SignalType = KFPC_SignalType_ClearChannel;

	memset(&m_Device,0,sizeof(m_Device));
	//memset(m_IVRChList,0,sizeof(m_IVRChList));
	//memset(&m_Cdt,0,sizeof(MS_CDT)*KFPC_MAX_CH_IVR_SIZE);		/**< 会议方 */

	m_CmdID = 0;
	ClearCallID();
	m_DstAppID = 0;
	m_ConType = ConType_CH_NULL;
	
	//m_SwitchChRes = NULL;		/**< 与之连接的资源 */

	//if(m_ChType != CH_TYPE_CONF)
	//{
	//	m_ConfRes = NULL;			/**< 相关的会议 */
	//}

	//m_IVRType = CH_IVRType_NULL;		/**< IVR资源类型 */
	//m_IVRChListCount = 0;		/**< IVR通道数 */

	//m_ActionType = KFPC_CHActionType_NULL;

	//m_ConnectMode = SC_FULLDUP;
	//m_FaxIPMCh = NULL;

	if(log)
	{
		SetStatus(KFPC_CH_Status_Unready);
	}
	else
	{
		m_Status = KFPC_CH_Status_Unready;
	}
	
	

	m_RouterTimerID = 0;

	//memset(&m_RedirectingAttr,0,sizeof(m_RedirectingAttr));
	//memset(&m_CallerNumAttr,0,sizeof(m_CallerNumAttr));
	//m_CalledNOA = 0;
	//m_OrgCalledNOA = 0;
	//m_DiaFlag = 0;
	//m_FlowNum = 0;
	//m_AppSpecificData = 0;
	m_Cause = 0;
	
	//if(m_ChType == CH_TYPE_CONF)
	//{
	//	m_CallFlag = CALL_FLAG_CONF;
	//}
	//else
	{
		m_CallFlag = CALL_FLAG_IN;
	}

	//m_MoreInfoTimeOutID = 0;

	//m_OverlapTimeOut = 0;
	//m_MaxCalledNumLength = 0;

	//m_MoreInfoBuf = "";
	//m_MoreInfo = "";
	//m_ReqMoreinfo = false;
	m_InitTime = 0;
	m_AnswerTime = 0;
	m_ConnectTime = 0;
	m_ReleaseTime = 0;
	//m_SAMEvtTimeOut = 0;
	//m_RelMode = CHANNEL_RELMODE_PARK;
	m_RemoteRelease = false;
	m_SessionCallID = 0;
	//m_Ip = "";
	//m_ConfCreator = false;
	m_Cause = 0;
	//m_MonitorIVRCh = NULL;
	//m_PlayApiFlag = 0;
	//m_MSML_DeleteWhen = MSML_DelMode_NoMedia;
	//Init(log);

}

void KFPC_Channel::SetStatus( KFPC_Ch_Status val )
{
	
	//if(m_SignalType == KFPC_SignalType_FXO ||
	//	m_SignalType == KFPC_SignalType_FXS)
	//{
	//	if(val == KFPC_CH_Status_Idle)
	//	{
	//		val = KFPC_CH_Status_OnHook;
	//	}
	//}

	if(m_ID != (unsigned short)-1)	/**< 避免构造输出 */
	{
		

		//提交数据库任务进行状态设置
		//KFPC_DBTaskImp* pDBTask = NULL;
		if(m_InsertDB == 0)
		{
			m_InsertDB = 1;

			unsigned int Span = ChannelToSpan(m_ID);
			KFPC_MonitorRefreshData_Instance->InserCh(m_UniqueID, 0, Span, ChannelToTimeSlot(m_ID), val, Span, CH_TYPE_SIP);

		}
		else
		{


		}

	}
	


	INFO_LOG(m_CallID,"UniqueID:%u,ChID:%u(Span:%u,Channel:%u),ChType:%s Status:%s-->Status:%s",
		m_UniqueID,m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),ChTypeToStr(CH_TYPE_SIP),ChStatusToStr(m_Status),ChStatusToStr(val));
	
	if(m_Status != val)
	{
		//KFPC_ChMgrInstance->ChStatusChange(m_Status,val, CH_TYPE_SIP);

		
		//KFPC_MonitorRefreshData_Instance->UpdateCh(m_UniqueID,val);

	}
	

	m_Status = val;

}

//void KFPC_Channel::BindCallHandlerRes( KFPC_CallHandler* val )
//{
//	m_CallHandlerRes = val;
//	m_CallHandlerRes->SetCh(this);
//}
//
//void KFPC_Channel::UnbindCallHandlerRes(KFPC_Channel* pCh)
//{
//	if(pCh != this)
//	{
//		ERROR_LOG(0,"pCh != this ChID:%u",m_ID);
//		return;
//	}
//
//	if(m_CallHandlerRes != NULL)
//	{
//		m_CallHandlerRes->SetCh(NULL);
//		m_CallHandlerRes = NULL;
//	}
//
//}
//
unsigned int KFPC_Channel::AcceptCall()
{
	//if(NULL == m_CallHandlerRes)
	//{
	//	WARNING_LOG(0,"ChID:%u ChRes is null.",m_ID);
	//	return KFPC_ERR_ChResIsNull;
	//}
	//else
	//{
	//	unsigned int DelayTime = (unsigned int)(time(NULL) - (GetCallID_TIME() + KFPC_START_TIME));

	//	if(DelayTime > 5)
	//	{
	//		WARNING_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),DelayTime:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),DelayTime);
	//	}
	//	else
	//	{
	//		INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),DelayTime:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),DelayTime);
	//	}
	//	

	//	KFPC_CallHandler* pCallHandler = 	(KFPC_CallHandler*)m_CallHandlerRes;
	//	return pCallHandler->AcceptCall();
	//}	

	return 0;
}
//
unsigned int KFPC_Channel::AnswerCall()
{
// 	if(NULL == m_CallHandlerRes)
// 	{
// 		WARNING_LOG(0,"ChID:%u ChRes is null.",m_ID);
// 		return KFPC_ERR_ChResIsNull;
// 	}
// 	else
// 	{
// 		unsigned int DelayTime = (unsigned int)(time(NULL) - (GetCallID_TIME() + KFPC_START_TIME));
// 
// 		if(DelayTime > 5 &&
// 			GetStatus() == KFPC_CH_Status_CallOffer)
// 		{
// 			WARNING_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),DelayTime:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),DelayTime);
// 		}
// 		else
// 		{
// 			INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),DelayTime:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),DelayTime);
// 		}
// 
// 		
// 		KFPC_CallHandler* pCallHandler = 	(KFPC_CallHandler*)m_CallHandlerRes;
// 		SetStatus(KFPC_CH_Status_Connect);
// 		return pCallHandler->AnswerCall();
// 		
// 	}	
	return 0;
}
//
unsigned int KFPC_Channel::ReleaseCall( int Cause )
{
// 	if(NULL == m_CallHandlerRes)
// 	{
// 		WARNING_LOG(0,"ChID:%u ChRes is null.",m_ID);
// 		return KFPC_ERR_ChResIsNull;
// 	}
// 	else
// 	{
// 		INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),Cause:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_Cause);
// 		SetCause(Cause);
// 		return m_CallHandlerRes->ReleaseCall(Cause);
// 		
// 	}	
	return 0;
}
//
//unsigned int KFPC_Channel::CallOut( KFPC_DEVICE& Device ,KFPC_TrunkGroup* pMyTrunkGroup,KFPC_SIP_Addr* pSipCallOutAddr,bool Overlap )
//{
//	unsigned int Ret = 0;
//	if(NULL == m_CallHandlerRes)
//	{
//		WARNING_LOG(0,"ChID:%u ChRes is null.",m_ID);
//		return KFPC_ERR_ChResIsNull;
//	}
//	else
//	{
//		
//		SetCallFlag(CALL_FLAG_OUT);
//
//		SetCallID();
//
//		INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u)",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
//
//		KFPC_OverlapCfg*	pOverlapCfg = KFPC_MoreInfCfg::GetInstance()->GetOverlapCfg(m_ID);
//
//		KFPC_DEVICE	NewDevice;
//
//		memcpy(&NewDevice,&Device,sizeof(Device));
//
//		unsigned int StripPrefixLen = strlen(pMyTrunkGroup->GetStripPrefix());
//
//		if( StripPrefixLen > 0 && 	StripPrefixLen < KFPC_MAX_NUMBER_SIZE)
//		{
//			char* p = strstr(NewDevice.CalledNO,pMyTrunkGroup->GetStripPrefix());
//
//			if(p == NewDevice.CalledNO)
//			{
//				strncpy(NewDevice.CalledNO,&Device.CalledNO[strlen(pMyTrunkGroup->GetStripPrefix())],KFPC_MAX_NUMBER_SIZE-1);
//				INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),New Called:%s",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),NewDevice.CalledNO);
//			}
//		}
//
//		if(strlen(pMyTrunkGroup->GetAddPrefix()) > 0)
//		{
//			snprintf(NewDevice.CalledNO,KFPC_MAX_NUMBER_SIZE,"%s%s",pMyTrunkGroup->GetAddPrefix(),Device.CalledNO);
//			INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),New Called:%s",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),NewDevice.CalledNO);
//		}
//
//
//
//
//		if(NULL != pOverlapCfg)
//		{
//			Ret = m_CallHandlerRes->CallOut(NewDevice , pMyTrunkGroup, pSipCallOutAddr,true);
//		}
//		else
//		{
//			Ret = m_CallHandlerRes->CallOut(NewDevice , pMyTrunkGroup, pSipCallOutAddr);
//		}
//		
//		/*
//		if(Ret != 0)
//		{
//			ClearCallID();
//		}
//		*/
//
//		if(pSipCallOutAddr != NULL)
//		{
//			SetIp(pSipCallOutAddr->GetIpv4Add());
//		}
//
//		return Ret;
//	}	
//}
//
unsigned int KFPC_Channel::AcceptCallAck( unsigned int Result )
{
// 	unsigned int CmdID = GetCmdID();
// 	if(0 == CmdID)
// 	{
// 		//WARNING_LOG(0,"ChID:%u CmdID is null.",m_ID);
// 		return KFPC_ERR_GetCmdIDFailed;
// 	}
// 
// 	KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(CmdID);
// 	if(NULL != pCmd)
// 	{
// 		pCmd->SetResult(Result);
// 		ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_AcceptCall);
// 	}
// 	else
// 	{
// 		SetCmdID(0,PREFIX_EXPRESSION_VALUE);
// 		WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,CmdID);
// 	}
	return 0;
}
//
unsigned int KFPC_Channel::AnswerCallAck( unsigned int Result )
{

// 	if(Result == 0)
// 	{
// 		m_AnswerTime = time(NULL);
// 	}
// 
// 	unsigned int CmdID = GetCmdID();
// 	if(0 == CmdID)
// 	{
// 		DEBUG_LOG(m_CallID,"ChID:%u CmdID is null.",m_ID);
// 		return KFPC_ERR_GetCmdIDFailed;
// 	}
// 	KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(CmdID);
// 	if(NULL != pCmd)
// 	{
// 		pCmd->SetResult(Result);
// 		ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_AnswerCall);
// 	}
// 	else
// 	{
// 		SetCmdID(0,PREFIX_EXPRESSION_VALUE);
// 		WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CallID);
// 	}
	return 0;
}
//
unsigned int KFPC_Channel::ReleaseCallAck( unsigned int Result )
{
// 	INFO_LOG(m_CallID,"Result:%u",Result);
// 	if(m_CmdID == 0)
// 	{
// 		WARNING_LOG(m_CallID,"ChID:%u not CmdID",m_ID);
// 
// 		Send_EVT_ReleasedCall(16);
// 
// 		Init();
// 	}
// 	else
// 	{
// 		KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
// 
// 		if(pCmd != NULL)
// 		{
// 			pCmd->SetResult(Result);
// 			ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_ReleaseCall);
// 		}
// 		else
// 		{
// 			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
// 			WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CallID);
// 		}
// 	}
	return 0;
}
//
unsigned int KFPC_Channel::CallOutAck( unsigned int Result,unsigned char Cause )
{
// 	if(m_CmdID == 0)
// 	{
// 		WARNING_LOG(m_CallID,"ChID:%u not CmdID",m_ID);
// 	}
// 	else
// 	{
// 		KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
// 
// 		if(pCmd != NULL)
// 		{
// 			
// 			pCmd->SetResult(Result);
// 			pCmd->SetCallOutCallID(m_CallID);
// 
// 			ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_CallOut);
// 		}
// 		else
// 		{
// 			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
// 			WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CallID);
// 		}
// 	}
	return 0;
}
//
unsigned int KFPC_Channel::EVT_IncomingCall( KFPC_DEVICE& Device )
{
	//SetCallID();
	//SetCallFlag(CALL_FLAG_IN);
	
	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) Caller:%s,Called:%s,OrgCalled:%s,RedDirNo:%s,TrunkGroup:%s.",
		m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),
		Device.CallerNO,
		Device.CalledNO,
		Device.OriginalCalled,
		Device.RedirectingNum,
		Device.TrunkGroup
		);

	//KFPC_OverlapCfg*	pOverlapCfg = KFPC_MoreInfCfg::GetInstance()->GetOverlapCfg(m_ID);


	//if(pOverlapCfg != NULL)
	//{
	//	if(pOverlapCfg->GetSAMEventTimeOut() > 0)
	//	{
	//		SetSAMEvtTimeOut(pOverlapCfg->GetSAMEventTimeOut());
	//	}
	//}

	//if(NULL != pOverlapCfg &&
	//	pOverlapCfg->GetTimeout() > 0 &&
	//	pOverlapCfg->GetCallednumlength() > 0)
	//{


	//	SetDevice(Device);

	//	KFPC_CalledPrefix*	pCalledPrefix = KFPC_MoreInfCfg::GetInstance()->GetCalledPrefix(Device.CalledNO);

	//	if(NULL != pCalledPrefix)
	//	{
	//		if(pCalledPrefix->GetCallednumlength() <= strlen(m_Device.CalledNO))
	//		{
	//			KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->Create_Cmd_EVT_IncomingCall(this,Device);

	//			if(m_CmdID == 0)
	//			{
	//				//静态执行CMD
	//				SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);
	//				ExecuteCmd(pCmd);
	//			}
	//			else
	//			{
	//				//放在队列
	//				PushCmdID(pCmd->GetID());
	//			}

	//			if(GetSAMEvtTimeOut() > 0)
	//			{
	//				SetSAMEvtTimer();
	//			}


	//			return 0;
	//		}
	//		else
	//		{
	//			SetOverlapTimeOut(pCalledPrefix->GetTimeout());
	//			SetMaxCalledNumLength(pCalledPrefix->GetCallednumlength());
	//		}

	//	}
	//	else
	//	{
	//		SetOverlapTimeOut(pOverlapCfg->GetTimeout());
	//		SetMaxCalledNumLength(pOverlapCfg->GetCallednumlength());
	//	}

	//	SetMoreInfoTimer();

	//	SetStatus(KFPC_CH_Status_WaitMoreInfo);

	//}
	//else
	//{
	//	KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->Create_Cmd_EVT_IncomingCall(this,Device);

	//	if(m_CmdID == 0)
	//	{
	//		//静态执行CMD
	//		//EH_Cmd_EVT_IncomingCall	Cmd_IncomingCall(m_CallID,m_DstAppID,0,0,Device);

	//		SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);

	//		//Cmd_IncomingCall.Execute2();
	//		//SetCmdID(0,PREFIX_EXPRESSION_VALUE);
	//	
	//		ExecuteCmd(pCmd);

	//	
	//	}
	//	else
	//	{
	//		//放在队列
	//	

	//		PushCmdID(pCmd->GetID());
	//	}
	//
	//	
	//}

	return 0;
}
//
unsigned int KFPC_Channel::EVT_AlertCall()
{
	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u)",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
	SetStatus(KFPC_CH_Status_Alerting);

	if(m_CmdID == 0)
	{

		Send_EVT_AlertCall();
	}
	else
	{
	
		CallOutAck(0,0);

	}


	//if(m_ConType == ConType_CH_CH)
	//{
	//	KFPC_Channel*	pCh = m_SwitchChRes->GetCh();

	//	if(pCh != NULL)
	//	{
	//		if(pCh->GetCallFlag() == CALL_FLAG_IN &&
	//			pCh->GetStatus() == KFPC_CH_Status_CallOffer)
	//		{
	//			pCh->AcceptCall();
	//		}
	//		
	//	}
	//	else
	//	{
	//		ERROR_LOG(m_CallID,"Con type CH_CH switch ch is NULL.");
	//	}
	//}

	return 0;	
}
//
unsigned int KFPC_Channel::EVT_AnsweredCall()
{
	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u)",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));

	m_AnswerTime = time(NULL);

	////放在队列
	//KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->Create_Cmd_EH_Evt_AnsweredCall(this);

	//if(m_CmdID == 0)
	//{
	//	SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);
	//	ExecuteCmd(pCmd);

	//}
	//else
	//{
	//	//此时,有可能是Callout后,没有收到Call Alerting 消息,所以需要check是否是callout 命令
	//	KFPC_BaseCommand*	pCurrentCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);

	//	if(pCurrentCmd != NULL)
	//	{
	//		pCurrentCmd->SetResult(0);
	//		pCurrentCmd->SetCallOutCallID(m_CallID);
	//		unsigned int nRet = pCurrentCmd->Execute(KFPC_MSG_ID_EH_CallOut, KFPC_MSG_TYPE_RESPONSE);

	//		if(KFPC_ERR_MsgIDNotMatch == nRet ||
	//			KFPC_ERR_CmdWaitAck == nRet)
	//		{
	//			PushCmdID(pCmd->GetID());
	//		}
	//		else
	//		{
	//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
	//			KFPC_CmdMgrInstance->FreeCmd(pCurrentCmd);

	//			ExecuteCmd(pCmd);
	//		}
	//	}
	//	else
	//	{
	//		ERROR_LOG(m_CallID,"m_CmdID is not exit.");
	//		SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);
	//		ExecuteCmd(pCmd);
	//	}
	//	
	//	
	//}
	
	//RelayAnswerCall();

	SetStatus(KFPC_CH_Status_Connect);

	return 0;	
}
//
unsigned int KFPC_Channel::EVT_ReleasedCall(unsigned int Cause)
{
	

	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u)Cause:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),Cause);
	//ClearMoreInfoTimer();

	m_ReleaseTime = time(NULL);
	m_RemoteRelease = true;
	SetCause(Cause);

	////判断当前是否是CallOut命令
	//if (m_CmdID != 0)
	//{
	//	KFPC_BaseCommand*	pCurrentCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
	//	if (pCurrentCmd != NULL)
	//	{
	//		pCurrentCmd->SetCause(Cause);
	//		pCurrentCmd->SetResult(KFPC_ERR_CallOutFailed);
	//		pCurrentCmd->SetCallOutCallID(m_CallID);

	//		if (ExecuteRspCmd(pCurrentCmd,KFPC_MSG_ID_EH_CallOut) != KFPC_ERR_MsgIDNotMatch)
	//		{
	//			return 0;
	//		}
	//	} 
	//	else
	//	{
	//		SetCmdID(0,PREFIX_EXPRESSION_VALUE);
	//	}
	//}
	//
	//if(m_CallID != 0)
	//{

	//	//放在队列
	//	KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->Create_CmdSet_EVT_ReleasedCall(this,m_DstAppID,0,0,Cause);

	//	if(0 != m_CmdID )
	//	{
	//		KFPC_BaseCommand*	pCurrentCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
	//		unsigned int MsgID;
	//		if(pCurrentCmd->GetCmdTypeIsCmdSet())
	//		{
	//			KFPC_BaseCommand* pExeCmdInSet = KFPC_CmdMgrInstance->GetCmd(pCurrentCmd->GetExeCmdID());
	//			MsgID = pExeCmdInSet->GetMsgID();

	//			if( KFPC_MSG_ID_EH_Connect == MsgID || 
	//				KFPC_MSG_ID_EH_Disconnect == MsgID 
	//				)
	//			{
	//				if(KFPC_MSG_ID_EH_Connect == MsgID )
	//				{
	//					pCurrentCmd->SetStopFlag(true,KFPC_ERR_ChannelReleased);
	//				}
	//				
	//				PushCmdID(pCmd->GetID());
	//				return 0;

	//			}
	//		}

	//		CancelCmdQueue();
	//		pCurrentCmd->Cancel();		
	//		KFPC_CmdMgrInstance->FreeCmd(pCurrentCmd);

	//		SetCmdID(0,PREFIX_EXPRESSION_VALUE);
	//	}
	//
	//	SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);
	//	ExecuteCmd(pCmd);
	//	
	//}
	//else
	//{
	//	Init();
	//}
	
	return 0;
}

unsigned int KFPC_Channel::PushCmdID( unsigned int CmdID )
{
	m_CmdIDQueue.push_back(CmdID);
	INFO_LOG(m_CallID,"ChID:%u,CmdID:%u,existed CmdID:%u,Cmd list size:%d",m_ID,CmdID,m_CmdID,m_CmdIDQueue.size());
	return m_CmdIDQueue.size();
}

unsigned int KFPC_Channel::PopCmdID()
{
	unsigned int CmdID = m_CmdIDQueue.front();
	m_CmdIDQueue.pop_front();
	INFO_LOG(m_CallID,"ChID:%u,CmdID:%u Cmd list size:%d",m_CallID,CmdID,m_CmdIDQueue.size());
	return CmdID;
}
//
//void KFPC_Channel::SetCallID()
//{
//	if(m_CallID != 0)
//	{
//		ERROR_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) CallID is not 0",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
//		
//	}
//	m_InitTime = time(NULL);
//
//	KFPC_CallID	CallID;
//	CallID.CallIDInfo.ChID = m_ID;
//	CallID.CallIDInfo.AppID = KFPC_GetLibParam()->AppInfo.AppID;
//	unsigned long long T = (m_InitTime - KFPC_START_TIME);
//	CallID.CallIDInfo.Time = (unsigned int)T;
//
//	m_CallID = CallID.CallID;
//	g_CallCount++;
//	
//	char TimeStr[128];
//	TimeToStr(TimeStr,GetCallID_TIME()+KFPC_START_TIME);
//	
//
//	DEBUG_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) CallCount:%u,ChannelType:%s,CallIDTime:%s",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),g_CallCount,ChTypeToStr(m_ChType),TimeStr);
//}
//
int KFPC_Channel::GetHandle()
{
	//if(m_CallHandlerRes != NULL)
	//{
	//	return m_CallHandlerRes->GetHandle();
	//}
	//else
	//{
		return 0;
	//}hulg
}
//
void KFPC_Channel::SetCmdID( unsigned int val,unsigned int DebugStrLen,const char* DebugStr )
{
// 	if(m_CmdID == 0 && val == 0)
// 	{
// 		DEBUG_LOG(m_CallID,"CmdID and val both are 0,Call by function %.*s",DebugStrLen,DebugStr);
// 		return;
// 	}
// 
// 	if(m_CmdID == val)
// 	{
// 		DEBUG_LOG(m_CallID,"CmdID:%u is same Call by function %.*s",val,DebugStrLen,DebugStr);
// 		return;
// 	}
// 
// 	if(val == 0 && !m_CmdIDQueue.empty())
// 	{
// 		INFO_LOG(GetCallID(),"Throw ThreadTask to handle CmdIDQueue Call by function %.*s",DebugStrLen,DebugStr);
// 		KFPC_ThreadTask* pThreadTask = new KFPC_CmdThreadTask(this);
// 		if(NULL != pThreadTask)	
// 		{
// 			KFPC_AppMainThreadInstance->PutTask(pThreadTask);
// 			//KFPC_EHSwitchInstance->WakeUp();
// 		}
// 	}
// 
// 	
// 	INFO_LOG(m_CallID,"ChID:%u,CmdID:%u-->CmdID:%u Call by function %.*s",m_ID,m_CmdID,val,DebugStrLen,DebugStr);
// 	m_CmdID = val;

	//if(0 == m_CmdID)
	//{
	//	ExeCmdQueue();
	//}
}
//
void KFPC_Channel::ExeCmdQueue()
{

	//while(!m_CmdIDQueue.empty())
	//{
	//	unsigned int CmdID = m_CmdIDQueue.front();
	//	m_CmdIDQueue.pop_front();

	//	KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(CmdID);

	//	if(NULL != pCmd)
	//	{
	//		INFO_LOG(m_CallID,"ChID:%u,CmdID:%u-->CmdID:%u",m_ID,m_CmdID,pCmd->GetID());

	//		if(m_CmdID != 0)
	//		{
	//			WARNING_LOG(m_CallID,"CmdID:%u will be freed before ExeCmdQueue()",m_CmdID);
	//			KFPC_BaseCommand* pCommand = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
	//			if(NULL != pCommand)
	//			{
	//				KFPC_CmdMgrInstance->FreeCmd(pCommand);
	//			}
	//		}
	//		m_CmdID = pCmd->GetID();

	//		unsigned int Ret = pCmd->Execute2();

	//		if(KFPC_ERR_CmdWaitAck == Ret)
	//		{
	//			return ;
	//		}
	//		else
	//		{
	//			KFPC_CmdMgrInstance->FreeCmd(pCmd);				
	//			m_CmdID = 0;
	//			INFO_LOG(m_CallID,"ChID:%u,CmdID:%u",m_ID,0);
	//		}
	//	}
	//}
}
//
//
//void KFPC_Channel::PlayVoiceBegin()
//{
//	if(m_CmdID != 0)
//	{
//		KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//		if(pCmd != NULL)
//		{
//			ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_PlayVoice);
//		}
//		else
//		{
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CmdID);
//		}
//		
//	}
//	else
//	{
//		WARNING_LOG(m_CallID,"ChID:%u has no CmdID",m_ID);
//	}
//}
//
//void KFPC_Channel::ExecuteCmd( KFPC_BaseCommand* pCmd )
//{
//	
//	unsigned int Ret = pCmd->Execute2();
//	
//	if(KFPC_ERR_CmdWaitAck != Ret)
//	{		
//		KFPC_CmdMgrInstance->FreeCmd(pCmd);
//		SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//	}
//}
//
//void KFPC_Channel::CancelCmd()
//{
//	KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//	if(NULL != pCmd)
//	{
//		unsigned int Ret = pCmd->Cancel();
//
//		if(KFPC_ERR_CmdWaitAck != Ret)
//		{
//
//			KFPC_CmdMgrInstance->FreeCmd(pCmd);
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//		}
//	}
//
//}
//
//void KFPC_Channel::CancelCmdQueue()
//{
//	while(!m_CmdIDQueue.empty())
//	{
//		unsigned int CmdID = m_CmdIDQueue.front();
//		KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(CmdID);
//
//		if(NULL != pCmd)
//		{
//			unsigned int Ret = pCmd->Cancel();
//			INFO_LOG(m_CallID,"CmdID:%u Canceled",CmdID);
//			KFPC_CmdMgrInstance->FreeCmd(pCmd);	
//		}
//
//		m_CmdIDQueue.pop_front();
//	}
//}

unsigned int KFPC_Channel::ExecuteRspCmd( KFPC_BaseCommand* pCmd,unsigned int MsgID )
{
	if(pCmd == NULL)
	{
		ERROR_LOG(m_CallID,"Cmd is NULL"); 
		return KFPC_ERR_GetCmdIDFailed;
	}

	unsigned int Ret = pCmd->Execute(MsgID,KFPC_MSG_TYPE_RESPONSE);

	if(KFPC_ERR_CmdWaitAck == Ret)
	{

	}
	else if(KFPC_ERR_MsgIDNotMatch == Ret)
	{
		DEBUG_LOG(m_CallID,"ChID:%u msg id doest not match.",m_ID);
	}
	else 
	{
		KFPC_CmdMgrInstance->FreeCmd(pCmd);
		SetCmdID(0,PREFIX_EXPRESSION_VALUE);		
	}

	return Ret;
}


//void KFPC_Channel::PlayVoiceCompleted(unsigned int Reason)
//{
//	INFO_LOG(m_CallID,
//		"ChID:%u,Term reason:%s",m_ID,TermToStr(Reason));
//
//	unsigned int DstAppID = GetDstAppID();
//
//	if(m_CmdID == 0 )
//	{
//		if(	TM_MAXTIME == Reason || TM_EOD == Reason)
//		{
//			//静态执行CMD
//
//			//KFPC_Cmd_EVT_PlayVoiceCompleted Cmd_PlayVoiceCompleted(m_CallID,DstAppID,0,0);
//			KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->Create_Cmd_EVT_PlayVoiceCompleted(this,DstAppID,0,0);
//
//			SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);
//
//			pCmd->Execute2();
//
//			KFPC_CmdMgrInstance->FreeCmd(pCmd);
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//
//			//Cmd_PlayVoiceCompleted.Execute2();
//			//SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			
//		}
//
//	}
//	else
//	{
//
//		//check if the command is what we need
//		KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//		if(NULL == pCmd)
//		{
//			WARNING_LOG(m_CallID,"ChID:%u,CmdID:%u",m_ID,m_CmdID);
//			return;
//		}
//
//		pCmd->SetResult(0);
//
//		
//
//		unsigned int nRet = 0;
//			
//		if(TM_USRSTOP == Reason)
//		{
//			nRet = pCmd->Execute(KFPC_MSG_ID_EH_StopPlayVoice, KFPC_MSG_TYPE_RESPONSE);
//		}
//		else
//		{
//			nRet = pCmd->Execute(KFPC_MSG_ID_EH_EVT_PlayVoiceCompleted, KFPC_MSG_TYPE_RESPONSE);
//		}
//
//			
//		if(KFPC_ERR_MsgIDNotMatch == nRet)
//		{
//			if(TM_MAXTIME == Reason)
//			{
//				//放在队列
//				KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->Create_Cmd_EVT_PlayVoiceCompleted(this,DstAppID,0,0);
//				PushCmdID(pCmd->GetID());
//			}
//
//		}
//		else if(KFPC_ERR_CmdWaitAck != nRet)
//		{
//			KFPC_CmdMgrInstance->FreeCmd(pCmd);
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//		}
//
//	}
//
//	return ;
//}
//
//void KFPC_Channel::CollectDigitCompleted(char* pDigits)
//{
//	//unsigned int DesAppID = GetDstAppID();
//	//if(m_CmdID == 0)
//	//{
//	//	//静态执行CMD
//
//	//	KFPC_Cmd_EVT_DigitCollected* pCmd_DigitCollected = KFPC_CmdMgrInstance->Create_Cmd_EH_Evt_DigitCollected(this,DesAppID,0,0,strlen(pDigits),pDigits);
//
//	//	//SetCmdID(pCmd_DigitCollected->GetID(),PREFIX_EXPRESSION_VALUE);
//
//	//	pCmd_DigitCollected->Execute2();	
//	//	KFPC_CmdMgrInstance->FreeCmd(pCmd_DigitCollected->GetID());
//
//	//	//SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//	//	
//	//}
//	//else
//	//{
//	//	//check if the command is what we need
//	//	KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//	//	unsigned int nRet = pCmd->Execute(KFPC_MSG_ID_EH_CollectDTMF, KFPC_MSG_TYPE_RESPONSE);
//	//	if(KFPC_ERR_MsgIDNotMatch == nRet)
//	//	{
//	//		//放在队列
//	//		KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->Create_Cmd_EH_Evt_DigitCollected(this,DesAppID,0,0,strlen(pDigits),pDigits);
//	//		PushCmdID(pCmd->GetID());
//	//	}
//	//	else if(KFPC_ERR_CmdWaitAck != nRet)
//	//	{
//	//		KFPC_CmdMgrInstance->FreeCmd(pCmd);
//	//		SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//	//	}
//
//	//}
//
//	return ;
//}

void KFPC_Channel::SetCh( KFPC_Channel* pch )
{
	ERROR_LOG(m_CallID,"ChID:%u unsupport this opreation",m_ID);
}


//
//void KFPC_Channel::SetSwitchChRes( KFPC_ChRes* val )
//{
//	m_SwitchChRes = val;	
//}
//
//void KFPC_Channel::ClearSwitchChRes()
//{
//	m_ConType = ConType_CH_NULL;
//	m_SwitchChRes = NULL;
//	INFO_LOG(m_CallID,"ChID:%u ",m_ID);
//}
//
//void KFPC_Channel::SetConfRes( KFPC_ConfRes* val )
//{
//	m_ConfRes = val;
//	if(val != NULL)
//	{
//		INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),ConfResID:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),val->GetID());
//	}
//	else
//	{
//		INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) val is null.",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
//	}
//	
//
//}
//
//void KFPC_Channel::SetConfSwitch( KFPC_VoiceCh* pVoiceCh, KFPC_ConfRes* pConfResCh,KFPC_Channel*pConfCh)
//{
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),ConfID:0x%u,VoiceID:%u,",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),pConfResCh->GetID(),pVoiceCh->GetID());
//
//	SetSessionCallID(pConfCh->GetCallID());
//
//	SetConType(ConType_CH_CONF);		
//	pVoiceCh->SetSwitchCh(this);
//	SetConfRes(pConfResCh);
//	SetSwitchChRes(pVoiceCh);
//	
//}
//
//unsigned int KFPC_Channel::CreateConf( unsigned int Size ,bool PlayRecord)
//{
//	if(NULL != m_ConfRes)
//	{
//
//		
//		unsigned int Ret =  m_ConfRes->CreateConf(m_ID,Size,PlayRecord);
//
//		if(Ret == 0)
//		{
//			SetCallID();
//		}
//		
//		INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) Size:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),Size);
//
//		return Ret;
//	}
//	else
//	{
//		WARNING_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) no conf res",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
//		return KFPC_ERR_NoConfResBind;
//	}
//}
//
//unsigned int KFPC_Channel::CreateConfAck( int Result,int ConfID  )
//{
//	/*if( CH_TYPE_CONF == m_ChType)
//	{
//		m_ConfRes->CreateConfAck(Result,ConfID);
//		SetCreateConfTimer(Result);
//	}
//
//	if(m_CmdID == 0)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u not CmdID",m_ID);
//	}
//	else
//	{
//		INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) EH ConfID:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),ConfID);
//
//		if( CH_IVRType_MIX == GetIVRType() && (Result == 0))
//		{
//			m_EH3ConfID = ConfID;
//		}
//		KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//		if(pCmd != NULL)
//		{
//
//			pCmd->SetResult(Result);
//
//			ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_CreateConference);
//		}
//		else
//		{
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CallID);
//		}
//	}*/
//	return 0;
//}
//
unsigned int KFPC_Channel::FreeConf()
{
//	if(NULL != m_ConfRes)
//	{
//#ifdef MSML
//		char ConfName[CONF_NAME] = "";
//
//		snprintf(ConfName,CONF_NAME,"conf:%llx",m_CallID);
//
//		KFPC_MsmlChMgr_INSTANCE->DelCallName_ID(ConfName);
//#endif // MSML
//
//		INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),ConfID:%u,EH ConfID:%u",
//			m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_ConfRes->GetID(),m_ConfRes->GetEHConfID());
//
//		return m_ConfRes->FreeConf();
//	}
//	else
//	{
//		WARNING_LOG(m_CallID,"ChID:%u no conf res");
//		return KFPC_ERR_NoConfResBind;
//	}

	return 0;
}
//
//unsigned int KFPC_Channel::FreeConfAck( int Result )
//{
//
//
//	//
//	//if( CH_TYPE_CONF == m_ChType)
//	//{
//	//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),EH ConfID:%u,Result:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_ConfRes->GetEHConfID(),Result);
//	//	m_ConfRes->FreeConfAck(Result);
//	//}
//	//else
//	//{
//	//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),3party EH ConfID:%u,Result:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_EH3ConfID,Result);
//	//}
//
//	//if(m_CmdID == 0)
//	//{
//	//	WARNING_LOG(m_CallID,"ChID:%u not CmdID",m_ID);
//	//	Init(true);
//	//}
//	//else
//	//{
//	//	KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//	//	if(pCmd != NULL)
//	//	{
//
//	//		pCmd->SetResult(Result);
//
//	//		ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_FreeConference);
//	//	}
//	//	else
//	//	{
//	//		SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//	//		WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CmdID);
//	//	}
//	//}
//	return 0;
//}
//
//void KFPC_Channel::SetIVRChList( KFPC_VoiceCh** val,unsigned char IvrChCount )
//{
//	for(unsigned int i=0;i<KFPC_MAX_CH_IVR_SIZE && i < IvrChCount;i++)
//	{
//		m_IVRChList[i] = val[i];
//	}
//	
//}

//
//unsigned int KFPC_Channel::JoinConf(KFPC_Channel*pConfCh, KFPC_VoiceCh* pVoiceCh,unsigned char Mode,int	DTMFSilence)
//{
//	if((m_Status & KFPC_CALL_LIVE) == 0)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) status:%s err",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),ChStatusToStr(m_Status));
//		return KFPC_ERR_ChStatusErr;
//	}
//
//	if(m_ConType != ConType_CH_NULL)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),ConType:%s,switchres ID:%u.",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),ConTypeToStr(m_ConType),m_SwitchChRes->GetID());
//		return KFPC_ERR_ChannelResBusy;
//	}
//	
//	pVoiceCh->SetConnectMode((Mode == 0)? SC_FULLDUP:SC_HALFDUP);
//
//	if ((ISX_nr_scroute(
//		pVoiceCh->GetConnectHandle(),
//		pVoiceCh->GetConnectDevType(),
//
//		GetConnectHandle(),
//		GetConnectDevType(),
//
//		pVoiceCh->GetConnectMode(),
//		EV_ASYNC)) == -1)
//	{
//
//		ERROR_LOG(m_CallID,"VoiceID:%u,ChID:%u ISX_nr_scroute Failed:%s", 			
//			((KFPC_VoiceCh*)pVoiceCh)->GetID(),
//			m_ID,
//			ISX_ATDV_ERRMSGP(pVoiceCh->GetHandle()));
//		return KFPC_ERR_ScrouteFailed;
//	}
//	else
//	{
//
//		
//		SetConfSwitch(pVoiceCh, pConfCh->GetConfRes(),pConfCh);
//
//		INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),ConfCallID:0x%llx,ConfID:%u,VoiceID:%u,IdleConfRes:%u",
//			m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),
//			pConfCh->GetCallID(),
//			pConfCh->GetConfRes()->GetID(),
//			pVoiceCh->GetID(),
//			pConfCh->GetConfRes()->GetIdleConfRes());
//
//		if(DTMFSilence)
//		{
//			pVoiceCh->SetDTMFSilence(true);
//		}
//		else
//		{
//			pVoiceCh->SetDTMFSilence(false);
//		}
//
//		SetActionType(KFPC_CHActionType_CH_CONF);
//
//		return 0;
//	}
//}

//
//unsigned int KFPC_Channel::LeaveConf()
//{
//	if(m_ConType != ConType_CH_CONF)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,ConType:%s.",m_ID,ConTypeToStr(m_ConType));
//		return KFPC_ERR_ChannelConfResErr;
//	}
//
//	KFPC_ChRes*	pChRes = GetSwitchChRes();
//
//
//	if ((ISX_nr_scunroute(
//		GetConnectHandle(),
//		GetConnectDevType(),
//		pChRes->GetConnectHandle(),
//		pChRes->GetConnectDevType(),
//		SC_FULLDUP,
//		EV_ASYNC)) == -1)
//	{
//		ERROR_LOG(m_CallID,"VoiceID:%u,ChID:%u ISX_nr_scroute Failed:%s", 			
//			pChRes->GetID(),
//			m_ID,
//			ISX_ATDV_ERRMSGP(pChRes->GetConnectHandle()));
//		return KFPC_ERR_ScrouteFailed;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//unsigned int KFPC_Channel::JoinConfAck( int Result )
//{
//	if(m_CmdID == 0)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u not CmdID",m_ID);
//	}
//	else
//	{
//		KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//		if(pCmd != NULL)
//		{
//
//			pCmd->SetResult(Result);
//
//			ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_JoinConference);
//		}
//		else
//		{
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CallID);
//		}
//	}
//	return 0;
//}

//unsigned int KFPC_Channel::LeaveConfAck( int Result )
//{
//	if(m_CmdID == 0)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u not CmdID",m_ID);
//	}
//	else
//	{
//		KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//		if(pCmd != NULL)
//		{
//
//			pCmd->SetResult(Result);
//
//			ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_LeaveConference);
//		}
//		else
//		{
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CallID);
//		}
//	}
//	return 0;
//}

int KFPC_Channel::GetConnectHandle()
{
// 	if(m_IVRType == CH_IVRType_MIX)
// 	{
// 		return m_IVRChList[2]->GetHandle();
// 	}
// 	else
// 	{
// 		return GetHandle();
// 	}
	return 0;
}
//
//unsigned int KFPC_Channel::ConnectToIVR(bool MonitorIVR)
//{
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),MonitorIVR:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),MonitorIVR);
//
//	if((m_Status & KFPC_CALL_LIVE) == 0)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u status:%s err",m_ID,ChStatusToStr(m_Status));
//		return KFPC_ERR_ChStatusErr;
//	}
//
//	KFPC_EHNode* pEHNode= NULL;
//
//	if(m_ChType == CH_TYPE_SIP)
//	{
//		pEHNode = m_CallHandlerRes->GetVOIPResNode();
//	}
//	else
//	{
//		pEHNode= GetNode();
//
//	}
//
//	if(NULL == pEHNode)
//	{
//		ERROR_LOG(m_CallID,"pEHNode is Null.");
//		return KFPC_ERR_FailedToGetNode;
//	}
//
//	KFPC_VoiceCh* pVoiceCh = NULL;
//
//	if(MonitorIVR )
//	{
//		if(GetMonitorIVRCh() != NULL)
//		{
//			return KFPC_ERR_IVRAlreadyConnected; 
//		}
//		else
//		{
//			if(!pEHNode->m_VoiceMgr.AssignIVRCh(m_ID,&pVoiceCh))
//			{
//				ERROR_LOG(m_CallID,"Failed to assign IVR ch.");
//				return KFPC_ERR_IVRChAssignFailed;
//			}
//			else
//			{
//				SetMonitorIVRCh(pVoiceCh);
//			}
//
//		}
//	}
//	else
//	{
//
//		if(CH_IVRType_MIX != GetIVRType())
//		{
//			if(ConType_CH_IVR == m_ConType)
//			{
//				return KFPC_ERR_IVRAlreadyConnected;
//			}
//			else if(ConType_CH_NULL == m_ConType)
//			{
//				//this IVR channel type must be a CH_IVRType_ONE 
//				//For CH_IVRType_MIX type, IVRs were assigned in Create3PartyConf()
//				if(!pEHNode->m_VoiceMgr.AssignIVRCh(m_ID,&pVoiceCh))
//				{
//					ERROR_LOG(m_CallID,"Failed to assign IVR ch.");
//					return KFPC_ERR_IVRChAssignFailed;
//				}
//				else
//				{
//					SetIVRType(CH_IVRType_ONE);	
//				}
//
//			}
//			else
//			{
//				WARNING_LOG(m_CallID,"ChID:%u,ConType:%s.",m_ID,ConTypeToStr(m_ConType));
//				return KFPC_ERR_ChConTypeErr;
//			}
//		}
//		else if(CH_IVRType_MIX == GetIVRType())
//		{
//			if(NULL != m_IVRChList[1])
//			{
//				pVoiceCh = m_IVRChList[1];
//
//				if(pVoiceCh->GetSwitchCh() == this)
//				{
//					return KFPC_ERR_IVRAlreadyConnected;
//				}
//				else
//				{
//					//exe connect
//				}
//			}
//			else
//			{
//				ERROR_LOG(m_CallID,"Failed to assign IVR[1] in CH_IVRType_MIX type .");
//				return KFPC_ERR_IVRChAssignFailed;
//			}
//		}
//
//	}
//		
//	int VoiceHandle = pVoiceCh->GetHandle();
//
//	KFPC_CallHandler* pChRes = GetCallHandlerResRes();
//	if(NULL == pChRes)
//	{
//		ERROR_LOG(m_CallID,"ChRes:%u is Null.",GetID());
//		return KFPC_ERR_ChResIsNull;
//	}
//
//	int DevHandle = pChRes->GetConnectHandle();
//	if(-1 == DevHandle)
//	{
//		ERROR_LOG(m_CallID,"Failed to get dev handle");
//		return KFPC_ERR_DevHandleInvalid;
//	}
//
//	int DevType = pChRes->GetConnectDevType();
//
//	if(MonitorIVR)
//	{
//		pVoiceCh->SetConnectMode(SC_HALFDUP);
//		if(DevType == SC_XOIP)
//		{
//			DevType = SC_XOIP_MIX;
//		}
//		else if(DevType == SC_DTI)
//		{
//			DevType = SC_DTI_MIX;
//		}
//		else if(DevType == SC_M3G)
//		{
//			DevType = SC_M3G_MIX;
//		}
//	}
//	else
//	{
//		pVoiceCh->SetConnectMode(SC_FULLDUP);
//	}
//	
//
//	if ((ISX_nr_scroute(DevHandle,DevType,  VoiceHandle, SC_VOX,
//		pVoiceCh->GetConnectMode(), EV_ASYNC)) == -1)
//	{
//		ERROR_LOG(m_CallID,"VoiceID:%u ChID:%u ISX_nr_scroute Failed:%s", 
//			pVoiceCh->GetID(), GetID(),
//			ISX_ATDV_ERRMSGP(VoiceHandle));
// 
//
//		if(CH_IVRType_ONE == GetIVRType())
//		{
//			pVoiceCh->ClearSwitchChRes();
//			ClearSwitchChRes();
//			SetIVRType(CH_IVRType_NULL);
//
//			pVoiceCh->GetNode()->m_VoiceMgr.RecoverIVRCh(pVoiceCh->GetID());			
//		}
//		else
//		{
//			pVoiceCh->ClearSwitchChRes();
//			SetMonitorIVRCh(NULL);
//			pVoiceCh->GetNode()->m_VoiceMgr.RecoverIVRCh(pVoiceCh->GetID());	
//		}
//
//		return KFPC_ERR_ScrouteFailed;
//	}
//	else
//	{
//		if(MonitorIVR)
//		{
//			DEBUG_LOG(m_CallID,"VoiceID:%u<-->ChID:%u monitor ivr", pVoiceCh->GetID(), m_ID);
//
//			pVoiceCh->SetSwitchCh(this);
//			SetMonitorIVRCh(pVoiceCh);
//			SetActionType(KFPC_CHActionType_CH_MONITOR_IVR);
//			return 0;
//		}
//		else
//		{
//			DEBUG_LOG(m_CallID,"VoiceID:%u<-->ChID:%u", pVoiceCh->GetID(), m_ID);
//
//			SetIVRSwitch(pVoiceCh);
//			SetActionType(KFPC_CHActionType_CH_IVR);
//			return 0;
//		}
//
//	}
//
//}
//
//
//void KFPC_Channel::ConnectedAck( int result )
//{
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),Result:%d,err:%s",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),result,ISX_ATDV_ERRMSGP(GetHandle()));
//
//	KFPC_ChannelActionType	CAT = m_ActionType;
//	SetActionType(KFPC_CHActionType_NULL);
//
//	switch(CAT)
//	{
//	case KFPC_CHActionType_CH_MONITOR_IVR:
//		{
//			if(0 != result )
//			{
//				ClearMonitorIVR();
//
//			}
//		}
//		break;
//	case KFPC_CHActionType_CH_IVR:
//		{
//			//ConnectToIVRAck(result);
//			if(0 != result )
//			{
//				if(CH_IVRType_ONE == GetIVRType())
//				{	
//					ClearIVRSwitch();
//				}
//			}
//
//		}
//		break;
//	case KFPC_CHActionType_CH_CH:
//		{
//			
//			if( CH_TYPE_AG == m_ChType )
//			{
//				if(NULL != m_CallHandlerRes)
//				{
//					INFO_LOG(m_CallID, "AG channel,AGID:%u, CHID:%u, OneWayRecoverIVR",((KFPC_AGCh*)m_CallHandlerRes)->GetID(),GetID() );
//					((KFPC_AGCh*)m_CallHandlerRes)->OneWayRecoverIVR();
//				}
//			}
//			////对端是AG通道，要将它自己的IVR资源单向重新连起来，以便检测忙音
//			if(NULL != m_SwitchChRes)
//			{
//				if(((KFPC_Channel*)m_SwitchChRes)->GetChType() == CH_TYPE_AG)
//				{
//					if(NULL != ((KFPC_Channel*)m_SwitchChRes)->GetCallHandlerResRes())
//					{
//						KFPC_AGCh* pAGCh = (KFPC_AGCh*)((KFPC_Channel*)m_SwitchChRes)->GetCallHandlerResRes();
//
//						INFO_LOG(m_CallID, "Peer is AG,AGID:%u, CHID:%u, OneWayRecoverIVR",pAGCh->GetID(),((KFPC_Channel*)m_SwitchChRes)->GetID() );
//						pAGCh->OneWayRecoverIVR();
//					}
//				}
//			}
//
//
//			if(0 != result)
//			{
//				ClearChSwitch();
//			}
//			else
//			{
//				KFPC_Channel*	pSwitchChannel = m_SwitchChRes->GetCh();
//
//				m_ConnectTime = time(NULL);
//				pSwitchChannel->SetConnectTime(m_ConnectTime);
//
//				//if(	m_CallFlag == CALL_FLAG_IN &&
//				//	m_Status == KFPC_CH_Status_Accept &&
//				//	pSwitchChannel->GetStatus() == KFPC_CH_Status_Connect)
//				//{
//				//	//对端已经摘机
//				//	AnswerCall();
//				//	
//				//	if(KFPC_CheckAppID(m_DstAppID) == 0)
//				//	{
//				//		KFCPTServerAPIHandlerImpInstance->SendTS_EVT_PassAnswerCall(m_DstAppID,
//				//			0,
//				//			0,
//				//			m_CallID);
//				//	
//				//	}
//				//}
//
//				if(pSwitchChannel->GetCallFlag() == CALL_FLAG_OUT)
//				{
//					pSwitchChannel->RelayAnswerCall();
//				}
//
//				if(GetCallFlag() == CALL_FLAG_OUT)
//				{
//					RelayAnswerCall();
//				}
//				
//
//				//if(	pSwitchChannel->GetCallFlag() == CALL_FLAG_IN &&
//				//	pSwitchChannel->GetStatus() == KFPC_CH_Status_Accept &&
//				//	m_Status == KFPC_CH_Status_Connect )
//				//{
//				//	pSwitchChannel->AnswerCall();
//
//				//	if(KFPC_CheckAppID(m_DstAppID) == 0)
//				//	{
//				//		KFCPTServerAPIHandlerImpInstance->SendTS_EVT_PassAnswerCall(m_DstAppID,
//				//			0,
//				//			0,
//				//			pSwitchChannel->GetCallID());
//				//		
//				//	}
//				//}
//			}
//			//ConnectToChAck(result);
//		}
//		break;
//	case KFPC_CHActionType_CH_CONF:
//		{
//			if(0 != result)
//			{
//				ClearConfSwitch();
//			}
//
//			m_ConnectTime = time(NULL);
//
//			//JoinConfAck(result);
//		}
//		break;
//	case KFPC_CHActionType_CH_CHANGE_CONNECT_MODE:
//		{
//
//		}
//		break;
//	case KFPC_CHActionType_CH_FAX:
//		{
//			if(0 != result)
//			{
//				ClearFaxSwitch();
//			}
//			
//		}
//		break;
//	default:
//		WARNING_LOG(m_CallID,"ChID:%u ConType:%s,ActionType:%s",m_ID,ConTypeToStr(m_ConType),ActionTypeToStr(m_ActionType));
//	
//	}
//
//	//报告连接结果
//	if(m_CmdID != 0)
//	{
//		KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);	
//		if(pCmd != NULL)
//		{
//			pCmd->SetResult(result);
//			ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_Connect);
//		}
//		else
//		{
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CmdID);
//		}
//
//	}
//	else
//	{
//		SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//		WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CmdID);
//	}
//
//}
//
//void KFPC_Channel::DisconnectedAck( int result )
//{
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),Result:%d,err:%s,ConType:%s",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),result,ISX_ATDV_ERRMSGP(GetHandle()),ConTypeToStr(m_ConType));
//
//	if(KFPC_CHActionType_CH_CHANGE_CONNECT_MODE == m_ActionType)
//	{
//		ChangeConnectMode(m_ConnectMode);
//	}
//	else
//	{
//		KFPC_ChannelActionType	CAT = m_ActionType;
//		SetActionType(KFPC_CHActionType_NULL);	
//		
//		if(CAT == KFPC_CHActionType_CH_MONITOR_IVR)
//		{
//			ClearMonitorIVR();
//		}
//		else if(CAT == KFPC_CHACTIONTYPE_CH_MIX_IVR)
//		{
//
//		}
//		else 
//		{
//			ClearSwitchData(result);
//		}
//
//		
//
//		//if( CH_TYPE_AG == m_ChType )
//		//{
//		//	if(NULL != m_CallHandlerRes)
//		//	{
//		//		KFPC_AGCh* pAGCh = (KFPC_AGCh*)m_CallHandlerRes;
//		//		if(m_IVRType == CH_IVRType_NULL)
//		//		{
//		//			INFO_LOG(m_CallID, "AG channel,AGID:%u, CHID:%u, RecoverIVR",pAGCh->GetID(),GetID() );
//		//			pAGCh->RecoverIVRCh();
//
//		//		}
//		//		else
//		//		{
//		//			INFO_LOG(m_CallID, "AG channel,AGID:%u, CHID:%u, current IVRType:%s",pAGCh->GetID(),GetID() ,IVRTypeToStr(m_IVRType));
//		//		}
//		//	}
//		//}
//
//		//报告连接结果
//		if(m_CmdID != 0)
//		{
//			KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);	
//			if(pCmd != NULL)
//			{
//				pCmd->SetResult(result);
//				ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_Disconnect);
//			}
//			else
//			{
//				SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//				WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CmdID);
//			}
//		}
//		else
//		{
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			ERROR_LOG(m_CallID,"ChID:%u has no CmdID",m_ID);
//		}
//	}
//
//}
//unsigned int KFPC_Channel::FirstDTMFReceived()
//{
//	KFPC_VoiceCh* pVoiceCh= GetIVRCh();
//
//	if(NULL != pVoiceCh && (pVoiceCh->GetVoiceStatus() & IVR_STATUS_PLAY_VOICE))
//	{
//		if(pVoiceCh->GetVoiceStopFlag() == 1)
//		{
//			INFO_LOG(m_CallID,"VoiceStopFlag is set 1, Stop Voice Now!");
//			//KFPC_Cmd_StopPlay pCmd_StopPlay(GetCallID(),GetDstAppID(),0,0, true);
//			//pCmd_StopPlay.Execute2();
//
//			pVoiceCh->StopPlayVoice();
//
//		}
//	}
//
//	return 0;
//}
//
//void KFPC_Channel::RecordFileCompleted(const char* pFileName,bool TransformMp3)
//{
//	unsigned int DstAppID = GetDstAppID();
//	if(m_CmdID == 0)
//	{
//		//静态执行CMD
//
//		KFPC_Cmd_EVT_RecordFileCompleted Cmd_RecordFileCompleted(m_CallID,DstAppID,0,0,pFileName,TransformMp3|KFPCTServerCfgInstance->GetRecord_Cfg().GetTransformMp3());
//
//		SetCmdID(Cmd_RecordFileCompleted.GetID(),PREFIX_EXPRESSION_VALUE);
//
//		Cmd_RecordFileCompleted.Execute2();
//		{
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//		}
//
//
//	}
//	else
//	{
//		//check if the command is what we need
//		KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//		unsigned int nRet = pCmd->Execute(KFPC_MSG_ID_EH_StopRecordFile, KFPC_MSG_TYPE_RESPONSE);
//		if(KFPC_ERR_MsgIDNotMatch == nRet)
//		{
//			//放在队列
//			KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->Create_Cmd_EVT_RecordFileCompleted(this,DstAppID,0,0,pFileName,TransformMp3|KFPCTServerCfgInstance->GetRecord_Cfg().GetTransformMp3());
//			PushCmdID(pCmd->GetID());
//		}
//		else if(KFPC_ERR_CmdWaitAck != nRet)
//		{
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			KFPC_CmdMgrInstance->FreeCmd(pCmd);
//		}
//
//	}
//
//	return ;
//}

//unsigned int KFPC_Channel::ConnectToIVRAck( unsigned int Result )
//{
//	//如果连接成功,绑定pchannel to IVR channel
//	if(0 != Result )
//	{
//
//
//		if(CH_IVRType_ONE == GetIVRType())
//		{	
//			ClearIVROne();
//		}
//	}
//
//
//
//	return 0;
//}
//
//void KFPC_Channel::RecordFileBegin()
//{
//	if(m_CmdID != 0)
//	{
//		KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//		if(pCmd != NULL)
//		{
//			ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_RecordFile);
//		}
//		else
//		{
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CmdID);
//		}
//
//		
//	}
//	else
//	{
//		WARNING_LOG(m_CallID,"ChID:%u has no CmdID",m_ID);
//	}
//}
//
//KFPC_VoiceCh* KFPC_Channel::GetIVRCh( )
//{
//	if(m_IVRType == CH_IVRType_ONE)
//	{
//		return (KFPC_VoiceCh*)m_SwitchChRes;
//	}
//	else if(m_IVRType == CH_IVRType_MIX)
//	{
//		return m_IVRChList[0];
//	}
//	else
//	{
//		if(m_ChType == CH_TYPE_CONF)
//		{
//			//虚拟会议通道
//			return m_ConfRes->GetIVRCh();
//		}
//		else
//		{
//			if(m_ConType == ConType_CH_CONF)
//			{	
//				//会议方
//				return (KFPC_VoiceCh*)m_SwitchChRes;
//			}
//			else
//			{
//				//WARNING_LOG(m_CallID,"IVR TYPE ERR:%s",IVRTypeToStr(m_IVRType));
//				return NULL;
//			}
//		}
//	}
//}

//unsigned int KFPC_Channel::Create3PartyConf()
//{
//	unsigned char	BrdID;
//	unsigned int Ret = 0;
//
//	KFPC_EHNode* pEHNode= NULL;
//
//	if(m_ChType == CH_TYPE_SIP)
//	{
//		pEHNode = m_CallHandlerRes->GetVOIPResNode();
//	}
//	else
//	{
//		pEHNode= GetNode();
//
//	}
//
//	if(NULL == pEHNode)
//	{
//		ERROR_LOG(0,"pEHNode is Null.");
//		return KFPC_ERR_FailedToGetNode;
//	}
//
//	if(!pEHNode->m_VoiceMgr.AssignIVRCh(m_ID,m_IVRChList,KFPC_MAX_CH_IVR_SIZE,&BrdID))
//	{
//		return KFPC_ERR_IVRChAssignFailed;
//	}
//
//	unsigned long UserAttr = SET_USER_ATTR((unsigned int)pEHNode->GetID(),GetID());
//
//	m_EH3ConfHandler = ISX_dcb_open(pEHNode->GetID(),BrdID,UserAttr);
//
//	if(m_EH3ConfHandler > 0)
//	{
//		for(unsigned int i=0;i<KFPC_MAX_CH_IVR_SIZE ;i++)
//		{
//			//m_VoiceCh[i]->SetConfCh(this);
//			m_Cdt[i].chan_num = m_IVRChList[i]->GetHandle();
//			m_Cdt[i].chan_attr = MSPA_MODEFULLDUPLX;
//			m_Cdt[i].chan_sel = MSPN_DXCH;
//
//			if(KFPCTServerCfgInstance->GetConfCfg().GetValid() != 0)
//			{
//				int Ret = ISXE_dx_adjvol(m_IVRChList[i]->GetHandle(),
//					KFPCTServerCfgInstance->GetConfCfg().GetDirection(), 
//					KFPCTServerCfgInstance->GetConfCfg().GetVolume());
//
//				if(Ret == -1)
//				{
//					ERROR_LOG(m_CallID,"ISXE_dx_adjvol.");
//				}
//			}
//
//		}
//		
//		//第一个通道用于会议放音
//		int DevHandle = m_IVRChList[0]->GetHandle();
//		int Param = VOICE_MODE_CONF;
//		ISX_dx_setparm(DevHandle,DXCH_VOICE_MODE,(void*)&Param);
//
//		if((Ret = ISX_dcb_estconf(m_EH3ConfHandler,
//			m_Cdt,
//			KFPC_MAX_CH_IVR_SIZE,
//			MSCA_NULL,
//			&m_EH3ConfID,
//			EV_ASYNC,
//			m_ID)) != 0)
//		{
//			FreeConf();
//			WARNING_LOG(m_pCh->GetCallID(),"ConfID:%u ISX_dcb_estconf fail.",m_ID);
//			return KFPC_EH_ERR(Ret);
//		}
//		else
//		{
//			SetIVRType(CH_IVRType_MIX);
//			//Note: m_IVRChList[1] is used to connect current Channel, will be binded until
//			//it connects to IVR. Don't bind here.
//			m_IVRChList[0]->SetSwitchCh(this);
//			m_IVRChList[2]->SetSwitchCh(this);
//			return 0;
//		}
//	}
//	else
//	{
//		FreeConf();
//		WARNING_LOG(0,"ConfID:%u ISX_dcb_open fail.",m_ID);
//		return KFPC_EH_ERR(Ret);
//	}
//}
//
//unsigned int KFPC_Channel::ConnectToCh( KFPC_Channel* pDstCh,unsigned char ConnectMode )
//{
//
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),Peer CallID:0x%llx,ConnectMode:%s",
//		m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),pDstCh->GetCallID(),(ConnectMode == 0)? "FULLDUP":"HALFDUP");
//
//	if((m_Status & KFPC_CALL_LIVE) == 0)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u status:%s err",m_ID,ChStatusToStr(m_Status));
//		return KFPC_ERR_ChStatusErr;
//	}
//
//	if(m_ConType != ConType_CH_NULL)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,ConType:%s.",m_ID,ConTypeToStr(m_ConType));
//		return KFPC_ERR_ChConTypeErr;
//	}
//
//	unsigned int EHConnectMode = (ConnectMode == 0)? SC_FULLDUP:SC_HALFDUP;
//
//	pDstCh->SetConnectMode(EHConnectMode);
//	SetConnectMode(SC_FULLDUP);
//
//	if ((ISX_nr_scroute(
//		GetConnectHandle(),
//		GetConnectDevType(),
//		pDstCh->GetConnectHandle(),
//		pDstCh->GetConnectDevType(),
//		EHConnectMode,
//		EV_ASYNC)) == -1)
//	{
//		ERROR_LOG(m_CallID,"Dst ChID:%u,ChID:%u ISX_nr_scroute Failed:%s", 			
//			pDstCh->GetID(),
//			m_ID,
//			ISX_ATDV_ERRMSGP(pDstCh->GetConnectHandle()));
//		return KFPC_ERR_ScrouteFailed;
//	}
//	else
//	{
//		if(SC_FULLDUP == EHConnectMode)
//		{
//			INFO_LOG(m_CallID,"ChID:%u<-->ChID:%u EHConnectMode:%u", 		
//				m_ID,
//				pDstCh->GetID(),				
//				EHConnectMode);
//		}
//		else
//		{
//			INFO_LOG(m_CallID,"ChID:%u-->ChID:%u EHConnectMode:%u", 		
//				m_ID,
//				pDstCh->GetID(),				
//				EHConnectMode);
//		}
//
//		SetChSwitch(pDstCh);
//		SetActionType(KFPC_CHActionType_CH_CH);
//		return 0;
//	}
//}

//
//unsigned int KFPC_Channel::ConnectToChAck( unsigned int Result )
//{
//	if(m_CmdID == 0)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u not CmdID",m_ID);
//	}
//	else
//	{
//		KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//		if(pCmd != NULL)
//		{
//
//			pCmd->SetResult(Result);
//
//			ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_Connect);
//		}
//		else
//		{
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CallID);
//		}
//	}
//	return 0;
//}

//unsigned int KFPC_Channel::DisconnectToIVRAck( int Result )
//{
//
//
//	return 0;
//}
//
//unsigned int KFPC_Channel::Free3PartyConf()
//{
//	unsigned int Ret = 0;
//
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),ChType:%s",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),ChTypeToStr(m_ChType));
//
//	KFPC_EHNode* pEHNode = GetNode();
//
//	if(NULL == pEHNode)
//	{
//		ERROR_LOG(0,"pEHNode is Null.");
//		return KFPC_ERR_FailedToGetNode;
//	}
//
//	if(m_IVRType != CH_IVRType_MIX)
//	{
//		WARNING_LOG(0,"IVR TYPE is not MIX.");
//		return KFPC_ERR_ChannelTypeErr;
//	}
//
//
//	if(Ret = ISX_dcb_delconf(m_EH3ConfHandler,
//		m_EH3ConfID,
//		EV_ASYNC,GetID()) != 0)
//	{
//		WARNING_LOG(GetCallID(),"EH ConfID:%u ISX_dcb_delconf fail:%s",
//			m_EH3ConfID, ISX_ATDV_ERRMSGP(GetID()));
//		return KFPC_EH_ERR(Ret);
//	}
//
//	if((Ret = ISX_dcb_close(m_EH3ConfHandler)) != 0)
//	{
//		WARNING_LOG(m_pCh->GetCallID(),"EH ConfID:%u ISX_dcb_close fail.",m_EH3ConfID);
//		return KFPC_EH_ERR(Ret);
//	}
//
//	int DevHandle = m_IVRChList[0]->GetHandle();
//	int Param = VOICE_MODE_NORMAL;
//	ISX_dx_setparm(DevHandle,DXCH_VOICE_MODE,(void*)&Param);
//
//	for(int i=0; i<KFPC_MAX_CH_IVR_SIZE; i ++)
//	{
//		m_IVRChList[i]->GetNode()->m_VoiceMgr.RecoverIVRCh(m_IVRChList[i]->GetID());
//	}
//
//	SetIVRType(CH_IVRType_NULL);
//	SetConType(ConType_CH_NULL);
//	SetActionType(KFPC_CHActionType_NULL);
//	m_EH3ConfHandler = 0;
//	m_EH3ConfID =0;
//	return 0;
//}
//
//unsigned int KFPC_Channel::Disconnect(unsigned short Mode)
//{
//	if(NULL != m_SwitchChRes)
//	{
//		if(m_ConType == ConType_CH_NULL)
//		{
//			WARNING_LOG(m_CallID,"ChID:%u con type err:%s",m_ID,ConTypeToStr(m_ConType));
//			return 0;
//		}
//
//		if ((ISX_nr_scunroute(GetConnectHandle(),
//			GetConnectDevType(),
//			m_SwitchChRes->GetConnectHandle(),
//			m_SwitchChRes->GetConnectDevType(), 
//			SC_FULLDUP, Mode)) == -1)
//		{
//			ERROR_LOG(m_CallID,"ChID:%u, ISX_nr_scunroute Failed:%s", 
//				m_ID,
//				ISX_ATDV_ERRMSGP(GetConnectHandle()));
//
//			return KFPC_ERR_ScrouteFailed;
//		}
//		else
//		{	
//			INFO_LOG(m_CallID,"ChID:%u<-x->ChID:%u,ConType:%s ", 
//				m_ID,m_SwitchChRes->GetID(),ConTypeToStr(m_ConType));
//
//			//if(m_ConType == ConType_CH_IVR)
//			//{
//			//	SetActionType(KFPC_CHActionType_CH_IVR);
//			//}
//			//else if(m_ConType == ConType_CH_CH)
//			//{
//			//	SetActionType(KFPC_CHActionType_CH_CH);
//			//}
//			//else if(m_ConType == ConType_CH_CONF)
//			//{
//			//	SetActionType(KFPC_CHActionType_CH_CONF);
//			//}
//			//else
//			//{
//			//	WARNING_LOG(m_CallID,"ChID:%u,ConType:%s",m_ID,ConTypeToStr(m_ConType));
//			//}
//
//			if(Mode == EV_SYNC)
//			{
//				ClearSwitchData(0);
//				return 0;
//			}
//			else
//			{
//				return KFPC_ERR_CmdWaitAck ;
//			}
//			
//		}
//	}
//	else
//	{
//		//WARNING_LOG(m_CallID,"ChID:%u not switch ch res",m_ID);
//		return 0;
//	}
//}
//
//void KFPC_Channel::ClearIVRSwitch()
//{
//	
//	if(m_IVRType == CH_IVRType_ONE)
//	{
//		INFO_LOG(m_CallID,"ChID:%u,VoiceID:%u,VoiceNodeID:%d",
//			m_ID,m_SwitchChRes->GetID(),m_SwitchChRes->GetNodeID());
//
//
//
//		m_SwitchChRes->GetNode()->m_VoiceMgr.RecoverIVRCh(m_SwitchChRes->GetID());		
//
//		m_SwitchChRes->ClearSwitchChRes();
//		ClearSwitchChRes();	
//		SetIVRType(CH_IVRType_NULL);
//		SetConType(ConType_CH_NULL);
//	}
//	else
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,IVRType:%s ERR,ConType:%s",m_ID,IVRTypeToStr(m_IVRType),ConTypeToStr(m_ConType));
//	}
//}
//
//void KFPC_Channel::ClearConfSwitch()
//{
//	if(m_SwitchChRes != NULL)
//	{
//		m_SwitchChRes->ClearSwitchChRes();
//	}
//	else
//	{
//		WARNING_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) SwitchChRes is NULL",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
//		
//	}
//
//	if(m_ConfRes != NULL)
//	{
//		if(m_ConfRes->GetConfSize() == 0)
//		{
//			ERROR_LOG(m_CallID,"ChID:%u,ConfID:%u,ConfSize:%u,IdleConfRes:%u,ConfSize Shoud be not 0.",m_ID,
//				m_ConfRes->GetID(),
//				m_ConfRes->GetConfSize(),
//				m_ConfRes->GetIdleConfRes());
//		}
//		else
//		{
//			INFO_LOG(m_CallID,"ChID:%u,ConfID:%u,ConfSize:%u,IdleConfRes:%u",m_ID,
//				m_ConfRes->GetID(),
//				m_ConfRes->GetConfSize(),
//				m_ConfRes->GetIdleConfRes());
//
//			FreeIdleConf();
//		}
//
//
//	}
//	else
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,ConfRes is NULL.",m_ID);
//	}
//
//
//	SetConType(ConType_CH_NULL);
//	SetConfRes(NULL);
//	ClearSwitchChRes();
//
//
//}
//
//void KFPC_Channel::ClearChSwitch()
//{	
//	INFO_LOG(m_CallID,"ChID:%u",m_ID);
//	m_SwitchChRes->ClearSwitchChRes();
//	SetConType(ConType_CH_NULL);
//	ClearSwitchChRes();
//}
//
//unsigned int KFPC_Channel::StartSendFaxAck(int Result)
//{
//	DEBUG_LOG(m_CallID,"Result:%d",Result);
//
//	if(0 != Result )
//	{
//		
//	}
//	else
//	{
//		if (NULL == m_FaxIPMCh)
//		{
//			Result = KFPC_ERR_IPMChAssignFailed;
//		}
//
//			
//	}
//
//	//报告连接结果
//	if(m_CmdID != 0)
//	{
//		KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//		if(pCmd != NULL)
//		{
//			pCmd->SetResult(Result);
//			ExecuteRspCmd(pCmd,KFPC_MSG_ID_FAX_StartSendFax);
//		}
//		else
//		{
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CmdID);
//		}
//
//
//	}
//	else
//	{
//		ERROR_LOG(m_CallID,"ChID:%u has no CmdID",m_ID);
//	}
//
//	return 0;
//}
//
//unsigned int KFPC_Channel::StopSendFaxAck( int Result )
//{
//	return 0;
//}
//
//unsigned int KFPC_Channel::StartRecvFaxAck( int Result)
//{
//	DEBUG_LOG(m_CallID,"Result:%d",Result);
//
//	if(0 != Result )
//	{
//
//	}
//	else
//	{
//		if (NULL == m_FaxIPMCh)
//		{
//			Result = KFPC_ERR_IPMChAssignFailed;
//		}
//		else
//		{
//	
//		}
//
//	}
//
//	//报告连接结果
//	if(m_CmdID != 0)
//	{
//		KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//		if(pCmd != NULL )
//		{
//			pCmd->SetResult(Result);
//			ExecuteRspCmd(pCmd,KFPC_MSG_ID_FAX_StartRecvFax);
//		}
//		else
//		{
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CmdID);
//		}
//		
//	}
//	else
//	{
//		ERROR_LOG(m_CallID,"ChID:%u has no CmdID",m_ID);
//	}
//
//	return 0;
//	return 0;
//}
//
//unsigned int KFPC_Channel::StopRecvFaxAck( int Result )
//{
//	return 0;
//}
//
//unsigned int KFPC_Channel::SendFaxCompleted( unsigned char PageNum,int Result )
//{
//	KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->Create_Cmd_Disconnect(this,0,0,0,true);
//
//	if(m_CmdID == 0)
//	{
//		SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);
//		ExecuteCmd(pCmd);
//
//	}
//	else
//	{
//		PushCmdID(pCmd->GetID());
//	}
//
//	KFCPTServerAPIHandlerImpInstance->SendTS_EVT_SendFaxCompleted(m_DstAppID,
//		0,0,m_CallID,PageNum,Result);
//	return 0;
//}
//
//unsigned int KFPC_Channel::RecvFaxCompleted( unsigned char PageNum,int Result )
//{
//
//
//	KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->Create_Cmd_Disconnect(this,0,0,0,true);
//
//	if(m_CmdID == 0)
//	{
//		SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);
//		ExecuteCmd(pCmd);
//
//	}
//	else
//	{
//		PushCmdID(pCmd->GetID());
//	}
//
//	KFCPTServerAPIHandlerImpInstance->SendTS_EVT_ReceiveFaxCompleted(m_DstAppID,
//		0,0,m_CallID,PageNum,Result);
//	return 0;
//}
//
//void KFPC_Channel::SetChSwitch( KFPC_Channel* pDstCh )
//{
//	DEBUG_LOG(m_CallID,"ChID:%u",m_ID);
//
//	if(m_ConType != ConType_CH_CH)
//	{
//		//未连接就设置
//		SetSessionCallID();
//		pDstCh->SetSessionCallID(m_SessionCallID);
//	}
//
//
//	pDstCh->SetSwitchChRes(this);
//	pDstCh->SetConType(ConType_CH_CH);
//	SetSwitchChRes(pDstCh);
//	SetConType(ConType_CH_CH);
//	
//
//}
//
//void KFPC_Channel::SetIVRSwitch( KFPC_VoiceCh* pVoiceCh )
//{
//	DEBUG_LOG(m_CallID,"ChID:%u,VoiceID:%u",m_ID,pVoiceCh->GetID());
//	if(CH_IVRType_ONE == GetIVRType())
//	{
//		pVoiceCh->SetSwitchCh(this);
//		SetSwitchChRes(pVoiceCh);
//		SetConType(ConType_CH_IVR);
//	}
//	else
//	{
//		pVoiceCh->SetSwitchCh(this);
//	}
//}
//
//unsigned int KFPC_Channel::ChangeConnectMode( unsigned int ConnectMode )
//{
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),ConnectMode:%s",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),(ConnectMode == 0)? "FULLDUP":"HALFDUP");
//
//	if((m_Status & KFPC_CALL_LIVE) == 0)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u status:%s err",m_ID,ChStatusToStr(m_Status));
//		return KFPC_ERR_ChStatusErr;
//	}
//
//	if(KFPC_CHActionType_NULL == m_ActionType)
//	{
//		if ((ISX_nr_scunroute(GetConnectHandle(),
//			GetConnectDevType(),
//			m_SwitchChRes->GetConnectHandle(),
//			m_SwitchChRes->GetConnectDevType(), 
//			SC_FULLDUP, EV_ASYNC)) == -1)
//		{
//			ERROR_LOG(m_CallID,"ChID:%u, ISX_nr_scunroute Failed:%s", 
//				m_ID,
//				ISX_ATDV_ERRMSGP(GetConnectHandle()));
//
//			return KFPC_ERR_ScrouteFailed;
//		}
//		else
//		{
//			m_SwitchChRes->SetConnectMode((ConnectMode == 0)? SC_FULLDUP:SC_HALFDUP);
//			SetConnectMode((ConnectMode == 0)? SC_FULLDUP:SC_HALFDUP);
//
//			SetActionType(KFPC_CHActionType_CH_CHANGE_CONNECT_MODE);
//			return 0;
//		}
//	}
//	else if(KFPC_CHActionType_CH_CHANGE_CONNECT_MODE == m_ActionType)
//	{
//		if(m_ConType == ConType_CH_CONF)
//		{
//			if ((ISX_nr_scroute(
//				m_SwitchChRes->GetConnectHandle(),
//				m_SwitchChRes->GetConnectDevType(),
//				GetConnectHandle(),
//				GetConnectDevType(),
//				((ConnectMode == 0)? SC_FULLDUP:SC_HALFDUP),
//				EV_ASYNC)) == -1)
//			{
//				ERROR_LOG(m_CallID,"ChID:%u ISX_nr_scroute Failed:%s", 			
//					m_ID,
//					ISX_ATDV_ERRMSGP(m_SwitchChRes->GetConnectHandle()));
//				return KFPC_ERR_ScrouteFailed;
//			}
//			else
//			{				
//				return 0;
//			}		
//		}
//		else if(m_ConType == ConType_CH_CH)
//		{
//			if ((ISX_nr_scroute(
//				GetConnectHandle(),
//				GetConnectDevType(),
//				m_SwitchChRes->GetConnectHandle(),
//				m_SwitchChRes->GetConnectDevType(),
//				((ConnectMode == 0)? SC_FULLDUP:SC_HALFDUP),
//				EV_ASYNC)) == -1)
//			{
//				ERROR_LOG(m_CallID,"ChID:%u ISX_nr_scroute Failed:%s", 			
//					m_ID,
//					ISX_ATDV_ERRMSGP(m_SwitchChRes->GetConnectHandle()));
//				return KFPC_ERR_ScrouteFailed;
//			}
//			else
//			{		
//
//				return 0;
//			}		
//		}
//		else
//		{
//			WARNING_LOG(m_CallID,"ChID:%u,ConType:%s,err.",m_ID,ConTypeToStr(m_ConType));
//			return KFPC_ERR_ChConTypeErr;
//		}
//	}
//	else
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,Action:%d,err.",m_ID,m_ActionType);
//		return KFPC_ERR_ChannelAction;
//	}
//
//}
//
//void KFPC_Channel::SetActionType( KFPC_ChannelActionType val )
//{
//	DEBUG_LOG(m_CallID,"ActionType:%s-->ActionType:%s",ActionTypeToStr(m_ActionType),ActionTypeToStr(val));
//	m_ActionType = val;
//}
//
//KFPC_VoiceCh* KFPC_Channel::GetDTMFCh()
//{
//	if(m_IVRType == CH_IVRType_ONE)
//	{
//		return (KFPC_VoiceCh*)m_SwitchChRes;
//	}
//	else if(m_IVRType == CH_IVRType_MIX)
//	{
//		return m_IVRChList[1];
//	}
//	else
//	{
//		if(m_ChType == CH_TYPE_CONF)
//		{
//			return NULL;
//		}
//		else
//		{
//			if(m_ConType == ConType_CH_CONF)
//			{
//				return (KFPC_VoiceCh*)m_SwitchChRes;
//			}
//			else
//			{
//				WARNING_LOG(m_CallID,"IVR TYPE ERR:%s",IVRTypeToStr(m_IVRType));
//				return NULL;
//			}
//		}
//	}
//}
//
//unsigned int KFPC_Channel::DisconnectMixIVR(unsigned short Mode)
//{
//	DEBUG_LOG(m_CallID,"Mode:%u",Mode);
//
//	KFPC_CallHandler* pChRes = GetCallHandlerResRes();
//	if(NULL == pChRes)
//	{
//		ERROR_LOG(m_CallID,"ChRes:%u is Null.",GetID());
//		return KFPC_ERR_ChResIsNull;
//	}
//
//	if(m_IVRType == CH_IVRType_MIX)
//	{
//		int DevHandle = pChRes->GetConnectHandle();
//		int DevType = pChRes->GetConnectDevType();
//
//		if(DevType == SC_XOIP)
//		{
//			DevType = SC_XOIP_MIX;
//		}
//		else if(DevType == SC_DTI)
//		{
//			DevType = SC_DTI_MIX;
//		}
//		else if(DevType == SC_M3G)
//		{
//			DevType = SC_M3G_MIX;
//		}
//
//		if ((ISX_nr_scunroute(DevHandle,
//			DevType,
//			GetIVRChList()[1]->GetHandle(),
//			SC_VOX,
//			SC_FULLDUP, Mode)) == -1)
//		{
//			ERROR_LOG(GetCallID(),"ChID:%u,CmdID:%u ISX_nr_scunroute Failed:%s", 
//				GetID(),
//				m_ID,
//				ISX_ATDV_ERRMSGP(GetHandle()));
//
//			return KFPC_ERR_ScrouteFailed;
//		}
//		else
//		{
//			SetActionType(KFPC_CHACTIONTYPE_CH_MIX_IVR);
//			if(Mode == EV_SYNC)
//			{
//				ClearSwitchData(0);
//			}
//
//			return 0;
//		}
//	}
//	else
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,IVRType:%s",m_ID,IVRTypeToStr(m_IVRType));
//		return 0;
//	}
//
//}
//
//unsigned int KFPC_Channel::DisconnectCallInAbnormalStatus()
//{
//	Disconnect(EV_SYNC);
//
//	if(CH_IVRType_MIX == GetIVRType())
//	{
//		DisconnectMixIVR(EV_SYNC);
//		Free3PartyConf();
//	}
//
//	ReleaseCall(16);
//	Send_EVT_ReleasedCall(16);
//	Init();
//	return 0;
//}
//
//
unsigned int KFPC_Channel::Send_EVT_ReleasedCall( int cause )
{
// 	INFO_LOG(GetCallID(),"DstID:%d",GetDstAppID());
// 	if(m_DstAppID > 0)
// 	{
// 
// 		//检测APP
// 		if(KFPC_CheckAppID(m_DstAppID) == 0)
// 		{
// 			KFCPTServerAPIHandlerImpInstance->SendTS_EVT_ReleasedCall(GetDstAppID(),
// 				0,
// 				0,
// 				GetCallID(),
// 				cause);
// 			return 0;
// 		}	
// 
// #ifdef TSERVER_GL
// 		else if(CheckComID(m_DstAppID))
// 		{
// 			
// 			TSAPI_IMPInstance->Send_ConnectionCleared(m_DstAppID,m_ID,m_AppSpecificData,cause,0);
// 
// 		}
// #endif
// 
// 
// 	}

	return 0;
}
//
//void KFPC_Channel::CancelCmdWithDSPError(unsigned int nReason)
//{
//	INFO_LOG(GetCallID(),"ChID:%u, DSP Error handling", GetID());
//	if(m_CmdID != 0)
//	{
//		KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//		if(pCmd != NULL)
//		{
//			unsigned int MsgID = pCmd->GetMsgID() ;
//			if(pCmd->GetCmdTypeIsCmdSet())
//			{
//				pCmd->SetStopFlag(true,KFPC_ERR_DSPERR);
//				KFPC_BaseCommand* pExeCmd = KFPC_CmdMgrInstance->GetCmd(pCmd->GetExeCmdID());
//				MsgID = pExeCmd->GetMsgID();
//			}
//			pCmd->SetResult(KFPC_ERR_DSPERR);
//			ExecuteRspCmd(pCmd,MsgID);
//		}
//		else
//		{
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CmdID);
//		}
//	}
//}
//
//void KFPC_Channel::ProcessEstConfError( unsigned int nReason )
//{
//	CancelCmdWithDSPError(nReason);
//	if( CH_TYPE_CONF == m_ChType)
//	{
//		m_ConfRes->FreeConf();
//	}
//}
//
//void KFPC_Channel::ProcessRouteError( unsigned int nReason )
//{
//	CancelCmdWithDSPError(nReason);
//	SetConType(ConType_CH_NULL);
//}
//
//unsigned int KFPC_Channel::ConnectToFax()
//{
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u)",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
//
//	if((m_Status & KFPC_CALL_LIVE) == 0)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u status:%s err",m_ID,ChStatusToStr(m_Status));
//		return KFPC_ERR_ChStatusErr;
//	}
//
//	KFPC_EHNode* pEHNode= GetNode();
//	if(NULL == pEHNode)
//	{
//		ERROR_LOG(m_CallID,"pEHNode is Null.");
//		return KFPC_ERR_FailedToGetNode;
//	}
//
//	//在对应节点上分配一个IPMCh
//	KFPC_IPMCh*	 pIPMCh = NULL;
//
//	if(ConType_CH_FAX == m_ConType)
//	{
//		return KFPC_ERR_FAXAlreadyConnected;
//	}
//	else if(ConType_CH_NULL != m_ConType)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,ConType:%s.",m_ID,ConTypeToStr(m_ConType));
//		return KFPC_ERR_ChConTypeErr;
//	}
//	else
//	{
//		if((pIPMCh = pEHNode->m_VOIPMgr.AssignIPMChCh())== NULL)
//		{
//			if((pIPMCh = KFPC_NodeMgrInstance->AssignIPMChCh()) == NULL)
//			{
//				WARNING_LOG(GetCallID(),"Allocate IPM channel not enough");
//				return KFPC_ERR_IPMChAssignFailed;
//			}
//		}
//
//
//	}
//
//
//	pIPMCh->SetConnectMode(SC_FULLDUP);
//
//	if ((ISX_nr_scroute(pIPMCh->GetConnectHandle(), pIPMCh->GetConnectDevType(),
//			GetConnectHandle(),GetConnectDevType(),  
//		SC_FULLDUP, EV_ASYNC)) == -1)
//	{
//		ERROR_LOG(m_CallID,"IPMID:%u ChID:%u ISX_nr_scroute Failed:%s", 
//			pIPMCh->GetID(), GetID(),
//			ISX_ATDV_ERRMSGP(pIPMCh->GetConnectHandle()));
//
//		RecoverFaxRes();
//		
//
//		return KFPC_ERR_ScrouteFailed;
//	}
//	else
//	{
//		INFO_LOG(m_CallID,"IPMID:%u<-->ChID:%u", pIPMCh->GetID(), m_ID);
//
//		SetFaxSwitch(pIPMCh);
//
//		SetActionType(KFPC_CHActionType_CH_FAX);
//		return 0;
//	}
//
//}
//
//void KFPC_Channel::SetFaxSwitch( KFPC_IPMCh* pIPMCh )
//{
//	INFO_LOG(m_CallID,"ChID:%u",m_ID);
//	//保存FaxIPMCh
//	SetFaxIPMCh(pIPMCh);
//	SetConType(ConType_CH_FAX);
//	SetSwitchChRes(pIPMCh);
//
//	pIPMCh->SetSwitchCh(this);
//}
//
//void KFPC_Channel::ClearFaxSwitch()
//{
//	INFO_LOG(m_CallID,"ChID:%u",m_ID);
//
//	StopSendFax();
//
//	RecoverFaxRes();
//
//	SetConType(ConType_CH_NULL);
//	m_SwitchChRes->ClearSwitchChRes();
//	SetSwitchChRes(NULL);
//}
//
//void KFPC_Channel::DoStartMediaAck( int Result )
//{
//	if(Result == 0)
//	{
//		INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u)",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
//	}
//	else
//	{
//		WARNING_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) fail.",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
//	}
//	
//
//	if(m_CmdID > 0)
//	{
//		KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//		if(pCmd != NULL)
//		{
//
//			pCmd->SetResult(Result);
//
//			ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_StartMedia);
//		}
//		else
//		{
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CmdID);
//		}
//	}
//
//}
//
//void KFPC_Channel::DoStopMediaAck( int Result )
//{
//	if(Result == 0)
//	{
//		INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u)",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
//	}
//	else
//	{
//		WARNING_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) fail.",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
//	}
//
//
//	if(m_CmdID > 0)
//	{
//		KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//		if(pCmd != NULL)
//		{
//
//			pCmd->SetResult(Result);
//
//			ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_StopMedia);
//		}
//		else
//		{
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CmdID);
//		}
//	}
//}
//
//int KFPC_Channel::StartFax()
//{
//	KFPC_IPMCh* pIPMCh= GetFaxIPMCh();
//
//	if (NULL == pIPMCh)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,pIPMCh is NULL.",m_ID);
//		return KFPC_ERR_IPMChAssignFailed;
//	}
//
//	int nRet = pIPMCh->IpmStartMedia(true);
//
//	if (nRet != 0)
//	{
//		return KFPC_EH_ERR(nRet);
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//int KFPC_Channel::Voice2Fax()
//{
//	KFPC_IPMCh* pIPMCh= GetFaxIPMCh();
//
//	if (NULL == pIPMCh)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,pIPMCh is NULL.",m_ID);
//		return KFPC_ERR_IPMChAssignFailed;
//	}
//
//	return pIPMCh->Voice2Fax();
//
//}
//
//void KFPC_Channel::DoVoice2FaxAck( int Result )
//{
//	KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//	if(pCmd != NULL)
//	{
//
//		pCmd->SetResult(Result);
//
//		ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_Voice2Fax);
//	}
//	else
//	{
//		SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//		WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CmdID);
//	}
//}
//
//void KFPC_Channel::ProcessFaxAppOffLine()
//{
//	if(ConType_CH_FAX != m_ConType )
//	{
//		WARNING_LOG(m_CallID,"ChID:%u not sending fax.",m_ID);
//		return;
//	}
//	ReleaseCall(KFPC_ERR_FAXDisconnected);
//	ClearFaxSwitch();
//
//}
//
//unsigned int KFPC_Channel::StartSendFax( const char* pFileName,const char *pSenderIdent,const char *pSubAddress,
//	const char *pPageHeaderInfo,const char *pIdentifier)
//{
//	
//	if (m_FaxIPMCh == NULL)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,pIPMCh is NULL.",m_ID);		
//		return KFPC_ERR_IPMChAssignFailed;
//	}
//
//	//获取可用的传真服务器
//	KFPC_FaxSer* pFaxSer = KFPC_FaxSerMgrInstance->GetFaxSer(m_FaxAppID);
//	if (NULL == pFaxSer)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,FaxServer is null.",m_ID);
//		return KFPC_ERR_NoAvailableFaxSer;
//	}
//
//	//SetFaxAppID(pFaxSer->GetAPPID());
//
//	//发送 请求发送传真命令
//	return KFPCFaxSerAPIHandlerImpInstance->SendREQ_Fax_StartSendFax(
//		pFaxSer->GetAPPID(),
//		0,
//		0,
//		m_CallID,
//		pFileName,
//		pSenderIdent,
//		pSubAddress,
//		pPageHeaderInfo,
//		pIdentifier
//		);
//}
//
//unsigned int KFPC_Channel::StartRecvFax( const char* pFileName )
//{
//
//	if (m_FaxIPMCh == NULL)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,pIPMCh is NULL.",m_ID);		
//		return KFPC_ERR_IPMChAssignFailed;
//	}
//
//	//获取可用的传真服务器
//	KFPC_FaxSer* pFaxSer = KFPC_FaxSerMgrInstance->GetFaxSer(m_FaxAppID);
//	if (NULL == pFaxSer)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,FaxServer is null.",m_ID);
//		return KFPC_ERR_NoAvailableFaxSer;
//	}
//
//	//SetFaxAppID(pFaxSer->GetAPPID());
//
//	//发送 请求发送传真命令
//	return KFPCFaxSerAPIHandlerImpInstance->SendREQ_Fax_StartRecvFax(
//		pFaxSer->GetAPPID(),
//		0,
//		0,
//		m_CallID,
//		pFileName
//
//		);
//}
//
//unsigned int KFPC_Channel::StopRecvFax()
//{
//	//发送 请求停止接受传真命令
//	if(0 != m_FaxAppID)
//	{
//		return KFPCFaxSerAPIHandlerImpInstance->SendREQ_Fax_StopRecvFax(
//			m_FaxAppID,
//			0,
//			0,
//			m_CallID
//			);
//	}
//	else
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,FaxAppID not exist.",m_ID);		
//		return KFPC_ERR_AppIDInvalid;
//	}
//	return 0;
//}
//
//unsigned int KFPC_Channel::StopSendFax()
//{
//	//发送 请求停止接受传真命令
//	if(0 != m_FaxAppID)
//	{
//		return KFPCFaxSerAPIHandlerImpInstance->SendREQ_Fax_StopSendFax(
//			m_FaxAppID,
//			0,
//			0,
//			m_CallID
//			);
//	}
//	else
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,FaxAppID not exist.",m_ID);		
//		return KFPC_ERR_AppIDInvalid;
//	}
//	return 0;
//}
//
//void KFPC_Channel::EVT_HookFlash()
//{
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u)",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
//	//放在队列
//	KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->Create_Cmd_EH_Evt_HookFlash(this);
//
//	if(m_CmdID == 0)
//	{
//		SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);
//		ExecuteCmd(pCmd);
//
//	}
//	else
//	{
//		PushCmdID(pCmd->GetID());
//	}
//
//	return;	
//}
//
//void KFPC_Channel::PlayDTMFCompleted( unsigned int Reason )
//{
//
//}
//
//void KFPC_Channel::RecoverIVRForAgChannel()
//{
//	if( CH_TYPE_AG == GetChType() )
//	{
//		if(NULL != GetCallHandlerResRes())
//		{
//			KFPC_AGCh* pAGCh = (KFPC_AGCh*)GetCallHandlerResRes();
//			if(GetIVRType() == CH_IVRType_NULL)
//			{
//				INFO_LOG(GetCallID(), "AG channel,AGID:%u, CHID:%u, RecoverIVR",pAGCh->GetID(),GetID() );
//				pAGCh->RecoverIVRCh();
//
//			}
//			else
//			{
//				INFO_LOG(GetCallID(), "AG channel,AGID:%u, CHID:%u, current IVRType:%s",pAGCh->GetID(),GetID() ,IVRTypeToStr(GetIVRType()));
//			}
//		}
//	}
//}
//
//unsigned int KFPC_Channel::ClearCmdQueue()
//{
//	DEBUG_LOG(GetCallID(),"");
//	if(!m_CmdIDQueue.empty())
//	{
//		KFPC_CmdIDListIter BeginIter = m_CmdIDQueue.begin();
//		//KFPC_CmdIDListIter EndIter = m_CmdIDQueue.end();
//		KFPC_CmdIDListIter Iter ;
//
//		for(Iter = BeginIter; Iter != m_CmdIDQueue.end(); Iter++)
//		{
//			KFPC_BaseCommand* pCmd  = KFPC_CmdMgrInstance->GetCmd(*Iter);
//			if(NULL != pCmd)
//			{
//				KFPC_CmdMgrInstance->FreeCmd(pCmd);
//			}
//		}		
//	}
//	m_CmdIDQueue.clear();
//	return 0;
//}
//
//void KFPC_Channel::OnRSP_API_TTS_TO_FILE( KFPC_RSP_API_TTS* pTTSMsg )
//{
//	KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(GetCmdID());
//	if(pCmd == NULL)
//	{
//		WARNING_LOG(m_CallID,"No find Cmd,pChID:%u",GetID());
//	}
//	else
//	{
//		if(pCmd->GetCmdTypeIsCmdSet())
//		{
//
//			KFPC_BaseCommandSet *pPlayVoiceCmd = (KFPC_BaseCommandSet *)pCmd;
//
//
//			if(pTTSMsg->Result == 0)
//			{
//				pPlayVoiceCmd->SetPlayContent(pTTSMsg->TTSFileName);
//			}
//			else
//			{
//				pCmd->SetStopFlag(true,pTTSMsg->Result);
//			}
//		
//			ExecuteRspCmd(pCmd,pTTSMsg->MsgHead.un32MsgId);
//		}
//		else
//		{
//			ERROR_LOG(m_CallID,"CmdID:%u not a CmdSet");
//		}
//
//	}
//}
//
//unsigned int KFPC_Channel::RequestFaxCh()
//{
//	if (m_FaxIPMCh == NULL)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,pIPMCh is NULL.",m_ID);		
//		return KFPC_ERR_IPMChAssignFailed;
//	}
//
//	//获取可用的传真服务器
//	KFPC_FaxSer* pFaxSer = KFPC_FaxSerMgrInstance->GetAvailableFaxSer();
//	if (NULL == pFaxSer)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u,FaxServer is null.",m_ID);
//		return KFPC_ERR_NoAvailableFaxSer;
//	}
//
//	SetFaxAppID(pFaxSer->GetAPPID());
//
//	//发送 请求发送传真命令
//	return KFPCFaxSerAPIHandlerImpInstance->SendREQ_Fax_RequestFaxCh(
//		pFaxSer->GetAPPID(),
//		0,
//		0,
//		m_CallID,
//		m_FaxIPMCh->GetSrcAddr()->IpAddr.IpAddr,
//		m_FaxIPMCh->GetSrcAddr()->RtpPort.UdpPort
//		);
//}
//
//unsigned int KFPC_Channel::RequestFaxChAck( char* pFaxServIP,unsigned short FaxServRTPPort,int Result,int FaxMode )
//{
//	DEBUG_LOG(m_CallID,"FaxServIP:%s,FaxServRTPPort:%d,Result:%d",pFaxServIP,FaxServRTPPort,Result);
//	if(0 != Result )
//	{
//
//	}
//	else
//	{
//		if (NULL == m_FaxIPMCh)
//		{
//			Result = KFPC_ERR_IPMChAssignFailed;
//		}
//		else
//		{
//			m_FaxIPMCh->SetDstAddr(	pFaxServIP,
//				FaxServRTPPort);
//
//			if(FaxMode == 0)
//			{
//				m_FaxIPMCh->SetG711Fax();	
//			}
//			else
//			{
//				m_FaxIPMCh->SetT38Fax();
//			}
//		}
//
//	}
//
//	//报告连接结果
//	if(m_CmdID != 0)
//	{
//		KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//		if(pCmd != NULL)
//		{
//			pCmd->SetResult(Result);
//			ExecuteRspCmd(pCmd,KFPC_MSG_ID_FAX_RequestFaxCh);
//		}
//		else
//		{
//			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//			WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CmdID);
//		}
//
//
//	}
//	else
//	{
//		ERROR_LOG(m_CallID,"ChID:%u has no CmdID",m_ID);
//	}
//
//	return 0;
//}
//
//void KFPC_Channel::SetDstAppID( unsigned int val )
//{
//	DEBUG_LOG(m_CallID,"ChID:%u DstAppID:%u-->DstAppID:%u",m_ID,m_DstAppID,val);
//	m_DstAppID = val;
//}
//
//
//unsigned int KFPC_Channel::GetCallID_TIME()
//{
//	KFPC_CallID*	pCallID;
//	
//	pCallID = (KFPC_CallID*)&m_CallID;
//	
//	return pCallID->CallIDInfo.Time;
//}
//
//void KFPC_Channel::ChannelParked()
//{
//#ifdef TSERVER_GL
//	if(m_RelMode == CHANNEL_RELMODE_PARK)
//	{
//		TSAPI_IMPInstance->Send_ConnectionParked(m_DstAppID,m_ID,m_AppSpecificData,0);
//	}
//	
//#endif
//}
//
//unsigned int KFPC_Channel::Send_EVT_AnsweredCall()
//{
//	INFO_LOG(GetCallID(),"DstID:%d",GetDstAppID());
//	if(m_DstAppID > 0)
//	{
//
//		//检测APP
//		if(KFPC_CheckAppID(m_DstAppID) == 0)
//		{
//			KFCPTServerAPIHandlerImpInstance->SendTS_EVT_AnsweredCall(m_DstAppID,
//				0,
//				0,
//				m_CallID);
//			return 0;
//		}	
//
//#ifdef TSERVER_GL
//		else if(CheckComID(m_DstAppID))
//		{
//
//			TSAPI_IMPInstance->Send_Answered(m_DstAppID,m_ID,m_AppSpecificData,0);
//
//		}
//#endif
//
//
//	}
//
//	return 0;
//}
//
//unsigned int KFPC_Channel::Send_EVT_PlayVoiceCompleted()
//{
//	INFO_LOG(GetCallID(),"DstID:%d",GetDstAppID());
//	if(m_DstAppID > 0)
//	{
//
//		//检测APP
//		if(KFPC_CheckAppID(m_DstAppID) == 0)
//		{
//			KFCPTServerAPIHandlerImpInstance->SendTS_EVT_PlayVoiceCompleted(m_DstAppID,
//				0,
//				0,
//				m_CallID);
//			return 0;
//		}	
//
//#ifdef TSERVER_GL
//		else if(CheckComID(m_DstAppID))
//		{
//
//			if(0 == m_PlayApiFlag)
//			{
//				TSAPI_IMPInstance->Send_AnnouncementCompleted(m_DstAppID,m_ID,m_AppSpecificData,0,0);
//			}
//			else
//			{
//				TSAPI_IMPInstance->PlayCompleted(m_DstAppID,m_ID);
//			}
//			
//
//		}
//#endif
//
//	}
//
//	return 0;
//}
//
//unsigned int KFPC_Channel::Send_EVT_CollectDTMFCompleted(unsigned int  DigitCount,const char* Digits,unsigned int Result)
//{
//	INFO_LOG(GetCallID(),"DstID:%d",GetDstAppID());
//	if(m_DstAppID > 0)
//	{
//
//		//检测APP
//		if(KFPC_CheckAppID(m_DstAppID) == 0)
//		{
//
//			KFCPTServerAPIHandlerImpInstance->SendTS_EVT_CollectDTMFCompleted(m_DstAppID,
//				0,
//				0,
//				m_CallID,
//				DigitCount,
//				Digits,
//				Result);
//
//			return 0;
//		}	
//
//#ifdef TSERVER_GL
//		else if(CheckComID(m_DstAppID))
//		{
//
//			TSAPI_IMPInstance->Send_DigitsGathered(m_DstAppID,m_ID,m_AppSpecificData,Digits,Result,0);
//
//		}
//#endif
//	}
//	return 0;
//}
//
//unsigned int KFPC_Channel::EVT_MoreInfo( const char* Num )
//{
//
//		unsigned int DstAppID = GetDstAppID();
//	
//		AppendMoreInfo(Num);
//	
//
//		if(m_CmdID !=0 )
//		{
//			//check if the command is what we need
//			KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//			if(pCmd != NULL)
//			{
//				if(pCmd->GetCmdClassID() == KFPC_TSERVER_CLASS_ID_Cmd_DeflectCall )
//				{
//					if(m_MoreInfoBuf.length() == 0)
//					{
//						pCmd->SetMoreInfo(Num);
//					}
//					else
//					{
//						m_MoreInfoBuf += Num;
//						pCmd->SetMoreInfo(m_MoreInfoBuf.c_str());
//						m_MoreInfoBuf = "";
//					}
//			
//					//pCmd->SetCallID(m_CallID);
//
//					unsigned int nRet = pCmd->Execute(KFPC_MSG_ID_EH_EVT_MoreInfo, KFPC_MSG_TYPE_EVENT);
//
//					if(KFPC_ERR_MsgIDNotMatch == nRet)
//					{
//
//					}
//					else if(KFPC_ERR_CmdWaitAck != nRet)
//					{
//						SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//						KFPC_CmdMgrInstance->FreeCmd(pCmd);
//					}
//
//					return 0;
//				}
//				
//			}
//			else
//			{
//				WARNING_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),CmdID:%u is NULL.",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_CmdID);
//			}
//
//		}
//
//		SetMoreInfoBuf(Num);
//
//	return 0;
//}
//
//void KFPC_Channel::AppendMoreInfo( const char* val )
//{
//	m_MoreInfo += val;
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),MoreInfo:%s",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_MoreInfo.c_str());
//}
//
//unsigned int KFPC_Channel::Send_MoreInfo( const char* Num )
//{
//	if(NULL == m_CallHandlerRes)
//	{
//		WARNING_LOG(0,"ChID:%u ChRes is null.",m_ID);
//		return KFPC_ERR_ChResIsNull;
//	}
//	else
//	{
//		AppendMoreInfo(Num);
//		if(m_ReqMoreinfo)
//		{
//			
//			return m_CallHandlerRes->Send_MoreInfo(Num);
//		}
//		else
//		{
//			SetMoreInfoBuf(Num);
//			return KFPC_ERR_CmdWaitAck;
//		}
//
//
//	}	
//}
//
//void KFPC_Channel::UpdateMoreInfo2Called()
//{
//	strncat(m_Device.CalledNO,m_MoreInfo.c_str(),KFPC_MAX_NUMBER_SIZE-1);
//}
//
//
//unsigned int KFPC_Channel::Send_MoreInfoAck( unsigned int Ret )
//{
//	KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);
//
//	if(pCmd != NULL)
//	{
//
//		pCmd->SetResult(Ret);
//
//		ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_SendMoreInfo);
//	}
//	else
//	{
//		SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//		WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CmdID);
//	}
//
//	return 0;
//}
//
unsigned int KFPC_Channel::Send_EVT_AlertCall()
{
// 	INFO_LOG(GetCallID(),"DstID:%d",GetDstAppID());
// 	if(m_DstAppID > 0)
// 	{
// 
// 		//检测APP
// 		if(KFPC_CheckAppID(m_DstAppID) == 0)
// 		{
// 			KFCPTServerAPIHandlerImpInstance->SendTS_EVT_AlertCall(m_DstAppID,
// 				0,
// 				0,
// 				m_CallID,
// 				0);
// 			return 0;
// 		}	
// 
// #ifdef TSERVER_GL
// 		else if(CheckComID(m_DstAppID))
// 		{
// 
// 			
// 
// 		}
// #endif
// 
// 
// 	}

	return 0;
}
//
//void KFPC_Channel::DoMoreInfoTimeOut()
//{
//
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),Called:%s",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_Device.CalledNO);
//
//	m_MoreInfoTimeOutID = 0;
//	m_OverlapTimeOut = 0;
//
//	KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->Create_Cmd_EVT_IncomingCall(this,m_Device);
//
//	if(m_CmdID == 0)
//	{
//		//静态执行CMD
//		//EH_Cmd_EVT_IncomingCall	Cmd_IncomingCall(m_CallID,m_DstAppID,0,0,Device);
//
//		SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);
//
//		//Cmd_IncomingCall.Execute2();
//		//SetCmdID(0,PREFIX_EXPRESSION_VALUE);
//
//		ExecuteCmd(pCmd);
//
//
//	}
//	else
//	{
//		//放在队列
//
//
//		PushCmdID(pCmd->GetID());
//	}
//	
//	if(GetSAMEvtTimeOut() > 0)
//	{
//		SetSAMEvtTimer();
//	}
//}
//
//void KFPC_Channel::ClearMoreInfoTimer()
//{
//	
//	DEBUG_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),MoreInfoTimeOutID:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_MoreInfoTimeOutID);
//	if(m_MoreInfoTimeOutID != 0)
//	{
//		KFPC_MoreInfoTimerInstance->m_Timer.ClearTimer(m_MoreInfoTimeOutID);
//	}
//	
//	m_MoreInfoTimeOutID = 0;
//
//
//}
//
//void KFPC_Channel::AppendMoreInfo2Called( const char* val )
//{
//	strncat(m_Device.CalledNO,val,KFPC_MAX_NUMBER_SIZE-1);
//
//	INFO_LOG(m_CallID,"CalledNO:%s",m_Device.CalledNO);
//}
//
//void KFPC_Channel::SetMoreInfoTimer()
//{
//	
//	//m_MoreInfoTimeOutID = KFPC_MoreInfoTimerInstance->m_Timer.SetTimer(NULL,NULL,m_OverlapTimeOut,0,m_CallID);
//	m_MoreInfoTimeOutID = KFPC_MoreInfoTimerInstance->SetMoreInfoTimer(m_CallID,m_OverlapTimeOut);
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),MoreInfoTimeOutID:%u,OverlapTimeOut:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_MoreInfoTimeOutID,m_OverlapTimeOut);
//}
//
//void KFPC_Channel::SetMoreInfoBuf( const char* val )
//{
//	m_MoreInfoBuf += val;
//
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),MoreInfoBuf:%s",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_MoreInfoBuf.c_str());
//}
//
//unsigned int KFPC_Channel::EVT_ReqMoreinfo()
//{
//
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),MoreInfoBuf:%s",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_MoreInfoBuf.c_str());
//
//	m_ReqMoreinfo = true;
//
//	if(m_MoreInfoBuf.length() > 0)
//	{
//		Send_MoreInfo(m_MoreInfoBuf.c_str());
//		m_MoreInfoBuf = "";
//	}
//	return 0;
//}
//
//unsigned int KFPC_Channel::EVT_Dialing()
//{
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),MoreInfoBuf:%s",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_MoreInfoBuf.c_str());
//
//	m_ReqMoreinfo = true;
//
//	if(m_MoreInfoBuf.length() > 0)
//	{
//		Send_MoreInfo(m_MoreInfoBuf.c_str());
//		m_MoreInfoBuf = "";
//	}
//
//	return 0;
//}
//
//void KFPC_Channel::ClearMoreInfoBuf()
//{
//	m_MoreInfoBuf = "";
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u)",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
//}
//
//void KFPC_Channel::EVT_RecvInfo(unsigned int ulSerialNo, const char* pInfo )
//{
//#ifdef MSML
//	
//	KFPCMSMLParseInstance->Parse(pInfo);
//	
//	KFPC_MSMLCommand Cmd = KFPCMSMLParseInstance->GetMSMLCommand();
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),INFO Command:%s",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),MSML_CmdToStr(Cmd));
//
//	switch(Cmd)
//	{
//	case 	KFPC_MSMLCommand_createconference:
//		{
//			SetConfCreator(true);
//			KFPC_CmdSet_MSML_CreateConf* pCmd = KFPC_CmdMgrInstance->Create_CmdSet_MSML_CreateConf(
//				this,
//				KFPCMSMLParseInstance->m_CreateconferenceParam.GetName(),
//				KFPCMSMLParseInstance->m_CreateconferenceParam.GetDeletewhen(),
//				KFPCMSMLParseInstance->m_CreateconferenceParam.GetN_loudest(),
//				KFPCMSMLParseInstance->m_CreateconferenceParam.GetAudiomix_asn_ri(),
//				ulSerialNo);
//
//			ExecuteCmd(pCmd);
//		}
//		break;
//
//	case KFPC_MSMLCommand_joinconference:
//		{
//			unsigned long long	ConfCallID	= KFPC_MsmlChMgr_INSTANCE->CallName2ID(KFPCMSMLParseInstance->m_JoinconferenceParam.Getid2());
//			KFPC_Channel*		pConf		= KFPC_ChMgrInstance->GetChannelByCallID(ConfCallID);
//
//			if(pConf != NULL)
//			{
//				unsigned int		JoinMode	= 0;
//
//				int					DTMFSilence = 0;
//
//				KFPC_CmdSet_MSML_JoinConf*	pCmd = KFPC_CmdMgrInstance->Create_CmdSet_MSML_JoinConf(
//					this,				
//					pConf,
//					JoinMode,
//					DTMFSilence,
//					true,
//					ulSerialNo);
//
//				ExecuteCmd(pCmd);
//			}
//			else
//			{
//				char Body[MAX_SIP_BODY] = "";
//
//				snprintf(Body,MAX_SIP_BODY,
//					"<?xml version=\"1.0\" encoding=\"UTF-8\"?> \n" \
//					"<msml version=\"1.1\">\n" \
//					"<result response=\"200\"/>\n" \
//					"</msml>\n" \
//					);
//
//
//				SIPSendInfoAck(IPEC_SIPReasonStatus488NotAcceptableHere,ulSerialNo,"");
//				ReleaseCall(IPEC_SIPReasonStatus488NotAcceptableHere);
//			}
//
//
//		}
//		break;
//
//	case KFPC_MSMLCommand_modifystream:
//		{
//			unsigned int		JoinMode	= 0;
//
//			if(strcmp(KFPCMSMLParseInstance->m_ModifystreamParam.Getdir(),"to-id1") == 0)
//			{
//				JoinMode = 0;
//			}
//			else
//			{
//				JoinMode = 1;
//			}
//
//			KFPC_CmdSet_MSML_Modifystream* pCmd = KFPC_CmdMgrInstance->Create_CmdSet_MSML_Modifystream(this,JoinMode,ulSerialNo);
//
//			ExecuteCmd(pCmd);
//		}
//		break;
//	}
//#endif
//}
//
//void KFPC_Channel::SetSignalType( KFPC_SignalType val )
//{
//	INFO_LOG(m_CallID,"SignalType:%s-->SignalType:%s",SignalTypeToStr(m_SignalType),SignalTypeToStr(val));
//	m_SignalType = val;
//}
//
void KFPC_Channel::SetUniqueID()
{

	unsigned int AppID = 0;
	SSTServerCfgInstance->GetAppID(AppID);

	m_UniqueID = KFPC_CHANNEL_UNIQUEID(AppID,m_ID);
	//DEBUG_LOG(0,"ChID:%u,UniqueID:0x%x(%u)",m_ID,m_UniqueID,m_UniqueID);
}
//
//void KFPC_Channel::RelayAnswerCall()
//{
//	if(m_ConType == ConType_CH_CH)
//	{
//		
//
//		KFPC_Channel*	pCh = m_SwitchChRes->GetCh();
//
//		if(pCh != NULL)
//		{
//			if(	pCh->GetCallFlag() == CALL_FLAG_IN)
//			{
//				if(pCh->GetStatus() ==  KFPC_CH_Status_CallOffer )
//				{				
//					if(GetStatus() == KFPC_CH_Status_Alerting)
//					{
//						INFO_LOG(m_CallID,"Accept ChID:%u(Span:%u,Channel:%u)-->ChID:%u(Span:%u,Channel:%u)",
//							m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),
//							pCh->m_ID,ChannelToSpan(pCh->m_ID),ChannelToTimeSlot(pCh->m_ID));						
//						pCh->AcceptCall();
//					}
//					else if(GetStatus() == KFPC_CH_Status_Connect)
//					{
//						INFO_LOG(m_CallID,"Connect ChID:%u(Span:%u,Channel:%u)-->ChID:%u(Span:%u,Channel:%u)",
//							m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),
//							pCh->m_ID,ChannelToSpan(pCh->m_ID),ChannelToTimeSlot(pCh->m_ID));
//
//						pCh->AnswerCall();
//
//						if(KFPC_CheckAppID(m_DstAppID) == 0)
//						{
//							KFCPTServerAPIHandlerImpInstance->SendTS_EVT_PassAnswerCall(m_DstAppID,
//								0,
//								0,
//								pCh->GetCallID());
//
//						}
//					}
//				}
//				else if(pCh->GetStatus() == KFPC_CH_Status_Accept)
//				{
//					if(GetStatus() == KFPC_CH_Status_Connect)
//					{
//						INFO_LOG(m_CallID,"Connect ChID:%u(Span:%u,Channel:%u)-->ChID:%u(Span:%u,Channel:%u)",
//							m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),
//							pCh->m_ID,ChannelToSpan(pCh->m_ID),ChannelToTimeSlot(pCh->m_ID));
//
//						pCh->AnswerCall();
//
//						if(KFPC_CheckAppID(m_DstAppID) == 0)
//						{
//							KFCPTServerAPIHandlerImpInstance->SendTS_EVT_PassAnswerCall(m_DstAppID,
//								0,
//								0,
//								pCh->GetCallID());
//
//						}
//					}
//
//				}
//
//			}
//
//		}
//		else
//		{
//			ERROR_LOG(m_CallID,"Con type CH_CH switch ch is NULL.");
//		}
//	}
//}
//
//unsigned int KFPC_Channel::SIPSendInfoAck(unsigned short usCause, unsigned int ulSerialNo,const char* Body )
//{
//	if(NULL == m_CallHandlerRes)
//	{
//		WARNING_LOG(m_CallID,"ChID:%u ChRes is null.",m_ID);
//		return KFPC_ERR_ChResIsNull;
//	}
//	else
//	{
//		INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),usCause:%u,ulSerialNo:%u,Body:%s",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),
//			usCause,ulSerialNo,Body
//			);
//		KFPC_CallHandler* pCallHandler = 	(KFPC_CallHandler*)m_CallHandlerRes;
//		return pCallHandler->SIPSendInfoAck(usCause, ulSerialNo,Body);
//	}	
//}
//
//MSML_DeleteWhen KFPC_Channel::GetMSML_DeleteWhen() const
//{
//	if(m_ConfRes != NULL &&
//		m_ChType == CH_TYPE_CONF)
//	{
//		return m_ConfRes->GetMSML_DeleteWhen();
//	}
//	else
//	{
//		ERROR_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) is not conf channel.",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
//
//		return MSML_DelMode_Never;
//	}
//
//}
//
//void KFPC_Channel::SetMSML_DeleteWhen( MSML_DeleteWhen val )
//{
//	
//	if(m_ConfRes != NULL &&
//		m_ChType == CH_TYPE_CONF)
//	{
//		m_ConfRes->SetMSML_DeleteWhen(val);
//	}
//	else
//	{
//		ERROR_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) is not conf channel.",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
//		
//	}
//}
//
void KFPC_Channel::ClearCallID()
{
	if(m_CallID != 0)
	{
		g_CallCount--;
		DEBUG_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),CallCount:%u,ChannelType:%s",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),g_CallCount,ChTypeToStr(CH_TYPE_SIP));
		m_CallID = 0;
		
		
		
	}
}
//
//void KFPC_Channel::FreeIdleConf()
//{
//	
//
//	if(m_ConfRes!= NULL &&
//		(m_ConfRes->GetMSML_DeleteWhen() == MSML_DelMode_NoMedia ||
//		m_ConfRes->GetMSML_DeleteWhen() == MSML_DelMode_NoControl))
//	{
//
//		if(	m_ConfRes->GetLiveConfParty() == 0)
//		{
//			DEBUG_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),EH ConfID:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_ConfRes->GetEHConfID());
//	
//			if(m_ConfRes->GetCh() != NULL)
//			{
//				KFPC_CmdSet_TS_FreeConf* pCmd = KFPC_CmdMgrInstance->Create_CmdSet_FreeConf(m_ConfRes->GetCh(),0,
//					0,
//					0);
//
//				if(pCmd != NULL)
//				{
//
//					if(m_ConfRes->GetCh()->GetCmdID() == 0)
//					{
//						m_ConfRes->GetCh()->SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);
//						KFPC_ExeCmdIDTask*	pExeCmdTask = new KFPC_ExeCmdIDTask(KFPC_CmdMgrInstance,pCmd->GetID());
//						KFPC_AppMainThreadInstance->PutTask(pExeCmdTask);
//						KFPC_EHSwitchInstance->WakeUp();
//					}
//					else
//					{
//						m_ConfRes->GetCh()->PushCmdID(pCmd->GetID());
//					}
//				}
//				else
//				{
//					ERROR_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) Create_CmdSet_FreeConf fail",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
//
//				}
//			}
//			else
//			{
//				ERROR_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) Conf Ch is NULL.",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID));
//			}
//
//		}
//	}
//
//}
//
//void KFPC_Channel::ClearConfTimer()
//{
//	if(m_FreeConfTimer != 0)
//	{
//		DEBUG_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),FreeConfTimer:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_FreeConfTimer);
//		KFPC_ConfTimerInstance->m_Timer.ClearTimer(m_FreeConfTimer);
//		m_FreeConfTimer = 0;
//	}
//	
//}
//
//void KFPC_Channel::SetCreateConfTimer( int Result )
//{
//	if(Result == 0)
//	{
//		m_FreeConfTimer = KFPC_ConfTimerInstance->m_Timer.SetTimer(0,0,CREATE_CONF_TIMER,0,m_CallID);
//
//		DEBUG_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),FreeConfTimer:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_FreeConfTimer);
//	}
//}
//
//void KFPC_Channel::RecoverFaxRes()
//{
//	if(m_FaxIPMCh != NULL)
//	{
//		KFPC_EHNode* pEHNode = m_FaxIPMCh->GetNode();
//
//		if(pEHNode != NULL)
//		{
//			pEHNode->m_VOIPMgr.RecoverIPMCh(m_FaxIPMCh);
//		}
//		else
//		{
//			ERROR_LOG(m_CallID,"FaxIPMCh no Node.");
//
//		}
//		SetFaxIPMCh(NULL);
//	}
//}
//
void KFPC_Channel::Log()
{
// 	char	CallIDTimeStr[100];
// 
// 	TimeToStr(CallIDTimeStr,GetCallID_TIME()+KFPC_START_TIME);
// 
// 	char	InitTimeStr[100];
// 	TimeToStr(InitTimeStr,m_InitTime);
// 
// 	DEBUG_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),UniqueID:%u,SignalType:%s,Status:%s,CallIDTime:%s,InitTime:%s,CallerNO:%s,CalledNO:%s,OriginalCalled:%s,RedirectingNum:%s,ChannelType:%s",
// 		m_ID,
// 		ChannelToSpan(m_ID),
// 		ChannelToTimeSlot(m_ID),
// 		m_UniqueID,
// 		SignalTypeToStr(m_SignalType),
// 		ChStatusToStr(m_Status),
// 		CallIDTimeStr,
// 		InitTimeStr,
// 		m_Device.CallerNO,
// 		m_Device.CalledNO,
// 		m_Device.OriginalCalled,
// 		m_Device.RedirectingNum,
// 		ChTypeToStr(m_ChType));

}
//
//void KFPC_Channel::ClearSwitchData( int result )
//{
//	switch(m_ConType)
//	{
//		//case KFPC_CHActionType_CH_IVR:
//	case ConType_CH_IVR:
//		{
//			if(0 == result )
//			{
//				if(CH_IVRType_ONE == GetIVRType())
//				{		
//
//					ClearIVRSwitch();
//				}
//				else
//				{
//					INFO_LOG(m_CallID,"Mix IVR was disconnected");
//				}
//
//			}
//
//		}
//		break;
//		//case KFPC_CHActionType_CH_CH:
//	case ConType_CH_CH:
//		{   
//			////对端是AG通道，要将它自己的IVR资源重新连起来，以便播放忙音
//			if(NULL != m_SwitchChRes)
//			{
//				KFPC_Channel* pSwitchCh = (KFPC_Channel*)m_SwitchChRes;
//
//				if(NULL != pSwitchCh)
//				{
//					pSwitchCh->RecoverIVRForAgChannel();
//
//					pSwitchCh->ChannelParked();
//
//				}
//				//if(pSwitchCh->GetChType() == CH_TYPE_AG)
//				//{
//				//	KFPC_AGCh* pAGCh = (KFPC_AGCh*)pSwitchCh->GetCallHandlerResRes();
//
//				//	if(pSwitchCh->GetIVRType() == CH_IVRType_NULL)
//				//	{
//				//		if(NULL != pAGCh)
//				//		{
//				//			KFPC_AGCh* pAGCh = (KFPC_AGCh*)((KFPC_Channel*)m_SwitchChRes)->GetCallHandlerResRes();
//
//				//			INFO_LOG(m_CallID, "Peer is AG,AGID:%u, CHID:%u, RecoverIVR",pAGCh->GetID(),pSwitchCh->GetID() );
//				//			pAGCh->RecoverIVRCh();
//				//		}
//				//	}
//				//	else
//				//	{
//				//		if(NULL != pAGCh)
//				//		{								
//				//			INFO_LOG(m_CallID, "Peer is AG,AGID:%u, CHID:%u, current IVRType:%s",pAGCh->GetID(),pSwitchCh->GetID(),IVRTypeToStr(pSwitchCh->GetIVRType()) );
//				//			
//				//		}
//				//	}
//				//}
//			}
//			ClearChSwitch();
//		}
//		break;
//		//case KFPC_CHActionType_CH_CON
//	case ConType_CH_CONF:
//		{
//			ClearConfSwitch();
//
//			//LeaveConfAck(result);
//		}
//		break;
//	case ConType_CH_FAX:
//		{
//			ClearFaxSwitch();
//		}
//		break;
//	default:
//		WARNING_LOG(m_CallID,"ChID:%u ConType:%s",m_ID,ConTypeToStr(m_ConType));
//
//	}
//	//对AG通道，将它自己的IVR资源重新连起来，以便播放忙音
//	RecoverIVRForAgChannel();
//}
//
void KFPC_Channel::LogCDR()
{

	char	InitTimeStr[100];
	TimeToStr(InitTimeStr, m_InitTime);

	char	AnswerTimeStr[100];
	TimeToStr(AnswerTimeStr, m_AnswerTime);

	char	ConnectTimeStr[100];
	TimeToStr(ConnectTimeStr, m_ConnectTime);

	char	ReleaseTimeStr[100];
	TimeToStr(ReleaseTimeStr, m_ReleaseTime);

	unsigned int	TalkTime = 0;
	if (m_AnswerTime > 0)
	{
		TalkTime = (unsigned int)(m_ReleaseTime - m_AnswerTime);
	}
	unsigned int	OccupyTime = 0;

	//if (m_ChType == CH_TYPE_CONF)
	//{
	//	m_CallFlag = CALL_FLAG_CONF;
	//}


	if (m_InitTime == 0)
	{
		WARNING_LOG(m_CallID, "InitTime is 0,%s,%s,%u,%u,%s,%s,%s,%s,%s,%s,%s,%u,%u",

			CallFlag2Str(m_CallFlag),
			ChTypeToStr(CH_TYPE_SIP),
			ChannelToSpan(m_ID),
			ChannelToTimeSlot(m_ID),
			m_Device.CallerNO, m_Device.CalledNO, m_Device.TrunkGroup,
			InitTimeStr, AnswerTimeStr, ConnectTimeStr, ReleaseTimeStr,
			TalkTime,
			m_RemoteRelease);
	}

	KFPC_CDR_Loger()->Info(",0x%llx,%s,%s,%u,%u,%s,%s,%s,%s,%s,%s,%s,%u,%u,0x%llx,%s,%u,%u",
		m_CallID,
		CallFlag2Str(m_CallFlag),
		ChTypeToStr(CH_TYPE_SIP),
		ChannelToSpan(m_ID),
		ChannelToTimeSlot(m_ID),
		m_Device.CallerNO, m_Device.CalledNO, m_Device.TrunkGroup,
		InitTimeStr, AnswerTimeStr, ConnectTimeStr, ReleaseTimeStr,
		TalkTime,
		m_RemoteRelease,
		m_SessionCallID,
		m_FromIp.c_str(),
		m_ConfCreator,
		m_Cause);

	if (m_CallID > 0)
	{
		DEBUG_LOG(m_CallID, "InsertCDR");

		char szInsertSQL[KFPC_MAX_SQL_STR] = "";

		int j = snprintf(szInsertSQL, KFPC_MAX_SQL_STR, "INSERT INTO tbl_ts_callrecord ("
			"CallID,"
			"CallType,"
			"ChannelType,"
			"Span,"
			"TimeSlot,"
			"Caller,"
			"Called,"
			"TrunkGroup,"
			"InitTime,"
			"AnswerTime,"
			"ConnectTime,"
			"ReleaseTime,"
			"TalkTime,"
			"RemoteRelease,"
			"SessionCallID,"
			"IP,"
			"ConfCreator,"
			"Cause"
			") VALUES ("
			"0x%llx,'%s','%s',%u,%u,'%s','%s','%s','%s','%s','%s','%s',%u,%u,0x%llx,'%s',%u,%u"
			")",
			m_CallID,
			CallFlag2Str(m_CallFlag),
			ChTypeToStr(CH_TYPE_SIP),
			ChannelToSpan(m_ID),
			ChannelToTimeSlot(m_ID),
			m_Device.CallerNO, m_Device.CalledNO, m_Device.TrunkGroup,
			InitTimeStr, AnswerTimeStr, ConnectTimeStr, ReleaseTimeStr,
			TalkTime,
			m_RemoteRelease,
			m_SessionCallID,
			m_FromIp.c_str(),
			m_ConfCreator,
			m_Cause);

#ifndef TSERVER_NODB

		KFPC_DBTask* pDBTask = NULL;

		smart_new(KFPC_DBTask(), pDBTask);

		pDBTask->SetSQLDebug(SSTServerCfgInstance->GetDBAccessInfoSet()->GetSQLDebug());

		pDBTask->SetSql(szInsertSQL);

		KFPC_DBThreadPoolInstance->PutTask(pDBTask);
#endif
	}


}
//
//void KFPC_Channel::SetSAMEvtTimer()
//{
//	m_SAMEvtTimerID = KFPC_MoreInfoTimerInstance->SetSAMEvtTimer(m_CallID,m_SAMEvtTimeOut);
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),SAMEvtTimerID:%u,SAMEvtTimeOut:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_SAMEvtTimerID,m_SAMEvtTimeOut);
//
//}
//
//void KFPC_Channel::ClearSAMEvtTimer()
//{
//
//	DEBUG_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),SAMEvtTimerID:%u",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_SAMEvtTimerID);
//	if(m_SAMEvtTimerID != 0)
//	{
//		KFPC_MoreInfoTimerInstance->m_Timer.ClearTimer(m_SAMEvtTimerID);
//	}
//
//	m_SAMEvtTimerID = 0;
//
//}
//
//void KFPC_Channel::DoSAMTimeOut()
//{
//	INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),Called:%s",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_Device.CalledNO);
//	m_SAMEvtTimerID = 0;
//
//#ifdef TSERVER_GL
//	
//
//	TSAPI_IMPInstance->Send_SAMEvent(m_DstAppID,m_ID,m_MoreInfo.c_str());
//
//#endif
//
//}
//
//void KFPC_Channel::ClearMonitorIVR()
//{
//	m_MonitorIVRCh->GetNode()->m_VoiceMgr.RecoverIVRCh(m_MonitorIVRCh->GetID());		
//	m_MonitorIVRCh->ClearSwitchChRes();
//	SetMonitorIVRCh(NULL);
//}
//
//unsigned int KFPC_Channel::DisconnectMonitorIVR(unsigned short Mode)
//{
//	if(NULL != m_MonitorIVRCh)
//	{
//
//		if ((ISX_nr_scunroute(GetConnectHandle(),
//			GetConnectDevType(),
//			m_MonitorIVRCh->GetConnectHandle(),
//			m_MonitorIVRCh->GetConnectDevType(), 
//			SC_FULLDUP, Mode)) == -1)
//		{
//			ERROR_LOG(m_CallID,"ChID:%u, ISX_nr_scunroute Failed:%s", 
//				m_ID,
//				ISX_ATDV_ERRMSGP(GetConnectHandle()));
//
//			return KFPC_ERR_ScrouteFailed;
//		}
//		else
//		{	
//			INFO_LOG(m_CallID,"ChID:%u<-x->ChID:%u MonitorIVR", 
//				m_ID,m_MonitorIVRCh->GetID());
//
//			SetActionType(KFPC_CHActionType_CH_MONITOR_IVR);
//
//			//if(m_ConType == ConType_CH_IVR)
//			//{
//			//	SetActionType(KFPC_CHActionType_CH_IVR);
//			//}
//			//else if(m_ConType == ConType_CH_CH)
//			//{
//			//	SetActionType(KFPC_CHActionType_CH_CH);
//			//}
//			//else if(m_ConType == ConType_CH_CONF)
//			//{
//			//	SetActionType(KFPC_CHActionType_CH_CONF);
//			//}
//			//else
//			//{
//			//	WARNING_LOG(m_CallID,"ChID:%u,ConType:%s",m_ID,ConTypeToStr(m_ConType));
//			//}
//
//			if(Mode == EV_SYNC)
//			{
//				ClearMonitorIVR();
//				return 0;
//			}
//			else
//			{
//				return KFPC_ERR_CmdWaitAck ;
//			}
//			
//		}
//	}
//	else
//	{
//		WARNING_LOG(m_CallID,"ChID:%u not switch ch res",m_ID);
//		return 0;
//	}
//}
//
//void KFPC_Channel::SetSessionCallID()
//{
//
//	m_InitTime = time(NULL);
//
//	KFPC_CallID	CallID;
//	CallID.CallIDInfo.ChID = m_ID;
//	CallID.CallIDInfo.AppID = KFPC_GetLibParam()->AppInfo.AppID;
//	unsigned long long T = (time(NULL) - KFPC_START_TIME);
//	CallID.CallIDInfo.Time = (unsigned int)T;
//
//	m_SessionCallID = CallID.CallID;
//
//
//	DEBUG_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) SessionCallID:0x%llx",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_SessionCallID);
//
//
//}
//
//void KFPC_Channel::SetSessionCallID( unsigned long long val )
//{
//	
//	m_SessionCallID = val;
//	DEBUG_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u) SessionCallID:0x%llx",m_ID,ChannelToSpan(m_ID),ChannelToTimeSlot(m_ID),m_SessionCallID);
//}
//
//void KFPC_Channel::SetChType( KFPC_CH_TYPE val )
//{
// 	m_ChType = val;
// 
// 	if(m_ChType == CH_TYPE_CONF)
// 	{
// 		m_CallFlag = CALL_FLAG_CONF;
// 	}
//}
//
//KFPC_MySipCh* KFPC_Channel::GetMySipCh()
//{
//	if(m_ChType == CH_TYPE_SIP &&
//		m_SipChType == SIP_CH_TYPE_MYSIP)
//	{
//		return (KFPC_MySipCh*)m_CallHandlerRes;
//	}
//	else
//	{
//		return NULL;
//	}
//}
//
//KFPC_IPMCh* KFPC_Channel::GetXiopCh()
//{
//	if(m_ChType == CH_TYPE_SIP &&
//		m_SipChType == SIP_CH_TYPE_SIP &&
//		NULL != m_CallHandlerRes)
//	{
//		 KFPC_SipCh* pSipCh = (KFPC_SipCh*)m_CallHandlerRes;
//
//		return pSipCh->GetXiopCh();
//	}
//	else
//	{
//		return NULL;
//	}
//}
//
void KFPC_Channel::DoCmdTimeOut()
{
	if(m_CmdID > 0)
	{
		KFPC_BaseCommand*	pCmd = KFPC_CmdMgrInstance->GetCmd(m_CmdID);

		if(pCmd != NULL)
		{

			pCmd->SetResult(0);

			ExecuteRspCmd(pCmd,KFPC_MSG_ID_EH_Timer);
		}
		else
		{
			SetCmdID(0,PREFIX_EXPRESSION_VALUE);
			WARNING_LOG(m_CallID,"ChID:%u CmdID:%u invalid.",m_ID,m_CmdID);
		}
	}
}

