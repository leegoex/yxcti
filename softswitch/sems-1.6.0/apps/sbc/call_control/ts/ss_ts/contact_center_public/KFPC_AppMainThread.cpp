#include "KFPC_AppMainThread.h"
#include "kfpc_api.h"
#include "kfpc_logex.h"
#include "KFPC_ComApiHandler.h"
#include "kfpc_log.h"
#include "kfpc_guid.h"

KFPC_AppMainThread::KFPC_AppMainThread(void):
m_TimeOut(500),
m_ElseMsgHandler(NULL),
m_LoopHandlerSize(0)
//m_Semaphore(1)
{
	m_Start = false;

	for(int i=0;i<KFPC_ID_CLASS_ALLOCATION_COMMON_END;i++)
	{
		m_KFPC_API_HanderMap[i] = NULL;
	}

	KFPC_GUID	GUID;

	unsigned char	HostIdentify[KFPC_MAX_GUID_LEN];
	GUID.GetHostID(HostIdentify);
	
	char	UniqueIDStr[512];
	
	Buf2HexStr(HostIdentify,sizeof(HostIdentify),UniqueIDStr,128);

	for(int i=0;i<MAX_LOOPHANDLER;i++)
	{
		m_KFPC_LoopHandlerSet[i]= NULL;
	}
	

	INFO_LOG(0,"HostID:%s",UniqueIDStr);

	//RegisterMsgHander(KFPC_ID_CLASS_COM_API,KFPC_ComApiHandler::GetInstance());
}

KFPC_AppMainThread::~KFPC_AppMainThread(void)
{
	Close();
}

void KFPC_AppMainThread::Start( KFPC_ConfigFile* pConfigFile,unsigned int ThreadCount,int TimeOut )
{
	INFO_LOG(0,"ConfigFile:%s",pConfigFile->GetFileName());

	if(!m_Start)
	{
		m_TimeOut = TimeOut;

		//初始化通信库
		if(0 != InitComLib(pConfigFile))
		{
			ERROR_LOG(0,"Failed to initial com lib.");
			return ;
		}

		//{
		//	SYSTEM_INFO si;
		//	GetSystemInfo(&si);

		//	ThreadCount = si.dwNumberOfProcessors;
		//}

		//启动线程
		if(0 != Open(PREFIX_EXPRESSION_VALUE,ThreadCount))
		{
			ERROR_LOG(0,"open thread pool fail.");
		}

		m_Start = true;
	}

}
void KFPC_AppMainThread::Close()
{
	if(m_Start)
	{
		INFO_LOG(0,"");
		//停止线程
		KFPC_ThreadPool::Close("AppMainThread");
		KFPC_WakeMsgFilter(-1);
		//关闭网络
		KFPC_CloseComLib();	
		
	}

}

int KFPC_AppMainThread::InitComLib(KFPC_ConfigFile* pConfigFile)
{

	INFO_LOG(0,"");


	KFPC_LIB_PARAMS	LibParams;
	memset(&LibParams,0,sizeof(KFPC_LIB_PARAMS));
	KFPC_InitServerLibParam(&LibParams,"kfpc_app",0,0);

	unsigned int Ret = 0;

	if(0 != (Ret = ReadLibCfg(pConfigFile, LibParams)))
	{
		return Ret;
	}

	if(KFPC_InitComLib(&LibParams) != 0)
	{
		return -1;
	}

	return 0;
}

