#include "kfpc_logex.h"
#include "KFPC_BaseCommand.h"
#include "kfpc_sn32.h"
#include "KFPC_StringUtils.h"
#include "KFPC_TServerErr.h"
#include "KFPC_ContactCenterPublicDef.h"

static	KFPC_SN32	g_CmdID;

KFPC_BaseCommand::KFPC_BaseCommand(unsigned int MsgID,
	KFPC_MSG_TYPE MsgType,
	unsigned long long CallID,
	unsigned int DstAppID,
	unsigned int UserContext1,
	unsigned int UserContext2,
	bool SubCmd):
m_MsgID(MsgID),			/**< 消息ID */
m_CallID(CallID),
//m_MemPool(pMemPool),			/**< 内存池对象 */
m_ID(0),
m_MsgType(MsgType),
m_Result(0),
m_UserContext1(UserContext1),
m_UserContext2(UserContext2),
m_Cause(16),
m_DstAppID(DstAppID),
m_SubCmd(SubCmd),
m_TypeIsCmdSet(false),
m_StopExeFlag(false),
m_NextCmdID(0),
m_ElseCmdID(0),
m_MsgPoint(NULL),
m_MsgHeader(NULL),
//m_PendMsg(0),
m_DonotCheckRet(false),
m_CmdClassID(0),
m_ProxyCmd(this),
m_CallOutCallID(0),
m_CreateTime(time(NULL))
{
	m_ID = g_CmdID.GetSN();
	CMD_DEBUG_LOG(m_CallID,"MsgID:0x%x",MsgID);
}

KFPC_BaseCommand::KFPC_BaseCommand( unsigned int MsgID,
	KFPC_MSG_TYPE MsgType,
	unsigned long long CallID,
	unsigned int DstAppID,
	unsigned int UserContext1,
	unsigned int UserContext2,
	KFPC_BaseCommand* ProxyCmd /*= NULL*/ ):
m_MsgID(MsgID),			/**< 消息ID */
	m_CallID(CallID),
	//m_MemPool(pMemPool),			/**< 内存池对象 */
	m_ID(0),
	m_MsgType(MsgType),
	m_Result(0),
	m_UserContext1(UserContext1),
	m_UserContext2(UserContext2),
	m_Cause(16),
	m_DstAppID(DstAppID),
	m_SubCmd((NULL == ProxyCmd)?false:true),
	m_TypeIsCmdSet(false),
	m_StopExeFlag(false),
	m_NextCmdID(0),
	m_ElseCmdID(0),
	m_MsgPoint(NULL),
	m_MsgHeader(NULL),
	//m_PendMsg(0),
	m_DonotCheckRet(false),
	m_CmdClassID(0),
	m_ProxyCmd((NULL == ProxyCmd)?this:ProxyCmd),
	m_CallOutCallID(0),
	m_CreateTime(time(NULL))
{
	m_ID = g_CmdID.GetSN();
	CMD_DEBUG_LOG(m_CallID,"MsgID:0x%x",MsgID);
}

KFPC_BaseCommand::~KFPC_BaseCommand(void)
{
	
}

void KFPC_BaseCommand::operator delete( void *p)
{
	//KFPC_CmdMgrInstance->GetKFPC_MemPool()->Free(p);
	GetKFPC_MemPool()->Free(p);
}

void * KFPC_BaseCommand::operator new( size_t s )
{
	//return KFPC_CmdMgrInstance->GetKFPC_MemPool()->Alloc(s);
	return GetKFPC_MemPool()->Alloc(s);

}

