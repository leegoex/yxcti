#ifndef kfpc_configfile_h__
#define kfpc_configfile_h__
#include<string>
using namespace std;
#include "KFPC_ContactCenterPublicDef.h"
#include "KFPC_DBAccessInfo.h"
#include <string.h>

#ifdef _WIN32
#pragma warning(disable:4091)
#endif // _WIN32

#include "tinyxml.h"


#define NODE_APPINFO				"/Configuration/AppInfo"
#define ATTR_APP_NAME				"AppName"
#define ATTR_APP_ID					"AppID"
#define ATTR_APP_TYPE				"AppType"
#define ATTR_APP_GROUP_ID			"AppGroupID"
#define ATTR_MASTER_FLAG			"MasterFlag"
#define ATTR_LISTEN_PORT			"ListenPort"
#define ATTR_APP_THREAD_POOL_SIZE	"AppThreadPoolSize"

#define NODE_COM_LIB_PARAMS			"/Configuration/ComLibParams"
#define ATTR_MULTICATE_PORT			"MulticatePort"
#define ATTR_MULITCATE_IP			"MulticateIP"
#define ATTR_CONNECT_PASS_WORD		"ConnectPassWord"
#define ATTR_THREAD_POOL_SIZE		"ThreadPoolSize"
#define ATTR_KEEP_LIVE_TIME			"KeepLiveTime"
#define ATTR_KEEP_LIVE_COUNT		"KeepLiveCount"
#define ATTR_MAX_SOCKET_COUNT		"MaxSocketCount"
#define ATTR_MSG_FILTER_COUNT		"MsgFilterCount"
#define ATTR_COM_OUT_PUT_MODE		"OutPutMode"
#define ATTR_COM_FILE_LOG_LEVEL		"FileLogLevel"
#define ATTR_COM_CONSOLE_LOG_LEVEL	"ConsoleLogLevel"

#define NODE_LOG					"/Configuration/Log"
#define ATTR_OUT_PUT_MODE			"OutPutMode"
#define ATTR_FILE_LOG_LEVEL			"FileLogLevel"
#define ATTR_CONSOLE_LOG_LEVEL		"ConsoleLogLevel"


#define NODE_CONNECTTOREMOTE		"/Configuration/ConnectToRemote"
#define ATTR_REMOTE_IP				"RemoteIP"
#define ATTR_REMOTE_PORT			"RemotePort"
#define ATTR_USER_CONTEXT1			"UserContext1"
#define ATTR_USER_CONTEXT2			"UserContext2"


#define NODE_DATABASE				"Database"
#define ATTR_DATASOURCE				"DataSource"
#define ATTR_USERNAME				"UserName"
#define ATTR_PASSWD					"Passwd"
#define ATTR_DATABASETYPE			"DataBaseType"
#define ATTR_THREADPOOLSIZE			"ThreadPoolSize"
#define ARRT_SQLDEBUG				"SQLDebug"

using namespace std;
class KFPC_ConfigFile
{
private:
	string	m_RemoteLicenseIP;
	unsigned int m_RemoteLicensePort;
	unsigned int m_AppID;

public:
	const char* GetRemoteLicenseIP() { return m_RemoteLicenseIP.c_str(); }
	unsigned int GetRemoteLicensePort(){return m_RemoteLicensePort;}

	KFPC_ConfigFile(void);
	~KFPC_ConfigFile(void);

	

	static KFPC_ConfigFile* GetInstance();

	//static void Destroy();
private:
	
	char			m_FileName[KFPC_MAX_FILE_NAME];

	const char *	m_pAppNameAttr;
	const char *	m_pAppIDAttr;
	const char *	m_pAppTypeAttr;
	const char *	m_pAppGroupIDAttr;
	const char *	m_pMasterFlagAttr;
	const char *	m_pListenPortAttr;
	const char *	m_pAppThreadPoolSizeAttr;
	void Init();
protected:
	TiXmlDocument	m_ConfigDocument;	
	bool m_ConfigFileLoadFlag;	

	KFPC_DBAccessInfo m_DBAccessInfo;
public:	
	unsigned int GetAppID() 
	{ 
		if(0 == m_AppID)
		{
			unsigned int AppID = 0;
			GetAppID(AppID);
		}

		return m_AppID; 
	}

	bool GetConfigFileLoadFlag() { return m_ConfigFileLoadFlag; }
	void SetConfigFileLoadFlag(bool val) { m_ConfigFileLoadFlag = val; }

	char* GetFileName() { return m_FileName; }
	
	//应用程序参数
	//int GetPeerPort(unsigned int &PeerPort);
	int GetAppName(char *pAppName,int Length);
	int GetAppID(unsigned int &AppID);
	int GetAppType(unsigned int &AppType);
	int GetAppGroupID(unsigned int &AppGroupID);
	int GetMasgetFlag(unsigned int &MasterFlag);
	int GetListenPort(unsigned int &ListenPort);
	//int GetPeerIP(char *pPeerIP,int Length);
	//int GetUniqueIdentify(char *pUniqueIdentify,int Length);
	int GetAppThreadPoolSize(unsigned int &AppThreadPoolSize);

	//通信库参数
	int GetMulticastPort(unsigned int &MulticatePort);
	int GetMulticastIP(char *pMulticastIP,int Length);
	int GetAuthPassWord(char *pAuthPassWord,int Length);
	int GetComThreadPoolSize(unsigned int &ThreadPoolSize);
	int GetKeepLiveTime(unsigned int &KeepLiveTime);
	int GetKeepLiveTimeCount(unsigned int &KeepLiveTimeCount);
	int GetMaxSocketCount(unsigned int &MaxSocketCount);
	int GetMsgFilterCount(unsigned int &MsgFilterCount);
	//int GetUserContext1(unsigned int &UserContext1);
	//int GetUserContext2(unsigned int &UserContext2);	
	int GetComLogOutPutMode(unsigned int &LogOutPutMode);
	int GetComFileLogLevel(unsigned int &FileLogLevel);
	int GetComConsoleLogLevel(unsigned int &ConsoleLogLevel);

	//日志参数
	int GetLogOutPutMode(unsigned int &LogOutPutMode);
	int GetFileLogLevel(unsigned int &FileLogLevel);
	int GetConsoleLogLevel(unsigned int &ConsoleLogLevel);
	virtual int LoadConfigFile(const char* pFileName);
	virtual int ReLoadConfigFile(const char* pFileName);
	int GetDBAccessInfo(TiXmlElement *pElement);

	virtual void ConfigFileLoadSuccess(){}

private:
	unsigned int GetRemoteLicense();
	
};
//#define  KFPCConfigFileInstance	KFPC_ConfigFile::GetInstance()
#endif // kfpc_configfile_h__