#ifndef _MYTIME_H_
#define _MYTIME_H_

#include <time.h>
#include <stdio.h>
#include <string.h>


#ifdef WIN32  

#define WIN32_LEAN_AND_MEAN
#include "kfpc_linuxwinapi.h"
#define	Millisecond_t	SYSTEMTIME

#else

#include  <sys/time.h>
#define	Millisecond_t	struct timeval

#endif


class KFPC_Time
{

public:	
	Millisecond_t	m_Time;

	KFPC_Time(void);
	KFPC_Time(KFPC_Time& val);
	KFPC_Time(time_t val);
	~KFPC_Time(void);
	void SecondTimeToStr(char* pTimeStr);
	void GetMillisecondToStr(char* pTimeStr, const char* pFormatStr = "%04d-%02d-%02d %02d:%02d:%02d.%03d");

	long long	operator-(KFPC_Time& val);
	bool operator==(KFPC_Time& val);
	bool operator<(KFPC_Time& val);
	bool operator>(KFPC_Time& val);
	bool operator<=(KFPC_Time& val);
	bool operator>=(KFPC_Time& val);
	bool operator!=(KFPC_Time& val);
	KFPC_Time& operator=(KFPC_Time* val);
	long long	TimeToMilliseconds(Millisecond_t& val);
	
	long long GetMilliseconds();
	unsigned long GetMillisecondsParty();
	#ifdef WIN32
	void TimetToSystemTime( time_t t, LPSYSTEMTIME pst );
	void SystemTimeToTimet( SYSTEMTIME& st, time_t *pt );
	#endif

	Millisecond_t&	GetNowTime(void);

	void ToZero();
	time_t	GetTime();

	bool IsZero();
};
#endif

