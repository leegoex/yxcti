#pragma once

#include "KFPC_Channel.h"
#include "KFPC_TServerDef.h"
#include "KFPC_ChMgr.h"
#include "KFPC_ConfChannel.h"

class KFPC_ChMgr
{
private:
	static KFPC_ChMgr* _Instance;
public:
	static KFPC_ChMgr* GetInstance();

	KFPC_ChMgr(void);
	virtual ~KFPC_ChMgr(void);
	KFPC_Channel* GetChannel(unsigned long LogicNO);
	
	void Reset(bool log = true);
	void SendCallReleasedMsg(int cause);

	static void Destory();
	
	unsigned int GetIdleConfCh(unsigned int NodeID);
	KFPC_Channel* GetChannelByCallID(unsigned long long& CallID);

		/**
	 * FullName:  	KFPC_BaseCommand::CheckCallID
	 * @brief 		检查CALLID，因为CALLID是时效性，只有当执行时才能判断
	 * @param[in,out] unsigned long long & CallID
	 * @return   	unsigned int
	 */
	unsigned int CheckCallID( unsigned long long& CallID,KFPC_Channel** ppCh );
	unsigned int NotifyCallReleasedWhenNodeReset(unsigned int NodeID);

	void OnAPP_DISCONNECT(unsigned int APPID);

	void CheckInvalidCallID();

	void ChStatusChange(KFPC_Ch_Status Old,KFPC_Ch_Status Now, KFPC_CH_TYPE ChType);
	unsigned int GetStatusCount(KFPC_Ch_Status Val);

	unsigned int GetUsedCount();
	unsigned int GetChUsedCount(unsigned int ChStatMap[]);


	unsigned int GetSIPChUsedCount(){return GetChUsedCount(m_SIPChStatMap);}
	unsigned int GetConfChUsedCount(){return GetChUsedCount(m_ConfChStatMap);}
	
	void LogChStat();
	void LogChTypeStat(unsigned int ChStatMap[],const char* ChannelType);
private:

	unsigned int			m_SIPChStatMap[MAX_STATUS_COUNT];
	unsigned int			m_ConfChStatMap[MAX_STATUS_COUNT];

	KFPC_Channel			m_Channels[KFPC_MAX_CHANNEL_NUMBER];
	KFPC_ConfChannel		m_ConfChannel[KFPC_SINGLE_NODE_MAX_CONF_SPAN];

private:
	void SetChannelType(KFPC_Channel &Channel,unsigned int ChannelID);
	
	
};

#define KFPC_ChMgrInstance	KFPC_ChMgr::GetInstance()

