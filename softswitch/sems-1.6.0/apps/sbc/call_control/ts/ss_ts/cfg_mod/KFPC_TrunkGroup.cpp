#include "kfpc_logex.h"
#include "KFPC_TrunkGroup.h"
#include "KFPC_TServerDef.h"
#include "KFPC_ChMgr.h"

#include <algorithm>
#include "KFPC_TServerErr.h"
#include "KFPC_ChMgr.h"
#include "kfpc_linuxwinnet.h"
#ifdef LINUX
#include <arpa/inet.h>
#endif
#include "KFPC_TServerAPIHandlerImp.h"

CChannelBlock::CChannelBlock()
{
}

CChannelBlock::~CChannelBlock()
{

}

void CChannelBlock::Log()
{
	DEBUG_LOG(0,"BeginSpan:%u,BeginChannel:%u,EndSpan:%u,EndChannel:%u,QueryIdleType:%s,LastSpan:%u,LastChannel:%u",
		m_BeginSpan,
		m_BeginChannel,
		m_EndSpan,
		m_EndChannel,
		IdleTypeToStr(m_QueryIdleType),
		m_LastSpan,
		m_LastChannel
		);
}

void CChannelBlock::SetIPChannelInService()
{
	INFO_LOG(0, "BeginSpan:%u,EndSpan:%u", m_BeginSpan, m_EndSpan);

	for(unsigned int span = m_BeginSpan ;span <= m_EndSpan;span++)
	{
		for(unsigned int channel = m_BeginChannel;channel <= m_EndChannel;channel++)
		{
			unsigned int Index = span * KFPC_MAX_CHANNEL + channel;

			KFPC_Channel* pChannel = KFPC_ChMgrInstance->GetChannel(Index);
			if(pChannel != NULL)
			{
				//if(pChannel->GetChType() == CH_TYPE_SIP)
				{
					pChannel->SetStatus(KFPC_CH_Status_Idle);
				}
			}

		}
	}
}

KFPC_TrunkGroup::KFPC_TrunkGroup():
m_Old(false),
m_SipCallOutMode(CallOutMode_StandBy),
m_AutoAnswer(false),
//m_SIPServer(0),
m_LocalRtp(LocalRtp_Relay),
m_Support183(false)
{
	Init();	
}

KFPC_TrunkGroup::~KFPC_TrunkGroup()
{
	
}

size_t KFPC_TrunkGroup::GetChannelBlockCount()
{ 
	return m_ChannelBlockList.size();
}

int  KFPC_TrunkGroup::AddRouteBlock(unsigned int BeginSpan, 
							unsigned int BeginChannel, 
							unsigned int EndSpan, 
							unsigned int EndChannel,
							KFPC_QueryIdleChType IdleType)
{


	CChannelBlock Block;
	memset(&Block, 0, sizeof(CChannelBlock));

	INFO_LOG(0,"AddRouteBlock Name:%s,BeginSpan:%d,BeginChannel:%d,EndSpan:%d,EndChannel:%d,IdleType:%d.",
				m_Name,
				BeginSpan,BeginChannel,EndSpan,EndChannel,IdleType);

	Block.SetBeginSpan(BeginSpan);
	Block.SetBeginChannel(BeginChannel);
	Block.SetEndSpan(EndSpan);
	Block.SetEndChannel(EndChannel);
	Block.SetIdleType(IdleType);
    
    SetLastSpan(BeginSpan);
	SetLastChannel(BeginChannel);

	m_ChannelBlockList.push_back(Block);
	return 0;
}

void KFPC_TrunkGroup::Init(void)
{
	memset(m_Name,0,KFPC_TRUNKGROUP_NAME_LEN);	//中继组名	
	memset(m_Description,0,KFPC_TRUNKGROUP_DESC_LEN);	//中继组描述

	m_LastSpan = 0;				//保留最后查询的位置
	m_LastChannel = 0;
	m_BlockIndex = 0;				//记录route Block的索引


	//以下是VOIP路由参数
	m_SIPCallOfferList.clear();			/**< 呼叫来电话的IP */
	//m_SIPCallOut.Init();				/**< 呼叫呼出网关 */
	m_SIPCallOutList.clear();

	m_AudioCodeList.clear();		/**< 编码地址 */

	m_ChannelBlockList.clear();		/**< 通道块例表 */

	memset(m_Name,0,KFPC_TRUNKGROUP_NAME_LEN);	//中继组名

	m_LastSpan = 0;				//保留最后查询的位置
	m_LastChannel = 0;

	m_SIPCallOfferList.clear();
	
	m_CallerNOA = 0;
	m_CalledNOA = 0;
}

void KFPC_TrunkGroup::SetNextBlockIndex(void)
{
	CChannelBlock*	pBlock = NULL;
	m_BlockIndex ++;

	if (m_BlockIndex < GetChannelBlockCount())
	{
	}
	else
	{
		m_BlockIndex = 0;
	}


}

