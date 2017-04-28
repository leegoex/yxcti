#include "KFPC_DBTaskInsertCallAlarm.h"
#include "KFPC_DBThreadPool.h"
#include "kfpc_logex.h"
#include "KFPC_MySipCh.h"
#include "kfpc_logex.h"
#include "KFPC_ContactCenterPublicDef.h"
#include "kfpc_msg.h"
#include "KFPC_TServerConfigFile.h"
#include "KFPC_TServerErr.h"
#include "KFPC_MonitorRefreshData.h"
#include "KFPC_CallAlarmMgr.h"
#include "KFPC_NodeMgr.h"
#include "kfpc_sipserver_api.h"


#ifdef LINUX
#include <arpa/inet.h>
#endif

KFPC_MySipCh::KFPC_MySipCh(){
	Reset(false);
}


KFPC_MySipCh::~KFPC_MySipCh()
{
}



unsigned int KFPC_MySipCh::Init(bool log)
{

	//m_LocalRtp = LocalRtp_EH;
	m_Status = MySipCh_Status_Null;							/**< Í¨µÀ×´Ì¬ */
	m_CallFlag = CALL_FLAG_IN;
	m_Action = MySipCh_Action_Null;

	return  0;
}

void KFPC_MySipCh::Reset(bool log )
{
	if(log)
		DEBUG_LOG(GetCallID(), "MySipID:%u", m_ID);

	Init(log);
}


unsigned int KFPC_MySipCh::AnswerCall()
{
	//AssignIPMChCh
	//KFPC_EHNode* pEHNode = GetNode();
	//unsigned int nRet =0;
	//KFPC_IPMCh*	 pIPMCh = NULL;
	//char PeerAddrStr[KFPC_SIP_SER_MAX_HOST_LEN];


	//if(m_LocalRtp == LocalRtp_EH)
	//{
	//	if(NULL == (pIPMCh = GetXiopCh()))
	//	{

	//		nRet = AssignVOIPCh(pIPMCh,1);

	//		if(nRet != 0)
	//		{
	//			Send_403Forbidden();
	//			return nRet;
	//		}

	//		SetXiopCh(pIPMCh);
	//		pIPMCh->SetSipCh(this);

	//		pIPMCh->SetDstAddr(IntIP2Str(GetPeerAddr(),PeerAddrStr,KFPC_SIP_SER_MAX_HOST_LEN),
	//			GetMediaPort());

	//		pIPMCh->SetCodeID(GetCurrentCode());
	//	

	//	}

	//	pIPMCh->SetDstAddr(IntIP2Str(GetPeerAddr(),PeerAddrStr,KFPC_SIP_SER_MAX_HOST_LEN),
	//		GetMediaPort());

	//	pIPMCh->SetCodeID(GetCurrentCode());

	//	nRet = pIPMCh->IpmStartMedia();

	//	if(nRet != 0)
	//	{

	//		WARNING_LOG(GetCallID(),"StartMedia Error on MySipID:%u, ",GetID());

	//		Send_403Forbidden();

	//		return KFPC_EH_ERR(nRet);
	//	}

	//}
	//else if(m_LocalRtp == LocalRtp_MediaServer)
	//{

	//}
	//else
	//{

	//}


	//KFPC_SdpInfo_t	SDP;

	//memset(&SDP,0,sizeof(SDP));

	//if(nRet = sdp_init(pIPMCh->GetSrcAddr()->IpAddr.IpAddr,
	//	pIPMCh->GetSrcAddr()->RtpPort.UdpPort,
	//	m_CodeIdList,
	//	m_CodeCount,
	//	&SDP,
	//	KFPC_SendRecvMode_Sendrecv) != 0)
	//{
	//	WARNING_LOG(GetCallID(),"sdp_init fail. MySipID:%u, ",GetID());

	//	Send_403Forbidden();
	//	RecoverVOIPCh();

	//	return nRet;
	//}


	//if ((nRet = Send_200(&SDP,&m_LocalContact)) != 0)
	//{
	//	WARNING_LOG(GetCallID(),"MySipID:%u Send_200 Failed",  GetID());

	//	RecoverVOIPCh();

	//	return nRet;
	//}
	//else
	//{
		return 0;
	//}	
	//
}

