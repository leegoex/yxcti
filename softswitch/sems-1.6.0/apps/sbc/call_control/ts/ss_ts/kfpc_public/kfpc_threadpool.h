#ifndef kfpc_threadpool_h__
#define kfpc_threadpool_h__
/********************************************************************
 * @data:		2012/09/27
 * @details:	27:9:2012   14:24
 * @file: 		d:\MyProgram\通信库\kfpc_com\kfpc_threadpool.h 
 * @author:		KFPC
 * @brief:		线程池类
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
	volatile unsigned int	m_ThreadCount;	/**< 线程池数量 */
	THREADID*		m_pThreadID;	/**< 线程ID列表 */
	HANDLE_t*		m_pThreadHandle;/**< 线程柄列表 */
	static void*	ThreadProc(void* param);/**< 线程函数 */
protected:
	void PutExitTask();
	int WaitThreadExit();
public:
	KFPC_ThreadTaskQueue	m_ThreadTaskQueue;	/**< 线程任务队列 */
	KFPC_ThreadTaskQueue*	m_ThreadTaskQueueGroups;	/**< 线程任务队列组，就是第一个线程的独的队列 */
	KFPC_ThreadParamInfo*	m_ThreadParamInfo;				/**< 线程信息 */

	KFPC_ThreadPool(void);
	virtual ~KFPC_ThreadPool(void);
	/**
	 * Method:    	Open
	 * FullName:  	KFPC_ThreadPool::Open
	 * @brief 		启动线程池
	 * @param[in] unsigned int ThreadCount	线程池数量
	 * @return   	void
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	int Open(unsigned int CallFunNameLen,const char* pCallFun,unsigned int ThreadCount = 1,unsigned int  StartCoreID = 0);
	/**
	 * Method:    	Close
	 * FullName:  	KFPC_ThreadPool::Close
	 * @brief 		关闭退出线程
	 * @return   	void
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	int Close(const char* ThreadPoolName = "");
	
	/**
	 * Method:    	Svc
	 * FullName:  	KFPC_ThreadPool::Svc
	 * @brief 		线程服务方法,其它子类必须继续这个方法
	 * @return   	void*
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
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