void KFPC_TrunkGroup::SetBlockIndex(unsigned int unBlockIndex) 
{ 
	CChannelBlock*	pBlock = NULL;

	m_BlockIndex = unBlockIndex; 
	if (m_BlockIndex < GetChannelBlockCount())
	{
		pBlock = &m_ChannelBlockList[m_BlockIndex];
		
		if (pBlock != NULL)
		{
			SetLastChannel(pBlock->GetBeginChannel());
			SetLastSpan(pBlock->GetBeginSpan());
		}
	}
	else
	{
		m_BlockIndex = 0;
		pBlock = &m_ChannelBlockList[0];

		if (pBlock != NULL)
		{
			SetLastChannel(pBlock->GetBeginChannel());
			SetLastSpan(pBlock->GetBeginSpan());
		}
	}
}



CChannelBlock*	KFPC_TrunkGroup::GetCurrentBlock()
{
	return &m_ChannelBlockList[m_BlockIndex];
}


int KFPC_TrunkGroup::AddFromAddrBlock(const  char* Ip,const char* pMask,unsigned short Port,const char* pUserName,const char* pPassWord )
{
	KFPC_SIP_Addr	SIP_Addr;

	SIP_Addr.SetIpv4Add(Ip);
	SIP_Addr.SetMask(inet_addr(pMask));
	SIP_Addr.SetUdpPort(Port);
	SIP_Addr.SetUserName(pUserName);
	SIP_Addr.SetPassWord(pPassWord);
	
	m_SIPCallOfferList.push_back(SIP_Addr);
	INFO_LOG(0,"IP:%s,Mask:%s,Port:%u,UserName:%s,PassWord:%s,SIPCallOfferList size:%u",Ip,pMask,Port,pUserName,pPassWord,m_SIPCallOfferList.size());
	return 0;
}



KFPC_SIP_Addr* KFPC_TrunkGroup::QueryFromAddr(const char* pIpAddr )
{
	unsigned int IP = inet_addr(pIpAddr);

	KFPC_SIP_Addr_List::iterator	BeginIter = m_SIPCallOfferList.begin();
	//KFPC_SIP_Addr_List::iterator	EndIter = m_SIPCallOfferList.end();

	for(;BeginIter != m_SIPCallOfferList.end();BeginIter++)
	{
		KFPC_SIP_Addr& SipAddr = *BeginIter;

		//if((SipAddr.GetMask() & IP) == SipAddr.GetIpv4Add())

		if(strcmp(pIpAddr,SipAddr.GetIpv4Add()) == 0)
		{
			return &(*BeginIter);
		}
		else
		{
			unsigned int IntIpAddr = inet_addr(SipAddr.GetIpv4Add());
			if((SipAddr.GetMask() & IP) == IntIpAddr)
			{
				return &(*BeginIter);
			}
		}
	}

	return NULL;

}

//int KFPC_TrunkGroup::SetToAddr(const  char* Ip,const char* pMask,unsigned short Port,const char* pUserName,const char* pPassWord )
//{
//	m_SIPCallOut.SetIpv4Add(Ip);
//	m_SIPCallOut.SetMask(inet_addr(pMask));
//	m_SIPCallOut.SetUdpPort(Port);
//	m_SIPCallOut.SetUserName(pUserName);
//	m_SIPCallOut.SetPassWord(pPassWord);	
//	return 0;
//}

void KFPC_TrunkGroup::AddAudioCode( unsigned int AudioCode )
{

	KFPC_AudioCode_List::iterator	BeginIter = m_AudioCodeList.begin();
	KFPC_AudioCode_List::iterator	EndIter = m_AudioCodeList.end();

	KFPC_AudioCode_List::iterator Iter = find(BeginIter,EndIter,AudioCode);

	if(Iter == EndIter)
	{
		m_AudioCodeList.push_back(AudioCode);
	}
	else
	{
		WARNING_LOG(0,"TrunkGroup name:%s,AudioCode:%u already exist.",m_Name,AudioCode)
	}
	
}

KFPC_AudioCode_List& KFPC_TrunkGroup::AudioCodeList()
{
	return m_AudioCodeList;
}
void KFPC_SIP_Addr::Init( )
{

	//m_Ipv4Add = 0;
	m_Mask = 0;
	m_UdpPort = 0;
	memset(m_UserName,0,KFPC_USER_NAME_LEN);
	memset(m_PassWord,0,KFPC_PASSWD_LEN);
	memset(m_Proxy,0,KFPC_MAX_IP_LEN);
	memset(m_Ipv4Add,0,KFPC_MAX_IP_LEN);
	m_NodeID = -1;
}

void KFPC_SIP_Addr::SetUdpPort( unsigned short val )
{
	m_UdpPort = val;
}

unsigned short& KFPC_SIP_Addr::GetUdpPort()
{
	return m_UdpPort;
}

void KFPC_SIP_Addr::SetUserName(const char* val )
{
	strncpy(m_UserName,val,KFPC_USER_NAME_LEN);
}

//char bit32Count(unsigned int I)
//{
//	char ret = 0;
//	for(int k=0;k<32;k++)
//	{
//		if(I & 0x01)
//		{
//			ret ++;
//			I >>=1;
//		}
//		else
//		{
//			return ret;
//		}
//	}
//	return ret;
//}

