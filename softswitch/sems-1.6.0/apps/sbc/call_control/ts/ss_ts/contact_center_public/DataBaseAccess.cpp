// DataBaseAccess.cpp: implementation of the CDataBaseAccess class.
//
//////////////////////////////////////////////////////////////////////

#include "kfpc_logex.h"
#include "DataBaseAccess.h"


#include <stdlib.h>
#include <malloc.h>

#include "apr_general.h"
#include "KFPC_StringUtils.h"

bool				g_DB_Debug = false;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRecordList::CRecordList(void)
{
	m_Eof = false;
	m_Bof = false;
}

void CRecordList::operator=(const CRecordList& RL)
{
	Copy(RL);
}

CRecordList::CRecordList(const CRecordList& RL)
{
	Copy(RL);

}
void CRecordList::Copy(const CRecordList& RL)
{
	if(this == &RL)	return ;

	this->m_Eof = RL.m_Bof;
	this->m_Bof = RL.m_Bof;
	m_RecordList_Iter = RL.m_RecordList_Iter;


	this->m_RecordList.clear();
	
	for( Const_RecordList_Iter_t	Iter = RL.m_RecordList.begin();
		Iter != RL.m_RecordList.end();Iter++)
	{
		const unsigned char* pBuf = (*Iter);
		size_t BufSize = _msize((void*)pBuf);
		unsigned char* pNewBuf = NULL;
		smart_new(unsigned char[BufSize],pNewBuf) ;
		memcpy(pNewBuf,pBuf,BufSize);
		this->m_RecordList.push_back(pNewBuf);
	}


	this->m_ColInfoVector.clear();
	for(Const_ColInfoVector_Iter_t	ColIter = RL.m_ColInfoVector.begin();
		ColIter != RL.m_ColInfoVector.end();ColIter++)
	{	
		this->m_ColInfoVector.push_back(*ColIter);
	}
}

CRecordList::~CRecordList(void)
{
	unsigned char * pBuf = NULL;
	RecordList_Iter_t	Iter;
	for(Iter=m_RecordList.begin();Iter != m_RecordList.end();Iter++)
	{
		pBuf = *Iter;
		smart_delete([]pBuf);
	}
}
void CRecordList::AddColInfo(int Index,ColInfo_t&	ColInfo)
{
	m_ColInfoVector.push_back(ColInfo);	
}

ColInfo_t* CRecordList::GetColInfo(int Index)
{
	return &m_ColInfoVector[Index];
}

void CRecordList::AddRecord(unsigned char* Buf)
{
	
	m_RecordList.push_back(Buf);
	m_RecordList_Iter = m_RecordList.begin();
}

bool CRecordList::MoveFirst(void)
{
	if(m_RecordList.empty())
	{
		return false;
	}
	else
	{
		m_Eof = false;
		m_Bof = false;
		m_RecordList_Iter = m_RecordList.begin();
		return true;
	}
}

bool CRecordList::MoveLast(void)
{	
	if(m_RecordList.empty())
	{
		return false;
	}
	else
	{
		m_Eof = false;
		m_Bof = false;
		m_RecordList_Iter = m_RecordList.end();
		m_RecordList_Iter--;
	}
	return true;
}

bool CRecordList::MoveNext(void)
{
	if(m_RecordList.empty())
	{
		return false;
	}
	else
	{		
		if(m_RecordList.end() != m_RecordList_Iter)
		{
			m_RecordList_Iter++;

			if(m_RecordList_Iter == m_RecordList.end())
			{
				m_Eof = true;
			}

			m_Bof = false;
			return true;
		}
		else
		{			
			return false;
		}
	}
}

bool CRecordList::MovePrev(void)
{
	if(m_RecordList.empty())
	{
		return false;
	}
	else
	{		
		if(m_RecordList.begin() != m_RecordList_Iter)
		{
			m_Eof = false;
			m_RecordList_Iter--;
			return true;
		}
		else
		{
			m_Bof = true;
			return false;
		}
	}
}

bool CRecordList::GetEof() 
{
	if(m_RecordList.empty())
	{
		return true;
	}

	return m_Eof;
}

bool CRecordList::GetBof() 
{
	if(m_RecordList.empty())
	{
		return true;
	}

	return m_Bof;
}

ColInfo_t* CRecordList::GetFieldByName(const char* pFieldName)
{
	for(unsigned int i=0;i<m_ColInfoVector.size();i++)
	{
		if(strcasecmp((char*)m_ColInfoVector[i].ColumnName,pFieldName) == 0)
		{
			return &m_ColInfoVector[i];
		}
	}

	return NULL;
}

bool	CRecordList::GetFieldAsString(const char* pFieldName,string& value)
{
	char*	pBuf = NULL;

	ColInfo_t* pColInfo = GetFieldByName(pFieldName);

	if(pColInfo != NULL)
	{
		switch(pColInfo->SqlDataType)
		{
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR:
		case SQL_DECIMAL:
			{
				pBuf = (char*)(*m_RecordList_Iter);
				value = &pBuf[pColInfo->FieldPos];
				return true;
			}
			break;
		case SQL_WCHAR:
		case SQL_WVARCHAR:
		case SQL_WLONGVARCHAR:		
			{
				pBuf = (char*)(*m_RecordList_Iter);
				value = &pBuf[pColInfo->FieldPos];
				return true;

				
				//char* pstr = smart_new(char[pColInfo->FieldSize*2]);				
				//char pstr [1000];
				//pBuf = (char*)(*m_RecordList_Iter);				
				//u2g(&pBuf[pColInfo->FieldPos],pColInfo->FieldSize,pstr,pColInfo->FieldSize*2);
				//value = pstr;

				//smart_delete([]pstr);

				return true;
			}
			break;
		default:
			{
				return false;
			}
		}
	}
	else
	{
		WARNING_LOG(0,"field find not:[%s] error.",pFieldName);
		return false;
	}
}

