#include "KFPC_EH_ID2Str.h"
//#include <aglib.h>
#include <string.h>
//#include "siplib.h"
//#include "gclib.h"
#include "KFPC_TServerDef.h"
//#include "KFPC_EH_Def.h"

//const char* ToneIDToStr(int ID)
//{
//	switch(ID)
//	{
//	case TONEID_BUSY:return "TONEID_BUSY";
//	case TONEID_DIAL:return "TONEID_DIAL";
//	case TONEID_RINGBACK:return "TONEID_RINGBACK";
//	case TONEID_HOWLER:return "TONEID_HOWLER";
//	case TONEID_BUSY1:return "TONEID_BUSY1";
//	case TONEID_RINGBACK2:return "TONEID_RINGBACK2";
//	case TONEID_FAX1:return "TONEID_FAX1";
//	case TONEID_FAX2:return "TONEID_FAX2";
//	case TONEID_HUMAN1:return "TONEID_HUMAN1";
//	case TONEID_HUMAN2:return "TONEID_HUMAN2";
//	case TONEID_USER_BUSY:	return "User_Busy";
//	case TONEID_USER_DIAL:	return "User_Dial";
//	case TONEID_USER_RINGBACK:return "User_RingBack";
//	case TONEID_USER_HOWLER:return "User_Howler";
//	default:
//		{
//			return "TONEID_UNKNOWN";
//		}
//	}
//}
//
//const char* MessageMaskIDToStr(int ID)
//{
//	switch(ID)
//	{
//	case MSMM_OFFHOOK:		return "MSMM_OFFHOOK";
//	case MSMM_RNGOFFHK:		return "MSMM_RNGOFFHK";
//	case MSMM_RNGSTOP:		return "MSMM_RNGSTOP";
//	case MSMM_ONHOOK:		return "MSMM_ONHOOK";
//	case MSMM_HOOKFLASH:	return "MSMM_HOOKFLASH";
//	case MSMM_TERM:			return "MSMM_TERM";
//	case MOMM_RINGS:		return "MOMM_RINGS";
//	case MOMM_RNGOFF:		return "MOMM_RNGOFF";
//	case AGMM_DIGITS:		return "AGMM_DIGITS";
//	case MSMM_RINGS:		return "MSMM_RINGS";
//	case MOMM_CALLERID:		return "MOMM_CALLERID";
//		default:
//			{
//				return "MSMM_UNKNOWN";
//			}
//	}
//
//}
//
//
//
//
//const char* StatusToStr(unsigned char ucStatus)
//{
//	switch(ucStatus){
//	case STATUS_RESET:		return "STATUS_RESET";
//	case STATUS_OUT_OF_SRV:	return "STATUS_OUT_OF_SRV";
//	case STATUS_REQ_STOP:	return "STATUS_REQ_STOP";
//	case STATUS_WORKING:	return "STATUS_WORKING";
//	default: break;
//	}
//	return "unknown state";
//}
//
//const char* SIPReasonStatusToStr(long ccValue)
//{	
//	switch(ccValue){
//	case IPEC_SIPReasonStatus200OK:                           return "200OK";                                
//	case IPEC_SIPReasonStatus400BadRequest:                   return "400BadRequest";
//	case IPEC_SIPReasonStatus401Unauthorized:                 return "401Unauthorized";                   
//	case IPEC_SIPReasonStatus402PaymentRequired:              return "402PaymentRequired";                
//	case IPEC_SIPReasonStatus403Forbidden:                    return "403Forbidden";                      
//	case IPEC_SIPReasonStatus404NotFound:                     return "404NotFound";                       
//	case IPEC_SIPReasonStatus405MethodNotAllowed:             return "405MethodNotAllowed";               
//	case IPEC_SIPReasonStatus406NotAcceptable:                return "406NotAcceptable";                  
//	case IPEC_SIPReasonStatus407ProxyAuthenticationRequired:  return "407ProxyAuthenticationRequired";    
//	case IPEC_SIPReasonStatus408RequestTimeout:               return "408RequestTimeout";
//	case IPEC_SIPReasonStatus410Gone:                         return "410Gone";                           
//	case IPEC_SIPReasonStatus413RequestEntityTooLarge:        return "413RequestEntityTooLarge";          
//	case IPEC_SIPReasonStatus414RequestUriTooLong:            return "414RequestUriTooLong";              
//	case IPEC_SIPReasonStatus415UnsupportedMediaType:         return "415UnsupportedMediaType";           
//	case IPEC_SIPReasonStatus416UnsupportedURIScheme:         return "416UnsupportedURIScheme";           
//	case IPEC_SIPReasonStatus420BadExtension:                 return "420BadExtension";                   
//	case IPEC_SIPReasonStatus421ExtensionRequired:            return "421ExtensionRequired";              
//	case IPEC_SIPReasonStatus423IntervalTooBrief:             return "423IntervalTooBrief";               
//	case IPEC_SIPReasonStatus480TemporarilyUnavailable:       return "480TemporarilyUnavailable";         
//	case IPEC_SIPReasonStatus481CallTransactionDoesNotExist:  return "481CallTransactionDoesNotExist";    
//	case IPEC_SIPReasonStatus482LoopDetected:                 return "482LoopDetected";
//	case IPEC_SIPReasonStatus483TooManyHops:                  return "483TooManyHops";                    
//	case IPEC_SIPReasonStatus484AddressIncomplete:            return "484AddressIncomplete";              
//	case IPEC_SIPReasonStatus485Ambiguous:                    return "485Ambiguous";                      
//	case IPEC_SIPReasonStatus486BusyHere:                     return "486BusyHere";                       
//	case IPEC_SIPReasonStatus487RequestTerminated:            return "487RequestTerminated";              
//	case IPEC_SIPReasonStatus488NotAcceptableHere:            return "488NotAcceptableHere";              
//	case IPEC_SIPReasonStatus491RequestPending:               return "491RequestPending";                 
//	case IPEC_SIPReasonStatus493Undecipherable:               return "493Undecipherable";                 
//	case IPEC_SIPReasonStatus500ServerInternalError:          return "500ServerInternalError";            
//	case IPEC_SIPReasonStatus501NotImplemented:               return "501NotImplemented";                 
//	case IPEC_SIPReasonStatus502BadGateway:                   return "502BadGateway";                     
//	case IPEC_SIPReasonStatus503ServiceUnavailable:           return "503ServiceUnavailable";             
//	case IPEC_SIPReasonStatus504ServerTimeout:                return "504ServerTimeout";                  
//	case IPEC_SIPReasonStatus505VersionNotSupported:          return "505VersionNotSupported";            
//	case IPEC_SIPReasonStatus513MessageTooLarge:              return "513MessageTooLarge";                
//	case IPEC_SIPReasonStatus600BusyEverywhere:               return "600BusyEverywhere";                 
//	case IPEC_SIPReasonStatus603Decline:                      return "603Decline";                        
//	case IPEC_SIPReasonStatus604DoesNotExistAnywhere:         return "604DoesNotExistAnywhere";           
//	case IPEC_SIPReasonStatus606NotAcceptable:                return "606NotAcceptable";                  
//	case IPEC_SIPReasonStatusBYE:                             return "BYE";                               
//	case IPEC_SIPReasonStatusCANCEL:                          return "CANCEL";                            
//	default: return "Cause xxx: Unknown";
//	}
//}

