#include "KFPC_BaseCommandSetEx.h"
#include "kfpc_logex.h"
#include "KFPC_ContactCenterPublicDef.h"
#include "KFPC_TServerErr.h"

KFPC_BaseCommandSetEx::~KFPC_BaseCommandSetEx(void)
{
	KFPC_CMD_SetIter_t	BeginIter = m_CmdIDSet.begin();

	for(;BeginIter != m_CmdIDSet.end();BeginIter++)
	{
		m_BaseCmdMgr->FreeCmd(*BeginIter);
	}
}


unsigned int KFPC_BaseCommandSetEx::Execute( unsigned int MsgID,KFPC_MSG_TYPE MsgType,KFPC_MSG_HEADER* MsgHeade,	void* pMsg)
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
	}

	char MsgIDStr[KFPC_MAX_MSG_ID_STR_LEN]="";
	INFO_LOG(m_CallID,"CmdID:%u,ChID:%u,MsgID:%s,MsgType:%s", m_ID,CallIDToChannel(m_CallID),MsgIDToStr(MsgID,MsgIDStr),MsgTypeToStr(MsgType));

	unsigned int Ret = m_Result;

	KFPC_BaseCommand* pCmd = GetCmd(m_LiveCmdID);

	if(NULL != pCmd)
	{
		pCmd->SetResult(m_Result);
	}

	while((pCmd = GetCmd(m_LiveCmdID)) != NULL)
	{
		if(MsgType == KFPC_MSG_TYPE_RESPONSE ||
			MsgType == KFPC_MSG_TYPE_EVENT)
		{
			Ret = pCmd->Execute( MsgID, MsgType);

			MsgType = KFPC_MSG_TYPE_REQUEST;
			if(m_StopExeFlag)
			{
				//Ret = m_Result;
				break;
			}
		}
		else
		{
			if(m_StopExeFlag)
			{
				//Ret = m_Result;
				break;
			}

			Ret = pCmd->Execute2();
		}

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
			m_Result = Ret;
			break;
		}

		m_LiveCmdID = pCmd->GetNextCmdID();
	}

	SendRSP(m_Result);

	EndExecute();
	return Ret;
}

KFPC_BaseCommand* KFPC_BaseCommandSetEx::GetCmd( unsigned int CmdID )
{
	if(m_CmdIDSet.find(CmdID) != m_CmdIDSet.end())
	{
		if(m_BaseCmdMgr != NULL)
		{
			return m_BaseCmdMgr->GetCmd(CmdID);
		}
		else
		{
			CMD_ERROR_LOG(m_CallID,"Base Cmd Mgr is NULL.");
			return NULL;
		}
	}
	else
	{
		//CMD_WARNING_LOG(m_CallID,"CmdID:%u invalid.",CmdID);
		return NULL;
	}

}

unsigned int KFPC_BaseCommandSetEx::Execute2()
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
	}


	INFO_LOG(m_CallID,"CmdID:%u,ChID:%u", m_ID,CallIDToChannel(m_CallID));

	unsigned int Ret = m_Result;

	KFPC_BaseCommand* pCmd = GetCmd(m_LiveCmdID);

	if(NULL != pCmd)
	{
		pCmd->SetResult(m_Result);
	}

	while((pCmd = GetCmd(m_LiveCmdID)) != NULL)
	{

		if(m_StopExeFlag)
		{
			Ret = m_Result;
			break;
		}

		Ret = pCmd->Execute2();

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
			m_Result = Ret;
			break;
		}

		m_LiveCmdID = pCmd->GetNextCmdID();
	}

	SendRSP(m_Result);

	EndExecute();
	return Ret;
}

void KFPC_BaseCommandSetEx::AppendCmd( unsigned int CmdID )
{
	m_CmdIDSet.insert(CmdID);
	INFO_LOG(m_CallID,"CmdID:%u,Cmd Set size:%u.",CmdID,m_CmdIDSet.size());
}

KFPC_BaseCommandSetEx::KFPC_BaseCommandSetEx( KFPC_BaseCmdMgr* BaseCmdMgr, 
	unsigned int DstAppID, 
	unsigned int UserContext1, 
	unsigned int UserContext2,
	bool SubCmd /*= false*/ ) :
m_First(true),
	KFPC_BaseCommand(0,KFPC_MSG_TYPE_FIRST,0,DstAppID,UserContext1,UserContext2,SubCmd),
	m_LiveCmdID(0),
	m_BaseCmdMgr(BaseCmdMgr)
{
	m_TypeIsCmdSet = true;
}