void KFPC_SIP_Addr::SetMask( unsigned int val )
{
	m_Mask = val;
}

void KFPC_SIP_Addr::Log()
{

	INFO_LOG(0,"PassWord:%s,Ipv4Add:%s,Mask:0x%x,UserName:%s,UdpPort:%u",m_PassWord,m_Ipv4Add,m_Mask,m_UserName,m_UdpPort);
}

void KFPC_SIP_Addr::SetProxy( const char* val )
{
	if(val != NULL)
	{
		strncpy(m_Proxy ,val,KFPC_MAX_IP_LEN-1);
	}
	else
	{
		memset(m_Proxy,0,sizeof(m_Proxy));
	}
	
}
unsigned int	KFPC_TrunkGroup::LookupIdleChannelInBlockWithW(KFPC_ChMgr &ChannelList,unsigned int* IdleChannel,CChannelBlock * pBlock)
{
	unsigned int	BeginSpan	= pBlock->GetBeginSpan();
	unsigned int	BeginChannel= pBlock->GetBeginChannel();
	unsigned int	EndSpan     = pBlock->GetEndSpan();
	unsigned int	EndChannel  = pBlock->GetEndChannel();
	unsigned int	LastSpan	= pBlock->GetLastSpan();
	unsigned int	LastChannel = pBlock->GetLastChannel();

	unsigned short	nSpan		= LastSpan;
	unsigned char	nChannel	= LastChannel;

	unsigned int	nIndex		= 0;
	KFPC_Channel*		pChannel	= NULL;

	pBlock->Log();

	//loop in last time remain channel in the same span
	for (nChannel = LastChannel; nChannel <= EndChannel; nChannel++)
	{
		nIndex = nSpan * KFPC_MAX_CHANNEL + nChannel;
		pChannel = ChannelList.GetChannel(nIndex);

		if (pChannel != NULL)
		{
			if (pChannel->GetStatus()  & KFPC_IDLE_STATUS)
			{
				*IdleChannel = nIndex;

				SetLastChannelWithW(nChannel,  nSpan,  pBlock);

				return 0;
			}
		}
	}//end for

	//
	for (nSpan =LastSpan + 1; nSpan <= EndSpan; nSpan++)
	{
		for (nChannel = BeginChannel; nChannel <= EndChannel; nChannel++)
		{
			nIndex = nSpan * KFPC_MAX_CHANNEL + nChannel;
			pChannel = ChannelList.GetChannel(nIndex);
			if (pChannel != NULL)
			{
				if (pChannel->GetStatus()  & KFPC_IDLE_STATUS)
				{
					*IdleChannel = nIndex;
					SetLastChannelWithW(nChannel,  nSpan,  pBlock);
					return 0;
				}
			}
		}
	}//end for


	//如果当前路由组有多个块,就找下一块,不在同一个块内循环查找，否则就重新开始
	if(this->GetChannelBlockCount() > 1)
	{
		pBlock->SetLastSpan(BeginSpan); pBlock->SetLastChannel(BeginChannel);
		return KFPC_ERR_NotFoundIdleChannel;
	}

	for (nSpan = BeginSpan; nSpan <=LastSpan; nSpan++)
	{
		for (nChannel = BeginChannel; nChannel < EndChannel; nChannel++)
		{
			nIndex = nSpan * KFPC_MAX_CHANNEL + nChannel;
			pChannel = ChannelList.GetChannel(nIndex);

			if (pChannel != NULL)
			{
				if (pChannel->GetStatus()  & KFPC_IDLE_STATUS)
				{
					*IdleChannel = nIndex;
					SetLastChannelWithW(nChannel,  nSpan,  pBlock);
					return 0;
				}
			}
		}
	}//end for

	return KFPC_ERR_NotFoundIdleChannel;
}

