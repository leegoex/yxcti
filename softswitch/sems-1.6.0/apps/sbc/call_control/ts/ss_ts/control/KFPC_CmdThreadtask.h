#ifndef kfpc_cmd_threadtask_h__
#define kfpc_cmd_threadtask_h__


#include "kfpc_threadtask.h"
class KFPC_Channel;

class KFPC_CmdThreadTask :
	public KFPC_ThreadTask
{
private:
	KFPC_Channel*	m_pCh;
public:
	KFPC_CmdThreadTask(KFPC_Channel* pChannel);
	virtual ~KFPC_CmdThreadTask(void);
	virtual void* Svc(); 	
};
#endif // kfpc_cmd_threadtask_h__