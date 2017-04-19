#include "KFPC_EHNode.h"
#include "KFPC_ChMgr.h"
#include "KFPC_TServerConfigFile.h"
#include "KFPC_TSLicSerMgr.h"
#include "KFPC_TSLicenseSerAPIHandlerImp.h"

KFPC_EHNode::KFPC_EHNode(void):
m_ID(-1),
//m_SipChMgr(this),
//m_VOIPMgr(this),
//m_DTIChMgr(this),
//m_ConfMgr(*this),
//m_AGChMgr(this),
//m_VoiceMgr(this),
m_MainBoardSN(""),
m_ValidTime(time(NULL) + 3600),
m_AgChLicCount(120),
m_SpanChLicCount(64),
m_VoipChLicCount(4096),
m_IVRChLicCount(4096),
m_TimerID(0)
{
	/**< 这里什么都不可以执行 */
#ifdef TSERVER_NO_LIC
	SetInfinityValidTime();
#endif


}


KFPC_EHNode::~KFPC_EHNode(void)
{
}

void KFPC_EHNode::Reset(bool log )
{
	m_ValidTime = time(NULL) + 3600;

#ifdef TSERVER_NO_LIC
	SetInfinityValidTime();
#endif

	m_AgChLicCount = 120;
	m_SpanChLicCount = 64;
	m_VoipChLicCount = 4096;
	m_IVRChLicCount = 4096;
	//m_SipChMgr.Reset(log);
	//m_VOIPMgr.Reset(log);
	//m_DTIChMgr.Reset(log);
	//m_ConfMgr.Reset(log);
	//m_AGChMgr.Reset(log);
	//m_VoiceMgr.Reset(log);
	//ResetIpCh();
	//SetConfInService();
}

void KFPC_EHNode::Working()
{

}

//void KFPC_EHNode::SetIpChInService(unsigned int  MaxSip)
//{
	
	//unsigned int  MaxSip = (unsigned int)(-1);
	

	//KFPC_NodeCfg* pNodeCfg = KFPCTServerCfgInstance->GetNodeCfgMgr()->GetNodeCfg(m_ID);

	//if(pNodeCfg != NULL)
	//{
	//	MaxSip = pNodeCfg->GetMaxSip();
	//}

	//

	//unsigned short BeginSpan	= KFPC_VOIP_BEGIN_SPAN + KFPC_NODE_MAX_SPAN*m_ID;
	//unsigned short EndSpan		= BeginSpan + KFPC_SINGLE_NODE_MAX_VOIP_SPAN;

	//INFO_LOG(0,"IsxNo:%d,MaxSip:%u,BeginSpan:%u,EndSpan:%u",m_ID,MaxSip,BeginSpan,EndSpan-1);

	//for(int Span=BeginSpan;Span<EndSpan;Span++)
	//{
	//	for(int ch = 0;ch < KFPC_MAX_CHANNEL;ch ++)
	//	{
	//		unsigned short ChID = Span*KFPC_MAX_CHANNEL+ch;

	//		KFPC_Channel*	pCh = KFPC_ChMgrInstance->GetChannel(ChID);

	//		if(MaxSip>0)
	//		{
	//			pCh->SetSignalType(KFPC_SignalType_SIP);
	//			pCh->SetStatus(KFPC_CH_Status_Idle);
	//			MaxSip--;
	//		}
	//	}

	//}
//}

//void KFPC_EHNode::ResetIpCh()
//{
	


	//unsigned int MaxSip = (unsigned int)(-1);


	//KFPC_NodeCfg* pNodeCfg = KFPCTServerCfgInstance->GetNodeCfgMgr()->GetNodeCfg(m_ID);

	//if(pNodeCfg != NULL)
	//{
	//	MaxSip = pNodeCfg->GetMaxSip();
	//}

	//unsigned short BeginSpan	= KFPC_VOIP_BEGIN_SPAN + KFPC_NODE_MAX_SPAN*m_ID;
	//unsigned short EndSpan		= BeginSpan + KFPC_SINGLE_NODE_MAX_VOIP_SPAN;
	//
	//INFO_LOG(0,"IsxNo:%d,BeginSpan:%u,EndSpan:%u,MaxSip:%u",m_ID,BeginSpan,EndSpan-1,MaxSip);

	//for(int Span=BeginSpan;Span<EndSpan;Span++)
	//{
	//	for(int ch = 0;ch < KFPC_MAX_CHANNEL;ch ++)
	//	{
	//		unsigned short ChID = Span*KFPC_MAX_CHANNEL+ch;

	//		KFPC_Channel*	pCh = KFPC_ChMgrInstance->GetChannel(ChID);
	//		if(MaxSip>0)
	//		{
	//			pCh->Reset(false);
	//			MaxSip--;
	//		}
	//		
	//	}

	//}
//}

