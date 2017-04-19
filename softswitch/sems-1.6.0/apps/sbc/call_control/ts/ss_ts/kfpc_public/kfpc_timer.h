#ifndef kfpc_timer_h__
#define kfpc_timer_h__
/********************************************************************
 * @data:		2012/10/08
 * @details:	8:10:2012   11:20
 * @file: 		d:\MyProgram\ͨ�ſ�\kfpc_com\kfpc_timer.h 
 * @author:		KFPC
 * @brief:		��ʱ������
*********************************************************************/
//#include "kfpc_linuxwinapi.h"
#include "kfpc_sn32.h"
#include "kfpc_mempool.h"

#include <unordered_map>


using namespace std;
#include "kfpc_mempool.h"

typedef struct	KFPC_TimerQueueData{
	
	unsigned int				OutTime;		/**< ʣ��ʱ�� */
	unsigned int				ID;				/**< ��ʱ��ID */
	void*						Arg1;			/**< �û�����1 */
	void*						Arg2;			/**< �û�����2 */
	unsigned long long			UserContext1;	/**< �û�����1 */
	unsigned long long			UserContext2;	/**< �û�����2 */
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
	KFPC_MemPool			m_MemPool;				/**< �ڴ�� */
	KFPC_TimerQueueData*	m_Head;					/**< ������ͷ */
	KFPC_TimerQueueData*	m_End;					/**< ����β */
	KFPC_TimerQueueData*	m_LastNode;				/**< ���һ���ڵ� */
	TimerQueueDataMap_t		m_TimerQueueDataMap;	/**< ��ʱ��ID�ڵ��ϵ��MAP�� */
	KFPC_Mutex					m_Mutex;				/**< ������� */
	KFPC_SN32				m_IDGenerator;			/**< ��ʱ��ID������ */
	time_t					m_StartTime;			/**< ��ʼʱ�� */
	int						m_ListSize;				/**< ��ʱ�������� */
	KFPC_Event					m_Event;
	unsigned int			m_AlarmValve;		/**< �澯��ֵ */

private:

	/**
	 * Method:    	CheckID
	 * FullName:  	KFPC_Timer::CheckID
	 * @brief 		���ID�Ƿ����
	 * @param[in,out] unsigned int ID
	 * @return   	bool
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
	 */
	bool CheckIDExist( unsigned int ID );

	/**
	 * Method:    	CreateNode
	 * FullName:  	KFPC_Timer::CreateNode
	 * @brief 		�����ڵ�
	 * @param[in] unsigned int ID
	 * @param[in] unsigned int OutTime
	 * @param[in] void * Arg1
	 * @param[in] void * Arg2
	 * @return   	KFPC_TimerQueueData*
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
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
	 * @brief 		���սڵ�
	 * @param[in] KFPC_TimerQueueData * pNode
	 * @return   	void
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
	 */
	void FreeNode(KFPC_TimerQueueData* pNode);

	/**
	 * Method:    	AddNode
	 * FullName:  	KFPC_Timer::AddNode
	 * @brief 		��һ���ڵ㵽β��
	 * @param[in] unsigned int ID
	 * @param[in] unsigned int OutTime
	 * @param[in] void * Arg1
	 * @param[in] void * Arg2
	 * @return   	KFPC_TimerQueueData* pNode	����ɹ����ؽڵ�ָ�룬ʧ�ܷ���NULL
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
	 */
	KFPC_TimerQueueData* AddNode(unsigned int ID,unsigned int	OutTime,void*	Arg1,void*	Arg2,
		unsigned long long&	UserContext1 ,
		unsigned long long&	UserContext2 );

	/**
	 * Method:    	InsertNode
	 * FullName:  	KFPC_Timer::InsertNode
	 * @brief 		����ڵ���pNodeǰ��
	 * @param[in]	 KFPC_TimerQueueData * pNode
	 * @param[in]	unsigned int ID
	 * @param[in]	unsigned int OutTime
	 * @param[in]	void * Arg1
	 * @param[in]	void * Arg2
	 * @return   	KFPC_TimerQueueData* pNode	����ɹ����ؽڵ�ָ�룬ʧ�ܷ���NULL
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
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
	 * @brief 		��ƶ�ʱ��
	 * @param[in,out] void * Arg1
	 * @param[in,out] void * Arg2
	 * @param[in,out] int Interval
	 * @return   	int ���ض�ʱ��ID
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
	 */
	
	unsigned int SetTimer(void *Arg1,void *Arg2,unsigned int Interval,unsigned int SN = 0,
		unsigned long long	UserContext1 = 0,
		unsigned long long	UserContext2 = 0);

	/**
	 * Method:    	OutTime
	 * FullName:  	KFPC_Timer::OutTime
	 * @brief 		��ʱ����ѭ����
	 * @param[out] void * * Arg1
	 * @param[out] void * * Arg2
	 * @return   	int
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
	 */
	int OutTime(unsigned int* TimerID, void **Arg1,void **Arg2,int TimeOut,
		unsigned long long*	UserContext1 = NULL,
		unsigned long long*	UserContext2 = NULL);
	/**
	 * Method:    	ClearTimer
	 * FullName:  	KFPC_Timer::ClearTimer
	 * @brief 		���ָ��ʱ��
	 * @param[in] unsigned int ID
	 * @param[out] void * * Arg1
	 * @param[out] void * * Arg2
	 * @return   	int
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
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

