#ifndef kfpc_mempool_h__
#define kfpc_mempool_h__
/********************************************************************
 * @data:		2012/09/29
 * @details:	29:9:2012   15:00
 * @file: 		d:\MyProgram\通信库\kfpc_com\kfpc_mempool.h 
 * @author:		KFPC
 * @brief:		内存池对象
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
	apr_pool_t *m_Root;	/**< 根池 */
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
	 * @brief 		分配内存
	 * @param[in] unsigned int Size 分配内存大小
	 * @param[in] apr_pool_t * Pool 内存池，如果指定内存就从内存池内分配
	 * @return   	void*
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
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