short int	CRecordList::GetFieldAsShort(const char* pFieldName)
{
	unsigned char*	pBuf = NULL;
	short int	ret;

	ColInfo_t* pColInfo = GetFieldByName(pFieldName);

	if(pColInfo != NULL)
	{
		switch(pColInfo->SqlDataType)
		{
		case SQL_INTEGER:
			{
				long int ret2;
				pBuf = (*m_RecordList_Iter);
				memmove(&ret2,&pBuf[pColInfo->FieldPos],sizeof(ret2));
				return ( short)ret2;
			}
			break;
		case SQL_SMALLINT:
			{
				pBuf = (*m_RecordList_Iter);
				memmove(&ret,&pBuf[pColInfo->FieldPos],sizeof(short int));
				return ret;
			}
			break;
		case SQL_BIGINT:
			{
				long long ret2 = 0;

				pBuf = (*m_RecordList_Iter);
				memmove(&ret2,&pBuf[pColInfo->FieldPos],sizeof(ret2));
				return (short)ret2;
			}
			break;
		case SQL_DECIMAL:
			{
				char* pchar = (char*)(*m_RecordList_Iter);
				string str = &pchar[pColInfo->FieldPos];
				
				if(IsNumber(str.c_str()))
				{
					unsigned int	ret2=atoi(str.c_str());
					return ret2;
				}
				else if(IsFloat(str.c_str()))
				{
					double ret2=atof(str.c_str());
					return (unsigned short)ret2;
				}
				else
				{
					WARNING_LOG(0,"GetFieldAsShort SQL_DECIMAL type string is not short[%s].",str.c_str());
					return 0;
				}
			}
			break;
		case SQL_FLOAT:
		case SQL_DOUBLE:
			{
				double	ret2=0;
				pBuf = (*m_RecordList_Iter);
				memmove(&ret2,&pBuf[pColInfo->FieldPos],sizeof(ret2));

				ret = (unsigned short)ret2;
				return ret;
			}
			break;
		default:
			{
				WARNING_LOG(0,"field:%s,SqlDataType:%d error.",pFieldName,pColInfo->SqlDataType);
				return 0;
			}
		}
	}
	else
	{
		WARNING_LOG(0,"field find not:[%s] error.",pFieldName);
		return 0;
	}
}


long int	CRecordList::GetFieldAsLongint(const char* pFieldName)
{
	unsigned char*	pBuf = NULL;
	long int	ret;

	ColInfo_t* pColInfo = GetFieldByName(pFieldName);

	if(pColInfo != NULL)
	{
		switch(pColInfo->SqlDataType)
		{
		case SQL_INTEGER:
			{
				pBuf = (*m_RecordList_Iter);
				memmove(&ret,&pBuf[pColInfo->FieldPos],sizeof(long int));
				return ret;
			}
			break;
		case SQL_BIGINT:
			{
				long long ret2 = 0;

				pBuf = (*m_RecordList_Iter);
				memmove(&ret2,&pBuf[pColInfo->FieldPos],sizeof(ret2));
				return (long int)ret2;
			}
			break;
		case SQL_SMALLINT:
			{
				short int ret2 = 0;
				pBuf = (*m_RecordList_Iter);
				memmove(&ret2,&pBuf[pColInfo->FieldPos],sizeof(ret2));
				return ret2;
			}
			break;
		case SQL_DECIMAL:
			{
				char* pchar = (char*)(*m_RecordList_Iter);
				string str = &pchar[pColInfo->FieldPos];
				
				if(IsNumber(str.c_str()))
				{
					unsigned int	ret2=atoi(str.c_str());
					return ret2;
				}
				else if(IsFloat(str.c_str()))
				{
					double ret2=atof(str.c_str());
					return (long int)ret2;
				}
				else
				{
					WARNING_LOG(0,"GetFieldAsLongint SQL_DECIMAL type string is not number[%s].",str.c_str());
					return 0;
				}
			}
			break;
		case SQL_FLOAT:
		case SQL_DOUBLE:
			{
				double	ret2=0;
				pBuf = (*m_RecordList_Iter);
				memmove(&ret2,&pBuf[pColInfo->FieldPos],sizeof(ret2));

				ret = (long int)ret2;
				return ret;
			}
			break;
		default:
			{
				WARNING_LOG(0,"field:%s, SqlDataType:%d error.",pFieldName,pColInfo->SqlDataType);
				return 0;
			}
		}
	}
	else
	{
		WARNING_LOG(0, "field find not:[%s] error.",pFieldName);
		return 0;
	}
}

float	CRecordList::GetFieldAsReal(const char* pFieldName)
{
	unsigned char*	pBuf = NULL;
	float	ret=0;

	ColInfo_t* pColInfo = GetFieldByName(pFieldName);

	if(pColInfo != NULL)
	{
		switch(pColInfo->SqlDataType)
		{
		case SQL_REAL:
			{
				pBuf = (*m_RecordList_Iter);
				memmove(&ret,&pBuf[pColInfo->FieldPos],sizeof(ret));
				return ret;
			}
			break;
		case SQL_FLOAT:
		case SQL_DOUBLE:
			{
				double	ret2=0;
				pBuf = (*m_RecordList_Iter);
				memmove(&ret2,&pBuf[pColInfo->FieldPos],sizeof(ret2));

				ret = (float)ret2;
				return ret;
			}
			break;
		case SQL_DECIMAL:
		case SQL_VARCHAR:
			{
				char* pChar = (char*)(*m_RecordList_Iter);
				string str = &pChar[pColInfo->FieldPos];
				
				if(IsFloat(str.c_str()))
				{
					double	ret2=atof(str.c_str());
					return (float)ret2;
				}
				else if(IsNumber(str.c_str()))
				{
					unsigned int	ret2=atoi(str.c_str());
					return (float)ret2;
				}
				else
				{
					WARNING_LOG(0,"GetFieldAsLongint SQL_DECIMAL type string is not float[%s].",str.c_str());
					return 0;
				}
			}
			break;

		default:
			{
				WARNING_LOG(0,"field:%s,SqlDataType:%d error.",pFieldName,pColInfo->SqlDataType);
				return 0;
			}
		}
	}
	else
	{
		WARNING_LOG(0,"field find not:[%s] error.",pFieldName);
		return 0;
	}
}

