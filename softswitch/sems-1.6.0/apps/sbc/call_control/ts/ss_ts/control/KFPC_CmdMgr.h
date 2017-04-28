#pragma once
#include "kfpc_mempool.h"
#include "KFPC_BaseCmdMgr.h"
#include "KFPC_Channel.h"

#include "KFPC_Cmd_EVT_IncomingCall.h"
//#include "KFPC_Cmd_EH_StopPlay.h"
//#include "KFPC_Cmd_EH_StopRecord.h"
//#include "KFPC_Cmd_EH_Disconnect.h"
//#include "KFPC_CmdSet_TS_ReleaseCall.h"
//#include "KFPC_Cmd_EH_ReleaseCall.h"
//#include "KFPC_Cmd_EH_AnswerCall.h"
//#include "KFPC_Cmd_EH_ChannelInit.h"
//#include "KFPC_Cmd_EH_Callout.h"
//#include "KFPC_CmdSet_TS_EVT_ReleasedCall.h"
//#include "KFPC_Cmd_EH_PlayVoice.h"
//#include "KFPC_Cmd_EH_ConnectToIVR.h"
//#include "KFPC_CmdSet_TS_PlayVoice.h"
//#include "KFPC_Cmd_EH_EVT_PlayVoiceCompleted.h"

//#include "KFPC_Cmd_EH_EVT_AnsweredCall.h"
//#include "KFPC_Cmd_EH_EVT_DigitCollected.h"
//#include "KFPC_Cmd_EH_CollectDTMF.h"
//#include "KFPC_CmdSet_TS_CollectDTMF.h"
//#include "KFPC_Cmd_EH_FreeConference.h"
//#include "KFPC_Cmd_EH_CreateConference.h"
//#include "KFPC_Cmd_EH_StopCollectDTMF.h"
//#include "KFPC_Cmd_EH_RecordFile.h"
//#include "KFPC_CmdSet_TS_RecordFile.h"
//#include "KFPC_Cmd_EH_EVT_RecordCompleted.h"
//#include "KFPC_Cmd_EH_JoinConference.h"
//#include "KFPC_Cmd_EH_LeaveConference.h"
//#include "KFPC_CmdSet_TS_StopPlayVoice.h"
//#include "KFPC_Cmd_EH_ConnectToCh.h"
//#include "KFPC_Cmd_EH_Create3PartyConf.h"
//#include "KFPC_CmdSet_TS_MixRecordFile.h"
//#include "KFPC_CmdSet_TS_StartSendFax.h"
//#include "KFPC_Cmd_TS_StartSendFax.h"
//#include "KFPC_Cmd_TS_StopSendFax.h"
//#include "KFPC_CmdSet_TS_Connect.h"
//#include "KFPC_Cmd_EH_DisconnectMixIVR.h"
//#include "KFPC_Cmd_EH_Free3PartyConf.h"
//#include "KFPC_Cmd_EH_AcceptCall.h"
//#include "KFPC_Cmd_EH_StartMedia.h"
//#include "KFPC_CmdSet_TS_JoinConf.h"
//#include "KFPC_Cmd_EH_ChangeConnectMode.h"
//#include "KFPC_CmdSet_TS_StartRecvFax.h"
//#include "KFPC_Cmd_TS_StartRecvFax.h"
//#include "KFPC_CmdSet_TS_FreeConf.h"
//#include "KFPC_CmdSet_TS_MixPlayVoice.h"
//#include "KFPC_Cmd_EH_TextToSpeech.h"
//#include "KFPC_Cmd_EH_ConnectToFAX.h"
//#include "KFPC_Cmd_EH_Voice2Fax.h"
//#include "KFPC_Cmd_TS_StopReceiveFax.h"
//#include "KFPC_CmdSet_TS_MixCollectDTMF.h"
//#include "KFPC_CmdSet_TS_PlayDTMF.h"
//#include "KFPC_Cmd_EH_PlayDTMF.h"
//#include "KFPC_Cmd_EH_Evt_HookFlash.h"
//#include "KFPC_Cmd_EH_StopMedia.h"
//#include "KFPC_Cmd_EH_Timer.h"

