#include "KFPC_DBAccessInfo.h"
#include <string.h>
#include "kfpc_logex.h"
#include "apr_general.h"

KFPC_DBAccessInfo::KFPC_DBAccessInfo(void):
m_SQLDebug(0),
m_PoolSize(1),
m_DBType(DB_MySql)
{
	memset(m_DataSource,0,KFPC_MAX_FILE_NAME);
	memset(m_UserName,0,KFPC_USER_NAME_LEN);
	memset(m_Passwd,0,KFPC_PASSWD_LEN);
	memset(m_DataBaseType,0,KFPC_USER_NAME_LEN);
	
}


KFPC_DBAccessInfo::~KFPC_DBAccessInfo(void)
{
}

int KFPC_DBAccessInfo::SetDataSource(const char *pVal)
{
	if(pVal == NULL)
	{
		return -1;
	}
	else
	{
		strncpy(m_DataSource,pVal,KFPC_MAX_FILE_NAME);
		return 0;
	}
}

char* KFPC_DBAccessInfo::GetDataSource()
{
	return m_DataSource;
}

int KFPC_DBAccessInfo::SetDBUserName(const char *pVal)
{
	if(pVal == NULL)
	{
		return -1;
	}
	else
	{
		strncpy(m_UserName,pVal,KFPC_USER_NAME_LEN);
		return 0;
	}
}

const char* KFPC_DBAccessInfo::GetDBUserName()
{
	return m_UserName;
}

int KFPC_DBAccessInfo::SetPasswd(const char *pVal)
{
	if(pVal == NULL)
	{
		return -1;
	}
	else
	{
		strncpy(m_Passwd,pVal,KFPC_PASSWD_LEN);
		return 0;
	}
}

char* KFPC_DBAccessInfo::GetPasswd()
{
	return m_Passwd;
}

int KFPC_DBAccessInfo::SetDataBaseType(const char *pVal)
{
	if(pVal == NULL)
	{
		return -1;
	}
	else
	{
		strncpy(m_DataBaseType,pVal,KFPC_USER_NAME_LEN);

		if (strcasecmp(pVal,MsSqlName) == 0) 
		{
			m_DBType = DB_MSSql;
		}
		else if(strcasecmp(pVal,MySqlName) == 0)
		{
			m_DBType = DB_MySql;

		}
		else if(strcasecmp(pVal,OracleName) == 0)
		{
			m_DBType = DB_Oracle;
		}
		else
		{
			m_DBType = DB_MySql;
		}
		return 0;
	}
}
//
//char* KFPC_DBAccessInfo::GetDataBaseType()
//{
//	return m_DataBaseType;
//}

int KFPC_DBAccessInfo::SetPoolSize(unsigned int val)
{
	m_PoolSize = val;
	return 0;
}

unsigned int KFPC_DBAccessInfo::GetPoolSize()
{
	return m_PoolSize;
}

void KFPC_DBAccessInfo::Log()
{
	INFO_LOG(0,"DataSource:%s,UserName:%s,Passwd:%s,DataBaseType:%s,PoolSize:%u,SQLDebug:%u",
		m_DataSource,
		m_UserName,
		m_Passwd,
		m_DataBaseType,
		m_PoolSize,
		m_SQLDebug
		);
}