#pragma once
#include <stdlib.h>

#ifdef SEMS_TS_API_EXPORTS
	#define SEMS_TS_API extern "C" 
#else
	#ifdef __cplusplus
		#define SEMS_TS_API extern "C" 
	#else
		#define SEMS_TS_API
	#endif
#endif


/**
* API初始化函数，在KFPC_CCTSModule::init中调用
*/
SEMS_TS_API void OnStart();

/**
* 收到INVITE消息，在KFPC_CCTSModule::onInitialInvite中调用
*/
SEMS_TS_API void OnInvite();

/**
* 会话开始，在KFPC_CCTSModule::onStateChange中调用
*/
SEMS_TS_API void OnSessionStart();

/**
* 对方响铃，在KFPC_CCTSModule::onStateChange中调用
*/
SEMS_TS_API void OnRinging();

/**
* SBCCallLeg不会重写这个虚函数，如果有需要，我们就需要在SBCCallLeg中重写这个虚函数，以便抛出事件
*/
SEMS_TS_API void OnEarlySession();

/**
* 呼叫失败，在KFPC_CCTSModule::onCallFailed中
*/
SEMS_TS_API void OnFailedCall();

/**
* 收到SIP Request，在KFPC_CCTSModule::onInDialogRequest中调用
*/
SEMS_TS_API void OnSipRequest();

/**
* 收到SIP Reply，在KFPC_CCTSModule::onInDialogReply中调用
*/
SEMS_TS_API void OnSipReply();

/**
* 释放前函数，在KFPC_CCTSModule::onDestroyLeg中调用
*/
SEMS_TS_API void OnBeforeDestroy();

/**
* 结束通话，在KFPC_CCTSModule::onStateChange中调用
*/
SEMS_TS_API void OnHangup();

/**
* 保留通话，在KFPC_CCTSModule::putOnHold中调用
*/
SEMS_TS_API void OnHold();

/**
* 结束保留，在KFPC_CCTSModule::resumeHeld中调用
*/
SEMS_TS_API void OnUnHold();

/**
* B2B请求，在KFPC_CCTSModule::onEvent中调用
*/
SEMS_TS_API void OnB2BOtherRequest();

/**
* B2B回复，在KFPC_CCTSModule::onEvent中调用
*/
SEMS_TS_API void OnB2BOtherReply();

/**
* CallLeg无此事件，这个事件只与与mod_py有关
*/
SEMS_TS_API void OnB2BOtherBye();

/**
* Session超时，在KFPC_CCTSModule::onStateChange中调用
*/
SEMS_TS_API void OnSessionTimeout();

/**
* Session超时，在KFPC_CCTSModule::onStateChange中调用
*/
SEMS_TS_API void OnRtpTimeout();

/**
* remote end in an established call is unreachable (408/481 received)
   parameters: see sipReply (below), except #old_dlg_status
   CallLeg无此事件
*/
SEMS_TS_API void OnRemoteDisappeared();

/**
* onKey，在KFPC_CCTSModule::onDtmf中调用
*/
SEMS_TS_API void OnKey();

/**
* 定时器事件，在KFPC_CCTSModule::onEvent中调用
*/
SEMS_TS_API void OnTimer();

/**
* OnNoAudio，在KFPC_CCTSModule::onEvent中调用
*/
SEMS_TS_API void OnNoAudio();

/**
* OnPlaylistSeparator，在KFPC_CCTSModule::onEvent中调用
*/
SEMS_TS_API void OnPlaylistSeparator();

/**
* OnB2BEvent，在KFPC_CCTSModule::onEvent中调用
*/
SEMS_TS_API void OnB2BEvent();

/**
* 模块启动函数，可以不适用
*/
SEMS_TS_API void OnStartup();

/**
* 重新加载配置函数，可以不适用
*/
SEMS_TS_API void OnReload();

/**
* 系统事件函数，可不适用
*/
SEMS_TS_API void OnSystem();

SEMS_TS_API void OnSIPSubscription();

