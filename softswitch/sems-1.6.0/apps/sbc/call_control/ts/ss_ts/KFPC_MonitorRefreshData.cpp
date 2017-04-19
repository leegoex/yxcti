#include "KFPC_MonitorRefreshData.h"
#include "KFPC_ContactCenterPublicDef.h"
#include "kfpc_linuxwinapi.h"
#include "kfpc_api.h"
#include "KFPC_DBTask.h"
#include "KFPC_DBThreadPool.h"
#include "kfpc_logex.h"
#include "KFPC_StringUtils.h"
#include "KFPC_TServerConfigFile.h"


KFPC_MonitorRefreshData::KFPC_MonitorRefreshData(void):
m_TimeStamp(time(NULL)),
m_ClearTimeStamp(0)
{
	ClearIVRCh();
	ClearVOIPCh();
	ClearCh();
	
	m_LastChStat = -1;
	m_ChChangeCount = 0;

	m_IVRStat = 0;
	m_LastIVRStat = -1;
	m_IVRChangeCount = 0;

	m_VOIPStat = 0;
	m_LastVOIPStat = -1;
	m_VOIPChangeCount = 0;

	m_MaxChStat = 0;
	m_MaxIVRStat = 0;
	m_MaxVOIPStat = 0;


	m_MaxChStatTime = 0;
	m_MaxIVRStatTime = 0;
	m_MaxVOIPStatTime = 0;

	m_MaxAgChStat = 0;
	m_MaxDTIChStat = 0;
	m_MaxSIPChStat = 0;
	m_MaxConfChStat = 0;

	if (SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType() == DB_MySql) 
	{
		m_TimeFunction = "NOW()";
	}
	else
	{
		m_TimeFunction = "GetDate()";
	}
	
}


KFPC_MonitorRefreshData::~KFPC_MonitorRefreshData(void)
{
}

int KFPC_MonitorRefreshData::Run()
{
	if((time(NULL) - m_TimeStamp) > UpdateDelay)
	{
		m_TimeStamp = time(NULL);

		DBInsertIVRCh();
		DBInsertVOIPCh();
		DBInserCh();

		DBUpdateIVRCh();		
		DBUpdateVOIPCh();		
		DBUpdateCh();

		DBInsertChStat();
		DBInsertIVRChStat();
		DBInsertVOIPChStat();

	}

	if((time(NULL) - m_ClearTimeStamp) > (3600*24))
	{
		m_ClearTimeStamp = time(NULL);

		ClearStatData();



	}


	return -1;
}

void KFPC_MonitorRefreshData::InsertIVRCh( unsigned int ID,unsigned int NODE,unsigned int BRD,unsigned int BRD_CH,unsigned int NODE_CH )
{
	IVRChInfo_t	IVRChInfo={ID,NODE,BRD,BRD_CH,NODE_CH};

	//m_IVRChInfoList.push_back(IVRChInfo);
	IVRChInfoMapInsertResult_t Ret = m_IVRChInfoMap.insert(IVRChInfoMapPair_t(ID,IVRChInfo));

	 if(!Ret.second)
	 {
		 Ret.first->second.ID = ID;
		 Ret.first->second.NODE = NODE;
		 Ret.first->second.BRD = BRD;
		 Ret.first->second.BRD_CH = BRD_CH;
		 Ret.first->second.NODE_CH = NODE_CH;
	 }

	if(m_IVRChInfoMap.size() >= MinListSize)
	{
		DBInsertIVRCh();
	}


}

void KFPC_MonitorRefreshData::UpdateIVRCh( unsigned int ID,unsigned int Used )
{
	//IVRStatus_t	IVRStatus={ID,Used};

	//m_IVRStatusList.push_back(IVRStatus);
	IVRStatusInsertResult_t	Ret = m_IVRStatusMap.insert(IVRStatusPair_t(ID,Used));
	if(!Ret.second)
	{
		Ret.first->second = Used;
	}

	if(m_IVRStatusMap.size() >= MaxListSize)
	{
		DBUpdateIVRCh();
	}

	if(SSTServerCfgInstance->GetMonitor_Cfg().m_StatInterval > 0)
	{
		if(Used)
		{
			if(m_IVRStat == 0 )
			{
				AddIVRStat();
			}

			m_IVRStat ++;
			
		}
		else
		{
			if(m_IVRStat > 0)
			{
				m_IVRStat --;

				//AddIVRStat();
				
				
			}
			else
			{
				WARNING_LOG(0,"IVR used is 0");
			}

		}

		m_IVRChangeCount ++;
		//if((m_IVRChangeCount % 10) == 0)
		//{
		//	//DBInsertIVRChStat();
		//	m_IVRChangeCount = 0;

		//	AddIVRStat();

		//}

		AddIVRStat();

		if(m_IVRStatList.size() >= MaxListSize)
		{
			DBInsertIVRChStat();
		}

	}

}

