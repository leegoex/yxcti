#ifndef kfpc_timer_h__
#define kfpc_timer_h__
/********************************************************************
 * @data:		2012/10/08
 * @details:	8:10:2012   11:20
 * @file: 		d:\MyProgram\通信库\kfpc_com\kfpc_timer.h 
 * @author:		KFPC
 * @brief:		定时器队列
*********************************************************************/
//#include "kfpc_linuxwinapi.h"
#include "kfpc_sn32.h"
#include "kfpc_mempool.h"

#include <unordered_map>


using namespace std;
#include "kfpc_mempool.h"

typedef struct	KFPC_TimerQueueData{
	
	unsigned int				OutTime;		/**< 剩余时间 */
	unsigned int				ID;				/**< 定时器ID */
	void*						Arg1;			/**< 用户数据1 */
	void*						Arg2;			/**< 用户数据2 */
	unsigned long long			UserContext1;	/**< 用户数据1 */
	unsigned long long			UserContext2;	/**< 用户数据2 */
	struct KFPC_TimerQueueData* Prev;			
	struct KFPC_TimerQueueData* Next;
}KFPC_TimerQueueData;

typedef unordered_map <unsigned int, KFPC_TimerQueueData*>		TimerQueueDataMap_t;
typedef TimerQueueDataMap_t:: iterator						TimerQueueDataMapIter_t;
typedef pair<unsigned int, KFPC_TimerQueueData*>			TimerQueueDataMapPair_t;
typedef pair< TimerQueueDataMap_t:: iterator, bool >		TimerQueueDataMapInsertResult_t;

class KFPC_Timer
{
private:
	KFPC_MemPool			m_MemPool;				/**< 内存池 */
	KFPC_TimerQueueData*	m_Head;					/**< 链表针头 */
	KFPC_TimerQueueData*	m_End;					/**< 链表尾 */
	KFPC_TimerQueueData*	m_LastNode;				/**< 最后一个节点 */
	TimerQueueDataMap_t		m_TimerQueueDataMap;	/**< 定时器ID节点关系与MAP表 */
	KFPC_Mutex					m_Mutex;				/**< 互斥对象 */
	KFPC_SN32				m_IDGenerator;			/**< 定时器ID生成器 */
	time_t					m_StartTime;			/**< 开始时间 */
	int						m_ListSize;				/**< 定时器链表长度 */
	KFPC_Event					m_Event;
	unsigned int			m_AlarmValve;		/**< 告警阀值 */

private:

	/**
	 * Method:    	CheckID
	 * FullName:  	KFPC_Timer::CheckID
	 * @brief 		检查ID是否存在
	 * @param[in,out] unsigned int ID
	 * @return   	bool
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	bool CheckIDExist( unsigned int ID );

	/**
	 * Method:    	CreateNode
	 * FullName:  	KFPC_Timer::CreateNode
	 * @brief 		创建节点
	 * @param[in] unsigned int ID
	 * @param[in] unsigned int OutTime
	 * @param[in] void * Arg1
	 * @param[in] void * Arg2
	 * @return   	KFPC_TimerQueueData*
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	KFPC_TimerQueueData* CreateNode( unsigned int ID, 
		unsigned int OutTime, 
		void* Arg1, 
		void* Arg2,
		unsigned long long&	UserContext1 ,
		unsigned long long&	UserContext2 );

	/**
	 * Method:    	FreeNode
	 * FullName:  	KFPC_Timer::FreeNode
	 * @brief 		回收节点
	 * @param[in] KFPC_TimerQueueData * pNode
	 * @return   	void
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	void FreeNode(KFPC_TimerQueueData* pNode);

	/**
	 * Method:    	AddNode
	 * FullName:  	KFPC_Timer::AddNode
	 * @brief 		增一个节点到尾部
	 * @param[in] unsigned int ID
	 * @param[in] unsigned int OutTime
	 * @param[in] void * Arg1
	 * @param[in] void * Arg2
	 * @return   	KFPC_TimerQueueData* pNode	如果成功返回节点指针，失败返回NULL
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	KFPC_TimerQueueData* AddNode(unsigned int ID,unsigned int	OutTime,void*	Arg1,void*	Arg2,
		unsigned long long&	UserContext1 ,
		unsigned long long&	UserContext2 );

	/**
	 * Method:    	InsertNode
	 * FullName:  	KFPC_Timer::InsertNode
	 * @brief 		插入节点在pNode前面
	 * @param[in]	 KFPC_TimerQueueData * pNode
	 * @param[in]	unsigned int ID
	 * @param[in]	unsigned int OutTime
	 * @param[in]	void * Arg1
	 * @param[in]	void * Arg2
	 * @return   	KFPC_TimerQueueData* pNode	如果成功返回节点指针，失败返回NULL
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	KFPC_TimerQueueData* InsertNode(KFPC_TimerQueueData* pNode,unsigned int ID,unsigned int	OutTime,void*	Arg1,void*	Arg2,
		unsigned long long&	UserContext1 ,
		unsigned long long&	UserContext2 );

	bool DelNode(unsigned int ID);


	KFPC_TimerQueueData* FirstNode(){return m_Head;}
	KFPC_TimerQueueData* NextNode(KFPC_TimerQueueData* pNode){return pNode->Next;}
	KFPC_TimerQueueData* FindNode(unsigned int ID);	
	KFPC_TimerQueueData* GetLastNode() { return m_LastNode; }

	

	void SetLastNode(KFPC_TimerQueueData* val) { m_LastNode = val; }
	
public:

	unsigned int GetAlarmValve() { return m_AlarmValve; }
	void SetAlarmValve(unsigned int val) { m_AlarmValve = val; }	


	size_t Size();

	KFPC_Timer(void);
	~KFPC_Timer(void);
	/**
	 * Method:    	SetTimer
	 * FullName:  	KFPC_Timer::SetTimer
	 * @brief 		设计定时器
	 * @param[in,out] void * Arg1
	 * @param[in,out] void * Arg2
	 * @param[in,out] int Interval
	 * @return   	int 返回定时器ID
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	
	unsigned int SetTimer(void *Arg1,void *Arg2,unsigned int Interval,unsigned int SN = 0,
		unsigned long long	UserContext1 = 0,
		unsigned long long	UserContext2 = 0);

	/**
	 * Method:    	OutTime
	 * FullName:  	KFPC_Timer::OutTime
	 * @brief 		定时器轮循函数
	 * @param[out] void * * Arg1
	 * @param[out] void * * Arg2
	 * @return   	int
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	int OutTime(unsigned int* TimerID, void **Arg1,void **Arg2,int TimeOut,
		unsigned long long*	UserContext1 = NULL,
		unsigned long long*	UserContext2 = NULL);
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
	bool ClearTimer(unsigned int ID,void **Arg1 = NULL,void **Arg2=NULL,		
		unsigned long long*	UserContext1 = NULL,
		unsigned long long*	UserContext2 = NULL);	

	bool PopTimer(unsigned int* ID,void **Arg1 = NULL,void **Arg2=NULL,		
		unsigned long long*	UserContext1 = NULL,
		unsigned long long*	UserContext2 = NULL);

	void Clear();
};

#endif // kfpc_timer_h__

