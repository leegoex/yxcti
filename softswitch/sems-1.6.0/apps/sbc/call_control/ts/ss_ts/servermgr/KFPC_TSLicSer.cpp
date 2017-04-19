#include "kfpc_logex.h"
#include "KFPC_TSLicSer.h"
#include "kfpc_sn32.h"

static KFPC_SN32	g_KFPC_LicSerSN;

KFPC_TSLicSer::KFPC_TSLicSer(void):
m_AppID(0),
m_AgChCount(0),			//模拟通道数
m_SpanChCount(0),
m_VoipChCount(0),
m_IVRChCount(0)
{
	m_SN = g_KFPC_LicSerSN.GetSN();
}

KFPC_TSLicSer::~KFPC_TSLicSer(void)
{
	
}