void KFPC_MonitorRefreshData::InsertVOIPCh( unsigned int ID,unsigned int NODE,unsigned int BRD,unsigned int BRD_CH,unsigned int NODE_CH )
{
	VOIPChInfo_t	VOIPChInfo = {ID, NODE,BRD,BRD_CH,NODE_CH};
	//m_VOIPChInfoList.push_back(VOIPChInfo);

	VOIPChInfoMapInsertResult_t Ret = m_VOIPChInfoMap.insert(VOIPChInfoMapPair_t(ID,VOIPChInfo));

	if(!Ret.second)
	{
		Ret.first->second.ID = ID;
		Ret.first->second.NODE = NODE;
		Ret.first->second.BRD = BRD;
		Ret.first->second.BRD_CH = BRD_CH;
		Ret.first->second.NODE_CH = NODE_CH;
	}

	if(m_VOIPChInfoMap.size() >= MinListSize)
	{
		DBInsertVOIPCh();
	}
}

void KFPC_MonitorRefreshData::UpdateVOIPCh( unsigned int ID,unsigned int Used )
{
	//VOIPStatus_t	VOIPStatus = {ID,Used};

	//m_VOIPStatusList.push_back(VOIPStatus);

	VOIPStatusInsertResult_t	Ret = m_VOIPStatusMap.insert(VOIPStatusPair_t(ID,Used));

	if(!Ret.second)
	{
		Ret.first->second = Used;
	}

	if(m_VOIPStatusMap.size() >= MaxListSize)
	{
		DBUpdateVOIPCh();
	}

	if(SSTServerCfgInstance->GetMonitor_Cfg().m_StatInterval > 0)
	{
		if(Used)
		{
			if(m_VOIPStat == 0 )
			{
				AddVOIPStat();

			}


			m_VOIPStat ++;
			//m_VOIPChangeCount ++;
		}
		else
		{
			

			if(m_VOIPStat > 0)
			{
				m_VOIPStat --;

				//if(m_VOIPStat == 0)
				//{
				//	AddVOIPStat();
				//}
			}
			else
			{
				WARNING_LOG(0,"VOIP used is 0");
			}
			
			//m_VOIPChangeCount ++;

		}

		m_VOIPChangeCount ++;
		AddVOIPStat();

		//if((m_VOIPChangeCount % 10) == 0)
		//{
		//	m_VOIPChangeCount = 0;

		//	if(m_LastVOIPStat != m_VOIPStat)
		//	{
		//		ChStat_t	VOIPStat = {time(NULL),m_VOIPStat};
		//		m_LastVOIPStat = m_VOIPStat;
		//		m_VOIPStatList.push_back(VOIPStat);
		//	}

		//}

		if(m_VOIPStatList.size() >= MaxListSize)
		{
			DBInsertVOIPChStat();
		}
	}

}



void KFPC_MonitorRefreshData::InserCh( unsigned int ID,unsigned int NODE,unsigned int Span,unsigned int Channel,unsigned int Status,unsigned int Node_Span,KFPC_CH_TYPE ChType )
{
	ChInfo_t	ChInfo = {ID,NODE,Span,Channel,Status,Node_Span,ChType};
	//m_ChInfoList.push_back(ChInfo);
	ChInfoMapInsertResult_t	Ret = m_ChInfoMap.insert(ChInfoMapPair_t(ID,ChInfo));

	if(!Ret.second)
	{
		Ret.first->second.ID = ID;
		Ret.first->second.NODE = NODE;
		Ret.first->second.Span = Span;
		Ret.first->second.Channel = Channel;
		Ret.first->second.Status = Status;
		Ret.first->second.Node_Span = Node_Span;
		Ret.first->second.ChType = ChType;
	}

	if(m_ChInfoMap.size() >= MinListSize)
	{
		DBInserCh();
	}
}

