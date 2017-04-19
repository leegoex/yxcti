#include "KFPC_EH_MsgID.h"

const char* EHMsgIDToStr( unsigned int MsgID )
{
	switch(MsgID)
	{
	case KFPC_MSG_ID_EH_NULL:								return "NULL";                          
	case KFPC_MSG_ID_EH_AcceptCall:							return "AcceptCall";                    
	case KFPC_MSG_ID_EH_AnswerCall:							return "AnswerCall";                    
	case KFPC_MSG_ID_EH_ReleaseCall:						return "ReleaseCall";                   
	case KFPC_MSG_ID_EH_CallOut	:							return "CallOut";                       
	case KFPC_MSG_ID_EH_EVT_IncomingCall	:				return "EVT_IncomingCall";              
	case KFPC_MSG_ID_EH_EVT_AlertCall	:					return "EVT_AlertCall";                 
	case KFPC_MSG_ID_EH_EVT_AnsweredCall	:				return "EVT_AnsweredCall";              
	case KFPC_MSG_ID_EH_EVT_ReleasedCall	:				return "EVT_ReleasedCall";              
	case KFPC_MSG_ID_EH_Connect	:							return "Connect";                       
	case KFPC_MSG_ID_EH_Disconnect:							return "Disconnect";                    
	case KFPC_MSG_ID_EH_CreateConference	:				return "CreateConference";              
	case KFPC_MSG_ID_EH_FreeConference	:					return "FreeConference";                
	case KFPC_MSG_ID_EH_JoinConference	:					return "JoinConference";                
	case KFPC_MSG_ID_EH_LeaveConference	:					return "LeaveConference";               
	case KFPC_MSG_ID_EH_ChangeConnectMode:					return "ChangeConnectMode";          
	case KFPC_MSG_ID_EH_CollectDTMF:						return "CollectDTMF";                   
	case KFPC_MSG_ID_EH_StopCollectDTMF	:					return "StopCollectDTMF";               
	case KFPC_MSG_ID_EH_EVT_CollectDTMFCompleted	:		return "EVT_CollectDTMFCompleted";      
	case KFPC_MSG_ID_EH_PlayVoice:							return "PlayVoice";                     
	case KFPC_MSG_ID_EH_StopPlayVoice	:					return "StopPlayVoice";                 
	case KFPC_MSG_ID_EH_EVT_PlayVoiceCompleted	:			return "EVT_PlayVoiceCompleted";        
	case KFPC_MSG_ID_EH_RecordFile:							return "RecordFile";                    
	case KFPC_MSG_ID_EH_StopRecordFile	:					return "StopRecordFile";                
	case KFPC_MSG_ID_EH_EVT_RecordFileCompleted	:			return "EVT_RecordFileCompleted";       
	case KFPC_MSG_ID_EH_ConfPlayVoice	:					return "ConfPlayVoice";                 
	case KFPC_MSG_ID_EH_StopConfPlayVoice:					return "StopConfPlayVoice";             
	case KFPC_MSG_ID_EH_EVT_ConfPlayFileCompleted:			return "EVT_ConfPlayFileCompleted";     
	case KFPC_MSG_ID_EH_ConfRecordFile	:					return "ConfRecordFile";                
	case KFPC_MSG_ID_EH_StopConfRecordFile:					return "StopConfRecordFile";            
	case KFPC_MSG_ID_EH_EVT_ConfRecordFileCompleted:		return "EVT_ConfRecordFileCompleted";   
	case KFPC_MSG_ID_EH_SendFax	:							return "SendFax";                       
	case KFPC_MSG_ID_EH_StopSendFax:						return "StopSendFax";                   
	case KFPC_MSG_ID_EH_EVT_SendFaxCompleted:				return "EVT_SendFaxCompleted";          
	case KFPC_MSG_ID_EH_RecvFax	:							return "RecvFax";                       
	case KFPC_MSG_ID_EH_StopRecvFax:						return "StopRecvFax";                   
	case KFPC_MSG_ID_EH_EVT_RecvFaxCompleted:				return "EVT_RecvFaxCompleted";          
	case KFPC_MSG_ID_EH_StartMedia:							return "StartMedia";
	case KFPC_MSG_ID_EH_Voice2Fax:							return "Voice2Fax";
	case KFPC_MSG_ID_EH_EVT_MoreInfo:						return "MoreInfo";
	case KFPC_MSG_ID_EH_SendMoreInfo:						return "SendMoreInfo";
	case KFPC_MSG_ID_EH_EVT_ReqMoreinfo:					return "ReqMoreinfo";
	case KFPC_MSG_ID_EH_EVT_Dial:							return "Dial";
	case KFPC_MSG_ID_EH_StopMedia:							return "StopMedia";
	case KFPC_MSG_ID_EH_Timer:								return "Timer";
	default:												return	"unknow";
	}
}