unsigned int	KFPC_TrunkGroup::LookupIdleChannelInBlockWithZ(KFPC_ChMgr &ChannelList,unsigned int* IdleChannel,CChannelBlock * pBlock)
{
	unsigned int	BeginSpan	= pBlock->GetBeginSpan();
	unsigned int	BeginChannel= pBlock->GetBeginChannel();
	unsigned int	EndSpan     = pBlock->GetEndSpan();
	unsigned int	EndChannel  = pBlock->GetEndChannel();
	unsigned int	LastSpan	= pBlock->GetLastSpan();
	unsigned int	LastChannel = pBlock->GetLastChannel();


	unsigned short	nSpan		= LastSpan;
	unsigned char	nChannel	= LastChannel;
	unsigned long	nIndex		= 0;
	KFPC_Channel*	pChannel	= NULL;

	pBlock->Log();

	//loop in last time remain channel in the same span
	for (nSpan = LastSpan; nSpan <= EndSpan; nSpan++)
	{
		nIndex = nSpan * KFPC_MAX_CHANNEL + nChannel;
		pChannel = ChannelList.GetChannel(nIndex);

		if (pChannel != NULL)
		{
			if (pChannel->GetStatus()  & KFPC_IDLE_STATUS)
			{
				*IdleChannel = nIndex;
				
				SetLastChannelWithZ(nChannel,  nSpan,  pBlock);

				return 0;
			}
		}
	}//end for

	//
	for (nChannel = LastChannel + 1; nChannel <= EndChannel; nChannel++)
	{
		for (nSpan = BeginSpan; nSpan <= EndSpan; nSpan++)
		{
			nIndex = nSpan * KFPC_MAX_CHANNEL + nChannel;
			pChannel = ChannelList.GetChannel(nIndex);

			if (pChannel != NULL)
			{
				if (pChannel->GetStatus()  & KFPC_IDLE_STATUS)
				{
					*IdleChannel = nIndex;

					SetLastChannelWithZ(nChannel,  nSpan,  pBlock);								

					return 0;
				}
			}
		}
	}//end for


	//如果当前路由组有多个块,就找下一块,不在同一个块内循环查找，否则就重新开始
	if(this->GetChannelBlockCount() > 1)
	{
		pBlock->SetLastSpan(BeginSpan); pBlock->SetLastChannel(BeginChannel);
		return KFPC_ERR_NotFoundIdleChannel;
	}

	//
	for (nChannel = BeginChannel; nChannel <= LastChannel; nChannel++)
	{
		for (nSpan = BeginSpan; nSpan < EndSpan; nSpan++)
		{
			nIndex = nSpan * KFPC_MAX_CHANNEL + nChannel;
			pChannel = ChannelList.GetChannel(nIndex);

			if (pChannel != NULL)
			{
				if (pChannel->GetStatus()  & KFPC_IDLE_STATUS)
				{
					*IdleChannel = nIndex;

					SetLastChannelWithZ(nChannel,  nSpan,  pBlock);							

					return 0;
				}
			}}

	}//end for

	return KFPC_ERR_NotFoundIdleChannel;
}

unsigned int	KFPC_TrunkGroup::LookupIdleChannelInBlockWithOdd(KFPC_ChMgr &ChannelList,unsigned int* IdleChannel,CChannelBlock * pBlock)
{

	unsigned int	BeginSpan	= pBlock->GetBeginSpan();
	unsigned int	BeginChannel= pBlock->GetBeginChannel();
	unsigned int	EndSpan     = pBlock->GetEndSpan();
	unsigned int	EndChannel  = pBlock->GetEndChannel();
	unsigned int	LastSpan	= pBlock->GetLastSpan();
	unsigned int	LastChannel = pBlock->GetLastChannel();


	unsigned short	nSpan		= LastSpan;
	unsigned char	nChannel	= LastChannel;
	unsigned long	nIndex		= 0;
	KFPC_Channel*	pChannel	= NULL;

	unsigned long	EvenChannel = ULONGTYPE;	//这个变量用于存储第一个偶数通道,如果奇数没有找到就返回这个值.

	pBlock->Log();

	//loop in last time remain channel in the same span
	for (nChannel = LastChannel; nChannel <= EndChannel; nChannel++)
	{
		nIndex = nSpan * KFPC_MAX_CHANNEL + nChannel;
		pChannel = ChannelList.GetChannel(nIndex);

		if (pChannel != NULL)
		{
			if (pChannel->GetStatus()  & KFPC_IDLE_STATUS)
			{
				if(nIndex%2 == 0)
				{
					if(EvenChannel == ULONGTYPE)	EvenChannel = nIndex;
				}
				else
				{

					*IdleChannel = nIndex;

					SetLastChannelWithOdd(nChannel,  nSpan,  pBlock);

					return 0;
				}
			}
		}
	}//end for

	//
	for (nSpan =LastSpan + 1; nSpan <= EndSpan; nSpan++)
	{
		for (nChannel = BeginChannel; nChannel <= EndChannel; nChannel++)
		{
			nIndex = nSpan * KFPC_MAX_CHANNEL + nChannel;
			pChannel = ChannelList.GetChannel(nIndex);
			if (pChannel != NULL)
			{
				if (pChannel->GetStatus()  & KFPC_IDLE_STATUS)
				{
					if(nIndex%2 == 0)
					{
						if(EvenChannel == ULONGTYPE)	EvenChannel = nIndex;
					}
					else
					{

						*IdleChannel = nIndex;
						SetLastChannelWithOdd(nChannel,  nSpan,  pBlock);
						return 0;
					}
				}
			}
		}
	}//end for

	//如果当前路由组有多个块,就找下一块,否则就重新开始
	if(this->GetChannelBlockCount() > 1)
	{
		pBlock->SetLastSpan(BeginSpan); pBlock->SetLastChannel(BeginChannel);

		if(EvenChannel == ULONGTYPE)
		{
			return KFPC_ERR_NotFoundIdleChannel;
		}
		else
		{
			*IdleChannel = EvenChannel;

			unsigned short nSpan = ChannelToSpan(EvenChannel);
			unsigned char  nChannel = ChannelToTimeSlot(EvenChannel);

			SetLastChannelWithOdd(nChannel,  nSpan,  pBlock);
			return 0;
		}
	}

	//
	for (nSpan = BeginSpan; nSpan <=LastSpan; nSpan++)
	{
		for (nChannel = BeginChannel; nChannel < EndChannel; nChannel++)
		{
			nIndex = nSpan * KFPC_MAX_CHANNEL + nChannel;
			pChannel = ChannelList.GetChannel(nIndex);

			if (pChannel != NULL)
			{
				if (pChannel->GetStatus()  & KFPC_IDLE_STATUS)
				{
					if(nIndex%2 == 0)
					{
						if(EvenChannel == ULONGTYPE)	EvenChannel = nIndex;
					}
					else
					{

						*IdleChannel = nIndex;
						SetLastChannelWithOdd(nChannel,  nSpan,  pBlock);
						return 0;
					}
				}
			}
		}
	}//end for

	if(EvenChannel == ULONGTYPE)
	{
		return KFPC_ERR_NotFoundIdleChannel;
	}
	else
	{
		*IdleChannel = EvenChannel;
		unsigned short nSpan = ChannelToSpan(EvenChannel);
		unsigned char  nChannel = ChannelToTimeSlot(EvenChannel);

		SetLastChannelWithOdd(nChannel,  nSpan,  pBlock);
		return 0;
	}
}

