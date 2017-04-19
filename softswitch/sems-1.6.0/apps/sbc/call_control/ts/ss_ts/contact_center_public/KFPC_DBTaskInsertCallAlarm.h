#pragma once
#include "kfpc_sn64.h"
#include "KFPC_ContactCenterPublicDef.h"
#include "kfpc_api.h"
#include "kfpc_msg.h"
#include "KFPC_API_Handle.h"
#include "KFPC_DBTask.h"
#include "KFPC_DBAccessInfo.h"
class KFPC_DBTaskInsertCallAlarm :
	public KFPC_DBTask
{
public:
	KFPC_DBTaskInsertCallAlarm(unsigned long long SN,unsigned long long CallID,unsigned InOutFlag,const char* Caller,const char* Called,const char* Info,DB_TYPE DBType)
	{
		if (DBType == DB_MySql) 
		{
			m_TimeFunction = "NOW()";
		}
		else
		{
			m_TimeFunction = "GetDate()";
		}

		KFPC_LIB_PARAMS*	LibParam  = KFPC_GetLibParam();
		unsigned int APPID = LibParam->AppInfo.AppID;

		char szInsertSQL[KFPC_MAX_SQL_STR]="";

		snprintf(szInsertSQL,KFPC_MAX_SQL_STR-1,"INSERT INTO TBL_PBX_CALL_ALARM(SN,APPID,APPNAME,CALLID,IN_OUT_FLAG,CALLER,CALLED,INFO,UPDATETIME,RECOVERYTIME,ALARMCOUNT)VALUES(%llu,%u,'%s',%llu,%u,'%s','%s',\"%s\",%s,%s,1);",
			SN,APPID,LibParam->AppInfo.AppName,CallID,InOutFlag,Caller,Called,Info,m_TimeFunction.c_str(),m_TimeFunction.c_str());
		m_InsertSQL = szInsertSQL;

	}

	KFPC_DBTaskInsertCallAlarm(unsigned long long SN,unsigned int AlarmCount,DB_TYPE DBType)
	{
		if (DBType == DB_MySql) 
		{
			m_TimeFunction = "NOW()";
		}
		else
		{
			m_TimeFunction = "GetDate()";
		}

		KFPC_LIB_PARAMS*	LibParam  = KFPC_GetLibParam();
		unsigned int APPID = LibParam->AppInfo.AppID;

		char szInsertSQL[KFPC_MAX_SQL_STR]="";

		snprintf(szInsertSQL,KFPC_MAX_SQL_STR-1,"UPDATE tbl_pbx_call_alarm SET RECOVERYTIME = %s, ALARMCOUNT = %u WHERE SN = %llu ;",
			m_TimeFunction.c_str(),AlarmCount,SN);
		m_InsertSQL = szInsertSQL;

	}

	~KFPC_DBTaskInsertCallAlarm(){}
	void* Svc()
	{
		if (!GetDataBaseAccess()->ExecuteSql(m_InsertSQL.c_str()))
		{
			//WARNING_LOG(0,"ExecuteSql Error (%s).",m_InsertSQL.c_str());		
		}
		return 0;
	}

private:
	string	m_InsertSQL;
	string	m_TimeFunction;

};
