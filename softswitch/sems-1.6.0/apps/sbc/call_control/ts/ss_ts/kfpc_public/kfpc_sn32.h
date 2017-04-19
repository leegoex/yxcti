#ifndef kfpc_sn32_h__
#define kfpc_sn32_h__
/********************************************************************
 * @data:		2012/10/10
 * @details:	10:10:2012   10:18
 * @file: 		D:\MyProgram\ͨ�ſ�\kfpc_com\kfpc_public\kfpc_sn32.h 
 * @author:		KFPC
 * @brief:		32λID�����������ѭ�����õ�����
*********************************************************************/
#include "kfpc_linuxwinapi.h"

class KFPC_SN32
{
private:
	KFPC_Mutex			m_Mutex;
	unsigned int  m_SN;
public:
	KFPC_SN32(void);
	~KFPC_SN32(void);
	unsigned int  GetSN();
	unsigned int  MonitorSN(){return m_SN;};
};

#endif // kfpc_sn32_h__

