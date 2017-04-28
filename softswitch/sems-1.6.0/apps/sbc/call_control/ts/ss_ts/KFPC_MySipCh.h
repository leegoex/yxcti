#pragma once
#include "kfpc_sipserver_api.h"
#include "KFPC_TrunkGroup.h"

typedef enum MySipCh_Action_t
{
	MySipCh_Action_Null,
	MySipCh_Action_ReleaseCall,
	MySipCh_Action_403Forbidden,
	MySipCh_Action_183SessionProgress,
	MySipCh_Action_200SessionProgress,
	MySipCh_Action_ReleaseCallCompleted
}MySipCh_Action_t;


static const char* Action2Str(MySipCh_Action_t Act)
{
	switch (Act)
	{
	case MySipCh_Action_Null:				return	"Null";
	case MySipCh_Action_ReleaseCall:		return	"ReleaseCall";
	case MySipCh_Action_403Forbidden:		return	"403Forbidden";
	case MySipCh_Action_183SessionProgress:	return	"183SessionProgress";
	case MySipCh_Action_200SessionProgress:	return	"200SessionProgress";
	case MySipCh_Action_ReleaseCallCompleted:return	"ReleaseCallCompleted";
	default:return "Unknow";
	}
	
}

typedef enum MySipCh_Status_t
{
	MySipCh_Status_Null,
	MySipCh_Status_CallOffer,
	MySipCh_Status_Ring,
	MySipCh_Status_Connected,
	MySipCh_Status_Release,
	MySipCh_Status_ByeEvt
}MySipCh_Status_t;

static const char* Status2Str(MySipCh_Status_t Status)
{
	switch (Status)
	{
	case MySipCh_Status_Null:		return "Status_Null";
	case MySipCh_Status_CallOffer:	return "Status_CallOffer";
	case MySipCh_Status_Ring:		return "Status_Ring";
	case MySipCh_Status_Connected:	return "Status_Connected";
	case MySipCh_Status_Release:	return "Status_Release";
	case MySipCh_Status_ByeEvt:		return "Status_ByeEvt";
	default:return "Unknow";
	}

}


class KFPC_MySipCh
{
private:
	unsigned int			m_ID;
	string					m_SIP_CallID;

	string					m_PeerMediaIP;
	unsigned short			m_PeerMediaPort;
	AudioCodeCfg_t			m_AudioCode;

	KFPC_Receive_Info_t		m_Receive_Info;
	KFPC_From_t				m_From;
	KFPC_To_t				m_To;		
	LocalRtp_t				m_LocalRtp;

	MySipCh_Status_t		m_Status;							/**< Í¨µÀ×´Ì¬ */
	KFPC_CALL_FLAG			m_CallFlag;
	MySipCh_Action_t		m_Action;

public:


	KFPC_CALL_FLAG GetCallFlag()  { return m_CallFlag; }
	void SetCallFlag(KFPC_CALL_FLAG val) { m_CallFlag = val; }

	MySipCh_Action_t GetAction() const { return m_Action; }
	void SetAction(MySipCh_Action_t val);

	MySipCh_Status_t GetStatus()  { return m_Status; }
	void SetStatus(MySipCh_Status_t val) { m_Status = val; }

	LocalRtp_t GetLocalRtp() const { return m_LocalRtp; }
	void SetLocalRtp(LocalRtp_t val) { m_LocalRtp = val; }

	KFPC_Receive_Info_t* GetReceive_Info() { return &m_Receive_Info; }
	void SetReceive_Info(KFPC_Receive_Info_t* val) { memcpy(&m_Receive_Info,val,sizeof(KFPC_Receive_Info_t)); }

	KFPC_From_t* GetFrom() { return &m_From; }
	void SetFrom(KFPC_From_t* val) { memcpy(&m_From,val,sizeof(KFPC_From_t)); }

	KFPC_To_t* GetTo() { return &m_To; }
	void SetTo(KFPC_To_t* val) { memcpy(&m_To,val,sizeof(KFPC_To_t)); }




	const char* GetSIP_CallID() const { return m_SIP_CallID.c_str(); }
	void SetSIP_CallID(const char* val) { m_SIP_CallID = val; }


	KFPC_MySipCh();
	~KFPC_MySipCh();

	unsigned int Init(bool log=true);
	void Reset(bool log = true);
	virtual unsigned int AcceptCall();	
	virtual unsigned int AnswerCall();	

	//************************************
	// Method:    ReleaseCall
	// FullName:  KFPC_SipCh::ReleaseCall
	// Access:    virtual public 
	// Returns:   unsigned int
	// Qualifier:
	// Parameter: int Cause
	//************************************
	virtual unsigned int ReleaseCall(int Cause);
	//************************************
	// Method:    CallOut
	// FullName:  KFPC_SipCh::CallOut
	// Access:    virtual public 
	// Returns:   unsigned int
	// Qualifier:
	// Parameter: KFPC_DEVICE & Device
	//************************************
	virtual unsigned int CallOut(KFPC_DEVICE&	Device ,KFPC_TrunkGroup* pMyTrunkGroup,KFPC_SIP_Addr* pSipCallOutAddr,bool Overlap = false);	

	virtual unsigned int AcceptCallAck(unsigned int	Result);	
	virtual unsigned int AnswerCallAck(unsigned int	Result);

	unsigned int StartMedia();
	virtual unsigned int ReleaseCallAck(unsigned int	Result);;

	virtual unsigned int CallOutAck(unsigned int Result,unsigned char	Cause);

	virtual unsigned int EVT_IncomingCall(KFPC_DEVICE&	Device);	
	virtual unsigned int EVT_AlertCall();	
	virtual unsigned int EVT_AnsweredCall();	
	virtual unsigned int EVT_ReleasedCall(unsigned int Cause);	
	int	SIPReasonTransform(unsigned short Reason);
	void RecoverResource();

	unsigned long long GetCallID();
	//unsigned int Send_MoreInfo(const char* Num) {return 0;}
	//unsigned int Send_MoreInfoAck(unsigned int Ret) { return 0;}

	void EVT_RecvInfo();
	void OnInfoSentAck();
	void OnInfoAckSentAck();
	void EVT_RecvInfoAck();

	unsigned int SIPSendInfoAck(unsigned short usCause,unsigned int ulSerialNo,const char* Body);
	void SIPSendPRACK();
		
	//void OnRSP_SIP_SIP_RESPONSE( KFPC_RSP_SIP_RESPONSE_t* pMsg );

	void Send_403Forbidden();
	//unsigned int Send_183(KFPC_SdpInfo_t*	SDP,KFPC_Contact_t*	Contact);
	//unsigned int Send_200(KFPC_SdpInfo_t*	SDP,KFPC_Contact_t*	Contact);
	
	//unsigned int sdp_init(
	//	const char* MediaIp,
	//	unsigned short MediaPort,
	//	unsigned char CodeIdList[],
	//	unsigned char CodeIDCount,
	//	KFPC_SdpInfo_t*	SDP,
	//	SendRecvMode_t SendRecvMode);

	//void OnEVT_SIP_ACK( KFPC_EVT_SIP_ACK_t* pMsg );
	//void OnEVT_SIP_BYE(KFPC_EVT_SIP_BYE_t* pMsg);
};

