#ifndef KFPC_AppMainThread_h__
#define KFPC_AppMainThread_h__

#include "kfpc_threadpool.h"
#include "KFPC_ConfigFile.h"
#include "kfpc_msg.h"
#include "KFPC_API_Handle.h"
#include "kfpc_id.h"
#include "KFPC_LoopHandler.h"
#include "kfpc_api.h"

//
#include <unordered_set>
typedef unordered_set <KFPC_LoopHandler*>					KFPC_LoopHandlerSet_t;
typedef KFPC_LoopHandlerSet_t:: iterator					KFPC_LoopHandlerSetIter_t;
typedef pair<KFPC_LoopHandlerSet_t::iterator, bool>			KFPC_LoopHandlerSetRet_t;

#define MAX_LOOPHANDLER		32

class KFPC_AppMainThread:public KFPC_ThreadPool
{
private:
	
	bool	m_Start;
	int InitComLib(KFPC_ConfigFile* pConfigFile);

	int ReadLibCfg( KFPC_ConfigFile* pConfigFile, KFPC_LIB_PARAMS &LibParams );
	void* DoThreadProc(KFPC_ThreadParamInfo* pThreadParamInfo);
	void ProcNetMsg(int TimeOut);
	int ProcOutTime();
	void ProcAppMsg(KFPC_MSG_HEADER* pMsg);

	KFPC_API_Handler*	m_KFPC_API_HanderMap[KFPC_ID_CLASS_ALLOCATION_COMMON_END];
	KFPC_LoopHandler*		m_KFPC_LoopHandlerSet[MAX_LOOPHANDLER];
	unsigned int			m_LoopHandlerSize;	
	//KFPC_LoopHandlerSet_t	m_KFPC_LoopHandlerSet;
	KFPC_API_Handler*		m_ElseMsgHandler;		//其它消息处理
	int	m_TimeOut;

public:

	//KFPC_Semaphore		m_Semaphore;

	virtual unsigned int PutTask(KFPC_ThreadTask* pTask);

	int GetTimeOut() { return m_TimeOut; }
	void SetTimeOut(int val) { m_TimeOut = val; }

	static KFPC_AppMainThread* GetInstance()
	{
		static KFPC_AppMainThread _Instance;
		return &_Instance;
	}

	KFPC_AppMainThread(void);
	~KFPC_AppMainThread(void);
	void Start(KFPC_ConfigFile* pConfigFile,unsigned int ThreadCount = 1,int TimeOut = 500);

	unsigned int StartInitClient(KFPC_ConfigFile* pConfigFile,unsigned int ThreadCount = 1,int TimeOut = 500);

	unsigned int StartKFPC_InitServer(const char*			AppName ,
		unsigned int	AppID,
		unsigned int	AppGroupID ,
		unsigned int	AppType,
		unsigned int	MasterFlag ,
		unsigned int	ListenPort ,
		unsigned int	MulticatePort,	//"12815";
		const char*			MulticateIP,		//"224.12.8.13",
		char*			pConnectPassWord,
		unsigned int	ThreadPoolSize,
		unsigned int	KeepLiveTime ,
		unsigned int	KeepLiveCount ,
		unsigned int	MaxSocketCount ,
		unsigned int	OutPutMode ,
		unsigned int	FileLogLevel ,
		unsigned int	ConsoleLogLevel ,
		unsigned int ThreadCount = 1,
		int TimeOut = 500);

	void Close();

	void RegisterElseMsgHander(KFPC_API_Handler* pKfpcApi);
	void RemoverElseMsgHander();

	/**
	 * FullName:  	KFPC_AppMainThread::RegisterMsgHander
	 * @brief 		注册消息处理器
	 * @param[in,out] unsigned int MsgGroupID
	 * @param[in,out] KFPC_API_Handler * pKfpcApi
	 * @return   	bool
	 */
	bool RegisterMsgHander(unsigned int MsgGroupID,KFPC_API_Handler* pKfpcApi);
	/**
	 * FullName:  	KFPC_AppMainThread::RemoverMsgHander
	 * @brief 		删除消息处理器
	 * @param[in,out] unsigned int MsgGroupID
	 * @return   	bool
	 */
	bool RemoverMsgHander(unsigned int MsgGroupID);

	bool RegisterLoopHandler(KFPC_LoopHandler* pLoopHandler,const char* Name);
	bool RemoverLoopHandler(KFPC_LoopHandler* pLoopHandler);


};
#define KFPC_AppMainThreadInstance	KFPC_AppMainThread::GetInstance()
#endif // KFPC_AppMainThread_h__
