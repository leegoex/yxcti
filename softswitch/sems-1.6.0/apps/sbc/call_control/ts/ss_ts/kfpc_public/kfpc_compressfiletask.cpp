#include "kfpc_compressfiletask.h"
#include "zlib.h"
#include "kfpc_logex.h"

KFPC_CompressFileTask::KFPC_CompressFileTask(KFPC_Log*	pLog, const char* pFileName) :
	m_pLog(pLog)
{
	strncpy(m_Filename, pFileName, MAX_FILE_NAME_LEN - 1);
}


KFPC_CompressFileTask::~KFPC_CompressFileTask(void)
{
}

void* KFPC_CompressFileTask::Svc()
{
	DEBUG_LOG(0, "");

	char	gzFileName[MAX_FILE_NAME_LEN];
	int		FileNameLen = strlen(m_Filename);

	strcpy(gzFileName, m_Filename);
	gzFileName[FileNameLen + 0] = '.';
	gzFileName[FileNameLen + 1] = 'g';
	gzFileName[FileNameLen + 2] = 'z';
	gzFileName[FileNameLen + 3] = '\0';

	if (CompressFile(m_Filename, gzFileName))
	{
		DelFile(m_Filename);
	}
	return NULL;
}



////////////////