//void KFPC_EHNode::SetConfInService()
//{

	//unsigned int  MaxConf = (unsigned int)(-1);

	//KFPC_NodeCfg* pNodeCfg = KFPCTServerCfgInstance->GetNodeCfgMgr()->GetNodeCfg(m_ID);

	//if(pNodeCfg != NULL)
	//{
	//	MaxConf = pNodeCfg->GetMaxConference();
	//}

	//unsigned short BeginSpan	= KFPC_NODE_MAX_SPAN*m_ID + KFPC_CONFID_BEGIN_SPAN;
	//unsigned short EndSpan		= BeginSpan + KFPC_SINGLE_NODE_MAX_CONF_SPAN;

	//unsigned int ConfBeginCh =	BeginSpan*KFPC_MAX_CHANNEL;
	//unsigned int ConfEndCh	=	EndSpan * KFPC_MAX_CHANNEL;

	//INFO_LOG(0,"IsxNo:%d,Conf BeginSpan:%u,EndSpan:%u,MaxConf:%u",m_ID,BeginSpan,EndSpan-1,MaxConf);

	//for (unsigned int i= ConfBeginCh;i<ConfEndCh;i++)
	//{
	//	KFPC_Channel*	pCh = KFPC_ChMgrInstance->GetChannel(i);
	//	if(MaxConf>0)
	//	{
	//		pCh->Reset(false);
	//		pCh->SetStatus(KFPC_CH_Status_Idle);

	//		MaxConf--;
	//	}
	//}
//}

void KFPC_EHNode::GetBrdInfo()
{
	//BOARD_INFO brdinfo;

	//int Ret = 0;
	//unsigned int LoopCount = 5;
	//while( (Ret = OAM_com_getbrdinfo(m_ID,0,BT_MB,&brdinfo)) != 0 && 
	//	(LoopCount --) > 0 ) 
	//{
	//	Sleep(500);
	//}

	//if(Ret == 0)
	//{
	//	char	MainBoardSN[128]="";

	//	unsigned int k = 0;
	//	for(unsigned int i=0;i<strlen(brdinfo.SerialNo);i++)
	//	{

	//		if(brdinfo.SerialNo[i] != '-')
	//		{
	//			MainBoardSN[k++] = brdinfo.SerialNo[i];
	//		}

	//	}

	//	MainBoardSN[k]=0;

	//	m_MainBoardSN = MainBoardSN;
	//	INFO_LOG(0,"NodeID:%u,SwitchID:%s",m_ID,MainBoardSN);
	//}
	//else
	//{
	//	long errcode = OAM_sr_lasterr();
	//	char* errmsgp = OAM_sr_errmsgp(errcode);
	//	WARNING_LOG(0,"err:%s",errmsgp);
	//}
}

void KFPC_EHNode::GetLic(unsigned int SN)
{
#ifndef TSERVER_NO_LIC


	if(strcmp(GetMainBoardSN(),"No SerialNo") == 0)
	{
		SetInfinityLic();
	}
	else
	{
		KFPC_TSLicSer* pLicSer = KFPC_TSLicSerMgrInstance->GetAvailableLicSer(SN);

		if(pLicSer != NULL)
		{
			KFPCTSLicenseSerAPIHandlerImpInstance->SendREQ_LIC_TSERVERLIC(pLicSer->GetSN(),m_ID,pLicSer->GetAppID(),0,m_MainBoardSN.c_str());
			SetTimer(GET_TS_LICFAIL_TIMER,pLicSer->GetSN());
		}
		else
		{
			SetTimer(GET_TS_LICFAIL_TIMER,0);
		}
	}


#endif


	
}

void KFPC_EHNode::SetTimer( unsigned int TimeOut /*= 600*/,unsigned int SN )
{
	if(m_TimerID > 0)
	{
		KFPC_TSLicSerMgrInstance->ClearTimer(m_TimerID);
	}

	m_TimerID = KFPC_TSLicSerMgrInstance->SetTimer(m_ID,TimeOut,SN);
}

void KFPC_EHNode::SetVoipChLicCount( unsigned short val )
{
	m_VoipChLicCount = val;
	//m_VOIPMgr.SetLicSize(val);
	INFO_LOG(0,"NodeID:%d,Voip license size:%u",m_ID,val);
}

void KFPC_EHNode::SetIVRChLicCount( unsigned short val )
{
	m_IVRChLicCount = val;
	//m_VoiceMgr.SetLicSize(val);
	INFO_LOG(0,"NodeID:%d,voice license size:%u",m_ID,val);
}

void KFPC_EHNode::SetAgChLicCount( unsigned short val )
{
	m_AgChLicCount = val;
	//m_AGChMgr.SetLicSize(val);
	INFO_LOG(0,"NodeID:%d,ag license size:%u",m_ID,val);
}

void KFPC_EHNode::SetSpanChLicCount( unsigned short val )
{
	m_SpanChLicCount = val;
	//m_DTIChMgr.SetLic(val);
	INFO_LOG(0,"NodeID:%d,dti license size:%u",m_ID,val);
}

unsigned short KFPC_EHNode::GetIVRChLicCount()
{
	return m_IVRChLicCount;
}

bool KFPC_EHNode::CheckLicValidTime()
{
#ifdef TSERVER_NO_LIC
	return true;
#else
	if(m_ValidTime > time(NULL))
	{
		return true;
	}
	else
	{
		ERROR_LOG(0,"iSxNo:%u,license over time.",m_ID);
		return false;
	}
#endif
}

void KFPC_EHNode::SetInfinityValidTime()
{

	m_ValidTime = time(NULL) + 3600*24*365*50;

}

void KFPC_EHNode::SetInfinityLic()
{
	DEBUG_LOG(0,"");
	SetInfinityValidTime();
	m_AgChLicCount = 120;
	m_SpanChLicCount = 64;
	m_VoipChLicCount = 4096;
	m_IVRChLicCount = 4096;
}