double	CRecordList::GetFieldAsdouble(const char* pFieldName)
{
	unsigned char*	pBuf = NULL;
	double	ret=0;

	ColInfo_t* pColInfo = GetFieldByName(pFieldName);

	if(pColInfo != NULL)
	{
		switch(pColInfo->SqlDataType)
		{
		case SQL_FLOAT:
		case SQL_DOUBLE:
			{
				pBuf = (*m_RecordList_Iter);
				memmove(&ret,&pBuf[pColInfo->FieldPos],sizeof(ret));
				return ret;
			}
			break;
		case SQL_REAL:
			{
				float ret2 = 0;
				pBuf = (*m_RecordList_Iter);
				memmove(&ret2,&pBuf[pColInfo->FieldPos],sizeof(ret2));
				return ret2;
			}
			break;
		case SQL_DECIMAL:
			{
				char* pchar = (char*)(*m_RecordList_Iter);
				string str = &pchar[pColInfo->FieldPos];
				
				if(IsFloat(str.c_str()))
				{
					double	ret2=atof(str.c_str());
					return ret2;
				}
				else if(IsNumber(str.c_str()))
				{
					unsigned int	ret2=atoi(str.c_str());
					return ret2;
				}
				else
				{
					WARNING_LOG(0,"GetFieldAsLongint SQL_DECIMAL type string is not float[%s].",str.c_str());
					return 0;
				}
			}
			break;
		default:
			{
				WARNING_LOG(0,"field:%s,SqlDataType:%d error.",pFieldName,pColInfo->SqlDataType);
				return 0;
			}
		}
	}
	else
	{
		WARNING_LOG(0,"field find not:[%s] error.",pFieldName);
		return 0;
	}
}

bool	CRecordList::GetFieldAsBinary		(const char* pFieldName,unsigned char* pBinBuf,unsigned long* Size)
{
	unsigned char*	pBuf = NULL;
	unsigned long	DataLen = 0;
	ColInfo_t* pColInfo = GetFieldByName(pFieldName);

	if(pColInfo != NULL)
	{
		switch(pColInfo->SqlDataType)
		{
		case SQL_BINARY:
		case SQL_VARBINARY:
		case SQL_LONGVARBINARY:
			{
				pBuf = (*m_RecordList_Iter);
				DataLen = min(*Size,pColInfo->ColumnSize);
				memmove(pBinBuf,&pBuf[pColInfo->FieldPos],DataLen);
				*Size = DataLen;
				return true;
			}
			break;
		default:
			{
				WARNING_LOG(0,"field:%s,SqlDataType:%d error.",pFieldName,pColInfo->SqlDataType);
				return false;
			}
		}
	}
	else
	{
		WARNING_LOG(0,"field find not:[%s] error.",pFieldName);
		return false;
	}
}

char	CRecordList::GetFieldAsTinyint(const char* pFieldName)
{
	unsigned char*	pBuf = NULL;
	char			Ret = 0;

	ColInfo_t* pColInfo = GetFieldByName(pFieldName);

	if(pColInfo != NULL)
	{
		switch(pColInfo->SqlDataType)
		{
		case SQL_TINYINT:
			{
				pBuf = (*m_RecordList_Iter);
				return pBuf[pColInfo->FieldPos];
			}
			break;
		default:
			{
				WARNING_LOG(0,"field:%s,SqlDataType:%d error.",pFieldName,pColInfo->SqlDataType);
				return 0;
			}
		}
	}
	else
	{
		WARNING_LOG(0,"field find not:[%s] error.",pFieldName);
		return 0;
	}
}

long long	CRecordList::GetFieldAsBigint(const char* pFieldName)
{
	unsigned char*	pBuf = NULL;
	long long			Ret = 0;

	ColInfo_t* pColInfo = GetFieldByName(pFieldName);

	if(pColInfo != NULL)
	{
		switch(pColInfo->SqlDataType)
		{
		case SQL_INTEGER:
			{
				long int ret2;
				pBuf = (*m_RecordList_Iter);
				memmove(&ret2,&pBuf[pColInfo->FieldPos],sizeof(ret2));
				return ret2;
			}
			break;

		case SQL_BIGINT:
			{
				pBuf = (*m_RecordList_Iter);
				memmove(&Ret,&pBuf[pColInfo->FieldPos],sizeof(long long));
				return Ret;
			}
			break;
		case SQL_SMALLINT:
			{
				short int ret2 = 0;
				pBuf = (*m_RecordList_Iter);
				memmove(&ret2,&pBuf[pColInfo->FieldPos],sizeof(ret2));
				return ret2;
			}
			break;
		case SQL_DECIMAL:
			{
				char* pchar = (char*)(*m_RecordList_Iter);
				string str = &pchar[pColInfo->FieldPos];
				
				if(IsNumber(str.c_str()))
				{
					long long	ret2=atoi(str.c_str());
					return ret2;
				}
				else if(IsFloat(str.c_str()))
				{
					long long ret2=(long long)atof(str.c_str());
					return (unsigned short)ret2;
				}
				else
				{
					WARNING_LOG(0,"GetFieldAsBigint SQL_DECIMAL type string is not short[%s].",str.c_str());
					return 0;
				}
			}
			break;
		default:
			{
				WARNING_LOG(0,"field:%s,SqlDataType:%d error.",pFieldName,pColInfo->SqlDataType);
				return 0;
			}
		}
	}
	else
	{
		WARNING_LOG(0,"field find not:[%s] error.",pFieldName);
		return 0;
	}
}


