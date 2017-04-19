#include "kfpc_logex.h"
#include "KFPC_DBThreadPool.h"
#include "KFPC_DBTask.h"
#include "kfpc_msg.h"
KFPC_DBThreadPool::KFPC_DBThreadPool(void):
m_DataBaseAccessList(NULL),
m_DBInx(0)
{
}


KFPC_DBThreadPool::~KFPC_DBThreadPool(void)
{
}

unsigned int KFPC_DBThreadPool::Open( const char* DataSource/*="ContactCenter"*/,const char* UserName/*="ContactCenter"*/,const char* Passwd/*="123456"*/,unsigned char poolSize /*=5*/ )
{
	INFO_LOG(0,"DataSource:%s,UserName:%s,Passwd:%s,poolSize:%u",DataSource ,  UserName , Passwd , poolSize)
	if(m_DataBaseAccessList == NULL)
	{
		m_DBInx = 0;
		smart_new(CDataBaseAccess[poolSize],m_DataBaseAccessList);
		
		for(int i = 0;i<poolSize;i++)
		{
			while(!m_DataBaseAccessList[i].InitDataBase(DataSource, UserName,Passwd))
			{
				Sleep(1000);
			}
		}

	}

	KFPC_ThreadPool::Open(PREFIX_EXPRESSION_VALUE,poolSize);
	return 0;
	
}

void KFPC_DBThreadPool::Close()
{
	KFPC_ThreadPool::Close();

	if(m_DataBaseAccessList != NULL)
	{
		smart_delete([]m_DataBaseAccessList);
		m_DataBaseAccessList = NULL;
	}
	
}
void* KFPC_DBThreadPool::DoThreadProc(KFPC_ThreadParamInfo* pThreadParamInfo)
{
	KFPC_ThreadTask*	pThreadTask = NULL;
	
	//unsigned int DBInx = m_DBInx++;
	unsigned int ThreadInx = pThreadParamInfo->ThreadInx;
	DEBUG_LOG(0,"start ThreadInx:%u",ThreadInx);

	while(true)
	{

		time_t	TaskTime = time(NULL);

		while((pThreadTask = m_ThreadTaskQueue.GetTask(200))!= NULL ||
			(pThreadTask = m_ThreadTaskQueueGroups[ThreadInx].GetTask(0))!= NULL)
		{

			if(pThreadTask->GetThreadTaskType() == TTT_ExitThread)
			{
				smart_delete(pThreadTask);
				DEBUG_LOG(0,"ThreadInx:%u,exit",ThreadInx);

				return NULL;
			}
			else
			{
				//DEBUG_LOG(0,"ThreadInx:%u start",ThreadInx);
				KFPC_DBTask* pDBTask = (KFPC_DBTask*)pThreadTask;
				pDBTask->SetDataBaseAccess(&m_DataBaseAccessList[ThreadInx]);

				time_t Delay =0;

				pThreadTask->DoSvc();

				if(Delay > 0)
				{
					WARNING_LOG(0,"Delay:%u second,and task queue size:%u.",Delay,GetTaskSize());
				}

				//DEBUG_LOG(0,"ThreadInx:%u end",ThreadInx);
				smart_delete (pThreadTask);
			}

			/**< 确保单次循环不要超过单个定时 */
			if((time(NULL) - TaskTime) >  KFPC_ONE_LOOP_TIME)
			{
				WARNING_LOG(0,"ThreadInx:%u,PROC task over %d second",ThreadInx,time(NULL) - TaskTime);
				break;
			}
		}

		
	}

	INFO_LOG(0,"ThreadInx:%u,exit.",ThreadInx);
	return NULL;
}
