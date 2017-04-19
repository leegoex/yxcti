#include "kfpc_logex.h"
#include "KFPC_ChMgr.h"
#include "KFPC_ContactCenterPublicDef.h"
#include "KFPC_TServerDef.h"
#include "KFPC_CmdMgr.h"
#include "KFPC_TServerErr.h"
#include "KFPC_TServerConfigFile.h"
#include "KFPC_ExeCmdIDTask.h"
#include "KFPC_AppMainThread.h"


KFPC_ChMgr*	KFPC_ChMgr::_Instance = NULL;

KFPC_ChMgr::KFPC_ChMgr(void)
{
	//memset(m_AgChStatMap,0,MAX_STATUS_COUNT*sizeof(unsigned int));
	//memset(m_DTIChStatMap,0,MAX_STATUS_COUNT*sizeof(unsigned int));
	memset(m_SIPChStatMap,0,MAX_STATUS_COUNT*sizeof(unsigned int));
	memset(m_ConfChStatMap,0,MAX_STATUS_COUNT*sizeof(unsigned int));

	//m_AgChStatMap[0] = KFPC_SINGLE_NODE_MAX_AG_SPAN*KFPC_MAX_CHANNEL;
	//m_DTIChStatMap[0] = KFPC_SINGLE_NODE_MAX_DTI_SPAN*KFPC_MAX_CHANNEL;
	//m_SIPChStatMap[0] =  KFPC_SINGLE_NODE_MAX_VOIP_SPAN*KFPC_MAX_CHANNEL;
	//m_ConfChStatMap[0] = KFPC_SINGLE_NODE_MAX_CONF_SPAN*KFPC_MAX_CHANNEL;


	Reset(false);

	//for (int i = 0;i < KFPC_MAX_CHANNEL_NUMBER;i++)
	{
		//m_Channels[i].SetID(i);
		//m_Channels[i].SetUniqueID();

		//SetChannelType(m_Channels[i],i);
		
		//int ChannelNote = i / (KFPC_NODE_MAX_SPAN * KFPC_MAX_CHANNEL);

		//KFPC_EHNode* pNode = KFPC_NodeMgrInstance->GetNode(ChannelNote);
		
		//if(NULL == pNode)
		//{
		//	WARNING_LOG(0,"IsxNo:%u,pNode is null.",ChannelNote);
		//	continue;
		//}
		//m_Channels[i].SetNode(pNode);
		//m_Channels[i].SetStatus(KFPC_CH_Status_Unready);

	}

	//BEGIN_MSG_LOG(0,"");

	//APPEND_MSG_LOG("%d",KFPC_AG_BEGIN_SPAN		);
	//APPEND_MSG_LOG("%d",KFPC_AG_END_SPAN		);
	//APPEND_MSG_LOG("%d",KFPC_DTI_BEGIN_SPAN	);
	//APPEND_MSG_LOG("%d",KFPC_DTI_END_SPAN		);
	//APPEND_MSG_LOG("%d",KFPC_VOIP_BEGIN_SPAN	);
	//APPEND_MSG_LOG("%d",KFPC_VOIP_END_SPAN		);
	//APPEND_MSG_LOG("%d",KFPC_CONFID_BEGIN_SPAN	);
	//APPEND_MSG_LOG("%d",KFPC_CONFID_END_SPAN	);
	//APPEND_MSG_LOG("%d",KFPC_NODE_MAX_SPAN	);
	//APPEND_MSG_LOG("%d",KFPC_MAX_SPAN	);
	//APPEND_MSG_LOG("%d",KFPC_MAX_CHANNEL_NUMBER	);
	//	
	//END_MSG_LOG();
	
}

KFPC_ChMgr::~KFPC_ChMgr(void)
{
}


//void KFPC_ChMgr::SetChannelType(KFPC_Channel &Channel, unsigned int ChannelID)
//{
//	ChannelID = ChannelID % (KFPC_NODE_MAX_SPAN * KFPC_MAX_CHANNEL);
//
//	//if (ChannelID >= SpanTimeSlotToChannel(KFPC_AG_BEGIN_SPAN, 0) && ChannelID <= SpanTimeSlotToChannel(KFPC_AG_END_SPAN, 31))
//	//{
//	//	Channel.SetChType(CH_TYPE_AG);
//	//}
//	//else if (ChannelID >= SpanTimeSlotToChannel(KFPC_DTI_BEGIN_SPAN, 0) && ChannelID <= SpanTimeSlotToChannel(KFPC_DTI_END_SPAN, 31))
//	//{
//	//	Channel.SetChType(CH_TYPE_DTI);
//	//}
//	//else 
//	if (ChannelID >= SpanTimeSlotToChannel(KFPC_VOIP_BEGIN_SPAN, 0) && ChannelID <= SpanTimeSlotToChannel(KFPC_VOIP_END_SPAN, 31))
//	{
//		Channel.SetChType(CH_TYPE_SIP);
//	}
//	else if (ChannelID >= SpanTimeSlotToChannel(KFPC_CONFID_BEGIN_SPAN, 0) && ChannelID <= SpanTimeSlotToChannel(KFPC_CONFID_END_SPAN, 31))
//	{
//		Channel.SetChType(CH_TYPE_CONF);
//	}
//	else
//	{
//		WARNING_LOG(0, "ChannelID(%d) is out of range", ChannelID);
//	}
//}

