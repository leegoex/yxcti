#include "kfpc_logex.h"
#include "KFPC_TSLicSerMgr.h"
#include "KFPC_NodeMgr.h"

KFPC_TSLicSerMgr::KFPC_TSLicSerMgr(void)
{
}


KFPC_TSLicSerMgr::~KFPC_TSLicSerMgr(void)
{
}

KFPC_TSLicSer* KFPC_TSLicSerMgr::GetAvailableLicSer( unsigned int LicSerSN/*=0*/ )
{
	if(m_LicSerMap.empty())
	{
		return NULL;
	}

	if(LicSerSN == 0)
	{
		return GetMinSNSer();
	}
	else
	{
		LicSerMapIter_t	BeginIter = m_LicSerMap.begin();
		//LicSerMapIter_t	EndIter = m_LicSerMap.end();

		for(;BeginIter != m_LicSerMap.end();BeginIter ++)
		{
			if(BeginIter->second.GetSN() > LicSerSN)
			{
				return &BeginIter->second;
			}
		}

		KFPC_TSLicSer* pTSLicSer = GetMinSNSer();
		return (pTSLicSer->GetSN() != LicSerSN)?pTSLicSer:NULL;

	}
	
}

KFPC_TSLicSer* KFPC_TSLicSerMgr::AddLicSer( unsigned int AppID)
{

	//É¾³ýÄ¬ÈÏµÄLIC
	m_LicSerMap.erase(0);

	KFPC_TSLicSer	LicSer;
	LicSer.SetAppID(AppID);
	LicSerMapInsertResult_t	Ret = m_LicSerMap.insert(LicSerMapPair_t(AppID,LicSer));

	if(!Ret.second)
	{
		WARNING_LOG(0,"LicSerAppID:%u already exist,Lic server count:%d",AppID,m_LicSerMap.size());
	}
	else
	{
		INFO_LOG(0,"LicSerAppID:%u Lic server count:%d",AppID,m_LicSerMap.size());
	}

	return &Ret.first->second;
}

KFPC_TSLicSer* KFPC_TSLicSerMgr::GetLicSer( unsigned int AppID )
{
	LicSerMapIter_t	Iter = m_LicSerMap.find(AppID);

	if(Iter != m_LicSerMap.end())
	{
		return &Iter->second;
	}
	else
	{
		return NULL;
	}
}

unsigned int KFPC_TSLicSerMgr::RemoveLicSer( unsigned int AppID )
{
	int Ret = m_LicSerMap.erase(AppID);
	if(Ret > 0)
	{
		INFO_LOG(0,"LicSerID:%u Lic server count:%d",AppID,m_LicSerMap.size());
		return 0;
	}
	else
	{
		return -1;
	}
}

int KFPC_TSLicSerMgr::Run()
{
	void*	Arg1 = NULL;
	void*	Arg2 = NULL;
	unsigned int TimerID = 0;
	int		Ret	=	0;
	unsigned long long SN = 0;

	Ret = m_Timer.OutTime(&TimerID,&Arg1,&Arg2,0,&SN);

	if(Ret == 0)
	{
		unsigned int NodeID = (unsigned int)Arg1;

		if(!m_LicSerMap.empty())
		{

			KFPC_EHNode* pNode = KFPC_NodeMgrInstance->GetNode(NodeID);

			if(pNode != NULL)
			{
				pNode->SetTimerID(0);
				if(strlen(pNode->GetMainBoardSN()) > 0)
				{
					pNode->GetLic((unsigned int)SN);
				}
			}

		}
	}
	return Ret;
}

unsigned int KFPC_TSLicSerMgr::SetTimer( unsigned int NodeID,unsigned int TimeOut /*= 600*/,unsigned int SN )
{
	INFO_LOG(0,"NodeID:%u,TimeOut:%u,SN:%u",NodeID,TimeOut,SN);

	return m_Timer.SetTimer((void*)NodeID,NULL,TimeOut,0,SN);

}

void KFPC_TSLicSerMgr::ClearTimer( unsigned int TimerID )
{
	m_Timer.ClearTimer(TimerID);
}

KFPC_TSLicSer* KFPC_TSLicSerMgr::GetMinSNSer()
{
	if(m_LicSerMap.empty()) return NULL;

	KFPC_TSLicSer* pMinSNSer = &m_LicSerMap.begin()->second;

	LicSerMapIter_t	BeginIter = m_LicSerMap.begin();
	//LicSerMapIter_t	EndIter = m_LicSerMap.end();

	for(;BeginIter != m_LicSerMap.end();BeginIter ++)
	{

		if(BeginIter->second.GetSN() < pMinSNSer->GetSN())
		{
			pMinSNSer =  &BeginIter->second;
		}
	}

	return pMinSNSer;
}