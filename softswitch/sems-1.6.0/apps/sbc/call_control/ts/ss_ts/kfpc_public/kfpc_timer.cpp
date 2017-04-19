#include "kfpc_timer.h"
#include "kfpc_log.h"
#include "kfpc_linuxwinapi.h"
#include "kfpc_logex.h"


//#define TIMER_LOG   1

KFPC_Timer::KFPC_Timer(void):
m_Head(NULL),
m_End(NULL),
m_LastNode(NULL),
m_StartTime(0),
m_ListSize(0),
m_AlarmValve(1024)
{
}


KFPC_Timer::~KFPC_Timer(void)
{
	Clear();
}

KFPC_TimerQueueData* KFPC_Timer::AddNode( unsigned int ID,unsigned int OutTime,void* Arg1,void* Arg2 ,
		unsigned long long&	UserContext1 ,
		unsigned long long&	UserContext2)
{
	if(CheckIDExist(ID)) return NULL;

	KFPC_TimerQueueData*		pTimerQueueData = CreateNode(ID, OutTime, Arg1, Arg2,UserContext1,UserContext2);

	if(m_Head == NULL)
	{		
		if(m_TimerQueueDataMap.size() > 0)
		{
			WARNING_LOG(0,"timer map doest not match timer list.");
		}

		m_Head = m_End = pTimerQueueData;		
	}
	else
	{
		pTimerQueueData->Prev = m_End;
		m_End->Next = pTimerQueueData;

		m_End = pTimerQueueData;
	}

	m_TimerQueueDataMap.insert(TimerQueueDataMapPair_t(ID,pTimerQueueData));
	//INFO_LOG(0, "Add TimerID:%u, m_TimerQueueDataMap size=%u",ID,m_TimerQueueDataMap.size());

	return pTimerQueueData;
}

KFPC_TimerQueueData* KFPC_Timer::InsertNode( KFPC_TimerQueueData* pNode,unsigned int ID,unsigned int OutTime,void* Arg1,void* Arg2 ,
	unsigned long long&	UserContext1 ,
	unsigned long long&	UserContext2)
{
	if(CheckIDExist(ID)) return NULL;

	KFPC_TimerQueueData*		pTimerQueueData = CreateNode(ID, OutTime, Arg1, Arg2,UserContext1,UserContext2);

	pTimerQueueData->Next = pNode;
	pTimerQueueData->Prev = pNode->Prev;	

	pNode->Prev = pTimerQueueData;

	if(pNode == m_Head)
	{
		m_Head = pTimerQueueData;
	}
	else
	{
		pTimerQueueData->Prev->Next = pTimerQueueData;
	}

	m_TimerQueueDataMap.insert(TimerQueueDataMapPair_t(ID,pTimerQueueData));

	return pTimerQueueData;
}

KFPC_TimerQueueData* KFPC_Timer::CreateNode( unsigned int ID, unsigned int OutTime,void* Arg1,void* Arg2 ,
	unsigned long long&	UserContext1 ,
	unsigned long long&	UserContext2)
{
	KFPC_TimerQueueData*		pTimerQueueData = (KFPC_TimerQueueData*)m_MemPool.Alloc(sizeof(KFPC_TimerQueueData));

	//KFPC_TimerQueueData*		pTimerQueueData = smart_new(KFPC_TimerQueueData);

	pTimerQueueData->ID = ID;
	pTimerQueueData->OutTime = OutTime;
	pTimerQueueData->Arg1 = Arg1;
	pTimerQueueData->Arg2 = Arg2;
	pTimerQueueData->UserContext1 = UserContext1;
	pTimerQueueData->UserContext2 = UserContext2;

	pTimerQueueData->Next = NULL;
	pTimerQueueData->Prev = NULL;
	m_ListSize++;
	return pTimerQueueData;
}

void KFPC_Timer::FreeNode( KFPC_TimerQueueData* pNode )
{
	m_ListSize--;
	//smart_delete(pNode);
	m_MemPool.Free(pNode);
}

bool KFPC_Timer::CheckIDExist( unsigned int ID )
{
	TimerQueueDataMapIter_t Iter		= m_TimerQueueDataMap.find(ID);

	if(Iter != m_TimerQueueDataMap.end())
	{
		ERROR_LOG(0,"CheckID ID:%d already exist.",ID);
		return true;
	}
	else
	{
		return false;
	}
}


