#pragma once
#include "KFPC_ConfigFile.h"
#include "kfpc_logex.h"
#include "KFPC_TrunkGroupMgr.h"

#define NODE_ENABLE					"Enable"
#define SIGNALTYPECOUNT				7

#pragma region 公用属性宏
#define ATTR_IP						"IP"
#define ATTR_PORT					"Port"
#define ATTR_FLAG					"Flag"
#define ATTR_DESCRIPTION			"Description"
#define ATTR_BEGINSPAN				"BeginSpan"
#define ATTR_BEGINCHANNEL			"BeginChannel"
#define ATTR_ENDSPAN				"EndSpan"
#define ATTR_ENDCHANNEL				"EndChannel"
#define ATTR_ID						"ID"
#define NODE_AG						"AG"
#define NODE_DTI					"DTI"
#pragma endregion 公用属性宏

#define NODE_EHANGCOM				"/Configuration/eHangCom"
#define ATTR_EHANGCOMKEEPALIVE		"KeepAlive"
#define ATTR_EHANGCOMSIPPORT		"SipPort"

#define NODE_TRUNKGROUPMGR			"TrunkGroupMgr"
#define NODE_TRUNKGROUP				"TrunkGroup"
#define ATTR_TRUNKGROUPNAME			"Name"
#define NODE_CHANNELBLOCK			"ChannelBlock"
#define ATTR_IDLETYPE				"IdleType"
#define NODE_SIPCALLOUT				"SIPCallOut"
#define ATTR_SIPCALLUSERNAME		"UserName"
#define ATTR_SIPCALLPASSWORD		"PassWord"
#define ATTR_SIPCALLAUDIOCODES		"AudioCodes"
#define NODE_SIPCALLOFFER			"SIPCallOffer"
#define ATTR_SIPCALLOFFERMASK		"Mask"
#define NODE_AUDIOCODE				"AudioCode"
#define ATTR_CODES					"Codes"
#define	ATTR_AUTOANSWER				"AutoAnswer"
#define	ATTR_SIPSERVER				"SIPServer"
#define	ATTR_LOCALRTP				"LocalRtp"
#define	ATTR_CallerNOA				"CallerNOA"	
#define	ATTR_CalledNOA				"CalledNOA"
#define	ATTR_Support183				"Support183"

#define ATTR_PROXY					"Proxy"
#define ATTR_AddPrefix				"AddPrefix"
#define ATTR_StripPrefix			"StripPrefix"

#define NODE_CallOutMode			"CallOutMode"
#define ATTR_Value					"Value"
 

#define NODE_ANALOGTONECFG			"AnalogToneCfg"
#define NODE_TONE					"Tone"
#define ATTR_TONEID					"ID"
#define ATTR_TONEFQ1				"Fq1"
#define ATTR_TONEFQ2				"Fq2"
#define ATTR_TONEON					"On"
#define ATTR_TONEONDV				"Ondv"
#define ATTR_TONEOFF				"Off"
#define ATTR_TONEOFFDV				"Offdv"

#define NODE_ANALOGCHNUMTABLE		"AnalogChNumTable"
#define ATTR_ANALOGCHANNEL			"Ch"
#define ATTR_ANALOGCHANNELNUM		"Num"
#define ATTR_ANALOGCHANNELQUICKDIAL	"QuickDial"

#define NODE_DIGITTRUNKNUMTABLE		"DigitTrunkNumTable"
#define NODE_TRUNK					"Trunk"
#define ATTR_DIGITSPAN				"Span"
#define ATTR_DIGITTRUNKNUM			"Num"

#define NODE_SIPREGISTERLIST		"SipRegisterList"
#define ATTR_REREGISTERINTERVAL		"ReregisterInterval"
#define ATTR_FAILREGISTERINTERVAL	"FailRegisterInterval"
#define NODE_SIPACCOUNT				"SipAccount"
#define ATTR_NODEID					"NodeID"
#define ATTR_BRD					"BRD"
#define ATTR_DOMAIN					"Domain"
#define ATTR_USERNAME				"UserName"
#define ATTR_PASSWORD				"PassWord"
#define ATTR_EXPIRES				"Expires"

