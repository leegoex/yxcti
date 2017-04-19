#pragma once
#include<string>
using namespace std;
#include "KFPC_ThreadTask.h"
#include "DataBaseAccess.h"

class KFPC_DBTask :
	public KFPC_ThreadTask
{
private:
	CDataBaseAccess*	m_DataBaseAccess;
	string				m_Sql;
	bool				m_Query;
	bool				m_SQLDebug;

public:	
	CDataBaseAccess* GetDataBaseAccess() { return m_DataBaseAccess; }
	void SetDataBaseAccess(CDataBaseAccess* val) { m_DataBaseAccess = val; }

	const char* GetSql() const { return m_Sql.c_str(); }
	void SetSql(const char* val) { m_Sql = val; }

	bool GetQuery() const { return m_Query; }
	void SetQuery(bool val) { m_Query = val; }
	KFPC_DBTask();
	virtual ~KFPC_DBTask(void);

	bool GetSQLDebug() const { return m_SQLDebug; }
	void SetSQLDebug(bool val) { m_SQLDebug = val; }
	virtual void* Svc();
};