unsigned int KFPC_MySipCh::AcceptCall()
{
	//unsigned int nRet = 0;
	//KFPC_IPMCh*	 pIPMCh = NULL;
	//char PeerAddrStr[KFPC_SIP_SER_MAX_HOST_LEN];

	//if(m_LocalRtp == LocalRtp_EH)
	//{
	//	if(NULL == (pIPMCh = GetXiopCh()))
	//	{
	//		nRet = AssignVOIPCh(pIPMCh,1);

	//		if(nRet != 0)
	//		{
	//			Send_403Forbidden();
	//			return nRet;
	//		}

	//		SetXiopCh(pIPMCh);
	//		pIPMCh->SetSipCh(this);
	//	}


	//	pIPMCh->SetDstAddr(IntIP2Str(GetPeerAddr(),PeerAddrStr,KFPC_SIP_SER_MAX_HOST_LEN),
	//		GetMediaPort());

	//	pIPMCh->SetCodeID(GetCurrentCode());
	//
	//	nRet = pIPMCh->IpmStartMedia();

	//	if(nRet != 0)
	//	{

	//		WARNING_LOG(GetCallID(),"StartMedia Error on MySipID:%u, ",GetID());

	//		Send_403Forbidden();

	//		return KFPC_EH_ERR(nRet);
	//	}

	//}
	//else if(m_LocalRtp == LocalRtp_MediaServer)
	//{

	//}
	//else
	//{

	//}


	//KFPC_SdpInfo_t	SDP;

	//memset(&SDP,0,sizeof(SDP));

	//if(nRet = sdp_init(pIPMCh->GetSrcAddr()->IpAddr.IpAddr,
	//	pIPMCh->GetSrcAddr()->RtpPort.UdpPort,
	//	m_CodeIdList,
	//	m_CodeCount,
	//	&SDP,
	//	KFPC_SendRecvMode_Sendrecv) != 0)
	//{
	//	WARNING_LOG(GetCallID(),"sdp_init fail. MySipID:%u, ",GetID());

	//	Send_403Forbidden();
	//	RecoverVOIPCh();

	//	return nRet;
	//}


	//if ((nRet = Send_183(&SDP,&m_LocalContact)) != 0)
	//{
	//	WARNING_LOG(GetCallID(),"MySipID:%u Send_183 Failed",  GetID());
	//	
	//	RecoverVOIPCh();

	//	return nRet;
	//}
	//else
	//{
		return 0;
	//}

}

unsigned int KFPC_MySipCh::AnswerCallAck( unsigned int Result )
{
	//if(NULL != m_pCh)
	//{

	//	m_pCh->AnswerCallAck(Result);

	//	if(Result == 0)
	//	{
	//		return StartMedia();

	//	}
	//	
	//}
	//else
	//{
	//	WARNING_LOG(GetCallID(),"MySipID:%u pch is null.",m_ID)
	//}
	return 0;
}

unsigned int KFPC_MySipCh::ReleaseCall( int Cause )
{

	//int Ret = 0;
	//unsigned long long CallID = 0;

	//Cause = SIPReasonTransform(Cause);

	//if(m_pCh != NULL)
	//{
	//	m_pCh->SetCause(Cause);
	//	CallID = m_pCh->GetCallID();
	//}

	//if(m_CallFlag == CALL_FLAG_IN)
	//{
	//	switch(m_Status)
	//	{
	//	case MySipCh_Status_CallOffer:
	//	case MySipCh_Status_Ring:

	//		{
	//			Ret = SIPServerAPIInstance->Send_REQ_SIP_RESPONSE(m_SIPServerAPPID,&m_DialogID,&m_TransactionID,CallID,Cause,"",0,0);
	//			SetAction(MySipCh_Action_ReleaseCall);
	//			SetStatus(MySipCh_Status_Release);
	//		}
	//		break;
	//	case MySipCh_Status_ByeEvt:
	//		{				
	//			Ret = SIPServerAPIInstance->Send_REQ_SIP_RESPONSE(m_SIPServerAPPID,&m_DialogID,&m_TransactionID,CallID,Cause,"",0,0);
	//			SetAction(MySipCh_Action_ReleaseCall);
	//			SetStatus(MySipCh_Status_Release);
	//		}
	//		break;
	//	case MySipCh_Status_Connected:
	//		{
	//			//Ret = SIPServerAPIInstance->Send_REQ_SIP_BYE(m_SIPServerAPPID,CallID,
	//			//	&m_LocalContact,
	//			//	m_LocalCseq++,
	//			//	&m_From,
	//			//	&m_To,
	//			//	m_CallFlag);

	//			SetAction(MySipCh_Action_ReleaseCall);
	//			SetStatus(MySipCh_Status_Release);
	//		}
	//		break;
	//	case MySipCh_Status_Release:
	//		{
	//			return KFPC_ERR_ChStatusErr;
	//		}
	//		break;
	//	default:
	//		{

	//		}
	//	}

	//}
	//else
	//{

	//}


	return 0;
}

