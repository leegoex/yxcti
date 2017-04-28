#include "kfpc_logex.h"
#include "KFPC_DBThreadPool.h"
#include "KFPC_Cmd_EVT_IncomingCall.h"
#include "KFPC_TServerErr.h"
#include "KFPC_Channel.h"
#include "KFPC_TServerConfigFile.h"
#include "KFPC_Q850.h"
#include "KFPC_TServerAPIHandlerImp.h"
#include "KFPC_CmdMgr.h"
#include "KFPC_DBTaskInsertCallAlarm.h"
#include "KFPC_ChMgr.h"
#include "KFPC_ExeCmdIDTask.h"
#include "KFPC_AppMainThread.h"

#include "KFPC_StringUtils.h"

EH_Cmd_EVT_IncomingCall::EH_Cmd_EVT_IncomingCall(unsigned long long& CallID,unsigned int DstAppID,unsigned int UserContext1,unsigned int UserContext2,bool SubCmd):
KFPC_BaseCommand(KFPC_MSG_ID_EH_EVT_IncomingCall,KFPC_MSG_TYPE_EVENT,CallID,DstAppID,UserContext1,UserContext2,SubCmd),
//m_Device(Device),
//m_SignalType(KFPC_SignalType_ClearChannel),
m_Cmd_Status(Cmd_Status_Start)
{
	m_UserContext1 = 0;
	m_UserContext2 = 0;
}


EH_Cmd_EVT_IncomingCall::~EH_Cmd_EVT_IncomingCall(void)
{
	KFPC_Channel* pCh = KFPC_ChMgrInstance->GetChannelByCallID(m_CallID);
	if(NULL != pCh && pCh->GetCmdID() == m_ID)
	{
		pCh->SetCmdID(0,PREFIX_EXPRESSION_VALUE);
	}
}

unsigned int EH_Cmd_EVT_IncomingCall::Execute(unsigned int MsgID,KFPC_MSG_TYPE MsgType,KFPC_MSG_HEADER* MsgHeader,void* pMsg )
{

	switch (m_Cmd_Status)
	{
	case Cmd_Status_Start:
		{
			//unsigned int RetCheckMsg = CheckMsg(MsgID,MsgType);
			//if( RetCheckMsg != 0)
			//{
			//	return RetCheckMsg;
			//}

			KFPC_Channel* pCh = KFPC_ChMgrInstance->GetChannelByCallID(m_CallID);

			if(NULL == pCh)
			{
				ERROR_LOG(m_CallID,"pCh is Null.");
				return KFPC_ERR_ChIDInvalid;
			}

			//pCh->SetCmdID(GetID());

			if((pCh->GetStatus() & KFPC_IDLE_STATUS) )
			{
				KFPC_TrunkGroup*	pTrunkGroup = NULL;

				DEBUG_LOG(0, "TrunkGroup is %s", pCh->GetDevice().TrunkGroup);
				pTrunkGroup = SSTServerCfgInstance->GetTrunkGroupMgr()->GetTrunkGroupByName(pCh->GetDevice().TrunkGroup);
				if (NULL == pTrunkGroup)
				{
					ERROR_LOG(m_CallID, "Not Found TrunkGroup.");
					return KFPC_ERR_TrunkGroupNotFound;
				}

				if(NULL != pTrunkGroup)
				{
					unsigned int StripPrefixLen = strlen(pTrunkGroup->GetStripPrefix());

					if( StripPrefixLen > 0 && 	StripPrefixLen < KFPC_MAX_NUMBER_SIZE)
					{
						char* p = strstr(pCh->GetDevice().CalledNO,pTrunkGroup->GetStripPrefix());

						if(p == pCh->GetDevice().CalledNO)
						{
							char	CalledNO[KFPC_MAX_NUMBER_SIZE];			/**< 被叫号码		**/
							strncpy(CalledNO, pCh->GetDevice().CalledNO,KFPC_MAX_NUMBER_SIZE-1);

							strncpy(pCh->GetDevice().CalledNO,&CalledNO[StripPrefixLen],KFPC_MAX_NUMBER_SIZE-1);
							INFO_LOG(m_CallID,"ChID:%u(Span:%u,Channel:%u),New Called:%s",pCh->GetID(),ChannelToSpan(pCh->GetID()),ChannelToTimeSlot(pCh->GetID()), pCh->GetDevice().CalledNO);
						}
					}

				}



				pCh->GetDevice().TimeSlot = ChannelToTimeSlot(pCh->GetID());
				pCh->GetDevice().Span	= ChannelToSpan(pCh->GetID());
				pCh->GetDevice().Type = DEVICE_TYPE_TRUNKGROUP;

				RTrim(pCh->GetDevice().CalledNO,'#');

				pCh->SetStatus(KFPC_CH_Status_CallOffer);

				if(pTrunkGroup->GetAutoAnswer())
				{
					////专用于MSML
					////pCh->AnswerCall();

					//KFPC_Cmd_AnswerCall* pCmd_AnswerCall = KFPC_CmdMgrInstance->Create_Cmd_AnswerCall(pCh,
					//	0,
					//	0,
					//	0);

					//if(pCh->GetCmdID() == 0)
					//{
					//	pCh->SetCmdID(pCmd_AnswerCall->GetID(),PREFIX_EXPRESSION_VALUE);
					//	KFPC_ExeCmdIDTask*	pExeCmdTask = new KFPC_ExeCmdIDTask(KFPC_CmdMgrInstance,pCmd_AnswerCall->GetID());
					//	KFPC_AppMainThreadInstance->PutTask(pExeCmdTask);
					//	KFPC_EHSwitchInstance->WakeUp();
					//}
					//else
					//{
					//	pCh->GetCh()->PushCmdID(pCmd_AnswerCall->GetID());
					//}

				}
				else
				{
					return CallOfferToApp(pTrunkGroup, pCh);
				}

			}
			else
			{
				WARNING_LOG(m_CallID,"CmdID:%u,ChID:%u Caller:%s,Called:%s,OrgCalled:%s,RedDirNo:%s Status:%s err.",
					m_ID,
					pCh->GetID(),
					pCh->GetDevice().CallerNO,
					pCh->GetDevice().CalledNO,
					pCh->GetDevice().OriginalCalled,
					pCh->GetDevice().RedirectingNum,
					ChStatusToStr(pCh->GetStatus()));

				pCh->ReleaseCall(IPEC_SIPReasonStatus403Forbidden,"channel status exception");
			}

			return 0;
		}
		break;

	}


	return KFPC_ERR_MsgIDNotMatch;
}

