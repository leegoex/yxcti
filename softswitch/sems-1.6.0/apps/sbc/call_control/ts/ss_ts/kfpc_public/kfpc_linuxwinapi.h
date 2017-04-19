#ifndef kfpc_linuxwinapi_h__
#define kfpc_linuxwinapi_h__


/********************************************************************
 * @data:		2012/09/26
 * @details:	26:9:2012   15:53
 * @file: 		D:\MyProgram\ͨ�ſ�\kfpc_com\kfpc_linuxwinapi.h 
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

	//����
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
	// ����
	#define  Sleep(x) usleep(x*1000)
	// ��
	#define  SleepEx(x) usleep(x*1000*1000)
	#define EPEVENTS_COUNT 64
	#define	_msize	malloc_usable_size
#endif



/*--------------------------------------------------------------------------------------------------------------------------------
 |  Defines
 *------------------------------------------------------------------------------------------------------------------------------*/
const char	KFPC_LOG_DIR[] =	"KFPC_LOG_DIR";	/**< �ռ��ļ����·��ϵͳ�������� */
const char	KFPC_CFG_DIR[] =	"KFPC_CFG_DIR";	/**< �����ļ��������� */
const int	MAX_FILE_NAME_LEN =	256;			/**< �ļ�·����󳤶� */


extern unsigned int	g_NewCount;
extern unsigned int g_SocketHandleCount;


unsigned int GetNewCount(int val);


typedef void* (*Thread_Proc)(void *);
 

//ϵͳ�������ʹ��

/**
 * Method:    	InitSection
 * FullName:  	InitSection
 * @brief 		�����ٽ����
 * @param[in,out]	THREAD_MUTEX * Thread_Mutex �¼�������
 * @return   	int
 * @pre			��
 * @par			ʾ��
 * @see			����
 */

int InitSection( THREAD_MUTEX *Thread_Mutex,void* attr );
/**
 * Method:    	DestroySection
 * FullName:  	DestroySection
 * @brief 		�����ٽ����
 * @param[in]	THREAD_MUTEX * Thread_Mutex �¼�������
 * @return   	int
 * @pre 		��
 * @par 		ʾ��
 * @see 		����
 */
int DestroySection( THREAD_MUTEX *Thread_Mutex,void* attr );
/**
 * Method:    	LockSection
 * FullName:  	LockSection
 * @brief 		�����ٽ����
 * @param[in]	THREAD_MUTEX * Thread_Mutex �¼�������
 * @return   	int
 * @pre 		��
 * @par 		ʾ��
 * @see 		����
 */
int LockSection( THREAD_MUTEX *Thread_Mutex );
/**
 * Method:    	UnlockSection
 * FullName:  	UnlockSection
 * @brief 		�����ٽ����
 * @param[in]	THREAD_MUTEX * Thread_Mutex �ٽ����
 * @return   	int
 * @pre 		��
 * @par 		ʾ��
 * @see 		����
 */
int UnlockSection( THREAD_MUTEX *Thread_Mutex );

bool TryLockSection( THREAD_MUTEX *Thread_Mutex );
/**
 * Method:    	InitEvent
 * FullName:  	InitEvent
 * @brief 		��ʼϵͳ�¼�
 * @param[in,out] EVENT_HANDLE * cond �¼�������
 * @return   	int
 * @pre 		��
 * @par 		ʾ��
 * @see 		����
 */
int InitEvent(EVENT_HANDLE* cond,bool bManualReset = false);
/**
 * Method:    	DestroyEvent
 * FullName:  	DestroyEvent
 * @brief 		�����¼�����
 * @param[in,out] EVENT_HANDLE * cond �¼�������
 * @return   	int
 * @pre 		��
 * @par 		ʾ��
 * @see 		����
 */