/**
 *	SIP支持语音编码
 */

typedef enum {
	AudioCodec_G711_ALAW_20MS = 0x00,
	AudioCodec_G711_ULAW_20MS = 0x01,
	AudioCodec_G726_16_20MS = 0x02,
	AudioCodec_G726_24_20MS = 0x03,
	AudioCodec_G726_32_20MS = 0x04,
	AudioCodec_G726_40_20MS = 0x05,
	AudioCodec_G727_16_20MS = 0x06,
	AudioCodec_G727_24_16_20MS = 0x07,
	AudioCodec_G727_24_20MS = 0x08,
	AudioCodec_G727_32_16_20MS = 0x09,
	AudioCodec_G727_32_24_20MS = 0x0a,
	AudioCodec_G727_32_20MS = 0x0b,
	AudioCodec_G727_40_16_20MS = 0x0c,
	AudioCodec_G727_40_24_20MS = 0x0d,
	AudioCodec_G727_40_32_20MS = 0x0e,
	AudioCodec_G723_5_3_30MS = 0x0f,
	AudioCodec_G723_6_3_30MS = 0x10,
	AudioCodec_G729_20MS = 0x11,
	AudioCodec_G711_ALAW_30MS = 0x12,
	AudioCodec_iLBC_20MS = 0x13,
	AudioCodec_iLBC_30MS = 0x14,
	AudioCodec_CLEAR_CHANNEL = 0x15,
	AudioCodec_GSM_FR = 0x16,
	AudioCodec_GSM_EFR = 0x17,
	AudioCodec_AMR_475_OA = 0x18,
	AudioCodec_AMR_515_OA = 0x19,/* 25 */
	AudioCodec_AMR_590_OA = 0x1a,
	AudioCodec_AMR_670_OA = 0x1b,
	AudioCodec_AMR_740_OA = 0x1c,
	AudioCodec_AMR_795_OA = 0x1d,
	AudioCodec_AMR_102_OA = 0x1e,/* 30 */
	AudioCodec_AMR_122_OA = 0x1f,
	AudioCodec_AMR_475_BE = 0x20,
	AudioCodec_AMR_515_BE = 0x21,
	AudioCodec_AMR_590_BE = 0x22,
	AudioCodec_AMR_670_BE = 0x23,/* 35 */
	AudioCodec_AMR_740_BE = 0x24,
	AudioCodec_AMR_795_BE = 0x25,
	AudioCodec_AMR_102_BE = 0x26,
	AudioCodec_AMR_122_BE = 0x27,/* 39 */
	AudioCodec_AMR_WB_66_BE = 0x28,
	AudioCodec_AMR_WB_885_BE = 0x29,
	AudioCodec_AMR_WB_1265_BE = 0x2A,
	AudioCodec_AMR_WB_1425_BE = 0x2B,
	AudioCodec_AMR_WB_1585_BE = 0x2C,
	AudioCodec_AMR_WB_1825_BE = 0x2D,
	AudioCodec_AMR_WB_1985_BE = 0x2E,
	AudioCodec_AMR_WB_2305_BE = 0x2F,
	AudioCodec_AMR_WB_2385_BE = 0x30,
	AudioCodec_AMR_WB_66_OA = 0x31,
	AudioCodec_AMR_WB_885_OA = 0x32,
	AudioCodec_AMR_WB_1265_OA = 0x33,
	AudioCodec_AMR_WB_1425_OA = 0x34,
	AudioCodec_AMR_WB_1585_OA = 0x35,
	AudioCodec_AMR_WB_1825_OA = 0x36,
	AudioCodec_AMR_WB_1985_OA = 0x37,
	AudioCodec_AMR_WB_2305_OA = 0x38,
	AudioCodec_AMR_WB_2385_OA = 0x39,
	AudioCodec_SILK_8KSS_20MS = 0x3A, //8K采样 [2015-4-28]
	AudioCodec_SILK_16KSS_20MS = 0x3B,	//16K采样[2015-4-28]
	AudioCodec_OPUS_8KSS_20MS = 0x3C,	//8K采样 [2015-4-28]
	AudioCodec_OPUS_16KSS_20MS = 0x3D, //16K采样[2015-4-28]
	AudioCodec_MaxNum,			//This item is not a valid codec
}eAUDIOCODEC;