#define NODE_CHANNELSIGANL			"ChannelSignal"
#define NODE_SIGNAL					"Signal"
#define ATTR_SIGNALTYPE				"Type"

#define NODE_FXS					"FXS"
#define NODE_COLLECTCALLED			"CollectCalled"
#define ATTR_MODE					"Mode"
#define ATTR_MAXDIGITS				"MaxDigits"
#define ATTR_TERMCHAR				"TermChar"
#define ATTR_FIRSTDIGITTIMER		"FirstDigitTimer"
#define ATTR_INTERDIGITTIMER		"InterDigitTimer"
#define ATTR_COMPLETIONTIMER		"CompletionTimer"
#define NODE_CALLOUNT				"CallOut"
#define ATTR_MAXRINGTIMES			"MaxRingTimes"

#define NODE_FXO					"FXO"
#define NODE_GETCALLER				"GetCaller"
#define ATTR_CALLOFFERRINGTIMES		"CallOfferRingTimes"



#define NODE_SWNODECONFIG			"NodeCfg"
#define NODE_SWNODE					"Node"
#define ATTR_SWNODEMAXVOICE			"MaxVoice"
#define ATTR_SWNODEMAXVOIP			"MaxVoip"
#define ATTR_SWNODEMAXSIP			"MaxSIP"
#define ATTR_SWNODEMAXCONFERENCE	"MaxConference"

#define NODE_AGC					"AGC"
#define ATTR_Valid					"Valid"
#define ATTR_Active					"Active"
#define ATTR_GainSlop				"GainSlop"
#define ATTR_Redirection			"Redirection" 
#define ATTR_TargetEnergy			"TargetEnergy"

#define NODE_Conference				"Conference"
#define ATTR_Direction				"Direction"
#define ATTR_Volume					"Volume"

#define NODE_MSML					"MSML"
#define ATTR_ConferenceSize			"ConferenceSize"

#define NODE_CheckinvalidCallID		"CheckinvalidCallID"
#define ATTR_Interval				"Interval"
#define ATTR_LiveTime				"LiveTime"
//#define ATTR_CallMaxTime			"CallMaxTime"

#define NODE_Monitor				"Monitor"
#define ATTR_StatInterval			"StatInterval"
#define NODE_Record					"Record"
#define ATTR_Mode					"Mode"
#define ATTR_TransformMp3			"TransformMp3"
#define ATTR_RecordAGC				"RecordAGC"

#define NODE_ContactIPMap			"ContactIPMap"
#define NODE_IPMap					"IPMap"
#define ATTR_LAN_IP					"LAN_IP"
#define ATTR_WAN_IP					"WAN_IP"

#define NODE_ModuleRes				"ModuleRes"
#define ATTR_MAX					"Max"

#define NODE_EchoCancel				"EchoCancel"

typedef enum	RecordMode_t
{
	RM_CONF,
	RM_Mix
}RecordMode_t;

class	Record_Cfg
{
private:
	RecordMode_t	m_RecordMode;
	bool			m_TransformMp3;
	int				m_RecordAGC;

public:
	bool GetTransformMp3() const { return m_TransformMp3; }
	void SetTransformMp3(bool val) { m_TransformMp3 = val; }

	Record_Cfg():
	m_TransformMp3(false),
		m_RecordAGC(1)
	{
		m_RecordMode = RM_CONF;
	}

	RecordMode_t GetRecordMode() const { return m_RecordMode; }
	void SetRecordMode(RecordMode_t val) { m_RecordMode = val; }

	int GetRecordAGC() const { return m_RecordAGC; }
	void SetRecordAGC(int val) { m_RecordAGC = val; }
};

class	Monitor_Cfg
{
public:
	Monitor_Cfg()
	{
		m_StatInterval = 30;
	}
	unsigned int	m_StatInterval;
};

class MSML_Cfg
{
public:
	unsigned int m_ConfSize;

	MSML_Cfg()
	{
		m_ConfSize = 6;
	}	
	
