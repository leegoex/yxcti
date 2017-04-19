#ifndef KFPC_StringUtils_h__
#define KFPC_StringUtils_h__
#include <time.h>


// 功能:删除左边指定字符
// str:要处理的字符串
// c:要删除的字符
// 返回值:无
void LTrim(char* str,const char c);

// 功能:删除右边指定字符
// str:要处理的字符串
// c:要删除的字符
// 返回值:无
void RTrim(char* str,const char c);

// 功能:删除两端指定字符
// str:要处理的字符串
// c:要删除的字符
// 返回值:无
void Trim(char *str,const char c);

// 功能:将字符串中老的字符用新的字符进行替换
// str:要处理的字符串
// oldChar:用于查找并将被替换的字符
// newChar:用于替换的字符
// 返回值:无
void Replace(char *str,const char oldChar,const char newChar);
//void Replace(std::string *strResult,const char *source,const char cOldChar,const char *csNew);
// 功能:判断字符串是否是整数
// str:要处理的字符串
// 返回值:返回true表示是整数，否则不是
bool IsNumber(const char *str);

// 功能:判断字符串是否是带符号的整数,不带符号时也可(即正数)
// str:要处理的字符串
// 返回值:返回true表示是符号的整数，否则不是
bool IsNumberSign(const char *str);

// 功能:判断字符串是否是数字(即可以有小数点)
// str:要处理的字符串
// 返回值:返回true表示是整数，否则不是
bool IsDecimal(const char *str);

// 功能:判断字符串是否是带符号的数字(即可以有小数点),不带符号时也可(即正数)
// str:要处理的字符串
// 返回值:返回true表示是符号的整数，否则不是
bool IsDecimalSign(const char *str);

bool IsDtmfChar(const char c);
bool	IsFloat(const char* num);

//代码转换:从一种编码转为另一种编码
int code_convert(const char *from_charset,const char *to_charset,const char *inbuf,size_t inlen,char *outbuf,size_t outlen);
int UNICODE2GB2312(const char *inbuf,size_t inlen,char *outbuf,size_t outlen);
int UNICODE2ASCII(const char *inbuf,size_t inlen,char *outbuf,size_t outlen);
int GB23122UNICODE(const char *inbuf,size_t inlen,char *outbuf,size_t outlen);


const char* TimeToStr(char* pStr,time_t t);



#endif // KFPC_StringUtils_h__