bool	CRecordList::GetFieldAsDate			(const char* pFieldName,DATE_STRUCT& value)
{
	unsigned char*	pBuf = NULL;

	ColInfo_t* pColInfo = GetFieldByName(pFieldName);

	if(pColInfo != NULL)
	{
		switch(pColInfo->SqlDataType)
		{
		case SQL_DATE:
		case SQL_TYPE_DATE:
			{
				pBuf = (*m_RecordList_Iter);
				memmove(&value,&pBuf[pColInfo->FieldPos],sizeof(value));
				return true;
			}
			break;
		default:
			{
				WARNING_LOG(0,"field:%s,SqlDataType:%d error.",pFieldName,pColInfo->SqlDataType);
				return false;
			}
		}
	}
	else
	{
		WARNING_LOG(0,"field find not:[%s] error.",pFieldName);
		return false;
	}
}

bool	CRecordList::GetFieldAsTime			(const char* pFieldName,TIME_STRUCT& value)
{
	unsigned char*	pBuf = NULL;

	ColInfo_t* pColInfo = GetFieldByName(pFieldName);

	if(pColInfo != NULL)
	{
		switch(pColInfo->SqlDataType)
		{
		case SQL_TIME:
		case SQL_TYPE_TIME:
			{
				pBuf = (*m_RecordList_Iter);
				memmove(&value,&pBuf[pColInfo->FieldPos],sizeof(value));
				return true;
			}
			break;
		default:
			{
				WARNING_LOG(0,"field:%s, SqlDataType:%d error.",pFieldName,pColInfo->SqlDataType);
				return false;
			}
		}
	}
	else
	{
		WARNING_LOG(0,"field find not:[%s] error.",pFieldName);
		return false;
	}
}

time_t CRecordList::GetFieldAsTime( const char* pFieldName )
{
	unsigned char*	pBuf = NULL;

	ColInfo_t* pColInfo = GetFieldByName(pFieldName);

	struct tm tm;
	memset(&tm,0,sizeof(tm));

	if(pColInfo != NULL)
	{
		switch(pColInfo->SqlDataType)
		{

		case SQL_TIMESTAMP:
		case SQL_TYPE_TIMESTAMP:
			{
				pBuf = (*m_RecordList_Iter);

				TIMESTAMP_STRUCT *	ts = (TIMESTAMP_STRUCT *)&pBuf[pColInfo->FieldPos];

				

				tm.tm_year	= ts->year-1900;
				tm.tm_mon	= ts->month - 1;
				tm.tm_mday	= ts->day;
				tm.tm_hour	= ts->hour;
				tm.tm_min	= ts->minute;
				tm.tm_sec	= ts->second;

				//char	timeStr[128];

				//DEBUG_LOG(0,"FieldName:%s,SQL_C_TIMESTAMP: %d-%d-%d %d:%d:%d.%d,Time:%s",
				//	pColInfo->ColumnName,ts->year, ts->month,ts->day, ts->hour, ts->minute, ts->second, ts->fraction,TimeToStr(timeStr, mktime(&tm)));

				return mktime(&tm);

			}
			break;
		default:
			{
				WARNING_LOG(0,"field:%s, SqlDataType:%d error.",pFieldName,pColInfo->SqlDataType);
				return 0;
			}
		}
	}
	else
	{
		WARNING_LOG(0,"field find not:[%s] error.",pFieldName);
		return 0;
	}
}
bool	CRecordList::GetFieldAsTimestamp		(const char* pFieldName,TIMESTAMP_STRUCT& value)
{
	unsigned char*	pBuf = NULL;

	ColInfo_t* pColInfo = GetFieldByName(pFieldName);

	if(pColInfo != NULL)
	{
		switch(pColInfo->SqlDataType)
		{
		case SQL_TIMESTAMP:
		case SQL_TYPE_TIMESTAMP:
			{
				pBuf = (*m_RecordList_Iter);
				memmove(&value,&pBuf[pColInfo->FieldPos],sizeof(value));
				return true;
			}
			break;
		default:
			{
				WARNING_LOG(0,"field:%s, SqlDataType:%d error.",pFieldName,pColInfo->SqlDataType);
				return false;
			}
		}
	}
	else
	{
		WARNING_LOG(0,"field find not:[%s] error.",pFieldName);
		return false;
	}
}

bool	CRecordList::GetFieldAsNumeric		(const char* pFieldName,SQL_NUMERIC_STRUCT& value)
{
	unsigned char*	pBuf = NULL;

	ColInfo_t* pColInfo = GetFieldByName(pFieldName);

	if(pColInfo != NULL)
	{
		switch(pColInfo->SqlDataType)
		{
		case SQL_NUMERIC:
			{
				pBuf = (*m_RecordList_Iter);
				memmove(&value,&pBuf[pColInfo->FieldPos],sizeof(value));
				return true;
			}
			break;
		default:
			{
				WARNING_LOG(0,"field:%s, SqlDataType:%d error.",pFieldName,pColInfo->SqlDataType);
				return false;
			}
		}
	}
	else
	{
		WARNING_LOG(0,"field find not:[%s] error.",pFieldName);
		return false;
	}
}

bool	CRecordList::GetFieldAsIntervalStruct(const char* pFieldName,SQL_INTERVAL_STRUCT& value)
{
		unsigned char*	pBuf = NULL;

	ColInfo_t* pColInfo = GetFieldByName(pFieldName);

	if(pColInfo != NULL)
	{
		switch(pColInfo->SqlDataType)
		{
		case SQL_DATE:
		case SQL_INTERVAL_YEAR:
		case SQL_INTERVAL_MONTH:
		case SQL_INTERVAL_DAY:
		case SQL_INTERVAL_HOUR:
		case SQL_INTERVAL_MINUTE:
		case SQL_INTERVAL_SECOND:
		case SQL_INTERVAL_YEAR_TO_MONTH:
		case SQL_INTERVAL_DAY_TO_HOUR:
		case SQL_INTERVAL_DAY_TO_MINUTE:
		case SQL_INTERVAL_DAY_TO_SECOND:
		case SQL_INTERVAL_HOUR_TO_MINUTE:
		case SQL_INTERVAL_HOUR_TO_SECOND:
		case SQL_INTERVAL_MINUTE_TO_SECOND:
			{
				pBuf = (*m_RecordList_Iter);
				memmove(&value,&pBuf[pColInfo->FieldPos],sizeof(value));
				return true;
			}
			break;
		default:
			{
				WARNING_LOG(0,"field:%s,SqlDataType:%d error.",pFieldName,pColInfo->SqlDataType);
				return false;
			}
		}
	}
	else
	{
		WARNING_LOG(0,"field find not:[%s] error.",pFieldName);
		return false;
	}
}

