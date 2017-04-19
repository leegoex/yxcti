#include "KFPC_ExeCmdIDTask.h"
#include "KFPC_TServerErr.h"


KFPC_ExeCmdIDTask::~KFPC_ExeCmdIDTask(void)
{
}

void* KFPC_ExeCmdIDTask::Svc()
{
	KFPC_BaseCommand* pCmd = m_BaseCmdMgr->GetCmd(m_CmdID);

	if(pCmd != NULL)
	{
		ExecuteCmd(pCmd);
	}

	return NULL;
}

unsigned int KFPC_ExeCmdIDTask::ExecuteCmd( KFPC_BaseCommand* pCmd )
{
	m_CmdID = 0;

	unsigned int Ret =pCmd->Execute2();

	if(KFPC_ERR_CmdWaitAck == Ret)
	{

	}
	else if(KFPC_ERR_MsgIDNotMatch == Ret)
	{
	}
	else 
	{
		m_BaseCmdMgr->FreeCmd(pCmd);
	}

	return Ret;
}

KFPC_ExeCmdIDTask::KFPC_ExeCmdIDTask( KFPC_BaseCmdMgr* pBaseCmdMgr,unsigned int CmdID ):
m_BaseCmdMgr(pBaseCmdMgr),
	m_CmdID(CmdID)
{

}