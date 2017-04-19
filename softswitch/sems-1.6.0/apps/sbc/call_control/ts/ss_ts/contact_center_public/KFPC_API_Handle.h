#ifndef KFPC_API_Handle_h__
#define KFPC_API_Handle_h__
#include "kfpc_msg.h"

class KFPC_API_Handler
{

public:
	

	KFPC_API_Handler(void);
	virtual ~KFPC_API_Handler(void);
	virtual void RecvMsg(KFPC_MSG_HEADER* pMsg){};
	virtual int SendMsg(KFPC_MSG_HEADER* pMsg){return 0;};
};
#endif // KFPC_API_Handle_h__

