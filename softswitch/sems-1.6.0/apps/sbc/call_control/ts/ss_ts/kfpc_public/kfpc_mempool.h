#ifndef kfpc_mempool_h__
#define kfpc_mempool_h__
/********************************************************************
 * @data:		2012/09/29
 * @details:	29:9:2012   15:00
 * @file: 		d:\MyProgram\ͨ�ſ�\kfpc_com\kfpc_mempool.h 
 * @author:		KFPC
 * @brief:		�ڴ�ض���
*********************************************************************/
#include "apr_pools.h"
/*
typedef struct KFPC_MemNode
{
	apr_pool_t* Pool;
	void*		Pointer;
}KFPC_MemNode;
*/
class KFPC_MemPool
{
private:
	apr_pool_t *m_Root;	/**< ���� */
	void SetMaxPoolSize(apr_size_t in_size);

public:
	KFPC_MemPool(void);
	~KFPC_MemPool(void);

	//static KFPC_MemPool* GetInstance()
	//{
	//	static KFPC_MemPool	MemPool;
	//	return &MemPool;
	//}

	/**
	 * Method:    	Alloc
	 * FullName:  	KFPC_MemPool::Alloc
	 * @brief 		�����ڴ�
	 * @param[in] unsigned int Size �����ڴ��С
	 * @param[in] apr_pool_t * Pool �ڴ�أ����ָ���ڴ�ʹ��ڴ���ڷ���
	 * @return   	void*
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
	 */
	void* Alloc(unsigned int Size,apr_pool_t* Pool = NULL);
	void Free(void*);

};
//#define  KFPCMEMPOOLINSTANCE	KFPC_MemPool::GetInstance
/*--------------------------------------------------------------------------------------------------------------------------------
 |  Macros
 *------------------------------------------------------------------------------------------------------------------------------*/
#define GET_POOL_POINTER(p)	(*((apr_pool_t**)((unsigned char*)p - sizeof(void*))))
#endif // kfpc_mempool_h__

