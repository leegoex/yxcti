#include "kfpc_timerthreadpool.h"

#include "kfpc_log.h"
#include "kfpc_logex.h"
#include "kfpc_timeouttask.h"
#include "kfpc_msg.h"


KFPC_TimerThreadPool::KFPC_TimerThreadPool(void):
m_TimerArray(NULL),
m_ThreadIndex(0)
{
	DEBUG_LOG(0,"");
}


KFPC_TimerThreadPool::~KFPC_TimerThreadPool(void)
{
	Close();
}

void* KFPC_TimerThreadPool::DoThreadProc(KFPC_ThreadParamInfo* pThreadParamInfo)
{
	KFPC_ThreadTask*	pThreadTask = NULL;
	unsigned int		ThreadIndex = 0;
	//m_Mutex.lock();
	//ThreadIndex = m_ThreadIndex++;
	//m_Mutex.unlock();

	ThreadIndex = pThreadParamInfo->ThreadInx;

	while(true)
	{
		time_t				TaskTime = time(NULL);

		pThreadTask = m_ThreadTaskQueue.GetTask(0);

		if(pThreadTask != NULL)
		{

			if(pThreadTask->GetThreadTaskType() == TTT_ExitThread)
			{
				smart_delete(pThreadTask);
				break;
			}
			else
			{
				pThreadTask->DoSvc();
				smart_delete (pThreadTask);
			}	
		}


		while(ProcOutTime(ThreadIndex) == 0)
		{
			/**< 确保单次循环不要超过单个定时 */
			if((time(NULL) - TaskTime) >  KFPC_ONE_LOOP_TIME)
			{
				WARNING_LOG(0,"PROC time out over %d second",time(NULL) - TaskTime);
				break;
			}
		}

	}

	return NULL;
}

void KFPC_TimerThreadPool::Open( unsigned int ThreadCount)
{
	DEBUG_LOG(0,"ThreadCount:%d",ThreadCount);
	smart_new(KFPC_Timer[ThreadCount],m_TimerArray);

	KFPC_ThreadPool::Open(PREFIX_EXPRESSION_VALUE,ThreadCount);

}

unsigned int KFPC_TimerThreadPool::SetTimer( KFPC_ThreadPool *Arg1,KFPC_ThreadTask *Arg2,unsigned int Interval)
{
	unsigned int SN = m_IDGenerator.GetSN();			/**< 定时器ID生成器 */

	unsigned int TimerIndex = SN % m_ThreadCount;

	return m_TimerArray[TimerIndex].SetTimer(Arg1,Arg2,Interval,SN);
}

bool KFPC_TimerThreadPool::ClearTimer( unsigned int ID,void **Arg1 /*= NULL*/,void **Arg2/*=NULL*/ )
{
	if(ID == 0)	return false;

	bool Ret = false;
	unsigned int TimerIndex = ID % m_ThreadCount;

	Ret = m_TimerArray[TimerIndex].ClearTimer(ID,Arg1,Arg2);

	return Ret;
}

void KFPC_TimerThreadPool::Close()
{	
	if(m_TimerArray != NULL)
	{

		for(unsigned int i=0;i<m_ThreadCount;i++)
		{
			unsigned int ID = 0;
			void *Arg1 = NULL;
			void *Arg2 = NULL;

			while(m_TimerArray[i].PopTimer(&ID,&Arg1,&Arg2))
			{
				smart_delete(Arg2);
			}
		}

		KFPC_ThreadPool::Close();
		smart_delete([]m_TimerArray);
		m_TimerArray = NULL;

		m_ThreadIndex = 0;
	}
}

int KFPC_TimerThreadPool::ProcOutTime( unsigned int TimerIndex )
{
	void*	Arg1 = NULL;
	void*	Arg2 = NULL;
	unsigned int TimerID = 0;
	int		Ret	=	0;

	
	Ret = m_TimerArray[TimerIndex].OutTime(&TimerID,&Arg1,&Arg2,200);
	
	if(Ret == 0)
	{
		KFPC_ThreadPool*	pThreadPool = (KFPC_ThreadPool*)Arg1;
		KFPC_TimeoutTask*	pThreadTask	= (KFPC_TimeoutTask*)Arg2;

		pThreadTask->TimerID = TimerID;
		DEBUG_LOG(0,"TimerID:%d",TimerID);

		pThreadPool->PutTask(pThreadTask);

		return 0;
	}
	else
	{
		return -1;
	}
}

