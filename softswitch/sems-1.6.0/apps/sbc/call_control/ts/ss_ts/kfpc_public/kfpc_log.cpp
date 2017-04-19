#include "kfpc_linuxwinapi.h"

#include "kfpc_log.h"
#include "kfpc_scanuncompressedlogfiletask.h"
#include "kfpc_compressfiletask.h"
#include "kfpc_scanlogpath.h"
#include <time.h>
#include "kfpc_logex.h"

#ifdef WIN32

#else

	#include <sys/syscall.h>

#endif

static void* ThreadProc( void* param )
{
	KFPC_Log* pLog = (KFPC_Log*)param;

	return pLog->DoThreadProc();
}

void* KFPC_Log::DoThreadProc()
{
	//m_LogEvent.Signal();
	KFPC_ThreadTask*	pThreadTask = NULL;

	INFO_LOG(0,"KFPC_Log::Svc thread start.\n");

	while(!m_Stop)
	{
		pThreadTask = GetTask(20);

		if(pThreadTask != NULL)
		{
			if(pThreadTask->GetThreadTaskType() == TTT_ExitThread)
			{
				smart_delete(pThreadTask);
				
				break;
			}
			else
			{
				time_t Delay =0;

				pThreadTask->DoSvc(&Delay);

				if(Delay > 0)
				{
					WARNING_LOG(0,"Delay:%u second,and task queue size:%u.",Delay,GetTaskSize());
				}

				smart_delete (pThreadTask);
			}	
		}	
	}

	INFO_LOG(0,"KFPC_Log::Svc thread exit.\n");
	return NULL;
}

KFPC_Log::KFPC_Log( const char* FileNamePrefix ):
m_ThreadCount(0),	/**< 线程池数量 */
m_pThreadID(0),	/**< 线程ID列表 */
m_pThreadHandle(0),/**< 线程柄列表 */
m_MaxKeepBackFilesCount(200),
m_MaxFileSize(1024*1024*100),
m_LogFileHandle(NULL),
m_AlarmLogFileHandle(NULL),
m_CurrentSize(0),
m_SN(true),
m_Stop(false),
m_OutputMode(LOM_FILE/*|LOM_CONSOLE*/),
m_FileLogLevel(LL_DEBUG),
m_ConsoleLogLevel(LL_DEBUG)
{
	sprintf(m_LogPath,"./log/%s",FileNamePrefix);
	sprintf(m_LogFileNamePrefix,"%s_",FileNamePrefix);

	m_AlarmLogFileNamePrefix = FileNamePrefix;
	m_AlarmLogFileNamePrefix += "Alarm_";

	m_FileName[0]='\0';

	char* pLogEnv=getenv(KFPC_LOG_DIR);

	if(pLogEnv != NULL)
	{
		sprintf(m_LogPath,"%s/%s",pLogEnv,FileNamePrefix);
	}
	
	//printf("KFPC_Log LogFileNamePrefix:%s,AlarmLogFileNamePrefix:%s\n",m_LogFileNamePrefix,m_AlarmLogFileNamePrefix.c_str());
}

KFPC_Log::~KFPC_Log(void)
{
	Close();
}

/**< 当程序启动的时候，把上一次关闭程序后未压缩的文件压缩 */
void KFPC_Log::ScanUncompressedLogFile(const char* FileNamePrefix,unsigned int MaxKeepFilesCount)
{
	KFPC_ScanUncompressedLogFileTask* pScanUncompressedLogFileTask = NULL;
	smart_new(KFPC_ScanUncompressedLogFileTask(this,FileNamePrefix,MaxKeepFilesCount),pScanUncompressedLogFileTask);

	PutTask(pScanUncompressedLogFileTask);
}

/**< 扫描删除就的日志文件 */
void KFPC_Log::ScanLogFilePath(const char* FileNamePrefix,unsigned int MaxKeepFilesCount)
{
	KFPC_ScanLogPath* pScanLogFileTask = NULL;
	smart_new(KFPC_ScanLogPath(this,FileNamePrefix,MaxKeepFilesCount),pScanLogFileTask);

	PutTask(pScanLogFileTask);

}

