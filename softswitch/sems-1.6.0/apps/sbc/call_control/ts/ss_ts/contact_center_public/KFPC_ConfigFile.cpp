#include "KFPC_ConfigFile.h"
#include <stdio.h>
#include "kfpc_linuxwinapi.h"
#include "xpath_static.h"
#include "kfpc_logex.h"
#include "kfpc_msg.h"
#include "kfpc_error.h"

//KFPC_ConfigFile* KFPC_ConfigFile::_Instance;

KFPC_ConfigFile::KFPC_ConfigFile(void)
{
	m_ConfigFileLoadFlag = false;
	m_FileName[0]='\0';
	Init();

}

KFPC_ConfigFile::~KFPC_ConfigFile(void)
{
}

int KFPC_ConfigFile::LoadConfigFile(const char* pFileName)
{
	strncpy(m_FileName,pFileName,KFPC_MAX_FILE_NAME-1);

	INFO_LOG(0,"FileName:%s",m_FileName);

	if(!m_ConfigFileLoadFlag)
	{
		
		//Init();
		char ConfigFileName[KFPC_MAX_FILE_NAME] = {0};

		//取环境变量
		char* pConfigFileDirEnv = getenv(KFPC_CFG_DIR);

		if(pConfigFileDirEnv == NULL)
		{
			strcpy(ConfigFileName,"./cfg/");
			strcat(ConfigFileName,m_FileName);
		}
		else
		{
			strcpy(ConfigFileName,pConfigFileDirEnv);
			strcat(ConfigFileName,"/");
			strcat(ConfigFileName,m_FileName);
		}

		INFO_LOG(0,"Config file name:%s.",ConfigFileName);

		if(m_ConfigDocument.LoadFile(ConfigFileName))
		{
			m_ConfigFileLoadFlag = true;
			GetRemoteLicense();
			ConfigFileLoadSuccess();
			return 0;
		}
		else
		{
			ERROR_LOG(0,"Failed to load config file[%s].",ConfigFileName);
			return KFPC_RESULT_OPEN_FILE_ERROR;
		}
	}
	else
	{
		INFO_LOG(0,"FileName:%s already load.",m_FileName);
		return 0;
	}
}

#pragma region 获取应用程序参数
/*
int KFPC_ConfigFile::GetPeerPort(unsigned int &PeerPort)
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_APPINFO);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found %s in %s.\n",NODE_APPINFO,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in %s.\n",NODE_APPINFO);
			return -1;
		}

		const char *pPeerPortAttr = pElement->Attribute(ATTR_REMOTE_PORT);
		if(pPeerPortAttr == NULL)
		{
			WARNING_LOG(0,"Not found %s attribute in %s.\n",ATTR_REMOTE_PORT,NODE_APPINFO);
			return -1;
		}

		PeerPort = atoi(pPeerPortAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Failed to load config file.\n");
		return -1;
	}
}
*/

int KFPC_ConfigFile::GetAppName(char *pAppName,int Length)
{
	if(Length < KFPC_API_NAME_MAX_LEN)
	{
		return -1;
	}

	if(m_ConfigFileLoadFlag)
	{
		if(NULL == m_pAppNameAttr)
		{
			TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_APPINFO);
			if(pNode == NULL)
			{
				WARNING_LOG(0,"Not found node[%]s in config file[%s].",NODE_APPINFO,m_FileName);
				return -1;
			}

			TiXmlElement *pElement = pNode->ToElement();
			if(pElement == NULL)
			{
				WARNING_LOG(0,"Not found effective element in node[%s].",NODE_APPINFO);
				return -1;
			}

			m_pAppNameAttr = pElement->Attribute(ATTR_APP_NAME);

		}

		if(m_pAppNameAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_APP_NAME,NODE_APPINFO);
			return -1;
		}


		strncpy(pAppName,m_pAppNameAttr,Length);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

