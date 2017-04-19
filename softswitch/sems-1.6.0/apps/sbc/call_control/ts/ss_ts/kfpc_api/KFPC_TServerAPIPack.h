#ifndef KFPC_TServerAPIPack_h__
#define KFPC_TServerAPIPack_h__

#include "kfpc_tserver_api.h"
#include "kfpc_api_handle.h"
#include "kfpc_api.h"

class KFPC_TServerAPIPack :
	public KFPC_API_Handler
{
public:

	KFPC_TServerAPIPack(void);
	virtual ~KFPC_TServerAPIPack(void);

	virtual int SendMsg(KFPC_MSG_HEADER* pMsg);

	static KFPC_TServerAPIPack* GetInstance()
	{
		static KFPC_TServerAPIPack _Instance;
		return &_Instance;
	}

	unsigned int  SendREQ_TS_GetTSVersion(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2);
	unsigned int  SendRSP_TS_GetTSVersion(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,const char *pVersion);

	unsigned int  SendREQ_TS_AcceptCall(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID);
	unsigned int  SendRSP_TS_AcceptCall(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long	CallID,unsigned int Result);

	unsigned int  SendREQ_TS_AnswerCall(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID);
	unsigned int  SendRSP_TS_AnswerCall(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long	CallID,unsigned int Result);

	unsigned int  SendREQ_TS_ReleaseCall(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int Cause);
	unsigned int  SendRSP_TS_ReleaseCall(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int Result);

	unsigned int  SendREQ_TS_CallOut(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,KFPC_DEVICE &Device,const char* InTrunkGroup="");	
	unsigned int  SendRSP_TS_CallOut(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long	CallID,unsigned int	Result,unsigned int Cause,KFPC_DEVICE* pDevice,unsigned int		SignalType);

	unsigned int  SendTS_EVT_IncomingCall(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,KFPC_DEVICE	&Device,unsigned int SignalType);
	unsigned int  SendTS_EVT_AlertCall(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int Cause);
	unsigned int  SendTS_EVT_AnsweredCall(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID);
	unsigned int  SendTS_EVT_ReleasedCall(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int Cause);


	unsigned int  SendREQ_TS_Connect(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID1,unsigned long long CallID2,unsigned int		ConnectMode,unsigned int StopMedia = 0);
	unsigned int  SendRSP_TS_Connect(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID1,unsigned long long CallID2,unsigned int Result,unsigned long long Session);

	unsigned int  SendREQ_TS_Disconnect(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID1);
	unsigned int  SendRSP_TS_Disconnect(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID1,unsigned int Result);

	unsigned int  SendREQ_TS_CreateConference(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned int NodeID,unsigned int MaxMember,unsigned int TserID, unsigned int CCSID);
	unsigned int  SendRSP_TS_CreateConference(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long ConfID,unsigned int CCSID,unsigned int Result);

	unsigned int  SendREQ_TS_FreeConference(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long ConfID);
	unsigned int  SendRSP_TS_FreeConference(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long ConfID,unsigned int Result);

	unsigned int  SendREQ_TS_JoinConference(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned long long ConfID,unsigned int JoinMode,int	DTMFSilence,unsigned int	StopMedia = 0);
	unsigned int  SendRSP_TS_JoinConference(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned long long ConfID,unsigned int Result,unsigned long long Session);

	unsigned int  SendREQ_TS_LeaveConference(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned long long ConfID);
	unsigned int  SendRSP_TS_LeaveConference(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned long long ConfID,unsigned int Result);

	unsigned int  SendREQ_TS_ChangeConnectMode(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int ConnectMode);
	unsigned int  SendRSP_TS_ChangeConnectMode(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int Result);

	unsigned int  SendREQ_TS_CollectDTMF(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,KFPC_DTMFParam &DTMFParam, unsigned int MixCollect);
	unsigned int  SendRSP_TS_CollectDTMF(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int Result);

	unsigned int  SendREQ_TS_StopCollectDTMF(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID);
	unsigned int  SendRSP_TS_StopCollectDTMF(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int Result);

	unsigned int  SendTS_EVT_CollectDTMFCompleted(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int DTMFCount,const char * pDTMF,unsigned int Result);

	unsigned int  SendREQ_TS_PlayVoice(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,KFPC_DTMFParam &DTMFParam,const char * pPlayContent,unsigned int MixRecord);
	unsigned int  SendRSP_TS_PlayVoice(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int Result);

	unsigned int  SendREQ_TS_StopPlayVoice(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int CollectDTMF);
	unsigned int  SendRSP_TS_StopPlayVoice(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int Result);

	unsigned int  SendTS_EVT_PlayVoiceCompleted(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID);

	unsigned int  SendREQ_TS_RecordFile(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int TermChar,const char *pFileName,unsigned int RecordTime,unsigned int MixRecord);
	unsigned int  SendRSP_TS_RecordFile(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int Result);

	unsigned int  SendREQ_TS_StopRecordFile(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID);
	unsigned int  SendRSP_TS_StopRecordFile(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int Result);

	unsigned int  SendTS_EVT_RecordFileCompleted(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID);

	/*unsigned int  SendREQ_TS_ConfPlayVoice(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long ConfID,char *pPlayContent);
	unsigned int  SendRSP_TS_ConfPlayVoice(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long ConfID,unsigned int Result);

	unsigned int  SendREQ_TS_ConfStopPlayVoice(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long ConfID);
	unsigned int  SendRSP_TS_ConfStopPlayVoice(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long ConfID,unsigned int Result);

	unsigned int  SendTS_EVT_ConfPlayVoiceCompleted(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long ConfID);

	unsigned int  SendREQ_TS_ConfStartRecordFile(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long ConfID,char *pFileName,unsigned int RecordTime);
	unsigned int  SendRSP_TS_ConfStartRecordFile(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long ConfID,unsigned int Result);

	unsigned int  SendREQ_TS_ConfStopRecordFile(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long ConfID);
	unsigned int  SendRSP_TS_ConfStopRecordFile(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long ConfID,unsigned int Result);

	unsigned int  SendTS_EVT_ConfRecordFileCompleted(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long ConfID);*/

	unsigned int  SendREQ_TS_RecvFax(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,const char *pFileName);
	unsigned int  SendRSP_TS_RecvFax(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int Result);

	unsigned int  SendREQ_TS_StopReceiveFax(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID);
	unsigned int  SendRSP_TS_StopReceiveFax(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int Result);

	unsigned int  SendTS_EVT_ReceiveFaxCompleted(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int PageCount,unsigned int Result);

	unsigned int  SendREQ_TS_StartSendFax(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,const char *pFileName,const char *pSenderIdent,
														  const char *pSubAddress,const char *pPageHeaderInfo,const char *pIdentifier);
	unsigned int  SendRSP_TS_StartSendFax(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int Result);

	unsigned int  SendREQ_TS_StopSendFax(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID);
	unsigned int  SendRSP_TS_StopSendFax(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int Result);

	unsigned int  SendTS_EVT_SendFaxCompleted(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int PageCount,unsigned int Result);

	unsigned int  SendREQ_TS_ReloadConfig(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2);
	unsigned int  SendRSP_TS_ReloadConfig(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned int Result);

	unsigned int  SendREQ_TS_QueryChStatus(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2);
	unsigned int  SendRSP_TS_QueryChStatus(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned int Result);

	unsigned int  SendTS_EVT_UpdateChStatus(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned int ChannelCount,unsigned int* Channel,unsigned int* State);

	unsigned int  SendREQ_TS_SetChState(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned int ChannelCount,unsigned int* Channel,unsigned int* State);
	unsigned int  SendRSP_TS_SetChState(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned int Result);

	unsigned int  SendREQ_TS_CoreDump(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2);
	unsigned int  SendRSP_TS_CoreDump(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned int Result);

	unsigned int  SendTS_EVT_AlarmEvent(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned int AlarmID,char *pAlarmContent);

	unsigned int  SendREQ_TS_WatchTrunkGroup(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,char* pTrunkGroup);
	unsigned int  SendRSP_TS_WatchTrunkGroup(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,char* pTrunkGroup,unsigned int Result);

	unsigned int  SendREQ_TS_CancelWatchTrunkGroup(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,char* pTrunkGroup);
	unsigned int  SendRSP_TS_CancelWatchTrunkGroup(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,char* pTrunkGroup,unsigned int Result);

	unsigned int  SendREQ_TS_QueryTrunkGroup(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2);
	unsigned int  SendRSP_TS_QueryTrunkGroup(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned int Result);

	unsigned int  SendTS_EVT_UpdateTrunkGroup(unsigned int	DstAPPId,char* pTrunkGroup);

	unsigned int  SendREQ_TS_PlayDTMF(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,char *pDTMF);
	unsigned int  SendRSP_TS_PlayDTMF(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID,unsigned int Result);
	unsigned int  SendTS_EVT_HookFlash(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID);
	unsigned int  SendTS_EVT_ExtNum2CCS(unsigned int DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned int Flag,const char* ExtNum,unsigned int CCS);
	unsigned int  SendTS_EVT_PassAnswerCall(unsigned int	DstAPPId,unsigned int	UserContext1,unsigned int	UserContext2,unsigned long long CallID);


private:
	KFPC_LIB_PARAMS* m_pLibParam;
};

#define KFPC_TSERVERAPI_INSTANCE	KFPC_TServerAPIPack::GetInstance()
#endif // KFPC_TServerAPIPack_h__