/**< 当前的日志文件超过设置大小，对文件进行压缩 */
void KFPC_Log::CompressLogFile(const char* FileName)
{
	KFPC_CompressFileTask* pCompressFileTask = NULL;
	smart_new(KFPC_CompressFileTask(this,FileName),pCompressFileTask);
	PutTask(pCompressFileTask);
}

bool KFPC_Log::Output2File(FILE* LogFileHandle,unsigned int&	CurrentSize, long long SN,const char* TimeStr,KFPC_LOG_LEVEL LogLevel,const char* Str,va_list Args ,bool AutoWrap )
{
	
	if (m_FileLogLevel > (unsigned int)LogLevel)
	{
		/**
		 *	日记级别不匹配
		 */
		return false;
	}

	if(LogFileHandle == NULL)
	{
		return false;
	}

	int WriteSize = 0;


	WriteSize +=fprintf(LogFileHandle,"%s | %6lld | %8s ",
									TimeStr,
									SN,KFPC_LOG_LEVEL_TO_STRING(LogLevel));

	

	WriteSize += vfprintf(LogFileHandle,Str,Args);

	if(AutoWrap)
	{
		fprintf(LogFileHandle,"\n");
	}

	if(WriteSize > 0)
	{
		CurrentSize +=WriteSize;
	}
	else
	{
		CurrentSize = 0xffffffff;
	}	

	//if(LogLevel >= LL_WARNING )
	{
		fflush(LogFileHandle);
	}

	return true;
}

void KFPC_Log::Output2Console(long long SN,const char* TimeStr, KFPC_LOG_LEVEL LogLevel,const char* Str,va_list Args  ,bool AutoWrap)
{
	if (m_ConsoleLogLevel > (unsigned int)LogLevel)
	{
		/**
		 *	日记级别不匹配
		 */
		return;
	}


	printf("%s | %6lld | %8s ",
		TimeStr,
		SN,KFPC_LOG_LEVEL_TO_STRING(LogLevel));

	vprintf(Str,Args);

	if(AutoWrap)
	{
		printf("\n");
	}
	

}

FILE* KFPC_Log::CreateNewLogFile()
{

	if (m_CurrentSize > m_MaxFileSize)	/**< 当文件大于指定大小就关闭文件 */
	{
		fclose(m_LogFileHandle);

		m_LogFileHandle = NULL;
		m_CurrentSize = 0;

		CompressLogFile(m_FileName);
		ScanLogFilePath(m_LogFileNamePrefix,GetMaxKeepBackFilesCount());
	}

	if (m_LogFileHandle == NULL)
	{
		try
		{
			// 初始化日志所在目录
			if (!DirectoryExist(m_LogPath))
			{
				MakeDirectory(m_LogPath);
			}
		}
		catch (...)
		{			
			;
		}

		time_t lNow = time(NULL);
		tm *tm_now = localtime(&lNow);

		/**< 以下处理避免文件冲突 */
		do 
		{

			sprintf(m_FileName, "%s/%s%d%02d%02d_%02d%02d%02d.log",
				m_LogPath,
				m_LogFileNamePrefix,
				tm_now->tm_year + 1900,
				tm_now->tm_mon + 1,
				tm_now->tm_mday,
				tm_now->tm_hour,
				tm_now->tm_min,
				tm_now->tm_sec);

			if (FileExist(m_FileName))
			{
				tm_now->tm_sec++;
			}
			else
			{
				break;
			}
		} while (true);


		// 打开(或创建新的)日志文件
		try
		{
			m_LogFileHandle = fopen(m_FileName,"a");
			
			if(m_ProgramVersion.length() > 0)
			{
				KFPC_Time	t ;
				char	TimeStr[100] = "";

				t.GetMillisecondToStr(TimeStr);

				m_CurrentSize+=fprintf(m_LogFileHandle,"%s |%8s ",
					TimeStr,
					KFPC_LOG_LEVEL_TO_STRING(LL_INFO));


				m_CurrentSize += fprintf(m_LogFileHandle,"Program version:%s",m_ProgramVersion.c_str());
				fprintf(m_LogFileHandle,"\n");
			}

			//printf("CreateNewLogFile FileName:%s\n",m_FileName);
			
		}
		catch (...)
		{			
			return NULL;
		}
	}

	return m_LogFileHandle;
}


