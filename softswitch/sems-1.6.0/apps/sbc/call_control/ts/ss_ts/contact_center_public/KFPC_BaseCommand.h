#pragma once
#include "kfpc_msg.h"
#include "KFPC_EH_MsgID.h"
#include "kfpc_mempool.h"
//class KFPC_Channel;

#include <list>
#include <unordered_map>
#include <string>

using namespace std;
typedef list<unsigned int>			KFPC_CmdIDList;
typedef KFPC_CmdIDList::iterator	KFPC_CmdIDListIter;

typedef unordered_map <unsigned int, unsigned int>			KFPC_ResultCMDIDMap_t;
typedef KFPC_ResultCMDIDMap_t:: iterator					KFPC_ResultCMDIDMapIter_t;
typedef pair<unsigned int,  unsigned int>					KFPC_ResultCMDIDMapPair_t;
typedef pair< KFPC_ResultCMDIDMap_t:: iterator, bool >		KFPC_ResultCMDIDMapInsertResult_t;

#define CMD_DEBUG_LOG(CallID,format, ...)		DEBUG_LOG(CallID,		"CmdID:%u," format,m_ID,##__VA_ARGS__)
#define CMD_INFO_LOG(CallID,format, ...)		INFO_LOG(CallID,		"CmdID:%u," format,m_ID,##__VA_ARGS__)
#define CMD_WARNING_LOG(CallID,format, ...)		WARNING_LOG(CallID,		"CmdID:%u," format,m_ID,##__VA_ARGS__)
#define CMD_ERROR_LOG(CallID,format, ...)		ERROR_LOG(CallID,		"CmdID:%u," format,m_ID,##__VA_ARGS__)
#define CMD_FATAL_LOG(CallID,format, ...)		FATAL_LOG(CallID,		"CmdID:%u," format,m_ID,##__VA_ARGS__)

#define KFPC_CMD_CLASS_ID_GEN(APPTYPE, ID)		(((unsigned int)(APPTYPE) << 16) + (ID))


class KFPC_BaseCommand
{	
protected:
	time_t			m_CreateTime;
	unsigned int	m_MsgID;			/**< 消息ID */
	KFPC_MSG_TYPE	m_MsgType;

	unsigned int	m_ID;							/**< 命令ID */
	unsigned int	m_Result;			/**< 执行结果 */
	
	unsigned int	m_UserContext1;		/**< 用户上下文 */
	unsigned int	m_UserContext2;		/**< 用户上下文 */
	unsigned long long m_CallID;		/**< Call ID */
	unsigned short	m_Cause;
	unsigned int	m_DstAppID;
	bool			m_SubCmd;			/**< 当前为子命令 */
	
	bool            m_TypeIsCmdSet;     /**< 命令是单个命令还是命令集*/
	bool            m_StopExeFlag;
	unsigned int    m_StopResult;

	unsigned int	m_NextCmdID;		//后继CMDID
	unsigned int	m_ElseCmdID;		//
	
	KFPC_ResultCMDIDMap_t	m_ResultCmdID;		//结果分支CMD
	void*						m_MsgPoint;			//当前消息指针
	KFPC_MSG_HEADER*			m_MsgHeader;			//当前消息指针
	

	//unsigned int				m_CmdObserver;		//当前命令观察家
	//unsigned int				m_PendMsg;			//挂起消息
	bool						m_DonotCheckRet;		//Tserver cmd set 不检查结果
	unsigned int				m_CmdClassID;
	KFPC_BaseCommand*			m_ProxyCmd;			//代理CMD
	
	string						m_MoreInfo;

	unsigned long long			m_CallOutCallID;		//这个变量的定义，实属无奈，其实是一个局部变量的作用
	//string						m_SubClassName;			//子类名称
	
protected:
	void SetMsgType(KFPC_MSG_TYPE val) { m_MsgType = val; }
public:		

	time_t GetCreateTime() const { return m_CreateTime; }
	void SetCreateTime(time_t val) { m_CreateTime = val; }


	//const char* GetSubClassName()  { return m_SubClassName.c_str(); }
	//void SetSubClassName(const char* val) { m_SubClassName = val; }

	unsigned long long GetCallOutCallID() const { return m_CallOutCallID; }
	virtual void SetCallOutCallID(unsigned long long val);

	const char* GetMoreInfo()  { return m_MoreInfo.c_str(); }
	virtual void SetMoreInfo(const char* val);

	KFPC_BaseCommand* GetProxyCmd() { return m_ProxyCmd; }
	void SetProxyCmd(KFPC_BaseCommand* val);
	//unsigned int GetCmdObserver() { return m_CmdObserver; }
	//void SetCmdObserver(unsigned int val) { m_CmdObserver = val; }
	unsigned int GetCmdClassID() { return m_CmdClassID; }
	void SetCmdClassID(unsigned int val) { m_CmdClassID = val; }