int KFPC_ConfigFile::GetAppID(unsigned int &AppID)
{
	if(m_ConfigFileLoadFlag)
	{
		if(m_AppID != 0)
		{
			AppID = m_AppID;
			return 0;
		}

		if(NULL == m_pAppIDAttr)
		{
			TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_APPINFO);
			if(pNode == NULL)
			{
				WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_APPINFO,m_FileName);
				return -1;
			}

			TiXmlElement *pElement = pNode->ToElement();
			if(pElement == NULL)
			{
				WARNING_LOG(0,"Not found effective element in node[%s].",NODE_APPINFO);
				return -1;
			}

			m_pAppIDAttr = pElement->Attribute(ATTR_APP_ID);
		}

		if(m_pAppIDAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_APP_ID,NODE_APPINFO);
			return -1;
		}

		m_AppID = AppID = atoi(m_pAppIDAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

int KFPC_ConfigFile::GetAppType(unsigned int &AppType)
{
	if(m_ConfigFileLoadFlag)
	{
		if(NULL == m_pAppTypeAttr)
		{
			TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_APPINFO);
			if(pNode == NULL)
			{
				WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_APPINFO,m_FileName);
				return -1;
			}

			TiXmlElement *pElement = pNode->ToElement();
			if(pElement == NULL)
			{
				WARNING_LOG(0,"Not found effective element in node[%s].",NODE_APPINFO);
				return -1;
			}

			m_pAppTypeAttr = pElement->Attribute(ATTR_APP_TYPE);
		}

		if(m_pAppTypeAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_APP_TYPE,NODE_APPINFO);
			return -1;
		}

		AppType = atoi(m_pAppTypeAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

int KFPC_ConfigFile::GetAppGroupID(unsigned int &AppGroupID)
{
	if(m_ConfigFileLoadFlag)
	{
		if(NULL == m_pAppGroupIDAttr)
		{
			TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_APPINFO);
			if(pNode == NULL)
			{
				WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_APPINFO,m_FileName);
				return -1;
			}

			TiXmlElement *pElement = pNode->ToElement();
			if(pElement == NULL)
			{
				WARNING_LOG(0,"Not found effective element in node[%s].",NODE_APPINFO);
				return -1;
			}

			m_pAppGroupIDAttr = pElement->Attribute(ATTR_APP_GROUP_ID);

		}

		if(m_pAppGroupIDAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_APP_GROUP_ID,NODE_APPINFO);
			return -1;
		}

		AppGroupID = atoi(m_pAppGroupIDAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

int KFPC_ConfigFile::GetMasgetFlag(unsigned int &MasterFlag)
{
	if(m_ConfigFileLoadFlag)
	{
		if(NULL == m_pMasterFlagAttr)
		{
			TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_APPINFO);
			if(pNode == NULL)
			{
				WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_APPINFO,m_FileName);
				return -1;
			}

			TiXmlElement *pElement = pNode->ToElement();
			if(pElement == NULL)
			{
				WARNING_LOG(0,"Not found effective element in node[%s].",NODE_APPINFO);
				return -1;
			}

			m_pMasterFlagAttr = pElement->Attribute(ATTR_MASTER_FLAG);
		}

		if(m_pMasterFlagAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_MASTER_FLAG,NODE_APPINFO);
			return -1;
		}

		MasterFlag = atoi(m_pMasterFlagAttr);
		if(MasterFlag != 2)
		{
			MasterFlag = 0;
		}

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