FILE* KFPC_Log::CreateNewAlarmLogFile()
{


	if(m_AlarmCurrentSize > m_MaxFileSize)
	{
		fclose(m_AlarmLogFileHandle);

		m_AlarmLogFileHandle = NULL;
		m_AlarmCurrentSize = 0;

		CompressLogFile(m_AlarmFileName.c_str());
		ScanLogFilePath(m_AlarmLogFileNamePrefix.c_str(),GetMaxKeepBackFilesCount());
	}



	if (m_AlarmLogFileHandle == NULL)
	{
		try
		{
			// 初始化日志所在目录
			if (!DirectoryExist(m_LogPath))
			{
				MakeDirectory(m_LogPath);
			}
		}
		catch (...)
		{			
			;
		}

		time_t lNow = time(NULL);
		tm *tm_now = localtime(&lNow);

		/**< 以下处理避免文件冲突 */
		do 
		{
			char	AlarmFileName[MAX_FILE_NAME_LEN];

			sprintf(AlarmFileName, "%s/%s%d%02d%02d_%02d%02d%02d.log",
				m_LogPath,
				m_AlarmLogFileNamePrefix.c_str(),
				tm_now->tm_year + 1900,
				tm_now->tm_mon + 1,
				tm_now->tm_mday,
				tm_now->tm_hour,
				tm_now->tm_min,
				tm_now->tm_sec);

			m_AlarmFileName = AlarmFileName;

			if (FileExist(AlarmFileName))
			{
				tm_now->tm_sec++;
			}
			else
			{
				break;
			}
		} while (true);


		// 打开(或创建新的)日志文件
		try
		{
			m_AlarmLogFileHandle = fopen(m_AlarmFileName.c_str(),"a");

			if(m_ProgramVersion.length() > 0)
			{
				KFPC_Time	t ;
				char	TimeStr[100] = "";

				t.GetMillisecondToStr(TimeStr);

				m_AlarmCurrentSize+=fprintf(m_AlarmLogFileHandle,"%s |%8s ",
					TimeStr,
					KFPC_LOG_LEVEL_TO_STRING(LL_INFO));


				m_AlarmCurrentSize += fprintf(m_AlarmLogFileHandle,"Program version:%s",m_ProgramVersion.c_str());
				fprintf(m_AlarmLogFileHandle,"\n");
			}

			//printf("CreateNewAlarmLogFile FileName:%s\n",m_AlarmFileName.c_str());
		}
		catch (...)
		{			
			return NULL;
		}
	}

	return m_AlarmLogFileHandle;
}

void KFPC_Log::WriteLog( KFPC_LOG_LEVEL LogLevel,const char* Str,va_list Args ,bool AutoWrap)
{
	KFPC_AutoMutex	AutoMutex(&m_Mutex);
	//m_Mutex.lock();


	CreateNewLogFile();
	CreateNewAlarmLogFile();

	//long long SN = m_SN.GetSN();
	KFPC_Time	t ;
	char	TimeStr[100] = "";
	
	t.GetMillisecondToStr(TimeStr);

	THREADID ThreadID = 0;

#ifdef WIN32
	ThreadID = GetCurrentThreadId();
#else
	ThreadID = syscall(SYS_gettid);//pthread_self();
#endif

	if(m_OutputMode & LOM_FILE)
	{
		Output2File(m_LogFileHandle,m_CurrentSize,ThreadID,TimeStr, LogLevel,Str,Args,AutoWrap);

		if(LogLevel >= LL_WARNING)
		{
			 Output2File(m_AlarmLogFileHandle,m_AlarmCurrentSize,ThreadID,TimeStr, LogLevel,Str,Args,AutoWrap);
		}

	}
	
	if(m_OutputMode & LOM_CONSOLE)
	{
		Output2Console(ThreadID,TimeStr, LogLevel,Str,Args,AutoWrap);
	}
	

	//m_Mutex.unlock();
}