void KFPC_MonitorRefreshData::UpdateCh( unsigned int ID,unsigned int Status )
{
	//ChStatus_t		ChStatus = {ID,Status};
	//m_ChStatusList.push_back(ChStatus);
	ChStatusInsertResult_t Ret = m_ChStatusMap.insert(ChStatusPair_t(ID,Status));

	if(!Ret.second)
	{
		Ret.first->second = Status;
	}
	

	if(m_ChStatusMap.size() >= MaxListSize)
	{
		DBUpdateCh();
	}

	if(SSTServerCfgInstance->GetMonitor_Cfg().m_StatInterval > 0)
	{
		m_ChChangeCount ++;

		//if((m_ChChangeCount % 10) == 0)
		//{

			//KFPC_ChMgrInstance->LogChStat();
			
		//	m_ChChangeCount = 0;
		//	unsigned int ChUsedCount = KFPC_ChMgrInstance->GetUsedCount();
			

		//	AddChStatCount(ChUsedCount);

			
		//}

		
		unsigned int ChUsedCount = KFPC_ChMgrInstance->GetUsedCount();

		//if(ChUsedCount == 1)
		//{
		//	ChUsedCount = KFPC_ChMgrInstance->GetUsedCount();
		//}
		//DEBUG_LOG(0,"ChUsedCount:%u",ChUsedCount);

		AddChStatCount(ChUsedCount,
			0,//KFPC_ChMgrInstance->GetAgChUsedCount(),
			0,//KFPC_ChMgrInstance->GetDTIChUsedCount(),
			KFPC_ChMgrInstance->GetSIPChUsedCount(),
			KFPC_ChMgrInstance->GetConfChUsedCount());

		if(m_ChStatList.size() >= MaxListSize)
		{
			DBInsertChStat();
		}
	}

}

void KFPC_MonitorRefreshData::DBInsertIVRCh()
{
	if(m_IVRChInfoMap.size() > 0)
	{
		DEBUG_LOG(0,"");
		char	SqlBuf[KFPC_MAX_SQL_STR] = "";

		int		n = 0;

		unsigned int AppID = KFPC_GetLibParam()->AppInfo.AppID;

		if(SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType() == DB_MySql)
		{
			n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"INSERT INTO tbl_monitor_ivrch (ID,NODE,BRD,BRD_CH,NODE_CH,USED,APPID,UPDATE_TIME) VALUES ");

			for(IVRChInfoMapIter_t Iter = m_IVRChInfoMap.begin();
				Iter != m_IVRChInfoMap.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"(%u,%u,%u,%u,%u,%u,%u,%s),",Iter->second.ID,
					Iter->second.NODE,
					Iter->second.BRD,
					Iter->second.BRD_CH,
					Iter->second.NODE_CH,
					0,
					AppID,
					m_TimeFunction.c_str());
			}

			n += snprintf(SqlBuf+n-1,KFPC_MAX_SQL_STR-n,";");
		}
		else
		{
			

			for(IVRChInfoMapIter_t Iter = m_IVRChInfoMap.begin();
				Iter != m_IVRChInfoMap.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"INSERT INTO tbl_monitor_ivrch (ID,NODE,BRD,BRD_CH,NODE_CH,USED,APPID,UPDATE_TIME) VALUES ");

				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"(%u,%u,%u,%u,%u,%u,%u,%s);",
					Iter->second.ID,
					Iter->second.NODE,
					Iter->second.BRD,
					Iter->second.BRD_CH,
					Iter->second.NODE_CH,
					0,
					AppID,
					m_TimeFunction.c_str());
			}

		}

		ExeSql(SqlBuf);

		m_IVRChInfoMap.clear();
	}	
}

void KFPC_MonitorRefreshData::DBUpdateIVRCh()
{
	if(m_IVRStatusMap.size() > 0)
	{
		DEBUG_LOG(0,"");
		char	SqlBuf[KFPC_MAX_SQL_STR] = "";

		int		n = 0;

		unsigned int AppID = KFPC_GetLibParam()->AppInfo.AppID;

		if(SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType() == DB_MySql)
		{
			n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"UPDATE tbl_monitor_ivrch SET UPDATE_TIME = %s, USED = CASE ID",m_TimeFunction.c_str());

			for(IVRStatusMapIter_t Iter = m_IVRStatusMap.begin();
				Iter != m_IVRStatusMap.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n," WHEN %u THEN %u ",
					Iter->first,
					Iter->second);
			}

			n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n," END WHERE ID IN (");

			for(IVRStatusMapIter_t Iter = m_IVRStatusMap.begin();
				Iter != m_IVRStatusMap.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n," %u,",Iter->first);
			}

			n += snprintf(SqlBuf+n-1,KFPC_MAX_SQL_STR-n,");");
		}
		else
		{
			
			for(IVRStatusMapIter_t Iter = m_IVRStatusMap.begin();
				Iter != m_IVRStatusMap.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"UPDATE tbl_monitor_ivrch SET UPDATE_TIME = %s, USED = %u WHERE ID=%u;",
					m_TimeFunction.c_str(),Iter->second,Iter->first);
			}
		}


		ExeSql(SqlBuf);

		m_IVRStatusMap.clear();
	}

}

