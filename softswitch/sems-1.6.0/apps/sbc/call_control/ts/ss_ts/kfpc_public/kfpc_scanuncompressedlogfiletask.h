
#ifndef kfpc_scanuncompressedlogfiletask_h__
#define kfpc_scanuncompressedlogfiletask_h__
#include "kfpc_scanlogpath.h"

class KFPC_ScanUncompressedLogFileTask:
	public KFPC_ScanLogPath
{
public:
	KFPC_ScanUncompressedLogFileTask(KFPC_Log*	pLog,const char* pFileName,unsigned int MaxKeepFilesCount);
	~KFPC_ScanUncompressedLogFileTask(void);
	virtual void* Svc();

};

#endif // kfpc_scanuncompressedlogfiletask_h__

