#include "kfpc_mempool.h"


#define MAX_POOL_SIZE    20*1000*1024     /**< max 20M memory pool*/
KFPC_MemPool::KFPC_MemPool(void)
{
	apr_pool_initialize();
	/**
	 *	��������(Ĭ�ϸ�����ȫ�ֳ�)������������Ϊ���������ڡ�������Ĭ��Ϊȫ�ַ�����
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

	/**< ���ڴ���ӳص�ָ�븳ֵ�������ڴ��ͷ�ĸ��ֽ� */
	*((apr_pool_t**)Ret) = pChildPool;

	/**< ���ط����ڴ�ָ��ĵ��ĸ��ֽ���Ϊ�û���ַ */
	return (void*)((unsigned char*)Ret + sizeof(void*));
}

void KFPC_MemPool::Free( void* p)
{
	/**< �һ�pָ���ǰ��4���ֽڵĵ�ַ */
	apr_pool_t* PointerHeader = GET_POOL_POINTER(p);
	/**< ������ת��Ϊ�ڴ��ָ�� */
	apr_pool_destroy(PointerHeader);
}

