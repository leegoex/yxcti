#ifndef kfpc_linuxwinapi_h__
#define kfpc_linuxwinapi_h__


/********************************************************************
 * @data:		2012/09/26
 * @details:	26:9:2012   15:53
 * @file: 		D:\MyProgram\通信库\kfpc_com\kfpc_linuxwinapi.h 
 * @author:		KFPC
 * @brief:		
*********************************************************************/

#include <ctype.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>


#ifdef WIN32
	//#pragma comment(lib, "libcmt.lib")
	//#define WIN32_LEAN_AND_MEAN
	//#pragma comment(lib, "ws2_32.lib")
	//#include <winsock2.h>	
	//#include <ws2tcpip.h>
	
	#include <windows.h>
	#include <process.h>
	#include <shellapi.h>
	#include <signal.h>
	#include <windowsx.h>
	#include <io.h>
	#include <direct.h>
	#include <tchar.h>
	
	#define snprintf _snprintf
	#define vsnprintf _vsnprintf
    #define THREAD_MUTEX    CRITICAL_SECTION
    #define EVENT_HANDLE    HANDLE
    #define HANDLE_t        HANDLE
	#define SemHandl_t		HANDLE

	//typedef int             socklen_t ;
	typedef unsigned long   THREADID;
	//typedef SOCKET          SOCKET_t; 

	//秒数
	#define SleepEx(x) Sleep(x * 1000)

	#define pthread_mutexattr_t	int

#else
	#include <semaphore.h>
	#include <sys/epoll.h>
	#include <dirent.h>
	#include <netdb.h>
	//#include <paths.h>
	#include <pthread.h>
	#include <signal.h>
	#include <unistd.h>
	//#include <arpa/inet.h>
	//#include <netinet/in.h>
	//#include <netinet/tcp.h>
	#include <sys/resource.h>
	//#include <sys/socket.h>
	#include <sys/time.h>
	#include <sys/types.h>
	#include <sys/wait.h>
	#include <pthread.h>
    #include <sys/types.h>
    #include <sys/time.h>
    #include <unistd.h>
	#include <signal.h>
    #define  Sleep(x)       usleep(x*1000)
    #define THREAD_MUTEX    pthread_mutex_t    
    #define EVENT_HANDLE    pthread_cond_t
    #define HANDLE_t        void *
	//#define SOCKET int
	//#define SOCKET_ERROR -1
	//#define INVALID_SOCKET -1
	typedef pthread_t       THREADID;
	//typedef int             SOCKET_t;
	#define  SemHandl_t		sem_t
	// 毫秒
	#define  Sleep(x) usleep(x*1000)
	// 秒
	#define  SleepEx(x) usleep(x*1000*1000)
	#define EPEVENTS_COUNT 64
	#define	_msize	malloc_usable_size
#endif



/*--------------------------------------------------------------------------------------------------------------------------------
 |  Defines
 *------------------------------------------------------------------------------------------------------------------------------*/
const char	KFPC_LOG_DIR[] =	"KFPC_LOG_DIR";	/**< 日记文件存放路径系统环境变量 */
const char	KFPC_CFG_DIR[] =	"KFPC_CFG_DIR";	/**< 配置文件环境变量 */
const int	MAX_FILE_NAME_LEN =	256;			/**< 文件路径最大长度 */


extern unsigned int	g_NewCount;
extern unsigned int g_SocketHandleCount;


unsigned int GetNewCount(int val);


typedef void* (*Thread_Proc)(void *);
 

//系统互斥变量使用

/**
 * Method:    	InitSection
 * FullName:  	InitSection
 * @brief 		创建临界变量
 * @param[in,out]	THREAD_MUTEX * Thread_Mutex 事件对象句柄
 * @return   	int
 * @pre			无
 * @par			示例
 * @see			引用
 */

int InitSection( THREAD_MUTEX *Thread_Mutex,void* attr );
/**
 * Method:    	DestroySection
 * FullName:  	DestroySection
 * @brief 		消毁临界变量
 * @param[in]	THREAD_MUTEX * Thread_Mutex 事件对象句柄
 * @return   	int
 * @pre 		无
 * @par 		示例
 * @see 		引用
 */
int DestroySection( THREAD_MUTEX *Thread_Mutex,void* attr );
/**
 * Method:    	LockSection
 * FullName:  	LockSection
 * @brief 		锁定临界变量
 * @param[in]	THREAD_MUTEX * Thread_Mutex 事件对象句柄
 * @return   	int
 * @pre 		无
 * @par 		示例
 * @see 		引用
 */