int KFPC_ConfigFile::GetListenPort(unsigned int &ListenPort)
{
	if(m_ConfigFileLoadFlag)
	{
		if(NULL == m_pListenPortAttr)
		{
			TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_APPINFO);
			if(pNode == NULL)
			{
				WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_APPINFO,m_FileName);
				return -1;
			}

			TiXmlElement *pElement = pNode->ToElement();
			if(pElement == NULL)
			{
				WARNING_LOG(0,"Not found effective element in node[%s].",NODE_APPINFO);
				return -1;
			}

			m_pListenPortAttr = pElement->Attribute(ATTR_LISTEN_PORT);

		}

		if(m_pListenPortAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_LISTEN_PORT,NODE_APPINFO);
			return -1;
		}

		ListenPort = atoi(m_pListenPortAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

/*
int KFPC_ConfigFile::GetPeerIP(char *pPeerIP,int Length)
{
	if(Length < KFPC_MAX_IP_LEN)
	{
		return -1;
	}

	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_APPINFO);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found %s in %s.\n",NODE_APPINFO,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in %s.\n",NODE_APPINFO);
			return -1;
		}

		const char *pPeerIPAttr = pElement->Attribute(ATTR_REMOTE_IP);
		if(pPeerIPAttr == NULL)
		{
			WARNING_LOG(0,"Not found %s attribute in %s.\n",ATTR_REMOTE_IP,NODE_APPINFO);
			return -1;
		}

		strncpy(pPeerIP,pPeerIPAttr,Length);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Failed to load config file.\n");
		return -1;
	}
}


int KFPC_ConfigFile::GetUniqueIdentify(char *pUniqueIdentify,int Length)
{
	return -1;
}
*/
int KFPC_ConfigFile::GetAppThreadPoolSize(unsigned int &AppThreadPoolSize)
{
	if(m_ConfigFileLoadFlag)
	{
		if(NULL == m_pAppThreadPoolSizeAttr)
		{
			TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_APPINFO);
			if(pNode == NULL)
			{
				WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_APPINFO,m_FileName);
				return -1;
			}

			TiXmlElement *pElement = pNode->ToElement();
			if(pElement == NULL)
			{
				WARNING_LOG(0,"Not found effective element in node[%s].",NODE_APPINFO);
				return -1;
			}

			m_pAppThreadPoolSizeAttr = pElement->Attribute(ATTR_APP_THREAD_POOL_SIZE);

		}

		if(m_pAppThreadPoolSizeAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_APP_THREAD_POOL_SIZE,NODE_APPINFO);
			return -1;
		}

		AppThreadPoolSize = atoi(m_pAppThreadPoolSizeAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}
#pragma endregion 获取应用程序参数

#pragma region 获取通信库参数
int KFPC_ConfigFile::GetMulticastPort(unsigned int &MulticatePort)
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_COM_LIB_PARAMS);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_COM_LIB_PARAMS,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in node[%s].",NODE_COM_LIB_PARAMS);
			return -1;
		}

		const char *pMulticatePortAttr = pElement->Attribute(ATTR_MULTICATE_PORT);
		if(pMulticatePortAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_MULTICATE_PORT,NODE_COM_LIB_PARAMS);
			return -1;
		}

		MulticatePort = atoi(pMulticatePortAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

int KFPC_ConfigFile::GetMulticastIP(char *pMulticastIP,int Length)
{
	if(Length < KFPC_MAX_IP_LEN)
	{
		return -1;
	}

	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_COM_LIB_PARAMS);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_COM_LIB_PARAMS,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in node[%s].",NODE_COM_LIB_PARAMS);
			return -1;
		}

		const char *pMulticateIPAttr = pElement->Attribute(ATTR_MULITCATE_IP);
		if(pMulticateIPAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_MULITCATE_IP,NODE_COM_LIB_PARAMS);
			return -1;
		}

		strncpy(pMulticastIP,pMulticateIPAttr,Length);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

int KFPC_ConfigFile::GetAuthPassWord(char *pAuthPassWord,int Length)
{
	if(Length < KFPC_MAX_PASSWD_LEN)
	{
		return -1;
	}

	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_COM_LIB_PARAMS);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_COM_LIB_PARAMS,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in node[%s].",NODE_COM_LIB_PARAMS);
			return -1;
		}

		const char *pAuthPassWordAttr = pElement->Attribute(ATTR_CONNECT_PASS_WORD);
		if(pAuthPassWordAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_CONNECT_PASS_WORD,NODE_COM_LIB_PARAMS);
			return -1;
		}

		strncpy(pAuthPassWord,pAuthPassWordAttr,Length);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

