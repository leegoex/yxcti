#pragma once
#include "kfpc_loophandler.h"
#include "kfpc_timer.h"
#include <time.h>

class KFPC_CheckInvalidCallID :
	public KFPC_LoopHandler
{
public:
	KFPC_CheckInvalidCallID(void);
	virtual ~KFPC_CheckInvalidCallID(void);

	time_t	m_StartTime;
	virtual int Run();

	static KFPC_CheckInvalidCallID* GetInstance()
	{
		static KFPC_CheckInvalidCallID _Instance;
		return &_Instance;
	}
};

#define KFPC_CheckInvalidCallIDInstance	KFPC_CheckInvalidCallID::GetInstance()