unsigned int	KFPC_TrunkGroup::LookupIdleChannelInBlockWithEven(KFPC_ChMgr &ChannelList,unsigned int* IdleChannel,CChannelBlock * pBlock)
{

	unsigned int	BeginSpan	= pBlock->GetBeginSpan();
	unsigned int	BeginChannel= pBlock->GetBeginChannel();
	unsigned int	EndSpan     = pBlock->GetEndSpan();
	unsigned int	EndChannel  = pBlock->GetEndChannel();
	unsigned int	LastSpan	= pBlock->GetLastSpan();
	unsigned int	LastChannel = pBlock->GetLastChannel();


	unsigned short	nSpan		= LastSpan;
	unsigned char	nChannel	= LastChannel;
	unsigned long	nIndex		= 0;
	KFPC_Channel*		pChannel	= NULL;

	unsigned long	OddChannel = ULONGTYPE;	//这个变量用于存储第一个偶数通道,如果奇数没有找到就返回这个值.

	pBlock->Log();

	//loop in last time remain channel in the same span
	for (nChannel = LastChannel; nChannel <= EndChannel; nChannel++)
	{
		nIndex = nSpan * KFPC_MAX_CHANNEL + nChannel;
		pChannel = ChannelList.GetChannel(nIndex);

		if (pChannel != NULL)
		{
			if (pChannel->GetStatus() & KFPC_IDLE_STATUS)
			{
				if(nIndex%2 != 0)
				{
					if(OddChannel == ULONGTYPE)	OddChannel = nIndex;
				}
				else
				{

					*IdleChannel = nIndex;

					SetLastChannelWithEvent(nChannel, nSpan, pBlock);

					return 0;
				}
			}
		}
	}//end for

	//
	for (nSpan =LastSpan + 1; nSpan <= EndSpan; nSpan++)
	{
		for (nChannel = BeginChannel; nChannel <= EndChannel; nChannel++)
		{
			nIndex = nSpan * KFPC_MAX_CHANNEL + nChannel;
			pChannel = ChannelList.GetChannel(nIndex);
			if (pChannel != NULL)
			{
				if (pChannel->GetStatus()  & KFPC_IDLE_STATUS)
				{
					if(nIndex%2 != 0)
					{
						if(OddChannel == ULONGTYPE)	OddChannel = nIndex;
					}
					else
					{

						*IdleChannel = nIndex;
						SetLastChannelWithEvent(nChannel, nSpan, pBlock);
						return 0;
					}
				}
			}
		}
	}//end for

	//如果当前路由组有多个块,就找下一块,否则就重新开始
	if(this->GetChannelBlockCount() > 1)
	{
		pBlock->SetLastSpan(BeginSpan); pBlock->SetLastChannel(BeginChannel);
		if(OddChannel == ULONGTYPE)
		{
			return KFPC_ERR_NotFoundIdleChannel;
		}
		else
		{
			*IdleChannel = OddChannel;	

			unsigned short nSpan = ChannelToSpan(OddChannel);
			unsigned char  nChannel = ChannelToTimeSlot(OddChannel);

			SetLastChannelWithEvent(nChannel, nSpan, pBlock);
			return 0;
		}
	}

	//
	for (nSpan = BeginSpan; nSpan <=LastSpan; nSpan++)
	{
		for (nChannel = BeginChannel; nChannel < EndChannel; nChannel++)
		{
			nIndex = nSpan * KFPC_MAX_CHANNEL + nChannel;
			pChannel = ChannelList.GetChannel(nIndex);

			if (pChannel != NULL)
			{
				if (pChannel->GetStatus()  & KFPC_IDLE_STATUS)
				{
					if(nIndex%2 != 0)
					{
						if(OddChannel == ULONGTYPE)	OddChannel = nIndex;
					}
					else
					{

						*IdleChannel = nIndex;
						SetLastChannelWithEvent(nChannel, nSpan, pBlock);
						return 0;
					}
				}
			}
		}
	}//end for

	if(OddChannel == ULONGTYPE)
	{
		return KFPC_ERR_NotFoundIdleChannel;
	}
	else
	{
		*IdleChannel = OddChannel;

		unsigned short nSpan = ChannelToSpan(OddChannel);
		unsigned char  nChannel = ChannelToTimeSlot(OddChannel);

		SetLastChannelWithEvent(nChannel, nSpan, pBlock);

		return 0;
	}
}


