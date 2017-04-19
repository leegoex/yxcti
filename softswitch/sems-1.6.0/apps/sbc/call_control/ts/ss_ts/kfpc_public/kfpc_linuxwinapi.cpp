#include "kfpc_log.h"
#include "kfpc_linuxwinapi.h"
#include "zlib.h"
#include "kfpc_logex.h"



#ifdef WIN32
#include <share.h>
#pragma warning (disable: 4996) 
#include <winsock2.h>	
#else
#include <sys/statfs.h> 
#endif
KFPC_Mutex	Mutex;
unsigned int g_NewCount = 0;


int InitSection( THREAD_MUTEX *Thread_Mutex,void* attr )
{
#ifdef LINUX
	if(attr != NULL)
	{
		pthread_mutexattr_init ((pthread_mutexattr_t*)attr);
		pthread_mutexattr_settype((pthread_mutexattr_t*)attr,PTHREAD_MUTEX_RECURSIVE);
	}
	
	return pthread_mutex_init( Thread_Mutex,(pthread_mutexattr_t*)attr );
#else
    	InitializeCriticalSection( Thread_Mutex );
	return 0;
#endif

}

int DestroySection( THREAD_MUTEX *Thread_Mutex ,void* attr)
{
#ifdef LINUX
	if(attr != NULL)
	{
		pthread_mutexattr_destroy ((pthread_mutexattr_t*)attr);
	}

	return pthread_mutex_destroy( Thread_Mutex );
#else
    	DeleteCriticalSection( Thread_Mutex );
	return 0;
#endif
}

int LockSection( THREAD_MUTEX *Thread_Mutex )
{
#ifdef LINUX
	return pthread_mutex_lock( Thread_Mutex );
#else
    	EnterCriticalSection( Thread_Mutex );
	return 0;
#endif
}

bool TryLockSection( THREAD_MUTEX *Thread_Mutex )
{
#ifdef LINUX
	return (pthread_mutex_trylock( Thread_Mutex ) == 0)?true:false;
#else
	return TryEnterCriticalSection( Thread_Mutex );
	
#endif
}


int UnlockSection( THREAD_MUTEX *Thread_Mutex )
{
#ifdef LINUX
	return pthread_mutex_unlock( Thread_Mutex );
#else 
    	LeaveCriticalSection( Thread_Mutex );
	return 0;
#endif
}

int InitEvent(EVENT_HANDLE* cond,bool bManualReset)
{
    #ifdef LINUX
        pthread_cond_init(cond,NULL);
    #else
        *cond = CreateEvent(NULL,bManualReset,false,NULL);
    #endif
        return 0;
}

int DestroyEvent(EVENT_HANDLE* cond)
{
    #ifdef LINUX
        return pthread_cond_destroy(cond);
    #else
        return CloseHandle(*cond);
    #endif
     
}

int WaitEvent(EVENT_HANDLE* cond,THREAD_MUTEX* mutex,long stimeout)
{
    int ret  =  0;

    #ifdef  LINUX
        
        LockSection(mutex);

        if(stimeout == -1)
        {            
            ret = pthread_cond_wait(cond,mutex);
        }
        else
        {
            struct timeval now;
            struct timespec timeout;

            gettimeofday(&now,NULL);
            
            timeout.tv_sec =    now.tv_sec + stimeout;
            timeout.tv_nsec =   now.tv_usec *1000;
            
            ret = pthread_cond_timedwait(cond,mutex,&timeout);
        }
        
        UnlockSection(mutex);
    #else

    //ResetEvent(*cond);
    if(stimeout == -1)
    {
        ret = WaitForSingleObject(*cond,INFINITE);        
    }
    else
    {
        ret = WaitForSingleObject(*cond,stimeout*1000);
    }   
    #endif

    return ret;
}