unsigned int KFPC_MySipCh::AcceptCallAck( unsigned int Result )
{
	//if(NULL != m_pCh)
	//{
	//	m_pCh->AcceptCallAck(Result);

	//	if(Result == 0)
	//	{
	//		StartMedia();
	//	}
	//}
	//else
	//{
	//	WARNING_LOG(GetCallID(),"MySipID:%u,SIPServerAPPID:%u, pch is null.",m_ID,m_SIPServerAPPID)
	//}
	return 0;
}

unsigned int KFPC_MySipCh::CallOut( KFPC_DEVICE& Device ,KFPC_TrunkGroup* pMyTrunkGroup,KFPC_SIP_Addr* pSipCallOutAddr,bool Overlap )
{

	return 0;
}

unsigned int KFPC_MySipCh::EVT_IncomingCall( KFPC_DEVICE& Device )
{

	return 0;
}

unsigned int KFPC_MySipCh::EVT_AlertCall()
{
	
	return 0;
}

unsigned int KFPC_MySipCh::EVT_AnsweredCall()
{

	return 0;
}

unsigned int KFPC_MySipCh::EVT_ReleasedCall(unsigned int Cause)
{

	return 0;
}

unsigned int KFPC_MySipCh::CallOutAck( unsigned int Result,unsigned char Cause )
{

	return 0;
}

unsigned int KFPC_MySipCh::ReleaseCallAck( unsigned int Result )
{

	return 0;
}

int	KFPC_MySipCh::SIPReasonTransform(unsigned short Reason)
{
	switch(Reason)
	{
	case IPEC_SIPReasonStatus200OK:
	case IPEC_SIPReasonStatus400BadRequest:             
	case IPEC_SIPReasonStatus401Unauthorized:                
	case IPEC_SIPReasonStatus402PaymentRequired:             
	case IPEC_SIPReasonStatus403Forbidden:                 
	case IPEC_SIPReasonStatus404NotFound:                  
	case IPEC_SIPReasonStatus405MethodNotAllowed:          
	case IPEC_SIPReasonStatus406NotAcceptable:           
	case IPEC_SIPReasonStatus407ProxyAuthenticationRequired:
	case IPEC_SIPReasonStatus408RequestTimeout:       
	case IPEC_SIPReasonStatus410Gone:                   
	case IPEC_SIPReasonStatus413RequestEntityTooLarge:  
	case IPEC_SIPReasonStatus414RequestUriTooLong:   
	case IPEC_SIPReasonStatus415UnsupportedMediaType:
	case IPEC_SIPReasonStatus416UnsupportedURIScheme: 
	case IPEC_SIPReasonStatus420BadExtension:         
	case IPEC_SIPReasonStatus421ExtensionRequired:
	case IPEC_SIPReasonStatus423IntervalTooBrief:
	case IPEC_SIPReasonStatus480TemporarilyUnavailable:
	case IPEC_SIPReasonStatus481CallTransactionDoesNotExist:
	case IPEC_SIPReasonStatus482LoopDetected:         
	case IPEC_SIPReasonStatus483TooManyHops:     
	case IPEC_SIPReasonStatus484AddressIncomplete:          
	case IPEC_SIPReasonStatus485Ambiguous:                  
	case IPEC_SIPReasonStatus486BusyHere:                
	case IPEC_SIPReasonStatus487RequestTerminated:        
	case IPEC_SIPReasonStatus488NotAcceptableHere:           
	case IPEC_SIPReasonStatus491RequestPending:              
	case IPEC_SIPReasonStatus493Undecipherable:          
	case IPEC_SIPReasonStatus500ServerInternalError:        
	case IPEC_SIPReasonStatus501NotImplemented:            
	case IPEC_SIPReasonStatus502BadGateway:              
	case IPEC_SIPReasonStatus503ServiceUnavailable:    
	case IPEC_SIPReasonStatus504ServerTimeout:        
	case IPEC_SIPReasonStatus505VersionNotSupported: 
	case IPEC_SIPReasonStatus513MessageTooLarge:        
	case IPEC_SIPReasonStatus600BusyEverywhere:     
	case IPEC_SIPReasonStatus603Decline:                  
	case IPEC_SIPReasonStatus604DoesNotExistAnywhere:    
	case IPEC_SIPReasonStatus606NotAcceptable:              
	case IPEC_SIPReasonStatusBYE:                         
	case IPEC_SIPReasonStatusCANCEL:
		{
			return Reason;
		}
	case 16:return IPEC_SIPReasonStatus403Forbidden;
	default:
		{		
			WARNING_LOG(GetCallID(),
				"Reason:%u err",Reason );

			return IPEC_SIPReasonStatus403Forbidden;
		}
	}
}

