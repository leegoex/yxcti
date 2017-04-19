#include "kfpc_logex.h"
#include "kfpc_threadtask.h"
#include <stdio.h>

KFPC_ThreadTask::KFPC_ThreadTask():
m_ThreadTaskType(TTT_RunThread),
m_Param(NULL),
m_TimeStamp(time(NULL))
{
}

KFPC_ThreadTask::KFPC_ThreadTask( void* p ):
m_ThreadTaskType(TTT_RunThread),
m_Param(p),
m_TimeStamp(time(NULL))
{

}

KFPC_ThreadTask::~KFPC_ThreadTask(void)
{
	
}

void* KFPC_ThreadTask::DoSvc(time_t* pDelay)
{
	time_t Delay = time(NULL) - m_TimeStamp;
	if(Delay > MaxThreadDelayAlarm)
	{
		WARNING_LOG(0,"Delay:%u second",Delay);
		if(pDelay != NULL)
		{
			*pDelay = Delay;
		}
	}

	return Svc();
}
KFPC_ExitThreadTask::KFPC_ExitThreadTask( void )
{
	SetThreadTaskType(TTT_ExitThread);
}

KFPC_ExitThreadTask::~KFPC_ExitThreadTask( void )
{

}