void KFPC_MonitorRefreshData::DBInsertVOIPCh()
{
	if(m_VOIPChInfoMap.size() > 0)
	{
		DEBUG_LOG(0,"");
		char	SqlBuf[KFPC_MAX_SQL_STR] = "";

		int		n = 0;

		unsigned int AppID = KFPC_GetLibParam()->AppInfo.AppID;

		if(SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType() == DB_MySql)
		{
			n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"INSERT INTO tbl_monitor_voipch (ID,NODE,BRD,BRD_CH,NODE_CH,USED,APPID,UPDATE_TIME) VALUES ");

			for(VOIPChInfoMapIter_t Iter = m_VOIPChInfoMap.begin();
				Iter != m_VOIPChInfoMap.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"(%u,%u,%u,%u,%u,%u,%u,%s),",
					Iter->second.ID,
					Iter->second.NODE,
					Iter->second.BRD,
					Iter->second.BRD_CH,
					Iter->second.NODE_CH,
					0,
					AppID,
					m_TimeFunction.c_str());
			}

			n += snprintf(SqlBuf+n-1,KFPC_MAX_SQL_STR-n,";");

		}
		else
		{
			

			for(VOIPChInfoMapIter_t Iter = m_VOIPChInfoMap.begin();
				Iter != m_VOIPChInfoMap.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"INSERT INTO tbl_monitor_voipch (ID,NODE,BRD,BRD_CH,NODE_CH,USED,APPID,UPDATE_TIME) VALUES ");
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"(%u,%u,%u,%u,%u,%u,%u,%s);",
					Iter->second.ID,
					Iter->second.NODE,
					Iter->second.BRD,
					Iter->second.BRD_CH,
					Iter->second.NODE_CH,
					0,
					AppID,
					m_TimeFunction.c_str());
			}

		}


		ExeSql(SqlBuf);

		m_VOIPChInfoMap.clear();
	}

}

void KFPC_MonitorRefreshData::DBUpdateVOIPCh()
{
	if(m_VOIPStatusMap.size() > 0)
	{
		DEBUG_LOG(0,"");
		char	SqlBuf[KFPC_MAX_SQL_STR] = "";

		int		n = 0;

		unsigned int AppID = KFPC_GetLibParam()->AppInfo.AppID;

		if(SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType() == DB_MySql)
		{
			n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"UPDATE tbl_monitor_voipch SET UPDATE_TIME = %s, USED = CASE ID",m_TimeFunction.c_str());

			for(VOIPStatusMapIter_t Iter = m_VOIPStatusMap.begin();
				Iter != m_VOIPStatusMap.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n," WHEN %u THEN %u ",
					Iter->first,
					Iter->second);
			}

			n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n," END WHERE ID IN (");

			for(VOIPStatusMapIter_t Iter = m_VOIPStatusMap.begin();
				Iter != m_VOIPStatusMap.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n," %u,",
					Iter->first);
			}

			n += snprintf(SqlBuf+n-1,KFPC_MAX_SQL_STR-n,");");

		}
		else
		{

			for(VOIPStatusMapIter_t Iter = m_VOIPStatusMap.begin();
				Iter != m_VOIPStatusMap.end();
				Iter ++)
			{

				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"UPDATE tbl_monitor_voipch SET UPDATE_TIME = %s, USED = %u WHERE ID=%u;",
					m_TimeFunction.c_str(),Iter->second,Iter->first);
			}



		}

		ExeSql(SqlBuf);

		m_VOIPStatusMap.clear();
	}
}

void KFPC_MonitorRefreshData::DBInserCh()
{
	if(m_ChInfoMap.size() > 0)
	{
		DEBUG_LOG(0,"ChInfoList.size:%u",m_ChInfoMap.size());
		char	SqlBuf[KFPC_MAX_SQL_STR] = "";

		int		n = 0;

		unsigned int AppID = KFPC_GetLibParam()->AppInfo.AppID;

		if(SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType() == DB_MySql)
		{
			n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"INSERT INTO tbl_monitor_channel ( ID,  SPAN_ID,  CHANNEL_ID,  CHANNEL_STATUS,  UPDATE_TIME,  APP_ID,  NODE,  NODE_SPAN,  CH_TYPE) VALUES ");

			for(ChInfoMapIter_t Iter = m_ChInfoMap.begin();
				Iter != m_ChInfoMap.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"(%u,%u,%u,'%s',%s,%u,%u,%u,'%s'),",
					Iter->second.ID,
					Iter->second.Span,
					Iter->second.Channel,
					ChStatusToStr(Iter->second.Status),
					m_TimeFunction.c_str(),
					AppID,
					Iter->second.NODE,
					Iter->second.Node_Span,
					ChTypeToStr(Iter->second.ChType));
			}

			n += snprintf(SqlBuf+n-1,KFPC_MAX_SQL_STR-n,";");

		}
		else
		{

			for(ChInfoMapIter_t Iter = m_ChInfoMap.begin();
				Iter != m_ChInfoMap.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"INSERT INTO tbl_monitor_channel ( ID,  SPAN_ID,  CHANNEL_ID,  CHANNEL_STATUS,  UPDATE_TIME,  APP_ID,  NODE,  NODE_SPAN,  CH_TYPE) VALUES ");

				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"(%u,%u,%u,'%s',%s,%u,%u,%u,'%s');",
					Iter->second.ID,
					Iter->second.Span,
					Iter->second.Channel,
					ChStatusToStr(Iter->second.Status),
					m_TimeFunction.c_str(),
					AppID,
					Iter->second.NODE,
					Iter->second.Node_Span,
					ChTypeToStr(Iter->second.ChType));
			}
		}


		ExeSql(SqlBuf);

		m_ChInfoMap.clear();
	}
}