unsigned int KFPC_BaseCommand::CheckMsg( unsigned int MsgID,KFPC_MSG_TYPE MsgType)
{

	if(m_MsgID != MsgID || 	m_MsgType != MsgType)
	{
		char MsgIDStr[KFPC_MAX_MSG_ID_STR_LEN]="";
		DEBUG_LOG(m_CallID,"CmdID:%u,ChID:%u,Cmd MsgID:%s<>MsgID:%s,MsgType:%s<>MsgType:%s not match",
			m_ID,
			CallIDToChannel(m_CallID),
			MsgIDToStr(m_MsgID,MsgIDStr),
			MsgIDToStr(MsgID,MsgIDStr),
			MsgTypeToStr(m_MsgType),
			MsgTypeToStr(MsgType));

		return KFPC_ERR_MsgIDNotMatch;
	}
	else
	{
		//INFO_LOG(m_CallID,"CmdID:%u,ChID:%u,MsgID:%s,MsgType:%s", m_ID,CallIDToChannel(m_CallID),MsgIDToStr(MsgID,MsgIDStr),MsgTypeToStr(MsgType));
		return 0;
	}
}



unsigned int KFPC_BaseCommand::Execute2()
{
	return Execute(m_MsgID,m_MsgType);
}

unsigned int KFPC_BaseCommand::Cancel()
{
	char MsgIDStr[KFPC_MAX_MSG_ID_STR_LEN]="";
	INFO_LOG(m_CallID,"CmdID:%u,ChID:%u,MsgID:%s,MsgType:%s", m_ID,CallIDToChannel(m_CallID),MsgIDToStr(m_MsgID,MsgIDStr),MsgTypeToStr(m_MsgType));

	SendRSP(KFPC_ERR_CmdCancel);
	return KFPC_ERR_CmdCancel;
}

unsigned int KFPC_BaseCommand::GetCmdIDByResult( unsigned int Result )
{
	if(Result == 0)
	{
		return m_NextCmdID;
	}
	else
	{
		KFPC_ResultCMDIDMapIter_t	Iter = m_ResultCmdID.find(Result);
		if(Iter == m_ResultCmdID.end())
		{
			return m_ElseCmdID;
		}
		else
		{
			return Iter->second;
		}
	}
}

void KFPC_BaseCommand::AddResultCmdID( unsigned int Result,unsigned int CmdID )
{
	m_ResultCmdID.insert(KFPC_ResultCMDIDMapPair_t(Result,CmdID));
}

KFPC_MemPool* KFPC_BaseCommand::GetKFPC_MemPool()
{
	static KFPC_MemPool	m_KFPC_MemPool;
	return &m_KFPC_MemPool;
}

void KFPC_BaseCommand::SetMsgHeader( KFPC_MSG_HEADER* val )
{
	m_MsgHeader = val;
}

void KFPC_BaseCommand::SetMsgPoint( void* val )
{
	m_MsgPoint = val;
}

void KFPC_BaseCommand::SetCallID( unsigned long long& val )
{
	
	DEBUG_LOG(m_CallID,"CmdID:%u CallID:0x%llx--->CallID:0x%llx",m_ID,m_CallID,val);
	m_CallID = val;
}

unsigned int KFPC_BaseCommand::ExtPendMsg()
{
	CMD_ERROR_LOG(m_CallID,"Do nothing");
	return KFPC_ERR_MsgIDNotMatch;
}

void KFPC_BaseCommand::SetProxyCmd( KFPC_BaseCommand* val )
{
	if(val == NULL)
	{
		CMD_ERROR_LOG(m_CallID,"ProxyCmd is NULL");
	}
	else
	{
		m_ProxyCmd = val;
	}
}

void KFPC_BaseCommand::SetMoreInfo( const char* val )
{
	m_MoreInfo = val;
	INFO_LOG(m_CallID,"MoreInfo:%s",val);
}

void KFPC_BaseCommand::SetCallOutCallID( unsigned long long val )
{
	

	DEBUG_LOG(m_CallID,"CmdID:%u CallOut CallID:0x%llx--->CallOut CallID:0x%llx",m_ID,m_CallOutCallID,val);
	
	m_CallOutCallID = val;
}


void KFPC_BaseCommand::WarningLog()
{
	char StrTime[64];
	TimeToStr(StrTime,m_CreateTime);
	CMD_WARNING_LOG(m_CallID,"Create Time:%s",StrTime);
}
