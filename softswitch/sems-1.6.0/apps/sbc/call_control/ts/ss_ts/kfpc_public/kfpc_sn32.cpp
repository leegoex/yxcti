
#include "kfpc_sn32.h"


KFPC_SN32::KFPC_SN32(void)
{
	m_SN = 0;
}


KFPC_SN32::~KFPC_SN32(void)
{

}

unsigned int KFPC_SN32::GetSN()
{
	KFPC_AutoMutex	AutoMtex(&m_Mutex);
	m_SN++;

	if(m_SN == 0)
	{
		m_SN=1;
	}

	return m_SN;
}

