#pragma once
#include<string>
using namespace std;
#include <list>
#include "kfpc_linuxwinapi.h"
#include <sqlext.h>
#include <vector>
#include <string.h>
#include <time.h>

using namespace std;

const int DataSourceLen = 256;
const int UserNameLen	= 256;
const int PasswordLen	= 256;
const int SqlStringLen  = 4096;
const int ColumnNameBufSize = 256;

typedef struct ColInfo_
{
	SQLCHAR 		ColumnName[ColumnNameBufSize];
	SQLSMALLINT		NameLength;
	SQLSMALLINT		SqlDataType;
	SQLSMALLINT		C_DataType;
	SQLUINTEGER		ColumnSize;
	SQLSMALLINT		DecimalDigits;
	SQLSMALLINT		Nullable;
	unsigned long	FieldPos;
	unsigned long	FieldSize;
}ColInfo_t;

typedef vector<ColInfo_t> ColInfoVector_t;
typedef ColInfoVector_t::iterator ColInfoVector_Iter_t;
typedef ColInfoVector_t::const_iterator	Const_ColInfoVector_Iter_t;

typedef list<unsigned char*> RecordList_t;
typedef RecordList_t::iterator	RecordList_Iter_t;
typedef RecordList_t::const_iterator Const_RecordList_Iter_t;

class CRecordList
{
private:
	RecordList_t		m_RecordList;
	RecordList_Iter_t	m_RecordList_Iter;
	ColInfoVector_t		m_ColInfoVector;
	bool				m_Eof;
	bool				m_Bof;
public:
	CRecordList(void);
	CRecordList(const CRecordList& RL);
	~CRecordList(void);
	void AddColInfo(int Index,ColInfo_t&	ColInfo);
	ColInfo_t* GetColInfo(int Index);
	void AddRecord(unsigned char* Buf);	
	ColInfo_t* GetFieldByName(const char* pFieldName);
	void operator=(const CRecordList& RL);
	void Copy(const CRecordList& RL);
	bool					GetFieldAsString		(const char* pFieldName,string& value);
	short int				GetFieldAsShort			(const char* pFieldName);
	//unsigned short int		GetFieldAsUnsignedshort	(const char* fieldname);
	long int				GetFieldAsLongint		(const char* pFieldName);
	//unsigned long int		GetFieldAsUnsignedlongint(const char* fieldname);
	float					GetFieldAsReal			(const char* pFieldName);
	double					GetFieldAsdouble		(const char* pFieldName);
	bool					GetFieldAsBinary		(const char* pFieldName,unsigned char* pBuf,unsigned long* Size);
	char					GetFieldAsTinyint		(const char* pFieldName);
	long long					GetFieldAsBigint		(const char* pFieldName);
	bool					GetFieldAsDate			(const char* pFieldName,DATE_STRUCT& value);
	bool					GetFieldAsTime			(const char* pFieldName,TIME_STRUCT& value);
	bool					GetFieldAsTimestamp		(const char* pFieldName,TIMESTAMP_STRUCT& value);
	bool					GetFieldAsNumeric		(const char* pFieldName,SQL_NUMERIC_STRUCT& value);
	bool					GetFieldAsIntervalStruct(const char* pFieldName,SQL_INTERVAL_STRUCT& value);
	time_t					GetFieldAsTime			(const char* pFieldName);

	bool MoveFirst(void);
	bool MoveLast(void);
	bool MoveNext(void);
	bool MovePrev(void);
	size_t GetRecordCount(void);
	bool GetEof();// {return m_Eof;}
	bool GetBof();// {return m_Bof;}
};


class CDataBaseAccess  
{
private:
	char		m_DataSource[DataSourceLen];
	char		m_UserName[UserNameLen];
	char		m_Password[PasswordLen];
	SQLHENV     m_Henv;		
	SQLHDBC     m_Hdbc;    
	SQLHSTMT    m_Hstmt;	
	char		m_SqlString[SqlStringLen];
	//KFPC_Mutex	m_Mutex;

public:
	
	static CDataBaseAccess* GetInstance()
	{
		static CDataBaseAccess _inStance;
		return &_inStance;
	}

	CDataBaseAccess();
	virtual ~CDataBaseAccess();
	bool InitDataBase(const char *DataSource,const char *UserName,const char *Password,bool reopen=false);
	bool CloseDataBase(void);	

	void SetDataSource(const char* pDataSource);
	const char* GetDataSource(void);

	void SetUserName(const char* pUserName);
	const char* GetUserName(void);

	void SetPassword(const char* pPassword);
	const char* GetPassword(void);

	static void	TimeToFormatStr(TIMESTAMP_STRUCT	*ptime,char* str,int nFlag);
	static void StrToTime(char* str,TIMESTAMP_STRUCT *ptime);
	
	bool DBIsOpen(void);
	unsigned int DisplayStmtError(const char* pstr);

	bool ReOpen(void);

	bool QueryData(const char* SqlStr,CRecordList* pRecordList,bool Log=false);	//须要等待结果集,每一个呼叫最多8个结果集,结果集可重复使用
	bool ExecuteSql(const char* SqlStr,bool Log=false);//主要用于执行播入，删除
	const char* DataTypeToStr(int DataType,SQLUINTEGER	ColumnSizePtr,unsigned long* DataTypeSize,SQLSMALLINT* c_datatype);
};

#define GlobalDBAccess	CDataBaseAccess::GetInstance()