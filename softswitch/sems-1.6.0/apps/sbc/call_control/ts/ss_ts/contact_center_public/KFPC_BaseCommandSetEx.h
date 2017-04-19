#pragma once
#include "kfpc_basecommand.h"
#include <unordered_set>
#include "KFPC_BaseCmdMgr.h"

typedef unordered_set <unsigned int>				KFPC_CMD_Set_t;
typedef KFPC_CMD_Set_t:: iterator					KFPC_CMD_SetIter_t;
typedef pair<KFPC_CMD_Set_t::iterator, bool>		KFPC_CMD_SetRet_t;

class KFPC_BaseCommandSetEx :
	public KFPC_BaseCommand
{
private:
	
protected:
	KFPC_CMD_Set_t		m_CmdIDSet;
	unsigned int		m_LiveCmdID;		//当前活着的CMDID

	bool				m_First;	
	KFPC_BaseCmdMgr*	m_BaseCmdMgr;
	
	KFPC_BaseCommand*	GetCmd(unsigned int CmdID);
public:
	KFPC_BaseCommandSetEx(
		KFPC_BaseCmdMgr*	BaseCmdMgr,
		unsigned int DstAppID,
		unsigned int UserContext1,
		unsigned int UserContext2,bool SubCmd = false);

	virtual ~KFPC_BaseCommandSetEx(void);
	virtual unsigned int Execute(unsigned int MsgID,KFPC_MSG_TYPE MsgType = KFPC_MSG_TYPE_FIRST,KFPC_MSG_HEADER* MsgHeader= NULL,	void* pMsg = NULL);
	virtual unsigned int Execute2();
	virtual unsigned int BeginExecute(){ return 0;}
	virtual void EndExecute(){}
	virtual void SetResult(unsigned int val)
	{
		m_Result = val;
	}
	void AppendCmd(unsigned int CmdID);

	unsigned int GetLiveCmdID() const { return m_LiveCmdID; }
	void SetLiveCmdID(unsigned int val) { m_LiveCmdID = val; }
};

