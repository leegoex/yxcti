#ifndef KFPC_TrunkGroup_h__
#define KFPC_TrunkGroup_h__

#include <vector>
#include <list>
#include "kfpc_msg.h"
#include "KFPC_ContactCenterPublicDef.h"
#include "KFPC_TServerDef.h"
#include "KFPC_ChMgr.h"

#include <string>

using namespace std ;

typedef enum SipCallOutMode_t
{
	CallOutMode_StandBy,				//冗余
	CallOutMode_MultiCall				//同时呼
}SipCallOutMode_t;

typedef enum LocalRtp_t
{
	LocalRtp_NoRtp,
	LocalRtp_Relay,
	LocalRtp_Transcoding
}LocalRtp_t;


class KFPC_SIP_Addr
{
private:
	char			m_PassWord[KFPC_PASSWD_LEN];	
	char			m_Ipv4Add[KFPC_MAX_IP_LEN];
	unsigned int	m_Mask;
	char			m_UserName[KFPC_USER_NAME_LEN];
	unsigned short	m_UdpPort;
	//char			m_FirewallIP[KFPC_FAX_IP_LEN];
	char			m_Proxy[KFPC_MAX_IP_LEN];
	int			m_NodeID;

public:
	KFPC_SIP_Addr(){Init();}
	void Init();

	int GetNodeID()  { return m_NodeID; }
	void SetNodeID( int val) { m_NodeID = val; }

	const char* GetIpv4Add() { return m_Ipv4Add; }
	void SetIpv4Add(const char* val) {  if(val != NULL) 	strncpy(m_Ipv4Add, val,KFPC_MAX_IP_LEN-1); }

	//unsigned int& GetIpv4Add() { return m_Ipv4Add; }
	//void SetIpv4Add(unsigned int val) { m_Ipv4Add = val; }
	
	unsigned int& GetMask() { return m_Mask; }
	void SetMask(unsigned int val);

	unsigned short& GetUdpPort();
	void SetUdpPort(unsigned short val);


	char* GetUserName() { return m_UserName; }
	void SetUserName(const char* val);



	char* GetPassWord() { return m_PassWord; }
	void SetPassWord(const char* val) {  if(val != NULL) strncpy(m_PassWord,val,KFPC_PASSWD_LEN-1); }

	//char* GetFirewallIP()  { return m_FirewallIP; }
	//void SetFirewallIP(const char* val) { if(val != NULL) strncpy(m_FirewallIP,val,KFPC_FAX_IP_LEN);  }
	char* GetProxy()  { return m_Proxy; }
	void SetProxy(const char* val);
	void Log();
};

/*****************************************************/
/* 路由组中的一块                                    */
/*                                                   */
/*****************************************************/
class CChannelBlock
{
public:
	CChannelBlock();
	~CChannelBlock();

private:
	unsigned int m_BeginSpan;				//开始中继
	unsigned int m_BeginChannel;			//开始通道
	unsigned int m_EndSpan;					//结束中继
	unsigned int m_EndChannel;				//结束通道
	KFPC_QueryIdleChType m_QueryIdleType;				//查询空闲通道方式
														//0 "W"型(纵向查找), 1 "Z"型(横向查找)
	unsigned int m_LastSpan;
	unsigned int m_LastChannel;	

public:
	unsigned int GetBeginSpan()    { return m_BeginSpan;    }
	unsigned int GetBeginChannel() { return m_BeginChannel; }
	unsigned int GetEndSpan()      { return m_EndSpan;      }
	unsigned int GetEndChannel()   { return m_EndChannel;   }
	unsigned int GetIdleType()	   { return m_QueryIdleType;	  }
	unsigned int GetLastSpan(void){return m_LastSpan;}
	unsigned int GetLastChannel(void){return m_LastChannel;}

	void SetBeginSpan(unsigned int unBeginSpan)       { m_LastSpan = m_BeginSpan   = unBeginSpan;   }
	void SetBeginChannel(unsigned int unBeginChannel) { m_LastChannel = m_BeginChannel = unBeginChannel; }
	void SetEndSpan(unsigned int unEndSpan)	          { m_EndSpan      = unEndSpan;      }
	void SetEndChannel(unsigned int unEndChannel)     { m_EndChannel   = unEndChannel;   }
	void SetIdleType(KFPC_QueryIdleChType IdleType)		  { m_QueryIdleType     = IdleType;	   }

	void SetLastSpan(unsigned int value){m_LastSpan = value;}
	void SetLastChannel(unsigned int value){m_LastChannel = value;}
	void SetIPChannelInService();

	void Log();
};

typedef vector<CChannelBlock>		ChannelBlock_t;
typedef list<KFPC_SIP_Addr>			KFPC_SIP_Addr_List;
typedef list<unsigned int>			KFPC_AudioCode_List;

