#pragma once
class KFPC_CallAlarmMgr
{
private:
	unsigned long long	m_IVRAlarmSN;
	unsigned int		m_IVRAlarmCount;	
	unsigned long long	m_VOIPAlarmSN;
	unsigned int		m_VOIPAlarmCount;	

	unsigned long long	m_LicAlarmSN;
	unsigned int		m_LicAlarmCount;	
public:
	KFPC_CallAlarmMgr(void);
	virtual ~KFPC_CallAlarmMgr(void);

	static KFPC_CallAlarmMgr* GetInstance()
	{
		static KFPC_CallAlarmMgr _Instance;
		return &_Instance;
	}

	void AppStartMsg(const char* pStr);
	void IVRAlarm(unsigned int ChID,const char* pStr);
	void IVRAlarmRecovery();
	void VOIPAlarm(unsigned int ChID,const char* pStr);
	void VOIPAlarmRecovery();

	void LicAlarm(const char* pStr);
	void LicAlarmRecovery();
};

#define KFPC_CallAlarmMgr_Instance	KFPC_CallAlarmMgr::GetInstance()