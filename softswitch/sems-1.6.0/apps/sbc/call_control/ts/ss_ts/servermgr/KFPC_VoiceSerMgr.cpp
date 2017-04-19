#include "kfpc_logex.h"
#include "KFPC_VoiceSerMgr.h"


KFPC_VoiceSerMgr::KFPC_VoiceSerMgr(void)
{
}


KFPC_VoiceSerMgr::~KFPC_VoiceSerMgr(void)
{
}

KFPC_VoiceSer* KFPC_VoiceSerMgr::AddVoiceSer( unsigned int AppID )
{
	KFPC_VoiceSer	VoiceSer;
	VoiceSerMapInsertResult_t Ret = m_VoiceSerMap.insert(VoiceSerMapPair_t(AppID,VoiceSer));
	
	Ret.first->second.SetAPPID(AppID);
	INFO_LOG(0,"AppID:%u,Result:%d,VoiceSerMap size:%d",AppID,Ret.second,m_VoiceSerMap.size());
	return &Ret.first->second;
}

KFPC_VoiceSer* KFPC_VoiceSerMgr::GetVoiceSer( unsigned int AppID )
{
	VoiceSerMapIter_t	Iter = m_VoiceSerMap.find(AppID);

	if(Iter != m_VoiceSerMap.end())
	{
		return &Iter->second;
	}
	else
	{
		return NULL;
	}
}

unsigned int KFPC_VoiceSerMgr::RemoveVoiceSer( unsigned int AppID )
{
	unsigned int Ret = m_VoiceSerMap.erase(AppID);

	INFO_LOG(0,"AppID:%u,Result:%d,VoiceSerMap size:%d",AppID,Ret,m_VoiceSerMap.size());
	return Ret;
}

KFPC_VoiceSer* KFPC_VoiceSerMgr::GetAvailableVoiceSer( unsigned int SN /*= 0*/ )
{
	if(m_VoiceSerMap.empty())
	{
		return NULL;
	}

	if(SN == 0)
	{
		return &m_VoiceSerMap.begin()->second;
	}
	else
	{
		VoiceSerMapIter_t	BeginIter = m_VoiceSerMap.begin();
		//VoiceSerMapIter_t	EndIter = m_VoiceSerMap.end();

		for(;BeginIter != m_VoiceSerMap.end();BeginIter ++)
		{
			if(BeginIter->second.GetSN() > SN)
			{
				return &BeginIter->second;
			}
		}

		return NULL;
	}
}