#include "kfpc_logex.h"
#include "KFPC_TrunkGroupMgr.h"

#include "apr_general.h"
#include "KFPC_TServerErr.h"
#include "KFPC_AppMainThread.h"
#include "KFPC_TServerAPIHandlerImp.h"
//#include "KFPC_SipSerMgr.h"

KFPC_TrunkGroupMgr::KFPC_TrunkGroupMgr()
{

}

KFPC_TrunkGroupMgr::~KFPC_TrunkGroupMgr()
{

}


KFPC_TrunkGroup* KFPC_TrunkGroupMgr::GetTrunkGroupByChannelID(unsigned int ChannelID)
{
	unsigned int nSpan = ChannelToSpan(ChannelID);
	unsigned int nChannel = ChannelToTimeSlot(ChannelID);
	
	KFPC_TrunkGroup *pTrunkGroup = NULL;
	CChannelBlock *pBlock = NULL;

	for (unsigned int i = 0; i < m_TrunkGroupList.size(); i++)
	{
		pTrunkGroup = &m_TrunkGroupList[i];
		if (pTrunkGroup)
		{
			for (unsigned int j = 0; j < pTrunkGroup->GetChannelBlockCount(); j++)
			{
				pBlock = &pTrunkGroup->m_ChannelBlockList[j];
				if (nSpan	 >= pBlock->GetBeginSpan()		&& 
					nSpan	 <= pBlock->GetEndSpan()		&& 
					nChannel >= pBlock->GetBeginChannel()	&&
					nChannel <= pBlock->GetEndChannel()
					)
				{
					return pTrunkGroup;
				}
			}
		}
	}
	return NULL;
}

/*
 * AddTrunkGroup
 */
KFPC_TrunkGroup * KFPC_TrunkGroupMgr::AddTrunkGroup(const char *pTrunkGroupName)
{
	KFPC_TrunkGroup * pTrunkGroup =  GetTrunkGroupByName(pTrunkGroupName);

	if(pTrunkGroup == NULL)
	{
		INFO_LOG(0,"AddTrunkGroup Name:%s.",pTrunkGroupName);

		KFPC_TrunkGroup	TrunkGroup;
		TrunkGroup.SetName(pTrunkGroupName);
		m_TrunkGroupList.push_back(TrunkGroup);
		return (&m_TrunkGroupList.back());
				
	}
	else
	{
		WARNING_LOG(0,"AddTrunkGroup Name:%s already exist.",pTrunkGroupName);
		return pTrunkGroup;
	}	
}

/*
 * DelTrunkGroup
 */
unsigned int KFPC_TrunkGroupMgr::DelTrunkGroup(const char *pTrunkGroupName)
{

	for(TrunkGroupIterator_t iter = m_TrunkGroupList.begin();iter != m_TrunkGroupList.end();)
	{
		if(strcasecmp((*iter).GetName(), pTrunkGroupName) == 0)
		{			
			m_TrunkGroupList.erase(iter++);
			return 0;
		}	
		else
		{
			iter++;
		}
	}

	return -1;
}

/*
 * GetTrunkGroupByName
 */
KFPC_TrunkGroup *KFPC_TrunkGroupMgr::GetTrunkGroupByName(const char *pTrunkGroupName)
{
	unsigned int i = 0;
	for (i = 0; i < m_TrunkGroupList.size(); i++)
	{
		if(strcasecmp(m_TrunkGroupList[i].GetName(), pTrunkGroupName) == 0)
		{			
			return (KFPC_TrunkGroup*)&m_TrunkGroupList[i];
		}		
	}

	//WARNING_LOG(0,"TrunkGroup:%s does not exist",pTrunkGroupName);
	return NULL;
}


unsigned int  KFPC_TrunkGroupMgr::GetIdleChannelByNameEx(const char *pTrunkGroupName,  unsigned int *IdleChannel,unsigned int SrcChannel)
{


	KFPC_TrunkGroup *pTrunkGroup = NULL;


	pTrunkGroup = GetTrunkGroupByName(pTrunkGroupName);
	if (pTrunkGroup == NULL)
	{		
		return KFPC_ERR_TrunkGroupNotFound;
	}
	else
	{
		return pTrunkGroup->GetIdleChannel(SrcChannel,IdleChannel);
	}

}