KFPC_Channel* KFPC_ChMgr::GetChannel(unsigned long ID)
{
	if(ID >= KFPC_MAX_CHANNEL_NUMBER)          
	{		
		ERROR_LOG(0, "ChannelID:%u over %u.", ID, KFPC_MAX_CHANNEL_NUMBER);
		return NULL;
	}

	return &(m_Channels[ID]);
}

void KFPC_ChMgr::Reset(bool log )
{
	for(int i=0;i<KFPC_MAX_CHANNEL_NUMBER;i++)
	{
		m_Channels[i].Reset(log);
	}
}

unsigned int KFPC_ChMgr::GetIdleConfCh( unsigned int NodeID )
{
	if(NodeID < KFPC_MAX_EH_NODE)
	{
		unsigned int ConfBeginCh =	KFPC_NODE_MAX_SPAN*NodeID*KFPC_MAX_CHANNEL + KFPC_CONFID_BEGIN_SPAN*KFPC_MAX_CHANNEL;
		unsigned int ConfEndCh	=	ConfBeginCh + KFPC_SINGLE_NODE_MAX_CONF_SPAN * KFPC_MAX_CHANNEL;

		for (unsigned int i= ConfBeginCh;i<ConfEndCh;i++)
		{
			if(m_Channels[i].GetStatus() == KFPC_CH_Status_Idle)
			{
				return i;
			}
		}

		ERROR_LOG(0,"NodeID:%u not idle conf channel,ConfBeginCh:%u,ConfEndCh:%u.",NodeID,ConfBeginCh,ConfEndCh);
		return -1;
	}
	else
	{
		return -1;
	}
}

