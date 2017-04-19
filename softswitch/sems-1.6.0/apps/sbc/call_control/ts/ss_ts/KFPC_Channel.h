#pragma once

#include "KFPC_TServerDef.h"
#include "KFPC_BaseCommand.h"
#include "kfpc_sn32.h"
#include "KFPC_ChRes.h"

//#include "KFPC_TrunkGroup.h"

//class KFPC_TrunkGroup;
//class KFPC_SIP_Addr;

class KFPC_Channel:public KFPC_ChRes
{
private:
	unsigned int		m_UniqueID;
	unsigned char		m_InsertDB;
	unsigned short		m_ID;								/**< 通道ID */
	KFPC_Ch_Status		m_Status;							/**< 通道状态 */
	//KFPC_SignalType		m_SignalType;						/**< 信令类型 */
	//KFPC_CH_TYPE		m_ChType;
	
	KFPC_ConnectionType	m_ConType;						/**< 连接类型 */
	unsigned long long	m_SessionCallID;
	//KFPC_CH_IVRType_t	m_IVRType;						/**< IVR资源类型 */
	//unsigned char		m_IVRChListCount;					/**< IVR通道数 */
	
	unsigned int		m_CmdID;							/**< 当前正在执行CMD  ID  */
	KFPC_CmdIDList		m_CmdIDQueue;						/**< 命令列表 */
	unsigned long long	m_CallID;						/**< Call ID */
	KFPC_DEVICE			m_Device;
	unsigned int		m_DstAppID;			/**< 对端AppID */

	unsigned int		m_RouterTimerID;

	unsigned int		m_Cause;						//释放原因值
	bool				m_RemoteRelease;				//远端挂机
	KFPC_CALL_FLAG		m_CallFlag;
	unsigned int		m_FreeConfTimer;		//释放会议定时器

	time_t				m_InitTime;
	time_t				m_AnswerTime;
	time_t				m_ConnectTime;
	time_t				m_ReleaseTime;
	bool				m_ConfCreator;
	string				m_FromIp;
protected:
	void SetID(unsigned short val) { m_ID = val; }
public:	

	time_t GetConnectTime() const { return m_ConnectTime; }
	void SetConnectTime(time_t val) { m_ConnectTime = val; }


	unsigned long long GetSessionCallID()  { return m_SessionCallID; }
	void SetSessionCallID();
	void SetSessionCallID(unsigned long long val);
	
	unsigned int GetFreeConfTimer()  { return m_FreeConfTimer; }
	void SetFreeConfTimer(unsigned int val) { m_FreeConfTimer = val; }

	unsigned int GetUniqueID()  { return m_UniqueID; }
	void SetUniqueID();


	KFPC_CALL_FLAG GetCallFlag() const { return m_CallFlag; }
	void SetCallFlag(KFPC_CALL_FLAG val) { m_CallFlag = val; }

	void AppendMoreInfo(const char* val);
	void AppendMoreInfo2Called(const char* val);
	unsigned int GetCause() const { return m_Cause; }
	void SetCause(unsigned int val) { m_Cause = val; }

	unsigned int GetCallID_TIME();


	unsigned int GetRouterTimerID()  { return m_RouterTimerID; }
	void SetRouterTimerID(unsigned int val) { m_RouterTimerID = val; }



	//unsigned char GetIVRChListCount() { return m_IVRChListCount; }
	//void SetIVRChListCount(unsigned char val) { m_IVRChListCount = val; }

	//KFPC_CH_IVRType_t GetIVRType() { return m_IVRType; }
	//void SetIVRType(KFPC_CH_IVRType_t val) { m_IVRType = val; }

	KFPC_ConnectionType GetConType() { return m_ConType; }
	void SetConType(KFPC_ConnectionType val) { m_ConType = val; }

	//void ClearSwitchChRes();

	void ClearCallID();

	void ExeCmdQueue();
	KFPC_DEVICE& GetDevice() { return m_Device; }
	void SetDevice(KFPC_DEVICE& val) { m_Device = val; }

	unsigned long long& GetCallID() { return m_CallID; }
	void SetCallID();

	unsigned int PushCmdID(unsigned int CmdID);	/**< 添加一个等待处理的Cmd */
	unsigned int PopCmdID();	/**< 弹出一个Cmd ID */

	unsigned int GetCmdID() { return m_CmdID; }
	void SetCmdID(unsigned int val,unsigned int DebugStrLen,const char* DebugStr);

	//KFPC_CH_TYPE GetChType() { return m_ChType; }
	//void SetChType(KFPC_CH_TYPE val);

	unsigned int& GetDstAppID() { return m_DstAppID; }
	void SetDstAppID(unsigned int val); 

	friend class KFPC_ChMgr;

	KFPC_Channel(void);
	~KFPC_Channel(void);

	unsigned short GetID() { return m_ID; }
	unsigned int Init(bool log=true);

	unsigned int ClearCmdQueue();

	KFPC_Ch_Status GetStatus() { return m_Status; }
	void SetStatus(KFPC_Ch_Status val);

	virtual int GetHandle();
	virtual int GetConnectHandle();

	virtual void SetCh(KFPC_Channel* pch);
	virtual KFPC_Channel* GetCh(){return this;};


	//KFPC_SignalType GetSignalType() { return m_SignalType; }
	//void SetSignalType(KFPC_SignalType val);

	void Reset(bool log = true);

	virtual unsigned int AcceptCall();
	virtual unsigned int AnswerCall();
	virtual unsigned int ReleaseCall(int Cause);
	//virtual unsigned int CallOut(KFPC_DEVICE&	Device ,KFPC_TrunkGroup* pMyTrunkGroup,KFPC_SIP_Addr* pSipCallOutAddr,bool Overlap = false);	

