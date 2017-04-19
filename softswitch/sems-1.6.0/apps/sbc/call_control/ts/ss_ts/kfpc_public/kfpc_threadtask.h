#ifndef kfpc_threadtask_h__
#define kfpc_threadtask_h__
/********************************************************************
 * @data:		2012/09/27
 * @details:	27:9:2012   14:49
 * @file: 		d:\MyProgram\ͨ�ſ�\kfpc_com\kfpc_threadtask.h 
 * @author:		KFPC
 * @brief:		����̳߳�һ��ʹ��
*********************************************************************/
#include <time.h>

#define	MaxThreadDelayAlarm	2

typedef enum ThreadTaskType
{
	
	TTT_RunThread,	/**< ִ���߳� */
	TTT_ExitThread	/**< �˳��߳� */

}ThreadTaskType_t;
/*
typedef enum ThreadTaskSubTypeType
{

	TTT_TimerThread,	
	TTT_MsgThread,	
	TTT_NoThread

}ThreadTaskSubTypeType_t;
*/
class KFPC_ThreadPool;
class KFPC_ThreadTask
{
private:
	ThreadTaskType_t	m_ThreadTaskType;	/**< �߳��������� */
	//ThreadTaskSubTypeType_t m_ThreadSubType;
	time_t				m_TimeStamp;
	time_t GetTimeStamp() const { return m_TimeStamp; }
protected:
	void * m_Param;	
public:
	KFPC_ThreadTask();
	KFPC_ThreadTask(void* p);
	virtual ~KFPC_ThreadTask(void);
	
	void* DoSvc(time_t* pDelay = NULL);	

	virtual void* Svc(){return 0;}	

	//ThreadTaskSubTypeType_t GetSubThreadType() { return m_ThreadSubType;}
	
	ThreadTaskType_t GetThreadTaskType() { return m_ThreadTaskType; }
	void SetThreadTaskType(ThreadTaskType_t val) { m_ThreadTaskType = val; }

};

class KFPC_ExitThreadTask:public KFPC_ThreadTask
{
public:
	KFPC_ExitThreadTask(void);
	~KFPC_ExitThreadTask(void);
};

#endif // kfpc_threadtask_h__