KFPC_Channel* KFPC_ChMgr::GetChannelByCallID( unsigned long long& CallID )
{
	if(CallID == 0)
	{
		return NULL;
	}

	unsigned int ChID = 	CallIDToChannel(CallID);

	KFPC_Channel* pCh = GetChannel(ChID);

	if(NULL != pCh)
	{
		if(pCh->GetCallID() == CallID)
		{
			return pCh;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
	
}

void KFPC_ChMgr::SendCallReleasedMsg(int cause)
{
	unsigned int CmdID = 0;
	for(int i=0;i<KFPC_MAX_CHANNEL_NUMBER;i++)
	{
		if(m_Channels[i].GetStatus() & KFPC_CALL_LIVE)
		{
			if(0 != (CmdID = m_Channels[i].GetCmdID()))
			{
				KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(CmdID);
				pCmd->Cancel();
				KFPC_CmdMgrInstance->FreeCmd(CmdID);
			}
			m_Channels[i].Send_EVT_ReleasedCall(cause);
			//m_Channels[i].Reset(false);
		}

	}
}

unsigned int KFPC_ChMgr::CheckCallID( unsigned long long& CallID,KFPC_Channel** ppCh )
{
	if(CallID == 0)
	{
		WARNING_LOG(CallID,"CallID is zero.");
		return KFPC_ERR_CallIDInvalid;
	}
	
	KFPC_CallID* kfpc_CallID = (KFPC_CallID*)&CallID;

	unsigned short	ChID = kfpc_CallID->CallIDInfo.ChID;

	*ppCh = GetChannel(ChID);

	if(NULL == (*ppCh))
	{
		WARNING_LOG(CallID,"Failed to get Channel from ID ChID%u",ChID);
		return KFPC_ERR_ChIDInvalid;
	}

	if((*ppCh)->GetCallID() != CallID)
	{
		DEBUG_LOG(CallID,"ChID:%u CallID:0x%llx err",(*ppCh)->GetID(),(*ppCh)->GetCallID());
		return KFPC_ERR_CallIDInvalid;
	}

	return 0;
}

//
//unsigned int KFPC_ChMgr::NotifyCallReleasedWhenNodeReset( unsigned int NodeID )
//{	
//	unsigned int CmdID = 0;
//	for(int i=0;i<KFPC_MAX_CHANNEL_NUMBER;i++)
//	{
//		if(m_Channels[i].GetStatus() & KFPC_CALL_LIVE && (m_Channels[i].GetNode()->GetID() == NodeID))
//		{
//			if(0 != (CmdID = m_Channels[i].GetCmdID()))
//			{
//				KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(CmdID);
//				pCmd->Cancel();
//				KFPC_CmdMgrInstance->FreeCmd(CmdID);
//			}
//
//			m_Channels[i].Send_EVT_ReleasedCall(16);
//			
//		}
//
//	}
//	return 0;
//}

void KFPC_ChMgr::OnAPP_DISCONNECT( unsigned int APPID )
{
	unsigned int CmdID = 0;
	for(int i=0;i<KFPC_MAX_CHANNEL_NUMBER;i++)
	{
		if(m_Channels[i].GetStatus() & KFPC_CALL_LIVE && (m_Channels[i].GetDstAppID() == APPID))
		{
			if(0 != (CmdID = m_Channels[i].GetCmdID()))
			{
				KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(CmdID);
				pCmd->Cancel();
				KFPC_CmdMgrInstance->FreeCmd(CmdID);

				if(m_Channels[i].GetCmdID() == CmdID)
				{
					m_Channels[i].SetCmdID(0,PREFIX_EXPRESSION_VALUE);
				}
			}
			
			//if(m_Channels[i].GetChType() == CH_TYPE_CONF)
			//{
			//	m_Channels[i].FreeConf();
			//}
			//else
			{
				m_Channels[i].ReleaseCall(16);
			}			
		}

	}
	
}

KFPC_ChMgr* KFPC_ChMgr::GetInstance()
{
	if(_Instance == NULL)
	{
		smart_new(KFPC_ChMgr,_Instance);
	}
	return _Instance;
}

void KFPC_ChMgr::Destory()
{
	if(_Instance != NULL)
	{
		smart_delete(_Instance);
		_Instance = NULL;
	}
}

void KFPC_ChMgr::CheckInvalidCallID()
{
	INFO_LOG(0,"");
	bool	WakeUp = false;

	for(int i=0;i<KFPC_MAX_CHANNEL_NUMBER;i++)
	{
		if( (m_Channels[i].GetCallID()) > 0 && 
			(time(NULL) - m_Channels[i].m_InitTime) > SSTServerCfgInstance->GetCheckCallIDLiveTime())
		{
			m_Channels[i].Log();
			

			//if(m_Channels[i].GetChType() == CH_TYPE_CONF)
			//{

			//}
			//else
			{
				WARNING_LOG(m_Channels[i].GetCallID(),"Purge call");

				//KFPC_Channel* pChannel = &m_Channels[i];

				//KFPC_CmdSet_ReleaseCall* pCmd = KFPC_CmdMgrInstance->Create_CmdSet_ReleaseCall(pChannel,16,0,0,0);

				//if(pChannel->GetCmdID() == 0)
				//{
				//	pChannel->SetCmdID(pCmd->GetID(),PREFIX_EXPRESSION_VALUE);
				//	KFPC_ExeCmdIDTask*	pExeCmdTask = new KFPC_ExeCmdIDTask(KFPC_CmdMgrInstance,pCmd->GetID());
				//	KFPC_AppMainThreadInstance->PutTask(pExeCmdTask);
				//	WakeUp = true;
				//}
				//else
				//{
				//	pChannel->PushCmdID(pCmd->GetID());
				//}
			}
		}
	}

	//if(WakeUp)
	//{
	//	KFPC_EHSwitchInstance->WakeUp();
	//}
}

void KFPC_ChMgr::ChStatusChange( KFPC_Ch_Status Old,KFPC_Ch_Status Now ,KFPC_CH_TYPE ChType)
{
	unsigned int OldInx = GetExp(Old);

	unsigned int NowInx = GetExp(Now);

	if(OldInx < MAX_STATUS_COUNT &&
		NowInx < MAX_STATUS_COUNT)
	{

		switch(ChType)
		{
		//case CH_TYPE_AG:					/**< 模拟通道 */
		//	{
		//		m_AgChStatMap[OldInx]--;
		//		m_AgChStatMap[NowInx]++;
		//	}break;
		//case CH_TYPE_DTI:				/**< 数字中继 */
		//	{
		//		m_DTIChStatMap[OldInx]--;
		//		m_DTIChStatMap[NowInx]++;
		//	}
		//	break;
		case CH_TYPE_SIP:				/**< SIP通道 */
			{
				m_SIPChStatMap[OldInx]--;
				m_SIPChStatMap[NowInx]++;
			}
			break;
		case CH_TYPE_CONF:				/**< 会议通道 */
			{
				m_ConfChStatMap[OldInx]--;
				m_ConfChStatMap[NowInx]++;
			}
			break;
		}


	}
	else
	{
		ERROR_LOG(0,"OldInx:%u,NowInx:%u",OldInx,NowInx);
	}
}

unsigned int KFPC_ChMgr::GetStatusCount( KFPC_Ch_Status Val )
{
	unsigned int Inx = GetExp(Val);

	if(Inx < MAX_STATUS_COUNT)
	{
		return m_SIPChStatMap[Inx]+m_ConfChStatMap[Inx];
	}
	else
	{
		ERROR_LOG(0,"Inx:%u",Inx);
		return 0;
	}
}



unsigned int KFPC_ChMgr::GetUsedCount()
{

	return 
		//GetChUsedCount(m_AgChStatMap)+
		//GetChUsedCount(m_DTIChStatMap) +
		GetChUsedCount(m_SIPChStatMap) +
		GetChUsedCount(m_ConfChStatMap);

}

void KFPC_ChMgr::LogChStat()
{
	//LogChTypeStat(m_AgChStatMap,"AG");
	//LogChTypeStat(m_AgChStatMap,"DTI");
	LogChTypeStat(m_SIPChStatMap,"SIP");
	LogChTypeStat(m_ConfChStatMap,"CONF");
}

void KFPC_ChMgr::LogChTypeStat(unsigned int ChStatMap[],const char* ChannelType)
{
	DEBUG_LOG(0,"ChannelType:%s,Unready:%u,CallOffer:%u,CallOut:%u,Accept:%u,Alerting:%u,"
		"Connect:%u,Release:%u,Failed:%u,OutofService:%u,LocalBlock:%u,"
		"Idle:%u,RemoteBlock:%u,HardwareFailureBlock:%u,OffHook:%u,OnHook:%u,WaitMoreInfo:%u",
		ChannelType,
		ChStatMap[KFPC_CH_Status_Inx_Unready],					
		ChStatMap[KFPC_CH_Status_Inx_CallOffer],				
		ChStatMap[KFPC_CH_Status_Inx_CallOut],					
		ChStatMap[KFPC_CH_Status_Inx_Accept],					
		ChStatMap[KFPC_CH_Status_Inx_Alerting],					
		ChStatMap[KFPC_CH_Status_Inx_Connect],					
		ChStatMap[KFPC_CH_Status_Inx_Release],					
		ChStatMap[KFPC_CH_Status_Inx_Failed],					
		ChStatMap[KFPC_CH_Status_Inx_OutofService],				
		ChStatMap[KFPC_CH_Status_Inx_LocalBlock],				
		ChStatMap[KFPC_CH_Status_Inx_Idle],						
		ChStatMap[KFPC_CH_Status_Inx_RemoteBlock],				
		ChStatMap[KFPC_CH_Status_Inx_HardwareFailureBlock],		
		ChStatMap[KFPC_CH_Status_Inx_OffHook],					
		ChStatMap[KFPC_CH_Status_Inx_OnHook],					
		ChStatMap[KFPC_CH_Status_Inx_WaitMoreInfo	]);
}

unsigned int KFPC_ChMgr::GetChUsedCount( unsigned int ChStatMap[] )
{
	return ChStatMap[KFPC_CH_Status_Inx_CallOffer]+
		ChStatMap[KFPC_CH_Status_Inx_CallOut]+				
		ChStatMap[KFPC_CH_Status_Inx_Accept]+				
		ChStatMap[KFPC_CH_Status_Inx_Alerting]+				
		ChStatMap[KFPC_CH_Status_Inx_Connect]+				
		ChStatMap[KFPC_CH_Status_Inx_Release]+				
		//KFPC_CH_Status_Inx_Failed				
		//KFPC_CH_Status_Inx_OutofService			
		//KFPC_CH_Status_Inx_LocalBlock			
		//KFPC_CH_Status_Inx_Idle					
		//KFPC_CH_Status_Inx_RemoteBlock			
		//KFPC_CH_Status_Inx_HardwareFailureBlock	
		ChStatMap[KFPC_CH_Status_Inx_OffHook]+				
		//KFPC_CH_Status_Inx_OnHook				
		ChStatMap[KFPC_CH_Status_Inx_WaitMoreInfo];
}