#ifdef MSML
#include "KFPC_CmdSet_MSML_CreateConf.h"
#include "KFPC_CmdSet_MSML_JoinConf.h"
#include "KFPC_CmdSet_MSML_Modifystream.h"
#endif // MSML


#ifdef TSERVER_GL
#include "TS_Cmd_AcceptCall.h"
#include "TS_Cmd_AnswerCall.h"
#include "tserver.api.h"
#include "tserver_api_appand1.h"
#include "TS_Cmd_ClearCall.h"
#include "TS_Cmd_ClearConnect.h"
#include "TS_Cmd_AlternateCall.h"
#include "TS_Cmd_RequestRouter.h"
#include "TS_Cmd_SetupOnePartCallEx.h"
#include "TS_Cmd_DeflectCallEx2.h"
#include "TS_Cmd_PlayVoice.h"
#include "TS_Cmd_GatherDigits.h"
#include "TS_Cmd_StopPlayVoice.h"
#include "TS_Cmd_MixPlayVoice.h"
#include "TS_Cmd_MixGatherDigits.h"
#endif



class KFPC_CmdMgr:public KFPC_BaseCmdMgr
{

public:
	
	//KFPC_MemPool* GetKFPC_MemPool() { return &m_KFPC_MemPool; }

	static KFPC_CmdMgr*  GetInstance()
	{
		static KFPC_CmdMgr	_Instance;
		return &_Instance;
	}

	KFPC_CmdMgr(void);
	~KFPC_CmdMgr(void);