size_t CRecordList::GetRecordCount(void)
{
	return m_RecordList.size();
}


CDataBaseAccess::CDataBaseAccess()
{
	memset(m_DataSource,0,DataSourceLen);
	memset(m_UserName,0,UserNameLen);
	memset(m_Password,0,PasswordLen);
	memset(m_SqlString,0,SqlStringLen);

	m_Henv = SQL_NULL_HENV;		
	m_Hdbc = SQL_NULL_HDBC;    
	m_Hstmt = SQL_NULL_HSTMT;	

}

CDataBaseAccess::~CDataBaseAccess()
{
	//INFO_LOG(0,"");
	CloseDataBase();
}

bool CDataBaseAccess::CloseDataBase(void)
{

	INFO_LOG(0,"");

	if(m_Hstmt != SQL_NULL_HSTMT)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_Hstmt);
	}

	if(m_Hdbc != SQL_NULL_HDBC)
	{
		SQLDisconnect(m_Hdbc);
		SQLFreeHandle(SQL_HANDLE_DBC, m_Hdbc);
	}

	if(m_Henv != SQL_NULL_HENV)
	{
		SQLFreeHandle(SQL_HANDLE_ENV, m_Henv);
	}

	m_Henv = SQL_NULL_HENV;		
	m_Hdbc = SQL_NULL_HDBC;    
	m_Hstmt = SQL_NULL_HSTMT;	

	return true;
}

bool CDataBaseAccess::InitDataBase(const char *DataSource,const char *UserName,const char *Password,bool reopen)
{

	INFO_LOG(0,"InitDataBase(DataSource:%s,UserName:%s,Password:%s)",DataSource,UserName,Password);
	SQLRETURN   Ret;

	if(!reopen)
	{
		SetDataSource(DataSource);
		SetUserName(UserName);
		SetPassword(Password);
	}

	Ret = SQLAllocHandle(SQL_HANDLE_ENV,NULL,&m_Henv);
	if (Ret!=SQL_SUCCESS && Ret!=SQL_SUCCESS_WITH_INFO) 
	{
		return false;
	}
	
	/* Set the ODBC version environment attribute */
	Ret = SQLSetEnvAttr(m_Henv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER); 
	if (Ret!=SQL_SUCCESS && Ret!=SQL_SUCCESS_WITH_INFO) 
	{
		WARNING_LOG(0,"InitDataBase Warning: set the environment attribute of odbc failed!");
		return false;
	}

	/* Allocate connection handle */
	Ret = SQLAllocHandle(SQL_HANDLE_DBC,m_Henv,&m_Hdbc); 
	if (Ret!=SQL_SUCCESS && Ret!=SQL_SUCCESS_WITH_INFO) 
	{
		SQLFreeHandle(SQL_HANDLE_ENV, m_Henv);
		m_Henv = SQL_NULL_HENV;
		return false;
	}

	/* Set login timeout to 5 seconds. */
    SQLSetConnectAttr(m_Hdbc,SQL_LOGIN_TIMEOUT,(void*)30,0);

	/* Connect to data source */
    Ret = SQLConnect(m_Hdbc,
				  (SQLCHAR*) DataSource, SQL_NTS,
                  (SQLCHAR*) UserName, SQL_NTS,
                  (SQLCHAR*) Password, SQL_NTS);

	if (Ret != SQL_SUCCESS && Ret != SQL_SUCCESS_WITH_INFO)
	{
		SQLCHAR			SqlState[6]					= "";
		SQLCHAR			Msg[SQL_MAX_MESSAGE_LENGTH] = "";
		SQLINTEGER		NativeError;
		SQLSMALLINT		MsgLen;

		SQLGetDiagRec(SQL_HANDLE_DBC, m_Hdbc, 1, SqlState, &NativeError,Msg, SQL_MAX_MESSAGE_LENGTH, &MsgLen);
		WARNING_LOG(0,"InitDataBase SQLConnect fail SqlState:%s,NativeError:%d, Msg:%s.",SqlState,NativeError,Msg);

		SQLFreeHandle(SQL_HANDLE_DBC, m_Hdbc);
		SQLFreeHandle(SQL_HANDLE_ENV, m_Henv);

		m_Henv = SQL_NULL_HENV;		
		m_Hdbc = SQL_NULL_HDBC;    

		return false;
	}

	/*
	Ret = SQLAllocHandle(SQL_HANDLE_STMT,m_Hdbc, &m_Hstmt); 
	if (Ret != SQL_SUCCESS && Ret != SQL_SUCCESS_WITH_INFO) 
	{
		DisplayStmtError("SQLAllocHandle");
		CloseDataBase();
		return false;			
	}

*/

	SQLINTEGER val  = 1;

	
	//SQLSetConnectAttr(m_Hdbc,SQL_ATTR_AUTOCOMMIT,&val,0);

	INFO_LOG(0,"InitDataBase success.");

	return true;
}
bool CDataBaseAccess::DBIsOpen(void)
{
	if(m_Henv != SQL_NULL_HENV && m_Hdbc != SQL_NULL_HDBC)
	{
		return true;
	}
	else
	{
		return false;
	}
	   
}


void CDataBaseAccess::SetDataSource(const char* pDataSource)
{
	strncpy(m_DataSource,pDataSource,DataSourceLen-1);
}

const char* CDataBaseAccess::GetDataSource(void)
{
	return m_DataSource;
}


void CDataBaseAccess::SetUserName(const char* pUserName)
{
	strncpy(m_UserName,pUserName,UserNameLen-1);
}

const char* CDataBaseAccess::GetUserName(void)
{
	return m_UserName;
}


