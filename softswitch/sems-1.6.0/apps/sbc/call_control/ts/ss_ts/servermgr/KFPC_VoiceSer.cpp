
#include "KFPC_VoiceSer.h"
#include "kfpc_sn32.h"

static KFPC_SN32	g_KFPC_TTSSerSN;

KFPC_VoiceSer::KFPC_VoiceSer(void):
m_APPID(0),
m_SN(0),
m_PRDID(0)
{
	m_SN = g_KFPC_TTSSerSN.GetSN();

}


KFPC_VoiceSer::~KFPC_VoiceSer(void)
{
}