int DestroyEvent(EVENT_HANDLE* cond);
/**
 * Method:    	WaitEvent
 * FullName:  	WaitEvent
 * @brief 		�ȴ��¼�
 * @param[in] EVENT_HANDLE * cond	�¼�������
 * @param[in] THREAD_MUTEX * mutex �ٽ����
 * @param[in] long stimeout ��ʱ�� ��λ��
 * @return   	int
 * @pre 		��
 * @par 		ʾ��
 * @see 		����
 */
int WaitEvent(EVENT_HANDLE* cond,THREAD_MUTEX* mutex,long stimeout);
/**
 * Method:    	WaitEventEx
 * FullName:  	WaitEventEx
 * @brief 		�ȴ��¼�����
 * @param[in] EVENT_HANDLE * cond	�¼�������
 * @param[in] THREAD_MUTEX * mutex	�ٽ����
 * @param[in] unsigned int stimeout ��ʱ�� ��λ����
 * @return   	int
 * @pre 		��
 * @par 		ʾ��
 * @see 		����
 */
int WaitEventEx(EVENT_HANDLE* cond,THREAD_MUTEX* mutex, int stimeout/*����*/);
/**
 * Method:    	SignalEvent
 * FullName:  	SignalEvent
 * @brief 		�����¼�����
 * @param[in] EVENT_HANDLE * cond �¼�������
 * @param[in] THREAD_MUTEX * mutex �ٽ����
 * @return   	int
 * @pre 		��
 * @par 		ʾ��
 * @see 		����
 */
int SignalEvent(EVENT_HANDLE* cond,THREAD_MUTEX* mutex,bool bManualReset = false);

//ɱ���߳�
int KillThread(THREADID pThreadID,HANDLE_t ThreadHandle);
//�����߳�
int Create_Thread(Thread_Proc proc,void* pParam,THREADID* pThreadID,HANDLE_t* ThreadHandle);
//�ȴ��߳��˳�
int ThreadJoin(THREADID pThreadID,HANDLE_t ThreadHandle,void* retval);

/**< �����ź��� */
int CreateSem(unsigned int SemCount,SemHandl_t* Handle);
/**< �����ź��� */
int SemWait(SemHandl_t* Handle, unsigned int val);
int TrySemWait(SemHandl_t* Handle );
int Sem_TimedWaitt(SemHandl_t* Handle,unsigned int TimeOut );

/**< �����ź��� */
int SemPost(SemHandl_t* Handle, unsigned int val );
/**< �ر��ź��� */
int	CloseSem(SemHandl_t Handle );

/**
 *	���������
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


    THREAD_MUTEX    m_Mutex;	/**< ������� */
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
 *	�¼�������
 */
class KFPC_Event{
private:
	bool	m_bManualReset;
public:
    KFPC_Event(bool bManualReset = false);
    virtual ~KFPC_Event(void);
	inline  int Wait(long stimeout)//��
	{

#ifdef WIN32

		if(m_bManualReset)
		{
			BOOL ret = ResetEvent(m_Event);
		}
#endif

		return WaitEvent(&m_Event,&m_Mutex,stimeout);
	}

	inline int WaitEx(unsigned int mtimeout)//����
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


    THREAD_MUTEX    m_Mutex;	/**< ������� */

    EVENT_HANDLE    m_Event;	/**< �¼����� */
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
/* �ļ�������غ���                                                     */
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


int GetLastErr(void); /**< �������Ĵ��� */
#define smart_new(T,P) {P = new T;  GetNewCount(1); DEBUGMEM_LOG(0,"smart_new NewCount:%d Pointer:0x%x.",g_NewCount,P);	}

#define smart_delete(V) {	delete V; GetNewCount(-1);  DEBUGMEM_LOG(0,"smart_delete NewCount:%d ",g_NewCount); }


void Buf2HexStr(unsigned char* byte,int len,char* OutStr,int OutStrLen);

/* *************************************** */

/* Bind this thread to a specific core */

int bindthread2core(THREADID thread_id, unsigned int core_id);

void DiskFree(const char* path,unsigned int* Total,unsigned int* AvailableDisk);
#endif // kfpc_linuxwinapi_h__

