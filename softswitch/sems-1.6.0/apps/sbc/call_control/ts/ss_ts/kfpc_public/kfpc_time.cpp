
#include "kfpc_time.h"

#ifdef WIN32
#pragma warning (disable: 4996) 
#endif

KFPC_Time::KFPC_Time(void)
{
#ifndef WIN32 
	gettimeofday(&m_Time,NULL);
#else
	 GetLocalTime (&m_Time);
#endif
}

void KFPC_Time::ToZero()
{
	memset(&m_Time,0,sizeof(m_Time));
}

KFPC_Time::~KFPC_Time(void)
{
}

void KFPC_Time::SecondTimeToStr(char* pTimeStr)
{
#ifdef WIN32
	sprintf(pTimeStr,"%04d-%02d-%02d %02d:%02d:%02d",m_Time.wYear,
		m_Time.wMonth,
		m_Time.wDay ,
		m_Time.wHour,
		m_Time.wMinute,
		m_Time.wSecond);
#else

	if(m_Time.tv_sec == 0)
	{
		sprintf(pTimeStr,"%04d-%02d-%02d %02d:%02d:%02d",0,
			0,
			0 ,
			0,
			0,
			0);		
	}
	else
	{
		struct tm *newtime = localtime(&m_Time.tv_sec);

		sprintf(pTimeStr,"%04d-%02d-%02d %02d:%02d:%02d",newtime->tm_year+1900 ,
			newtime->tm_mon+1,
			newtime->tm_mday,
			newtime->tm_hour,
			newtime->tm_min,
			newtime->tm_sec);	
	}

#endif
}

#ifdef WIN32

void KFPC_Time::TimetToSystemTime( time_t t, SYSTEMTIME* pst )
{
   FILETIME ft;

   LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
   ft.dwLowDateTime = (DWORD) ll;
   ft.dwHighDateTime = (DWORD)(ll >> 32);

   FileTimeToSystemTime( &ft, pst );
}