int LockSection( THREAD_MUTEX *Thread_Mutex );
/**
 * Method:    	UnlockSection
 * FullName:  	UnlockSection
 * @brief 		解锁临界变量
 * @param[in]	THREAD_MUTEX * Thread_Mutex 临界变量
 * @return   	int
 * @pre 		无
 * @par 		示例
 * @see 		引用
 */
int UnlockSection( THREAD_MUTEX *Thread_Mutex );

bool TryLockSection( THREAD_MUTEX *Thread_Mutex );
/**
 * Method:    	InitEvent
 * FullName:  	InitEvent
 * @brief 		初始系统事件
 * @param[in,out] EVENT_HANDLE * cond 事件对象句柄
 * @return   	int
 * @pre 		无
 * @par 		示例
 * @see 		引用
 */
int InitEvent(EVENT_HANDLE* cond,bool bManualReset = false);
/**
 * Method:    	DestroyEvent
 * FullName:  	DestroyEvent
 * @brief 		消毁事件对象
 * @param[in,out] EVENT_HANDLE * cond 事件对象句柄
 * @return   	int
 * @pre 		无
 * @par 		示例
 * @see 		引用
 */
int DestroyEvent(EVENT_HANDLE* cond);
/**
 * Method:    	WaitEvent
 * FullName:  	WaitEvent
 * @brief 		等待事件
 * @param[in] EVENT_HANDLE * cond	事件对象句柄
 * @param[in] THREAD_MUTEX * mutex 临界变量
 * @param[in] long stimeout 超时间 单位秒
 * @return   	int
 * @pre 		无
 * @par 		示例
 * @see 		引用
 */
int WaitEvent(EVENT_HANDLE* cond,THREAD_MUTEX* mutex,long stimeout);
/**
 * Method:    	WaitEventEx
 * FullName:  	WaitEventEx
 * @brief 		等待事件对象
 * @param[in] EVENT_HANDLE * cond	事件对象句柄
 * @param[in] THREAD_MUTEX * mutex	临界变量
 * @param[in] unsigned int stimeout 超时间 单位毫秒
 * @return   	int
 * @pre 		无
 * @par 		示例
 * @see 		引用
 */
int WaitEventEx(EVENT_HANDLE* cond,THREAD_MUTEX* mutex, int stimeout/*毫秒*/);
/**
 * Method:    	SignalEvent
 * FullName:  	SignalEvent
 * @brief 		激活事件对象
 * @param[in] EVENT_HANDLE * cond 事件对象句柄
 * @param[in] THREAD_MUTEX * mutex 临界变量
 * @return   	int
 * @pre 		无
 * @par 		示例
 * @see 		引用
 */
int SignalEvent(EVENT_HANDLE* cond,THREAD_MUTEX* mutex,bool bManualReset = false);

//杀死线程
int KillThread(THREADID pThreadID,HANDLE_t ThreadHandle);
//创建线程
int Create_Thread(Thread_Proc proc,void* pParam,THREADID* pThreadID,HANDLE_t* ThreadHandle);
//等待线程退出
int ThreadJoin(THREADID pThreadID,HANDLE_t ThreadHandle,void* retval);

/**< 创建信号量 */
int CreateSem(unsigned int SemCount,SemHandl_t* Handle);
/**< 消费信号量 */
int SemWait(SemHandl_t* Handle, unsigned int val);
int TrySemWait(SemHandl_t* Handle );
int Sem_TimedWaitt(SemHandl_t* Handle,unsigned int TimeOut );

/**< 回收信号量 */
int SemPost(SemHandl_t* Handle, unsigned int val );
/**< 关闭信号量 */
int	CloseSem(SemHandl_t Handle );

/**
 *	互斥对象类
 */
class KFPC_Mutex{
public:
    KFPC_Mutex(void);
    virtual ~KFPC_Mutex(void);
	inline void lock(){LockSection(&m_Mutex);}
    inline void unlock(){UnlockSection(&m_Mutex);}
	inline bool trylock(){ return TryLockSection(&m_Mutex);}
private:

	pthread_mutexattr_t	m_Attr;


    THREAD_MUTEX    m_Mutex;	/**< 互斥变量 */
};

