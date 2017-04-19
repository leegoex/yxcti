#pragma once
#include "kfpc_threadpool.h"
#include "DataBaseAccess.h"

class KFPC_DBThreadPool :
	public KFPC_ThreadPool
{
private:
	CDataBaseAccess*	m_DataBaseAccessList;
	unsigned int		m_DBInx;
public:
	KFPC_DBThreadPool(void);
	virtual ~KFPC_DBThreadPool(void);
	unsigned int Open(const char* DataSource="ContactCenter",
		const char* UserName="ContactCenter",
		const char* Passwd="123456",
		unsigned char poolSize =5);
	void Close();
	void* DoThreadProc(KFPC_ThreadParamInfo* pThreadParamInfo);

	static KFPC_DBThreadPool* GetInstance()
	{
		static KFPC_DBThreadPool _Instance;
		return &_Instance;
	}
};

#define  KFPC_DBThreadPoolInstance	KFPC_DBThreadPool::GetInstance()

class KFPC_CRMDBThreadPool :
	public KFPC_DBThreadPool
{

public:
	KFPC_CRMDBThreadPool(void){};
	virtual ~KFPC_CRMDBThreadPool(void){};
	
	static KFPC_CRMDBThreadPool* GetInstance()
	{
		static KFPC_CRMDBThreadPool _Instance;
		return &_Instance;
	}
};
#define  KFPC_CRMDBThreadPoolInstance	KFPC_CRMDBThreadPool::GetInstance()

class KFPC_QueryLastServiceDBThreadPool:public KFPC_DBThreadPool
{
public:
	KFPC_QueryLastServiceDBThreadPool(void){};
	virtual ~KFPC_QueryLastServiceDBThreadPool(void){};

	static KFPC_QueryLastServiceDBThreadPool* GetInstance()
	{
		static KFPC_QueryLastServiceDBThreadPool _Instance;
		return &_Instance;
	}
};

#define  KFPC_QueryLastServiceDBThreadPoolInstance	KFPC_QueryLastServiceDBThreadPool::GetInstance()