static KFPC_AudioCode	KFPC_AudioCodeList[AudioCodec_MaxNum]={
	{"G711_ALAW",		AudioCodec_G711_ALAW_20MS},
	{"G711_ULAW",		AudioCodec_G711_ULAW_20MS},
	{"G726_16",			AudioCodec_G726_16_20MS},
	{"G726_24",			AudioCodec_G726_24_20MS},
	{"G726_32",			AudioCodec_G726_32_20MS},
	{"G726_40",			AudioCodec_G726_40_20MS},
	{"G727_16",			AudioCodec_G727_16_20MS},
	{"G727_24_16",		AudioCodec_G727_24_16_20MS},
	{"G727_24",			AudioCodec_G727_24_20MS},
	{"G727_32_16",		AudioCodec_G727_32_16_20MS},
	{"G727_32_24",		AudioCodec_G727_32_24_20MS},
	{"G727_32",			AudioCodec_G727_32_20MS},
	{"G727_40_16",		AudioCodec_G727_40_16_20MS},
	{"G727_40_24",		AudioCodec_G727_40_24_20MS},
	{"G727_40_32",		AudioCodec_G727_40_32_20MS},
	{"G723_5_3",		AudioCodec_G723_5_3_30MS},
	{"G723_6_3",		AudioCodec_G723_6_3_30MS},
	{"G729",			AudioCodec_G729_20MS},
	{"PCMA_30",			AudioCodec_G711_ALAW_30MS},
	{"iLBC_20",			AudioCodec_iLBC_20MS},
	{"iLBC_30",			AudioCodec_iLBC_30MS},
	{"",				AudioCodec_CLEAR_CHANNEL},
	{"",				AudioCodec_GSM_FR},
	{"",				AudioCodec_GSM_EFR},
	{"",				AudioCodec_AMR_475_OA},
	{"",				AudioCodec_AMR_515_OA},
	{"",				AudioCodec_AMR_590_OA},
	{"",				AudioCodec_AMR_670_OA},
	{"",				AudioCodec_AMR_740_OA},
	{"",				AudioCodec_AMR_795_OA},
	{"",				AudioCodec_AMR_102_OA},
	{"",				AudioCodec_AMR_122_OA},
	{"",				AudioCodec_AMR_475_BE},
	{"",				AudioCodec_AMR_515_BE},
	{"",				AudioCodec_AMR_590_BE},
	{"",				AudioCodec_AMR_670_BE},
	{"",				AudioCodec_AMR_740_BE},
	{"",				AudioCodec_AMR_795_BE},
	{"",				AudioCodec_AMR_102_BE},
	{"",				AudioCodec_AMR_122_BE},
	{"",				AudioCodec_AMR_WB_66_BE},
	{"",				AudioCodec_AMR_WB_885_BE},
	{"",				AudioCodec_AMR_WB_1265_BE},  
	{"",				AudioCodec_AMR_WB_1425_BE},  
	{"",				AudioCodec_AMR_WB_1585_BE},  
	{"",				AudioCodec_AMR_WB_1825_BE},  
	{"",				AudioCodec_AMR_WB_1985_BE},  
	{"",				AudioCodec_AMR_WB_2305_BE},  
	{"",				AudioCodec_AMR_WB_2385_BE},  
	{"",				AudioCodec_AMR_WB_66_OA		 },
	{"",				AudioCodec_AMR_WB_885_OA	},
	{"",				AudioCodec_AMR_WB_1265_OA	},
	{"",				AudioCodec_AMR_WB_1425_OA	},
	{"",				AudioCodec_AMR_WB_1585_OA	},
	{"",				AudioCodec_AMR_WB_1825_OA	},
	{"",				AudioCodec_AMR_WB_1985_OA	},
	{"",				AudioCodec_AMR_WB_2305_OA	},
	{"",				AudioCodec_AMR_WB_2385_OA	},
	{"SILK_8KSS",		AudioCodec_SILK_8KSS_20MS	},
	{"SILK",			AudioCodec_SILK_16KSS_20MS	},
	{"OPUS_8KSS",		AudioCodec_OPUS_8KSS_20MS	},
	{"opus",			AudioCodec_OPUS_16KSS_20MS	}
};

