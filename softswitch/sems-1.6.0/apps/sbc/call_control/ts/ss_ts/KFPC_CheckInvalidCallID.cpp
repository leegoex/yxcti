#include "KFPC_CheckInvalidCallID.h"
#include "kfpc_logex.h"
#include "KFPC_ChMgr.h"
#include "KFPC_TServerConfigFile.h"
#include "KFPC_CmdMgr.h"

KFPC_CheckInvalidCallID::KFPC_CheckInvalidCallID(void):
m_StartTime(0)
{
	m_StartTime = time(NULL);
}


KFPC_CheckInvalidCallID::~KFPC_CheckInvalidCallID(void)
{
}

int KFPC_CheckInvalidCallID::Run()
{
	if((time(NULL) - m_StartTime) > SSTServerCfgInstance->GetCheckCallIDInterval())
	{
		m_StartTime = time(NULL);

		KFPC_ChMgrInstance->CheckInvalidCallID();
		KFPC_CmdMgrInstance->CheckInvalidCmd();
	}

	return -1;
}
