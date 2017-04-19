#ifndef KFPC_StringUtils_h__
#define KFPC_StringUtils_h__
#include <time.h>


// ����:ɾ�����ָ���ַ�
// str:Ҫ������ַ���
// c:Ҫɾ�����ַ�
// ����ֵ:��
void LTrim(char* str,const char c);

// ����:ɾ���ұ�ָ���ַ�
// str:Ҫ������ַ���
// c:Ҫɾ�����ַ�
// ����ֵ:��
void RTrim(char* str,const char c);

// ����:ɾ������ָ���ַ�
// str:Ҫ������ַ���
// c:Ҫɾ�����ַ�
// ����ֵ:��
void Trim(char *str,const char c);

// ����:���ַ������ϵ��ַ����µ��ַ������滻
// str:Ҫ������ַ���
// oldChar:���ڲ��Ҳ������滻���ַ�
// newChar:�����滻���ַ�
// ����ֵ:��
void Replace(char *str,const char oldChar,const char newChar);
//void Replace(std::string *strResult,const char *source,const char cOldChar,const char *csNew);
// ����:�ж��ַ����Ƿ�������
// str:Ҫ������ַ���
// ����ֵ:����true��ʾ��������������
bool IsNumber(const char *str);

// ����:�ж��ַ����Ƿ��Ǵ����ŵ�����,��������ʱҲ��(������)
// str:Ҫ������ַ���
// ����ֵ:����true��ʾ�Ƿ��ŵ�������������
bool IsNumberSign(const char *str);

// ����:�ж��ַ����Ƿ�������(��������С����)
// str:Ҫ������ַ���
// ����ֵ:����true��ʾ��������������
bool IsDecimal(const char *str);

// ����:�ж��ַ����Ƿ��Ǵ����ŵ�����(��������С����),��������ʱҲ��(������)
// str:Ҫ������ַ���
// ����ֵ:����true��ʾ�Ƿ��ŵ�������������
bool IsDecimalSign(const char *str);

bool IsDtmfChar(const char c);
bool	IsFloat(const char* num);

//����ת��:��һ�ֱ���תΪ��һ�ֱ���
int code_convert(const char *from_charset,const char *to_charset,const char *inbuf,size_t inlen,char *outbuf,size_t outlen);
int UNICODE2GB2312(const char *inbuf,size_t inlen,char *outbuf,size_t outlen);
int UNICODE2ASCII(const char *inbuf,size_t inlen,char *outbuf,size_t outlen);
int GB23122UNICODE(const char *inbuf,size_t inlen,char *outbuf,size_t outlen);


const char* TimeToStr(char* pStr,time_t t);



#endif // KFPC_StringUtils_h__
