#include "KFPC_NodeMgr.h"


//KFPC_NodeMgr* KFPC_NodeMgr::_Instance = NULL;

KFPC_NodeMgr::KFPC_NodeMgr(void)
{
	

	for (int i=0;i<KFPC_MAX_EH_NODE;i++)
	{
		m_EHNodeList[i].SetID(i);
	}
}


KFPC_NodeMgr::~KFPC_NodeMgr(void)
{
}

KFPC_EHNode* KFPC_NodeMgr::GetNode( unsigned char NodeID )
{
	if(NodeID < KFPC_MAX_EH_NODE)
	{
		return &m_EHNodeList[NodeID];
	}
	else
	{
		ERROR_LOG(0,"NodeID:%u err",NodeID);
		return NULL;
	}
}

KFPC_EHNode* KFPC_NodeMgr::GetNode( char* SwitchID )
{
	for (int i=0;i<KFPC_MAX_EH_NODE;i++)
	{
		if(strcmp(m_EHNodeList[i].GetMainBoardSN(),SwitchID) == 0)
		{
			return &m_EHNodeList[i];
		}
	}
	ERROR_LOG(0,"MainBoardSN:%s err",SwitchID);
	return NULL;
}
KFPC_NodeMgr* KFPC_NodeMgr::GetInstance()
{
	static KFPC_NodeMgr	_Instance;

	//if(_Instance == NULL)
	//{
	//	smart_new(KFPC_NodeMgr,_Instance);
	//}
	return &_Instance;
}

void KFPC_NodeMgr::Reset()
{
	for (int i=0;i<KFPC_MAX_EH_NODE;i++)
	{
		m_EHNodeList[i].Reset(false);
	}
}

void KFPC_NodeMgr::RequestAllLic()
{
	INFO_LOG(0,"");
	for (int i=0;i<KFPC_MAX_EH_NODE;i++)
	{
		if(strlen(m_EHNodeList[i].GetMainBoardSN()) > 0)
		{
			m_EHNodeList[i].GetLic(0);

			//if(strcmp(m_EHNodeList[i].GetMainBoardSN(),"No SerialNo") == 0)
			//{
			//	m_EHNodeList[i].SetInfinityLic();
			//}
			//else
			//{
			//m_EHNodeList[i].GetLic(0);
			//}

		}
	}
}
//
//KFPC_IPMCh* KFPC_NodeMgr::AssignIPMChCh()
//{
//	KFPC_IPMCh*	 pIPMCh = NULL;
//	for (int i = 0; i < KFPC_MAX_EH_NODE; i++)
//	{
//		if (strlen(m_EHNodeList[i].GetMainBoardSN()) > 0)
//		{
//			if ((pIPMCh = m_EHNodeList[i].m_VOIPMgr.AssignIPMChCh()) != NULL)
//			{
//				return pIPMCh;
//			}
//		}
//	}
//
//	return NULL;
//}
//
//bool KFPC_NodeMgr::AssignIVRCh(unsigned short ChID, KFPC_VoiceCh* pVoiceCh[], unsigned int Size/*=1*/, unsigned char* BrdNo/*=NULL*/)
//{
//	for (int i=0;i<KFPC_MAX_EH_NODE;i++)
//	{
//		if(strlen(m_EHNodeList[i].GetMainBoardSN()) > 0)
//		{
//			if(m_EHNodeList[i].m_VoiceMgr.AssignIVRCh(ChID,pVoiceCh,Size,BrdNo))
//			{
//				return true;
//			}
//		}
//	}
//
//	return false;
//}