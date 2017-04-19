#include "md5.h"
#include "kfpc_guid.h"
#include "kfpc_time.h"
#include "kfpc_getmac.h"

KFPC_GUID::KFPC_GUID(void)
{
	memset(m_MacList,0,sizeof(m_MacList));
	memset(m_ethNameList,0,sizeof(m_ethNameList));
	memset(m_InterfaceIP,0,sizeof(m_InterfaceIP));
	m_InterfaceCount = 0;

	GetLocalMac(m_MacList,m_InterfaceIP,m_ethNameList,&m_InterfaceCount,false);
}


KFPC_GUID::~KFPC_GUID(void)
{
}

void KFPC_GUID::GetGUID( unsigned char* pGuid )
{
	KFPC_SN64	m_SN64;

	union
	{
		md5_byte_t		digest[16];
		long long		Num[2];	
	} MD5Code = {0};

	md5_state_t state;
	

	memset(&state,0,sizeof(state));

	md5_init(&state);

	long long SN = m_SN64.GetSN();
	
	Millisecond_t t = m_MyTime.GetNowTime();


	md5_append(&state, (const md5_byte_t *)&SN, sizeof(long long));

	md5_append(&state, (const md5_byte_t *)&t, sizeof(Millisecond_t));

	md5_append(&state, (const md5_byte_t *)m_MacList, sizeof(m_MacList));

	md5_append(&state, (const md5_byte_t *)m_AppName, sizeof(m_AppName));
	
	md5_finish(&state, MD5Code.digest);

	memcpy(pGuid,MD5Code.digest,16);
}

void KFPC_GUID::GetHostID( unsigned char* pHostID )
{
	union
	{
		md5_byte_t		digest[16];
		long long		Num[2];	
	} MD5Code = {0};

	md5_state_t state;


	memset(&state,0,sizeof(state));

	md5_init(&state);

	md5_append(&state, (const md5_byte_t *)m_MacList, sizeof(m_MacList));

	md5_finish(&state, MD5Code.digest);

	memcpy(pHostID,MD5Code.digest,16);
}
