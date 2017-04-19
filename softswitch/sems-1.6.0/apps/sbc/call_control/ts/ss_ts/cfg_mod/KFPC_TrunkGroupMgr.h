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
	 * @brief 		����м���
	 * @param[in,out] const char * szName
	 * @return   	KFPC_TrunkGroup *
	 */
	KFPC_TrunkGroup *  AddTrunkGroup(const char *szName);
	/**
	 * FullName:  	KFPC_TrunkGroupMgr::DelTrunkGroup
	 * @brief 		ɾ���м���
	 * @param[in,out] const char * szName
	 * @return   	int
	 */
	unsigned int  DelTrunkGroup(const char *szName);
	/**
	 * FullName:  	KFPC_TrunkGroupMgr::DelAllTrunkGroup
	 * @brief 		ɾ�������м���
	 * @return   	void
	 */
	void DelAllTrunkGroup();
	unsigned int  GetCount();
	
	KFPC_TrunkGroup *GetTrunkGroupByName(const char *pTrunkGroupName);
	bool CheckTrunkGroupByName(const char *pTrunkGroupName);
	/**
	 * FullName:  	KFPC_TrunkGroupMgr::GetIdleChannelByName
	 * @brief 		ͨ���м�������ÿ���ͨ����
	 * @param[in,out] const char * pTrunkGroupName
	 * @param[in,out] KFPC_ChMgr & ChMgr
	 * @param[in,out] unsigned int * IdleChannel
	 * @return   	int
	 */
	unsigned int GetIdleChannelByName(const char *pTrunkGroupName, unsigned int *IdleChannel);
	/**
	 * FullName:  	KFPC_TrunkGroupMgr::GetIdleChannelByNameEx
	 * @brief 		��ѯ����ͨ������Դͨ����
	 * @param[in,out] unsigned long SrcChannel		Դͨ��
	 * @param[in,out] const char * pTrunkGroup
	 * @param[in,out] KFPC_ChMgr & ChannelList
	 * @param[in,out] unsigned long * IdleChannel
	 * @return   	int
	 */
	unsigned int GetIdleChannelByNameEx(const char *pTrunkGroupName,  unsigned int *IdleChannel,unsigned int SrcChannel = -1);

	/**
	 * FullName:  	KFPC_TrunkGroupMgr::GetTrunkGroupByChannelID
	 * @brief 		����ͨ���ҵ��м���,��Ҫ���ں������߶�λ�м���,IP��������ȡ�����˺���Ϣ
	 * @param[in,out] unsigned int ChannelID
	 * @return   	KFPC_TrunkGroup*
	 */
	KFPC_TrunkGroup* GetTrunkGroupByChannelID(unsigned int ChannelID);
	/**
	 * FullName:  	KFPC_TrunkGroupMgr::GetTrunkGroupByIP
	 * @brief 		����IP��λ�м���
	 * @param[in,out] char * Ip
	 * @return   	KFPC_TrunkGroup*
	 */
	KFPC_TrunkGroup* GetTrunkGroupByIP(const char* Ip);
	
	/**
	 * FullName:  	KFPC_TrunkGroupMgr::PreLoadCfg
	 * @brief 		׼����������
	 * @return   	void
	 */
	void PreLoadCfg();
	/**
	 * FullName:  	KFPC_TrunkGroupMgr::EndLoadCfg
	 * @brief 		������������
	 * @return   	void
	 */
	void EndLoadCfg();

	/**
	 * FullName:  	KFPC_TrunkGroupMgr::Send_EVT_UpdateTrunkGroup
	 * @brief 		����TrunkGroup ��Ӧ��
	 * @param[in,out] unsigned int AppID
	 * @return   	void
	 */
	void Send_EVT_UpdateTrunkGroup(unsigned int AppID);

	void DelWatchAppID(unsigned int AppID);

	void SetIPChannelInService(void);

	void UpdateTrunkGroup();
};