/// 以下事件可以不适用，和上面的重复
SEMS_TS_API void OnInitialInvite();
SEMS_TS_API void OnStateChange();
SEMS_TS_API void OnBLegRefused();

SEMS_TS_API void OnInDialogRequest();
SEMS_TS_API void OnInDialogReply();

SEMS_TS_API void OnEvent();
SEMS_TS_API void OnDtmf(int event, int duration);

SEMS_TS_API void OnputOnHold();
SEMS_TS_API void OnresumeHeld(bool send_reinvite);
SEMS_TS_API void OncreateHoldRequest();
SEMS_TS_API void OnhandleHoldReply(bool succeeded);



typedef	unsigned int (*stopCall_t)();
typedef	unsigned int(*disconnect_t)();
typedef	unsigned int(*putOnHold_t)();
typedef	unsigned int(*resumeHeld_t)();

typedef	unsigned int(*getCallStatus_t)();
typedef	unsigned int(*relayReliableEvent_t)();

typedef	unsigned int(*addCallee_t)();

typedef	unsigned int(*enableRelayDTMFReceiving_t)();
typedef	unsigned int(*addToMediaProcessor_t)();
typedef	unsigned int(*removeFromMediaProcessor_t)();

typedef	unsigned int(*streamsSetReceiving_t)();

typedef	unsigned int(*clearExtLocalTag_t)();
typedef	unsigned int(*setExtLocalTag_t)();

typedef	unsigned int(*setLastReq_t)();

typedef	unsigned int(*testSDPConnectionAddress_t)();

///////////////////////////////////////////////////////////
static stopCall_t					g_stopCall = NULL;
static disconnect_t					g_disconnect = NULL;
static putOnHold_t					g_putOnHold = NULL;
static resumeHeld_t					g_resumeHeld = NULL;

static getCallStatus_t				g_getCallStatus = NULL;
static relayReliableEvent_t			g_relayReliableEvent = NULL;

static addCallee_t					g_addCallee = NULL;

static enableRelayDTMFReceiving_t	g_enableRelayDTMFReceiving = NULL;
static addToMediaProcessor_t		g_addToMediaProcessor = NULL;
static removeFromMediaProcessor_t	g_removeFromMediaProcessor = NULL;

static streamsSetReceiving_t		g_streamsSetReceiving = NULL;

static clearExtLocalTag_t			g_clearExtLocalTag = NULL;
static setExtLocalTag_t				g_setExtLocalTag = NULL;

static setLastReq_t					g_setLastReq = NULL;

static testSDPConnectionAddress_t	g_testSDPConnectionAddress = NULL;

///////////////////////////////////////////////////////////////
SEMS_TS_API void set_stopCall(stopCall_t p);
SEMS_TS_API void set_disconnect(disconnect_t p);
SEMS_TS_API void set_putOnHold_t(putOnHold_t p);
SEMS_TS_API void set_resumeHeld_t(resumeHeld_t p);

SEMS_TS_API void set_getCallStatus_t(getCallStatus_t p);
SEMS_TS_API void set_relayReliableEvent_t(relayReliableEvent_t p);
SEMS_TS_API void set_addCallee_t(addCallee_t p);

SEMS_TS_API void set_enableRelayDTMFReceiving_t(enableRelayDTMFReceiving_t p);
SEMS_TS_API void set_addToMediaProcessor_t(addToMediaProcessor_t p);
SEMS_TS_API void set_removeFromMediaProcessor_t(removeFromMediaProcessor_t p);

SEMS_TS_API void set_streamsSetReceiving_t(streamsSetReceiving_t p);
SEMS_TS_API void set_clearExtLocalTag_t(clearExtLocalTag_t p);
SEMS_TS_API void set_setExtLocalTag_t(setExtLocalTag_t p);

SEMS_TS_API void set_setLastReq_t(setLastReq_t p);
SEMS_TS_API void set_testSDPConnectionAddress_t(testSDPConnectionAddress_t p);