unsigned int KFPC_TrunkGroup::GetIdleChannel( unsigned int SrcChannel, unsigned int *IdleChannel )
{
	
	/**
	 *	如果通道块为0 则返回错误
	 */
	if(this->GetChannelBlockCount() == 0)
	{
		WARNING_LOG(0,"TrunkName:%s,no channel block count.",m_Name)
		return KFPC_ERR_TrunkGroupNoChannelBlock;
	}

	/**
	 *	如果只有一个通道块，则只查一次
	 */
	unsigned int unMaxBlockCount = (this->GetChannelBlockCount() == 1)?this->GetChannelBlockCount():this->GetChannelBlockCount()+1;
	unsigned int unBlockCount	=	0;

	DEBUG_LOG(0,"SrcChannel:%u,MaxBlockCount:%u,BlockIndex:%u",SrcChannel,unMaxBlockCount,m_BlockIndex);

	//优先查找一个与SrcChannel相同的板卡路由块
	if(SrcChannel != UINTTYPE)
	{
		do
		{
			CChannelBlock *pBlock = NULL;

			pBlock = this->GetCurrentBlock();

			unBlockCount++;

			if (pBlock != NULL)
			{

				unsigned int BeginSpan =	pBlock->GetBeginSpan();
				unsigned int BeginChannel =	pBlock->GetBeginChannel();
				unsigned int EndSpan =		pBlock->GetEndSpan();
				unsigned int EndChannel = 	pBlock->GetEndChannel();

				unsigned short	sSpan		= ChannelToSpan(SrcChannel);
				unsigned char	sChannel	= ChannelToTimeSlot(SrcChannel);

				if(	BeginSpan <= sSpan &&sSpan <= EndSpan &&
					BeginChannel <= sChannel && sChannel <= EndChannel)
				{
					int ret =  LookupIdleChannel(pBlock, IdleChannel);
					if(ret == 0)	return 0;
				}

				this->SetNextBlockIndex();
			}
		}while(unBlockCount < unMaxBlockCount);

		
		unBlockCount	=	0;

		do
		{
			CChannelBlock *pBlock = NULL;

			pBlock = this->GetCurrentBlock();

			unBlockCount++;

			if (pBlock != NULL)
			{
				unsigned int BeginSpan =	pBlock->GetBeginSpan();
				unsigned int BeginChannel =	pBlock->GetBeginChannel();
				unsigned int EndSpan =		pBlock->GetEndSpan();
				unsigned int EndChannel = 	pBlock->GetEndChannel();

				unsigned short	sSpan		= ChannelToSpan(SrcChannel);
				unsigned char	sChannel	= ChannelToTimeSlot(SrcChannel);
				
				/**< 如果没有找到再找非同一块的通道 */
				if(	!(BeginSpan <= sSpan && sSpan <= EndSpan &&
					BeginChannel <= sChannel && sChannel <= EndChannel))
				{
					int ret =  LookupIdleChannel(pBlock,  IdleChannel);
					if(ret == 0)	return 0;
				}

				this->SetNextBlockIndex();
			}
		}while(unBlockCount < unMaxBlockCount);

	}
	else
	{
		do
		{
			CChannelBlock *pBlock = NULL;

			pBlock = this->GetCurrentBlock();

			unBlockCount++;

			if (pBlock != NULL)
			{

				int ret =  LookupIdleChannel(pBlock, IdleChannel);
				if(ret == 0)	return 0;

				this->SetNextBlockIndex();
			}
		}while(unBlockCount < unMaxBlockCount);
	}

	return KFPC_ERR_NotFoundIdleChannel;
}

unsigned int KFPC_TrunkGroup::LookupIdleChannel( CChannelBlock * pBlock, unsigned int * IdleChannel )
{
	///////////////////////////////////////////////////////////////////////
	// "W" vertical look for idle channel 
	///////////////////////////////////////////////////////////////////////
	if (pBlock->GetIdleType() == KFPC_QueryIdleChType_W)
	{
		return LookupIdleChannelInBlockWithW(	*KFPC_ChMgrInstance,
			IdleChannel,
			pBlock);


	}

	if (pBlock->GetIdleType() == KFPC_QueryIdleChType_Z)
	{
		return  LookupIdleChannelInBlockWithZ(	*KFPC_ChMgrInstance,
			IdleChannel,
			pBlock);
		

	}

	if (pBlock->GetIdleType() == KFPC_QueryIdleChType_Odd)
	{
		return LookupIdleChannelInBlockWithOdd(	*KFPC_ChMgrInstance,
			IdleChannel,
			pBlock);
		

	}

	if (pBlock->GetIdleType() == KFPC_QueryIdleChType_Even)
	{
		return  LookupIdleChannelInBlockWithEven(	*KFPC_ChMgrInstance,
			IdleChannel,
			pBlock);	

	}
	else
	{
		WARNING_LOG(0,"Idle Type err.");
		pBlock->Log();

		return LookupIdleChannelInBlockWithW(	*KFPC_ChMgrInstance,
			IdleChannel,
			pBlock);

	}

	return KFPC_ERR_LookUpIdleChannelTypeErr;
}