void CDataBaseAccess::SetPassword(const char* pPassword)
{
	strncpy(m_Password,pPassword,PasswordLen-1);

}

const char* CDataBaseAccess::GetPassword(void)
{
	return m_Password;
}

bool CDataBaseAccess::QueryData(const char* SqlStr,CRecordList* pRecordList,bool Log)
{
	SQLRETURN		Ret =		SQL_SUCCESS;
	SQLSMALLINT		ColCount =	0;	
	unsigned long	ToTalFieldLen = 0;
	SQLCHAR*		FieldBuf = NULL;
	SQLINTEGER		StrLen = 0;
	SQLSMALLINT		C_DataType = 0;
	SQLSMALLINT		BufferLength		= ColumnNameBufSize;
	unsigned long	RecordCount = 0;

	if(Log)
	{
		INFO_LOG(0,"QueryData SqlStr:[%s].",SqlStr);
	}

	if(! DBIsOpen())
	{
		if(!ReOpen())
		{	
			return false;
		}
	}


	if(m_Hstmt != SQL_NULL_HSTMT)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_Hstmt);
		m_Hstmt = SQL_NULL_HSTMT;	
	}


	Ret = SQLAllocHandle(SQL_HANDLE_STMT,m_Hdbc, &m_Hstmt); 
	if (Ret != SQL_SUCCESS && Ret != SQL_SUCCESS_WITH_INFO) 
	{
		DisplayStmtError("SQLAllocHandle");
		CloseDataBase();
		return false;			
	}


	Ret = SQLPrepare(m_Hstmt,(SQLTCHAR *)SqlStr, SQL_NTS);
	if(Ret!=SQL_SUCCESS && Ret!=SQL_SUCCESS_WITH_INFO)
	{
		DisplayStmtError("SQLPrepare");
		CloseDataBase();
		return false;
	}

	Ret = SQLNumResultCols(m_Hstmt,&ColCount);
	if(Ret!=SQL_SUCCESS && Ret!=SQL_SUCCESS_WITH_INFO)
	{
		DisplayStmtError("SQLNumResultCols");
		CloseDataBase();
		return false;
	}

	if(ColCount != 0)
	{	
		for(int i=1;i<=ColCount;i++)
		{
			ColInfo_t		ColInf;

			Ret = SQLDescribeCol(m_Hstmt,i,
								ColInf.ColumnName,
								BufferLength,
								&ColInf.NameLength,
								&ColInf.SqlDataType,
								&ColInf.ColumnSize,
								&ColInf.DecimalDigits,
								&ColInf.Nullable);
			if(Ret==SQL_SUCCESS)
			{
				const char* pTypeStr = DataTypeToStr(ColInf.SqlDataType,ColInf.ColumnSize,&ColInf.FieldSize,&ColInf.C_DataType);

				if(g_DB_Debug)
				{
					DEBUG_LOG(0,"ColumnName:\"%s\",NameLength:%d,SqlDataType:%d(%s),ColumnSize:%d,FieldSize:%d,DecimalDigitsPtr:%d,NullablePtr:%d,C_DataType:%d.",
						ColInf.ColumnName,
						ColInf.NameLength	,					
						ColInf.SqlDataType,pTypeStr,
						ColInf.ColumnSize,ColInf.FieldSize,
						ColInf.DecimalDigits,
						ColInf.Nullable,
						ColInf.C_DataType);
				}

				ColInf.FieldPos=ToTalFieldLen;
				pRecordList->AddColInfo(i-1,ColInf);
				ToTalFieldLen+=ColInf.FieldSize;
			}
			else
			{
				DisplayStmtError("SQLDescribeCol");
				CloseDataBase();				
				return false;
			}
			
		}
	}	

	Ret = SQLExecute(m_Hstmt);
	if(Ret!=SQL_SUCCESS && Ret!=SQL_SUCCESS_WITH_INFO)
	{
		WARNING_LOG(0,"QueryData SqlStr:[%s].",SqlStr);
		DisplayStmtError("SQLExecute");
		CloseDataBase();				
		return false;
	}
	else
	{
		while(true)
		{
			Ret = SQLFetch(m_Hstmt) ;
			
			if (Ret == SQL_SUCCESS || Ret == SQL_SUCCESS_WITH_INFO)
			{
				//分配空间
				smart_new(SQLCHAR[ToTalFieldLen],FieldBuf);
				memset(FieldBuf,0,sizeof(SQLCHAR)*ToTalFieldLen);
				for(int i=0;i<ColCount;i++)
				{
					ColInfo_t* pColInfo = pRecordList->GetColInfo(i);

					

					Ret = SQLGetData(m_Hstmt,i+1, pColInfo->C_DataType, FieldBuf+pColInfo->FieldPos, pColInfo->FieldSize,&StrLen);	
					//g_log.Debug("C_DataType:%d,Ret:%d.",pColInfo->C_DataType,Ret);			
					//FieldBuf[pColInfo->FieldPos+StrLen] = '\0';		

					//if(SQL_TIMESTAMP == pColInfo->C_DataType ||
					//	 SQL_TYPE_TIMESTAMP  == pColInfo->C_DataType)
					//{
					//	TIMESTAMP_STRUCT* ts = (TIMESTAMP_STRUCT*)&FieldBuf[pColInfo->FieldPos];

					//	DEBUG_LOG(0,"FieldName:%s,SQL_C_TIMESTAMP: %d-%d-%d %d:%d:%d.%d",pColInfo->ColumnName,ts->year, ts->month,ts->day, ts->hour, ts->minute, ts->second, ts->fraction);
					//}
					

					if(Ret!=SQL_SUCCESS && Ret != SQL_SUCCESS_WITH_INFO)
					{
						WARNING_LOG(0,"QueryData SqlStr:[%s].",SqlStr);
						DisplayStmtError("SQLGetData");
						CloseDataBase();
						return false;	
					}
				}
         
				pRecordList->AddRecord(FieldBuf);
				RecordCount++;
			}
			else
			{
				break;
			}
		}
		if(Log)
		{
			INFO_LOG(0,"QueryData RecordCount:%d.",RecordCount);
		}
	}
	return true;
}