	EH_Cmd_EVT_IncomingCall* Create_Cmd_EVT_IncomingCall(KFPC_Channel* pCh);

//	KFPC_Cmd_StopRecord* Create_Cmd_StopRecord(KFPC_Channel* pCh,
//		unsigned int AppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//
//	KFPC_Cmd_Disconnect* Create_Cmd_Disconnect( KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false,
//		bool MonitorIVR = false);
//
//	KFPC_CmdSet_ReleaseCall* Create_CmdSet_ReleaseCall(KFPC_Channel* pCh,unsigned int Cause,unsigned int AppID,unsigned int UserContext1,unsigned int UserContext2);
//
//	KFPC_Cmd_ReleaseCall* Create_Cmd_ReleaseCall(KFPC_Channel* pCh,
//		unsigned int Cause,
//		unsigned int AppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,bool SubCmd);
//
//	KFPC_Cmd_AnswerCall* Create_Cmd_AnswerCall(KFPC_Channel* pCh,
//		unsigned int AppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2);
//
//	KFPC_Cmd_Callout* Create_Cmd_Callout(KFPC_DEVICE& Device,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//
//
//	KFPC_Cmd_ChannelInit* Create_Cmd_ChannelInit(KFPC_Channel* pCh,unsigned short Cause, bool SubCmd = false);
//
//	KFPC_CmdSet_EVT_ReleasedCall*	Create_CmdSet_EVT_ReleasedCall(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2, 
//		unsigned int Cause);
//
//	KFPC_Cmd_PlayVoice* Create_Cmd_PlayVoice(KFPC_Channel* pCh,
//		unsigned int AppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2, 
//		char* VoiceFile, 
//		KFPC_DTMFParam* pDTMFPara,
//		bool SubCmd = false);
//
//	KFPC_Cmd_ConnectToIVR* Create_Cmd_ConnectToIVR(KFPC_Channel* pCh,
//		unsigned int AppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool	MonitorIVR = false);
//
//	KFPC_CmdSet_PlayVoice* Create_CmdSet_PlayVoice(KFPC_Channel* pCh, 
//		char* VoiceFile,
//		KFPC_DTMFParam* pDTMFPara,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//
//	KFPC_CmdSet_MixPlayVoice* Create_CmdSet_MixPlayVoice(KFPC_Channel* pCh, 
//		char* VoiceFile,
//		KFPC_DTMFParam* pDTMFPara,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//
//	KFPC_Cmd_EVT_PlayVoiceCompleted* Create_Cmd_EVT_PlayVoiceCompleted(KFPC_Channel* pCh,
//		unsigned int AppID,
//		unsigned int UserContext1, 
//		unsigned int UserContext2);
//
//	KFPC_Cmd_EH_Evt_AnsweredCall*	Create_Cmd_EH_Evt_AnsweredCall(KFPC_Channel* pCh);
//
//	KFPC_Cmd_EVT_DigitCollected*    Create_Cmd_EH_Evt_DigitCollected(KFPC_Channel* pCh, 
//		unsigned int AppID,
//		unsigned int UserContext1, 
//		unsigned int UserContext2,
//		unsigned int DigitCount, 
//		char* pDigits);
//	
//	KFPC_Cmd_StopPlay* Create_Cmd_StopPlay(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
///*
//	KFPC_CmdSet_StopMixPlay* Create_CmdSet_StopMixPlay(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//*/
//	KFPC_Cmd_CollectDTMF* Create_Cmd_CollectDTMF(KFPC_Channel* pCh,
//		unsigned int DstAppID, 
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		KFPC_DTMFParam* pDTMFPara,
//		bool SubCmd = false);
//
//	KFPC_CmdSet_CollectDTMF* Create_CmdSet_CollectDTMF(KFPC_Channel* pCh, 
//		KFPC_DTMFParam* pDTMFPara,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//
//	KFPC_Cmd_EH_CreateConference* Create_Cmd_EH_CreateConference( unsigned int& CCSID,
//		unsigned int&	MaxMember,
//		unsigned int&	NodeID,
//		unsigned int& DstAppID,
//		unsigned int& UserContext1,
//		unsigned int& UserContext2,
//		bool SubCmd = false);
//
//	KFPC_Cmd_EH_FreeConference* Create_Cmd_EH_FreeConference(KFPC_Channel* pCh,
//		unsigned int& DstAppID,
//		unsigned int& UserContext1,
//		unsigned int& UserContext2,
//		bool SubCmd = false);
//
//	KFPC_Cmd_StopCollectDTMF* Create_Cmd_StopCollectDTMF(KFPC_Channel* pCh,
//		unsigned int DstAppID, 
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//
//	KFPC_Cmd_RecordFile* Create_Cmd_RecordFile(KFPC_Channel* pCh,
//		unsigned int AppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2, 
//		const char* RecordFile,
//		int RecordTime, 
//		unsigned int TermChar,
//		bool SubCmd = false);
//
//	KFPC_Cmd_TextToSpeech*	Create_Cmd_TextToSpeech(KFPC_Channel* pCh,
//		unsigned int DstAppID, 
//		char *pPlayContent,
//		unsigned int& UserContext1, 
//		unsigned int& UserContext2,bool SubCmd = false);
//
//	KFPC_CmdSet_RecordFile* Create_CmdSet_RecordFile(KFPC_Channel* pCh,
//		char* RecordFile,
//		int RecordTime,
//		unsigned int TermChar,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//	KFPC_CmdSet_MixRecordFile* Create_CmdSet_MixRecordFile(KFPC_Channel* pCh,
//		char* RecordFile,
//		int RecordTime,
//		unsigned int TermChar,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		unsigned int MixRecord,
//		bool SubCmd = false);
//	KFPC_Cmd_EVT_RecordFileCompleted* Create_Cmd_EVT_RecordFileCompleted(KFPC_Channel* pCh,
//		unsigned int AppID,
//		unsigned int UserContext1, 
//		unsigned int UserContext2,
//		const char* pFileName,
//		bool TransformMp3,
//		bool SubCmd = false);
//
//	KFPC_Cmd_EH_JoinConference*	Create_Cmd_JoinConf(KFPC_Channel* pCh,
//													KFPC_Channel* pConfCh,
//													unsigned int JoinMode,
//													int			DTMFSilence,
//													unsigned int AppID,
//													unsigned int UserContext1, 
//													unsigned int UserContext2,
//													bool SubCmd = false
//													);
//
//	KFPC_Cmd_EH_LeaveConference*	Create_Cmd_LeaveConf(KFPC_Channel* pCh,
//		KFPC_Channel* pConfCh,
//		unsigned int AppID,
//		unsigned int UserContext1, 
//		unsigned int UserContext2,
//		bool SubCmd = false
//		);
//	KFPC_CmdSet_StopPlayVoice* Create_CmdSet_StopPlayVoice(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//
//	KFPC_EH_ConnectToCh* Create_Cmd_ConnectToCh(KFPC_Channel* pCh,
//		KFPC_Channel* pCh2,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		unsigned char ConnectMode,
//		bool SubCmd = false);
//
//	KFPC_Cmd_Create3PartyConf* Create_Cmd_Setup3PartyConf(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//
//	KFPC_Cmd_TS_StartSendFax* Create_Cmd_StartSendFax(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		const char *pFileName,
//		const char *pSenderIdent,
//		const char *pSubAddress,
//		const char *pPageHeaderInfo,
//		const char *pIdentifier,
//		bool SubCmd = false);
//
//	KFPC_Cmd_EH_StartFaxMedia* Create_Cmd_StartFaxMedia(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//
//	KFPC_Cmd_TS_StopSendFax* Create_Cmd_StopSendFax(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//
//	KFPC_Cmd_TS_StartRecvFax* Create_Cmd_StartRecvFax(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		char* FaxFileName,
//		bool SubCmd = false);
//
//	KFPC_CmdSet_TS_Connect* Create_CmdSet_TS_Connect(KFPC_Channel* pCh,
//		KFPC_Channel* pCh2,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		unsigned char ConnectMode,
//		unsigned int	StopMedia);
//
//	KFPC_Cmd_DisconnectMixIVR* Create_Cmd_DisconnectMixIVR(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//
//	KFPC_Cmd_Free3PartyConf* Create_Cmd_Free3PartyConf(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//
//	KFPC_CmdSet_TS_StartSendFax* Create_CmdSet_StartSendFax(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		const char *pFileName,
//		const char *pSenderIdent,
//		const char *pSubAddress,
//		const char *pPageHeaderInfo,
//		const char *pIdentifier,
//		bool SubCmd = false);
//
//	KFPC_CmdSet_TS_StartRecvFax* Create_CmdSet_StartRecvFax(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		char* FaxFileName,
//		bool SubCmd = false);
//
//
//	KFPC_Cmd_AcceptCall* Create_Cmd_AcceptCall(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//
//	KFPC_CmdSet_TS_JoinConf* Create_CmdSet_TS_JoinConf(
//		KFPC_Channel* pCh,
//		KFPC_Channel* pConfCh,
//		unsigned int JoinMode,
//		int			DTMFSilence,
//		unsigned int AppID,
//		unsigned int UserContext1, 
//		unsigned int UserContext2,
//		unsigned int StopMedia);
//	KFPC_Cmd_EH_ChangeConnectMode* Create_Cmd_EH_ChangeConnectMode(
//		KFPC_Channel* pCh,
//		unsigned int ConnectMode, 
//		unsigned int& DstAppID,
//		unsigned int& UserContext1,
//		unsigned int& UserContext2,
//		bool SubCmd = false
//		);
//	KFPC_CmdSet_TS_FreeConf*	Create_CmdSet_FreeConf(KFPC_Channel* pCh,
//		unsigned int DstAppID, 
//		unsigned int UserContext1, 
//		unsigned int UserContext2);
//
//	KFPC_Cmd_EH_ConnectToFAX*	Create_Cmd_EH_ConnectToFAX(KFPC_Channel* pCh,
//		unsigned int AppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2);
//	KFPC_Cmd_EH_Voice2Fax*	Create_Cmd_EH_Voice2Fax(KFPC_Channel* pCh,
//		unsigned int AppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2);
//	KFPC_Cmd_TS_StopReceiveFax* Create_Cmd_StopReceiveFax(KFPC_Channel* pCh,
//		unsigned int AppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false
//		);
//	KFPC_CmdSet_MixCollectDTMF* Create_CmdSet_MixCollect(KFPC_Channel* pCh,
//		KFPC_DTMFParam* pDTMFPara,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//	KFPC_Cmd_PlayDTMF*  Create_Cmd_PlayDTMF(KFPC_Channel* pCh,
//		char* pDTMF,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//	KFPC_CmdSet_PlayDTMF* Create_CmdSet_PlayDTMF(KFPC_Channel* pCh,
//		char* pDTMF,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//	KFPC_Cmd_EH_Evt_HookFlash* Create_Cmd_EH_Evt_HookFlash(KFPC_Channel* pCh);
//
//	KFPC_Cmd_TS_RequestFaxCh*	Create_Cmd_TS_RequestFaxCh(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//
//	KFPC_Cmd_EH_StopMedia*	Create_Cmd_EH_StopMedia(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		bool SubCmd = false);
//
//	KFPC_Cmd_EH_Timer*	Create_Cmd_EH_Timer(KFPC_Channel* pCh,
//		unsigned int DstAppID,
//		unsigned int UserContext1,
//		unsigned int UserContext2,
//		unsigned int TimeOut,
//		bool SubCmd = false);

#ifdef MSML	
	KFPC_CmdSet_MSML_CreateConf*	Create_CmdSet_MSML_CreateConf(
		KFPC_Channel* pCh, 
		const char*		Name,
		MSML_DeleteWhen	MSML_DeleteWhen,
		unsigned int	Mix_N_Loudest,		//最大发言人数
		unsigned int	Mix_Asn_Ri,			//minimum reporting interval
		unsigned int SerialNo);

