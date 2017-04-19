#include "log.h"
#include "KFPC_CCTS.h"

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
  return StopProcessing;
}

void KFPC_CCTSModule::onStateChange(SBCCallLeg *call, const CallLeg::StatusChangeCause &cause) {
  DBG("ExtCC: onStateChange - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE_VOID;
//  h->onStateChange(call, cause);
};

CCChainProcessing KFPC_CCTSModule::onBLegRefused(SBCCallLeg *call, const AmSipReply& reply)
{
  DBG("ExtCC: onBLegRefused - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->onBLegRefused(call, reply);
  return StopProcessing;
}
void KFPC_CCTSModule::onDestroyLeg(SBCCallLeg *call) {
  DBG("ExtCC: onDestroyLeg - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
  DBG("TODO: call DSM event?\n");
//  deleteDSMInstance(call->getCallProfile());
}

/** called from A/B leg when in-dialog request comes in */
CCChainProcessing KFPC_CCTSModule::onInDialogRequest(SBCCallLeg *call, const AmSipRequest &req) {
  DBG("ExtCC: onInDialogRequest - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->onInDialogRequest(call, req);
  return StopProcessing;
}

CCChainProcessing KFPC_CCTSModule::onInDialogReply(SBCCallLeg *call, const AmSipReply &reply) {
  DBG("ExtCC: onInDialogReply - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->onInDialogReply(call, reply);
  return StopProcessing;
}

/** called before any other processing for the event is done */
CCChainProcessing KFPC_CCTSModule::onEvent(SBCCallLeg *call, AmEvent *e) {
  DBG("ExtCC: onEvent - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->onEvent(call, e);
  return StopProcessing;
}

CCChainProcessing KFPC_CCTSModule::onDtmf(SBCCallLeg *call, int event, int duration) { 
  DBG("ExtCC: onDtmf(%i;%i) - call instance: '%p' isAleg==%s\n",
      event, duration, call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->onDtmf(call, event, duration);
  return StopProcessing;
}

// hold related functionality
CCChainProcessing KFPC_CCTSModule::putOnHold(SBCCallLeg *call) {
  DBG("ExtCC: putOnHold - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->putOnHold(call);
  return StopProcessing;
}

CCChainProcessing KFPC_CCTSModule::resumeHeld(SBCCallLeg *call, bool send_reinvite) {
  DBG("ExtCC: resumeHeld - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->resumeHeld(call, send_reinvite);
  return StopProcessing;
}

CCChainProcessing KFPC_CCTSModule::createHoldRequest(SBCCallLeg *call, AmSdp &sdp) {
  DBG("ExtCC: createHoldRequest - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->createHoldRequest(call, sdp);
  return StopProcessing;
}

CCChainProcessing KFPC_CCTSModule::handleHoldReply(SBCCallLeg *call, bool succeeded) {
  DBG("ExtCC: handleHoldReply - call instance: '%p' isAleg==%s\n", call, call->isALeg()?"true":"false");
//  GET_DSM_INSTANCE;
//  return h->handleHoldReply(call, succeeded);
  return StopProcessing;
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