unsigned long long KFPC_MySipCh::GetCallID()
{
	return 0;
}


void KFPC_MySipCh::EVT_RecvInfo()
{


}

void KFPC_MySipCh::OnInfoSentAck()
{
	
}

void KFPC_MySipCh::OnInfoAckSentAck()
{
	
}

void KFPC_MySipCh::EVT_RecvInfoAck()
{
	
}

unsigned int KFPC_MySipCh::SIPSendInfoAck(unsigned short usCause,unsigned int ulSerialNo,const char* Body)
{
	//SIP_INFO_ACK Ack;
	//Ack.ulSerialNo = ulSerialNo;
	//Ack.usCause = usCause;//IPEC_SIPReasonStatus200OK;
	//
	//if(strlen(Body) > 0)
	//{
	//	
	//	Ack.Body.u.BodyTrans.ContentType.Valid = 1;
	//	Ack.Body.u.BodyTrans.ContentType.MediaType = ISXSIP_MEDIATYPE_APPLICATION;
	//	Ack.Body.u.BodyTrans.ContentType.MediaSubType = ISXSIP_MEDIASUBTYPE_OTHER;
	//	strcpy(Ack.Body.u.BodyTrans.ContentType.MediaSubTypeStr,"xml");
	//
	//	Ack.Body.Valid = 1;
	//	Ack.Body.BodyPartyType = BodyPartyType_TRANS;
	//	
	//	Ack.Body.u.BodyTrans.BodyLen = strlen(Body);
	//	strncpy(Ack.Body.u.BodyTrans.Body,Body,MAX_TRANS_LEN-1);
	//	

	//}
	//else
	//{
	//	Ack.Body.Valid = 0;
	//}
	//
	//int Ret = ISX_gc_SIPSendInfoAck(m_crn, EV_ASYNC, &Ack);

	return 0;
}