void* KFPC_AppMainThread::DoThreadProc(KFPC_ThreadParamInfo* pThreadParamInfo)
{
	KFPC_ThreadTask*	pThreadTask = NULL;
	DEBUG_LOG(0,"start");

	while(true)
	{

		time_t	TaskTime = time(NULL);

		while((pThreadTask = m_ThreadTaskQueue.GetTask(0))!= NULL)
		{

			if(pThreadTask->GetThreadTaskType() == TTT_ExitThread)
			{
				smart_delete(pThreadTask);
				DEBUG_LOG(0,"exit");

				return NULL;
			}
			else
			{
				time_t Delay =0;
				pThreadTask->DoSvc();

				if(Delay > 0)
				{
					WARNING_LOG(0,"Delay:%u second,and task queue size:%u.",Delay,GetTaskSize());
				}

				smart_delete (pThreadTask);
			}

			/**< 确保单次循环不要超过单个定时 */
			if((time(NULL) - TaskTime) >  KFPC_ONE_LOOP_TIME)
			{
				WARNING_LOG(0,"PROC task over %d second",time(NULL) - TaskTime);
				break;
			}
		}

		
		//m_Semaphore.SemWait();

		ProcNetMsg(m_TimeOut);	
		
		//m_Semaphore.SemPost();

		ProcOutTime();

		//KFPC_LoopHandlerSetIter_t BeginIter = m_KFPC_LoopHandlerSet.begin();
		////KFPC_LoopHandlerSetIter_t EndIter = m_KFPC_LoopHandlerSet.end();

		//for(;BeginIter != m_KFPC_LoopHandlerSet.end();BeginIter++)
		//{
		//	while((*BeginIter)->Run() == 0);
		//	//(*BeginIter)->Run();
		//}
		
		
		unsigned int i=0;
		for(;i<m_LoopHandlerSize && i<MAX_LOOPHANDLER;i++)
		{
			if(m_KFPC_LoopHandlerSet[i] != NULL)
			{
				TaskTime = time(NULL);

				while(m_KFPC_LoopHandlerSet[i]->Run() == 0)
				{
					if((time(NULL) - TaskTime) >  KFPC_ONE_LOOP_TIME)
					{
						WARNING_LOG(0,"PROC Loop handler over %d second",time(NULL) - TaskTime);
						break;
					}
				}
			}
		}

	}

	INFO_LOG(0,"exit.");
	return NULL;
}

void KFPC_AppMainThread::ProcNetMsg(int TimeOut)
{
	KFPC_MSG_HEADER*	pMsg = NULL;
	int	Ret = 0;

	unsigned int RecvConut = 50;

	do
	{
		pMsg = NULL;

		if((Ret = KFPC_ReceiveMsg(-1,TimeOut,&pMsg)) == 0)
		{
			ProcAppMsg(pMsg);
			KFPC_ReleaseMsg(pMsg);
		}
		else
		{
			break;
		}

	}while((RecvConut--) > 0 && TimeOut == 0);
}

int KFPC_AppMainThread::ProcOutTime()
{
	return -1;
}

void KFPC_AppMainThread::ProcAppMsg( KFPC_MSG_HEADER* pMsg )
{
	unsigned int MsgGroupID = KFPC_MSG_ID_GET_GROUP(pMsg->un32MsgId);

	if(MsgGroupID < KFPC_ID_CLASS_ALLOCATION_COMMON_END)
	{
		if(NULL != m_KFPC_API_HanderMap[MsgGroupID])
		{
			m_KFPC_API_HanderMap[MsgGroupID]->RecvMsg(pMsg);
		}
		else
		{
			if(m_ElseMsgHandler != NULL)
			{
				m_ElseMsgHandler->RecvMsg(pMsg);
			}
			else
			{
				WARNING_LOG(0,"MsgGroupID:%s not register.",KFPC_ID_CLASS_COM_TO_STRING(KFPC_MSG_ID_GEN(MsgGroupID,0)));
			}
			

		}
	}
	else
	{
		ERROR_LOG(0,"MsgGroupID:0x%x too large.",MsgGroupID);
	}

}

