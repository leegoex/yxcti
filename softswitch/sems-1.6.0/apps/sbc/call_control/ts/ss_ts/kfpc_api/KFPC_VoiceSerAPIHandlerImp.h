#pragma once
#include "KFPC_VoiceSerAPIHandler.h"

class KFPC_VoiceSerAPIHandlerImp :
	public KFPC_VoiceSerAPIHandler
{
public:
	KFPC_VoiceSerAPIHandlerImp(void);
	~KFPC_VoiceSerAPIHandlerImp(void);
	virtual void OnEVT_API_VOICE_SERVER_INFO(KFPC_EVT_API_VOICE_SERVER_INFO* pEvt);
	static KFPC_VoiceSerAPIHandlerImp* GetInstance()
	{
		static KFPC_VoiceSerAPIHandlerImp VoiceSerAPIHandlerImpInstance;
		return &VoiceSerAPIHandlerImpInstance;
	}
};

#define  KFPCVoiceSerAPIHandlerImpInstance	KFPC_VoiceSerAPIHandlerImp::GetInstance()
