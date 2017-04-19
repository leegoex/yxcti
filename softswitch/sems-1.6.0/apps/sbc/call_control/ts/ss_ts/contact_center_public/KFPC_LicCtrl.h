#pragma once
class KFPC_LicCtrl
{
protected:
	unsigned int		m_LicSize;		//lic 数
	unsigned int		m_UseSize;		//当前使用数

public:
	KFPC_LicCtrl(void);
	~KFPC_LicCtrl(void);

	unsigned int GetUseSize() { return m_UseSize; }
	//void SetUseSize(unsigned int val) { m_UseSize = val; }

	unsigned int GetLicSize() { return m_LicSize; }
	void SetLicSize(unsigned int val) { m_LicSize = val; }	

	void Reset();
};