bool KFPC_AppMainThread::RegisterMsgHander( unsigned int MsgGroupID,KFPC_API_Handler* pKfpcApihander )
{
	
	if(MsgGroupID < KFPC_ID_CLASS_ALLOCATION_COMMON_END)
	{
		if(NULL != m_KFPC_API_HanderMap[MsgGroupID])
		{
			WARNING_LOG(0,"MsgGroupID:%s exist.",KFPC_ID_CLASS_COM_TO_STRING(KFPC_MSG_ID_GEN(MsgGroupID,0)));
		}

		m_KFPC_API_HanderMap[MsgGroupID] = pKfpcApihander;

		INFO_LOG(0,"MsgGroupID:%s.",KFPC_ID_CLASS_COM_TO_STRING(KFPC_MSG_ID_GEN(MsgGroupID,0)));

		return true;
	}
	else
	{
		ERROR_LOG(0,"MsgGroupID:0x%x too large.",MsgGroupID);
		return false;
	}
}

bool KFPC_AppMainThread::RemoverMsgHander( unsigned int MsgGroupID )
{
	if(MsgGroupID < KFPC_ID_CLASS_ALLOCATION_COMMON_END)
	{
		if(NULL != m_KFPC_API_HanderMap[MsgGroupID])
		{
			m_KFPC_API_HanderMap[MsgGroupID] = NULL;
		}
		else
		{
			WARNING_LOG(0,"MsgGroupID:%s not exist.",KFPC_ID_CLASS_COM_TO_STRING(KFPC_MSG_ID_GEN(MsgGroupID,0)));
		}

		return true;
	}
	else
	{
		ERROR_LOG(0,"MsgGroupID:0x%x too large.",MsgGroupID);
		return false;
	}
}

bool KFPC_AppMainThread::RegisterLoopHandler( KFPC_LoopHandler* pLoopHandler ,const char* Name)
{
	//KFPC_LoopHandlerSetRet_t Ret = m_KFPC_LoopHandlerSet.insert(pLoopHandler);
	for(int i=0;i<MAX_LOOPHANDLER;i++)
	{
		if(m_KFPC_LoopHandlerSet[i] == NULL)
		{
			m_KFPC_LoopHandlerSet[i] = pLoopHandler;
			m_LoopHandlerSize ++;
			INFO_LOG(0,"pLoopHandler:0x%x,LoopHandler name:%s,LoopHandlerSet size:%u",pLoopHandler,Name,m_LoopHandlerSize);
			return true;
		}
	}
	WARNING_LOG(0,"pLoopHandler:0x%x,LoopHandler name:%s,LoopHandlerSet size:%u fail.",pLoopHandler,Name,m_LoopHandlerSize);
	return false;

	//INFO_LOG(0,"pLoopHandler:0x%x,LoopHandler name:%s,LoopHandlerSet size:%u",pLoopHandler,Name,m_KFPC_LoopHandlerSet.size());
	//return Ret.second;
}

bool KFPC_AppMainThread::RemoverLoopHandler( KFPC_LoopHandler* pLoopHandler )
{
	INFO_LOG(0,"pLoopHandler:0x%x,LoopHandlerSet size:%u",pLoopHandler,m_LoopHandlerSize);
	if(pLoopHandler == NULL)	return false;

	unsigned int i=0;
	for(;i<m_LoopHandlerSize && i<MAX_LOOPHANDLER;i++)
	{
		if(m_KFPC_LoopHandlerSet[i] == pLoopHandler)
		{
			m_KFPC_LoopHandlerSet[i] = NULL;			

			for(;i<(m_LoopHandlerSize-1) && i<MAX_LOOPHANDLER;i++)
			{
				m_KFPC_LoopHandlerSet[i] = m_KFPC_LoopHandlerSet[i+1];			
			}
			
			m_LoopHandlerSize --;

			INFO_LOG(0,"pLoopHandler:0x%x,LoopHandlerSet size:%u",pLoopHandler,m_LoopHandlerSize);
			return true;
		}
	}

	WARNING_LOG(0,"pLoopHandler:0x%x not exist,LoopHandlerSet size:%u",pLoopHandler,m_LoopHandlerSize);
	return false;

	//if(m_KFPC_LoopHandlerSet.erase(pLoopHandler) > 0)
	//{
	//	INFO_LOG(0,"pLoopHandler:0x%x,LoopHandlerSet size:%u",pLoopHandler,m_KFPC_LoopHandlerSet.size());
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
}

