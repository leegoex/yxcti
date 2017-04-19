#ifndef kfpc_timeouttask_h__
#define kfpc_timeouttask_h__

#include "kfpc_threadtask.h"

class KFPC_TimeoutTask: public KFPC_ThreadTask
{
public:	
	//KFPC_TcpSocket* Agr;
	unsigned int	TimerID;
	KFPC_TimeoutTask(void);
	~KFPC_TimeoutTask(void);
	virtual void* Svc();
};
#endif // kfpc_timeouttask_h__