void KFPC_Log::Debug( const char* str,... )
{
	if (m_FileLogLevel > LL_DEBUG)
	{
		//printf("no debug\n");
		return ;
	}

	va_list args;

	va_start(args,str);

	WriteLog(LL_DEBUG,str,args);
	va_end(args);
}

void KFPC_Log::DebugMem( const char* str,... )
{
	if (m_FileLogLevel > LL_DEBUGMEM)
	{
		return ;
	}

	va_list args;

	va_start(args,str);

	WriteLog(LL_DEBUGMEM,str,args);
	va_end(args);
}

void KFPC_Log::Info( const char* str,... )
{
	if (m_FileLogLevel > LL_INFO)
	{
		return ;
	}

	va_list args;

	va_start(args,str);

	WriteLog(LL_INFO,str,args);
	va_end(args);
}

void KFPC_Log::Warning( const char* str,... )
{
	if (m_FileLogLevel > LL_WARNING)
	{
		return ;
	}

	va_list args;

	va_start(args,str);

	WriteLog(LL_WARNING,str,args);
	va_end(args);
}

void KFPC_Log::Error( const char* str,... )
{
	if (m_FileLogLevel > LL_ERROR)
	{
		return ;
	}

	va_list args;

	va_start(args,str);

	WriteLog(LL_ERROR,str,args);
	va_end(args);
}

void KFPC_Log::Fatal( const char* str,... )
{
	if (m_FileLogLevel > LL_FATAL)
	{
		return ;
	}

	va_list args;

	va_start(args,str);

	WriteLog(LL_FATAL,str,args);
	va_end(args);
}

void KFPC_Log::BeginLog( KFPC_LOG_LEVEL LogLevel,const char* Str,... )
{
	if (m_FileLogLevel > LogLevel)
	{
		return ;
	}

	va_list Args;

	va_start(Args,Str);

	m_Mutex.lock();

	CreateNewLogFile();
	//long long SN = m_SN.GetSN();
	KFPC_Time	t ;
	char	TimeStr[100] = "";

	t.GetMillisecondToStr(TimeStr);

	THREADID ThreadID = 0;

#ifdef WIN32
	ThreadID = GetCurrentThreadId();
#else
	ThreadID = pthread_self();
#endif

	if(m_OutputMode & LOM_FILE)
	{
		Output2File(m_LogFileHandle,m_CurrentSize,ThreadID,TimeStr, LogLevel,Str,Args,false);

	}


	if(m_OutputMode & LOM_CONSOLE)
	{
		Output2Console(ThreadID,TimeStr, LogLevel,Str,Args,false);
	}

	va_end(Args);
}

void KFPC_Log::AppendLog(KFPC_LOG_LEVEL LogLevel, const char* str,... )
{
	if (m_FileLogLevel > LogLevel)
	{
		return ;
	}

	va_list args;

	va_start(args,str);

	if(m_OutputMode & LOM_FILE)
	{
		Append2File(LogLevel,str,args);
	}

	if(m_OutputMode & LOM_CONSOLE)
	{
		Append2Console(LogLevel,str,args);
	}

	va_end(args);

}

void KFPC_Log::Append2File(KFPC_LOG_LEVEL LogLevel, const char* Str,va_list Args )
{

	if (m_FileLogLevel > (unsigned int)LogLevel)
	{
		/**
		 *	日记级别不匹配
		 */
		return;
	}

	if(m_LogFileHandle == NULL)
	{
		return;
	}

	m_CurrentSize += vfprintf(m_LogFileHandle,Str,Args);
}