void KFPC_MonitorRefreshData::DBUpdateCh()
{
	if(m_ChStatusMap.size() > 0)
	{
		DEBUG_LOG(0,"ChStatusList.size:%u",m_ChStatusMap.size());
		char	SqlBuf[KFPC_MAX_SQL_STR] = "";

		int		n = 0;

		unsigned int AppID = KFPC_GetLibParam()->AppInfo.AppID;

		if(SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType() == DB_MySql)
		{
			n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"UPDATE tbl_monitor_channel SET UPDATE_TIME = %s, CHANNEL_STATUS = CASE ID",m_TimeFunction.c_str());

			for(ChStatusMapIter_t Iter = m_ChStatusMap.begin();
				Iter != m_ChStatusMap.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n," WHEN %u THEN '%s' ",Iter->first,
					ChStatusToStr(Iter->second));
			}

			n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n," END WHERE ID IN (");

			for(ChStatusMapIter_t Iter = m_ChStatusMap.begin();
				Iter != m_ChStatusMap.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n," %u,",Iter->first);
			}

			n += snprintf(SqlBuf+n-1,KFPC_MAX_SQL_STR-n,");");
		}
		else
		{
			

			for(ChStatusMapIter_t Iter = m_ChStatusMap.begin();
				Iter != m_ChStatusMap.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"UPDATE tbl_monitor_channel SET UPDATE_TIME = %s, CHANNEL_STATUS = '%s' WHERE ID=%u;",
					m_TimeFunction.c_str(),ChStatusToStr(Iter->second),Iter->first);
			}
		}

		ExeSql(SqlBuf);

		m_ChStatusMap.clear();
	}
}

void KFPC_MonitorRefreshData::ExeSql( char* SqlBuf )
{
#ifndef TSERVER_NODB
	//DEBUG_LOG(0,"SqlBuf:%s",SqlBuf);
	KFPC_DBTask* pDBTask = NULL;

	smart_new(KFPC_DBTask(),pDBTask);

	pDBTask->SetSQLDebug(SSTServerCfgInstance->GetDBAccessInfoSet()->GetSQLDebug());

	pDBTask->SetSql(SqlBuf);

	KFPC_DBThreadPoolInstance->PutTask(pDBTask);
#endif

}

void KFPC_MonitorRefreshData::ClearIVRCh(unsigned int Node)
{
	DEBUG_LOG(0,"");
	char	SqlBuf[KFPC_MAX_SQL_STR] = "";

	int		n = 0;

	unsigned int AppID = KFPC_GetLibParam()->AppInfo.AppID;

	if(0 == Node)
	{
		n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"DELETE FROM TBL_MONITOR_IVRCH WHERE APPID=%d",AppID);

	}
	else
	{
		n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"DELETE FROM TBL_MONITOR_IVRCH WHERE (App_ID=%d and NODE=%u)",AppID,Node);
	}


	ExeSql(SqlBuf);
}

void KFPC_MonitorRefreshData::ClearVOIPCh(unsigned int Node)
{
	DEBUG_LOG(0,"");
	char	SqlBuf[KFPC_MAX_SQL_STR] = "";

	int		n = 0;

	unsigned int AppID = KFPC_GetLibParam()->AppInfo.AppID;

	if(0 == Node)
	{
		n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"DELETE FROM TBL_MONITOR_VOIPCH WHERE APPID=%d",AppID);
	}
	else
	{
		n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"DELETE FROM TBL_MONITOR_VOIPCH WHERE (App_ID=%d and NODE=%u)",AppID,Node);
	}
	

	ExeSql(SqlBuf);
}

