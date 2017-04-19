#pragma once

#include "KFPC_TServerDef.h"
#include "KFPC_ChRes.h"

class KFPC_ChRes
{
protected:
	unsigned long long m_CallID;
public:
	KFPC_ChRes();
	virtual ~KFPC_ChRes();
};