void KFPC_AppMainThread::RegisterElseMsgHander( KFPC_API_Handler* pKfpcApi )
{
	if(m_ElseMsgHandler != NULL)
	{
		WARNING_LOG(0,"update else msg handler");
	}
	else
	{
		INFO_LOG(0,"");
	}
	m_ElseMsgHandler = pKfpcApi;
}

void KFPC_AppMainThread::RemoverElseMsgHander()
{
	m_ElseMsgHandler = NULL;
	INFO_LOG(0,"");
}

unsigned int KFPC_AppMainThread::StartInitClient(  KFPC_ConfigFile* pConfigFile,unsigned int ThreadCount,int TimeOut)
{

	if(!m_Start)
	{

		m_TimeOut = TimeOut;

		KFPC_LIB_PARAMS	LibParams;
		memset(&LibParams,0,sizeof(KFPC_LIB_PARAMS));

		KFPC_InitClientLibParam(&LibParams,"");
		unsigned int Ret = 0;

		if(0 != (Ret = ReadLibCfg(pConfigFile, LibParams)))
		{
			return Ret;
		}

		LibParams.AppInfo.AppID = 0;

		//LibParams.AppInfo.AppType = AppType;
		//LibParams.KeepLiveTime = KeepLiveTime;
		//LibParams.KeepLiveTimeCount = KeepLiveCount;
		//LibParams.LogOutputMode = OutPutMode;
		//LibParams.FileLogLevel = FileLogLevel;
		//LibParams.ConsoleLogLevel = ConsoleLogLevel;
		//strncpy(LibParams.AuthPassWord,pConnectPassWord,KFPC_MAX_PASSWD_LEN);

		Ret = KFPC_InitComLib(&LibParams);

		if(Ret != 0)
		{
			return Ret;
		}

		//启动线程
		if(0 != (Ret = Open(PREFIX_EXPRESSION_VALUE,ThreadCount)))
		{
			ERROR_LOG(0,"open thread pool fail.");
			return Ret;
		}

		m_Start = true;
		return 0;
	}
	else
	{
		return 0;
	}
}

unsigned int KFPC_AppMainThread::StartKFPC_InitServer(const char*			AppName ,
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
	unsigned int ThreadCount ,
	int TimeOut )
{


	if(!m_Start)
	{
		m_TimeOut = TimeOut;


		KFPC_LIB_PARAMS	LIB_PARAMS;

		KFPC_InitServerLibParam(&LIB_PARAMS,AppName,AppID,AppGroupID);

		LIB_PARAMS.AppInfo.AppType = AppType;
		LIB_PARAMS.AppInfo.MasterFlag = MasterFlag;
		LIB_PARAMS.AppInfo.ListenPort = ListenPort;
		LIB_PARAMS.MulticastPort = MulticatePort;
		

		strcpy(LIB_PARAMS.MutticastIP,MulticateIP);
		LIB_PARAMS.ThreadPoolSize = ThreadPoolSize;
		LIB_PARAMS.KeepLiveTime = KeepLiveTime;
		LIB_PARAMS.KeepLiveTimeCount = KeepLiveCount;
		LIB_PARAMS.MaxSocketCount = MaxSocketCount;
		LIB_PARAMS.LogOutputMode = OutPutMode;
		LIB_PARAMS.FileLogLevel = FileLogLevel;
		LIB_PARAMS.ConsoleLogLevel = ConsoleLogLevel;
		strncpy(LIB_PARAMS.AuthPassWord,pConnectPassWord,KFPC_MAX_PASSWD_LEN);

		unsigned int Ret = KFPC_InitComLib(&LIB_PARAMS);

		INFO_LOG(0,"AppName:%s,AppID:%u,AppGroupID:%u,	MasterFlag:%u,ListenPort:%u,"
			"MulticatePort:%u,MulticateIP:%s,ThreadPoolSize:%u,KeepLiveTime:%u,"
			"KeepLiveCount:%u,MaxSocketCount:%u,OutPutMode:%u ,FileLogLevel:%u,ConsoleLogLevel:%u,Ret:%u",
			AppName ,
			AppID ,
			AppGroupID,
			MasterFlag ,
			ListenPort ,
			MulticatePort ,	//"12815";
			MulticateIP ,	//"224.12.8.13",
			ThreadPoolSize,
			KeepLiveTime ,
			KeepLiveCount,
			MaxSocketCount,
			OutPutMode ,
			FileLogLevel,
			ConsoleLogLevel,
			Ret
			);

		if(Ret != 0)
		{
			return Ret;
		}

		//启动线程
		if(0 != (Ret = Open(PREFIX_EXPRESSION_VALUE,ThreadCount)))
		{
			ERROR_LOG(0,"open thread pool fail.");
			return Ret;
		}

		m_Start = true;
		return 0;
	}
	else
	{
		return 0;
	}
}

