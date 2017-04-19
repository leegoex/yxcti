#include "KFPC_CallAlarmMgr.h"
#include "KFPC_ContactCenterPublicDef.h"
#include "kfpc_api.h"
#include "KFPC_DBTaskInsertCallAlarm.h"
#include "kfpc_linuxwinapi.h"
#include "KFPC_TServerConfigFile.h"
#include "KFPC_DBThreadPool.h"

KFPC_CallAlarmMgr::KFPC_CallAlarmMgr(void)
{
	m_IVRAlarmSN = 0;
	m_IVRAlarmCount = 0;
	m_VOIPAlarmSN = 0;
	m_VOIPAlarmCount = 0;	

	m_LicAlarmSN = 0;
	m_LicAlarmCount = 0;	
}


KFPC_CallAlarmMgr::~KFPC_CallAlarmMgr(void)
{
}


void KFPC_CallAlarmMgr::IVRAlarm( unsigned int ChID,const char* pStr )
{
	if(m_IVRAlarmSN == 0)
	{

		KFPC_CallID	CallID;
		CallID.CallIDInfo.ChID = ChID;
		CallID.CallIDInfo.AppID = KFPC_GetLibParam()->AppInfo.AppID;
		unsigned long long T = (time(NULL) - KFPC_START_TIME);
		CallID.CallIDInfo.Time = (unsigned int)T;

		m_IVRAlarmSN = CallID.CallID;
		m_IVRAlarmCount ++;

#ifndef TSERVER_NODB

		KFPC_DBTaskInsertCallAlarm* pDBTask = NULL;
		smart_new(KFPC_DBTaskInsertCallAlarm(m_IVRAlarmSN,0,0xff,"","",pStr,SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType()),pDBTask);
		KFPC_DBThreadPoolInstance->PutTask(pDBTask);
#endif
	}
	else
	{
		m_IVRAlarmCount ++;
	}
}

void KFPC_CallAlarmMgr::IVRAlarmRecovery()
{
	if(m_IVRAlarmSN > 0)
	{
#ifndef TSERVER_NODB
		KFPC_DBTaskInsertCallAlarm* pDBTask = NULL;
		smart_new(KFPC_DBTaskInsertCallAlarm(m_IVRAlarmSN,m_IVRAlarmCount,SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType()),pDBTask);
		KFPC_DBThreadPoolInstance->PutTask(pDBTask);
#endif
	}


	m_IVRAlarmSN = 0;
	m_IVRAlarmCount = 0;
}


void KFPC_CallAlarmMgr::VOIPAlarm( unsigned int ChID,const char* pStr )
{
	if(m_VOIPAlarmSN == 0)
	{

		KFPC_CallID	CallID;
		CallID.CallIDInfo.ChID = ChID;
		CallID.CallIDInfo.AppID = KFPC_GetLibParam()->AppInfo.AppID;
		unsigned long long T = (time(NULL) - KFPC_START_TIME);
		CallID.CallIDInfo.Time = (unsigned int)T;

		m_VOIPAlarmSN = CallID.CallID;
		m_VOIPAlarmCount ++;

#ifndef TSERVER_NODB
		KFPC_DBTaskInsertCallAlarm* pDBTask = NULL;
		smart_new(KFPC_DBTaskInsertCallAlarm(m_VOIPAlarmSN,0,0xff,"","",pStr,SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType()),pDBTask);
		KFPC_DBThreadPoolInstance->PutTask(pDBTask);
#endif

	}
	else
	{
		m_VOIPAlarmCount ++;
	}
}
void KFPC_CallAlarmMgr::VOIPAlarmRecovery()
{
	if(m_VOIPAlarmSN > 0)
	{
#ifndef TSERVER_NODB
		KFPC_DBTaskInsertCallAlarm* pDBTask = NULL;
		smart_new(KFPC_DBTaskInsertCallAlarm(m_VOIPAlarmSN,m_VOIPAlarmCount,SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType()),pDBTask);
		KFPC_DBThreadPoolInstance->PutTask(pDBTask);
#endif
	}


	m_VOIPAlarmSN = 0;
	m_VOIPAlarmCount = 0;
}

void KFPC_CallAlarmMgr::AppStartMsg( const char* pStr )
{
	KFPC_CallID	CallID;
	CallID.CallIDInfo.ChID = 0xffff;
	CallID.CallIDInfo.AppID = KFPC_GetLibParam()->AppInfo.AppID;
	unsigned long long T = (time(NULL) - KFPC_START_TIME);
	CallID.CallIDInfo.Time = (unsigned int)T;
#ifndef TSERVER_NODB
	KFPC_DBTaskInsertCallAlarm* pDBTask = NULL;
	smart_new(KFPC_DBTaskInsertCallAlarm(CallID.CallID,0,0xff,"","",pStr,SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType()),pDBTask);
	KFPC_DBThreadPoolInstance->PutTask(pDBTask);
#endif
	
}

void KFPC_CallAlarmMgr::LicAlarm( const char* pStr )
{
	if(m_LicAlarmSN == 0)
	{

		KFPC_CallID	CallID;
		CallID.CallIDInfo.ChID = 0xfffe;
		CallID.CallIDInfo.AppID = KFPC_GetLibParam()->AppInfo.AppID;
		unsigned long long T = (time(NULL) - KFPC_START_TIME);
		CallID.CallIDInfo.Time = (unsigned int)T;

		m_LicAlarmSN = CallID.CallID;
		m_LicAlarmCount ++;

#ifndef TSERVER_NODB
		KFPC_DBTaskInsertCallAlarm* pDBTask = NULL;
		smart_new(KFPC_DBTaskInsertCallAlarm(m_LicAlarmSN,0,0xff,"","",pStr,SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType()),pDBTask);
		KFPC_DBThreadPoolInstance->PutTask(pDBTask);
#endif

	}
	else
	{
		m_LicAlarmCount ++;
	}
}

void KFPC_CallAlarmMgr::LicAlarmRecovery()
{

	if(m_LicAlarmSN > 0)
	{
#ifndef TSERVER_NODB
		KFPC_DBTaskInsertCallAlarm* pDBTask = NULL;
		smart_new(KFPC_DBTaskInsertCallAlarm(m_VOIPAlarmSN,m_VOIPAlarmCount,SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType()),pDBTask);
		KFPC_DBThreadPoolInstance->PutTask(pDBTask);
#endif

	}

	m_LicAlarmSN = 0;
	m_LicAlarmCount = 0;	
}