	KFPC_CmdSet_MSML_JoinConf*	Create_CmdSet_MSML_JoinConf(
		KFPC_Channel* pCh, 
		KFPC_Channel* pConf,
		unsigned int JoinMode, 
		int DTMFSilence,
		unsigned int StopMedia,
		unsigned int SerialNo);

	KFPC_CmdSet_MSML_Modifystream*	Create_CmdSet_MSML_Modifystream(KFPC_Channel* pCh,unsigned int JoinMode,unsigned int SerialNo);
#endif // MSML


#ifdef TSERVER_GL
	TS_Cmd_AcceptCall*	Create_Cmd_TS_Cmd_AcceptCall(KFPC_Channel* pCh,	unsigned int AppID, unsigned int Tag,bool SubCmd);
	TS_Cmd_AnswerCall*	Create_Cmd_TS_Cmd_AnswerCall(KFPC_Channel* pCh,	unsigned int AppID,TS_AnswerCall *pAnswerCall);
	TS_Cmd_ClearCall*	Create_Cmd_TS_Cmd_ClearCall(KFPC_Channel* pCh,TS_ClearCall *pClearCall);
	TS_Cmd_ClearConnect* Create_Cmd_TS_Cmd_ClearConnect(KFPC_Channel* pCh,TS_ClearConnection *pClearConnection);
	TS_Cmd_AlternateCall*	Create_Cmd_TS_Cmd_AlternateCall(KFPC_Channel* pCh,KFPC_Channel* pCh2,unsigned int Tag,unsigned int DstApp);
	TS_Cmd_RequestRouter*	Create_Cmd_TS_Cmd_RequestRouter(
		unsigned int RouteAppID,
		unsigned char USerType,
		const char*  GroupName,
		const char*  CallingNum,
		const char*  CountryCode,
		const char*  Destination,
		unsigned char  OutRouterMethod,
		TS_RouteResult*	pRouteResult,
		KFPC_DEVICE*	pDevice,
		bool SubCmd = false);