int KFPC_AppMainThread::ReadLibCfg( KFPC_ConfigFile* pConfigFile, KFPC_LIB_PARAMS &LibParams )
{
	if(pConfigFile->GetAppName(LibParams.AppInfo.AppName,KFPC_API_NAME_MAX_LEN) != 0)
	{
		return -1;
	}

	if(pConfigFile->GetAppGroupID(LibParams.AppInfo.AppGroupID) != 0)
	{
		return -1;
	}
	else
	{
		if(LibParams.AppInfo.AppGroupID < 0)
		{
			ERROR_LOG(0,"AppGroupID must be >= 0.");
			return -1;
		}
	}

	if(pConfigFile->GetAppID(LibParams.AppInfo.AppID) != 0)
	{
		return -1;
	}
	else
	{
		if(LibParams.AppInfo.AppID > KFPC_MAX_APP_ID)
		{
			ERROR_LOG(0,"AppID:%d is too large(<=50000).",LibParams.AppInfo.AppID);
			return -1;
		}
	}

	if(pConfigFile->GetAppType(LibParams.AppInfo.AppType) != 0)
	{
		return -1;
	}
	else
	{
		if(LibParams.AppInfo.AppType < 0 || LibParams.AppInfo.AppType > KFPC_APP_TYPE_END)
		{
			ERROR_LOG(0,"AppType:%d is invalid.",LibParams.AppInfo.AppType);
			return -1;
		}
	}

	if(pConfigFile->GetComConsoleLogLevel(LibParams.ConsoleLogLevel) != 0)
	{
		ERROR_LOG(0,"ComConsoleLogLevel:%d is invalid,to use default value.",LibParams.ConsoleLogLevel);
		LibParams.ConsoleLogLevel = 0;
	}
	else
	{
		//if(LibParams.ConsoleLogLevel < LL_DEBUGMEM || LibParams.ConsoleLogLevel > LL_FATAL)
		//{
		//	WARNING_LOG(0,"Com consoleLogLevel value is invalid,to use default value.\n");
		//}
	}

	if(pConfigFile->GetComFileLogLevel(LibParams.FileLogLevel) != 0)
	{
		ERROR_LOG(0,"GetComFileLogLevel:%d is invalid,to use default value.",LibParams.FileLogLevel);
		LibParams.FileLogLevel = 0;
	}
	else
	{
		//if(LibParams.FileLogLevel < LL_DEBUGMEM || LibParams.FileLogLevel > LL_FATAL)
		//{
		//	WARNING_LOG(0,"Com FileLogLevel value is invalid,to use default value.\n");
		//}
	}

	if(pConfigFile->GetComLogOutPutMode(LibParams.LogOutputMode) != 0)
	{
		ERROR_LOG(0,"GetComLogOutPutMode:%d is invalid,to use default value.",LibParams.LogOutputMode);
		LibParams.LogOutputMode = 0;
	}
	else
	{
		if(LibParams.LogOutputMode < 0 || LibParams.LogOutputMode > (LOM_CONSOLE|LOM_FILE))
		{
			ERROR_LOG(0,"Com LogOutputMode value is invalid,to use default value.");
		}
	}

	if(pConfigFile->GetKeepLiveTime(LibParams.KeepLiveTime) != 0)
	{
		return -1;
	}
	else
	{
		if(LibParams.KeepLiveTime < 0)
		{
			WARNING_LOG(0,"KeepLiveTime value is invalid,to use default value.");
		}
	}

	if(pConfigFile->GetKeepLiveTimeCount(LibParams.KeepLiveTimeCount) != 0)
	{
		return -1;
	}
	else
	{
		if(LibParams.KeepLiveTimeCount < 0)
		{
			WARNING_LOG(0,"KeepLiveTimeCount value is invalid,to use default value.");
		}
	}



	if(pConfigFile->GetMasgetFlag(LibParams.AppInfo.MasterFlag) != 0)
	{
		return -1;
	}

	if(pConfigFile->GetMaxSocketCount(LibParams.MaxSocketCount) != 0)
	{
		return -1;
	}
	else
	{
		if(LibParams.MaxSocketCount < 0)
		{		
			WARNING_LOG(0,"MaxSocketCount value is invalid,to use default value.");
		}
	}

	if(pConfigFile->GetMsgFilterCount(LibParams.MsgFilterCount) != 0)
	{
		return -1;
	}
	else
	{
		if(LibParams.MsgFilterCount < 0)
		{
			WARNING_LOG(0,"MsgFilterCount value is invalid,to use default value.");
		}
	}

	if(pConfigFile->GetMulticastPort(LibParams.MulticastPort) != 0)
	{
		return -1;
	}
	else
	{
		if(LibParams.MulticastPort < 0)
		{
			WARNING_LOG(0,"MulticastPort[%d] must be >= 0.",LibParams.MulticastPort);
		}
	}

	if(pConfigFile->GetMulticastIP(LibParams.MutticastIP,KFPC_MAX_IP_LEN) != 0)
	{
		return -1;
	}

	if(pConfigFile->GetListenPort(LibParams.AppInfo.ListenPort) != 0)
	{
		return -1;
	}
	else
	{
		if(LibParams.AppInfo.ListenPort < 0)
		{
			LibParams.AppInfo.ListenPort = -1;
		}
	}

	if(pConfigFile->GetAppThreadPoolSize(LibParams.ThreadPoolSize) != 0)
	{
		return -1;
	}


	char	AuthPassWord[KFPC_MAX_PASSWD_LEN]="";	
	int		Len = KFPC_MAX_PASSWD_LEN;
	if(pConfigFile->GetAuthPassWord(AuthPassWord,Len) == 0)
	{
		strncpy(LibParams.AuthPassWord,AuthPassWord,KFPC_MAX_PASSWD_LEN);
	}


	LibParams.MaxSocketCount = (LibParams.MaxSocketCount > 256)?LibParams.MaxSocketCount:256;

	INFO_LOG(0,"LogOutputMode:%u,ConsoleLogLevel:%u,FileLogLevel:%u,AppName:%s,AppID:%u,KeepLiveTime:%u,KeepLiveTimeCount:%u,MulticastPort:%u,MutticastIP:%s,MaxSocketCount:%u",
		LibParams.LogOutputMode,
		LibParams.ConsoleLogLevel,
		LibParams.FileLogLevel,
		LibParams.AppInfo.AppName,
		LibParams.AppInfo.AppID,
		LibParams.KeepLiveTime,
		LibParams.KeepLiveTimeCount,
		LibParams.MulticastPort,
		LibParams.MutticastIP,
		LibParams.MaxSocketCount);

	return 0;
}

unsigned int KFPC_AppMainThread::PutTask( KFPC_ThreadTask* pTask )
{
	if(m_TimeOut != 0)
	{
		KFPC_WakeMsgFilter(-1);
	}

	unsigned int Size =  KFPC_ThreadPool::PutTask(pTask);

	if((Size % 10) == 0)
	{
		DEBUG_LOG(0,"Size:%u,TimeOut:%u",Size,m_TimeOut);
	}
	

	return Size;
}