#pragma once

class KFPC_VoiceSer
{
private:
	unsigned int	m_APPID;				/**< ����Ӧ�õ�ID */
	unsigned int	m_SN;					/**< ��������SN */
	unsigned int	m_PRDID;				/**< PRDID */

public:
	KFPC_VoiceSer(void);
	~KFPC_VoiceSer(void);

	unsigned int GetAPPID() { return m_APPID; }
	void SetAPPID(unsigned int val) { m_APPID = val; }

	unsigned int GetSN() { return m_SN; }
	void SetSN(unsigned int val) { m_SN = val; }

	unsigned int GetPRDID() { return m_PRDID; }
	void SetPRDID(unsigned int val) { m_PRDID = val; }
};

