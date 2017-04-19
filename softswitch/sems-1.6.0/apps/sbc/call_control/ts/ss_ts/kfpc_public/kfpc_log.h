
#ifndef kfpc_log_h__
#define kfpc_log_h__
/********************************************************************
 * @data:		2012/09/26
 * @details:	26:9:2012   21:52
 * @file: 		d:\MyProgram\ͨ�ſ�\kfpc_com\kfpc_log.h 
 * @author:		KFPC
 * @brief:		�ռ����ģ��
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
 *	�����ռǼ���
 */
typedef enum KFPC_LOG_LEVEL
{
	LL_DEBUGMEM = 0x01,		/**< �ڴ������ */
	LL_DEBUG	= 0x02,		/**< ���Լ� */
	LL_INFO		= 0x04,		/**< ��Ϣ�� */
	LL_WARNING	= 0x08,		/**< ���漶 */
	LL_ERROR	= 0x10,		/**< ���� */
	LL_FATAL	= 0x20,		/**< ���ϼ� */	
}KFPC_LOG_LEVEL;

/**
 *	�ռ������ʽ
 */
typedef enum KFPC_LOG_OUT_MODE
{	
	LOM_FILE	=	0x01,	/**< ������ļ� */	
	LOM_CONSOLE	=	0x02	/**< ���������̨ */
}KFPC_LOG_OUT_MODE;

#define MAX_ALARM_LOG_COUNT	10

#include <list>
using namespace std;
typedef list<KFPC_ThreadTask*>					LogThreadTaskList_t;
typedef list<KFPC_ThreadTask*>::iterator		LogThreadTaskListIter_t;


/**
 *	�ռ��������
 */
class KFPC_Log
{
private:
	volatile unsigned int	m_ThreadCount;	/**< �̳߳����� */
	THREADID		m_pThreadID;	/**< �߳�ID�б� */
	HANDLE_t		m_pThreadHandle;/**< �̱߳��б� */

	LogThreadTaskList_t	m_LogThreadTaskQueue;	/**< �߳�������� */
	KFPC_Mutex			m_LogThreadTaskQueueMutex;			/**< �̻߳��� */
	KFPC_Event			m_LogThreadTaskQueueEvent;							/**< �߳��¼� */

	//unsigned int	m_OutputMode;						/**< �ռ������ʽ */
	//unsigned int	m_FileLogLevel;						/**< �ռ��ļ�������� */
	//unsigned int	m_ConsoleLogLevel;					/**< ����̨������� */
	char			m_LogPath[MAX_FILE_NAME_LEN];		/**< �ռ��ļ�·�� */	
	char			m_LogFileNamePrefix[MAX_FILE_NAME_LEN];	/**< ��־�ļ���ǰ׺ */
	char			m_FileName[MAX_FILE_NAME_LEN];		/**< ����ʹ�õ��ļ��� */	
	
	
	unsigned int	m_MaxKeepBackFilesCount;			/**< ������ļ����� */
	unsigned int	m_MaxFileSize;						/**< ����ļ���С */
	
	//KFPC_ThreadPool	m_LogManagerThreadPool;				/**< �ռǹ����̳߳� */
	
	


	FILE*			m_LogFileHandle;					/**< �ռ��ļ���� */
	FILE*			m_AlarmLogFileHandle;					/**< �ռ��ļ���� */
	unsigned int	m_CurrentSize;						/**< ��ǰ�ļ���С */
	unsigned int	m_AlarmCurrentSize;						/**< ��ǰ�ļ���С */
	string			m_AlarmFileName;							/**< ����ʹ�õ��ļ��� */	
	string			m_AlarmLogFileNamePrefix;			/**< ��־�ļ���ǰ׺ */
	KFPC_SN64		m_SN;
	
	string			m_ProgramVersion;					//��ǰ����汾��
	bool			m_Stop;
protected:
	unsigned int	m_OutputMode;						/**< �ռ������ʽ */
	unsigned int	m_FileLogLevel;						/**< �ռ��ļ�������� */
	unsigned int	m_ConsoleLogLevel;					/**< ����̨������� */