	virtual unsigned int AcceptCallAck(unsigned int	Result); 
	virtual unsigned int AnswerCallAck(unsigned int	Result);
	virtual unsigned int ReleaseCallAck(unsigned int	Result);

	virtual unsigned int CallOutAck(unsigned int Result,unsigned char	Cause);

	virtual unsigned int EVT_IncomingCall(KFPC_DEVICE&	Device);	

	void SetMoreInfoTimer();
	void SetSAMEvtTimer();
	void ClearSAMEvtTimer();

	virtual unsigned int EVT_AlertCall();
	virtual unsigned int EVT_AnsweredCall();

	void RelayAnswerCall();
	virtual unsigned int EVT_ReleasedCall(unsigned int Cause);
	//unsigned int	EVT_ReqMoreinfo();
	//unsigned int	EVT_Dialing();
	//void ClearMoreInfoTimer();
	//virtual unsigned int EVT_MoreInfo(const char* Num);
	

	void ExecuteCmd( KFPC_BaseCommand* pCmd );
	void CancelCmd();
	void CancelCmdQueue();

	unsigned int ExecuteRspCmd(KFPC_BaseCommand* pCmd,unsigned int MsgID);


	void ConnectedAck(int result);

	void ClearMonitorIVR();
	
	void DisconnectedAck(int result);

	void ClearSwitchData( int result );
	
	void PlayVoiceBegin();
	void PlayVoiceCompleted(unsigned int Reason);
	void PlayDTMFCompleted(unsigned int Reason);
	void CollectDigitCompleted(char* pDigits);
	void RecordFileCompleted(const char* pFileName,bool TransformMp3);
	void RecordFileBegin();


	unsigned int CreateConf(unsigned int Size,bool PlayRecord = true);
	unsigned int CreateConfAck( int Result,int ConfID );

	void SetCreateConfTimer( int Result );
	unsigned int FreeConf();
	unsigned int FreeConfAck(int Result);

	void ClearConfTimer();
	

	unsigned int ConnectToIVR(bool MonitorIVR);

	unsigned int ConnectToFax();
	

	unsigned int FirstDTMFReceived();


	//unsigned int ConnectToCh(KFPC_Channel* pDstCh,unsigned char ConnectMode = SC_FULLDUP);
	

	unsigned int ConnectToChAck(unsigned int Result);
	//unsigned int DisconnectToIVRAck(int Result);
	unsigned int Free3PartyConf();

	//unsigned int Disconnect(unsigned short Mode = EV_ASYNC);
	//unsigned int DisconnectMonitorIVR(unsigned short Mode = EV_ASYNC);

	unsigned int RequestFaxChAck(char* pFaxServIP,unsigned short	FaxServRTPPort,int Result,int FaxMode);
	unsigned int StartSendFaxAck(int Result);
	unsigned int StopSendFaxAck(int Result);
	unsigned int StartRecvFaxAck(int Result);
	unsigned int StopRecvFaxAck(int Result);
	unsigned int SendFaxCompleted(unsigned char PageNum,int Result);
	unsigned int RecvFaxCompleted(unsigned char PageNum,int Result);
	//unsigned int DisconnectMixIVR(unsigned short Mode = EV_ASYNC);
	unsigned int DisconnectCallInAbnormalStatus();

	unsigned int Send_EVT_ReleasedCall(int cause);
	unsigned int Send_EVT_AnsweredCall();
	unsigned int Send_EVT_AlertCall();

	unsigned int Send_EVT_PlayVoiceCompleted();
	unsigned int Send_EVT_CollectDTMFCompleted(unsigned int  DigitCount,const char* Digits,unsigned int Result);

	void CancelCmdWithDSPError(unsigned int nReason);
	void ProcessEstConfError(unsigned int nReason);
	void ProcessRouteError(unsigned int nReason);
	void ProcessFaxAppOffLine();
	/**
	 * FullName:  	KFPC_Channel::ChangeConnectMode
	 * @brief 		改变连接模式
	 * @param[in,out] unsigned int ConnectMode 0为听说,1为只听
	 * @return   	unsigned int
	 */
	unsigned int ChangeConnectMode(unsigned int ConnectMode);

	int StartFax();
	void DoStartMediaAck(int Result);
	void DoStopMediaAck(int Result);

	int Voice2Fax();
	void DoVoice2FaxAck(int Result);

	unsigned int RequestFaxCh();
	unsigned int StartSendFax(const char* pFileName,const char *pSenderIdent,const char *pSubAddress,const char *pPageHeaderInfo,const char *pIdentifier);
	unsigned int StartRecvFax(const char* pFileName);
	unsigned int StopRecvFax();
	unsigned int StopSendFax();
	void EVT_HookFlash();
	void RecoverIVRForAgChannel();

	//void  OnRSP_API_TTS_TO_FILE(KFPC_RSP_API_TTS* pTTSMsg);

	void ChannelParked();		//通道被保持

	unsigned int Send_MoreInfo(const char* Num);
	unsigned int Send_MoreInfoAck(unsigned int Ret);
	void UpdateMoreInfo2Called();

	void DoMoreInfoTimeOut();
	void DoSAMTimeOut();
	void EVT_RecvInfo(unsigned int ulSerialNo,const char* pInfo);

	MSML_DeleteWhen GetMSML_DeleteWhen() const;
	void SetMSML_DeleteWhen(MSML_DeleteWhen val);

	unsigned int SIPSendInfoAck(unsigned short usCause,unsigned int ulSerialNo,const char* Body);

	void Log();
	void LogCDR();

	void DoCmdTimeOut();
	
};

