#pragma once
#include "kfpc_threadtask.h"
#include "KFPC_BaseCmdMgr.h"
#include "KFPC_BaseCommand.h"

class KFPC_ExeCmdIDTask :
	public KFPC_ThreadTask
{

private:
	unsigned int m_CmdID;

	virtual void* Svc();

	unsigned int ExecuteCmd( KFPC_BaseCommand* pCmd );
	KFPC_BaseCmdMgr*	m_BaseCmdMgr;
public:	

	KFPC_ExeCmdIDTask(KFPC_BaseCmdMgr*	pBaseCmdMgr,unsigned int CmdID);
	virtual ~KFPC_ExeCmdIDTask(void);

	unsigned int GetCmdID() { return m_CmdID; }
	void SetCmdID(unsigned int val) { m_CmdID = val; }

};

