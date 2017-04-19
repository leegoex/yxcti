#include "kfpc_mempool.h"


#define MAX_POOL_SIZE    20*1000*1024     /**< max 20M memory pool*/
KFPC_MemPool::KFPC_MemPool(void)
{
	apr_pool_initialize();
	/**
	 *	创建根池(默认父池是全局池)，根池生命期为进程生存期。分配子默认为全局分配子
	 */
	apr_pool_create(&m_Root,NULL);
	SetMaxPoolSize(MAX_POOL_SIZE);
}

void KFPC_MemPool::SetMaxPoolSize(apr_size_t in_size)
{
	if(m_Root == NULL)
	{
		return;
	}
	apr_allocator_t *allocator = apr_pool_allocator_get(m_Root);
	apr_allocator_max_free_set(allocator, in_size );
}

KFPC_MemPool::~KFPC_MemPool(void)
{
	apr_pool_terminate();
}

void* KFPC_MemPool::Alloc( unsigned int Size,apr_pool_t* Pool /*= NULL*/ )
{
	apr_pool_t* pChildPool = NULL;

	if(Pool != NULL)
	{
		pChildPool = Pool;
	}
	else
	{
		apr_pool_create(&pChildPool,m_Root);
	}
	
	
	void* Ret =  apr_palloc(pChildPool,  Size+sizeof(void*));

	memset(Ret,0,Size+sizeof(void*));

	/**< 把内存池子池的指针赋值给分配内存的头四个字节 */
	*((apr_pool_t**)Ret) = pChildPool;

	/**< 返回分配内存指针的第四个字节做为用户地址 */
	return (void*)((unsigned char*)Ret + sizeof(void*));
}

void KFPC_MemPool::Free( void* p)
{
	/**< 找回p指针的前面4个字节的地址 */
	apr_pool_t* PointerHeader = GET_POOL_POINTER(p);
	/**< 并将它转换为内存池指针 */
	apr_pool_destroy(PointerHeader);
}