int KFPC_ConfigFile::GetComThreadPoolSize(unsigned int &ThreadPoolSize)
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_COM_LIB_PARAMS);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_COM_LIB_PARAMS,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in node[%s].",NODE_COM_LIB_PARAMS);
			return -1;
		}

		const char *pThreadPoolSizeAttr = pElement->Attribute(ATTR_THREAD_POOL_SIZE);
		if(pThreadPoolSizeAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_THREAD_POOL_SIZE,NODE_COM_LIB_PARAMS);
			return -1;
		}

		ThreadPoolSize = atoi(pThreadPoolSizeAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

int KFPC_ConfigFile::GetKeepLiveTime(unsigned int &KeepLiveTime)
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_COM_LIB_PARAMS);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_COM_LIB_PARAMS,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in node[%s}.",NODE_COM_LIB_PARAMS);
			return -1;
		}

		const char *pKeepLiveTimeAttr = pElement->Attribute(ATTR_KEEP_LIVE_TIME);
		if(pKeepLiveTimeAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_KEEP_LIVE_TIME,NODE_COM_LIB_PARAMS);
			return -1;
		}

		KeepLiveTime = atoi(pKeepLiveTimeAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

int KFPC_ConfigFile::GetKeepLiveTimeCount(unsigned int &KeepLiveTimeCount)
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_COM_LIB_PARAMS);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_COM_LIB_PARAMS,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in node[%s].",NODE_COM_LIB_PARAMS);
			return -1;
		}

		const char *pKeepLiveTimeCountAttr = pElement->Attribute(ATTR_KEEP_LIVE_COUNT);
		if(pKeepLiveTimeCountAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_KEEP_LIVE_COUNT,NODE_COM_LIB_PARAMS);
			return -1;
		}

		KeepLiveTimeCount = atoi(pKeepLiveTimeCountAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

int KFPC_ConfigFile::GetMaxSocketCount(unsigned int &MaxSocketCount)
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_COM_LIB_PARAMS);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_COM_LIB_PARAMS,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in node[%s].",NODE_COM_LIB_PARAMS);
			return -1;
		}

		const char *pMaxSocketCountAttr = pElement->Attribute(ATTR_MAX_SOCKET_COUNT);
		if(pMaxSocketCountAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_MAX_SOCKET_COUNT,NODE_COM_LIB_PARAMS);
			return -1;
		}

		MaxSocketCount = atoi(pMaxSocketCountAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

int KFPC_ConfigFile::GetMsgFilterCount(unsigned int &MsgFilterCount)
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_COM_LIB_PARAMS);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_COM_LIB_PARAMS,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in node[%s].",NODE_COM_LIB_PARAMS);
			return -1;
		}

		const char *pMsgFilterCountAttr = pElement->Attribute(ATTR_MSG_FILTER_COUNT);
		if(pMsgFilterCountAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_MSG_FILTER_COUNT,NODE_COM_LIB_PARAMS);
			return -1;
		}

		MsgFilterCount = atoi(pMsgFilterCountAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}
/*
int KFPC_ConfigFile::GetUserContext1(unsigned int &UserContext1)
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_COM_LIB_PARAMS);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found %s in %s.",NODE_COM_LIB_PARAMS,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in %s.",NODE_COM_LIB_PARAMS);
			return -1;
		}

		const char *pUserContext1Attr = pElement->Attribute(ATTR_USER_CONTEXT1);
		if(pUserContext1Attr == NULL)
		{
			WARNING_LOG(0,"Not found %s attribute in %s.",ATTR_USER_CONTEXT1,NODE_COM_LIB_PARAMS);
			return -1;
		}

		UserContext1 = atoi(pUserContext1Attr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Failed to load config file.\n");
		return -1;
	}
}

int KFPC_ConfigFile::GetUserContext2(unsigned int &UserContext2)
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_COM_LIB_PARAMS);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found %s in %s.",NODE_COM_LIB_PARAMS,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in %s.",NODE_COM_LIB_PARAMS);
			return -1;
		}

		const char *pUserContext2Attr = pElement->Attribute(ATTR_USER_CONTEXT2);
		if(pUserContext2Attr == NULL)
		{
			WARNING_LOG(0,"Not found %s attribute in %s.",ATTR_USER_CONTEXT2,NODE_COM_LIB_PARAMS);
			return -1;
		}

		UserContext2 = atoi(pUserContext2Attr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Failed to load config file.\n");
		return -1;
	}
}
*/

