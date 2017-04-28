
#include "kfpc_logex.h"
#include "KFPC_DBThreadPool.h"
//#include "KFPC_DBTaskImp.h"
#include "KFPC_ConfigFile.h"
#include "kfpc_api.h"
#include "kfpc_logex.h"
#include "KFPC_AppMainThread.h"
#include "KFPC_ComApiHandler.h"
#include "KFPC_NodeMgr.h"
#include "KFPC_TServerConfigFile.h"
#include "KFPC_TServerMain.h"
#include "KFPC_ComApiHanderImp.h"
#include "KFPC_TServerAPIHandlerImp.h"
#include "KFPC_VoiceSerAPIHandlerImp.h"
#include "KFPC_TSLicenseSerAPIHandlerImp.h"
#include "KFPC_TSLicSerMgr.h"
#include "kfpc_logex.h"
#include "kfpc_log.h"
#include "KFPC_CheckInvalidCallID.h"
#include "KFPC_MonitorRefreshData.h"
#include "KFPC_DBTaskInsertCallAlarm.h"
#include "KFPC_CallAlarmMgr.h"
#include "KFPC_CmdTimer.h"

#ifdef LINUX_SERVICE
#include <unistd.h>
#include "KFPC_LinuxDaemon.h"
KFPC_LinuxDaemon	g_LinuxDaemon;
#endif
#include "kfpc_getmac.h"


class AutoDel
{
public:
	AutoDel(){}
	~AutoDel()
	{
		TServerClose();
		//KFPCTServerCfgInstance->Destroy();
	}
};


static	AutoDel	g_AutoDel;

inline KFPC_Log* KFPC_CC_Loger()
{	
	static KFPC_Log		g_KFPC_CC_Loger("SS_TServer");
	return &g_KFPC_CC_Loger;
}

inline KFPC_Log* KFPC_CDR_Loger()
{	
	static KFPC_Log		g_KFPC_CDR_Loger("SS_TServerCDR");
	return &g_KFPC_CDR_Loger;
}

void ChangeAppLogMode()
{
	unsigned int LogOutPutMode = 0;
	if(SSTServerCfgInstance->GetLogOutPutMode(LogOutPutMode) != 0)
	{
		ERROR_LOG(0,"Failed to get LogOutPutMode.\n");
	}
	else
	{
		if(LogOutPutMode < 0 || LogOutPutMode > (LOM_CONSOLE|LOM_FILE))
		{
			ERROR_LOG(0,"LogOutputMode value is invalid.\n");
		}
		else
		{
			if(LogOutPutMode != 0)
			{
				KFPC_CC_Loger()->SetOutputMode(LogOutPutMode);
			}
			else
			{				
				KFPC_CC_Loger()->SetOutputMode(LOM_FILE);
			}
			
		}
	}

	unsigned int ConsoleLogLevel = 0;
	if(SSTServerCfgInstance->GetConsoleLogLevel(ConsoleLogLevel) != 0)
	{
		ERROR_LOG(0,"Failed to get ConsoleLogLevel.\n");
	}
	else
	{
		if(0 == ConsoleLogLevel)
		{
			KFPC_CC_Loger()->SetConsoleLogLevel(LL_INFO);
		}
		else if((ConsoleLogLevel >= LL_DEBUGMEM) && (ConsoleLogLevel <= LL_FATAL))
		{
			KFPC_CC_Loger()->SetConsoleLogLevel(ConsoleLogLevel);
		}
		else
		{
			ERROR_LOG(0,"ConsoleLogLevel value is invalid.\n");
		}
	}

	unsigned int FileLogLevel = 0;
	if(SSTServerCfgInstance->GetFileLogLevel(FileLogLevel) != 0)
	{
		ERROR_LOG(0,"Failed to get FileLogLevel.\n");
	}
	else
	{
		if(0 == FileLogLevel)
		{
			KFPC_CC_Loger()->SetFileLogLevel(LL_INFO);
		}
		else if((FileLogLevel >= LL_DEBUGMEM) && (FileLogLevel <= LL_FATAL))
		{
			KFPC_CC_Loger()->SetFileLogLevel(FileLogLevel);
		}
		else
		{
			ERROR_LOG(0,"FileLogLevel value is invalid.\n");
		}
	}
}



