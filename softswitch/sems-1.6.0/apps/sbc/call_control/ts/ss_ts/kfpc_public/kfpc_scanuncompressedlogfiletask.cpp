#include "kfpc_scanuncompressedlogfiletask.h"
#include "kfpc_log.h"
#include "kfpc_logex.h"

KFPC_ScanUncompressedLogFileTask::KFPC_ScanUncompressedLogFileTask(KFPC_Log*	pLog,const char* FileNamePrefix,unsigned int MaxKeepFilesCount):
KFPC_ScanLogPath(pLog,FileNamePrefix,MaxKeepFilesCount)
{
#ifdef WIN32
	sprintf(m_RegexStr,"%s/%s*.log",m_pLog->GetLogPath(),FileNamePrefix);
#endif

#ifdef LINUX
	//sprintf(m_RegexStr,"%s/%s*.log$",m_pLog->GetLogPath(),m_pLog->GetLogFileNamePrefix());
	sprintf(m_RegexStr,"%s\\w*.log$",FileNamePrefix);
#endif

	INFO_LOG(0,"RegexStr:%s",m_RegexStr);
}


KFPC_ScanUncompressedLogFileTask::~KFPC_ScanUncompressedLogFileTask(void)
{

}

void* KFPC_ScanUncompressedLogFileTask::Svc()
{
	INFO_LOG(0,"RegexStr:%s",m_RegexStr);

	ScanLogPath();

	FileInfoListIter_t	Iter = m_FileInfoList.begin();

	for(;Iter != m_FileInfoList.end();Iter++)
	{
		char	gzFileName[MAX_FILE_NAME_LEN];
		int		FileNameLen = strlen((*Iter).GetFilename());

		strcpy(gzFileName,(*Iter).GetFilename());
		gzFileName[FileNameLen + 0] = '.';
		gzFileName[FileNameLen + 1] = 'g';
		gzFileName[FileNameLen + 2] = 'z';
		gzFileName[FileNameLen + 3] = '\0';

		if(CompressFile((*Iter).GetFilename(),gzFileName))
		{
			DelFile((*Iter).GetFilename());
		}
	}

	return NULL;
}