int KFPC_ConfigFile::GetComLogOutPutMode( unsigned int &LogOutPutMode )
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_COM_LIB_PARAMS);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_COM_LIB_PARAMS,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in node[%s].",NODE_COM_LIB_PARAMS);
			return -1;
		}

		const char *pOutPutModeAttr = pElement->Attribute(ATTR_COM_OUT_PUT_MODE);
		if(pOutPutModeAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_COM_OUT_PUT_MODE,NODE_COM_LIB_PARAMS);
			return -1;
		}

		LogOutPutMode = atoi(pOutPutModeAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

int KFPC_ConfigFile::GetComFileLogLevel( unsigned int &FileLogLevel )
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_COM_LIB_PARAMS);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_COM_LIB_PARAMS,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in node[%s].",NODE_COM_LIB_PARAMS);
			return -1;
		}

		const char *pFileLogLevelAttr = pElement->Attribute(ATTR_COM_FILE_LOG_LEVEL);
		if(pFileLogLevelAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_COM_FILE_LOG_LEVEL,NODE_COM_LIB_PARAMS);
			return -1;
		}

		FileLogLevel = atoi(pFileLogLevelAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

int KFPC_ConfigFile::GetComConsoleLogLevel( unsigned int &ConsoleLogLevel )
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_COM_LIB_PARAMS);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_COM_LIB_PARAMS,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in node[%s].",NODE_COM_LIB_PARAMS);
			return -1;
		}

		const char *pConsoleLogLevelAttr = pElement->Attribute(ATTR_COM_CONSOLE_LOG_LEVEL);
		if(pConsoleLogLevelAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_COM_CONSOLE_LOG_LEVEL,NODE_COM_LIB_PARAMS);
			return -1;
		}

		ConsoleLogLevel = atoi(pConsoleLogLevelAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}
#pragma endregion 获取通信库参数

#pragma region 获取日志参数
int KFPC_ConfigFile::GetLogOutPutMode(unsigned int &LogOutPutMode)
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_LOG);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_LOG,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in node[%s].",NODE_LOG);
			return -1;
		}

		const char *pLogOutPutModeAttr = pElement->Attribute(ATTR_OUT_PUT_MODE);
		if(pLogOutPutModeAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_OUT_PUT_MODE,NODE_LOG);
			return -1;
		}

		LogOutPutMode = atoi(pLogOutPutModeAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

int KFPC_ConfigFile::GetFileLogLevel(unsigned int &FileLogLevel)
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_LOG);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_LOG,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in node[%s].",NODE_LOG);
			return -1;
		}

		const char *pFileLogLevelAttr = pElement->Attribute(ATTR_FILE_LOG_LEVEL);
		if(pFileLogLevelAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_FILE_LOG_LEVEL,NODE_LOG);
			return -1;
		}

		FileLogLevel = atoi(pFileLogLevelAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

int KFPC_ConfigFile::GetConsoleLogLevel(unsigned int &ConsoleLogLevel)
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_LOG);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_LOG,m_FileName);
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in node[%s].",NODE_LOG);
			return -1;
		}

		const char *pConsoleLogLevelAttr = pElement->Attribute(ATTR_CONSOLE_LOG_LEVEL);
		if(pConsoleLogLevelAttr == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_CONSOLE_LOG_LEVEL,NODE_LOG);
			return -1;
		}

		ConsoleLogLevel = atoi(pConsoleLogLevelAttr);

		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

void KFPC_ConfigFile::Init()
{
	m_AppID = 0;
	m_pAppNameAttr = NULL;
	m_pAppIDAttr = NULL;
	m_pAppTypeAttr = NULL;
	m_pAppGroupIDAttr = NULL;
	m_pListenPortAttr = NULL;
	m_pAppThreadPoolSizeAttr = NULL;
	m_pMasterFlagAttr = NULL;
}

KFPC_ConfigFile* KFPC_ConfigFile::GetInstance()
{
	static KFPC_ConfigFile Instance;
	return &Instance;
}

//void KFPC_ConfigFile::Destroy()
//{
//	smart_delete(_Instance);
//	_Instance = NULL;
//}

