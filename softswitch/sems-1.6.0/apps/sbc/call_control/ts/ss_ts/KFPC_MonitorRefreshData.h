#pragma once
#include "kfpc_loophandler.h"
#include <time.h>
#include "KFPC_TServerDef.h"
#include <string>

#define MinListSize		16
#define MaxListSize		30
#define UpdateDelay		2

typedef struct	IVRChInfo_t
{
	unsigned int ID;
	unsigned int  NODE;
	unsigned int BRD;
	unsigned int BRD_CH;
	unsigned int NODE_CH;
}IVRChInfo_t;

typedef struct VOIPChInfo_t
{
	unsigned int ID;
	unsigned int  NODE;
	unsigned int BRD;
	unsigned int BRD_CH;
	unsigned int NODE_CH;
}VOIPChInfo_t;

typedef struct ChInfo_t
{
	unsigned int ID;
	unsigned int  NODE;
	unsigned int Span;
	unsigned int Channel;
	unsigned int Status;
	unsigned int Node_Span;
	KFPC_CH_TYPE ChType;
}ChInfo_t;


typedef struct IVRStatus_t
{
	unsigned int ID;
	unsigned int Status;
}IVRStatus_t;

typedef struct VOIPStatus_t
{
	unsigned int ID;
	unsigned int Status;
}VOIPStatus_t;

typedef struct ChStatus_t
{
	unsigned int ID;
	unsigned int Status;
}ChStatus_t;


typedef	struct ChStat_t 
{
	time_t	m_time;
	unsigned int m_Count;
	unsigned int m_MaxAgChStat;
	unsigned int m_MaxDTIChStat;
	unsigned int m_MaxSIPChStat;
	unsigned int m_MaxConfChStat;
}ChStat_t;

#include <list>
#include <unordered_map>
using namespace std;

typedef unordered_map <unsigned int, IVRChInfo_t>		IVRChInfoMap_t;
typedef IVRChInfoMap_t:: iterator						IVRChInfoMapIter_t;
typedef pair<unsigned int, IVRChInfo_t>					IVRChInfoMapPair_t;
typedef pair< IVRChInfoMap_t:: iterator, bool >			IVRChInfoMapInsertResult_t;
//typedef list<IVRChInfo_t>								IVRChInfoList_t;
//typedef list<IVRChInfo_t>::iterator					IVRChInfoListIter_t;


typedef unordered_map <unsigned int, VOIPChInfo_t>		VOIPChInfoMap_t;
typedef VOIPChInfoMap_t:: iterator						VOIPChInfoMapIter_t;
typedef pair<unsigned int, VOIPChInfo_t>				VOIPChInfoMapPair_t;
typedef pair< VOIPChInfoMap_t:: iterator, bool >		VOIPChInfoMapInsertResult_t;
//typedef list<VOIPChInfo_t>							VOIPChInfoList_t;
//typedef list<VOIPChInfo_t>::iterator					VOIPChInfoListIter_t;


typedef unordered_map <unsigned int, ChInfo_t>			ChInfoMap_t;
typedef ChInfoMap_t:: iterator							ChInfoMapIter_t;
typedef pair<unsigned int, ChInfo_t>					ChInfoMapPair_t;
typedef pair< ChInfoMap_t:: iterator, bool >			ChInfoMapInsertResult_t;
//typedef list<ChInfo_t>								ChInfoList_t;
//typedef list<ChInfo_t>::iterator						ChInfoListIter_t;


typedef unordered_map <unsigned int, unsigned int>		IVRStatusMap_t;
typedef IVRStatusMap_t:: iterator						IVRStatusMapIter_t;
typedef pair<unsigned int, unsigned int>				IVRStatusPair_t;
typedef pair< IVRStatusMap_t:: iterator, bool >			IVRStatusInsertResult_t;
//typedef list<IVRStatus_t>								IVRStatusList_t;
//typedef list<IVRStatus_t>::iterator					IVRStatusListIter_t;


typedef unordered_map <unsigned int, unsigned int>		VOIPStatusMap_t;
typedef VOIPStatusMap_t:: iterator						VOIPStatusMapIter_t;
typedef pair<unsigned int, unsigned int>				VOIPStatusPair_t;
typedef pair< VOIPStatusMap_t:: iterator, bool >		VOIPStatusInsertResult_t;
//typedef list<VOIPStatus_t>							VOIPStatusList_t;
//typedef list<VOIPStatus_t>::iterator					VOIPStatusListIter_t;