void KFPC_MonitorRefreshData::ClearCh(unsigned int Node)
{
	DEBUG_LOG(0,"");
	char	SqlBuf[KFPC_MAX_SQL_STR] = "";

	int		n = 0;

	unsigned int AppID = KFPC_GetLibParam()->AppInfo.AppID;

	if(0 == Node)
	{
		n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"DELETE FROM TBL_MONITOR_CHANNEL WHERE App_ID=%d",AppID);

	}
	else
	{
		n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"DELETE FROM TBL_MONITOR_CHANNEL WHERE (App_ID=%d and NODE=%u)",AppID,Node);
	}

	ExeSql(SqlBuf);
}

void KFPC_MonitorRefreshData::DBInsertChStat()
{

	if(m_MaxChStat > 0 )
	{

		ChStat_t	ChStat = {m_MaxChStatTime,m_MaxChStat,m_MaxAgChStat,m_MaxDTIChStat,m_MaxSIPChStat,m_MaxConfChStat};
		//DEBUG_LOG(0,"m_MaxChStat:%u,m_MaxAgChStat:%u,m_MaxDTIChStat:%u,m_MaxSIPChStat:%u,m_MaxConfChStat:%u,",m_MaxChStat,m_MaxAgChStat,m_MaxDTIChStat,m_MaxSIPChStat,m_MaxConfChStat);
		m_ChStatList.push_back(ChStat);
		m_LastChStat = m_MaxChStat;
	}

	if(m_ChChangeCount > 0)
	{
		unsigned int ChUsedCount = KFPC_ChMgrInstance->GetUsedCount();
		AddChStatCount(ChUsedCount,
			0,//KFPC_ChMgrInstance->GetAgChUsedCount(),
			0,//KFPC_ChMgrInstance->GetDTIChUsedCount(),
			KFPC_ChMgrInstance->GetSIPChUsedCount(),
			KFPC_ChMgrInstance->GetConfChUsedCount());
	}

	
	m_ChChangeCount = 0;
	m_MaxChStat = 0;
	m_MaxAgChStat = 0;
	m_MaxDTIChStat = 0;
	m_MaxSIPChStat = 0;
	m_MaxConfChStat = 0;

	if(m_ChStatList.size() > 0)
	{
		DEBUG_LOG(0,"ChStatList.size:%u",m_ChStatList.size());
		KFPC_ChMgrInstance->LogChStat();
		char	SqlBuf[KFPC_MAX_SQL_STR] = "";

		int		n = 0;

		unsigned int AppID = KFPC_GetLibParam()->AppInfo.AppID;

		if(SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType() == DB_MySql)
		{
			n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"INSERT INTO tbl_monitor_channel_stat ( UpdateTime, ChannelStat, APPID,AgChannelStat, DTIChannelStat,  SIPChannelStat,  ConfChannelStat ) VALUES ");

			char	TimeStr[128]="";

			for(ChStatListIter_t Iter = m_ChStatList.begin();
				Iter != m_ChStatList.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"('%s',%u,%u,%u,%u,%u,%u),",
					TimeToStr(TimeStr,Iter->m_time),
					Iter->m_Count,
					AppID,
					Iter->m_MaxAgChStat,
					Iter->m_MaxDTIChStat,
					Iter->m_MaxSIPChStat,
					Iter->m_MaxConfChStat);
			}

			n += snprintf(SqlBuf+n-1,KFPC_MAX_SQL_STR-n,";");
		}
		else
		{
			

			char	TimeStr[128]="";

			for(ChStatListIter_t Iter = m_ChStatList.begin();
				Iter != m_ChStatList.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"INSERT INTO tbl_monitor_channel_stat ( UpdateTime, ChannelStat, APPID,AgChannelStat, DTIChannelStat,  SIPChannelStat,  ConfChannelStat ) VALUES ");

				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"('%s',%u,%u,%u,%u,%u,%u);",
					TimeToStr(TimeStr,Iter->m_time),
					Iter->m_Count,
					AppID,
					Iter->m_MaxAgChStat,
					Iter->m_MaxDTIChStat,
					Iter->m_MaxSIPChStat,
					Iter->m_MaxConfChStat);
			}

		}

		ExeSql(SqlBuf);
		m_ChStatList.clear();
	}
}