typedef list<unsigned int>			KFPC_APPID_List;
typedef	KFPC_APPID_List::iterator	KFPC_APPID_ListIter;

/*****************************************************/
/* 路由组                                            */
/*                                                   */
/*****************************************************/
class KFPC_TrunkGroup
{
public:
	KFPC_TrunkGroup();
	~KFPC_TrunkGroup();

private:
	KFPC_APPID_List		m_WatchAppIDList;
	

	char				m_Name[KFPC_TRUNKGROUP_NAME_LEN];	//中继组名	
	char				m_Description[KFPC_TRUNKGROUP_DESC_LEN];

	unsigned int		m_LastSpan;				//保留最后查询的位置
	unsigned int		m_LastChannel;
	unsigned int        m_BlockIndex;				//记录route Block的索引
	bool				m_AutoAnswer;			//自动认应
	string				m_AddPrefix;
	string				m_StripPrefix;
	//unsigned int		m_SIPServer;
	LocalRtp_t			m_LocalRtp;

	unsigned char		m_CallerNOA;
	unsigned char		m_CalledNOA;
	bool				m_Support183;

	unsigned int	LookupIdleChannelInBlockWithW(KFPC_ChMgr &ChMgr,unsigned int* IdleChannel,CChannelBlock * pBlock);
	void SetLastChannelWithW( unsigned char nChannel,  unsigned short nSpan,  CChannelBlock * pBlock);

	unsigned int	LookupIdleChannelInBlockWithZ(KFPC_ChMgr &ChMgr,unsigned int* IdleChannel,CChannelBlock * pBlock);
	void SetLastChannelWithZ( unsigned char nChannel, unsigned short nSpan, CChannelBlock * pBlock );

	unsigned int	LookupIdleChannelInBlockWithOdd(KFPC_ChMgr &ChMgr,unsigned int* IdleChannel,CChannelBlock * pBlock);
	void SetLastChannelWithOdd( unsigned char nChannel,unsigned short nSpan, CChannelBlock * pBlock );

	unsigned int	LookupIdleChannelInBlockWithEven(KFPC_ChMgr &ChMgr,unsigned int* IdleChannel,CChannelBlock * pBlock);
	void SetLastChannelWithEvent(unsigned char nChannel, unsigned short nSpan, CChannelBlock * pBlock);

	bool				m_Old;					/**< 旧的，当标志为true时，将被删除 */

public:
	LocalRtp_t	SetLocalRtp(const char* str)
	{
		if(strcmp(str,"EH") == 0)
		{
			m_LocalRtp = LocalRtp_Relay;
			return LocalRtp_Relay;
		}
		else if(strcmp(str,"MediaServer") == 0)
		{
			m_LocalRtp = LocalRtp_Transcoding;
			return LocalRtp_Transcoding;
		}
		else
		{
			m_LocalRtp = LocalRtp_NoRtp;
			return LocalRtp_NoRtp;
		}
	}


	LocalRtp_t GetLocalRtp() const { return m_LocalRtp; }
	void SetLocalRtp(LocalRtp_t val) { m_LocalRtp = val; }


	//unsigned int GetSIPServer() const { return m_SIPServer; }
	//void SetSIPServer(unsigned int val) { m_SIPServer = val; }


	const char* GetAddPrefix() const { return m_AddPrefix.c_str(); }
	void SetAddPrefix(const char* val) { m_AddPrefix = val; }

	const char* GetStripPrefix() const { return m_StripPrefix.c_str(); }
	void SetStripPrefix(const char* val) { m_StripPrefix = val; }


	bool GetAutoAnswer() const { return m_AutoAnswer; }
	void SetAutoAnswer(bool val) { m_AutoAnswer = val; }

	bool GetOld() { return m_Old; }
	void SetOld(bool val) { m_Old = val; }

	//以下是VOIP路由参数
	KFPC_SIP_Addr_List		m_SIPCallOfferList;			/**< 呼叫来电话的IP */
	KFPC_SIP_Addr_List		m_SIPCallOutList;			/**< 呼叫来电话的IP */
	KFPC_SIP_Addr_List& GetSIPCallOutList() { return m_SIPCallOutList; }

	//KFPC_SIP_Addr			m_SIPCallOut;				/**< 呼叫呼出网关 */
	KFPC_AudioCode_List		m_AudioCodeList;		/**< 编码地址 */
	SipCallOutMode_t		m_SipCallOutMode;		/**< SIP 外呼模式 */

	ChannelBlock_t			m_ChannelBlockList;		/**< 通道块例表 */

	CChannelBlock*	GetCurrentBlock();

	size_t	GetChannelBlockCount();								/**< 获得到通道块的数量 */
	char*		GetName()				{ return m_Name;       }
	const char*		GetDescription()		{ return m_Description;       }
	
