#ifndef kfpc_threadtaskqueue_h__
#define kfpc_threadtaskqueue_h__
/********************************************************************
 * @data:		2012/09/27
 * @details:	27:9:2012   15:08
 * @file: 		d:\MyProgram\通信库\kfpc_com\kfpc_threadtaskqueue.h 
 * @author:		KFPC
 * @brief:		线程任务队列
*********************************************************************/
#include "kfpc_threadtask.h"
#include "kfpc_linuxwinapi.h"

#include <list>
using namespace std;
typedef list<KFPC_ThreadTask*>					ThreadTaskList_t;
typedef list<KFPC_ThreadTask*>::iterator		ThreadTaskListIter_t;
class KFPC_ThreadTaskQueue
{
private:
	ThreadTaskList_t	m_ThreadTaskList;	/**< 线程任务队列 */
	KFPC_Mutex			m_Mutex;			/**< 线程互斥 */
	KFPC_Event			m_Event;			/**< 线程事件 */

	unsigned int		m_AlarmValve;		/**< 告警阀值 */
public:
	int Signal()
	{
		return m_Event.Signal();
	}

	KFPC_ThreadTaskQueue(void);
	~KFPC_ThreadTaskQueue(void);

	unsigned int GetAlarmValve() { return m_AlarmValve; }
	void SetAlarmValve(unsigned int val) { m_AlarmValve = val; }

	unsigned int PutTask(KFPC_ThreadTask* pTask);
	KFPC_ThreadTask* GetTask(int Timeout);
	unsigned int QueueSize();
	void Clear();
};
#endif // kfpc_threadtaskqueue_h__