bool CDataBaseAccess::ExecuteSql(const char * SqlStr,bool Log)//主要用于执行播入，删除
{
	SQLRETURN		Ret =		SQL_SUCCESS;

	if(Log)
	{	
		INFO_LOG(0,"ExecuteSql SqlStr:[%s].",SqlStr);

	}

	if(! DBIsOpen())
	{
		if(!ReOpen())
		{	
			return false;
		}
	}

	if(m_Hstmt != SQL_NULL_HSTMT)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_Hstmt);
		m_Hstmt = SQL_NULL_HSTMT;	
	}


	Ret = SQLAllocHandle(SQL_HANDLE_STMT,m_Hdbc, &m_Hstmt); 
	if (Ret != SQL_SUCCESS && Ret != SQL_SUCCESS_WITH_INFO) 
	{
		INFO_LOG(0,"ExecuteSql SqlStr:[%s].",SqlStr);
		DisplayStmtError("SQLAllocHandle");
		CloseDataBase();
		return false;			
	}

	Ret = SQLExecDirect(m_Hstmt,(SQLCHAR*)SqlStr,(SQLINTEGER)strlen((char*)SqlStr));
	if(Ret==SQL_NO_DATA)
	{
		WARNING_LOG(0,"SQLExecDirect update or delete statement that does not affect any rows at the data source,SqlStr:[%s].",SqlStr);
		return true;
	}
	else if(	Ret!=SQL_SUCCESS && 
		Ret!=SQL_SUCCESS_WITH_INFO)
	{
		WARNING_LOG(0,"ExecuteSql SqlStr:[%s],Ret:%d.",SqlStr,Ret);
		unsigned int Ret = DisplayStmtError("SQLExecDirect");
		
		//if(Ret == 1189 ||
		//	Ret == 1190 ||
		//	Ret == 1191 ||
		//	Ret == 1053 )
		//{
			CloseDataBase();				
		//}
		
		return false;
	}
	else
	{
		return true;
	}

}

bool CDataBaseAccess::ReOpen(void)
{
	INFO_LOG(0,"");
	if(DBIsOpen())
	{
		CloseDataBase();	
	}

	//Sleep(1000);
	return InitDataBase(m_DataSource,m_UserName,m_Password,true);

}

unsigned int CDataBaseAccess::DisplayStmtError(const char* pstr)
{
	SQLCHAR			SqlState[6]					= "";
	SQLCHAR			Msg[SQL_MAX_MESSAGE_LENGTH] = "";
	SQLINTEGER		NativeError = 0;
	SQLSMALLINT		MsgLen = 0;

	SQLGetDiagRec(SQL_HANDLE_STMT, m_Hstmt, 1, SqlState, &NativeError,Msg,SQL_MAX_MESSAGE_LENGTH-1, &MsgLen);
	WARNING_LOG(0,"%s SqlState:%s,NativeError:%d, Msg:%s.",pstr,SqlState,NativeError,Msg);

	return NativeError;
}