KFPC_TimerQueueData* KFPC_Timer::FindNode( unsigned int ID )
{
	TimerQueueDataMapIter_t Iter		= m_TimerQueueDataMap.find(ID);

	if(Iter != m_TimerQueueDataMap.end())
	{
		return Iter->second;
	}
	else
	{
		WARNING_LOG(0,"FindID ID:%d err in Map, Map size:%u.",ID,m_TimerQueueDataMap.size());
		return NULL;
	}
}

bool KFPC_Timer::DelNode( unsigned int ID )
{
	TimerQueueDataMapIter_t Iter		= m_TimerQueueDataMap.find(ID);

	if(Iter != m_TimerQueueDataMap.end())
	{
		KFPC_TimerQueueData* pNode = Iter->second;

		m_TimerQueueDataMap.erase(ID);

		if(pNode == m_Head)
		{
			if(m_Head == m_End)
			{
				m_LastNode = m_Head = m_End = NULL;

				if(m_TimerQueueDataMap.size() > 0)
				{
					WARNING_LOG(0,"timer map doest not match timer list.");
				}
				else
				{
					#ifdef	TIMER_LOG
					
					DEBUG_LOG(0,"m_LastNode = m_Head = m_End = NULL");

					#endif
				}
			}
			else
			{

				m_LastNode = m_Head->Next;
				m_Head=m_Head->Next;
				m_Head->Prev = NULL;


				#ifdef TIMER_LOG
				DEBUG_LOG(0,"Head:%d",m_Head->ID);
				#endif // TIMER_LOG

			}
		}
		else if(pNode == m_End)
		{
			m_LastNode = pNode->Prev;

			KFPC_TimerQueueData* prev = pNode->Prev;

			prev->Next = NULL;
			m_End = prev;


#ifdef TIMER_LOG
			{
				DEBUG_LOG(0,"End:%d",m_End->ID);
			}
#endif // TIMER_LOG
		}
		else
		{
			m_LastNode = pNode->Prev;

			KFPC_TimerQueueData* prev = pNode->Prev;
			KFPC_TimerQueueData* next = pNode->Next;

			next->Prev = prev;
			prev->Next = next;


#ifdef TIMER_LOG
			{
				DEBUG_LOG(0,"Prev:%d,Next:%d",prev->ID,next->ID);
			}
#endif // TIMER_LOG

		}

		FreeNode(pNode);

		return true;
	}
	else
	{
		ERROR_LOG(0,"ID:%d ineistnce",ID);
		return false;
	}
}

size_t KFPC_Timer::Size()
{
	return m_TimerQueueDataMap.size();
}

