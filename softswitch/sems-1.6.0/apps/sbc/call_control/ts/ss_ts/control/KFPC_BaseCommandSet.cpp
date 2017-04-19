#include "kfpc_logex.h"
#include "KFPC_BaseCommandSet.h"
#include "KFPC_CmdMgr.h"
#include "KFPC_TServerErr.h"
#include "KFPC_ChMgr.h"

KFPC_BaseCommandSet::KFPC_BaseCommandSet(unsigned int MsgID,KFPC_MSG_TYPE MsgType,unsigned long long& CallID,unsigned int DstAppID,unsigned int UserContext1,unsigned int UserContext2):
m_ExeOrCancel(true),
m_First(true),
KFPC_BaseCommand(MsgID,MsgType,CallID,DstAppID,UserContext1,UserContext2)
{
	m_ExeIter = m_CmdIDList.end();
	m_TypeIsCmdSet = true;
}

unsigned int KFPC_BaseCommandSet::Execute( unsigned int MsgID,KFPC_MSG_TYPE MsgType ,KFPC_MSG_HEADER* MsgHeader,void* pMsg )
{
	if(m_First)
	{
		unsigned int Ret = BeginExecute();

		if(Ret != 0)
		{
			return Ret;
		}
		else
		{
			m_First = false;
		}
		m_ExeIter = m_CmdIDList.begin();
	}

	char MsgIDStr[KFPC_MAX_MSG_ID_STR_LEN]="";
	INFO_LOG(m_CallID,"CmdID:%u,ChID:%u,MsgID:%s,MsgType:%s", m_ID,CallIDToChannel(m_CallID),MsgIDToStr(MsgID,MsgIDStr),MsgTypeToStr(MsgType));

	unsigned int Ret = 0;

	if(m_ExeOrCancel)
	{
		for(;m_ExeIter != m_CmdIDList.end();m_ExeIter++)
		{
			KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(*m_ExeIter);

			if(MsgType == KFPC_MSG_TYPE_RESPONSE ||
				MsgType == KFPC_MSG_TYPE_EVENT)
			{

				Ret = pCmd->Execute( MsgID, MsgType);


				MsgType = KFPC_MSG_TYPE_REQUEST;
				if(m_StopExeFlag)
				{
					Ret = m_Result;
					break;
				}
			}
			else
			{
				if(m_StopExeFlag)
				{
					Ret = m_Result;
					break;
				}

				Ret = pCmd->Execute2();
			}
			
			if(KFPC_ERR_CmdWaitAck == Ret ||
				KFPC_ERR_MsgIDNotMatch == Ret)
			{
				CMD_INFO_LOG(m_CallID,"Ret:%u(%s)",Ret,GetErrorStr(Ret));
				return Ret;
			}
			else if(Ret == 0)
			{

			}
			else
			{
				CMD_WARNING_LOG(m_CallID,"Ret:%d and terminate cmd set",Ret);
				break;
			}
		}
	}
	else
	{
		for(;m_ExeIter != m_CmdIDList.begin();m_ExeIter--)
		{
			KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(*m_ExeIter);

			if(MsgType == KFPC_MSG_TYPE_RESPONSE ||
				MsgType == KFPC_MSG_TYPE_EVENT)
			{
				Ret = pCmd->Execute( MsgID, MsgType);
				MsgType = KFPC_MSG_TYPE_REQUEST;

				if(KFPC_ERR_CmdWaitAck == Ret ||
					KFPC_ERR_MsgIDNotMatch == Ret)
				{
					return Ret;
				}
				else if(Ret == 0)
				{

				}
				else
				{
					WARNING_LOG(m_CallID,"Ret:%d and terminate cmd set",Ret);
					break;
				}
			}
			else
			{
				Ret = pCmd->Execute2();

				if(KFPC_ERR_CmdWaitAck == Ret)
				{
					CMD_INFO_LOG(m_CallID,"Ret:%u(%s)",Ret,GetErrorStr(Ret));
					return Ret;
				}
				else if(Ret == 0)
				{

				}
				else
				{
					CMD_WARNING_LOG(m_CallID,"Ret:%d and terminate cmd set",Ret);
					break;
				}
			}
		}
	}


	SendRSP(Ret);

	EndExecute();
	return Ret;
}

unsigned int KFPC_BaseCommandSet::Execute2()
{
	if(m_First)
	{
		unsigned int Ret = BeginExecute();

		if(Ret != 0)
		{
			return Ret;
		}
		else
		{
			m_First = false;
		}
		m_ExeIter = m_CmdIDList.begin();
	}

	unsigned int Ret = 0;

	for(;m_ExeIter != m_CmdIDList.end();m_ExeIter++)
	{
		KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(*m_ExeIter);

		if(m_StopExeFlag)
		{
			Ret = m_Result;
			break;
		}

		Ret = pCmd->Execute2();

		if(KFPC_ERR_CmdWaitAck == Ret)
		{
			CMD_INFO_LOG(m_CallID,"Ret:%u(%s)",Ret,GetErrorStr(Ret));
			return Ret;
		}
		else if(Ret == 0)
		{

		}
		else
		{
			CMD_WARNING_LOG(m_CallID,"Ret:%d and terminate cmd set",Ret);
			break;
		}
	}


	SendRSP(Ret);

	EndExecute();

	return Ret;	
}
unsigned int KFPC_BaseCommandSet::Cancel()
{
	WARNING_LOG(m_CallID,"CmdID:%u",m_ID);
	SendRSP(KFPC_ERR_CmdCancel);
	return KFPC_ERR_CmdCancel;
}


KFPC_BaseCommandSet::~KFPC_BaseCommandSet(void)
{
	KFPC_CmdIDListIter	BeginIter = m_CmdIDList.begin();
	//KFPC_CmdIDListIter	EndIter = m_CmdIDList.end();

	for(;BeginIter != m_CmdIDList.end();BeginIter++)
	{
		KFPC_CmdMgrInstance->FreeCmd(*BeginIter);
	}
}

void KFPC_BaseCommandSet::SetResult( unsigned int val )
{
	m_Result = val;
	if(!m_CmdIDList.empty())
	{
		KFPC_BaseCommand* pCmd = KFPC_CmdMgrInstance->GetCmd(*m_ExeIter);
		if(pCmd != NULL)
		{
			pCmd->SetResult(val);
		}
	}

	
}
