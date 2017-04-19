#pragma once

#include "KFPC_TSLicSer.h"
#include "KFPC_LoopHandler.h"
#include "kfpc_timer.h"
#include <unordered_map>

typedef std::unordered_map<unsigned int,KFPC_TSLicSer>		LicSerMap_t;
typedef LicSerMap_t::iterator								LicSerMapIter_t;
typedef std::pair<unsigned int, KFPC_TSLicSer>				LicSerMapPair_t;
typedef std::pair< LicSerMapIter_t, bool >					LicSerMapInsertResult_t;
#define GET_TS_LICFAIL_TIMER	10
using namespace std;

class KFPC_TSLicSerMgr :public KFPC_LoopHandler
{
private:
	LicSerMap_t	m_LicSerMap;
	KFPC_Timer		m_Timer;
public:
	KFPC_TSLicSerMgr(void);
	~KFPC_TSLicSerMgr(void);

	static KFPC_TSLicSerMgr* GetInstance()
	{
		static KFPC_TSLicSerMgr _inStance;
		return &_inStance;
	}

	KFPC_TSLicSer* AddLicSer(unsigned int AppID);
	KFPC_TSLicSer* GetLicSer(unsigned int AppID);
	unsigned int RemoveLicSer(unsigned int AppID);

	KFPC_TSLicSer* GetAvailableLicSer(unsigned int LicSerSN=0);

	unsigned int SetTimer(unsigned int NodeID,unsigned int TimeOut = 600,unsigned int SN=0);
	virtual int Run();
	void ClearTimer(unsigned int TimerID);
	unsigned int GetLicSerSize(){return m_LicSerMap.size();}

	KFPC_TSLicSer* GetMinSNSer();

};

#define KFPC_TSLicSerMgrInstance KFPC_TSLicSerMgr::GetInstance()



