
#ifndef kfpc_sn64_h__
#define kfpc_sn64_h__
/********************************************************************
 * @data:		2012/10/10
 * @details:	10:10:2012   10:19
 * @file: 		D:\MyProgram\ͨ�ſ�\kfpc_com\kfpc_public\kfpc_sn64.h 
 * @author:		KFPC
 * @brief:		64λID������,64λ��ӡ���printf("%lld",64val);
*********************************************************************/
#include "kfpc_linuxwinapi.h"

class KFPC_SN64
{
private:
	KFPC_Mutex			m_Mutex;
	long long m_SN;
public:
	KFPC_SN64(bool start0 = false);
	~KFPC_SN64(void);
	long long GetSN();
};
#endif // kfpc_sn64_h__