//
//void KFPC_MySipCh::Send_403Forbidden()
//{
//	SIPServerAPIInstance->Send_REQ_SIP_RESPONSE(m_SIPServerAPPID,&m_DialogID,&m_TransactionID,m_pCh->GetCallID(),IPEC_SIPReasonStatus403Forbidden,"Forbidden",0,0);
//	WARNING_LOG(GetCallID(),"MySipID:%u.",GetID());
//	SetAction(MySipCh_Action_403Forbidden);
//}
//
//
//unsigned int KFPC_MySipCh::Send_183( KFPC_SdpInfo_t* SDP,KFPC_Contact_t*	Contact )
//{
//
//	unsigned  int Ret = SIPServerAPIInstance->Send_REQ_SIP_RESPONSE(m_SIPServerAPPID,&m_DialogID,&m_TransactionID,m_pCh->GetCallID(),183,"Session Progress",0,0,SDP,Contact);
//	DEBUG_LOG(GetCallID(),"MySipID:%u.",GetID());
//	SetAction(MySipCh_Action_183SessionProgress);
//
//	return Ret;
//}
//
//unsigned int KFPC_MySipCh::sdp_init( const char* MediaIp, unsigned short MediaPort, unsigned char CodeIdList[], unsigned char CodeIDCount, KFPC_SdpInfo_t* SDP,SendRecvMode_t SendRecvMode )
//{
//	if(CodeIDCount == 0)
//	{
//		WARNING_LOG(GetCallID()," MediaIp:%s,MediaPort:%u,CodeIDCount:%u err",MediaIp, MediaPort,CodeIDCount);
//		return KFPC_SIP_ERR_CodeCount;
//	}
//	else
//	{
//		DEBUG_LOG(GetCallID()," MediaIp:%s,MediaPort:%u,CodeIDCount:%u",MediaIp, MediaPort,CodeIDCount);
//	}
//	
//	memset(SDP,0,sizeof(KFPC_SdpInfo_t));
//
//	SDP->Host = inet_addr(MediaIp);
//	SDP->StreamsNum = 1;
//
//	for (int k=0;k<SDP->StreamsNum;k++)
//	{
//		SDP->SdpStream[k].MediaType = KFPC_MediaType_audio;
//		SDP->SdpStream[k].PayloadsNum = CodeIDCount;
//		SDP->SdpStream[k].Port = MediaPort;
//		SDP->SdpStream[k].SendRecvMode = SendRecvMode;
//		SDP->SdpStream[k].TransportProto = KFPC_TransportProto_RTP_AVP;
//
//		CodeIDCount = MIN(CodeIDCount,KFPC_SIP_SER_MAX_PAYLOAD_COUNT);
//
//		for(int i=0;i<CodeIDCount;i++)
//		{
//			SDP->SdpStream[k].Payloads[i] = CodeIDToPayLoadID(CodeIdList[i]);
//
//		}
//
//		SDP->SdpStream[k].PayloadsNum = CodeIDCount;
//
//		for(int j=0;j<CodeIDCount;j++)
//		{
//			KFPC_SdpPayloadAttr_t* pSdpPayloadAttr = CodeIDToVoicePayloadAttrMap(CodeIdList[j]);
//
//			if(pSdpPayloadAttr != NULL)
//			{
//				memcpy(&SDP->SdpStream[k].PayloadAttr[j],pSdpPayloadAttr,sizeof(KFPC_SdpPayloadAttr_t));
//			}
//			else
//			{
//				ERROR_LOG(GetCallID(),"MySipID:%u,CodeID:%u error",GetID(),CodeIdList[j]);
//			}
//		}
//		
//		SDP->SdpStream[k].SdpPayloadAttrNum = CodeIDCount;
//
//		if(SDP->SdpStream[k].SdpPayloadAttrNum < KFPC_SIP_SER_MAX_PAYLOAD_ATTR_COUNT)
//		{
//			SDP->SdpStream[k].PayloadAttr[SDP->SdpStream[k].SdpPayloadAttrNum].AttFieldType = KFPC_AttFieldType_Rtpmap;
//			SDP->SdpStream[k].PayloadAttr[SDP->SdpStream[k].SdpPayloadAttrNum].RtpPayload	= 101;
//			SDP->SdpStream[k].PayloadAttr[SDP->SdpStream[k].SdpPayloadAttrNum].RtpClock		= 8000;
//			strncpy(SDP->SdpStream[k].PayloadAttr[SDP->SdpStream[k].SdpPayloadAttrNum].RtpEnc,"telephone-event",KFPC_SIP_SER_MAX_ENCODE_LEN-1);
//			//strncpy(SDP->SdpStream[k].PayloadAttr[SDP->SdpStream[k].SdpPayloadAttrNum].FmtpString,"0-15",KFPC_SIP_SER_MAX_FMTP_STR_LEN-1);
//			SDP->SdpStream[k].SdpPayloadAttrNum++;
//		}
//
//		if(SDP->SdpStream[k].SdpPayloadAttrNum < KFPC_SIP_SER_MAX_PAYLOAD_ATTR_COUNT)
//		{
//			SDP->SdpStream[k].PayloadAttr[SDP->SdpStream[k].SdpPayloadAttrNum].AttFieldType = KFPC_AttFieldType_Fmtp;
//			SDP->SdpStream[k].PayloadAttr[SDP->SdpStream[k].SdpPayloadAttrNum].RtpPayload	= 101;
//			strncpy(SDP->SdpStream[k].PayloadAttr[SDP->SdpStream[k].SdpPayloadAttrNum].FmtpString,"0-15",KFPC_SIP_SER_MAX_FMTP_STR_LEN-1);
//			SDP->SdpStream[k].SdpPayloadAttrNum++;
//		}		
//
//	}
//
//	return 0;
//}
//
//unsigned int KFPC_MySipCh::Send_200( KFPC_SdpInfo_t* SDP,KFPC_Contact_t*	Contact)
//{
//	unsigned  int Ret = SIPServerAPIInstance->Send_REQ_SIP_RESPONSE(m_SIPServerAPPID,&m_DialogID,&m_TransactionID,m_pCh->GetCallID(),200,"OK",0,0,SDP,Contact);
//	DEBUG_LOG(GetCallID(),"MySipID:%u.",GetID());
//	SetAction(MySipCh_Action_200SessionProgress);
//
//	return Ret;
//}
//
//void KFPC_MySipCh::SetCodeIDList( unsigned char* CodeIDList,unsigned int CodeCount )
//{
//
//	m_CodeCount = MIN(CodeCount,KFPC_SIP_SER_MAX_PAYLOAD_COUNT);
//	for(int i=0;i<m_CodeCount;i++)
//	{
//		m_CodeIdList[i] = CodeIDList[i];
//	}
//
//}

