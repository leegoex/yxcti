#pragma once
class KFPC_LoopHandler
{
public:
	KFPC_LoopHandler(void);
	virtual ~KFPC_LoopHandler(void);
	virtual int Run() {return -1;};
};

