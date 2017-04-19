#pragma once

class KFPC_TSLicSer
{
private:
	unsigned int	m_SN;
	unsigned int	m_AppID;

	unsigned short	m_AgChCount;			//模拟通道数
	unsigned short	m_SpanChCount;			//数字中继数
	unsigned short	m_VoipChCount;			//Voip通道数
	unsigned short	m_IVRChCount;			//IVR通道数

public:
	KFPC_TSLicSer(void);
	~KFPC_TSLicSer(void);


	unsigned short GetAgChCount() const { return m_AgChCount; }
	void SetAgChCount(unsigned int val) { m_AgChCount = val; }

	unsigned short GetSpanChCount() const { return m_SpanChCount; }
	void SetSpanChCount(unsigned int val) { m_SpanChCount = val; }

	unsigned short GetVoipChCount() const { return m_VoipChCount; }
	void SetVoipChCount(unsigned int val) { m_VoipChCount = val; }
	
	unsigned short GetIVRChCount() const { return m_IVRChCount; }
	void SetIVRChCount(unsigned int val) { m_IVRChCount = val; }

	unsigned int GetAppID() const { return m_AppID; }
	void SetAppID(unsigned int val) { m_AppID = val; }

	unsigned int GetSN() { return m_SN; }
	void SetSN(unsigned int val) { m_SN = val; }

	void OpenLicSer();
};


