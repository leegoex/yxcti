#include "KFPC_VoiceSerAPIHandlerImp.h"
#include "KFPC_VoiceSerMgr.h"

KFPC_VoiceSerAPIHandlerImp::KFPC_VoiceSerAPIHandlerImp(void)
{
}


KFPC_VoiceSerAPIHandlerImp::~KFPC_VoiceSerAPIHandlerImp(void)
{
}

void KFPC_VoiceSerAPIHandlerImp::OnEVT_API_VOICE_SERVER_INFO( KFPC_EVT_API_VOICE_SERVER_INFO* pEvt )
{
	KFPC_VoiceSer* pVoiceSer = KFPC_VoiceSerMgrInstance->GetVoiceSer(pEvt->Header.un32SrcAPPId);

	if(pVoiceSer != NULL)
	{
		pVoiceSer->SetPRDID(pEvt->PRDID);
	}
}