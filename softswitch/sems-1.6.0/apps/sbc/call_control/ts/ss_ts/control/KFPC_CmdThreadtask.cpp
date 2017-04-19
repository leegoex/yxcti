#include "KFPC_CmdThreadtask.h"
#include "KFPC_Channel.h"


KFPC_CmdThreadTask::KFPC_CmdThreadTask(KFPC_Channel* pChannel):
m_pCh(pChannel)
{

}

KFPC_CmdThreadTask::~KFPC_CmdThreadTask( void )
{

}

void* KFPC_CmdThreadTask::Svc()
{
	m_pCh->ExeCmdQueue();
	return 0;
}