unsigned int EH_Cmd_EVT_IncomingCall::CallOfferToApp( KFPC_TrunkGroup* pTrunkGroup, KFPC_Channel* pCh )
{


	unsigned int AppID  = pTrunkGroup->GetCallOfferAppID(pCh->GetID());

	if(AppID == -1)
	{


		WARNING_LOG(m_CallID,"CmdID:%u,ChID:%u Caller:%s,Called:%s,OrgCalled:%s,RedDirNo:%s,TrunkGroup:%s does not app watch.",
			m_ID,
			pCh->GetID(),
			pCh->GetDevice().CallerNO,
			pCh->GetDevice().CalledNO,
			pCh->GetDevice().OriginalCalled,
			pCh->GetDevice().RedirectingNum,
			pCh->GetDevice().TrunkGroup);

		pCh->ReleaseCall(IPEC_SIPReasonStatus403Forbidden, "No Route To Destination app");
		return 0;
	}
	else
	{

		m_DstAppID = AppID;

		unsigned int Ret = -1;

		//检测APP
		if(KFPC_CheckAppID(m_DstAppID) == 0)
		{
			Ret = KFCPTServerAPIHandlerImpInstance->SendTS_EVT_IncomingCall(
				AppID,
				m_UserContext1,
				m_UserContext2,
				m_CallID,
				pCh->GetDevice(),
				KFPC_SignalType_SIP);

			if(Ret != 0)
			{
				pCh->ReleaseCall(IPEC_SIPReasonStatus403Forbidden,"No Route To Destination app");
			}
			else
			{
				pCh->SetDstAppID(AppID);
			}
			return 0;
		}	


		WARNING_LOG(m_CallID,"Dst APPID:%u does not online.",m_DstAppID);

		pCh->ReleaseCall(IPEC_SIPReasonStatus403Forbidden, "No Route To Destination app");
		return 0;
	}
}