int WaitEventEx(EVENT_HANDLE* cond,THREAD_MUTEX* mutex,int stimeout/*毫秒*/)
{
    int ret  =  0;

    #ifdef  LINUX
        
        LockSection(mutex);

        if(stimeout == -1)
        {            
            ret = pthread_cond_wait(cond,mutex);
        }
        else
        {
            struct timeval now;
            struct timespec timeout;

            gettimeofday(&now,NULL);
            
			timeout.tv_sec =    now.tv_sec;
			unsigned int nsec = (now.tv_usec *1000)+(stimeout*1000000);
			timeout.tv_nsec =   nsec%1000000000;
			timeout.tv_sec += nsec/1000000000;

            ret = pthread_cond_timedwait(cond,mutex,&timeout);
        }
        
        UnlockSection(mutex);
    #else

    //ResetEvent(*cond);
    if(stimeout == -1)
    {
        ret = WaitForSingleObject(*cond,INFINITE);        
    }
    else
    {
        ret = WaitForSingleObject(*cond,stimeout);
    }   
    #endif

    return ret;
}


int SignalEvent(EVENT_HANDLE* cond,THREAD_MUTEX* mutex,bool bManualReset)
{
    int    ret;

    #ifdef LINUX
              
        LockSection(mutex);
		if(bManualReset)
		{
			ret = pthread_cond_broadcast(cond);
		}
		else
		{
			ret =  pthread_cond_signal(cond);
		}
        UnlockSection(mutex);
                
    #else
       
        ret = SetEvent(*cond);

    #endif

    return ret;
}

//杀死线程
//杀死线程
int KillThread(THREADID pThreadID,HANDLE_t ThreadHandle)
{
    #ifdef LINUX
        int itype = 0;
        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,&itype);
        return pthread_cancel(pThreadID);
    #else
        DWORD ExitCode = 0;
        GetExitCodeThread(ThreadHandle,&ExitCode);
        return TerminateThread(ThreadHandle,ExitCode);
    #endif
}

int Create_Thread(Thread_Proc proc,void* pParam,THREADID *pThreadID,HANDLE_t *ThreadHandle)
{
    int ret = 0;

    #ifdef LINUX

        ret = pthread_create(pThreadID,NULL,proc,pParam);

        if ( ret == 0)
        {
			//pthread_detach((*pThreadID));
            ret = 0;
            ThreadHandle = 0;
        }
    #else
        *ThreadHandle = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)proc,(void *)pParam,0,pThreadID);

        if(*ThreadHandle == NULL)
        {
            ret = -1;
        }
        else
        {
            ret = 0;
        }

    #endif

    return ret;
}

int ThreadJoin( THREADID pThreadID,HANDLE_t ThreadHandle,void* retval )
{
	int ret = 0;

#ifdef LINUX
	ret = pthread_join(pThreadID,&retval);
#else
	ret =  WaitForSingleObject(ThreadHandle,INFINITE);   
	GetExitCodeThread(ThreadHandle,(PDWORD)&retval);
#endif
	return ret;
}
//********************事件类定义***************************
KFPC_Event::KFPC_Event(bool bManualReset):m_bManualReset(bManualReset)
{
	memset(&m_Attr,0,sizeof(m_Attr));

    InitSection(&m_Mutex,&m_Attr);
    InitEvent(&m_Event,bManualReset);
}

KFPC_Event::~KFPC_Event(void)
{
    DestroySection(&m_Mutex,&m_Attr);
    DestroyEvent(&m_Event);
}


bool DirectoryExist(const char *csDirectory)
{
#ifdef WIN32
#if _UNICODE
	TCHAR  lpszcsDirectory[MAX_FILE_NAME_LEN*sizeof(wchar_t)];  
	CharToWchar(csDirectory,lpszcsDirectory,MAX_FILE_NAME_LEN*sizeof(wchar_t));
	int iCode = GetFileAttributes(lpszcsDirectory);
#else
	int iCode = GetFileAttributes(csDirectory);
#endif
	int iResult = iCode & FILE_ATTRIBUTE_DIRECTORY;
	return (iCode != -1) && (iResult != 0);
#else
	struct stat stat_dir;
	if (stat(csDirectory, &stat_dir) == 0)
		return stat_dir.st_mode;
	else
		return false;
#endif
}

bool FileExist(const char *csDirectory)
{
	return (access(csDirectory,0) == 0); 
}

