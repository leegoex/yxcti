#pragma once

#include "kfpc_loophandler.h"
#include "kfpc_timer.h"

class KFPC_CmdTimer :
	public KFPC_LoopHandler
{
public:
	KFPC_CmdTimer(void);
	virtual ~KFPC_CmdTimer(void);

	KFPC_Timer	m_Timer;
	virtual int Run();

	static KFPC_CmdTimer* GetInstance()
	{
		static KFPC_CmdTimer _Instance;
		return &_Instance;
	}
};

#define KFPC_CmdTimerInstance	KFPC_CmdTimer::GetInstance()