int KFPC_ConfigFile::GetDBAccessInfo(TiXmlElement *pElement)
{
	const char *pDataSource = pElement->Attribute(ATTR_DATASOURCE);
	if(pDataSource != NULL)
	{
		m_DBAccessInfo.SetDataSource((char *) pDataSource);
	}
	else
	{
		m_DBAccessInfo.SetDataSource("ContactCenter");
		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_DATASOURCE,NODE_DATABASE);
	}

	const char *pUserName = pElement->Attribute(ATTR_USERNAME);
	if(pUserName != NULL)
	{
		m_DBAccessInfo.SetDBUserName((char *)pUserName);
	}
	else
	{
		m_DBAccessInfo.SetDBUserName("ContactCenter");
		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_USERNAME,NODE_DATABASE);
	}

	const char *pPassWord = pElement->Attribute(ATTR_PASSWD);
	if(pPassWord != NULL)
	{
		m_DBAccessInfo.SetPasswd((char *)pPassWord);
	}
	else
	{
		m_DBAccessInfo.SetPasswd("123456");
		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_PASSWD,NODE_DATABASE);
	}

	const char *pDataBaseType = pElement->Attribute(ATTR_DATABASETYPE);
	if(pDataBaseType != NULL)
	{
		m_DBAccessInfo.SetDataBaseType((char *)pDataBaseType);
	}
	else
	{
		m_DBAccessInfo.SetDataBaseType("MySql");
		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_DATABASETYPE,NODE_DATABASE);
	}

	const char *pThreadPoolSize = pElement->Attribute(ATTR_THREADPOOLSIZE);
	if(pThreadPoolSize != NULL)
	{
		m_DBAccessInfo.SetPoolSize(atoi(pThreadPoolSize));
	}
	else
	{
		m_DBAccessInfo.SetPoolSize(5);
		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_THREADPOOLSIZE,NODE_DATABASE);
	}

	unsigned int SQLDebug = 0;

	
	const char *pSQLDebug = pElement->Attribute(ARRT_SQLDEBUG);
	if(pSQLDebug != NULL)
	{
		m_DBAccessInfo.SetSQLDebug((atoi(pSQLDebug) == 0)?false:true);
	}
	else
	{
		m_DBAccessInfo.SetSQLDebug(false);
		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ARRT_SQLDEBUG,NODE_DATABASE);
	}

	m_DBAccessInfo.Log();
	return 0;
}

unsigned int KFPC_ConfigFile::GetRemoteLicense()
{
	TiXmlElement *pRootElement = m_ConfigDocument.RootElement();
	if(pRootElement == NULL)
	{
		WARNING_LOG(0, "Not found root node in config file[%s].",GetFileName());
		return -1;
	}

	TiXmlNode *pChildNode = NULL;
	while(pChildNode = pRootElement->IterateChildren(pChildNode))
	{
		if(pChildNode == NULL)
		{
			continue;
		}

		TiXmlElement *pChildElement = pChildNode->ToElement();
		if(pChildElement != NULL && pChildElement->Value() != NULL)
		{

			if(strcmp(pChildElement->Value(),"RemoteLicense") == 0)
			{
				const char *pIP = pChildElement->Attribute("IP");
				if(pIP != NULL)
				{
					m_RemoteLicenseIP = pIP;
				}
				else
				{						
					WARNING_LOG(0,"Not found attribute[%s] in node[%s].","IP","RemoteLicense");
					return -1;
				}

				const char *pAPP_ID = pChildElement->Attribute(ATTR_APP_ID);
				if(pAPP_ID != NULL)
				{
					m_RemoteLicensePort = 12813+atoi(pAPP_ID);
				}
				else
				{
					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_APP_ID,"RemoteLicense");
					return -1;
				}

				INFO_LOG(0,"RemoteLicense IP:%s,Port:%u",m_RemoteLicenseIP.c_str(),m_RemoteLicensePort);
				return 0;					
			}
		}
	}

	return -1;
}

int KFPC_ConfigFile::ReLoadConfigFile( const char* pFileName )
{
	m_ConfigFileLoadFlag = false;
	return LoadConfigFile(pFileName);
}
#pragma endregion 获取日志参数