unsigned int KFPC_Timer::SetTimer( void *Arg1,void *Arg2,unsigned int Interval,unsigned int SN ,
	unsigned long long	UserContext1 ,
	unsigned long long	UserContext2)
{
	
	KFPC_AutoMutex	AutoMutex(&m_Mutex);

	unsigned int TimerID = SN;

	if(SN == 0)
	{
		TimerID = m_IDGenerator.GetSN();
	}
	

	if (m_Head==NULL)
	{
		m_StartTime = time(NULL);
	}
	else
	{
		time_t Nowtime = time(NULL);

		unsigned int ElapseTime  = (unsigned int )(Nowtime - m_StartTime);	/**< 流逝的时间 */
		

		if(m_Head->OutTime > ElapseTime)
		{
			m_Head->OutTime -= ElapseTime;
		}
		else
		{
			m_Head->OutTime = 0;	/**< 定时器已经到期 */
		}

		m_StartTime = time(NULL);
	}


	KFPC_TimerQueueData* pTimerQueueHead = m_Head;
	KFPC_TimerQueueData* pTimerQueuePrev = NULL;
	KFPC_TimerQueueData* pNewTimerQueue = NULL;

	if (pTimerQueueHead==NULL)
	{
		pNewTimerQueue = AddNode(TimerID,Interval,Arg1,Arg2,UserContext1,UserContext2);



#ifdef TIMER_LOG
		if(m_TimerQueueDataMap.size() >	m_AlarmValve)
		{
			WARNING_LOG(0,"timer list size:%d,map size:%d,Interval:%u,TimerID:%u,StartTime:%u and at queue head.",m_ListSize,m_TimerQueueDataMap.size(),Interval,TimerID,m_StartTime);

		}
		else
		{
			DEBUG_LOG(0,"timer list size:%d,map size:%d,Interval:%u,TimerID:%u,StartTime:%u,and at queue head.",m_ListSize,m_TimerQueueDataMap.size(),Interval,TimerID,m_StartTime);
		}
#endif // TIMER_LOG

		m_Event.Signal();

		return TimerID;
	}

	while(pTimerQueueHead != NULL)
	{
		if (pTimerQueueHead->OutTime > Interval)
		{
			pTimerQueueHead->OutTime -= Interval;
			/**
			 *	把当前定时器插在pTimerQueueHead前面
			 */
			pNewTimerQueue = InsertNode(pTimerQueueHead,TimerID,Interval,Arg1,Arg2,UserContext1,UserContext2);


#ifdef TIMER_LOG
			if(m_TimerQueueDataMap.size() >	m_AlarmValve)
			{
				WARNING_LOG(0,"timer list size:%d,map size:%d,Interval:%u,TimerID:%u.",m_ListSize,m_TimerQueueDataMap.size(),Interval,TimerID);

			}
			else
			{
				DEBUG_LOG(0,"timer list size:%d,map size:%d,Interval:%u,TimerID:%u.",m_ListSize,m_TimerQueueDataMap.size(),Interval,TimerID);
			}
#endif // TIMER_LOG

			m_Event.Signal();
			return TimerID;
		}
		else
		{
			/**
			 *	递减定时器
			 */
			Interval = Interval - pTimerQueueHead->OutTime;

			if(pTimerQueueHead->Next==NULL)
			{
				/**
				 *	加到最后
				 */
				pNewTimerQueue = AddNode(TimerID,Interval,Arg1,Arg2,UserContext1,UserContext2);


#ifdef TIMER_LOG
				if(m_TimerQueueDataMap.size() >	m_AlarmValve)
				{
					WARNING_LOG(0,"timer list size:%d,map size:%d,Interval:%u,TimerID:%u.",m_ListSize,m_TimerQueueDataMap.size(),Interval,TimerID);

				}
				else
				{
					DEBUG_LOG(0,"timer list size:%d,map size:%d,Interval:%u,TimerID:%u.",m_ListSize,m_TimerQueueDataMap.size(),Interval,TimerID);
				}
#endif // TIMER_LOG

				m_Event.Signal();
				
				return TimerID;
			}
			else
			{
				pTimerQueueHead=pTimerQueueHead->Next;
			}
		}
	}
	
	ERROR_LOG(0,"return -1");
	return -1;

}

int KFPC_Timer::OutTime(unsigned int* TimerID, void **Arg1,void **Arg2,int TimeOut,unsigned long long*	UserContext1 ,
	unsigned long long*	UserContext2  )
{	
	m_Mutex.lock();
	
	time_t Nowtime = time(NULL);
	bool	StartTimer = false;

	if (m_Head==NULL)
	{
		if(TimeOut != 0)
		{
			StartTimer = true;
		}
		else
		{
			m_Mutex.unlock();
			return -1;
		}
	}
	else
	{
		time_t ElapseTime= Nowtime-m_StartTime;
		if (ElapseTime < m_Head->OutTime)
		{
			StartTimer = true;
		}
	}

	if(StartTimer)
	{
		if(TimeOut != 0)
		{	
			m_Mutex.unlock();

			m_Event.WaitEx(TimeOut);

			m_Mutex.lock();

			if (m_Head==NULL)
			{
				m_Mutex.unlock();
				return -1;
			}
		}
		else
		{
			m_Mutex.unlock();
			return -1;
		}
	}
		
	
	Nowtime = time(NULL);
	time_t ElapseTime=Nowtime-m_StartTime;
	//ElapseTime可能为负数，所以不用能无符号整型
	if( ElapseTime >=m_Head->OutTime )
    {
        KFPC_TimerQueueData* pTimerQueueData = m_Head;
	
		*Arg1 = pTimerQueueData->Arg1;
		*Arg2 = pTimerQueueData->Arg2;
		*TimerID = pTimerQueueData->ID;

		if(UserContext1 != NULL)
		{
			*UserContext1 = pTimerQueueData->UserContext1;
		}

		if(UserContext2 != NULL)
		{
			*UserContext2 = pTimerQueueData->UserContext2;
		}

		DelNode(pTimerQueueData->ID);

		m_StartTime = time(NULL);


#ifdef TIMER_LOG
		if(m_TimerQueueDataMap.size() >	m_AlarmValve)
		{
			WARNING_LOG(0,"timer list size:%d,map size:%d,TimerID:%u,Nowtime:%u,StartTime:%u.",m_ListSize,m_TimerQueueDataMap.size(),*TimerID,Nowtime,m_StartTime);
		}
		else
		{
			DEBUG_LOG(0,"timer list size:%d,map size:%d,TimerID:%u,Nowtime:%u,StartTime:%u.",m_ListSize,m_TimerQueueDataMap.size(),*TimerID,Nowtime,m_StartTime);
		}
#endif // TIMER_LOG

		m_Mutex.unlock();
		return 0;
	}

	m_Mutex.unlock();
	return -1;
}