void KFPC_TrunkGroup::SetLastChannelWithW( unsigned char nChannel,  unsigned short nSpan,  CChannelBlock * pBlock )
{
	unsigned int	BeginSpan	= pBlock->GetBeginSpan();
	unsigned int	BeginChannel= pBlock->GetBeginChannel();
	unsigned int	EndSpan     = pBlock->GetEndSpan();
	unsigned int	EndChannel  = pBlock->GetEndChannel();

	//找到块尾
	if (nChannel == EndChannel && nSpan == EndSpan)
	{
		pBlock->SetLastSpan(BeginSpan); pBlock->SetLastChannel(BeginChannel);
		this->SetNextBlockIndex(); 
	}
	else
	{
		if(nChannel == EndChannel)
		{
			pBlock->SetLastSpan(nSpan+1); pBlock->SetLastChannel(BeginChannel);
		}
		else
		{
			pBlock->SetLastSpan(nSpan); pBlock->SetLastChannel(nChannel + 1);
		}								
	}

	DEBUG_LOG(0,"Channel:%u,Span:%u,NextBlockIndex:%u",nChannel,nSpan,m_BlockIndex);
}

void KFPC_TrunkGroup::SetLastChannelWithZ( unsigned char nChannel, unsigned short nSpan, CChannelBlock * pBlock)
{
	unsigned int	BeginSpan	= pBlock->GetBeginSpan();
	unsigned int	BeginChannel= pBlock->GetBeginChannel();
	unsigned int	EndSpan     = pBlock->GetEndSpan();
	unsigned int	EndChannel  = pBlock->GetEndChannel();

	if (nChannel == EndChannel && nSpan == EndSpan)
	{
		pBlock->SetLastSpan(BeginSpan); pBlock->SetLastChannel(BeginChannel);
		this->SetNextBlockIndex();
	}
	else if(nSpan == EndSpan)
	{
		pBlock->SetLastSpan(BeginSpan); pBlock->SetLastChannel(nChannel+1);
	}
	else
	{
		pBlock->SetLastSpan(nSpan+1); pBlock->SetLastChannel(nChannel);
	}
}

void KFPC_TrunkGroup::SetLastChannelWithOdd( unsigned char nChannel,unsigned short nSpan, CChannelBlock * pBlock )
{
	unsigned int	BeginSpan	= pBlock->GetBeginSpan();
	unsigned int	BeginChannel= pBlock->GetBeginChannel();
	unsigned int	EndSpan     = pBlock->GetEndSpan();
	unsigned int	EndChannel  = pBlock->GetEndChannel();

	//找到块尾
	if (nChannel == EndChannel && nSpan == EndSpan)
	{
		pBlock->SetLastSpan(BeginSpan); pBlock->SetLastChannel(BeginChannel);
		this->SetNextBlockIndex(); 
	}
	else
	{
		if(nChannel == EndChannel)
		{
			pBlock->SetLastSpan(nSpan+1); pBlock->SetLastChannel(BeginChannel);
		}
		else
		{
			pBlock->SetLastSpan(nSpan); pBlock->SetLastChannel(nChannel + 1);
		}								
	}
}

void KFPC_TrunkGroup::SetLastChannelWithEvent( unsigned char nChannel, unsigned short nSpan, CChannelBlock * pBlock)
{
	unsigned int	BeginSpan	= pBlock->GetBeginSpan();
	unsigned int	BeginChannel= pBlock->GetBeginChannel();
	unsigned int	EndSpan     = pBlock->GetEndSpan();
	unsigned int	EndChannel  = pBlock->GetEndChannel();

	//找到块尾
	if (nChannel == EndChannel && nSpan == EndSpan)
	{
		pBlock->SetLastSpan(BeginSpan); pBlock->SetLastChannel(BeginChannel);
		this->SetNextBlockIndex(); 
	}
	else
	{
		if(nChannel == EndChannel)
		{
			pBlock->SetLastSpan(nSpan+1); pBlock->SetLastChannel(BeginChannel);
		}
		else
		{
			pBlock->SetLastSpan(nSpan); pBlock->SetLastChannel(nChannel + 1);
		}								
	}
}

void KFPC_TrunkGroup::AddWatchAppID( unsigned int AppID )
{
	m_WatchAppIDList.push_back(AppID);
	m_WatchAppIDList.unique();

	INFO_LOG(0,"AppID:%u,TrunkGroup:%s,WatchAppIDList size:%d",AppID,m_Name,m_WatchAppIDList.size());
}