void KFPC_MySipCh::SetAction( MySipCh_Action_t val )
{
	
	DEBUG_LOG(GetCallID(),"MySipID:%u,Action:%s-->%s",m_ID,Action2Str(m_Action),Action2Str(val));

	m_Action = val;


}
//
//void KFPC_MySipCh::OnEVT_SIP_ACK( KFPC_EVT_SIP_ACK_t* pMsg )
//{
//	INFO_LOG(GetCallID(),"MySipID:%u,Status:%s",GetID(),Status2Str(m_Status));
//
//	switch(m_Status)
//	{
//	case MySipCh_Status_Null:break;
//	case MySipCh_Status_CallOffer:
//		{
//
//		}
//		break;
//	case MySipCh_Status_Ring:break;
//	case MySipCh_Status_Connected:break;
//	case MySipCh_Status_Release:break;
//	default:
//		{
//			WARNING_LOG(GetCallID(),"MySipID:%u,Status error.",GetID());
//		}
//	}
//}
//
//void KFPC_MySipCh::OnEVT_SIP_BYE( KFPC_EVT_SIP_BYE_t* pMsg )
//{
//	if(NULL != m_pCh)
//	{
//		if(m_Status == MySipCh_Status_Connected)
//		{
//			INFO_LOG(m_pCh->GetCallID(),"ChID:%u,MySipID:%u",m_pCh->GetID(),GetID());
//			SetStatus(MySipCh_Status_ByeEvt);
//
//			m_pCh->EVT_ReleasedCall(200);
//
//			//KFPC_Contact_t	Contact;
//
//			//memset(&Contact,0,sizeof(KFPC_Contact_t));
//
//			//strncpy(Contact.UserInfo,m_To.UserInfo,KFPC_SIP_SER_MAX_USER_LEN-1);
//
//			//Contact.HostPort.Host=KFPC_ContactIPMapMgrInstance->LanIP2WanIP(m_Receive_Info.InterfaceIp);
//
//			//Contact.HostPort.Port = m_Receive_Info.InterfacePort;
//
//			//Send_200ForBye(&Contact);
//		}
//		else
//		{
//			WARNING_LOG(GetCallID(),"MySipID:%u,Status:%s error.",GetID(),Status2Str(m_Status));
//		}
//	}
//	else
//	{
//		WARNING_LOG(GetCallID(),"MySipID:%u pch is null.",GetID())
//	}
//	
//}
//
//KFPC_EHNode* KFPC_MySipCh::GetVOIPResNode()
//{
//	if(m_IPMCh != NULL)
//	{
//		return m_IPMCh->GetNode();
//	}
//	else
//	{
//		return NULL;
//	}
//}
//
//int KFPC_MySipCh::GetHandle()
//{
//	if(NULL != m_IPMCh)
//	{
//		return m_IPMCh->GetHandle();
//	}
//	else
//	{
//		WARNING_LOG(GetCallID(),"SIPID:%u IPMCh is NULL",m_ID);
//		return -1;
//	}
//}