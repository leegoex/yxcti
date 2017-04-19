#pragma once
#include "kfpc_logex.h"


class KFPC_EHNode
{
private:
	unsigned char	m_ID;
	string			m_MainBoardSN;
	unsigned long long	m_ValidTime;		//有效时间
	unsigned short	m_AgChLicCount;			//模拟通道数
	unsigned short	m_SpanChLicCount;		//数字中继数
	unsigned short	m_VoipChLicCount;		//Voip通道数
	unsigned short	m_IVRChLicCount;		//IVR通道数

	unsigned int	m_TimerID;

public:	
	unsigned int GetTimerID() { return m_TimerID; }
	void SetTimerID(unsigned int val) { m_TimerID = val; }

	unsigned short GetIVRChLicCount();
	void SetIVRChLicCount(unsigned short val);

	unsigned short GetVoipChLicCount() { return m_VoipChLicCount; }
	void SetVoipChLicCount(unsigned short val);

	unsigned short GetSpanLicChCount() { return m_SpanChLicCount; }
	void SetSpanChLicCount(unsigned short val);

	unsigned short GetAgChLicCount() { return m_AgChLicCount; }
	void SetAgChLicCount(unsigned short val);

	//time_t GetValidTime() { return m_ValidTime; }
	void SetValidTime(unsigned long long val) { m_ValidTime = val; }

	const char* GetMainBoardSN() { return m_MainBoardSN.c_str(); }
	void SetMainBoardSN(const char* val) { m_MainBoardSN = val; }

	unsigned char GetID() { return m_ID; }
	void SetID(unsigned char val) { m_ID = val; }

	//KFPC_SipChMgr	m_SipChMgr;
	//KFPC_VOIPMgr	m_VOIPMgr;
	//KFPC_DTIChMgr	m_DTIChMgr;
	//KFPC_ConfMgr	m_ConfMgr;
	//KFPC_AGChMgr	m_AGChMgr;
	//KFPC_VoiceMgr	m_VoiceMgr;

	KFPC_EHNode(void);

	void SetInfinityValidTime();
	void SetInfinityLic();
	~KFPC_EHNode(void);

	void Reset(bool log = true);
	void Working();
	//void SetIpChInService(unsigned int  MaxSip = -1);
	//void ResetIpCh();
	//void SetConfInService();

	void GetBrdInfo();
	void GetLic(unsigned int SN);
	void SetTimer(unsigned int TimeOut = 600,unsigned int SN=0);

	bool CheckLicValidTime();

};

