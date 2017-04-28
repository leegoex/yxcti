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

#include "kfpc_sipserver_api.h"

SEMS_TS_API void OnStart(const char* callid,const char* remote_tag,const char* local_tag,void* pCallLeg);
SEMS_TS_API void OnInvite(const char* callid, void* pCallLeg,
	KFPC_From_t*	pFrom,
	KFPC_To_t*		pTo,
	KFPC_Receive_Info_t*	pReceive_Info,
	KFPC_SdpInfo_t* pSdpInfo);


SEMS_TS_API void OnSessionStart(void* pCallLeg,unsigned long long TSCallID);
SEMS_TS_API void OnRinging(void* pCallLeg,unsigned long long TSCallID);
SEMS_TS_API void OnEarlySession(void* pCallLeg, unsigned long long TSCallID);
SEMS_TS_API void OnFailedCall(void* pCallLeg, unsigned long long TSCallID);
SEMS_TS_API void OnSipRequest(void* pCallLeg, unsigned long long TSCallID);
SEMS_TS_API void OnSipReply(void* pCallLeg, unsigned long long TSCallID);
SEMS_TS_API void OnBeforeDestroy(void* pCallLeg, unsigned long long TSCallID);

SEMS_TS_API void OnHangup(void* pCallLeg, unsigned long long TSCallID);
SEMS_TS_API void OnHold(void* pCallLeg, unsigned long long TSCallID);
SEMS_TS_API void OnUnHold(void* pCallLeg, unsigned long long TSCallID);

SEMS_TS_API void OnB2BOtherRequest(void* pCallLeg, unsigned long long TSCallID);
SEMS_TS_API void OnB2BOtherReply(void* pCallLeg, unsigned long long TSCallID);
SEMS_TS_API void OnB2BOtherBye(void* pCallLeg, unsigned long long TSCallID);

SEMS_TS_API void OnSessionTimeout(void* pCallLeg, unsigned long long TSCallID);
SEMS_TS_API void OnRtpTimeout(void* pCallLeg, unsigned long long TSCallID);
SEMS_TS_API void OnRemoteDisappeared(void* pCallLeg, unsigned long long TSCallID);

SEMS_TS_API void OnKey(void* pCallLeg, unsigned long long TSCallID) {}
SEMS_TS_API void OnTimer(void* pCallLeg, unsigned long long TSCallID) {}

SEMS_TS_API void OnNoAudio(void* pCallLeg, unsigned long long TSCallID) {}
SEMS_TS_API void OnPlaylistSeparator(void* pCallLeg, unsigned long long TSCallID) {}

SEMS_TS_API void OnB2BEvent(void* pCallLeg, unsigned long long TSCallID) {}

SEMS_TS_API void OnStartup();
SEMS_TS_API void OnReload();
SEMS_TS_API void OnSystem();
SEMS_TS_API void OnDestroy();

SEMS_TS_API void OnSIPSubscription() {}

SEMS_TS_API void OnInitialInvite() {}
SEMS_TS_API void OnStateChange(void* pCallLeg, unsigned long long TSCallID) {}
SEMS_TS_API void OnBLegRefused(void* pCallLeg, unsigned long long TSCallID) {}

SEMS_TS_API void OnInDialogRequest(void* pCallLeg, unsigned long long TSCallID) {}
SEMS_TS_API void OnInDialogReply(void* pCallLeg, unsigned long long TSCallID) {}

SEMS_TS_API void OnEvent(void* pCallLeg, unsigned long long TSCallID) {}
SEMS_TS_API void OnDtmf(void* pCallLeg, unsigned long long TSCallID,int event, int duration) {}

SEMS_TS_API void OnputOnHold(void* pCallLeg, unsigned long long TSCallID) {}
SEMS_TS_API void OnresumeHeld(void* pCallLeg, unsigned long long TSCallID,bool send_reinvite) {}
SEMS_TS_API void OncreateHoldRequest(void* pCallLeg, unsigned long long TSCallID) {}
SEMS_TS_API void OnhandleHoldReply(void* pCallLeg, unsigned long long TSCallID,bool succeeded) {}



typedef	unsigned int (*stopCall_t)(const char* callid, const char* remote_tag, const char* local_tag, void* pCallLeg,unsigned int reason, const char *desc);
typedef	unsigned int(*disconnect_t)(bool hold_remote, bool preserve_media_session);
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

typedef void(*setTSCallID_sync_t)(void* pCallLeg,unsigned long long CallID);

typedef unsigned int(*send180Ringing_t)();
typedef unsigned int(*send200OK_t)();
typedef unsigned int(*sendBye_t)();

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
static setTSCallID_sync_t			g_setTSCallID_sync = NULL;

static send180Ringing_t             g_send180Ringing = NULL;
static send200OK_t                  g_send200OK = NULL;
static sendBye_t                    g_sendBye = NULL;

///////////////////////////////////////////////////////////////
SEMS_TS_API void set_stopCall(stopCall_t p) { g_stopCall = p; }
SEMS_TS_API void set_disconnect(disconnect_t p) { g_disconnect = p; }
SEMS_TS_API void set_putOnHold_t(putOnHold_t p) { g_putOnHold = p; }
SEMS_TS_API void set_resumeHeld_t(resumeHeld_t p) { g_resumeHeld = p; }

SEMS_TS_API void set_getCallStatus_t(getCallStatus_t p) { g_getCallStatus = p; }
SEMS_TS_API void set_relayReliableEvent_t(relayReliableEvent_t p) { g_relayReliableEvent = p; }
SEMS_TS_API void set_addCallee_t(addCallee_t p) {}

SEMS_TS_API void set_enableRelayDTMFReceiving_t(enableRelayDTMFReceiving_t p) {}
SEMS_TS_API void set_addToMediaProcessor_t(addToMediaProcessor_t p) {}
SEMS_TS_API void set_removeFromMediaProcessor_t(removeFromMediaProcessor_t p) {}

SEMS_TS_API void set_streamsSetReceiving_t(streamsSetReceiving_t p) {}
SEMS_TS_API void set_clearExtLocalTag_t(clearExtLocalTag_t p) {}
SEMS_TS_API void set_setExtLocalTag_t(setExtLocalTag_t p) {}

SEMS_TS_API void set_setLastReq_t(setLastReq_t p) {}
SEMS_TS_API void set_testSDPConnectionAddress_t(testSDPConnectionAddress_t p) {}
SEMS_TS_API void set_setTSCallID_sync(setTSCallID_sync_t p) { g_setTSCallID_sync = p; }

SEMS_TS_API void set_send180Ringing_t(send180Ringing_t p) { g_send180Ringing = p;  }
SEMS_TS_API void set_send200OK_t(send200OK_t p) { g_send200OK = p;  }
SEMS_TS_API void set_sendBye_t(sendBye_t p) { g_sendBye = p; }