	TS_Cmd_SetupOnePartCallEx*	Create_Cmd_TS_Cmd_SetupOnePartCallEx(
		TS_SetupOnePartCallEx* pSetupOnePartCallEx
		);

	TS_Cmd_DeflectCallEx2*	Create_Cmd_TS_Cmd_DeflectCallEx2(
		TS_DeflectCallEx2* pDeflectCallEx2,
		unsigned long long	ConToBeDiverted
		);

	TS_Cmd_PlayVoice*	Create_Cmd_TS_Cmd_PlayVoice(KFPC_Channel* pCh,unsigned int DstAppID,const char* VoiceFile,unsigned int PlayApiFlag);

	TS_Cmd_GatherDigits*	Create_Cmd_TS_Cmd_GatherDigits(KFPC_Channel* pCh,TS_GatherDigits *pGatherDigits);
	TS_Cmd_MixGatherDigits*	Create_Cmd_TS_Cmd_MixGatherDigits(KFPC_Channel* pCh,TS_GatherDigits *pGatherDigits);

	TS_Cmd_StopPlayVoice*	Create_Cmd_TS_Cmd_StopPlayVoice(KFPC_Channel* pCh,TS_StopPlayVoice *pStopPlayVoice);

	TS_Cmd_MixPlayVoice*	Create_Cmd_TS_Cmd_MixPlayVoice(KFPC_Channel* pCh,unsigned int DstAppID,const char* VoiceFile,unsigned int PlayApiFlag);

#endif

public:
	void ExecuteCmd(KFPC_Channel* pCh, KFPC_BaseCommand* pCmd );
	void CancelCmd(KFPC_Channel* pCh, KFPC_BaseCommand* pCmd );