void KFPC_Log::Append2Console(KFPC_LOG_LEVEL LogLevel, const char* Str,va_list Args )
{
	if (m_ConsoleLogLevel > (unsigned int)LogLevel)
	{
		/**
		 *	日记级别不匹配
		 */
		return;
	}

	vprintf(Str,Args);
}

void KFPC_Log::EndLog(KFPC_LOG_LEVEL LogLevel)
{
	AppendLog(LogLevel,"\n");
	fflush(m_LogFileHandle);

	m_Mutex.unlock();
}

void KFPC_Log::SetLogFileNamePrefix( const char* val )
{
	
	m_Mutex.lock();	

//	if (m_CurrentSize > 0)	/**< 当文件大于指定大小就关闭文件 */
	{
		if(m_LogFileHandle)
		{
			fclose(m_LogFileHandle);
		}
		
		m_LogFileHandle = NULL;
		m_CurrentSize = 0;

		CompressLogFile(m_FileName);
		ScanLogFilePath(m_LogFileNamePrefix,GetMaxKeepBackFilesCount());
	}

	
	//if (m_AlarmCurrentSize > 0)	/**< 当文件大于指定大小就关闭文件 */
	{
		if(m_AlarmLogFileHandle)
		{
			fclose(m_AlarmLogFileHandle);
		}
		
		m_AlarmLogFileHandle = NULL;
		m_AlarmCurrentSize = 0;

		CompressLogFile(m_AlarmFileName.c_str());
		ScanLogFilePath(m_AlarmLogFileNamePrefix.c_str(),MAX_ALARM_LOG_COUNT);
	}

	sprintf(m_LogFileNamePrefix,"%s_comlib",val);

	char	AlarmFileNamePrefix[MAX_FILE_NAME_LEN];

	sprintf(AlarmFileNamePrefix,"%s_Alarm_comlib",val);

	m_AlarmLogFileNamePrefix = AlarmFileNamePrefix;

	m_Mutex.unlock();
	INFO_LOG(0,"LogFileNamePrefix:%s,AlarmFileNamePrefix:%s",m_LogFileNamePrefix,m_AlarmLogFileNamePrefix.c_str());

	ScanUncompressedLogFile(m_LogFileNamePrefix,GetMaxKeepBackFilesCount());

	ScanUncompressedLogFile(m_AlarmLogFileNamePrefix.c_str(),MAX_ALARM_LOG_COUNT);
	
	CreateNewLogFile();
	CreateNewAlarmLogFile();
	WARNING_LOG(0,"LogFileNamePrefix:%s,AlarmFileNamePrefix:%s",m_LogFileNamePrefix,m_AlarmLogFileNamePrefix.c_str());

}



void KFPC_Log::Close()
{
	m_Stop = true;
	CloseThread();
	fflush(m_LogFileHandle);
}

int KFPC_Log::OpenThread()
{

	if(m_ThreadCount == 0)
	{
		m_ThreadCount = 1;

		unsigned int Ret = Create_Thread(ThreadProc,this,&m_pThreadID,&m_pThreadHandle);
		
		INFO_LOG(0,"KFPC_Log::OpenThread ThreadID:%u,ThreadHandle:%u,Ret:%u",m_pThreadID,m_pThreadHandle,Ret);

		ScanUncompressedLogFile(m_LogFileNamePrefix,GetMaxKeepBackFilesCount());
		ScanLogFilePath(m_LogFileNamePrefix,GetMaxKeepBackFilesCount());

		ScanUncompressedLogFile(m_AlarmLogFileNamePrefix.c_str(),MAX_ALARM_LOG_COUNT);
		ScanLogFilePath(m_AlarmLogFileNamePrefix.c_str(),MAX_ALARM_LOG_COUNT);

		return 0;
	}
	else
	{
		return -1;
	}
}

