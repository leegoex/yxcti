#ifndef kfpc_sn32_h__
#define kfpc_sn32_h__
/********************************************************************
 * @data:		2012/10/10
 * @details:	10:10:2012   10:18
 * @file: 		D:\MyProgram\通信库\kfpc_com\kfpc_public\kfpc_sn32.h 
 * @author:		KFPC
 * @brief:		32位ID生成器，解决循环重置的问题
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