unsigned char StrToAudioCodeID(const char* pCodeID)
{
	for(int i=0;i<AudioCodec_MaxNum;i++)
	{
		if(strcmp(KFPC_AudioCodeList[i].AudioName,pCodeID) == 0)
		{
			return KFPC_AudioCodeList[i].AudioCodeID;
		}
	}

	return -1;
}


//static KFPC_AudioCode	KFPC_AudioCodePayloadList[]={
//	{"G711_ALAW",		8},
//	{"G711_ULAW",		0},
//	{"G726_16",			35},
//	{"G726_24",			36},
//	{"G726_32",			2},
//	{"G726_40",			38},
//	{"G727_16",			39},
//	{"G727_24_16",		40},
//	{"G727_24",			41},
//	{"G727_32_16",		42},
//	{"G727_32_24",		43},
//	{"G727_32",			44},
//	{"G727_40_16",		45},
//	{"G727_40_24",		46},
//	{"G727_40_32",		47},
//	{"G723_5_3",		4},
//	{"G723_6_3",		4},
//	{"G729",			18},
//	{"PCMA_30",			9},
//	{"iLBC_20",			80},
//	{"iLBC_30",			98}
//};

//
//
//unsigned char StrToPayloadID(const char* pCodeID)
//{
//	for(int i=0;i<AudioCodec_MaxNum;i++)
//	{
//		if(strcmp(KFPC_AudioCodePayloadList[i].AudioName,pCodeID) == 0)
//		{
//			return KFPC_AudioCodePayloadList[i].AudioCodeID;
//		}
//	}
//
//	return -1;
//}


//const char* KFPC_PayloadIDToAudioCode(int PayloadID)
//{
//	for(int i=0;i<AudioCodec_MaxNum;i++)
//	{
//		if(KFPC_AudioCodePayloadList[i].AudioCodeID == PayloadID)
//		{
//			return KFPC_AudioCodePayloadList[i].AudioName;
//		}
//	}
//	return "unknown";
//
//}


