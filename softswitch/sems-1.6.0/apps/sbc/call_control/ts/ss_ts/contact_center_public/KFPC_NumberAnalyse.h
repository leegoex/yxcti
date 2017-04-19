#pragma once
#include "KFPC_ContactCenterPublicDef.h"

class KFPC_NumberAnalyse
{
private:
	int IsdnToSs7Noa( int noa );
	int NumAnalyse( const char* pNum );
public:
	KFPC_NumberAnalyse(void);
	~KFPC_NumberAnalyse(void);
	unsigned char GetNOA(const char* Num,KFPC_SignalType	SignalType);

	static KFPC_NumberAnalyse* GetInstance()
	{
		static KFPC_NumberAnalyse _Instance;
		return &_Instance;
	}

};

