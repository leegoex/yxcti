#pragma once

#include "KFPC_TrunkGroup.h"
//#include "KFPC_ChMgr.h"

class KFPC_TrunkGroupMgr
{
public:
	KFPC_TrunkGroupMgr();
	~KFPC_TrunkGroupMgr();

private:
	TrunkGroupList_t m_TrunkGroupList;



public:
	/**
	 * FullName:  	KFPC_TrunkGroupMgr::AddTrunkGroup
	 * @brief 		添加中继组
	 * @param[in,out] const char * szName
	 * @return   	KFPC_TrunkGroup *
	 */
	KFPC_TrunkGroup *  AddTrunkGroup(const char *szName);
	/**
	 * FullName:  	KFPC_TrunkGroupMgr::DelTrunkGroup
	 * @brief 		删除中继组
	 * @param[in,out] const char * szName
	 * @return   	int
	 */
	unsigned int  DelTrunkGroup(const char *szName);
	/**
	 * FullName:  	KFPC_TrunkGroupMgr::DelAllTrunkGroup
	 * @brief 		删除所有中继组
	 * @return   	void
	 */
	void DelAllTrunkGroup();
	unsigned int  GetCount();
	
	KFPC_TrunkGroup *GetTrunkGroupByName(const char *pTrunkGroupName);
	bool CheckTrunkGroupByName(const char *pTrunkGroupName);
	/**
	 * FullName:  	KFPC_TrunkGroupMgr::GetIdleChannelByName
	 * @brief 		通过中继组名获得空闲通道号
	 * @param[in,out] const char * pTrunkGroupName
	 * @param[in,out] KFPC_ChMgr & ChMgr
	 * @param[in,out] unsigned int * IdleChannel
	 * @return   	int
	 */
	unsigned int GetIdleChannelByName(const char *pTrunkGroupName, unsigned int *IdleChannel);
	/**
	 * FullName:  	KFPC_TrunkGroupMgr::GetIdleChannelByNameEx
	 * @brief 		查询空闲通道根据源通道号
	 * @param[in,out] unsigned long SrcChannel		源通道
	 * @param[in,out] const char * pTrunkGroup
	 * @param[in,out] KFPC_ChMgr & ChannelList
	 * @param[in,out] unsigned long * IdleChannel
	 * @return   	int
	 */
	unsigned int GetIdleChannelByNameEx(const char *pTrunkGroupName,  unsigned int *IdleChannel,unsigned int SrcChannel = -1);

	/**
	 * FullName:  	KFPC_TrunkGroupMgr::GetTrunkGroupByChannelID
	 * @brief 		根据通道找到中继组,主要用于呼叫入线定位中继组,IP呼出，提取呼叫账号信息
	 * @param[in,out] unsigned int ChannelID
	 * @return   	KFPC_TrunkGroup*
	 */
	KFPC_TrunkGroup* GetTrunkGroupByChannelID(unsigned int ChannelID);
	/**
	 * FullName:  	KFPC_TrunkGroupMgr::GetTrunkGroupByIP
	 * @brief 		根据IP定位中继组
	 * @param[in,out] char * Ip
	 * @return   	KFPC_TrunkGroup*
	 */
	KFPC_TrunkGroup* GetTrunkGroupByIP(const char* Ip);
	
	/**
	 * FullName:  	KFPC_TrunkGroupMgr::PreLoadCfg
	 * @brief 		准备加载配置
	 * @return   	void
	 */
	void PreLoadCfg();
	/**
	 * FullName:  	KFPC_TrunkGroupMgr::EndLoadCfg
	 * @brief 		结束加载配置
	 * @return   	void
	 */
	void EndLoadCfg();

	/**
	 * FullName:  	KFPC_TrunkGroupMgr::Send_EVT_UpdateTrunkGroup
	 * @brief 		发送TrunkGroup 到应用
	 * @param[in,out] unsigned int AppID
	 * @return   	void
	 */
	void Send_EVT_UpdateTrunkGroup(unsigned int AppID);

	void DelWatchAppID(unsigned int AppID);

	void SetIPChannelInService(void);

	void UpdateTrunkGroup();
};


