#ifndef kfpc_compressfiletask_h__
#define kfpc_compressfiletask_h__
#include "kfpc_log.h"
#include "kfpc_threadtask.h"
class KFPC_CompressFileTask :
	public KFPC_ThreadTask
{
private:
	KFPC_Log*		m_pLog;
	char			m_Filename[MAX_FILE_NAME_LEN];	/**< 长文件名，包括路径 */
public:
	KFPC_CompressFileTask(KFPC_Log*	pLog,const char* pFileName);
	~KFPC_CompressFileTask(void);
	void* Svc();	
	
};
#endif // kfpc_compressfiletask_h__

