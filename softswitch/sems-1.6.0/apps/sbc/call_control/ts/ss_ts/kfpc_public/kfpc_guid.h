#ifndef kfpc_guid_h__
#define kfpc_guid_h__
#include "kfpc_sn64.h"
#include "kfpc_time.h"
#include "kfpc_getmac.h"
#include "kfpc_msg.h"
#ifdef WIN32
#pragma warning (disable: 4996) 
#endif

typedef struct GUID64
{
	unsigned long long H_GUID;
	unsigned long long L_GUID;
}GUID64;

class KFPC_GUID
{
private:
	KFPC_Time	m_MyTime;
	char		m_MacList[KFPC_MAX_INTERFACE_COUNT][MAXMACLEN];
	char		m_ethNameList[KFPC_MAX_INTERFACE_COUNT][MAXethNameLen];
	char		m_InterfaceIP[KFPC_MAX_INTERFACE_COUNT][MAXethNameLen];
	unsigned int m_InterfaceCount;
	char		m_AppName[KFPC_API_NAME_MAX_LEN];
public:
	KFPC_GUID(void);
	~KFPC_GUID(void);

	static KFPC_GUID* GetInstance()
	{
		static KFPC_GUID	kfpc_guid;
		return &kfpc_guid;
	}

	void Open(const char* pAppName){strncpy(m_AppName,pAppName,KFPC_API_NAME_MAX_LEN-1);}

	void GetGUID(unsigned char* pGuid);
	void GetHostID(unsigned char* pHostID);
};

#define  KFPCGuidInstance	KFPC_GUID::GetInstance()

#endif // kfpc_guid_h__
