#include "KFPC_DBTask.h"
#include "kfpc_logex.h"

KFPC_DBTask::KFPC_DBTask():
m_DataBaseAccess(NULL),
	m_Query(false),
	m_SQLDebug(false)
{
}


KFPC_DBTask::~KFPC_DBTask(void)
{
}

void* KFPC_DBTask::Svc()
{

	if (!GetDataBaseAccess()->ExecuteSql(m_Sql.c_str(),m_SQLDebug))
	{
		WARNING_LOG(0,"ExecuteSql Error (%s).",m_Sql.c_str());		
	}

	return 0;
}