void KFPC_Time::SystemTimeToTimet( SYSTEMTIME& st, time_t *pt )
{
   FILETIME ft;
   SystemTimeToFileTime( &st, &ft );

   LONGLONG ll;

   ULARGE_INTEGER ui;
   ui.LowPart = ft.dwLowDateTime;
   ui.HighPart = ft.dwHighDateTime;

   ll = (ft.dwHighDateTime << 32) + ft.dwLowDateTime;

   *pt = (DWORD)((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
}

#endif

long long  KFPC_Time::operator-(KFPC_Time& val)
{
	
#ifdef WIN32
	time_t	t1;
	time_t	t2;

	SystemTimeToTimet(m_Time,&t1);
	SystemTimeToTimet(val.m_Time,&t2);

	return (t1-t2)*1000+(m_Time.wMilliseconds-val.m_Time.wMilliseconds);

#else
	long long timeuse = 0;
	timeuse = 1000000 * ( m_Time.tv_sec - val.m_Time.tv_sec ) + m_Time.tv_usec - val.m_Time.tv_usec; 
	timeuse /= 1000;
	return timeuse;


#endif
}

bool KFPC_Time::operator==(KFPC_Time& val)
{
#ifdef WIN32 
	if( m_Time.wYear		== val.m_Time.wYear   && 
		m_Time.wMonth		== val.m_Time.wMonth &&
		m_Time.wDayOfWeek   == val.m_Time.wDayOfWeek &&
		m_Time.wDay			== val.m_Time.wDay &&
		m_Time.wHour		== val.m_Time.wHour &&
		m_Time.wMinute		== val.m_Time.wMinute &&
		m_Time.wSecond		== val.m_Time.wSecond &&
		m_Time.wMilliseconds == val.m_Time.wMilliseconds )
	{
		return true;
	}
	else
	{
		return false;
	}
#else

	if( m_Time.tv_sec == val.m_Time.tv_sec  && 
		m_Time.tv_usec == val.m_Time.tv_usec)
	{
		return true;
	}
	else
	{
		return false;
	}

#endif

}
long long	KFPC_Time::TimeToMilliseconds(Millisecond_t& val)
{

#ifdef WIN32 
	time_t	t;

	SystemTimeToTimet(val,&t);	
	return t*1000+val.wMilliseconds;



#else
	return  (val.tv_sec *1000000+val.tv_usec)/1000;
#endif	
}

bool KFPC_Time::operator<(KFPC_Time& val)
{

	if(TimeToMilliseconds(m_Time) < TimeToMilliseconds(val.m_Time))
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool KFPC_Time::operator>(KFPC_Time& val)
{
	if(TimeToMilliseconds(m_Time) > TimeToMilliseconds(val.m_Time))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool KFPC_Time::operator<=(KFPC_Time& val)
{
	if(TimeToMilliseconds(m_Time) <= TimeToMilliseconds(val.m_Time))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool KFPC_Time::operator>=(KFPC_Time& val)
{
	if(TimeToMilliseconds(m_Time) >= TimeToMilliseconds(val.m_Time))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool KFPC_Time::operator!=(KFPC_Time& val)
{
	if(TimeToMilliseconds(m_Time) != TimeToMilliseconds(val.m_Time))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Millisecond_t&	KFPC_Time::GetNowTime(void)
{
#ifdef WIN32 
	GetLocalTime (&m_Time);
#else
	gettimeofday(&m_Time,NULL);	 
#endif
	return m_Time;
}
KFPC_Time::KFPC_Time(KFPC_Time& val)
{
	m_Time = val.m_Time;
}

KFPC_Time::KFPC_Time( time_t val )
{
#ifdef WIN32 
	 
	TimetToSystemTime(val,&m_Time);	 

#else
	m_Time.tv_sec = val;
#endif
}


time_t	KFPC_Time::GetTime()
{
#ifdef WIN32
	time_t	t;
	SystemTimeToTimet(m_Time,&t);
	return t;	
#else
	return m_Time.tv_sec;		 	
#endif
}

long long KFPC_Time::GetMilliseconds()
{
#ifdef WIN32 
	
	time_t	t;

	SystemTimeToTimet(m_Time,&t);	
	return t*1000+m_Time.wMilliseconds;

#else

	return  (m_Time.tv_sec *1000000+m_Time.tv_usec)/1000;
#endif	

}

unsigned long KFPC_Time::GetMillisecondsParty()
{
#ifdef WIN32 

	return m_Time.wMilliseconds;

#else

	return  (m_Time.tv_usec)/1000;
#endif	

}

bool KFPC_Time::IsZero()
{
	Millisecond_t	tmp;
	memset(&tmp,0,sizeof(tmp));

	if(memcmp(&m_Time,&tmp,sizeof(m_Time)) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

KFPC_Time& KFPC_Time::operator=(KFPC_Time* val)
{
	
	m_Time = val->m_Time;
	return *this;
}

void KFPC_Time::GetMillisecondToStr( char* pTimeStr, const char* pFormatStr )
{
#ifdef WIN32

	sprintf(pTimeStr,pFormatStr,m_Time.wYear,
		m_Time.wMonth,
		m_Time.wDay ,
		m_Time.wHour,
		m_Time.wMinute,
		m_Time.wSecond,
		m_Time.wMilliseconds);

#else



	if(m_Time.tv_sec == 0)
	{
		sprintf(pTimeStr,pFormatStr,0,
			0,
			0 ,
			0,
			0,
			0,
			0);		
	}
	else
	{


		struct tm *newtime = localtime(&m_Time.tv_sec);

		sprintf(pTimeStr,pFormatStr,newtime->tm_year+1900 ,
			newtime->tm_mon+1,
			newtime->tm_mday,
			newtime->tm_hour,
			newtime->tm_min,
			newtime->tm_sec,
			m_Time.tv_usec/1000);	
	}

#endif
}