	//void DoREQ_TS_AnswerCall(KFPC_Channel* pCh,KFPC_REQ_TS_AnswerCall* pMsg);
	//void DoREQ_TS_ReleaseCall(KFPC_Channel* pCh,KFPC_REQ_TS_ReleaseCall* pMsg);
	//void DoREQ_TS_CallOut(KFPC_REQ_TS_CallOut* pMsg);
	//void DoREQ_TS_Disconnect(KFPC_Channel* pCh,KFPC_REQ_TS_Disconnect* pMsg);
	//void DoREQ_TS_CreateConference(KFPC_REQ_TS_CreateConference* pMsg);
	//void DoREQ_TS_PlayVoice(KFPC_Channel* pCh,KFPC_REQ_TS_PlayVoice* pMsg);
	//void DoREQ_TS_StopPlayVoice(KFPC_Channel* pCh,KFPC_REQ_TS_StopPlayVoice* pMsg);
	//void DoREQ_TS_CollectDTMF(KFPC_Channel* pCh,KFPC_REQ_TS_CollectDTMF* pMsg);
	//void DoREQ_TS_FreeConference(KFPC_Channel* pCh,KFPC_REQ_TS_FreeConference* pMsg);
	//void DoREQ_TS_StopCollectDTMF(KFPC_Channel* pCh,KFPC_REQ_TS_StopCollectDTMF* pMsg);
	//void DoREQ_TS_RecordFile(KFPC_Channel* pCh,KFPC_REQ_TS_StartRecordFile* pMsg);
	//void DoREQ_TS_StopRecordFile(KFPC_Channel* pCh,KFPC_REQ_TS_StopRecordFile* pMsg);
	//void DoREQ_TS_JoinConference(KFPC_Channel* pCh,KFPC_Channel* pConfCh,KFPC_REQ_TS_JoinConference* pMsg);
	//void DoREQ_TS_LeaveConference(KFPC_Channel* pCh,KFPC_Channel* pConfCh,KFPC_REQ_TS_LeaveConference* pMsg);
	//void DoREQ_TS_Connect(KFPC_Channel* pCh,KFPC_Channel* pCh2,KFPC_REQ_TS_Connect* pMsg);
	//void DoREQ_TS_StartSendFax(KFPC_Channel* pCh,KFPC_REQ_TS_StartSendFax* pMsg);
	//void DoREQ_TS_StartRecvFax(KFPC_Channel* pCh,KFPC_REQ_TS_RecvFax* pMsg);
	//void DoREQ_TS_StopSendFax(KFPC_Channel* pCh,KFPC_REQ_TS_StopSendFax* pMsg);
	//void DoREQ_TS_AcceptCall(KFPC_Channel* pCh,KFPC_REQ_TS_AcceptCall* pMsg);
	//void DoREQ_TS_ChangeConnectMode(KFPC_Channel* pCh,KFPC_REQ_TS_ChangeConnectMode* pMsg);
	//void DoREQ_TS_StopReceiveFax(KFPC_Channel* pCh,KFPC_REQ_TS_StopReceiveFax* pMsg);
	//void DoREQ_TS_PlayDTMF(KFPC_Channel* pCh,KFPC_REQ_TS_PlayDTMF* pMsg);

	unsigned int ExecuteRspCmd( KFPC_BaseCommand* pCmd,unsigned int MsgID );

};

#define KFPC_CmdMgrInstance		KFPC_CmdMgr::GetInstance()