void KFPC_MonitorRefreshData::DBInsertIVRChStat()
{

	if(m_MaxIVRStat > 0)
	{
		ChStat_t	IVRStat = {m_MaxIVRStatTime,m_MaxIVRStat};
		m_LastIVRStat = m_IVRStat;
		m_IVRStatList.push_back(IVRStat);
	}


	if(m_IVRChangeCount > 0)
	{
		AddIVRStat();
	}

	m_IVRChangeCount = 0;
	m_MaxIVRStat = 0;

	if(m_IVRStatList.size() > 0)
	{
		DEBUG_LOG(0,"IVRStatList.size:%u",m_IVRStatList.size());
		char	SqlBuf[KFPC_MAX_SQL_STR] = "";

		int		n = 0;

		unsigned int AppID = KFPC_GetLibParam()->AppInfo.AppID;

		if(SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType() == DB_MySql)
		{

			n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"INSERT INTO tbl_monitor_ivrch_stat ( UpdateTime, ChannelStat, APPID) VALUES ");

			char	TimeStr[128]="";

			for(ChStatListIter_t Iter = m_IVRStatList.begin();
				Iter != m_IVRStatList.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"('%s',%u,%d),",
					TimeToStr(TimeStr,Iter->m_time),
					Iter->m_Count,
					AppID);
			}

			n += snprintf(SqlBuf+n-1,KFPC_MAX_SQL_STR-n,";");

		}
		else
		{
			
			char	TimeStr[128]="";

			for(ChStatListIter_t Iter = m_IVRStatList.begin();
				Iter != m_IVRStatList.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"INSERT INTO tbl_monitor_ivrch_stat ( UpdateTime, ChannelStat, APPID) VALUES ");

				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"('%s',%u,%d);",
					TimeToStr(TimeStr,Iter->m_time),
					Iter->m_Count,
					AppID);
			}

		}

		ExeSql(SqlBuf);
		m_IVRStatList.clear();
	}
	
}

void KFPC_MonitorRefreshData::DBInsertVOIPChStat()
{

	//if(m_VOIPChangeCount > 0)
	//{
	//	if(m_LastVOIPStat != m_VOIPStat)
	//	{
	//		ChStat_t	VOIPStat = {time(NULL),m_VOIPStat};
	//		m_LastVOIPStat = m_VOIPStat;
	//		m_VOIPStatList.push_back(VOIPStat);			
	//	}
	//	
	//	
	//}

	if(m_MaxVOIPStat > 0)
	{
		ChStat_t	VOIPStat = {m_MaxVOIPStatTime,m_MaxVOIPStat};		
		m_VOIPStatList.push_back(VOIPStat);		
		m_LastVOIPStat = m_VOIPStat;	
	}

	if(m_VOIPChangeCount > 0)
	{
		AddVOIPStat();
	}

	m_MaxVOIPStat = 0;
	m_VOIPChangeCount = 0;

	if(m_VOIPStatList.size() > 0)
	{
		DEBUG_LOG(0,"VOIPStatList.size:%u",m_VOIPStatList.size());
		char	SqlBuf[KFPC_MAX_SQL_STR] = "";

		int		n = 0;

		unsigned int AppID = KFPC_GetLibParam()->AppInfo.AppID;

		if(SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType() == DB_MySql)
		{
			n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"INSERT INTO tbl_monitor_voipch_stat ( UpdateTime, ChannelStat, APPID) VALUES ");

			char	TimeStr[128]="";

			for(ChStatListIter_t Iter = m_VOIPStatList.begin();
				Iter != m_VOIPStatList.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"('%s',%u,%d),",
					TimeToStr(TimeStr,Iter->m_time),
					Iter->m_Count,
					AppID);
			}

			n += snprintf(SqlBuf+n-1,KFPC_MAX_SQL_STR-n,";");

		}
		else
		{
			

			char	TimeStr[128]="";

			for(ChStatListIter_t Iter = m_VOIPStatList.begin();
				Iter != m_VOIPStatList.end();
				Iter ++)
			{
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"INSERT INTO tbl_monitor_voipch_stat ( UpdateTime, ChannelStat, APPID) VALUES ");
				n += snprintf(SqlBuf+n,KFPC_MAX_SQL_STR-n,"('%s',%u,%d);",
					TimeToStr(TimeStr,Iter->m_time),
					Iter->m_Count,
					AppID);
			}
		}

		ExeSql(SqlBuf);
		m_VOIPStatList.clear();
	}

}