	unsigned int	GetLastSpan()	{ return m_LastSpan;   }
	unsigned int	GetLastChannel(){ return m_LastChannel;}

	void  SetLastSpan(unsigned int unSpan)          { m_LastSpan = unSpan; }
	void  SetLastChannel(unsigned int unChannel)    { m_LastChannel = unChannel; }

	unsigned int GetBlockIndex() { return m_BlockIndex; }

	void		 SetBlockIndex(unsigned int unBlockIndex);
	/**
	 * FullName:  	KFPC_TrunkGroup::SetNextBlockIndex
	 * @brief 		设置下一个通道块
	 * @param[in,out] void
	 * @return   	void
	 */
	void		SetNextBlockIndex(void);
	void		SetName(const char *szName) { strncpy(m_Name, szName, KFPC_TRUNKGROUP_NAME_LEN - 1); }
	void		SetDescription(const char *szDescription) { strncpy(m_Description, szDescription, KFPC_TRUNKGROUP_DESC_LEN - 1); }
    void Init(void);

	bool GetSupport183() const { return m_Support183; }
	void SetSupport183(bool val) { m_Support183 = val; }
public:
	
	/**
	 * FullName:  	CChannelGroup::AddRouteBlock
	 * @brief 		添加路由块
	 * @param[in,out] unsigned int unBeginSpan
	 * @param[in,out] unsigned int unBeginChannel
	 * @param[in,out] unsigned int unEndSpan
	 * @param[in,out] unsigned int unEndChannel
	 * @param[in,out] KFPC_QueryIdleChType IdleType
	 * @return   	int
	 */
	int	AddRouteBlock(unsigned int unBeginSpan, 
						unsigned int unBeginChannel, 
						unsigned int unEndSpan, 
						unsigned int unEndChannel,
						KFPC_QueryIdleChType IdleType);

	int AddFromAddrBlock(const char* Ip,const char* pMask,unsigned short	Port,const char*	pUserName,const char*	pPassWord);

	int AddCallOutAddrBlock(const char* Ip,unsigned short	Port,const char*	pUserName,const char*	pPassWord ,int NodeID,const char* Proxy);

	KFPC_SIP_Addr* QueryFromAddr(const char* pIpAddr);

	int SetToAddr(const char* Ip,const char* pMask,unsigned short	Port,const char*	pUserName,const char*	pPassWord);
	//KFPC_SIP_Addr* GetToAddr(){	return &m_SIPCallOut;}
	
	void AddAudioCode(unsigned int AudioCode);
	KFPC_AudioCode_List& AudioCodeList();

	bool GetAllCodeList(unsigned char CodeIdList[], unsigned char* pCodeCount);

	/**
	 * FullName:  	KFPC_TrunkGroupMgr::GetIdleChannelByNameEx
	 * @brief 		查询空闲通道根据源通道号
	 * @param[in,out] unsigned int SrcChannel		源通道
	 * @param[in,out] KFPC_ChMgr & ChannelList
	 * @param[in,out] unsigned int * IdleChannel
	 * @return   	int
	 */
	unsigned int GetIdleChannel(unsigned int SrcChannel, unsigned int *IdleChannel);

	unsigned int LookupIdleChannel( CChannelBlock * pBlock, unsigned int * IdleChannel );

	/**
	 * FullName:  	KFPC_TrunkGroup::AddWatchAppID
	 * @brief 		添加watch app 的ID
	 * @param[in,out] unsigned int AppID
	 * @return   	void
	 */
	void AddWatchAppID(unsigned int AppID);
	/**
	 * FullName:  	KFPC_TrunkGroup::DelWatchAppID
	 * @brief 		添加watch app id
	 * @param[in,out] unsigned int AppID
	 * @return   	void
	 */
	void DelWatchAppID(unsigned int AppID);
	unsigned int GetCallOfferAppID(unsigned int ChID);	/**< 循环使用APPID */

	void Clear();

	SipCallOutMode_t GetSipCallOutMode() const { return m_SipCallOutMode; }
	void SetSipCallOutMode(SipCallOutMode_t val) { m_SipCallOutMode = val; }

	void SetIPChannelInService();
	void UpdateTrunkGroup();
	unsigned char GetCallerNOA() const { return m_CallerNOA; }
	void SetCallerNOA(unsigned char val) { m_CallerNOA = val; }
	unsigned char GetCalledNOA() const { return m_CalledNOA; }
	void SetCalledNOA(unsigned char val) { m_CalledNOA = val; }
	void log();
};

typedef vector<KFPC_TrunkGroup>				TrunkGroupList_t;
typedef vector<KFPC_TrunkGroup>::iterator	TrunkGroupIterator_t;
#endif // KFPC_TrunkGroup_h__



