
#ifndef kfpc_log_h__
#define kfpc_log_h__
/********************************************************************
 * @data:		2012/09/26
 * @details:	26:9:2012   21:52
 * @file: 		d:\MyProgram\通信库\kfpc_com\kfpc_log.h 
 * @author:		KFPC
 * @brief:		日记输出模块
*********************************************************************/

#ifdef WIN32
#pragma warning (disable: 4996) 
#endif
#include <string>
using namespace std;

#include <time.h>
#include "kfpc_time.h"
#include "kfpc_sn64.h"
#include "kfpc_threadtask.h"
#include "kfpc_threadtaskqueue.h"



/*--------------------------------------------------------------------------------------------------------------------------------
 |  Types
 *------------------------------------------------------------------------------------------------------------------------------*/
/**
 *	定义日记级别
 */
typedef enum KFPC_LOG_LEVEL
{
	LL_DEBUGMEM = 0x01,		/**< 内存输出级 */
	LL_DEBUG	= 0x02,		/**< 调试级 */
	LL_INFO		= 0x04,		/**< 消息级 */
	LL_WARNING	= 0x08,		/**< 警告级 */
	LL_ERROR	= 0x10,		/**< 错误级 */
	LL_FATAL	= 0x20,		/**< 故障级 */	
}KFPC_LOG_LEVEL;

/**
 *	日记输出方式
 */
typedef enum KFPC_LOG_OUT_MODE
{	
	LOM_FILE	=	0x01,	/**< 输出到文件 */	
	LOM_CONSOLE	=	0x02	/**< 输出到控制台 */
}KFPC_LOG_OUT_MODE;

#define MAX_ALARM_LOG_COUNT	10

#include <list>
using namespace std;
typedef list<KFPC_ThreadTask*>					LogThreadTaskList_t;
typedef list<KFPC_ThreadTask*>::iterator		LogThreadTaskListIter_t;


/**
 *	日记输出对象
 */
class KFPC_Log
{
private:
	volatile unsigned int	m_ThreadCount;	/**< 线程池数量 */
	THREADID		m_pThreadID;	/**< 线程ID列表 */
	HANDLE_t		m_pThreadHandle;/**< 线程柄列表 */

	LogThreadTaskList_t	m_LogThreadTaskQueue;	/**< 线程任务队列 */
	KFPC_Mutex			m_LogThreadTaskQueueMutex;			/**< 线程互斥 */
	KFPC_Event			m_LogThreadTaskQueueEvent;							/**< 线程事件 */

	//unsigned int	m_OutputMode;						/**< 日记输出方式 */
	//unsigned int	m_FileLogLevel;						/**< 日记文件输出级别 */
	//unsigned int	m_ConsoleLogLevel;					/**< 控制台输出级别 */
	char			m_LogPath[MAX_FILE_NAME_LEN];		/**< 日记文件路径 */	
	char			m_LogFileNamePrefix[MAX_FILE_NAME_LEN];	/**< 日志文件名前缀 */
	char			m_FileName[MAX_FILE_NAME_LEN];		/**< 正在使用的文件名 */	
	
	
	unsigned int	m_MaxKeepBackFilesCount;			/**< 最大保留文件个数 */
	unsigned int	m_MaxFileSize;						/**< 最大文件大小 */
	
	//KFPC_ThreadPool	m_LogManagerThreadPool;				/**< 日记管理线程池 */
	
	


	FILE*			m_LogFileHandle;					/**< 日记文件句柄 */
	FILE*			m_AlarmLogFileHandle;					/**< 日记文件句柄 */
	unsigned int	m_CurrentSize;						/**< 当前文件大小 */
	unsigned int	m_AlarmCurrentSize;						/**< 当前文件大小 */
	string			m_AlarmFileName;							/**< 正在使用的文件名 */	
	string			m_AlarmLogFileNamePrefix;			/**< 日志文件名前缀 */
	KFPC_SN64		m_SN;
	
	string			m_ProgramVersion;					//当前程序版本号
	bool			m_Stop;
protected:
	unsigned int	m_OutputMode;						/**< 日记输出方式 */
	unsigned int	m_FileLogLevel;						/**< 日记文件输出级别 */
	unsigned int	m_ConsoleLogLevel;					/**< 控制台输出级别 */

	KFPC_Mutex		m_Mutex;							/**< 多线程访问互斥对象 */
	bool Output2File(FILE* LogFileHandle,unsigned int&	CurrentSize,long long SN,const char* TimeStr,KFPC_LOG_LEVEL LogLevel,const char* Str,va_list Args,bool AutoWrap);		/**< 输出日记到文件 */
	virtual void Output2Console(long long SN,const char* TimeStr,KFPC_LOG_LEVEL LogLevel,const char* Str,va_list Args,bool AutoWrap);	/**< 输出日记到控制台 */
	virtual void Append2Console(KFPC_LOG_LEVEL LogLevel,const char* Str,va_list Args);

public:	

	const char* GetAlarmLogFileNamePrefix()  { return m_AlarmLogFileNamePrefix.c_str(); }
	void SetAlarmLogFileNamePrefix(const char* val) { m_AlarmLogFileNamePrefix = val; }


	const char* GetAlarmFileName()  { return m_AlarmFileName.c_str(); }
	void SetAlarmFileName(const char*  val) { m_AlarmFileName = val; }

	const char* GetProgramVersion() const { return m_ProgramVersion.c_str(); }
	void SetProgramVersion(const char* val);

	unsigned int GetMaxFileSize() { return m_MaxFileSize; }
	void SetMaxFileSize(unsigned int val) { m_MaxFileSize = val; }

