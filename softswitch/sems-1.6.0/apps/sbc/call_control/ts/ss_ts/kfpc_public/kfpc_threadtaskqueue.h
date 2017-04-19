#ifndef kfpc_threadtaskqueue_h__
#define kfpc_threadtaskqueue_h__
/********************************************************************
 * @data:		2012/09/27
 * @details:	27:9:2012   15:08
 * @file: 		d:\MyProgram\ͨ�ſ�\kfpc_com\kfpc_threadtaskqueue.h 
 * @author:		KFPC
 * @brief:		�߳��������
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
	ThreadTaskList_t	m_ThreadTaskList;	/**< �߳�������� */
	KFPC_Mutex			m_Mutex;			/**< �̻߳��� */
	KFPC_Event			m_Event;			/**< �߳��¼� */

	unsigned int		m_AlarmValve;		/**< �澯��ֵ */
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

