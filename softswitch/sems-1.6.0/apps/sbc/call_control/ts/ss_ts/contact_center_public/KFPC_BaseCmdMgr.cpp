#include "KFPC_BaseCmdMgr.h"
#include "kfpc_logex.h"
#include "KFPC_ContactCenterPublicDef.h"

KFPC_BaseCmdMgr::KFPC_BaseCmdMgr(void)
{
}


KFPC_BaseCmdMgr::~KFPC_BaseCmdMgr(void)
{
}



//CommandMapIter_t& KFPC_BaseCmdMgr::GetBeginCmdIter()
//{
//	return m_CommandMap.begin();
//}
//
//CommandMapIter_t& KFPC_BaseCmdMgr::GetEndCmdIter()
//{
//	return m_CommandMap.end();
//}

KFPC_BaseCommand* KFPC_BaseCmdMgr::GetExeCmd()
{
	return m_CmdIter->second;
}

void KFPC_BaseCmdMgr::SetCmdIter( CommandMapIter_t iter )
{
	m_CmdIter = iter;
}

void KFPC_BaseCmdMgr::SetBeginCmdIter()
{
	m_CmdIter = m_CommandMap.begin();
}

CommandMapIter_t& KFPC_BaseCmdMgr::GetExeCmdIter()
{
	return m_CmdIter;
}

void KFPC_BaseCmdMgr::SetNextCmdIter()
{
	++m_CmdIter;
}

KFPC_BaseCommand* KFPC_BaseCmdMgr::GetCmd( unsigned int CmdID )
{
	CommandMapIter_t	Iter = m_CommandMap.find(CmdID);

	if(Iter != m_CommandMap.end())
	{
		return Iter->second;
	}
	else
	{
		WARNING_LOG(0,"CmdID:%u not exist.",CmdID);
		return NULL;
	}
}

void KFPC_BaseCmdMgr::FreeCmd( KFPC_BaseCommand* pCmd )
{
	CommandMapIter_t	Iter = m_CommandMap.find(pCmd->GetID());

	if(Iter != m_CommandMap.end())
	{
		FreeCmd(Iter);

		//m_KFPC_MemPool.Free(pCmd);
	}
	else
	{
		ERROR_LOG(pCmd->GetCallID(),"ChID:%u,CmdID:%u,left CommandMap size:%u.",CallIDToChannel(pCmd->GetCallID()),pCmd->GetID(),m_CommandMap.size());
	}
}

void KFPC_BaseCmdMgr::FreeCmd( unsigned int CmdID )
{
	CommandMapIter_t	Iter = m_CommandMap.find(CmdID);

	if(Iter != m_CommandMap.end())
	{
		FreeCmd(Iter);
		//INFO_LOG(0,"CmdID:%u freed, CommandMap size:%u.",CmdID,m_CommandMap.size());
	}
	else
	{
		ERROR_LOG(0,"CmdID:%u not exit, CommandMap size:%u.",CmdID,m_CommandMap.size());
	}
}

void KFPC_BaseCmdMgr::FreeCmd( CommandMapIter_t Iter)
{
	KFPC_BaseCommand* pCmd = Iter->second;
	m_CommandMap.erase(Iter);

	DEBUG_LOG(pCmd->GetCallID(),"ChID:%u,CmdID:%u,left CommandMap size:%u.",CallIDToChannel(pCmd->GetCallID()),pCmd->GetID(),m_CommandMap.size());

	delete pCmd;
}

void KFPC_BaseCmdMgr::CheckInvalidCmd()
{
	
	CommandMapIter_t	BeginIter = m_CommandMap.begin();

	for(;BeginIter != m_CommandMap.end();BeginIter++)
	{
		time_t LiveTime = time(NULL) - BeginIter->second->GetCreateTime();

		if(LiveTime > MAX_CMD_LIVE_TIME)
		{
			BeginIter->second->WarningLog();
		}

	}
}