	bool GetDonotCheckRet() { return m_DonotCheckRet; }
	void SetDonotCheckRet(bool val) { m_DonotCheckRet = val; }

	virtual unsigned int ExtPendMsg();


	KFPC_MSG_TYPE GetMsgType() { return m_MsgType; }

	virtual KFPC_MSG_HEADER* GetMsgHeader() { return m_MsgHeader; }
	virtual void SetMsgHeader(KFPC_MSG_HEADER* val);

	bool GetSubCmd() { return m_SubCmd; }

	virtual void* GetMsgPoint() { return m_MsgPoint; }
	virtual void SetMsgPoint(void* val);

	unsigned int GetNextCmdID() { return m_NextCmdID; }
	void SetNextCmdID(unsigned int val) { m_NextCmdID = val; }

	unsigned int GetElseCmdID() { return m_ElseCmdID; }
	void SetElseCmdID(unsigned int val) { m_ElseCmdID = val; }

	void AddResultCmdID(unsigned int Result,unsigned int CmdID);

	unsigned int GetCmdIDByResult(unsigned int Result);

	static KFPC_MemPool* GetKFPC_MemPool();

	unsigned int GetDstAppID() { return m_DstAppID; }
	void SetDstAppID(unsigned int val) { m_DstAppID = val; }
	unsigned int GetID() { return m_ID; }

	KFPC_BaseCommand(unsigned int MsgID,KFPC_MSG_TYPE MsgType,unsigned long long CallID,unsigned int DstAppID,unsigned int UserContext1,unsigned int UserContext2,bool SubCmd = false);
	KFPC_BaseCommand(unsigned int MsgID,KFPC_MSG_TYPE MsgType,unsigned long long CallID,unsigned int DstAppID,unsigned int UserContext1,unsigned int UserContext2,KFPC_BaseCommand* ProxyCmd);

	virtual ~KFPC_BaseCommand(void);

	virtual unsigned int Execute(
		unsigned int				MsgID,
		KFPC_MSG_TYPE				MsgType		= KFPC_MSG_TYPE_FIRST,	
		KFPC_MSG_HEADER*			MsgHeader	= NULL,				//当前消息指针
		void*						pMsg		= NULL					//当前消息指针
		) = 0;

	virtual unsigned int Execute2();
	virtual unsigned int Cancel();	

	virtual unsigned int GetExeCmdID()   {return m_ID;}
	

	virtual void SendRSP(unsigned int Ret){}


	void SetStopFlag(bool StopExeFlag,unsigned int Result) {m_StopExeFlag = StopExeFlag;m_StopResult = Result;}
	bool GetStopFlag() {return m_StopExeFlag;}

	bool GetCmdTypeIsCmdSet()    {return m_TypeIsCmdSet;}
	unsigned int GetResult() { return m_Result; }
	virtual void SetResult(unsigned int val) { m_Result = val; }
	unsigned int& GetUserContext1() { return m_UserContext1; }
	void SetUserContext1(unsigned int& val) { m_UserContext1 = val; }
	unsigned int& GetUserContext2() { return m_UserContext2; }
	void SetUserContext2(unsigned int& val) { m_UserContext2 = val; }

	unsigned long long& GetCallID() { return m_CallID; }
	virtual void SetCallID(unsigned long long& val);

	
	unsigned int GetMsgID()  {return m_MsgID;}
	void *operator new (size_t s) ;
    void operator delete (void *p);  

	unsigned short GetCause() { return m_Cause; }
	void SetCause(unsigned short val) { m_Cause = val; }

	/**
	 * FullName:  	KFPC_BaseCommand::CheckMsg
	 * @brief 		检查消息ID是否匹配
	 * @param[in,out] unsigned int MsgID
	 * @param[in,out] KFPC_MSG_TYPE MsgType
	 * @return   	unsigned int
	 */
	virtual unsigned int CheckMsg(unsigned int MsgID,KFPC_MSG_TYPE MsgType);

	virtual unsigned int BeginExecute(){ return 0;}
	virtual void EndExecute(){}
	
	/**
	 * FullName:  	KFPC_BaseCommand::AppDisconnect
	 * @brief 		收到APP下线处理
	 * @param[in,out] unsigned int AppID
	 * @param[in,out] unsigned int AppType
	 * @return   	unsigned int 返回0释放Cmd
	 */
	virtual unsigned int AppDisconnect(unsigned int AppID,unsigned int AppType){return -1;}
	virtual unsigned int CallReleased(unsigned int Cause){return -1;}

	
	void WarningLog();
};

#define DisplayCmd(MsgID, MsgType)\
{\
	char MsgIDStr[KFPC_MAX_MSG_ID_STR_LEN]="";\
	INFO_LOG(m_CallID,"CmdID:%u,MsgID:%s,MsgType:%s", m_ID,	MsgIDToStr(MsgID,MsgIDStr),MsgTypeToStr(MsgType));\
}

