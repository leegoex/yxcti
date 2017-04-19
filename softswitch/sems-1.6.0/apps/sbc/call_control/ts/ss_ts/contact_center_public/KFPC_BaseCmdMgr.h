#pragma once

#include "kfpc_mempool.h"
#include "KFPC_BaseCommand.h"
#include <unordered_map>
using namespace std;
typedef unordered_map <unsigned int, KFPC_BaseCommand*>		CommandMap_t;
typedef CommandMap_t:: iterator								CommandMapIter_t;
typedef pair<unsigned int, KFPC_BaseCommand*>				CommandMapPair_t;
typedef pair< CommandMap_t:: iterator, bool >				CommandMapInsertResult_t;


class KFPC_BaseCmdMgr
{
protected:
	//KFPC_MemPool	m_KFPC_MemPool;					/**< ÄÚ´æ³Ø */

	

	CommandMapIter_t   m_CmdIter;
public:
	
	CommandMap_t	m_CommandMap;					/**< ÃüÁîMAP */
	KFPC_BaseCmdMgr(void);
	virtual ~KFPC_BaseCmdMgr(void);

	KFPC_BaseCommand* GetExeCmd();

	//CommandMapIter_t& GetEndCmdIter();
	//CommandMapIter_t& GetBeginCmdIter();
	CommandMapIter_t& GetExeCmdIter();
	void SetCmdIter(CommandMapIter_t iter);
	void SetBeginCmdIter();
	void SetNextCmdIter();
	KFPC_BaseCommand* GetCmd( unsigned int CmdID );

	void FreeCmd( KFPC_BaseCommand* pCmd );

	void FreeCmd( unsigned int CmdID );

	void FreeCmd( CommandMapIter_t Iter );

	CommandMap_t& GetCommandMap()  {return m_CommandMap;}

	void CheckInvalidCmd();
};

