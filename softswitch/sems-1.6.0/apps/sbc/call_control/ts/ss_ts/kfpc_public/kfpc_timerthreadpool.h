#ifndef kfpc_timerthreadpool_h__
#define kfpc_timerthreadpool_h__


#include "kfpc_threadpool.h"
#include "kfpc_timer.h"


class KFPC_TimerThreadPool :
	public KFPC_ThreadPool
{
private:
	KFPC_Timer*		m_TimerArray;	/**< 定时器数组 */
	KFPC_SN32		m_IDGenerator;			/**< 定时器ID生成器 */
	unsigned int	m_ThreadIndex;
	KFPC_Mutex			m_Mutex;
protected:


	virtual void* DoThreadProc(KFPC_ThreadParamInfo* pThreadParamInfo);

	virtual int ProcOutTime(unsigned int TimerIndex);

public:
	KFPC_TimerThreadPool(void);
	~KFPC_TimerThreadPool(void);

	void Open(unsigned int ThreadCount);
	void Close();

	static KFPC_TimerThreadPool* GetInstance()
	{
		static KFPC_TimerThreadPool	RoactorThreadPool;
		return &RoactorThreadPool;
	}


	/**
	 * Method:    	SetTimer
	 * FullName:  	KFPC_Timer::SetTimer
	 * @brief 		设计定时器
	 * @param[in,out] KFPC_ThreadPool * Arg1
	 * @param[in,out] void * Arg2
	 * @param[in,out] int Interval
	 * @return   	int 返回定时器ID
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	unsigned int SetTimer(KFPC_ThreadPool *Arg1,KFPC_ThreadTask *Arg2,unsigned int Interval);

	/**
	 * Method:    	ClearTimer
	 * FullName:  	KFPC_Timer::ClearTimer
	 * @brief 		清除指定时器
	 * @param[in] unsigned int ID
	 * @param[out] void * * Arg1
	 * @param[out] void * * Arg2
	 * @return   	int
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	bool ClearTimer(unsigned int ID,void **Arg1 = NULL,void **Arg2=NULL);	

};
#define KFPCTimerThreadPoolInstance	KFPC_TimerThreadPool::GetInstance()
#endif // kfpc_timerthreadpool_h__