void KFPC_TrunkGroup::DelWatchAppID( unsigned int AppID )
{
	KFPC_APPID_ListIter	BeginIter = m_WatchAppIDList.begin();
	KFPC_APPID_ListIter	EndIter =	m_WatchAppIDList.end();

	KFPC_APPID_ListIter Iter = find(BeginIter,EndIter,AppID);

	if(Iter == EndIter)
	{
		WARNING_LOG(0,"AppID:%u not exist,TrunkGroup:%s,WatchAppIDList size:%d",AppID,m_Name,m_WatchAppIDList.size());
	}
	else
	{
		m_WatchAppIDList.erase(Iter);

		INFO_LOG(0,"AppID:%u,TrunkGroup:%s,WatchAppIDList size:%d,Ret:%d",AppID,m_Name,m_WatchAppIDList.size());
	}


}

unsigned int KFPC_TrunkGroup::GetCallOfferAppID(unsigned int ChID)
{
	unsigned int AppID = -1;

	if(m_WatchAppIDList.empty())
	{
		WARNING_LOG(0,"ChID:%u,TrunkGroup:%s not watch app id.",ChID,m_Name);
		return AppID;
	}
	else
	{
		AppID = m_WatchAppIDList.front();

		m_WatchAppIDList.pop_front();
		m_WatchAppIDList.push_back(AppID);

		return AppID;
	}
}

bool KFPC_TrunkGroup::GetAllCodeList(unsigned char CodeIdList[], unsigned char* pCodeCount)
{
	if(m_AudioCodeList.empty())
	{
		return false;
	}
	*pCodeCount = m_AudioCodeList.size();
	KFPC_AudioCode_List::iterator	BeginIter = m_AudioCodeList.begin();
	//KFPC_AudioCode_List::iterator	EndIter = m_AudioCodeList.end();

	KFPC_AudioCode_List::iterator Iter;
	int i=0;
	for(Iter = BeginIter; Iter != m_AudioCodeList.end(); Iter++)
	{
		CodeIdList[i++] = (*Iter);
	}
	return true;
}

void KFPC_TrunkGroup::Clear()
{
	m_SIPCallOfferList.clear();			/**< 呼叫来电话的IP */
	//m_SIPCallOut.Init();				/**< 呼叫呼出网关 */
	m_SIPCallOutList.clear();

	m_AudioCodeList.clear();		/**< 编码地址 */

	m_ChannelBlockList.clear();		/**< 通道块例表 */
}

int KFPC_TrunkGroup::AddCallOutAddrBlock( const char* Ip,unsigned short Port,const char* pUserName,const char* pPassWord,int NodeID,const char* Proxy )
{
	KFPC_SIP_Addr	SIP_Addr;

	SIP_Addr.SetIpv4Add(Ip);
	SIP_Addr.SetMask(0);
	SIP_Addr.SetUdpPort(Port);
	SIP_Addr.SetUserName(pUserName);
	SIP_Addr.SetPassWord(pPassWord);
	SIP_Addr.SetProxy(Proxy);
	

	SIP_Addr.SetNodeID(NodeID);


	m_SIPCallOutList.push_back(SIP_Addr);

	INFO_LOG(0,"IP:%s,Port:%u,UserName:%s,Passwd:%s,NodeID:%d,Proxy:%s,SIPCallOutList size :%u",
		SIP_Addr.GetIpv4Add(),SIP_Addr.GetUdpPort(),SIP_Addr.GetUserName(),SIP_Addr.GetPassWord(),NodeID,Proxy,m_SIPCallOutList.size());

	return 0;
}

void KFPC_TrunkGroup::SetIPChannelInService()
{
	

	//if(m_SIPServer)
	{
		INFO_LOG(0,"TrunkName:%s",m_Name);

		ChannelBlock_t::iterator	BeginIter = m_ChannelBlockList.begin();

		for(;BeginIter != m_ChannelBlockList.end();BeginIter++)
		{
			CChannelBlock& ChannelBlock = (*BeginIter);

			ChannelBlock.SetIPChannelInService();

		}
	}

}

void KFPC_TrunkGroup::UpdateTrunkGroup()
{

	KFPC_APPID_ListIter	BeginIter = m_WatchAppIDList.begin();

	for(;BeginIter != m_WatchAppIDList.end();BeginIter++)
	{
		unsigned int AppID = (*BeginIter);
		
		KFCPTServerAPIHandlerImpInstance->SendTS_EVT_UpdateTrunkGroup(AppID,
			m_Name);

	}
}

void KFPC_TrunkGroup::log()
{

	INFO_LOG(0,
				"Name:%s,"
				"Description:%s,"	
				"CallerNOA:%u,"
				"CalledNOA:%u,"
				"AutoAnswer:%u,"
				"AddPrefix:%s,"
				"StripPrefix:%s,"
				//"SIPServer:%u,"
				"LocalRtp:%s,"
				"Support183:%s"
				,
				m_Name,
				m_Description,
				m_CallerNOA,
				m_CalledNOA,
				m_AutoAnswer,
				m_AddPrefix.c_str(),
				m_StripPrefix.c_str(),
				//m_SIPServer,
				((m_LocalRtp == LocalRtp_Relay)?"EH":"MediaServer"),
				(m_Support183)?"Enable":"Disable");


}
