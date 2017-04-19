#include "KFPC_LicCtrl.h"


KFPC_LicCtrl::KFPC_LicCtrl(void):
m_LicSize(0xffffffff),
m_UseSize(0)
{
}


KFPC_LicCtrl::~KFPC_LicCtrl(void)
{
}

void KFPC_LicCtrl::Reset()
{
	m_LicSize = 0xffffffff;
	m_UseSize = 0;
}