void* TServerMain(void*)
{

	KFPC_CC_Loger()->SetProgramVersion("0.0.1");

	KFPC_CC_Loger()->OpenThread();
	KFPC_CC_Loger()->SetOutputMode(LOM_FILE);


	KFPC_CDR_Loger()->SetProgramVersion(",CallID,CallType,ChannelType,Span,TimeSlot,Caller,Called,TrunkGroup,InitTime,AnswerTime,ConnectTime,ReleaseTime,TalkTime,RemoteRelease,SessionCallID,IP,ConfCreator,Cause");
	KFPC_CDR_Loger()->OpenThread();
	KFPC_CDR_Loger()->SetOutputMode(LOM_FILE);
	

	INFO_LOG(0,"");

	/**
	*	加载配置文件
	*/
	SSTServerCfgInstance->LoadConfigFile(SS_TSERVER_CFG);

	ChangeAppLogMode();
	
	//KFPCTServerCfgInstance->SetConfigFileLoadFlag(false);

	//KFPCTServerCfgInstance->LoadConfigFile(KFPC_TSERVER_CFG);


	char	AuthPassWord[KFPC_MAX_PASSWD_LEN];
	int	PwdLen = KFPC_MAX_PASSWD_LEN;
	int Ret = SSTServerCfgInstance->GetAuthPassWord(AuthPassWord,PwdLen);

	if(Ret == 0)
	{
		KFPC_ComApiHanderImpInstance->SetAuthPassWord(AuthPassWord);
	}

	KFPC_DBAccessInfo* pKFPC_DBAccessInfo = SSTServerCfgInstance->GetDBAccessInfoSet();

	if(pKFPC_DBAccessInfo != NULL)
	{
#ifndef TSERVER_NODB
		KFPC_DBThreadPoolInstance->Open(pKFPC_DBAccessInfo->GetDataSource(),
			pKFPC_DBAccessInfo->GetDBUserName(),
			pKFPC_DBAccessInfo->GetPasswd(),
			pKFPC_DBAccessInfo->GetPoolSize());
#endif

	}

	//KFPC_TrunkGroup* pMyTrunkGroup = KFPCTServerCfgInstance->GetTrunkGroupMgr()->GetTrunkGroupByIP("192.168.18.50");

	/**
	*	初始化数据
	*/
	KFPC_NodeMgrInstance;
	KFPC_ChMgrInstance;
	//KFPC_MySipChMgrInstance;


	KFPC_AppMainThreadInstance->RegisterMsgHander(KFPC_ID_CLASS_COM_API,KFPC_ComApiHanderImpInstance);


	KFPC_AppMainThreadInstance->RegisterMsgHander(KFPC_ID_CLASS_COM_TSERVER,KFCPTServerAPIHandlerImpInstance);
	//KFPC_AppMainThreadInstance->RegisterMsgHander(KFPC_ID_CLASS_COM_FAX,KFPCFaxSerAPIHandlerImpInstance);
	KFPC_AppMainThreadInstance->RegisterMsgHander(KFPC_ID_CLASS_COM_VOICE,KFPCVoiceSerAPIHandlerImpInstance);
	//KFPC_AppMainThreadInstance->RegisterMsgHander(KFPC_ID_CLASS_COM_TTS,KFPCTTSSerAPIHandlerImpInstance);
	KFPC_AppMainThreadInstance->RegisterMsgHander(KFPC_ID_CLASS_COM_LIC, KFPCTSLicenseSerAPIHandlerImpInstance);
	//KFPC_AppMainThreadInstance->RegisterMsgHander(KFPC_ID_CLASS_COM_SIPSERVER, SIPServerAPIInstance);


	//KFPC_AppMainThreadInstance->RegisterLoopHandler(KFPC_SipRegisterTimerInstance,"KFPC_SipRegisterTimerInstance");

	//KFPC_AppMainThreadInstance->RegisterLoopHandler(KFPC_MoreInfoTimerInstance,"KFPC_MoreInfoTimerInstance");


	//KFPC_AppMainThreadInstance->RegisterLoopHandler(KFPC_ConfTimerInstance,"KFPC_ConfTimerInstance");
	KFPC_AppMainThreadInstance->RegisterLoopHandler(KFPC_TSLicSerMgrInstance,"KFPC_TSLicSerMgrInstance");
	KFPC_AppMainThreadInstance->RegisterLoopHandler(KFPC_CheckInvalidCallIDInstance,"KFPC_CheckInvalidCallIDInstance");	
	KFPC_AppMainThreadInstance->RegisterLoopHandler(KFPC_CmdTimerInstance,"KFPC_CmdTimerInstance");	

	/**		
	*	启动主线程
	*/
	KFPC_AppMainThreadInstance->Start(SSTServerCfgInstance,1,500);

	if(strlen(SSTServerCfgInstance->GetRemoteLicenseIP()) > 0 &&
		SSTServerCfgInstance->GetRemoteLicensePort())
	{
		KFPC_ComApiHanderImpInstance->ConnectRemoteLicenseSer(SSTServerCfgInstance->GetRemoteLicenseIP(),
			SSTServerCfgInstance->GetRemoteLicensePort());
	}

	char		MacList[KFPC_MAX_INTERFACE_COUNT][MAXMACLEN];
	char		ethNameList[KFPC_MAX_INTERFACE_COUNT][MAXethNameLen];
	char		InterfaceIP[KFPC_MAX_INTERFACE_COUNT][MAXethNameLen];
	unsigned int InterfaceCount;

	memset(MacList,0,sizeof(MacList));
	memset(ethNameList,0,sizeof(ethNameList));
	memset(InterfaceIP,0,sizeof(InterfaceIP));
	InterfaceCount = 0;

	GetLocalMac(MacList,InterfaceIP,ethNameList,&InterfaceCount,true);

	char LogBuf[1024];
	for(unsigned int i=0;i<InterfaceCount;i++)
	{
		if(strcmp(InterfaceIP[i],"127.0.0.1") != 0 &&
			strcmp(InterfaceIP[i],"0.0.0.0") != 0)
		{
			snprintf(LogBuf,1024,"program start on host ip:%s",InterfaceIP[i]);
			INFO_LOG(0, "%s", LogBuf);
			break;
		}
		
	}

	SSTServerCfgInstance->GetTrunkGroupMgr()->SetIPChannelInService();

	KFPC_CallAlarmMgr_Instance->AppStartMsg(LogBuf);
	return NULL;
}

 void TServerClose()
 {
	 
	 KFPC_AppMainThreadInstance->Close();

#ifndef TSERVER_NODB
	 KFPC_DBThreadPoolInstance->Close();
#endif

	 //KFPC_NodeMgr::Destory();
	 KFPC_ChMgr::Destory();
	

	 INFO_LOG(0,"TServer perfect exit.");
 }