	unsigned int GetMaxKeepBackFilesCount() { return m_MaxKeepBackFilesCount; }
	void SetMaxKeepBackFilesCount(unsigned int val) { m_MaxKeepBackFilesCount = val; }


	const char* GetFileName() { return m_FileName; }
	void SetFileName(const char* val) { strncpy(m_FileName,val,MAX_FILE_NAME_LEN-1); }


	const char* GetLogFileNamePrefix() { return m_LogFileNamePrefix; }
	void SetLogFileNamePrefix(const char* val);
	

	const char* GetLogPath() { return m_LogPath; }
	void SetLogPath(const char* val) { strncpy(m_LogPath,val,MAX_FILE_NAME_LEN-1); }


	unsigned int GetConsoleLogLevel() { return m_ConsoleLogLevel; }
	void SetConsoleLogLevel(unsigned int val) { m_ConsoleLogLevel = val; }


	unsigned int GetFileLogLevel() { return m_FileLogLevel; }
	void SetFileLogLevel(unsigned int val) { m_FileLogLevel = val; }


	unsigned int GetOutputMode() { return m_OutputMode; }
	void SetOutputMode(unsigned int val) { m_OutputMode = val; }


	/**
	 * Method:    	KFPC_Log
	 * FullName:  	KFPC_Log::KFPC_Log
	 * @brief 		构造函数
	 * @param[in] const char * FileNamePrefix	文件名前缀
	 * @return   	
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	KFPC_Log(const char* FileNamePrefix);
	~KFPC_Log(void);

	

	void Debug(const char* str,...);		/**< 输出调试信息 */
	void DebugMem(const char* str,...);		/**< 输出内存调试信息 */
	void Info(const char* str,...);			/**< 一般信息 */
	void Warning(const char* str,...);		/**< 警告信息 */
	void Error(const char* str,...);		/**< 错误信息 */
	void Fatal(const char* str,...);		/**< 故障信息 */

	/**
	 * Method:    	WriteLog
	 * FullName:  	KFPC_Log::WriteLog
	 * @brief 		日记输出
	 * @param[in] KFPC_LOG_LEVEL LogLevel	日记级别
	 * @param[in] const char * Str	日记格式化字符串
	 * @param[in] va_list Args	格式化参数
	 * @return   	void
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	virtual void WriteLog(KFPC_LOG_LEVEL LogLevel,const char* Str,va_list Args,bool AutoWrap = true);
	
	void BeginLog(KFPC_LOG_LEVEL LogLevel,const char* str,...);
	void AppendLog(KFPC_LOG_LEVEL LogLevel,const char* str,...);
	void EndLog(KFPC_LOG_LEVEL LogLevel);
	
	
	void* DoThreadProc();
	void Close();
	int OpenThread();
	int CloseThread();

	bool IsNotCurrentFile(const char* pFileName);

private:	
	

	unsigned int PutTask(KFPC_ThreadTask* pTask);
	KFPC_ThreadTask* GetTask(int Timeout);
	void Clear();

	unsigned long GetTaskSize();

	void PutExitTask();
	int WaitThreadExit();

	void Append2File(KFPC_LOG_LEVEL LogLevel,const char* Str,va_list Args);
	//void Append2Console(KFPC_LOG_LEVEL LogLevel,const char* Str,va_list Args);
	

	FILE* CreateNewLogFile();	/**< 创建新的日记文件，当文件大于指定大小时关闭当前文件，并打开新的文件 */

	FILE* CreateNewAlarmLogFile();
	/**
	 * Method:    	ScanUncompressedLogFile
	 * FullName:  	KFPC_Log::ScanUncompressedLogFile
	 * @brief 		当程序启动时，扫描压缩一下上一次程序退出未压缩的文件
	 * @return   	void
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	void ScanUncompressedLogFile(const char* FileNamePrefix,unsigned int MaxKeepFilesCount);
	/**
	 * Method:    	DelOldLogFile
	 * FullName:  	KFPC_Log::DelOldLogFile
	 * @brief 		扫描日记文件，并删除多余的旧日记文件
	 * @return   	void
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	void ScanLogFilePath(const char* FileNamePrefix,unsigned int MaxKeepFilesCount);
	/**
	 * Method:    	CompressLogFile
	 * FullName:  	KFPC_Log::CompressLogFile
	 * @brief 		压缩日记文件，当单个日记超过设定大小时，会自动创建新的日记文件，并将旧的日记文件压缩
	 * @return   	void
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	void CompressLogFile(const char* pFileName);
};
/*--------------------------------------------------------------------------------------------------------------------------------
 |  Global variables
 *------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Macros
 *------------------------------------------------------------------------------------------------------------------------------*/
//#define ALL_LOG_LEVEL	(LL_DEBUGMEM|LL_DEBUG|LL_WARNING|LL_ERROR|LL_FATAL)	/**< 所有日记级别 */

/**
 * Method:    	KFPC_LOG_LEVEL_TO_STRING
 * FullName:  	KFPC_LOG_LEVEL_TO_STRING
 * @brief 		将日记级别输出字符串
 * @param[in]	KFPC_LOG_LEVEL LogLevel	日记级别
 * @return   	const char*	
 * @pre 		无
 * @par 		示例
 * @see 		引用
 */
static __inline const char* KFPC_LOG_LEVEL_TO_STRING( KFPC_LOG_LEVEL LogLevel )
{

	switch( LogLevel )
	{
	case LL_DEBUGMEM:	return "DEBUGMEM";
	case LL_DEBUG:		return "DEBUG";
	case LL_INFO:		return "INFO";
	case LL_WARNING:	return "WARNING";
	case LL_ERROR:		return "!!!ERROR";
	case LL_FATAL:		return "FATAL";
	}
	return (const char*)"";
}

#endif // kfpc_log_h__