	unsigned int GetConfSize() const { return m_ConfSize; }
	void SetConfSize(unsigned int val) { m_ConfSize = val; }
};

//配置文件节点对象类型
typedef enum ConfigObjectType_t
{
	OP_TRUNKGROUP = 0,
	OP_ANALOGTONE,
	OP_ANALOGCHANNELNUM,
	OP_DIGITTRUNKNUM,
	OP_SIPREGISTER,
	OP_CHANNELSIGNAL,
	OP_FXSINFO,
	OP_FXOINFO,
	OP_DBACCESSINFO,
	OP_NODECONFIG,
	OP_AGC,
	OP_CONFCFG,
	OP_MSML,
	OP_CheckinvalidCallID
}ConfigObjectType_t;

class KFC_Agc
{
private:
	int	m_Valid;

	int m_Active;// = 1;
	int m_GainSlop;// = 3;
	int m_Redirection;// = 1;
	int m_TargetEnergy;// = 40;

public:
	KFC_Agc():
	  m_Valid(0),
	  m_Active(1),
	  m_GainSlop(3),
	  m_Redirection(1),
	  m_TargetEnergy(40)
	{

	}

	  int GetValid() { return m_Valid; }
	  void SetValid(int val) { m_Valid = val; }

	  int GetActive() { return m_Active; }
	  void SetActive(int val) { m_Active = val; }

	  int GetGainSlop() { return m_GainSlop; }
	  void SetGainSlop(int val) { m_GainSlop = val; }

	  int GetRedirection() { return m_Redirection; }
	  void SetRedirection(int val) { m_Redirection = val; }

	  int GetTargetEnergy() { return m_TargetEnergy; }
	  void SetTargetEnergy(int val) { m_TargetEnergy = val; }

	  void Log()
	  {
		  INFO_LOG(0,"Valid:%u,Active:%u,GainSlop:%u,Redirection:%u,TargetEnergy:%u.",
			  m_Valid,
			  m_Active,
			  m_GainSlop,
			  m_Redirection,
			  m_TargetEnergy);
	  }

};

class KFC_ConfCfg
{
private:
	int m_Valid;
	int m_Direction;
	int m_Volume;

public:
	KFC_ConfCfg():
	  m_Valid(0),
	  m_Direction(0),
	  m_Volume(0)
	{

	}	
	  
	int GetValid() { return m_Valid; }
	void SetValid(int val) { m_Valid = val; }

	int GetDirection() { return m_Direction; }
	void SetDirection(int val) { m_Direction = val; }

	int GetVolume() { return m_Volume; }
	void SetVolume(int val) { m_Volume = val; }

	void Log()
	{
		INFO_LOG(0,"Valid:%u,Direction:%u,Volume:%u.",
			m_Valid,
			m_Direction,
			m_Volume);
	}
};




class SS_TServerConfigFile:public KFPC_ConfigFile
{
public:
	static SS_TServerConfigFile* GetInstance();

	SS_TServerConfigFile(void);
	~SS_TServerConfigFile(void);

	/**
	 * FullName:  	KFPC_TServerConfigFile::GeteHangComIp
	 * @brief 		获得EH MC IP
	 * @param[in,out] char * Ip
	 * @return   	unsigned int 成功返回0，失败返回错误代码
	 */
	unsigned int GeteHangComIp(char* Ip);

	/**
	 * FullName:  	KFPC_TServerConfigFile::GeteHangComPort
	 * @brief 		获得EH MC port
	 * @param[in,out] unsigned int & Port
	 * @return   	unsigned int 成功返回0，失败返回错误代码
	 */
	unsigned int GeteHangComPort(unsigned int& Port);

	/**
	 * FullName:  	KFPC_TServerConfigFile::GeteHangComKeeyAlive
	 * @brief 		获得EH Keep live 
	 * @param[in,out] unsigned int & KeepAlive
	 * @return   	unsigned int  成功返回0，失败返回错误代码
	 */
	unsigned int GeteHangComKeepAlive(unsigned int& KeepAlive);

	unsigned int GeteHangComSipPort(unsigned int& Port);