class KFPC_AutoMutex
{
private:
	KFPC_Mutex*	m_Mutex;
public:
	KFPC_AutoMutex(KFPC_Mutex* pMutex);
	~KFPC_AutoMutex();
};

/**
 *	事件对象类
 */
class KFPC_Event{
private:
	bool	m_bManualReset;
public:
    KFPC_Event(bool bManualReset = false);
    virtual ~KFPC_Event(void);
	inline  int Wait(long stimeout)//秒
	{

#ifdef WIN32

		if(m_bManualReset)
		{
			BOOL ret = ResetEvent(m_Event);
		}
#endif

		return WaitEvent(&m_Event,&m_Mutex,stimeout);
	}

	inline int WaitEx(unsigned int mtimeout)//毫秒
	{

#ifdef WIN32

		if(m_bManualReset)
		{
			ResetEvent(m_Event);
		}
#endif


		return WaitEventEx(&m_Event,&m_Mutex,mtimeout);
	}

    inline int Signal(void)
	{
		return SignalEvent(&m_Event,&m_Mutex,m_bManualReset);
	}

private:


	pthread_mutexattr_t	m_Attr;


    THREAD_MUTEX    m_Mutex;	/**< 互斥变量 */

    EVENT_HANDLE    m_Event;	/**< 事件变量 */
};

class KFPC_Semaphore
{
private:
	SemHandl_t	m_SemHandle;
public:
	KFPC_Semaphore(unsigned int SemCount);
	virtual ~KFPC_Semaphore(void);
	inline int SemWait(unsigned int val = 1){
		return ::SemWait(&m_SemHandle,val);
	}
	inline int SemPost(unsigned int val = 1){
		return ::SemPost(&m_SemHandle,val);
	}
	inline int TrySemWait(){
		return ::TrySemWait(&m_SemHandle);
	}
	inline int SemTimedWaitt(unsigned int TimeOut)
	{
		return ::Sem_TimedWaitt(&m_SemHandle,TimeOut);
	}
};

class KFPC_AutoPostSemaphore
{
private:
	KFPC_Semaphore*	m_Semaphore;
	unsigned int	m_Count;
public:
	KFPC_AutoPostSemaphore(KFPC_Semaphore*	pSemaphore,unsigned int Count = 1):m_Semaphore(pSemaphore),m_Count(Count){}
	~KFPC_AutoPostSemaphore(){m_Semaphore->SemPost(m_Count);}
};

class KFPC_AutoSemaphore
{
private:
	KFPC_Semaphore*	m_Semaphore;
	unsigned int	m_Count;
public:
	KFPC_AutoSemaphore(KFPC_Semaphore*	pSemaphore,unsigned int Count = 1);
	~KFPC_AutoSemaphore();
};

/************************************************************************/
/* 文件处理相关函数                                                     */
/************************************************************************/

bool DirectoryExist(const char *csDirectory);
bool FileExist(const char *csDirectory);
void MakeDirectory(const char *csDirectory);

void DelFile(const char * szFile);
bool CompressFile(const char* source,const char* destination);
void RenameFile(const char* source,const char* destination);
#ifdef WIN32
void CharToWchar(const char *chr,wchar_t *wchar,int size);
void WcharToChar(const wchar_t *wchar, char *chr, int length);
void UTF8ToWChar(const char *utf8chr, wchar_t *chr, int length);
void WCharToUTF8(const wchar_t *chr,char *utf8chr, int length);
#endif

#ifdef LINUX
char *strupr(char *str);
#endif
void	GetPathByFileName(const char* FileGlobalName,char* pPath,char* pFileName);


int GetLastErr(void); /**< 返回最后的错误 */
#define smart_new(T,P) {P = new T;  GetNewCount(1); DEBUGMEM_LOG(0,"smart_new NewCount:%d Pointer:0x%x.",g_NewCount,P);	}

#define smart_delete(V) {	delete V; GetNewCount(-1);  DEBUGMEM_LOG(0,"smart_delete NewCount:%d ",g_NewCount); }


void Buf2HexStr(unsigned char* byte,int len,char* OutStr,int OutStrLen);

/* *************************************** */

/* Bind this thread to a specific core */

int bindthread2core(THREADID thread_id, unsigned int core_id);

void DiskFree(const char* path,unsigned int* Total,unsigned int* AvailableDisk);
#endif // kfpc_linuxwinapi_h__

