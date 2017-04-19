#include "kfpc_logex.h"
#include "kfpc_threadpool.h"
#include "kfpc_log.h"
#include "kfpc_error.h"




KFPC_ThreadPool::KFPC_ThreadPool(void)
{
	m_ThreadCount = 0;		/**< 线程池数量 */
	m_pThreadID = NULL;		/**< 线程ID列表 */
	m_pThreadHandle = NULL;	/**< 线程柄列表 */

}


KFPC_ThreadPool::~KFPC_ThreadPool(void)
{
	Close();
}

void* KFPC_ThreadPool::ThreadProc( void* param )
{
	KFPC_ThreadParamInfo*	pThreadParamInfo = (KFPC_ThreadParamInfo*)param;

	KFPC_ThreadPool* pThreadPool = pThreadParamInfo->ThreadPoolThis;
	return pThreadPool->DoThreadProc(pThreadParamInfo);
}

int KFPC_ThreadPool::Open(unsigned int CallFunNameLen,const char* pCallFun, unsigned int ThreadCount /*= 1*/ ,unsigned int  StartCoreID)
{
	INFO_LOG(0,"ThreadCount:%d call by   %.*s,StartCoreID:%u",ThreadCount,CallFunNameLen,pCallFun,StartCoreID);

	if(m_ThreadCount == 0)
	{
		m_ThreadCount = ThreadCount;
		smart_new(THREADID[m_ThreadCount],m_pThreadID);
		smart_new( HANDLE_t[m_ThreadCount],m_pThreadHandle);		
		smart_new(KFPC_ThreadTaskQueue[m_ThreadCount],m_ThreadTaskQueueGroups);
		smart_new(KFPC_ThreadParamInfo[m_ThreadCount],m_ThreadParamInfo);


		for(unsigned int i=0;i<ThreadCount;i++)
		{
			m_ThreadParamInfo[i].ThreadPoolThis = this;
			m_ThreadParamInfo[i].ThreadInx = StartCoreID + i;

			Create_Thread(ThreadProc,&m_ThreadParamInfo[i],&m_pThreadID[i],&m_pThreadHandle[i]);
			INFO_LOG(0,"ThreadID:%u,",m_pThreadID[i]);
		}

		return 0;
	}
	else
	{
		return KFPC_RESULT_THREADPOOL_ALREADY_OPEN;
	}
}

int KFPC_ThreadPool::Close(const char* ThreadPoolName)
{
	INFO_LOG(0,"%s",ThreadPoolName);

	if(m_ThreadCount > 0)
	{
		PutExitTask();

		return WaitThreadExit();
	}
	else
	{
		return KFPC_RESULT_THREADPOOL_NOT_OPEN;
	}
}

void* KFPC_ThreadPool::DoThreadProc(KFPC_ThreadParamInfo* pThreadParamInfo)
{
	
	KFPC_ThreadTask*	pThreadTask = NULL;

	INFO_LOG(0,"thread start.");
	while(1)
	{
		pThreadTask = m_ThreadTaskQueue.GetTask(-1);

		if(pThreadTask != NULL)
		{
			if(pThreadTask->GetThreadTaskType() == TTT_ExitThread)
			{
				smart_delete(pThreadTask);
				DEBUG_LOG(0,"break exit");
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

	INFO_LOG(0,"thread exit.");
	return NULL;
}

unsigned int KFPC_ThreadPool::PutTask( KFPC_ThreadTask* pTask )
{
	return m_ThreadTaskQueue.PutTask(pTask);
}

KFPC_ThreadTask* KFPC_ThreadPool::GetTask( int Timeout )
{
	return m_ThreadTaskQueue.GetTask(Timeout);
}

void KFPC_ThreadPool::PutExitTask()
{
	for(unsigned int i=0;i<m_ThreadCount;i++)
	{
		KFPC_ExitThreadTask*	pExitThreadTask = NULL;

		smart_new(KFPC_ExitThreadTask,pExitThreadTask) ;
		m_ThreadTaskQueue.PutTask(pExitThreadTask);

		//smart_new(KFPC_ExitThreadTask,pExitThreadTask) ;
		//m_ThreadTaskQueueGroups[i].PutTask(pExitThreadTask);
	}
}

int KFPC_ThreadPool::WaitThreadExit()
{
	if(m_ThreadCount > 0)
	{

		void* ExitCode = NULL;
		for(unsigned int i=0;i<m_ThreadCount;i++)
		{
			ThreadJoin(m_pThreadID[i],m_pThreadHandle[i],&ExitCode);
		}

		smart_delete( []m_pThreadID);
		smart_delete( []m_pThreadHandle);
		smart_delete( []m_ThreadTaskQueueGroups);
		smart_delete( []m_ThreadParamInfo);
		
		m_pThreadID = NULL;
		m_pThreadHandle = NULL;
		m_ThreadCount = 0;
		m_ThreadTaskQueueGroups = NULL;

		m_ThreadTaskQueue.Clear();

	}

	return 0;
}

unsigned int KFPC_ThreadPool::PutTaskThreadInx( KFPC_ThreadTask* pTask,unsigned int ThreadInx )
{
	if(ThreadInx<m_ThreadCount)
	{
		m_ThreadTaskQueue.Signal();
		return m_ThreadTaskQueueGroups[ThreadInx].PutTask(pTask);
	}
	else
	{
		return m_ThreadTaskQueue.PutTask(pTask);
	}
}

KFPC_ThreadTask* KFPC_ThreadPool::GetTaskThreadInx( int Timeout,unsigned int ThreadInx )
{
	if(ThreadInx<m_ThreadCount)
	{
		return m_ThreadTaskQueueGroups[ThreadInx].GetTask(Timeout);
	}
	else
	{
		return m_ThreadTaskQueue.GetTask(Timeout);
	}
}

unsigned long KFPC_ThreadPool::GetTaskSize()
{
	return m_ThreadTaskQueue.QueueSize();
}
