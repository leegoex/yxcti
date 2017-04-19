#pragma once
#include "kfpc_basecommand.h"
class KFPC_BaseCommandSet :
	public KFPC_BaseCommand
{
protected:
	KFPC_CmdIDList		m_CmdIDList;
	KFPC_CmdIDListIter	m_ExeIter;
	bool				m_ExeOrCancel;		/**< 执行还是Cancel ，如果是执行m_ExeIter++,否则m_ExeIter--*/
	bool				m_First;
	
public:
	KFPC_BaseCommandSet(unsigned int MsgID,
		KFPC_MSG_TYPE MsgType,
		unsigned long long& CallID,
		unsigned int DstAppID,
		unsigned int UserContext1,
		unsigned int UserContext2);
	
	virtual ~KFPC_BaseCommandSet(void);
	virtual unsigned int Execute(unsigned int MsgID,KFPC_MSG_TYPE MsgType = KFPC_MSG_TYPE_FIRST,KFPC_MSG_HEADER* MsgHeader= NULL,void* pMsg = NULL);
	virtual unsigned int Execute2();
	virtual unsigned int Cancel();
	virtual unsigned int BeginExecute(){ return 0;}
	virtual void EndExecute(){}
	virtual void SetResult(unsigned int val);
	virtual unsigned int GetExeCmdID() {return (*m_ExeIter); }
	virtual void SetPlayContent(char *pPlayContent){};

};

