#ifndef KFPC_VoiceSerAPIHandler_h__
#define KFPC_VoiceSerAPIHandler_h__


#include "kfpc_api_handle.h"
#include "kfpc_voiceser_api.h"

class KFPC_VoiceSerAPIHandler :
	public KFPC_API_Handler
{

private:

	void RecvVOICE_FILE_COMPRESS(KFPC_MSG_HEADER* pMsg);	
	void RecvVOICE_EVT_SERVER_INFO(KFPC_MSG_HEADER* pMsg);	
public:
	virtual void RecvMsg(KFPC_MSG_HEADER* pMsg);
	virtual int SendMsg(KFPC_MSG_HEADER* pMsg);


	virtual void OnREQ_API_VOICE_FILE_COMPRESS(KFPC_REQ_API_VOICE_FILE_COMPRESS* pMsg){};
	virtual void OnRSP_API_VOICE_FILE_COMPRESS(KFPC_RSP_API_VOICE_FILE_COMPRESS* pMsg){};
	virtual void OnEVT_API_VOICE_SERVER_INFO(KFPC_EVT_API_VOICE_SERVER_INFO* pEvt){}

	void SendREQ_API_VOICE_FILE_COMPRESS(unsigned long long CallID,unsigned int DestAppID,const char *OrgFileName,const char *DstFileName);
	void SendRSP_API_VOICE_FILE_COMPRESS(unsigned long long CallID,unsigned int DestAppID,unsigned int Result);

	void SendEVT_API_VOICE_SERVER_INFO(unsigned int DestAppID,unsigned int PRDID);
	KFPC_VoiceSerAPIHandler(void);
	virtual ~KFPC_VoiceSerAPIHandler(void);
};

#endif // KFPC_VoiceSerAPIHandler_h__