//
//const char*	TermToStr(unsigned long mask)
//{
//	switch(mask)
//	{
//	case TM_NORMTERM: return  	"NORMTERM";
//	case TM_MAXDTMF : return  	"MAXDTMF";
//	case TM_IDDTIME : return  	"IDDTIME";
//	case TM_MAXTIME : return 	"MAXTIME";
//	case TM_DIGIT   : return 	"DIGIT";
//	case TM_USRSTOP : return  	"USRSTOP"; 
//	case TM_EOD     : return  	"EOD";
//	case TM_TONE    : return  	"TONE";   
//	case TM_BARGEIN : return  	"BARGEIN";
//	case TM_ERROR   : return 	"ERROR";
//	case TM_MAXDATA : return  	"MAXDATA"; 
//	case TM_TIMEOUT : return 	"TIMEOUT";
//	default: return "unkown term";
//
//	}
//}
//
//
//
//const char* OperToStr(int val)
//{
//	switch(val)
//	{
//	case OPER_UNKNOWN:					return "OPER_UNKNOWN";
//	case OPER_PLAY:						return "OPER_PLAY";
//	case OPER_RECORD:					return "OPER_RECORD";
//	case OPER_GETDIG:					return "OPER_GETDIG";
//	case OPER_ACCEPTCALL:				return "OPER_ACCEPTCALL";
//	case OPER_ANSWERCALL:				return "OPER_ANSWERCALL";
//	case OPER_MAKECALL:					return "OPER_MAKECALL";
//	case OPER_DROPCALL:					return "OPER_DROPCALL";
//	case OPER_SETBILLING:				return "OPER_SETBILLING";
//	case OPER_SENDMOREINFO:				return "OPER_SENDMOREINFO";
//	case OPER_DLCACHE:					return "OPER_DLCACHE";
//	case OPER_DLMEM:					return "OPER_DLMEM";
//	case OPER_STOPCH:					return "OPER_STOPCH";
//	case OPER_PUTEVT:					return "OPER_PUTEVT";
//	case OPER_SYSNOTIFY:				return "OPER_SYSNOTIFY";	
//	case OPER_CST:						return "OPER_CST";
//	case OPER_GETTRCOUNT:				return "OPER_GETTRCOUNT";
//	case OPER_XOIP_SETRESATTR:			return "OPER_XOIP_SETRESATTR";
//	case OPER_XOIP_GETRESATTR:			return "OPER_XOIP_GETRESATTR";
//	case OPER_XOIP_GETSSINFO:			return "OPER_XOIP_GETSSINFO";
//	case OPER_XOIP_STARTMEDIA:			return "OPER_XOIP_STARTMEDIA";
//	case OPER_XOIP_STOP:				return "OPER_XOIP_STOP";
//	case OPER_XOIP_SENDDIGITS:			return "OPER_XOIP_SENDDIGITS";
//	case OPER_XOIP_ENABLEEVENT:			return "OPER_XOIP_ENABLEEVENT";
//	case OPER_XOIP_DISABLEEVENT:		return "OPER_XOIP_DISABLEEVENT";
//	case OPER_XOIP_RECEIVEDIGITS:		return "OPER_XOIP_RECEIVEDIGITS";
//	case OPER_XOIP_SENDRFC2833:			return "OPER_XOIP_SENDRFC2833";
//	case OPER_SENDCPG:					return "OPER_SENDCPG";
//	case OPER_CALLPROCEEDING:			return "OPER_CALLPROCEEDING";
//	case OPER_CALLPROGRESS:				return "OPER_CALLPROGRESS";
//	case OPER_SETUPACK:					return "OPER_SETUPACK";
//	case OPER_SIP_SENDREINVITE:			return "OPER_SIP_SENDREINVITE";
//	case OPER_SIP_SENDREINVITEACK:		return "OPER_SIP_SENDREINVITEACK";
//	case OPER_SIP_SENDREGISTER:			return "OPER_SIP_SENDREGISTER";
//	case OPER_XOIP_SWITCH_VF:			return "OPER_XOIP_SWITCH_VF";
//	case OPER_SIP_SENDINFO:				return "OPER_SIP_SENDINFO";
//	case OPER_SIP_SENDINFOACK:			return "OPER_SIP_SENDINFOACK";
//	case OPER_NR_SCROUTE:				return "OPER_NR_SCROUTE";
//	case OPER_NR_SCUNROUTE:				return "OPER_NR_SCUNROUTE";
//	case OPER_SIP_SENDREGISTERACK:		return "OPER_SIP_SENDREGISTERACK";
//	case OPER_SIP_SENDTRYING:			return "OPER_SIP_SENDTRYING";
//	case OPER_DT_SETTSSIG:				return "OPER_DT_SETTSSIG";
//	case OPER_DT_GETTSSIG:				return "OPER_DT_GETTSSIG";
//	case OPER_SIP_SENDSUBSCRIBE:		return "OPER_SIP_SENDSUBSCRIBE";
//	case OPER_SIP_SENDNOTIFYACK:		return "OPER_SIP_SENDNOTIFYACK";
//	case OPER_GETCONFENERGY:			return "OPER_GETCONFENERGY";
//	case OPER_ESTCONF:					return "OPER_ESTCONF";
//	case OPER_ADDCONF:					return "OPER_ADDCONF";
//	case OPER_REMCONF:					return "OPER_REMCONF";
//	case OPER_DELCONF:					return "OPER_DELCONF";
//	case OPER_SETCDE	:				return "OPER_SETCDE	";
//	case OPER_ESTCONF_EX:				return "OPER_ESTCONF_EX";
//	case OPER_ADDCONF_EX:				return "OPER_ADDCONF_EX";
//	case OPER_REMCONF_EX:				return "OPER_REMCONF_EX";
//	case OPER_SETCDE_EX:				return "OPER_SETCDE_EX";
//	case OPER_SETLMASKEX:				return "OPER_SETLMASKEX";
//	case OPER_SS7_SENDEXT:				return "OPER_SS7_SENDEXT";
//	case OPER_FXS_SEND:					return "OPER_FXS_SEND";
//	case OPER_FXS_RECV:					return "OPER_FXS_RECV";
//	case OPER_MO_SETHOOK:				return "OPER_MO_SETHOOK";
//	case OPER_MO_DIAL:					return "OPER_MO_DIAL";
//	case OPER_MS_GENRING:				return "OPER_MS_GENRING";
//	case OPER_MS_WTRING:				return "OPER_MS_WTRING";
//	case OPER_AG_SENDTONE:				return "OPER_AG_SENDTONE";
//	case OPER_RECVFSK:					return "OPER_RECVFSK";
//	case OPER_SENDFSK:					return "OPER_SENDFSK";
//	case OPER_SIP_RECVUPDATE:			return "OPER_SIP_RECVUPDATE";
//	case OPER_SIP_SENDUPDATE:			return "OPER_SIP_SENDUPDATE";
//	case OPER_SIP_RECVUPDATEACK:		return "OPER_SIP_RECVUPDATEACK";
//	case OPER_SIP_SENDUPDATEACK:		return "OPER_SIP_SENDUPDATEACK";
//	case OPER_SIP_RECVACK:				return "OPER_SIP_RECVACK";
//	case OPER_SIP_SENDACK:				return "OPER_SIP_SENDACK";
//	case OPER_SIP_RECVPRACK:			return "OPER_SIP_RECVPRACK";
//	case OPER_SIP_SENDPRACK:			return "OPER_SIP_SENDPRACK";
//	case OPER_SIP_SENDPRACKACK:			return "OPER_SIP_SENDPRACKACK";
//	case OPER_SIP_RECVPRACKACK:			return "OPER_SIP_RECVPRACKACK";
//	default:							
//		{
//			return "OPER_UNKNOWN";
//		}
//	}
//}
//
//const char* CallTermMaskToStr(int val)
//{
//	switch(val)
//	{
//	case  CR_SS_TELNUM:	return "Send tele number succ";
//	case CR_BUSY:return "Line busy";
//	case CR_NOANS:return "No answer";
//	case CR_NORB:return "No ringback";
//	case CR_CNCT:return "Call connected";
//	case CR_CEPT:return "Operator intercept";
//	case CR_STOPD:return "Call analysis stopped";
//	case CR_NODIALTONE:return "No dialtone detected";
//	case CR_FAXTONE:return "Fax tone detected";
//	case CR_SF_TELNUM:return "Send tele number fail";
//	case CR_ERROR:return "Call analysis error";
//	default:return "Call analysis error";
//
//	}
//}
//
//const char* ReleaseCallReason(long ccValue)
//{
//	long lReason = ccValue & 0xff;
//
//	switch(lReason){
//	case NOT_RECV_VALID_CC:		return("Cause 00: Valid cause code not yet received");
//	case UNASSIGNED_NUMBER:		return("Cause 01: Unassigned (unallocated) number");
//	case NO_ROUTE:				return("Cause 02: No route to specified transit network");
//	case CHANNEL_UNACCEPTABLE:	return("Cause 06: Channel unacceptable");  
//	case NORMAL_CLEARING:		return("Cause 16: Normal call clearing");  
//	case USER_BUSY:				return("Cause 17: User busy");  
//	case NO_USER_RESPONDING:	return("Cause 18: No user responding");  
//	case NO_ANSWER_FROM_USER:	return("Cause 19: No answer from user (user alerted)");
//	case 20:					return("Cause 20: Subscriber absent");
//	case CALL_REJECTED:			return("Cause 21: Call rejected");  
//	case NUMBER_CHANGED:		return("Cause 22: Number changed");  
//	case DEST_OUT_OF_ORDER:		return("Cause 27: Destination out of order");  
//	case INVALID_NUMBER_FORMAT:	return("Cause 28: Invalid number format (incomplete number)");  
//	case FACILITY_REJECTED:		return("Cause 29: Facility rejected");  
//	case RESP_TO_STAT_ENQ:		return("Cause 30: Response to STATUS ENQUIRY");  
//	case UNSPECIFIED_CAUSE:		return("Cause 31: Normal, unspecified");  
//	case CIRCUIT_OUT_OF_ORDER:	return("Cause 33: Circuit out of order");
//	case NO_CIRCUIT_AVAILABLE:	return("Cause 34: No circuit/channel available");  
//	case NETWORK_OUT_OF_ORDER:	return("Cause 38: Network out of order");  
//	case TEMPORARY_FAILURE:		return("Cause 41: Temporary failure");  
//	case NETWORK_CONGESTION:	return("Cause 42: Switching equipment congestion");  
//	case REQ_CHANNEL_NOT_AVAIL:	return("Cause 44: Requested circuit/channel not available");  
//	case PRE_EMPTED:			return("Cause 45: Call preempted");  
//	case FACILITY_NOT_SUBSCRIBED:return("Cause 50: Requested facility not subscribed (see Q.850)");
//	case OUTGOING_CALL_BARRED:	return("Cause 52: Outgoing call barred");  
//	case INCOMING_CALL_BARRED:	return("Cause 54: Incoming call barred"); 
//	case BEAR_CAP_NOT_AVAIL:	return("Cause 58: Bearer capability not presently available");  
//	case SERVICE_NOT_AVAIL:		return("Cause 63: Service or option not available, unspecified");  
//	case CAP_NOT_IMPLEMENTED:	return("Cause 65: Bearer capability not implemented");  
//	case CHAN_NOT_IMPLEMENTED:	return("Cause 66: Channel type not implemented");  
//	case FACILITY_NOT_IMPLEMENT:return("Cause 69: Requested facility not implemented");  
//	case INVALID_CALL_REF:		return("Cause 81: Invalid call reference value");  
//	case CHAN_DOES_NOT_EXIST:	return("Cause 82: Identified channel does not exist");  
//	case INCOMPATIBLE_DEST:		return("Cause 88: Incompatible destination");  
//	case INVALID_MSG_UNSPEC:	return("Cause 95: Invalid message, unspecified");  
//	case MANDATORY_IE_MISSING:	return("Cause 96: Mandatory information element is missing");  
//	case NONEXISTENT_MSG:		return("Cause 97: Message type non-existent or not implemented");  
//	case WRONG_MESSAGE:			return("Cause 98: Message not compatible with call state or message type non-existent or not implemented");  
//	case BAD_INFO_ELEM:			return("Cause 99: Information element non-existent or not implemented");  
//	case INVALID_ELEM_CONTENTS:	return("Cause 100: Invalid information element contents");  
//	case WRONG_MSG_FOR_STATE:	return("Cause 101: Message not compatible with call state");  
//	case TIMER_EXPIRY:			return("Cause 102: Recovery on time expiry");  
//	case MANDATORY_IE_LEN_ERR:	return("Cause 103: Invalid length for information element");  
//	case PROTOCOL_ERROR:		return("Cause 111: Protocol error, unspecified");  
//	case INTERWORKING_UNSPEC:	return("Cause 127: Interworking, unspecified");  
//	default: return "Cause xxx: Unknown";
//	}
//}
//
//const char* SYSEvtToStr( unsigned int Evt )
//{
//	switch(Evt)
//	{
//	case  SYSEV_MC_STATUS:						return "SYSEV_MC_STATUS";
//	case  SYSEV_PRD_STATUS:						return "SYSEV_PRD_STATUS";
//	case  SYSEV_MB_STATUS:						return "SYSEV_MB_STATUS";
//	case  SYSEV_DSP_STATUS:						return "SYSEV_DSP_STATUS";
//	case  SYSEV_PRI_STATUS:						return "SYSEV_PRI_STATUS";
//	case  SYSEV_SPAN_STATUS:					return "SYSEV_SPAN_STATUS";
//	case  SYSEV_DSP_BRD_CAP:					return "SYSEV_DSP_BRD_CAP";
//	case  SYSEV_PRI_BRD_CAP:					return "SYSEV_PRI_BRD_CAP";
//	case  SYSEV_XOIP_BRD_CAP:					return "SYSEV_XOIP_BRD_CAP";
//	case  SYSEV_SPAN_ALARM:						return "SYSEV_SPAN_ALARM";
//	case  SYSEV_SPAN_E1:						return "SYSEV_SPAN_E1";
//	case  SYSEV_SPAN_T1:						return "SYSEV_SPAN_T1";
//	case  SYSEV_SPAN_J1:						return "SYSEV_SPAN_J1";
//	case  SYSEV_SS7_STATUS:						return "SYSEV_SS7_STATUS";
//	case  SYSEV_CAP_DATA:						return "SYSEV_CAP_DATA";
//	case  SYSEV_XOIP_STATUS:					return "SYSEV_XOIP_STATUS";
//	case  SYSEV_SS7_BRD_CAP:					return "SYSEV_SS7_BRD_CAP";
//	case  SYSEV_SIP_STATUS:						return "SYSEV_SIP_STATUS";
//	case  SYSEV_SIP_BRD_CAP:					return "SYSEV_SIP_BRD_CAP";
//	case  SYSEV_M3G_STATUS:						return "SYSEV_M3G_STATUS";
//	case  SYSEV_M3G_BRD_CAP:					return "SYSEV_M3G_BRD_CAP";
//	case	SYSEV_M3G_CONN_STATUS:				return "SYSEV_M3G_CONN_STATUS";
//	case  SYSEV_ETHERCAP_DATA:					return "SYSEV_ETHERCAP_DATA";
//	case  SYSEV_PRI_L2DATA:						return "SYSEV_PRI_L2DATA";
//	case  SYSEV_FXS_STATUS:						return "SYSEV_FXS_STATUS";
//	case  SYSEV_AG_STATUS:						return "SYSEV_AG_STATUS";
//	case  SYSEV_SIP_REGISTERSENT:				return "SYSEV_SIP_REGISTERSENT";
//	case  SYSEV_SIP_RECVREGISTERACK:			return "SYSEV_SIP_RECVREGISTERACK";
//	case  SYSEV_SIP_REGISTERACKSENT:			return "SYSEV_SIP_REGISTERACKSENT";
//	case  SYSEV_SIP_RECVREGISTER:				return "SYSEV_SIP_RECVREGISTER";
//	case  SYSEV_SIP_TRANSACTIONSENT:			return "SYSEV_SIP_TRANSACTIONSENT";
//	case  SYSEV_SIP_RECVTRANSACTION:			return "SYSEV_SIP_RECVTRANSACTION";
//	case  SYSEV_SIP_TRANSACTIONACKSENT:			return "SYSEV_SIP_TRANSACTIONACKSENT";
//	case  SYSEV_SIP_RECVTRANSACTIONACK:			return "SYSEV_SIP_RECVTRANSACTIONACK";
//	case  SYSEV_SIP_REGUSER_NEW:				return "SYSEV_SIP_REGUSER_NEW";
//	case  SYSEV_SIP_REGUSER_DEL:				return "SYSEV_SIP_REGUSER_DEL";
//
//	case  SYSEV_SS7_CGBSENT:					return "SYSEV_SS7_CGBSENT";
//	case  SYSEV_SS7_GRSSENT:					return "SYSEV_SS7_GRSSENT";
//	case  SYSEV_SS7_CGUSENT:					return "SYSEV_SS7_CGUSENT";
//	case  SYSEV_SS7_RECVCGB:					return "SYSEV_SS7_RECVCGB";
//	case  SYSEV_SS7_RECVGRS:					return "SYSEV_SS7_RECVGRS";
//	case  SYSEV_SS7_RECVCGU:					return "SYSEV_SS7_RECVCGU";
//
//	case  SYSEV_PRIDCH_ALARM:					return "SYSEV_PRIDCH_ALARM";
//	case  SYSEV_S7LINK_ALARM:					return "SYSEV_S7LINK_ALARM";
//	default:	return "unkown";
//
//	}
//
//}
//
//const char* DevTypeToStr(int val)
//{
//	switch(val)
//	{
//	case  DT_DSP_BRD:	return "DSP board device";
//	case  DT_DSP_CH:	return "DSP voice channel device";
//	case  DT_DTI_CH:	return "DTI voice channel device";
//	case  DT_SIG_CH:	return "SS7 & PRI(Global Call) channel device";
//	case  DT_CS_CH:		return "DT_CS_CH";
//	case  DT_XOIP_CH:	return "IPM channel device";
//	case  DT_PRD:		return "Play and Record Device";
//	case  DT_SIP_CH:	return "SIP(Global Call) channel device";
//	case  DT_FXS_CH:	return "FXS channel device";
//	case  DT_AG_CH:		return "Analog channel device";
//	case	DT_M3G_BRD:	return "M3G board device";
//	case 	DT_M3G_CH:	return "M3G channel device";
//	case  DT_XOIP_BRD:	return "XOIP board device";
//	case  DT_SYS:		return "system device";
//	default: return		"unknow";
//	}
//
//}

const char* KFPC_CodeIDToAudioCode( unsigned char CodeID )
{
	if(CodeID<AudioCodec_MaxNum)
	{

		return KFPC_AudioCodeList[CodeID].AudioName;

	}
	return "unknown";
}

//const char* EHProtocol2Str( unsigned int Pro )
//{
//	switch(Pro)
//	{
//	case eGCPro_PRI:	return "PRI";
//	case eGCPro_SS7:	return "SS7";
//	case eGCPro_SIP:	return "SIP";
//	default:	return "ClearChannel";
//	}
//}