void MakeDirectory(const char *csDirectory)
{
	if (csDirectory == NULL)
		return;
	char csDir[MAX_FILE_NAME_LEN];
	char tmpDir[MAX_FILE_NAME_LEN];
	sprintf((char*)csDir,"%s",csDirectory);
	size_t iLen = strlen(csDir);
	for(size_t i=0; i < iLen; i++)   
	{   
		if((csDir[i] == '/')||(csDir[i] == '\\'))
		{   			
			strcpy(tmpDir,csDir);
			tmpDir[i] = '\0';  
			if(!DirectoryExist(tmpDir))   
			{
#ifdef WIN32
				if(_mkdir(tmpDir) == -1)
				{
					printf("mkdir fail %s\n",tmpDir);
					continue;
				}
#else
				if(mkdir(tmpDir,0755) == -1)   
				{   
					printf("mkdir fail:%s,csDirectory:%s\n",tmpDir,csDirectory);
					continue;
				}
#endif
			}
			csDir[i] = '/';   
		}   
	} 

#ifdef WIN32
	if(_mkdir(csDir) == -1)
	{
		printf("mkdir fail:%s",csDir);
		return;
	}
#else
	if(mkdir(csDir,0755) == -1)   
	{   
		printf("mkdir fail:%s\n",csDir);
		return;
	}
#endif

}

void DelFile(const char * szFile)
{
#ifdef WIN32
#if _UNICODE 
	TCHAR  lpszFile[MAX_FILE_NAME_LEN*sizeof(wchar_t)];
	CharToWchar(szFile,lpszFile,MAX_FILE_NAME_LEN*sizeof(wchar_t));
	DeleteFile(lpszFile);
#else
	DeleteFile(szFile);
#endif
#else
	remove(szFile);
#endif
}

int GetLastErr( void )
{
#ifdef LINUX
	return errno;
#else
	return WSAGetLastError ();
#endif
}

bool CompressFile( const char* source,const char* destination )
{

	FILE	*pfSource			= NULL;
	gzFile	pfDestination		= NULL;
	const unsigned int BufSize	= 4096;
	char ucBuffer[BufSize]		= "";
	char* csLineString			= NULL;

	try
	{
#ifdef	WIN32
		int  fh = 0;
		errno_t err = _sopen_s( &fh, source, _O_RDONLY, _SH_DENYRW, _S_IREAD | _S_IWRITE );
		if(err != 0)
		{
			return false;
		}
		else
		{
			_close( fh );
		}

		pfSource = fopen(source,"rt");
#else

		pfSource = fopen(source,"rtx");
#endif


		if (pfSource == NULL)
		{
			WARNING_LOG(0,"fopen(%s) fail.",source);
			return false;
		}

		pfDestination = gzopen(destination,"wb");
		if (pfDestination != NULL)
		{
			if (pfSource != NULL)
			{
				while (!feof(pfSource))
				{
					csLineString = fgets((char*)ucBuffer,BufSize,pfSource);
					if (csLineString != NULL)
					{
						gzputs(pfDestination,csLineString);
					}
				}
				fclose(pfSource);
			}
			gzclose(pfDestination);
		}
	}
	catch (...)
	{

		if (pfSource != NULL) fclose(pfSource);
		if (pfDestination != NULL) gzclose(pfDestination);

		WARNING_LOG(0,"source:%s,destination:%s fail.",source,destination);
		return false;
	}
	DEBUG_LOG(0,"source:%s,destination:%s success.",source,destination);
	return true;
}

#ifdef WIN32
void CharToWchar(const char *chr, wchar_t *wchar, int size)
{
	MultiByteToWideChar(CP_ACP,0,chr,strlen(chr)+1,wchar,size/sizeof(wchar[0]));
}

void WcharToChar(const wchar_t *wchar, char *chr, int length)
{  
	WideCharToMultiByte(CP_ACP,0,wchar,-1,chr, length, NULL, NULL); 
}  

void UTF8ToWChar(const char *utf8chr, wchar_t *wchar, int length)
{  
	MultiByteToWideChar(CP_UTF8,0,utf8chr,-1,wchar, length/sizeof(wchar[0])); 
}  


void WCharToUTF8( const wchar_t *wchar,char *utf8chr, int length )
{
	WideCharToMultiByte(CP_UTF8,0,wchar,-1,utf8chr, length, NULL, NULL); 
}