	KFPC_Mutex		m_Mutex;							/**< ���̷߳��ʻ������ */
	bool Output2File(FILE* LogFileHandle,unsigned int&	CurrentSize,long long SN,const char* TimeStr,KFPC_LOG_LEVEL LogLevel,const char* Str,va_list Args,bool AutoWrap);		/**< ����ռǵ��ļ� */
	virtual void Output2Console(long long SN,const char* TimeStr,KFPC_LOG_LEVEL LogLevel,const char* Str,va_list Args,bool AutoWrap);	/**< ����ռǵ�����̨ */
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
	 * @brief 		���캯��
	 * @param[in] const char * FileNamePrefix	�ļ���ǰ׺
	 * @return   	
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
	 */
	KFPC_Log(const char* FileNamePrefix);
	~KFPC_Log(void);

	

	void Debug(const char* str,...);		/**< ���������Ϣ */
	void DebugMem(const char* str,...);		/**< ����ڴ������Ϣ */
	void Info(const char* str,...);			/**< һ����Ϣ */
	void Warning(const char* str,...);		/**< ������Ϣ */
	void Error(const char* str,...);		/**< ������Ϣ */
	void Fatal(const char* str,...);		/**< ������Ϣ */

	/**
	 * Method:    	WriteLog
	 * FullName:  	KFPC_Log::WriteLog
	 * @brief 		�ռ����
	 * @param[in] KFPC_LOG_LEVEL LogLevel	�ռǼ���
	 * @param[in] const char * Str	�ռǸ�ʽ���ַ���
	 * @param[in] va_list Args	��ʽ������
	 * @return   	void
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
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
	

	FILE* CreateNewLogFile();	/**< �����µ��ռ��ļ������ļ�����ָ����Сʱ�رյ�ǰ�ļ��������µ��ļ� */

	FILE* CreateNewAlarmLogFile();
	/**
	 * Method:    	ScanUncompressedLogFile
	 * FullName:  	KFPC_Log::ScanUncompressedLogFile
	 * @brief 		����������ʱ��ɨ��ѹ��һ����һ�γ����˳�δѹ�����ļ�
	 * @return   	void
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
	 */
	void ScanUncompressedLogFile(const char* FileNamePrefix,unsigned int MaxKeepFilesCount);
	/**
	 * Method:    	DelOldLogFile
	 * FullName:  	KFPC_Log::DelOldLogFile
	 * @brief 		ɨ���ռ��ļ�����ɾ������ľ��ռ��ļ�
	 * @return   	void
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
	 */
	void ScanLogFilePath(const char* FileNamePrefix,unsigned int MaxKeepFilesCount);
	/**
	 * Method:    	CompressLogFile
	 * FullName:  	KFPC_Log::CompressLogFile
	 * @brief 		ѹ���ռ��ļ����������ռǳ����趨��Сʱ�����Զ������µ��ռ��ļ��������ɵ��ռ��ļ�ѹ��
	 * @return   	void
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
	 */
	void CompressLogFile(const char* pFileName);
};
/*--------------------------------------------------------------------------------------------------------------------------------
 |  Global variables
 *------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Macros
 *------------------------------------------------------------------------------------------------------------------------------*/
//#define ALL_LOG_LEVEL	(LL_DEBUGMEM|LL_DEBUG|LL_WARNING|LL_ERROR|LL_FATAL)	/**< �����ռǼ��� */

/**
 * Method:    	KFPC_LOG_LEVEL_TO_STRING
 * FullName:  	KFPC_LOG_LEVEL_TO_STRING
 * @brief 		���ռǼ�������ַ���
 * @param[in]	KFPC_LOG_LEVEL LogLevel	�ռǼ���
 * @return   	const char*	
 * @pre 		��
 * @par 		ʾ��
 * @see 		����
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

