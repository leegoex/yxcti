#pragma once

#include "KFPC_ContactCenterPublicDef.h"

typedef enum DB_TYPE
{
	DB_MySql,
	DB_MSSql,
	DB_Oracle
}DB_TYPE;

#define MySqlName	"MySql"
#define MsSqlName	"MSSql"
#define OracleName	"Oracle"

class KFPC_DBAccessInfo
{
private:
	char m_DataSource[KFPC_MAX_FILE_NAME];
	char m_UserName[KFPC_USER_NAME_LEN];
	char m_Passwd[KFPC_PASSWD_LEN];
	char m_DataBaseType[KFPC_USER_NAME_LEN];
 	unsigned int m_PoolSize;
	bool m_SQLDebug;
	DB_TYPE	m_DBType;

public:
	KFPC_DBAccessInfo(void);
	~KFPC_DBAccessInfo(void);
	bool GetSQLDebug() { return m_SQLDebug; }
	void SetSQLDebug(bool val) { m_SQLDebug = val; }

	int SetDataSource(const char *pVal);
	char* GetDataSource();

	int SetDBUserName(const char *pVal);
	const char* GetDBUserName();

	int SetPasswd(const char *pVal);
	char* GetPasswd();

	int SetDataBaseType(const char *pVal);
	//char* GetDataBaseType();
	DB_TYPE GetDBType() const { return m_DBType; }

	int SetPoolSize(unsigned int val);
	unsigned int GetPoolSize();
	void Log();
};