const char* CDataBaseAccess::DataTypeToStr(int DataType,SQLUINTEGER	ColumnSize,unsigned long* DataTypeSize,SQLSMALLINT* c_datatype)
{
	switch(DataType)
	{
	case SQL_CHAR:
		{
			 (*DataTypeSize)=ColumnSize;
			 *c_datatype = SQL_C_CHAR;
			 return "SQL_CHAR";
		}break;
	case SQL_VARCHAR:
		{
			(*DataTypeSize)=ColumnSize;
			*c_datatype = SQL_C_CHAR;
			return "SQL_VARCHAR";
			
		}break;
	case SQL_LONGVARCHAR:
		{
			(*DataTypeSize)=ColumnSize;
			*c_datatype = SQL_C_CHAR;
			return "SQL_LONGVARCHAR";			
		}break;

	case SQL_WCHAR:
		{			
			(*DataTypeSize)=ColumnSize;
			*c_datatype = SQL_C_CHAR;
			return "SQL_WCHAR";
		}break;
	case SQL_WVARCHAR:
		{
			(*DataTypeSize)=ColumnSize;
			*c_datatype = SQL_C_CHAR;
			return "SQL_WVARCHAR";			
		}break;
	case SQL_WLONGVARCHAR:
		{
			(*DataTypeSize)=ColumnSize;
			*c_datatype = SQL_C_CHAR;
			return "SQL_WLONGVARCHAR";			
		}break;

	case SQL_DECIMAL:
		{
			(*DataTypeSize)=ColumnSize;
			*c_datatype = SQL_C_CHAR;
			return "SQL_DECIMAL";			
		}break;

	case SQL_NUMERIC:
		{			
			(*DataTypeSize)=ColumnSize;
			*c_datatype = SQL_C_CHAR;
			return "SQL_NUMERIC";
		}break;
	case SQL_SMALLINT:
		{			
			(*DataTypeSize)=sizeof(short int);
			*c_datatype = SQL_C_SSHORT;
			return "SQL_SMALLINT";
		}break;
	case SQL_INTEGER:
		{			
			(*DataTypeSize)=sizeof(long int);
			*c_datatype = SQL_C_SLONG;
			return "SQL_INTEGER";
		}break;

	case SQL_REAL:
		{			
			(*DataTypeSize)=sizeof(float);
			*c_datatype = SQL_C_FLOAT;
			return "SQL_REAL";
		}break;

	case SQL_FLOAT:
		{
			(*DataTypeSize)=sizeof(double);
			*c_datatype = SQL_C_DOUBLE;
			return "SQL_FLOAT";
		}break;
	case SQL_DOUBLE:
		{
			(*DataTypeSize)=sizeof(double);
			*c_datatype = SQL_C_DOUBLE;
			return "SQL_DOUBLE";
		}break;
	case SQL_BIT:
		{
			(*DataTypeSize)=sizeof(unsigned char);
			*c_datatype = SQL_C_BIT;
			return "SQL_BIT";
		}break;
	case SQL_TINYINT:
		{
			(*DataTypeSize)=sizeof(signed char);
			*c_datatype = SQL_C_STINYINT;
			return "SQL_TINYINT";
		}break;
	case SQL_BIGINT:
		{
			(*DataTypeSize)= sizeof(long long);
			*c_datatype = SQL_C_SBIGINT;
			return "SQL_BIGINT";
		}break;
	case SQL_BINARY:
		{
			(*DataTypeSize)=ColumnSize;
			*c_datatype = SQL_C_BINARY;
			return "SQL_BINARY";
		}break;
	case SQL_VARBINARY:
		{
			(*DataTypeSize)=ColumnSize;
			*c_datatype = SQL_C_BINARY;
			return "SQL_VARBINARY";
		}break;
	case SQL_LONGVARBINARY:
		{
			(*DataTypeSize)=ColumnSize;
			*c_datatype = SQL_C_BINARY;
			return "SQL_LONGVARBINARY";
		}break;
	case SQL_TYPE_DATE:
		{
			(*DataTypeSize)=sizeof(DATE_STRUCT);
			*c_datatype = SQL_C_TYPE_DATE;
			return "SQL_TYPE_DATE";
		}break;
	case SQL_TYPE_TIME:
		{
			(*DataTypeSize)=sizeof(TIME_STRUCT);
			*c_datatype = SQL_C_TYPE_TIME;
			return "SQL_TYPE_TIME";
		}break;
	case SQL_TYPE_TIMESTAMP:
		{
			(*DataTypeSize)=sizeof(SQL_TIMESTAMP_STRUCT);
			*c_datatype = SQL_C_TYPE_TIMESTAMP;
			return "SQL_TYPE_TIMESTAMP";
		}break;
	case SQL_INTERVAL_MONTH:
		{
			(*DataTypeSize)=sizeof(SQL_INTERVAL_STRUCT);
			*c_datatype = SQL_C_INTERVAL_MONTH;
			return "SQL_INTERVAL_MONTH";
		}break;
	case SQL_INTERVAL_YEAR:
		{	
			(*DataTypeSize)=sizeof(SQL_INTERVAL_STRUCT);
			*c_datatype = SQL_C_INTERVAL_YEAR;
			return "SQL_INTERVAL_YEAR";
		}break;
	case SQL_INTERVAL_YEAR_TO_MONTH:
		{
			(*DataTypeSize)=sizeof(SQL_INTERVAL_STRUCT);
			*c_datatype = SQL_C_INTERVAL_YEAR_TO_MONTH;
			return "SQL_INTERVAL_YEAR_TO_MONTH";
		}break;
	case SQL_INTERVAL_DAY:
		{
			(*DataTypeSize)=sizeof(SQL_INTERVAL_STRUCT);
			*c_datatype = SQL_C_INTERVAL_DAY;
			return "SQL_INTERVAL_DAY";
		}break;
	case SQL_INTERVAL_HOUR:
		{
			(*DataTypeSize)=sizeof(SQL_INTERVAL_STRUCT);
			*c_datatype = SQL_C_INTERVAL_HOUR;
			return "SQL_INTERVAL_HOUR";
		}break;
	case SQL_INTERVAL_MINUTE:
		{
			(*DataTypeSize)=sizeof(SQL_INTERVAL_STRUCT);
			*c_datatype = SQL_C_INTERVAL_MINUTE;
			return "SQL_INTERVAL_MINUTE";
		}break;
	case SQL_INTERVAL_SECOND:
		{
			(*DataTypeSize)=sizeof(SQL_INTERVAL_STRUCT);
			*c_datatype = SQL_C_INTERVAL_SECOND;
			return "SQL_INTERVAL_SECOND";
		}break;
	case SQL_INTERVAL_DAY_TO_HOUR:
		{
			(*DataTypeSize)=sizeof(SQL_INTERVAL_STRUCT);
			*c_datatype = SQL_C_INTERVAL_DAY_TO_HOUR;
			return "SQL_INTERVAL_DAY_TO_HOUR";
		}break;
	case SQL_INTERVAL_DAY_TO_MINUTE:
		{
			(*DataTypeSize)=sizeof(SQL_INTERVAL_STRUCT);
			*c_datatype = SQL_C_INTERVAL_DAY_TO_MINUTE;
			return "SQL_INTERVAL_DAY_TO_MINUTE";
		}break;
	case SQL_INTERVAL_DAY_TO_SECOND:
		{
			(*DataTypeSize)=sizeof(SQL_INTERVAL_STRUCT);
			*c_datatype = SQL_C_INTERVAL_DAY_TO_SECOND;
			return "SQL_INTERVAL_DAY_TO_SECOND";
		}break;
	case SQL_INTERVAL_HOUR_TO_MINUTE:
		{
			(*DataTypeSize)=sizeof(SQL_INTERVAL_STRUCT);
			*c_datatype = SQL_C_INTERVAL_HOUR_TO_MINUTE;
			return "SQL_INTERVAL_HOUR_TO_MINUTE";
		}break;
	case SQL_INTERVAL_HOUR_TO_SECOND:
		{
			(*DataTypeSize)=sizeof(SQL_INTERVAL_STRUCT);
			*c_datatype = SQL_C_INTERVAL_HOUR_TO_SECOND;
			return "SQL_INTERVAL_HOUR_TO_SECOND";
		}break;
	case SQL_INTERVAL_MINUTE_TO_SECOND:
		{
			(*DataTypeSize)=sizeof(SQL_INTERVAL_STRUCT);
			*c_datatype = SQL_C_INTERVAL_MINUTE_TO_SECOND;
			return "SQL_INTERVAL_MINUTE_TO_SECOND";
		}break;
	case SQL_GUID:
		{
			(*DataTypeSize)=sizeof(SQLGUID);
			 *c_datatype = SQL_C_CHAR;
			return "SQL_GUID";
		}break;
	default:{return "unknown";};
	}
}

