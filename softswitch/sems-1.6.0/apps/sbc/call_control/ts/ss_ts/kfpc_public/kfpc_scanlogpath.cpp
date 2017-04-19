#include <iostream>
using namespace std;
#include "kfpc_scanlogpath.h"
#include "kfpc_log.h"
#include "kfpc_logex.h"
#include "kfpc_linuxwinapi.h"
#include "pcre++.h"


using namespace pcrepp;

KFPC_ScanLogPath::KFPC_ScanLogPath(KFPC_Log*	pLog,const char* FileNamePrefix,unsigned int MaxKeepFilesCount):
m_pLog(pLog),
m_MaxKeepFilesCount(MaxKeepFilesCount)
{
	m_FileNamePrefix = FileNamePrefix;

#ifdef WIN32
	sprintf(m_RegexStr,"%s/%s*.log.gz",m_pLog->GetLogPath(),m_FileNamePrefix.c_str());
#endif

#ifdef LINUX
	sprintf(m_RegexStr,"%s\\w*.log.gz$",m_FileNamePrefix.c_str());
#endif

	

}


KFPC_ScanLogPath::~KFPC_ScanLogPath(void)
{
}



void* KFPC_ScanLogPath::Svc()
{
	INFO_LOG(0,"RegexStr:%s.",m_RegexStr);

	ScanLogPath();
	DelOldFile();
	return NULL;
}

void KFPC_ScanLogPath::AddFileInfo( time_t CreateTime, const char* logfile )
{
	CFileInfo  FileInfo;
	FileInfo.SetCreatetime(CreateTime);
	FileInfo.SetFilename(logfile);

	FileInfoListIter_t	FileInfoListIter;
	FileInfoListIter = m_FileInfoList.begin();
	unsigned int Postion = 0;

	char	TimeStr[128]="";
	//char	TimeStr2[128]="";

	for (; FileInfoListIter != m_FileInfoList.end(); ++ FileInfoListIter)
	{
		Postion++;
		//DEBUG_LOG(0,"Org Time:%u,New Time:%u",FileInfoListIter->GetCreatetime(),FileInfo.GetCreatetime());
		if(FileInfoListIter->GetCreatetime() > FileInfo.GetCreatetime() )
		{
			
			m_FileInfoList.insert(FileInfoListIter, FileInfo);
			//m_pLog->Debug("| %32s | insert file info list filename:%s,size:%d.",__FUNCTION__,logfile,m_FileInfoList.size());
			DEBUG_LOG(0,"insert file:%s,CreateTime:%s,postion:%u,info list size:%u",logfile,TimeToStr(TimeStr,CreateTime),Postion,m_FileInfoList.size());
			return;
		}
	}

	m_FileInfoList.push_back(FileInfo);
	DEBUG_LOG(0,"push back file:%s,CreateTime:%s,info list size:%u",logfile,TimeToStr(TimeStr,CreateTime),m_FileInfoList.size());
}

void KFPC_ScanLogPath::DelOldFile()
{
	FileInfoListIter_t	FileInfoListIter;

	size_t nlistSize = m_FileInfoList.size();
	INFO_LOG(0,"gz filelist size:%d",m_FileInfoList.size());

	if(nlistSize > m_MaxKeepFilesCount)
	{
		for(size_t i=0;i<(nlistSize -  m_MaxKeepFilesCount);i++)
		{
			FileInfoListIter = m_FileInfoList.begin(); //iterFileAttr never NULL because have (lstFileAttr.size() -n)
			DelFile((*FileInfoListIter).GetFilename());
			//m_pLog->Info("| %32s | remove gz file %s list size:%d\n",__FUNCTION__, (*FileInfoListIter).GetFilename(),m_FileInfoList.size());		
			DEBUG_LOG(0,"remove gz file %s list size:%d",(*FileInfoListIter).GetFilename(),m_FileInfoList.size());
			m_FileInfoList.pop_front();
		}
	}
}

void KFPC_ScanLogPath::ScanLogPath()
{
	INFO_LOG(0,"");

	char				tmplogfile[MAX_FILE_NAME_LEN] = "";
#ifdef WIN32

	WIN32_FIND_DATA FileData; 
	HANDLE			hSearch; 			
	struct _stat	fstat;
	
#if _UNICODE
	TCHAR  lpszRegexStr[MAX_REGEX_STR*sizeof(wchar_t)];  
	CharToWchar(m_RegexStr,lpszRegexStr,MAX_REGEX_STR*sizeof(wchar_t));
	hSearch = FindFirstFile(lpszRegexStr, &FileData);
#else
	hSearch = FindFirstFile(m_RegexStr, &FileData);
#endif
	 
	if (hSearch == INVALID_HANDLE_VALUE) 
	{
		return ;
	}

	do
	{
		sprintf(tmplogfile,"%s/%s",m_pLog->GetLogPath(),FileData.cFileName);

		if(_stat(tmplogfile , &fstat) == 0 && 
			m_pLog->IsNotCurrentFile(tmplogfile))
		{
			 

			AddFileInfo(fstat.st_ctime, tmplogfile);
		}
	}while(FindNextFile(hSearch,&FileData));

	FindClose(hSearch);
#endif

#ifdef LINUX
	DIR*				pDir	= NULL;		/**< 打开目录句柄 */
	struct dirent*		ent		= NULL;		/**< 读目录数据 */
	Pcre				RegexExp(m_RegexStr);	/**< 正则表达式处理器 */

	try
	{

		pDir = opendir(m_pLog->GetLogPath());
		if (pDir == NULL)
		{
			WARNING_LOG(0,"opendir:%s fail",m_pLog->GetLogPath());
			return ;
		}
		while((ent = readdir(pDir)) != NULL) 
		{
			// 只处理文件型文件
			if (ent->d_type == 8)
			{
				int iExistFileNameLen = 0;

				iExistFileNameLen = strlen(ent->d_name);
				if (iExistFileNameLen > 4)
				{					
					sprintf(tmplogfile,"%s/%s",m_pLog->GetLogPath(),ent->d_name);
					DEBUG_LOG(0,"RegexStr:%s,begin RegexExp search:%s",m_RegexStr,ent->d_name);
					if(RegexExp.search(ent->d_name) == true)
					{
						struct stat stSTAT;
						if(stat(tmplogfile,&stSTAT) == 0 && m_pLog->IsNotCurrentFile(tmplogfile))
						{
							AddFileInfo(stSTAT.st_ctime, tmplogfile);						
						}
					}
				}
			}
		}
		closedir(pDir);
		pDir = NULL;
	}
	catch(...)
	{
		return ;
	}

#endif

}

const char* KFPC_ScanLogPath::TimeToStr( char* pStr,time_t t )
{
	if (0 == t)
	{
		//strcpy(pStr,"NULL");
		strcpy(pStr, "0000-00-00 00:00:00");

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
