#pragma once

#include "KFPC_VoiceSer.h"
#include <unordered_map>

typedef std::unordered_map<unsigned int,KFPC_VoiceSer>		VoiceSerMap_t;
typedef VoiceSerMap_t::iterator								VoiceSerMapIter_t;
typedef std::pair<unsigned int, KFPC_VoiceSer>				VoiceSerMapPair_t;
typedef std::pair< VoiceSerMapIter_t, bool >				VoiceSerMapInsertResult_t;

class KFPC_VoiceSerMgr
{
private:
	VoiceSerMap_t	m_VoiceSerMap;
public:
	KFPC_VoiceSerMgr(void);
	~KFPC_VoiceSerMgr(void);
	static KFPC_VoiceSerMgr* GetInstance()
	{
		static KFPC_VoiceSerMgr _inStance;
		return &_inStance;
	}

	KFPC_VoiceSer* AddVoiceSer(unsigned int AppID);
	KFPC_VoiceSer* GetVoiceSer(unsigned int AppID);
	unsigned int RemoveVoiceSer(unsigned int AppID);


	KFPC_VoiceSer* GetAvailableVoiceSer( unsigned int SN = 0);
	
};
#define KFPC_VoiceSerMgrInstance KFPC_VoiceSerMgr::GetInstance()

