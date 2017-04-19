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
	0x00��δ֪��
	0x01�����ʺ��룻
	0x02�����ں��룻
	0x03�������ض����룻
	0x04���û����룻
	0x07��Ϊ��չ������

	//SS7
	0x00�����ã�
	0x01���û����룻
	0x02�����ã����������ã�
	0x03�����ڣ���Ч�����룻
	0x04�����ʺ��룻
	���������á�

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

	//0x00��δ֪��
	//0x01�����ʺ��룻
	//0x02�����ں��룻
	//0x03�������ض����룻
	//0x04���û����룻
	//0x07��Ϊ��չ������
	//������������

	//00��ʼ��Ϊ���ʺ���

	if(strstr(Num,"00") == Num)
	{
		return 1;
	}

	if(strstr(Num,"400") == Num)
	{
		return 2;
	}

	if(NumLen == 3) //Ϊ�������� ���غ���
	{
		return 4;
	}
	else if(NumLen < 11) //Ϊ���غ���
	{
		return 4;
	}
	else if(NumLen = 11) //Ϊ�ֻ��� ����
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
	else		//��������
	{
		return 2;
	}
}