bool KFPC_Timer::ClearTimer( unsigned int ID,void **Arg1 /*= NULL*/,void **Arg2/*=NULL*/ ,
	unsigned long long*	UserContext1 ,
	unsigned long long*	UserContext2 )
{

#ifdef TIMER_LOG
	if(m_TimerQueueDataMap.size() >	m_AlarmValve)
	{
		WARNING_LOG(0,"timer list size:%d,map size:%d,TimerID:%u.",m_ListSize,m_TimerQueueDataMap.size(),ID);
	}
	else
	{
		DEBUG_LOG(0,"timer list size:%d,map size:%d,TimerID:%u.",m_ListSize,m_TimerQueueDataMap.size(),ID);
	}
#endif // TIMER_LOG

	KFPC_AutoMutex	AutoMutex(&m_Mutex);

	KFPC_TimerQueueData*  pTimerQueueData = FindNode(ID);

	if(pTimerQueueData == NULL)
	{
		return false;	
	}
	else
	{
		if(Arg1 != NULL)
		{
			*Arg1 = pTimerQueueData->Arg1;
		}

		if(Arg2 != NULL)
		{
			*Arg2 = pTimerQueueData->Arg2;
		}
		
		if(UserContext1 != NULL)
		{
			*UserContext1 = pTimerQueueData->UserContext1;
		}

		if(UserContext2 != NULL)
		{
			*UserContext2 = pTimerQueueData->UserContext2;
		}

		if(pTimerQueueData->Next != NULL)
		{
			(pTimerQueueData->Next)->OutTime += pTimerQueueData->OutTime;
		}


		DelNode(pTimerQueueData->ID);

		m_Event.Signal();

		return true;
	}
	
}

void KFPC_Timer::Clear()
{
	KFPC_AutoMutex	AutoMutex(&m_Mutex);

	KFPC_TimerQueueData*  pTimerQueueData = NULL;

	while(m_End != NULL)
	{
		pTimerQueueData= m_Head;


		if(m_Head == m_End)
		{
			m_End = m_End->Next;
		}

		m_Head = m_Head->Next;
		FreeNode(pTimerQueueData);
	}

	m_TimerQueueDataMap.clear();

	m_Event.Signal();
}

bool KFPC_Timer::PopTimer( unsigned int* ID,void **Arg1 /*= NULL*/,void **Arg2/*=NULL*/,
	unsigned long long*	UserContext1 ,
	unsigned long long*	UserContext2)
{
	KFPC_AutoMutex	AutoMutex(&m_Mutex);

	if(m_Head == NULL)
	{
		return false;
	}

	KFPC_TimerQueueData* pTimerQueueData = m_Head;

	*ID = pTimerQueueData->ID;
	*Arg1 = pTimerQueueData->Arg1;
	*Arg2 = pTimerQueueData->Arg2;

	if(UserContext1 != NULL)
	{
		*UserContext1 = pTimerQueueData->UserContext1;
	}

	if(UserContext2 != NULL)
	{
		*UserContext2 = pTimerQueueData->UserContext2;
	}

	DelNode(pTimerQueueData->ID);

	m_StartTime = time(NULL);


#ifdef TIMER_LOG
	{
		DEBUG_LOG(0,"timer list size:%d,map size:%d.",m_ListSize,m_TimerQueueDataMap.size());	
	}
#endif // TIMER_LOG

	return true;
}

