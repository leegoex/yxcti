#include "kfpc_sn64.h"
#include <time.h>
static const long long MaxInt = 1000000000;
KFPC_SN64::KFPC_SN64(bool start0)
{
	
	if(start0)
	{	
		/**< 从1开始 */
		m_SN = 1;
	}
	else
	{
		time_t	t = time(NULL);

		m_SN = t*MaxInt;	
	}

}
KFPC_SN64::~KFPC_SN64(void)
{
}

long long KFPC_SN64::GetSN()
{
	KFPC_AutoMutex	AutoMtex(&m_Mutex);
	m_SN++;

	if(m_SN < 0)
	{
		//估计没有机会运行到
		time_t	t = time(NULL);

		m_SN = t*MaxInt;	
	}

	return m_SN;
}

