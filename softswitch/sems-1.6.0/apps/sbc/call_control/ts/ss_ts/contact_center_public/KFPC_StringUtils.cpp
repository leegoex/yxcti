#include <string.h>
#include <vector>
#include "KFPC_StringUtils.h"
#include <iconv.h>
#include <stdio.h>

void LTrim(char* str,const char c)
{
	size_t	iLen = strlen(str);
	unsigned int i = 0;
	while(str[i] == c && i < iLen)
		i++;
	if(i > 0)
		strcpy(str,str + i);
}

void RTrim(char* str,const char c)
{
	size_t	iLen = strlen(str);
	while(iLen > 0 && str[iLen - 1] == c  )
	{	
		iLen--;	
		str[iLen] = '\0';
	}
}

void Trim(char *str,const char c)
{
	RTrim(str,c);
	LTrim(str,c);
}

void Replace(char *str,const char oldChar,const char newChar)
{
	size_t iLen = strlen(str);
	size_t i = 0; 
	for ( i = 0; i < iLen; i++)
	{
		if (str[i] == oldChar)
			str[i] = newChar;
	}
}

//
//void Replace(std::string *strResult,const char *source,const char cOldChar,const char *csNew)
//{
//	*strResult = std::string("");
//	std::string strSource = source;
//	size_t iSourceLen = strSource.length();
//
//	if(iSourceLen > 0)
//	{
//		for (size_t i = 0; i < iSourceLen; i++)
//		{
//			if(source[i] == cOldChar)
//				strResult->append(csNew);
//			else
//				strResult->append(1,source[i]);
//		}
//	}
//}


bool IsNumber(const char *str)
{
	size_t uiLen = strlen(str);
	if (uiLen < 1)
		return false;
	for(size_t i = 0;i < uiLen;i++)
	{
		if(str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

bool IsNumberSign(const char *str)
{
	size_t uiLen = strlen(str);
	if (uiLen < 2)
		return false;
	if ((str[0] != '-')&&(str[0] != '+')&&(str[0] < '0' || str[0] > '9'))
		return false;
	for(size_t i = 1;i < strlen(str);i++)
	{
		if(str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

bool IsDecimal(const char *str)
{
	unsigned int iDotCount = 0;
	size_t uiLen = strlen(str);
	if (uiLen < 1)
		return false;
	for(size_t i = 0;i < uiLen;i++)
	{
		if (iDotCount > 1)
			return false;
		if (str[i] == '.')
			iDotCount++;
		else if(str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

bool IsDecimalSign(const char *str)
{
	unsigned int iDotCount = 0;
	size_t uiLen = strlen(str);
	if (uiLen < 2)
		return false;
	if (str[0] == '.')
		iDotCount++;
	else if ((str[0] != '-')&&(str[0] != '+')&&(str[0] < '0' || str[0] > '9'))
		return false;

	for(size_t i = 1;i < uiLen;i++)
	{
		if (iDotCount > 1)
			return false;
		if (str[i] == '.')
			iDotCount++;
		else if(str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

int code_convert(const char *from_charset,const char *to_charset,const char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
	iconv_t cd;
	const char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset,from_charset);
	if (cd==0) return -1;
	memset(outbuf,0,outlen);
#ifdef _WIN32
	if (iconv(cd,(const char**)pin,&inlen,pout,&outlen)==-1) return -1;
#else
	if (iconv(cd,(char**)pin,&inlen,pout,&outlen)==-1) return -1;

#endif
	iconv_close(cd);
	return 0;

}

//UNICODE码转为GB2312码
int UNICODE2GB2312(const char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{

	return code_convert("UTF-8","GB2312",inbuf,inlen,outbuf,outlen);
}
//GB2312码转为UNICODE码
int GB23122UNICODE(const char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
	return code_convert("GB2312","UTF-8",inbuf,inlen,outbuf,outlen);
}

int UNICODE2ASCII(const char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
	return code_convert("UTF-8","ARMSCII-8",inbuf,inlen,outbuf,outlen);
}



bool	IsFloat(const char* num)
{
	for(unsigned int i=0;i<strlen(num);i++)
	{
		if((num[i] >= '0' && num[i] <= '9') || num[i] == '.')
		{
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool IsDtmfChar(const char c)
{
	if(c >= '0' && c <= '9' && (c == '*' || c == '#'))
		return true;
	else
		return false;
}

const char* TimeToStr( char* pStr,time_t t )
{
	if (0 == t)
	{
		//strcpy(pStr,"NULL");
		strcpy(pStr, "");

	}
	else if(0xffffffff == t)
	{
		strcpy(pStr, "infinite");
	}
	else
	{
		tm *tm_now = localtime(&t);

		if(NULL == tm_now)
		{
			strcpy(pStr, "0000-00-00 00:00:00");
		}
		else
		{
			sprintf(pStr, "%d-%02d-%02d %02d:%02d:%02d",

				tm_now->tm_year + 1900,
				tm_now->tm_mon + 1,
				tm_now->tm_mday,
				tm_now->tm_hour,
				tm_now->tm_min,
				tm_now->tm_sec);
		}

	}
	
	return pStr;
}