unsigned int KFPC_TrunkGroupMgr::GetCount()
{
	return m_TrunkGroupList.size();
}

void KFPC_TrunkGroupMgr::DelAllTrunkGroup()
{
	m_TrunkGroupList.clear();
}



KFPC_TrunkGroup* KFPC_TrunkGroupMgr::GetTrunkGroupByIP(const char* Ip)
{
	KFPC_TrunkGroup *pTrunkGroup = NULL;

	for (unsigned int i = 0; i < m_TrunkGroupList.size(); i++)
	{
		pTrunkGroup = &m_TrunkGroupList[i];
		if (pTrunkGroup)
		{
			if(pTrunkGroup->QueryFromAddr(Ip))
			{
				return pTrunkGroup;				
			}
		}
	}

	return NULL;
}

void KFPC_TrunkGroupMgr::PreLoadCfg()
{
	
	TrunkGroupIterator_t	BeginIter = m_TrunkGroupList.begin();
	//TrunkGroupIterator_t	EndIter = m_TrunkGroupList.end();

	for (;BeginIter != m_TrunkGroupList.end();BeginIter++)
	{
		KFPC_TrunkGroup& TrunkGroup = (*BeginIter);

		TrunkGroup.SetOld(true);
	}

}

void KFPC_TrunkGroupMgr::EndLoadCfg()
{
	TrunkGroupIterator_t	BeginIter = m_TrunkGroupList.begin();
	//TrunkGroupIterator_t	EndIter = m_TrunkGroupList.end();  会出问题，有bug

	while(BeginIter !=  m_TrunkGroupList.end())
	{
		KFPC_TrunkGroup& TrunkGroup = (*BeginIter);

		if(TrunkGroup.GetOld())
		{
			INFO_LOG(0,"TrunkGroup:%s removed",TrunkGroup.GetName());
			BeginIter = m_TrunkGroupList.erase(BeginIter);
			
		}
		else
		{
			BeginIter++;
		}
	}

	
}

void KFPC_TrunkGroupMgr::Send_EVT_UpdateTrunkGroup( unsigned int AppID )
{
	TrunkGroupIterator_t	BeginIter = m_TrunkGroupList.begin();
	//TrunkGroupIterator_t	EndIter = m_TrunkGroupList.end();

	for(;BeginIter != m_TrunkGroupList.end();BeginIter++)
	{
		KFPC_TrunkGroup& TrunkGroup = (*BeginIter);

		KFCPTServerAPIHandlerImpInstance->SendTS_EVT_UpdateTrunkGroup(AppID,
			TrunkGroup.GetName());
	}
}

bool KFPC_TrunkGroupMgr::CheckTrunkGroupByName( const char *pTrunkGroupName )
{
	unsigned int i = 0;
	for (i = 0; i < m_TrunkGroupList.size(); i++)
	{
		if(strcasecmp(m_TrunkGroupList[i].GetName(), pTrunkGroupName) == 0)
		{			
			return true;
		}		
	}

	return false;
}

void KFPC_TrunkGroupMgr::DelWatchAppID( unsigned int AppID )
{
	TrunkGroupIterator_t	BeginIter = m_TrunkGroupList.begin();

	for(;BeginIter != m_TrunkGroupList.end();BeginIter++)
	{
		KFPC_TrunkGroup& TrunkGroup = (*BeginIter);
		TrunkGroup.DelWatchAppID(AppID);
	}
}

void KFPC_TrunkGroupMgr::SetIPChannelInService( void )
{
	INFO_LOG(0,"");


	TrunkGroupIterator_t	BeginIter = m_TrunkGroupList.begin();

	for(;BeginIter != m_TrunkGroupList.end();BeginIter++)
	{
		KFPC_TrunkGroup& TrunkGroup = (*BeginIter);

		TrunkGroup.SetIPChannelInService();
	}


}

void KFPC_TrunkGroupMgr::UpdateTrunkGroup()
{
	INFO_LOG(0,"");


	TrunkGroupIterator_t	BeginIter = m_TrunkGroupList.begin();

	for(;BeginIter != m_TrunkGroupList.end();BeginIter++)
	{
		KFPC_TrunkGroup& TrunkGroup = (*BeginIter);

		TrunkGroup.UpdateTrunkGroup();
	}
}