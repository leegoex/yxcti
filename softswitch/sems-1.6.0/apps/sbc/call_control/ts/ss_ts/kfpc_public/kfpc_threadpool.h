#ifndef kfpc_threadpool_h__
#define kfpc_threadpool_h__
/********************************************************************
 * @data:		2012/09/27
 * @details:	27:9:2012   14:24
 * @file: 		d:\MyProgram\ͨ�ſ�\kfpc_com\kfpc_threadpool.h 
 * @author:		KFPC
 * @brief:		�̳߳���
*********************************************************************/

#include "kfpc_threadtaskqueue.h"

class KFPC_ThreadPool;

typedef struct KFPC_ThreadParamInfo
{
	KFPC_ThreadPool*	ThreadPoolThis;
	unsigned int ThreadInx;
}KFPC_ThreadParamInfo;

class KFPC_ThreadPool
{
protected:
	volatile unsigned int	m_ThreadCount;	/**< �̳߳����� */
	THREADID*		m_pThreadID;	/**< �߳�ID�б� */
	HANDLE_t*		m_pThreadHandle;/**< �̱߳��б� */
	static void*	ThreadProc(void* param);/**< �̺߳��� */
protected:
	void PutExitTask();
	int WaitThreadExit();
public:
	KFPC_ThreadTaskQueue	m_ThreadTaskQueue;	/**< �߳�������� */
	KFPC_ThreadTaskQueue*	m_ThreadTaskQueueGroups;	/**< �߳���������飬���ǵ�һ���̵߳Ķ��Ķ��� */
	KFPC_ThreadParamInfo*	m_ThreadParamInfo;				/**< �߳���Ϣ */

	KFPC_ThreadPool(void);
	virtual ~KFPC_ThreadPool(void);
	/**
	 * Method:    	Open
	 * FullName:  	KFPC_ThreadPool::Open
	 * @brief 		�����̳߳�
	 * @param[in] unsigned int ThreadCount	�̳߳�����
	 * @return   	void
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
	 */
	int Open(unsigned int CallFunNameLen,const char* pCallFun,unsigned int ThreadCount = 1,unsigned int  StartCoreID = 0);
	/**
	 * Method:    	Close
	 * FullName:  	KFPC_ThreadPool::Close
	 * @brief 		�ر��˳��߳�
	 * @return   	void
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
	 */
	int Close(const char* ThreadPoolName = "");
	
	/**
	 * Method:    	Svc
	 * FullName:  	KFPC_ThreadPool::Svc
	 * @brief 		�̷߳��񷽷�,���������������������
	 * @return   	void*
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
	 */
	virtual void* DoThreadProc(KFPC_ThreadParamInfo* pThreadParamInfo);

	virtual unsigned int PutTask(KFPC_ThreadTask* pTask);
	KFPC_ThreadTask* GetTask(int Timeout);
	unsigned long GetTaskSize();

	unsigned int PutTaskThreadInx(KFPC_ThreadTask* pTask,unsigned int ThreadInx);
	KFPC_ThreadTask* GetTaskThreadInx(int Timeout,unsigned int ThreadInx);

	unsigned int GetThreadCount() { return m_ThreadCount; }
	void SetThreadCount( unsigned int val) { m_ThreadCount = val; }

};
#endif // kfpc_threadpool_h__