typedef unordered_map <unsigned int, unsigned int>		ChStatusMap_t;
typedef VOIPStatusMap_t:: iterator						ChStatusMapIter_t;
typedef pair<unsigned int, unsigned int>				ChStatusPair_t;
typedef pair< VOIPStatusMap_t:: iterator, bool >		ChStatusInsertResult_t;
//typedef list<ChStatus_t>								ChStatusList_t;
//typedef list<ChStatus_t>::iterator						ChStatusListIter_t;


typedef list<ChStat_t>						ChStatList_t;
typedef list<ChStat_t>::iterator			ChStatListIter_t;

class KFPC_MonitorRefreshData :
	public KFPC_LoopHandler
{
private:
	//IVRChInfoList_t		m_IVRChInfoList;
	IVRChInfoMap_t		m_IVRChInfoMap;
	//VOIPChInfoList_t	m_VOIPChInfoList;
	VOIPChInfoMap_t		m_VOIPChInfoMap;

	//ChInfoList_t		m_ChInfoList;
	ChInfoMap_t			m_ChInfoMap;

	//IVRStatusList_t		m_IVRStatusList;
	IVRStatusMap_t		m_IVRStatusMap;

	//VOIPStatusList_t	m_VOIPStatusList;
	VOIPStatusMap_t		m_VOIPStatusMap;

	//ChStatusList_t		m_ChStatusList;
	
	ChStatusMap_t		m_ChStatusMap;

	ChStatList_t		m_ChStatList;
	ChStatList_t		m_IVRStatList;
	ChStatList_t		m_VOIPStatList;

	time_t				m_TimeStamp;
	time_t				m_ClearTimeStamp;
	void DBInsertIVRCh();

	void ExeSql( char* SqlBuf );
	void DBUpdateIVRCh();
	void DBInsertVOIPCh();
	void DBUpdateVOIPCh();
	void DBInserCh();
	void DBUpdateCh();

	//unsigned	int m_ChStat;
	unsigned	int m_LastChStat;
	unsigned	int m_MaxChStat;
	time_t			m_MaxChStatTime;
	unsigned	int	m_ChChangeCount;
	unsigned	int m_MaxAgChStat;
	unsigned	int m_MaxDTIChStat;
	unsigned	int m_MaxSIPChStat;
	unsigned	int m_MaxConfChStat;

	unsigned	int m_IVRStat;
	unsigned	int m_LastIVRStat;
	unsigned	int m_MaxIVRStat;
	time_t			m_MaxIVRStatTime;
	unsigned	int	m_IVRChangeCount;

	unsigned	int m_VOIPStat;
	unsigned	int m_LastVOIPStat;
	unsigned	int m_MaxVOIPStat;
	time_t			m_MaxVOIPStatTime;

	unsigned	int	m_VOIPChangeCount;

	string		m_TimeFunction;

	void DBInsertChStat();
	void DBInsertIVRChStat();
	void DBInsertVOIPChStat();
public:
	KFPC_MonitorRefreshData(void);
	virtual ~KFPC_MonitorRefreshData(void);
	virtual int Run();

	void ClearStatData();
	static KFPC_MonitorRefreshData* GetInstance()
	{
		static KFPC_MonitorRefreshData _Instance;
		return &_Instance;
	}

	void InsertIVRCh(unsigned int ID,unsigned int  NODE,unsigned int BRD,unsigned int BRD_CH,unsigned int NODE_CH);
	void UpdateIVRCh(unsigned int ID,unsigned int Used);

	void AddIVRStat();
	void InsertVOIPCh(unsigned int ID,unsigned int  NODE,unsigned int BRD,unsigned int BRD_CH,unsigned int NODE_CH);
	void UpdateVOIPCh(unsigned int ID,unsigned int Used);

	void AddVOIPStat();
	void InserCh(unsigned int ID,unsigned int  NODE,unsigned int Span,unsigned int Channel,unsigned int Status,unsigned int Node_Span,KFPC_CH_TYPE ChType);
	void UpdateCh(unsigned int ID,unsigned int Status);

	void AddChStatCount( unsigned int ChUsedCount,unsigned int AgCount,unsigned int DTICount,unsigned int SIPCount,unsigned int ConfCount );
	void ClearIVRCh(unsigned int Node = 0);
	void ClearVOIPCh(unsigned int Node = 0);
	void ClearCh(unsigned int Node = 0);
};

#define KFPC_MonitorRefreshData_Instance	KFPC_MonitorRefreshData::GetInstance()
