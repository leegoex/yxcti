#include "log.h"
#include "KFPC_CCTS.h"
/// sems_ts_api.h
#include "ss_ts/sems_ts_api.h"
#include "AmAdvancedAudio.h"
/// end

static const string data_var_name(MOD_NAME "::data");

EXPORT_PLUGIN_CLASS_FACTORY(KFPC_CCTSFactory, MOD_NAME);

KFPC_CCTSModule* KFPC_CCTSModule::_instance = 0;

KFPC_CCTSModule* KFPC_CCTSModule::instance()
{
    if (!_instance) _instance = new KFPC_CCTSModule();
    return _instance;
}

void KFPC_CCTSModule::invoke(const string& method, const AmArg& args, AmArg& ret)
{
  TRACE(MOD_NAME " %s(%s)\n", method.c_str(), AmArg::print(args).c_str());

  if ((method == "start") || (method == "connect") || (method == "end")) {
    return; // FIXME: advertise that the interface shouldn't be used
  }
  else if(method == "_list"){
    ret.push("start");
    ret.push("connect");
    ret.push("end");
  }
  else if (method == "getExtendedInterfaceHandler") {
    ret.push((AmObject*)this);
  }
  else
    throw AmDynInvoke::NotImplemented(method);
}

int KFPC_CCTSModule::onLoad()
{
	set_stopCall(stopCall);
	set_disconnect(disconnect);
	set_putOnHold_t(putOnHold);
	set_resumeHeld_t(resumeHeld);

	set_getCallStatus_t(getCallStatus);
	set_relayReliableEvent_t(relayReliableEvent);
	set_addCallee_t(addCallee);

	set_enableRelayDTMFReceiving_t(enableRelayDTMFReceiving);
	set_addToMediaProcessor_t(addToMediaProcessor);
	set_removeFromMediaProcessor_t(removeFromMediaProcessor);

	set_streamsSetReceiving_t(streamsSetReceiving);
	set_clearExtLocalTag_t(clearExtLocalTag);
	set_setExtLocalTag_t(setExtLocalTag);

	set_setLastReq_t(setLastReq);
	set_testSDPConnectionAddress_t(testSDPConnectionAddress);
	
	set_send180Ringing_t(send180Ringing);
	set_send200OK_t(send200OK);
	set_sendBye_t(sendBye);
	
	OnStartup();
	
	return 0;
}

void KFPC_CCTSModule::onUnload()
{
//	OnDestroy();
}

/*SBCDSMInstance* KFPC_CCTSModule::getDSMInstance(SBCCallProfile &profile)
{
  SBCVarMapIteratorT i = profile.cc_vars.find(data_var_name);
  if (i != profile.cc_vars.end())
    return dynamic_cast<SBCDSMInstance*>(i->second.asObject());

  return NULL;
}

void KFPC_CCTSModule::deleteDSMInstance(SBCCallProfile &profile)
{
  SBCVarMapIteratorT i = profile.cc_vars.find(data_var_name);
  if (i != profile.cc_vars.end()) {
    SBCDSMInstance* h = dynamic_cast<SBCDSMInstance*>(i->second.asObject());
    if (h) delete h;
    profile.cc_vars.erase(i);
  }
}

void KFPC_CCTSModule::resetDSMInstance(SBCCallProfile &profile)
{
  SBCVarMapIteratorT i = profile.cc_vars.find(data_var_name);
  if (i != profile.cc_vars.end()) {
    profile.cc_vars.erase(i);
  }
}*/

bool KFPC_CCTSModule::init(SBCCallLeg *call, const map<string, string> &values)
{
  DBG("ExtCC: init - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");

  /*SBCCallProfile &profile = call->getCallProfile();
  resetDSMInstance(profile); // just forget the handler if already set

  // if (!call->isALeg()) return;

  // create DSM handler if necessary (with evaluated configuration)
  try {
    SBCDSMInstance* h = new SBCDSMInstance(call, values);
    profile.cc_vars[data_var_name] = (AmObject*)h;
  } catch (const string& e) {
    ERROR("initializing DSM Call control module: '%s'\n", e.c_str());
    return false;
  } catch (...) {
    ERROR("initializing DSM Call control module\n");
    return false;
  }*/

  /// sems_ts_api.h
  OnStart(call->dlg->getCallid().c_str(), call->dlg->getRemoteTag().c_str(), call->dlg->getLocalTag().c_str(), call);
  /// end

  return true;
}