void KFPC_MonitorRefreshData::ClearStatData()
{
	char	SqlBuf[KFPC_MAX_SQL_STR] = "";
	if (SSTServerCfgInstance->GetDBAccessInfoSet()->GetDBType() == DB_MySql) 
	{

		snprintf(SqlBuf,KFPC_MAX_SQL_STR,"DELETE FROM tbl_monitor_ivrch_stat  WHERE  UpdateTime <= DATE_SUB(NOW(),INTERVAL %u DAY)",	SSTServerCfgInstance->GetMonitor_Cfg().m_StatInterval);
		ExeSql(SqlBuf);
		snprintf(SqlBuf,KFPC_MAX_SQL_STR,"DELETE FROM tbl_monitor_voipch_stat  WHERE  UpdateTime <= DATE_SUB(NOW(),INTERVAL %u DAY)",	SSTServerCfgInstance->GetMonitor_Cfg().m_StatInterval);
		ExeSql(SqlBuf);
		snprintf(SqlBuf,KFPC_MAX_SQL_STR,"DELETE FROM tbl_monitor_channel_stat  WHERE  UpdateTime <= DATE_SUB(NOW(),INTERVAL %u DAY)",SSTServerCfgInstance->GetMonitor_Cfg().m_StatInterval);
		ExeSql(SqlBuf);
	}
	else
	{
		snprintf(SqlBuf,KFPC_MAX_SQL_STR,"DELETE FROM tbl_monitor_ivrch_stat  WHERE  UpdateTime <= dateadd(day,-%u,getdate())",		SSTServerCfgInstance->GetMonitor_Cfg().m_StatInterval);
		ExeSql(SqlBuf);
		snprintf(SqlBuf,KFPC_MAX_SQL_STR,"DELETE FROM tbl_monitor_voipch_stat  WHERE  UpdateTime <= dateadd(day,-%u,getdate())",	SSTServerCfgInstance->GetMonitor_Cfg().m_StatInterval);
		ExeSql(SqlBuf);
		snprintf(SqlBuf,KFPC_MAX_SQL_STR,"DELETE FROM tbl_monitor_channel_stat  WHERE  UpdateTime <= dateadd(day,-%u,getdate())",	SSTServerCfgInstance->GetMonitor_Cfg().m_StatInterval);
		ExeSql(SqlBuf);
	}
}

void KFPC_MonitorRefreshData::AddChStatCount( unsigned int ChUsedCount,unsigned int AgCount,unsigned int DTICount,unsigned int SIPCount,unsigned int ConfCount)
{
	if(m_LastChStat != ChUsedCount)
	{
		if(ChUsedCount > m_MaxChStat )
		{
			m_LastChStat = ChUsedCount;
			m_MaxChStat = ChUsedCount;
			m_MaxChStatTime = time(NULL);

			m_MaxAgChStat = (m_MaxAgChStat < AgCount)?AgCount:m_MaxAgChStat;
			m_MaxDTIChStat = (m_MaxDTIChStat < DTICount)?DTICount:m_MaxDTIChStat;
			m_MaxSIPChStat = (m_MaxSIPChStat < SIPCount)?SIPCount:m_MaxSIPChStat;
			m_MaxConfChStat = (m_MaxConfChStat < ConfCount)?ConfCount:m_MaxConfChStat;

		}
		else if(ChUsedCount == 0)
		{
			ChStat_t	ChStat = {time(NULL),ChUsedCount,AgCount,DTICount,SIPCount,ConfCount};
			m_ChStatList.push_back(ChStat);
			m_LastChStat = ChUsedCount;
			m_MaxChStat = ChUsedCount;
			m_MaxChStatTime = time(NULL);

			m_MaxAgChStat = AgCount;
			m_MaxDTIChStat = DTICount;
			m_MaxSIPChStat = SIPCount;
			m_MaxConfChStat = ConfCount;
		}
	}


}

void KFPC_MonitorRefreshData::AddIVRStat()
{
	if(m_LastIVRStat != m_IVRStat)
	{
		if(m_IVRStat > m_MaxIVRStat)
		{
			m_LastIVRStat = m_IVRStat;
			m_MaxIVRStat = m_IVRStat;
			m_MaxIVRStatTime = time(NULL);
		}
		else if(m_IVRStat == 0)
		{
			ChStat_t	IVRStat = {time(NULL),m_IVRStat};
			m_IVRStatList.push_back(IVRStat);
			m_LastIVRStat = m_IVRStat;
			m_MaxIVRStat = m_IVRStat;
			m_MaxIVRStatTime = time(NULL);
		}
	}

}

void KFPC_MonitorRefreshData::AddVOIPStat()
{
	if(m_LastVOIPStat != m_VOIPStat )
	{
		if(m_VOIPStat > m_MaxVOIPStat )
		{
			m_LastVOIPStat = m_VOIPStat;
			m_MaxVOIPStat = m_VOIPStat;
			m_MaxVOIPStatTime = time(NULL);
		}
		else if(m_VOIPStat == 0)
		{
			ChStat_t	VOIPStat = {time(NULL),m_VOIPStat};
			m_VOIPStatList.push_back(VOIPStat);

			m_LastVOIPStat = m_VOIPStat;
			m_MaxVOIPStat = m_VOIPStat;
			m_MaxVOIPStatTime = time(NULL);
		}
	}

}
