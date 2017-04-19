#pragma once
#include "KFPC_EHNode.h"
#include "KFPC_TServerDef.h"

class KFPC_NodeMgr
{
private:
	KFPC_EHNode	m_EHNodeList[KFPC_MAX_EH_NODE];
	//static KFPC_NodeMgr* _Instance;
public:
	

	static KFPC_NodeMgr* GetInstance();

	
	KFPC_EHNode*	GetNode(unsigned char NodeID);
	KFPC_EHNode*	GetNode(char* SwitchID);

	KFPC_NodeMgr(void);
	~KFPC_NodeMgr(void);

	void Reset();
	void RequestAllLic();
	//KFPC_IPMCh*	AssignIPMChCh();
	//bool AssignIVRCh( unsigned short ChID,KFPC_VoiceCh* pVoiceCh[],unsigned int Size=1,unsigned char* BrdNo=NULL);
	//static void Destory()
	//{
	//	if(_Instance != NULL)
	//	{
	//		smart_delete(_Instance);
	//		_Instance = NULL;
	//	}
	//}
};

#define KFPC_NodeMgrInstance	KFPC_NodeMgr::GetInstance()