#define GET_DSM_INSTANCE				      \
  SBCDSMInstance* h = getDSMInstance(call->getCallProfile()); \
  if (NULL == h)					      \
    return StopProcessing;

#define GET_DSM_INSTANCE_VOID						\
  SBCDSMInstance* h = getDSMInstance(call->getCallProfile());		\
  if (NULL == h) {							\
    ERROR("DSM instance not found for call leg\n");			\
    return;/* todo: throw exception? */					\
  }


  
CCChainProcessing KFPC_CCTSModule::onInitialInvite(SBCCallLeg *call, InitialInviteHandlerParams &params)
{
  DBG("ExtCC: onInitialInvite - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->onInitialInvite(call, params);

  DBG("ExtCC: onInitialInvite - %s --- %s\n", params.original_invite->from.c_str(), params.original_invite->to.c_str());
  DBG("ExtCC: onInitialInvite - %s --- %s\n", call->dlg->getRemoteParty().c_str(), call->dlg->getLocalParty().c_str());
  DBG("ExtCC: onInitialInvite - %s --- %s\n", call->dlg->getRemoteUri().c_str(), call->dlg->getLocalUri().c_str());
  
  /// sems_ts_api.h
  KFPC_From_t         remote;
  KFPC_To_t           local;
  KFPC_Receive_Info_t recvInfo;
  KFPC_SdpInfo_t      sdpInfo;
  
  char remote_host[KFPC_SIP_SER_MAX_HOST_LEN]    = {0};
  char remote_port[KFPC_SIP_SER_MAX_HOST_LEN]    = {0};
  sscanf(call->dlg->getRemoteUri().c_str(), "%*[^@]@%[^:]:%[^;]", remote_host, remote_port);
  
  remote.UserInfo        = "";
  remote.HostPort.Host   = remote_host;
  remote.HostPort.Port   = atoi(remote_port);
  remote.DisplayName     = "";
  remote.Tag             = call->dlg->getRemoteTag();
  
  char local_host[KFPC_SIP_SER_MAX_HOST_LEN]    = {0};
  char local_port[KFPC_SIP_SER_MAX_HOST_LEN]    = {0};
  sscanf(call->dlg->getLocalUri().c_str(), "%*[^@]@%[^:]:%[^;]", local_host, local_port);
  
  local.UserInfo         = call->dlg->getUser();
  local.HostPort.Host    = local_host;
  local.HostPort.Port    = atoi(local_port);
  local.DisplayName      = "";
  local.Tag              = call->dlg->getLocalTag();
  
  recvInfo.FromIp        = params.original_invite->remote_ip;
  recvInfo.FromPort      = params.original_invite->remote_port;
  recvInfo.InterfaceIp   = params.original_invite->local_ip;
  recvInfo.InterfacePort = params.original_invite->local_port;
  
  const AmSdp& sdp = call->dlg->getRemoteSdp();
  
  sdpInfo.Address	= sdp.conn.address;
  sdpInfo.MediaNum   = sdp.media.size();

  for(int i = 0; (i < sdp.media.size() && i < KFPC_SIP_SER_MAX_STREAM_COUNT); ++i)
  {	
	  sdpInfo.SdpMedia[i].Port               = sdp.media[i].port;
	  sdpInfo.SdpMedia[i].MediaType          = (KFPC_MediaType_t)sdp.media[i].type;
	  sdpInfo.SdpMedia[i].TransportProto     = (KFPC_TransportProto_t)sdp.media[i].transport;

	  if(sdp.media[i].send && sdp.media[i].recv)
		  sdpInfo.SdpMedia[i].SendRecvMode   = KFPC_SendRecvMode_Sendrecv;
	  else if(!sdp.media[i].send && sdp.media[i].recv)
		  sdpInfo.SdpMedia[i].SendRecvMode   = KFPC_SendRecvMode_Recvonly;
	  else if(sdp.media[i].send && !sdp.media[i].recv)
		  sdpInfo.SdpMedia[i].SendRecvMode   = KFPC_SendRecvMode_Sendonly;
	  else
		  sdpInfo.SdpMedia[i].SendRecvMode   = KFPC_SendRecvMode_Inactive;	  


	  sdpInfo.SdpMedia[i].SdpPayloadAttrNum = sdp.media[i].payloads.size();

	  for(int pai = 0; (pai < sdpInfo.SdpMedia[i].SdpPayloadAttrNum && pai < KFPC_SIP_SER_MAX_PAYLOAD_ATTR_COUNT); ++pai)
	  {

		  //sdpInfo.SdpMedia[i].PayloadAttr[pai].AttFieldType = 0;
		  sdpInfo.SdpMedia[i].PayloadAttr[pai].MediaType	= sdp.media[i].payloads[pai].type;
		  sdpInfo.SdpMedia[i].PayloadAttr[pai].RtpPayload   = sdp.media[i].payloads[pai].payload_type;
		  sdpInfo.SdpMedia[i].PayloadAttr[pai].Channel      = 1; 
		  sdpInfo.SdpMedia[i].PayloadAttr[pai].RtpClock     = sdp.media[i].payloads[pai].clock_rate;
		  sdpInfo.SdpMedia[i].PayloadAttr[pai].RtpEnc       = sdp.media[i].payloads[pai].encoding_name;
		  sdpInfo.SdpMedia[i].PayloadAttr[pai].RtpParams    = sdp.media[i].payloads[pai].sdp_format_parameters;
		  sdpInfo.SdpMedia[i].PayloadAttr[pai].FmtpString   = sdp.media[i].payloads[pai].format;

		  DBG("MediaType:%u,RtpPayload:%u,Channel:%u,RtpClock:%u,RtpEnc:%s,RtpParams:%s,FmtpString:%s",
			  //sdpInfo.SdpMedia[i].PayloadAttr[pai].AttFieldType,
			  sdpInfo.SdpMedia[i].PayloadAttr[pai].MediaType,
			  sdpInfo.SdpMedia[i].PayloadAttr[pai].RtpPayload,
			  sdpInfo.SdpMedia[i].PayloadAttr[pai].Channel,
			  sdpInfo.SdpMedia[i].PayloadAttr[pai].RtpClock,
			  sdpInfo.SdpMedia[i].PayloadAttr[pai].RtpEnc.c_str(),
			  sdpInfo.SdpMedia[i].PayloadAttr[pai].RtpParams.c_str(),
			  sdpInfo.SdpMedia[i].PayloadAttr[pai].FmtpString.c_str()

			  );
	  }
  }
  
  OnInvite(call->dlg->getCallid().c_str(), 
	call,
	&remote,
	&local,
	&recvInfo,
	&sdpInfo);
  /// end

  return ContinueProcessing;
}

void KFPC_CCTSModule::onStateChange(SBCCallLeg *call, const CallLeg::StatusChangeCause &cause) {
  DBG("ExtCC: onStateChange - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE_VOID;
//  h->onStateChange(call, cause);

  /// sems_ts_api.h
  
  switch(call->getCallStatus()) {
  case CallLeg::Ringing:
    OnRinging(call, call->getTSCallID());
    break;
  case CallLeg::Connected:
    OnSessionStart(call, call->getTSCallID());
    break;
  case CallLeg::Disconnected:
    OnHangup(call, call->getTSCallID());
    break;
  case CallLeg::NoReply:
  case CallLeg::Disconnecting:
    break;
  default:
    break;
  };
  
  switch (cause.reason) {
  case CallLeg::StatusChangeCause::SipReply:
  case CallLeg::StatusChangeCause::SipRequest:
  case CallLeg::StatusChangeCause::Canceled:
  case CallLeg::StatusChangeCause::NoAck:
  case CallLeg::StatusChangeCause::NoPrack:
    break;
  case CallLeg::StatusChangeCause::RtpTimeout: 
    OnRtpTimeout(call, call->getTSCallID()); 
    break;
  case CallLeg::StatusChangeCause::SessionTimeout: 
    OnSessionTimeout(call, call->getTSCallID());
    break;
  default: 
    break;
  };
  /// end
  
};

CCChainProcessing KFPC_CCTSModule::onBLegRefused(SBCCallLeg *call, const AmSipReply& reply)
{
  DBG("ExtCC: onBLegRefused - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->onBLegRefused(call, reply);
  return ContinueProcessing;
}
void KFPC_CCTSModule::onDestroyLeg(SBCCallLeg *call) {
  DBG("ExtCC: onDestroyLeg - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
  DBG("TODO: call DSM event?\n");
  
  /// sems_ts_api.h
  OnBeforeDestroy(call, call->getTSCallID());
  /// end
  
//  deleteDSMInstance(call->getCallProfile());
}

/** called from A/B leg when in-dialog request comes in */
CCChainProcessing KFPC_CCTSModule::onInDialogRequest(SBCCallLeg *call, const AmSipRequest &req) {
  DBG("ExtCC: onInDialogRequest - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->onInDialogRequest(call, req);

  /// sems_ts_api.h
  OnSipRequest(call, call->getTSCallID());
  /// end
  
  return ContinueProcessing;
}

CCChainProcessing KFPC_CCTSModule::onInDialogReply(SBCCallLeg *call, const AmSipReply &reply) {
  DBG("ExtCC: onInDialogReply - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->onInDialogReply(call, reply);

  /// sems_ts_api.h
  OnSipReply(call, call->getTSCallID());
  /// end
  
  return ContinueProcessing;
}

/** called before any other processing for the event is done */
CCChainProcessing KFPC_CCTSModule::onEvent(SBCCallLeg *call, AmEvent *e) {
  DBG("ExtCC: onEvent - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->onEvent(call, e);

  /// sems_ts_api.h
  B2BEvent* b2b_ev = dynamic_cast<B2BEvent*>(e);
  if(b2b_ev && b2b_ev->ev_type == B2BEvent::B2BApplication) {
    OnB2BEvent(call, call->getTSCallID());
    return ContinueProcessing;
  }
  
  if(b2b_ev && b2b_ev->ev_type == B2BEvent::B2BCore) {
    B2BSipRequestEvent* b2b_req_ev = dynamic_cast<B2BSipRequestEvent*>(b2b_ev);
    if (b2b_req_ev) {
      OnB2BOtherRequest(call, call->getTSCallID());
	  return ContinueProcessing;
    } else {
      B2BSipReplyEvent* b2b_reply_ev = dynamic_cast<B2BSipReplyEvent*>(b2b_ev);
      if (b2b_reply_ev) {
	    OnB2BOtherReply(call, call->getTSCallID());
      }
    }
  }
  
  AmPluginEvent* plugin_event = dynamic_cast<AmPluginEvent*>(e);
  if(plugin_event && plugin_event->name == "timer_timeout") {
    int timer_id = plugin_event->data.get(0).asInt();
    OnTimer(call, call->getTSCallID());
    return ContinueProcessing;
  }
  
  AmPlaylistSeparatorEvent* sep_ev = dynamic_cast<AmPlaylistSeparatorEvent*>(e);
  if (sep_ev) {
    OnPlaylistSeparator(call, call->getTSCallID());
    return ContinueProcessing;
  }
  
  AmAudioEvent* audio_event = dynamic_cast<AmAudioEvent*>(e);
  if(audio_event) {
    if(audio_event->event_id == AmAudioEvent::noAudio)
		OnNoAudio(call, call->getTSCallID());
    return ContinueProcessing;
  }
  /// end
  
  return ContinueProcessing;
}

CCChainProcessing KFPC_CCTSModule::onDtmf(SBCCallLeg *call, int event, int duration) { 
  DBG("ExtCC: onDtmf(%i;%i) - call instance: '%p' isAleg==%s\n",
      event, duration, call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->onDtmf(call, event, duration);

  /// sems_ts_api.h
  OnKey(call, call->getTSCallID());
  /// end
  
  return ContinueProcessing;
}

// hold related functionality
CCChainProcessing KFPC_CCTSModule::putOnHold(SBCCallLeg *call) {
  DBG("ExtCC: putOnHold - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->putOnHold(call);

  /// sems_ts_api.h
  OnHold(call, call->getTSCallID());
  /// end
  
  return ContinueProcessing;
}

CCChainProcessing KFPC_CCTSModule::resumeHeld(SBCCallLeg *call, bool send_reinvite) {
  DBG("ExtCC: resumeHeld - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->resumeHeld(call, send_reinvite);

  /// sems_ts_api.h
  OnUnHold(call, call->getTSCallID());
  /// end
  
  return ContinueProcessing;
}

CCChainProcessing KFPC_CCTSModule::createHoldRequest(SBCCallLeg *call, AmSdp &sdp) {
  DBG("ExtCC: createHoldRequest - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->createHoldRequest(call, sdp);
  return ContinueProcessing;
}

CCChainProcessing KFPC_CCTSModule::handleHoldReply(SBCCallLeg *call, bool succeeded) {
  DBG("ExtCC: handleHoldReply - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->handleHoldReply(call, succeeded);
  return ContinueProcessing;
}

/** Possibility to influence messages relayed to the B2B peer leg.
    return value:
    - lower than 0 means error (returned upstream, the one
    returning error is responsible for destrying the event instance)
    - greater than 0 means "stop processing and return 0 upstream"
    - equal to 0 means "continue processing" */
int KFPC_CCTSModule::relayEvent(SBCCallLeg *call, AmEvent *e) {
  // todo
  return 0;
}

// using extended CC modules with simple relay

struct RelayUserData {
  SimpleRelayDialog *relay;
  SBCCallProfile& profile;
  RelayUserData(SimpleRelayDialog *relay, SBCCallProfile& profile)
    : relay(relay), profile(profile) { }
};


bool KFPC_CCTSModule::init(SBCCallProfile& profile, SimpleRelayDialog *relay, void *&user_data) {
  /*SBCDSMInstance* h = getDSMInstance(profile);
  if (NULL == h) {
    user_data = NULL;
    return false;
  }

  if (!h->init(profile, relay)) {
    return false;
  }*/

  user_data = new RelayUserData(relay, profile);
  return true;
}

#define GET_USER_DATA				\
  if (NULL == user_data)			\
    return;					\
  						\
  RelayUserData* ud= (RelayUserData*)user_data;		\
  SBCDSMInstance* h = getDSMInstance(ud->profile);	\
  if (NULL == h) {					\
    ERROR("SBC DSM instance disappeared, huh?\n");	\
    return;						\
  }

void KFPC_CCTSModule::initUAC(const AmSipRequest &req, void *user_data) {
//  GET_USER_DATA;
//  h->initUAC(ud->profile, ud->relay, req);
}

void KFPC_CCTSModule::initUAS(const AmSipRequest &req, void *user_data) {
//  GET_USER_DATA;
//  h->initUAS(ud->profile, ud->relay, req);
}

void KFPC_CCTSModule::finalize(void *user_data) {
//  GET_USER_DATA;
//  h->finalize(ud->profile, ud->relay);
//  delete ud;
}

void KFPC_CCTSModule::onSipRequest(const AmSipRequest& req, void *user_data) {
//  GET_USER_DATA;
//  h->onSipRequest(ud->profile, ud->relay, req);
}

void KFPC_CCTSModule::onSipReply(const AmSipRequest& req,
			     const AmSipReply& reply,
			     AmBasicSipDialog::Status old_dlg_status,
			     void *user_data) {
//  GET_USER_DATA;
//  h->onSipReply(ud->profile, ud->relay, req, reply, old_dlg_status);
}

void KFPC_CCTSModule::onB2BRequest(const AmSipRequest& req, void *user_data) {
//  GET_USER_DATA;
//  h->onB2BRequest(ud->profile, ud->relay, req);
}

void KFPC_CCTSModule::onB2BReply(const AmSipReply& reply, void *user_data) {
//  GET_USER_DATA;
//  h->onB2BReply(ud->profile, ud->relay, reply);
}

/// sems_ts_api.h
void KFPC_CCTSModule::onCallFailed(SBCCallLeg *call, CallLeg::CallFailureReason reason, const AmSipReply *reply)
{
  OnFailedCall(call, call->getTSCallID());
}
// -- ts call back --
unsigned int KFPC_CCTSModule::stopCall(const char* callid, const char* remote_tag, const char* local_tag, void* pCallLeg,unsigned int reason, const char *desc)
{
	DBG("ExtCC: stopCall\n");
	return 0;
}

unsigned int KFPC_CCTSModule::disconnect(bool hold_remote, bool preserve_media_session)
{
	DBG("ExtCC: disconnect\n");
	return 0;
}

unsigned int KFPC_CCTSModule::putOnHold()
{
	DBG("ExtCC: putOnHold\n");
	return 0;
}

unsigned int KFPC_CCTSModule::resumeHeld()
{
	DBG("ExtCC: resumeHeld\n");
	return 0;
}

unsigned int KFPC_CCTSModule::getCallStatus()
{
	DBG("ExtCC: getCallStatus\n");
	return 0;
}

unsigned int KFPC_CCTSModule::relayReliableEvent()
{
	DBG("ExtCC: relayReliableEvent\n");
	return 0;
}

unsigned int KFPC_CCTSModule::addCallee()
{
	DBG("ExtCC: addCallee\n");
	return 0;
}

unsigned int KFPC_CCTSModule::enableRelayDTMFReceiving()
{
	DBG("ExtCC: enableRelayDTMFReceiving\n");
	return 0;
}

unsigned int KFPC_CCTSModule::addToMediaProcessor()
{
	DBG("ExtCC: addToMediaProcessor\n");
	return 0;
}

unsigned int KFPC_CCTSModule::removeFromMediaProcessor()
{
	DBG("ExtCC: removeFromMediaProcessor\n");
	return 0;
}

unsigned int KFPC_CCTSModule::streamsSetReceiving()
{
	DBG("ExtCC: streamsSetReceiving\n");
	return 0;
}

unsigned int KFPC_CCTSModule::clearExtLocalTag()
{
	DBG("ExtCC: clearExtLocalTag\n");
	return 0;
}

unsigned int KFPC_CCTSModule::setExtLocalTag()
{
	DBG("ExtCC: setExtLocalTag\n");
	return 0;
}

unsigned int KFPC_CCTSModule::setLastReq()
{
	DBG("ExtCC: setLastReq\n");
	return 0;
}

unsigned int KFPC_CCTSModule::testSDPConnectionAddress()
{
	DBG("ExtCC: testSDPConnectionAddress\n");
	return 0;
}

unsigned int KFPC_CCTSModule::setTSCallID_sync(void* pCallLeg, unsigned long long CallID)
{
	DBG("ExtCC: setTSCallID_sync - ts server call id %lld\n", CallID);
	if(pCallLeg == NULL) {
		ERROR("ExtCC: setTSCallID_sync - pCallLeg is a null pointer\n");
	}
	SBCCallLeg *call = (SBCCallLeg*)pCallLeg;
	if(call) {
		call->setTSCallID(CallID);
	}
	return 0;
}

unsigned int KFPC_CCTSModule::send180Ringing()
{
	return 0;
}

unsigned int KFPC_CCTSModule::send200OK()
{
	return 0;
}

unsigned int KFPC_CCTSModule::sendBye()
{
	return 0;
}

/// end