int KFPC_Log::CloseThread()
{
	if(m_ThreadCount > 0)
	{
		PutExitTask();

		return WaitThreadExit();
	}
	else
	{
		return -1;
	}
}

void KFPC_Log::PutExitTask()
{

	KFPC_ExitThreadTask*	pExitThreadTask = NULL;

	smart_new(KFPC_ExitThreadTask,pExitThreadTask) ;

	PutTask(pExitThreadTask);

}

int KFPC_Log::WaitThreadExit()
{
	void* ExitCode = NULL;

	ThreadJoin(m_pThreadID,m_pThreadHandle,&ExitCode);

	m_pThreadID = 0;
	m_pThreadHandle = 0;
	m_ThreadCount = 0;

	Clear();
	return 0;
}



unsigned int KFPC_Log::PutTask( KFPC_ThreadTask* pTask )
{
	KFPC_AutoMutex	AutoMutex(&m_LogThreadTaskQueueMutex);

	if(pTask == NULL)	return m_LogThreadTaskQueue.size();

	//m_LogThreadTaskQueueMutex.lock();
	m_LogThreadTaskQueue.push_back(pTask);
	
	//DEBUG_LOG(0,"LogThreadTaskQueue size:%u",m_LogThreadTaskQueue.size());
	
	//m_LogThreadTaskQueueMutex.unlock();
	m_LogThreadTaskQueueEvent.Signal();
	

	return m_LogThreadTaskQueue.size();
}

KFPC_ThreadTask* KFPC_Log::GetTask(int Timeout )
{
	KFPC_ThreadTask* pTask = NULL;

	m_LogThreadTaskQueueMutex.lock();
	if(m_LogThreadTaskQueue.empty())
	{
		if(Timeout != 0)
		{
			m_LogThreadTaskQueueMutex.unlock();
			m_LogThreadTaskQueueEvent.WaitEx(Timeout);
			m_LogThreadTaskQueueMutex.lock();

			if(!m_LogThreadTaskQueue.empty())
			{
				pTask = m_LogThreadTaskQueue.front();
				m_LogThreadTaskQueue.pop_front();
			}
		}
	}
	else
	{
		pTask = m_LogThreadTaskQueue.front();
		m_LogThreadTaskQueue.pop_front();
	}

	m_LogThreadTaskQueueMutex.unlock();

	if(m_LogThreadTaskQueue.size() > 50)
	{
		Warning("log thread task list size:%d too big!!!!!!!!!!",m_LogThreadTaskQueue.size());
	}

	//DEBUG_LOG(0,"LogThreadTaskQueue size:%u",m_LogThreadTaskQueue.size());

	return pTask;
}


void KFPC_Log::Clear()
{
	Info("log thread task list size:%d",m_LogThreadTaskQueue.size());

	m_LogThreadTaskQueueMutex.lock();
	ThreadTaskListIter_t	Iter = m_LogThreadTaskQueue.begin();
	for(;Iter != m_LogThreadTaskQueue.end();Iter++)
	{
		// KFPC_ThreadTask* p= *Iter;

		smart_delete(*Iter);
	}

	m_LogThreadTaskQueue.clear();

	m_LogThreadTaskQueueMutex.unlock();
}

void KFPC_Log::SetProgramVersion( const char* val )
{
	m_ProgramVersion = val;
	//INFO_LOG(0,"Program version:%s",val);
}

bool KFPC_Log::IsNotCurrentFile( const char* pFileName )
{


	if((strcmp(m_FileName,pFileName) == 0) ||
		(strcmp(m_AlarmFileName.c_str(),pFileName) == 0))
	{
		return false;
	}
	else
	{
		return true;
	}
}

unsigned long KFPC_Log::GetTaskSize()
{
	KFPC_AutoMutex	AutoMutex(&m_LogThreadTaskQueueMutex);

	return m_LogThreadTaskQueue.size();

}