#endif


 int CreateSem( unsigned int SemCount,SemHandl_t* Handle)
{
	int Ret = 0;
#ifdef LINUX
	Ret = sem_init(Handle, 0, SemCount);
	if (Ret != 0) {
		/* error. errno has been set */
		WARNING_LOG(0,"Unable to initialize the semaphore");
		return -1;
	}
	DEBUG_LOG(0,"SemHandle:%u",*Handle);
#else

	HANDLE hSemaphore = CreateSemaphore( 
		NULL,           // default security attributes
		SemCount,  // initial count
		SemCount,  // maximum count
		NULL);          // unnamed semaphore
	DEBUG_LOG(0,"SemHandle:%u",*Handle);

	if (hSemaphore == NULL) 
	{		
		return -1;
	}
	else
	{
		*Handle  = hSemaphore;
		return 0;
	}

#endif

return Ret;
}

int SemWait(SemHandl_t* Handle, unsigned int val )
{
	int Ret = 0;

	for(unsigned int i=0;i<val;i++)
	{
#ifdef LINUX
		if((Ret = sem_wait(Handle)) != 0)
		{
			WARNING_LOG(0,"ret:%d",Ret);
			return -1;
		}
#else		
		if(Ret = WaitForSingleObject(*Handle,-1) != 0)
		{
			WARNING_LOG(0,"ret:%d",Ret);
			return -1;
		}
#endif
	}

return Ret;
}

int TrySemWait(SemHandl_t* Handle )
{
	int Ret = 0;


#ifdef LINUX
		if((Ret = sem_trywait(Handle)) != 0)
		{
			//WARNING_LOG(0,"ret:%d",Ret);
			return -1;
		}
#else		
		if(Ret = WaitForSingleObject(*Handle,0) != 0)
		{
			//WARNING_LOG(0,"ret:%d",Ret);
			return -1;
		}
#endif


	return Ret;
}

int Sem_TimedWaitt(SemHandl_t* Handle,unsigned int TimeOut )
{
	int Ret = 0;
#ifdef LINUX

	struct timeval now;
	struct timespec timeout;

	gettimeofday(&now,NULL);

	timeout.tv_sec =    now.tv_sec;
	unsigned int nsec = (now.tv_usec *1000)+(TimeOut*1000000);
	timeout.tv_nsec =   nsec%1000000000;
	timeout.tv_sec += nsec/1000000000;

	Ret=sem_timedwait(Handle,&timeout);  
#else
	if(Ret = WaitForSingleObject(*Handle,TimeOut) != 0)
	{
		//WARNING_LOG(0,"ret:%d",Ret);
		return -1;
	}
#endif

	return Ret;
}

int SemPost(SemHandl_t* Handle, unsigned int val )
{
	int Ret = 0;
	for(unsigned int i=0;i<val;i++)
	{
	#ifdef LINUX

		if((Ret = sem_post(Handle)) != 0)
		{
			WARNING_LOG(0,"ret:%d",Ret);
			break;
		}

	#else
		if (!ReleaseSemaphore( 
			*Handle,  // handle to semaphore
			1,            // increase count by one
			NULL) )       // not interested in previous count
		{
			WARNING_LOG(0,"ReleaseSemaphore error: %d\n", GetLastError());
			break;
		}
	
	#endif
	}

	return Ret;
}

int CloseSem( SemHandl_t* Handle )
{
	int Ret = 0;
#ifdef LINUX
	Ret = sem_destroy(Handle);
#else
	Ret = CloseHandle(*Handle);
#endif
	if(Ret != 0)
	{
		WARNING_LOG(0,"ret:%d",Ret);		
	}
	return Ret;
}


unsigned int GetNewCount(int val)
{
	
	Mutex.lock();
	g_NewCount +=val;
	Mutex.unlock();

	return g_NewCount;
}

void GetPathByFileName( const char* FileGlobalName,char* pPath,char* pFileName )
{
	int StrLen=strlen(FileGlobalName);
	pPath[0] = '\0';
	pFileName[0] = '\0';

	while(	StrLen>0)
	{
		StrLen --;
		if(	FileGlobalName[StrLen] == '\\' ||
			FileGlobalName[StrLen] == '/')
		{
			memmove(pPath,FileGlobalName,StrLen);
			pPath[StrLen] = '\0';

			strcpy(pFileName,&FileGlobalName[StrLen+1]);
			return;
		}
	}
}


