#include "KFPC_NumberAnalyse.h"
#include <string.h>

KFPC_NumberAnalyse::KFPC_NumberAnalyse(void)
{
}


KFPC_NumberAnalyse::~KFPC_NumberAnalyse(void)
{
}

unsigned char KFPC_NumberAnalyse::GetNOA( const char* Num,KFPC_SignalType SignalType )
{
	int Noa = NumAnalyse(Num);

	if(KFPC_SignalType_SS7_ISUP == SignalType)
	{
		return IsdnToSs7Noa(Noa);
	}
	
	return Noa;

}
int KFPC_NumberAnalyse::IsdnToSs7Noa( int noa )
{
	/*
	//ISDN
	0x00：未知；
	0x01：国际号码；
	0x02：国内号码；
	0x03：网络特定号码；
	0x04：用户号码；
	0x07：为扩展保留；

	//SS7
	0x00：备用；
	0x01：用户号码；
	0x02：备用，留作国内用；
	0x03：国内（有效）号码；
	0x04：国际号码；
	其他：备用。

	*/

	switch(noa)
	{
	case 0: return 0;
	case 1: return 4;
	case 2: return 3;
	case 4: return 1;
	default:return 0;

	}
}

int KFPC_NumberAnalyse::NumAnalyse( const char* Num )
{
	int NumLen = strlen(Num);

	//0x00：未知；
	//0x01：国际号码；
	//0x02：国内号码；
	//0x03：网络特定号码；
	//0x04：用户号码；
	//0x07：为扩展保留；
	//其他：保留。

	//00开始的为国际号码

	if(strstr(Num,"00") == Num)
	{
		return 1;
	}

	if(strstr(Num,"400") == Num)
	{
		return 2;
	}

	if(NumLen == 3) //为紧急号码 本地号码
	{
		return 4;
	}
	else if(NumLen < 11) //为本地号码
	{
		return 4;
	}
	else if(NumLen = 11) //为手机号 国内
	{
		if(strstr(Num,"0") == Num)
		{
			return 2;
		}
		else
		{
			return 4;
		}		
	}
	else		//其它国内
	{
		return 2;
	}
}
