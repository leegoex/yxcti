#include "KFPC_CmdTimer.h"
#include "kfpc_logex.h"
#include "KFPC_CmdMgr.h"
#include "KFPC_ChMgr.h"

KFPC_CmdTimer::KFPC_CmdTimer(void)
{
}


KFPC_CmdTimer::~KFPC_CmdTimer(void)
{
}

int KFPC_CmdTimer::Run()
{
	void*	Arg1 = NULL;
	void*	Arg2 = NULL;
	unsigned int TimerID = 0;
	unsigned long long CallID = 0;
	unsigned long long CmdID = 0;
	int		Ret	=	0;


	Ret = m_Timer.OutTime(&TimerID,&Arg1,&Arg2,0,&CmdID,&CallID);

	if(Ret == 0)	
	{
		KFPC_Channel*	pCh = KFPC_ChMgrInstance->GetChannelByCallID(CallID);

		if(NULL != pCh)
		{

			pCh->DoCmdTimeOut();
		}
		else
		{
			WARNING_LOG(CallID,"pch is null.");
		}

	}
	return Ret;
}