#ifdef LINUX
char *strupr(char *str)
{
	char *ptr = str;

	while (*ptr != '\0') {
		if (islower(*ptr)) 
			*ptr = toupper(*ptr);
		ptr++;
	}

	return str;
}


#endif

KFPC_AutoMutex::KFPC_AutoMutex( KFPC_Mutex* pMutex ) :m_Mutex(pMutex)
{
	m_Mutex->lock();
}

KFPC_AutoMutex::~KFPC_AutoMutex()
{
	m_Mutex->unlock();
}

KFPC_Mutex::KFPC_Mutex( void )
{
	memset(&m_Attr,0,sizeof(m_Attr));

	InitSection(&m_Mutex,&m_Attr);
}

KFPC_Mutex::~KFPC_Mutex( void )
{
	DestroySection(&m_Mutex,&m_Attr);
}



KFPC_Semaphore::KFPC_Semaphore( unsigned int SemCount )
{
	CreateSem(SemCount,&m_SemHandle);
	
}
KFPC_Semaphore::~KFPC_Semaphore(  )
{
	CloseSem(&m_SemHandle);
}


KFPC_AutoSemaphore::KFPC_AutoSemaphore( KFPC_Semaphore* pSemaphore,unsigned int Count /*= 1*/ ) :m_Semaphore(pSemaphore),m_Count(Count)
{
	pSemaphore->SemWait(m_Count);
}

KFPC_AutoSemaphore::~KFPC_AutoSemaphore()
{
	m_Semaphore->SemPost(m_Count);
}

void Buf2HexStr( unsigned char* byte,int len,char* OutStr,int OutStrLen )
{
	int j=0;
	for(int i=0;i<len;i++)
	{
		j += snprintf(OutStr+j,OutStrLen-j,"%02x",byte[i]);
	}
}

void RenameFile( const char* source,const char* destination )
{
#ifdef WIN32

	
#ifdef _UNICODE 
	TCHAR wSource[1024]={0};
	TCHAR wDestination[1024]={0};

	CharToWchar(source,wSource,1024);
	CharToWchar(destination,wDestination,1024);

	MoveFile(wSource,wDestination);

#else
	MoveFile(source,destination );
#endif

#else
	rename(source,destination );
#endif
}

int bindthread2core(THREADID thread_id, unsigned int core_id)
{
#ifdef LINUX
	cpu_set_t cpuset;
	int s;

	CPU_ZERO(&cpuset);
	CPU_SET(core_id, &cpuset);
	if((s = pthread_setaffinity_np(thread_id, sizeof(cpu_set_t), &cpuset)) != 0) {
		fprintf(stderr, "Error while binding to core %u: errno=%i\n", core_id, s);
		return(-1);
	} else {
		return(0);
	}
#endif // LINUX
	return(0);
}

void DiskFree( const char* path,unsigned int* Total,unsigned int* AvailableDisk )
{
#ifdef LINUX
	struct statfs diskInfo; 

	statfs(path, &diskInfo); 
	unsigned long long blocksize = diskInfo.f_bsize; //每个block里包含的字节数 
	unsigned long long totalsize = blocksize * diskInfo.f_blocks; //总的字节数，f_blocks为block的数目 

	*Total = (unsigned int)(totalsize>>20);

	//printf("Total_size = %llu B = %llu KB = %lu MB = %llu GB\n", 
	//	totalsize, totalsize>>10, (*Total), totalsize>>30); 

	//unsigned long long freeDisk = diskInfo.f_bfree * blocksize; //剩余空间的大小 
	unsigned long long availableDisk = diskInfo.f_bavail * blocksize; //可用空间大小 

	*AvailableDisk = (unsigned int)(availableDisk>>20);

	//printf("Disk_free = %llu MB = %llu GB\nDisk_available = %lu MB = %llu GB\n", 
	//	freeDisk>>20, freeDisk>>30, (*AvailableDisk), availableDisk>>30); 
#else
	_ULARGE_INTEGER freespace,totalspace,userspace;
	if(GetDiskFreeSpaceEx(path,&userspace,&totalspace,&freespace))
	{
		*Total = (unsigned int)(totalspace.QuadPart >> 20);
		*AvailableDisk = (unsigned int)(userspace.QuadPart>>20);
	}

#endif // LINUX

}