#include "kfpc_logex.h"
#include "kfpc_linuxwinapi.h"
#include "kfpc_threadtaskqueue.h"
#include "kfpc_log.h"



KFPC_ThreadTaskQueue::KFPC_ThreadTaskQueue(void):
m_AlarmValve(1024)
{
}


KFPC_ThreadTaskQueue::~KFPC_ThreadTaskQueue(void)
{
	Clear();
}

unsigned int KFPC_ThreadTaskQueue::PutTask( KFPC_ThreadTask* pTask )
{
	KFPC_AutoMutex	AutoMutex(&m_Mutex);
	
	if(pTask == NULL)	return m_ThreadTaskList.size();

	m_ThreadTaskList.push_back(pTask);
	m_Event.Signal();
	

	if(m_ThreadTaskList.size() > m_AlarmValve)
	{
		if((m_ThreadTaskList.size() % 100) == 0)
		{
			WARNING_LOG(0,"thread task list size:%d",m_ThreadTaskList.size());
		}
		
	}
	else
	{
#ifdef THREAD_TASK_QUEUE_LOG
	DEBUG_LOG(0,"thread task list size:%d",m_ThreadTaskList.size());
#endif // THREAD_TASK_QUEUE_LOG
		
	}
	
	return m_ThreadTaskList.size();
}

 KFPC_ThreadTask* KFPC_ThreadTaskQueue::GetTask(int Timeout )
{
	KFPC_ThreadTask* pTask = NULL;

	m_Mutex.lock();
	if(m_ThreadTaskList.empty())
	{
		if(Timeout != 0)
		{
			m_Mutex.unlock();
			m_Event.WaitEx(Timeout);
			m_Mutex.lock();

			if(!m_ThreadTaskList.empty())
			{
				pTask = m_ThreadTaskList.front();
				m_ThreadTaskList.pop_front();
			}
		}
	}
	else
	{
		pTask = m_ThreadTaskList.front();
		m_ThreadTaskList.pop_front();
	}


	if(m_ThreadTaskList.size() > m_AlarmValve)
	{
		if((m_ThreadTaskList.size() % 100) == 0)
		{
			WARNING_LOG(0,"thread task list size:%d",m_ThreadTaskList.size());
		}		
	}

	
	m_Mutex.unlock();
	return pTask;
}

 unsigned int KFPC_ThreadTaskQueue::QueueSize()
 {
	KFPC_AutoMutex	AutoMutex(&m_Mutex);
	
	return  m_ThreadTaskList.size();
 }

 void KFPC_ThreadTaskQueue::Clear()
 {
	KFPC_AutoMutex	AutoMutex(&m_Mutex);	

	if(m_ThreadTaskList.size() > 0)
	{
		INFO_LOG(0,"thread task list size:%d",m_ThreadTaskList.size());

		ThreadTaskListIter_t	Iter = m_ThreadTaskList.begin();
		for(;Iter != m_ThreadTaskList.end();Iter++)
		{
			// KFPC_ThreadTask* p= *Iter;
			smart_delete(*Iter);
		}
		m_ThreadTaskList.clear();
	}


 }

