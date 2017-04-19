#include "kfpc_linuxwinapi.h"
#include "KFPC_TServerDef.h"

const char* VoiceStatusToStr(unsigned int val,char* Str)
{
	int i = 0;

	if(val == IVR_STATUS_IDLE)
	{
		i = sprintf(Str,"IDLE");
	}
	else
	{
		if(val & IVR_STATUS_PLAY_VOICE)
		{
			i = sprintf(Str+i," PLAY_Voice");
		}

		if(val & IVR_STATUS_RECORD_FILE)
		{
			i = sprintf(Str+i," RECORD_FILE");
		}

		if(val & IVR_STATUS_COLLECT_DTMF)
		{
			i = sprintf(Str+i," COLLECT_DTMF");
		}
		if(val & IVR_STATUS_PLAY_DTMF)
		{
			i = sprintf(Str+i," PLAY_DTMF");
		}
		
	}

	
	return Str;

}

const char* ChTypeToStr( KFPC_CH_TYPE val )
{
	switch(val)
	{
	case CH_TYPE_AG:	return "AG";
	case CH_TYPE_DTI:	return "DTI";
	case CH_TYPE_SIP:	return "SIP";
	case CH_TYPE_CONF:	return "CONF";
	default: return "ERR CH TYPE";
	}
}

const char* ConTypeToStr( KFPC_ConnectionType val )
{
	switch(val)
	{
	case ConType_CH_NULL:	return "CH-NULL";
	case ConType_CH_IVR:	return "CH-IVR";
	case ConType_CH_FAX:	return "CH-FAX";
	case ConType_CH_CH:		return "CH-CH";
	case ConType_CH_CONF:	return "CH-CONF";
	default:				return "ERR CON TYPE";
	}
}

const char* VoiceRoleToStr( KFPC_VoiceRole val )
{
	switch(val)
	{
	case VoiceRole_IVR:	return "IVR";
	case VoiceRole_AGTONE: return "AGTONE";
	case VoiceRole_CONF:return "CONF";
	default:return "ERR IVR ROLE";
	}
}

const char* IVRTypeToStr( KFPC_CH_IVRType_t val )
{
	switch(val)
	{
	case CH_IVRType_NULL:		return "NULL";
	case CH_IVRType_ONE:		return "ONE";
	case CH_IVRType_MIX:		return "MIX";
	default: return "ERR IVR TYPE";
	}
}


const char* ActionTypeToStr( KFPC_ChannelActionType val )
{
	switch(val)
	{
	case KFPC_CHActionType_NULL:	return "NULL";
	case KFPC_CHActionType_CH_IVR:	return "CH_IVR";
	case KFPC_CHActionType_CH_FAX:	return "CH_FAX";
	case KFPC_CHActionType_CH_CH:	return "CH_CH";
	case KFPC_CHActionType_CH_CONF:	return "CH_CONF";
	case KFPC_CHActionType_CH_CHANGE_CONNECT_MODE:	return "CH_CHANGE_CONNECT_MODE";
	case KFPC_CHActionType_CH_MONITOR_IVR:return "CH_MONITOR_IVR";
	case KFPC_CHACTIONTYPE_CH_MIX_IVR:return "MIX_IVR";
	default:return "unknow action type";
	}
}

unsigned int CheckVoiceType(char *pPlayContent)
{
	char *pPos = strstr(pPlayContent,"|TTS");
	if(pPos == NULL)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

static const KFPC_IdleType_Info KFPC_IdleType_List[] = {
	{KFPC_QueryIdleChType_W,	"W"	},
	{KFPC_QueryIdleChType_Z,	"Z"	},
	{KFPC_QueryIdleChType_Odd,	"Odd"},
	{KFPC_QueryIdleChType_Even,	"Even"}
};

const char* IdleTypeToStr(unsigned int Type)
{
	if(Type <= KFPC_QueryIdleChType_Even)
	{
		return KFPC_IdleType_List[Type].IdleTypeName;
	}
	else
	{
		return "W";
	}
}
