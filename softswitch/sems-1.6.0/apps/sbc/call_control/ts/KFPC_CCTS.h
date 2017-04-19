#ifndef _KFPC_CCTS_h_
#define _KFPC_CCTS_h_

#include "AmArg.h"
#include "AmApi.h"
#include "AmPlugIn.h"
#include "SBCCallLeg.h"
//#include "SBCDSMInstance.h"
#include "ExtendedCCInterface.h"

#define TRACE DBG

class KFPC_CCTSModule: public AmObject /* passing through DI */, public AmDynInvoke, public ExtendedCCInterface
{
  private:

    static KFPC_CCTSModule* _instance;

//    SBCDSMInstance* getDSMInstance(SBCCallProfile &profile);
//    void deleteDSMInstance(SBCCallProfile &profile);
//    void resetDSMInstance(SBCCallProfile &profile);

  public:

    KFPC_CCTSModule() { }
    virtual ~KFPC_CCTSModule() { }
    static KFPC_CCTSModule* instance();

    virtual void invoke(const string& method, const AmArg& args, AmArg& ret);
    virtual int onLoad() { TRACE(MOD_NAME " call control module loaded.\n"); return 0; }
    virtual void onUnload() { TRACE(MOD_NAME " unloading...\n"); }

    // CC interface
    bool init(SBCCallLeg *call, const map<string, string> &values);
    CCChainProcessing onInitialInvite(SBCCallLeg *call, InitialInviteHandlerParams &params);
    CCChainProcessing onBLegRefused(SBCCallLeg *call, const AmSipReply& reply);
    void onDestroyLeg(SBCCallLeg *call);
    void onStateChange(SBCCallLeg *call, const CallLeg::StatusChangeCause &cause);
    CCChainProcessing onInDialogRequest(SBCCallLeg *call, const AmSipRequest &req);
    CCChainProcessing onInDialogReply(SBCCallLeg *call, const AmSipReply &reply);
    CCChainProcessing onEvent(SBCCallLeg *call, AmEvent *e);
    CCChainProcessing onDtmf(SBCCallLeg *call, int event, int duration);
    CCChainProcessing putOnHold(SBCCallLeg *call);
    CCChainProcessing resumeHeld(SBCCallLeg *call, bool send_reinvite);
    CCChainProcessing createHoldRequest(SBCCallLeg *call, AmSdp &sdp);
    CCChainProcessing handleHoldReply(SBCCallLeg *call, bool succeeded);
    int relayEvent(SBCCallLeg *call, AmEvent *e);

    // simple relay
    bool init(SBCCallProfile &profile, SimpleRelayDialog *relay, void *&user_data);
    void initUAC(const AmSipRequest &req, void *user_data);
    void initUAS(const AmSipRequest &req, void *user_data);
    void finalize(void *user_data);
    void onSipRequest(const AmSipRequest& req, void *user_data);
    void onSipReply(const AmSipRequest& req,
		    const AmSipReply& reply,
		    AmBasicSipDialog::Status old_dlg_status,
		    void *user_data);
    void onB2BRequest(const AmSipRequest& req, void *user_data);
    void onB2BReply(const AmSipReply& reply, void *user_data);
};

class KFPC_CCTSFactory : public AmDynInvokeFactory
{
  public:
    KFPC_CCTSFactory(const string& name): AmDynInvokeFactory(name) {}

    virtual AmDynInvoke* getInstance() { return KFPC_CCTSModule::instance(); }
    virtual int onLoad() { return KFPC_CCTSModule::instance()->onLoad(); }
    virtual void onUnload() { KFPC_CCTSModule::instance()->onUnload(); }
};


#endif