	KFPC_TrunkGroupMgr *GetTrunkGroupMgr();

	KFPC_DBAccessInfo *GetDBAccessInfoSet();


	unsigned int GetSignalType(unsigned int ChID,KFPC_SignalType& SignalType);
	KFC_Agc& GetAgc() { return m_Agc; }
	KFC_ConfCfg& GetConfCfg() { return m_ConfCfg; }

#ifdef TSERVER_GL
	NetServer_Cfg& GetNetServer_Cfg()  { return m_NetServer_Cfg; }
#endif
	MSML_Cfg& GetMSMLCfg()  { return m_MSMLCfg; }

	unsigned int GetCheckCallIDInterval() const { return m_CheckCallIDInterval; }
	void SetCheckCallIDInterval(unsigned int val) { m_CheckCallIDInterval = val; }

	unsigned int GetCheckCallIDLiveTime() const { return m_CheckCallIDLiveTime; }
	void SetCheckCallIDLiveTime(unsigned int val) { m_CheckCallIDLiveTime = val; }

	//unsigned int GetCallMaxTime() const { return m_CallMaxTime; }
	//void SetCallMaxTime(unsigned int val) { m_CallMaxTime = val; }

	Monitor_Cfg& GetMonitor_Cfg() { return m_Monitor_Cfg; }
	
	Record_Cfg& GetRecord_Cfg() { return m_Record_Cfg; }

	bool GetEchoCancel() { return m_EchoCancel; }
	void SetEchoCancel(bool val) { m_EchoCancel = val; }

private:
	KFPC_TrunkGroupMgr m_TrunkGroupMgr;

	

	bool m_GetChannelSignalFlag;

	KFC_Agc	m_Agc;
	KFC_ConfCfg	m_ConfCfg;
	MSML_Cfg	m_MSMLCfg;
	unsigned int m_CheckCallIDInterval;
	unsigned int m_CheckCallIDLiveTime;
	//unsigned int m_CallMaxTime;
	Monitor_Cfg	m_Monitor_Cfg;
	Record_Cfg	m_Record_Cfg;
	bool		m_EchoCancel;


private:
	KFPC_SignalType Translate(char * pType);
	/**
	 * FullName:  	KFPC_TServerConfigFile::GeteTrunkGroup
	 * @brief 		加载中继配置信息
	 * @param[in,out] KFPC_TrunkGroupMgr & TrunkGroupMgr
	 * @return   	unsigned int  成功返回0，失败返回错误代码
	 */
	unsigned int GetTserverCfg(ConfigObjectType_t NodeType);
	unsigned int GetAgc(TiXmlElement *pElement);
	unsigned int GetConfCfg(TiXmlElement *pElement);

	int GetTrunkGroup(TiXmlElement *pElement);
	unsigned int GetChannelBlock(TiXmlElement *pElement,KFPC_TrunkGroup *pTrunkGroup);
	KFPC_QueryIdleChType GetQueryIdleChType(const char* pIdleType);
	unsigned int GetSipCallOut(TiXmlElement *pElement,KFPC_TrunkGroup *pTrunkGroup);
	unsigned int GetSipCallOffer(TiXmlElement *pElement,KFPC_TrunkGroup *pTrunkGroup);
	unsigned int GetAudioCode(TiXmlElement *pElement,KFPC_TrunkGroup *pTrunkGroup);

	unsigned int GetCallOutMode(TiXmlElement *pElement,KFPC_TrunkGroup *pTrunkGroup);

	//unsigned int GetSipRegister(TiXmlElement *pElement);

	int GetMSMLCfg(TiXmlElement *pElement);
	int GetCheckinvalidCallIDCfg(TiXmlElement *pElement);
	int GetMonitorCfg();

	int GetRecordCfg();
	int GetContactIPMap();
	unsigned int GetIPMap(TiXmlElement *pElement);
	int GetEchoCancelCfg();
protected:
	virtual void ConfigFileLoadSuccess();



};


#define  SSTServerCfgInstance	SS_TServerConfigFile::GetInstance()
