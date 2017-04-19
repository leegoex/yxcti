#include "kfpc_id.h"

static KFPC_APP_TYPE_INFO KFPC_APP_TYPE_LIST[]={
	{KFPC_APP_TYPE_UNKNOW,		"UNKNOW"},
	{KFPC_APP_TYPE_TSERVER,		"TSERVER"},
	{KFPC_APP_TYPE_CTI,			"CTI"},
	{KFPC_APP_TYPE_CCS,			"CCS"},
	{KFPC_APP_TYPE_AGENT,		"AGENT"},
	{KFPC_APP_TYPE_TTS,			"TTS"},
	{KFPC_APP_TYPE_VOICE,		"VOICE"},
	{KFPC_APP_TYPE_FAX,			"FAX"},
	{KFPC_APP_TYPE_ROUTER,		"ROUTE"},
	{KFPC_APP_TYPE_IVR,			"IVR"},
	{KFPC_APP_TYPE_LICENSE,		"LICENSE"},
	{KFPC_APP_TYPE_BILL,		"BILL"},
	{KFPC_APP_TYPE_PBX,			"PBX"},
	{KFPC_APP_TYPE_SOFTSWITCH,	"SOFTSWITCH"},
	{KFPC_APP_TYPE_SMS,			"SMS"},
	{KFPC_APP_TYPE_FAXCONVERT,	"FAXCONVERT"},
	{KFPC_APP_TYPE_FAXFLOW,		"FAXFLOW"},
	{KFPC_APP_TYPE_CTRL,		"CTRL"},
	{KFPC_APP_TYPE_NETSERVER,	"NETSERVER"},
	{KFPC_APP_TYPE_SIPSERVER,	"SIPSERVER"},
	{KFPC_APP_TYPE_TANDEM,		"TANDEM"},
	{KFPC_APP_TYPE_IPREC,		"IPREC"},
	{KFPC_APP_TYPE_NOTIFY,		"NOTIFY"},
	
};


KFPC_APP_TYPE AppTypeName2ID( const char* pAppTypeName )
{
	int i=0;

	for(;i<KFPC_APP_TYPE_END;i++)
	{
		if(strcmp(pAppTypeName,KFPC_APP_TYPE_LIST[i].Name) == 0)
		{
			return KFPC_APP_TYPE_LIST[i].Type;
		}
	}
	return KFPC_APP_TYPE_UNKNOW;
}

const char* KFPC_ID_CLASS_COM_TO_STRING( unsigned int in_un32MsgId )
{
	unsigned int	un32ClassId = (in_un32MsgId & 0x00FF0000) >> 16;

	switch( un32ClassId )
	{
	case KFPC_ID_CLASS_COM_INTERNAL:				return (const char*)"KFPC_INTERNAL";
	case KFPC_ID_CLASS_COM_API:						return (const char*)"KFPC_API";
	case KFPC_ID_CLASS_COM_TSERVER:					return (const char*)"KFPC_TSERVER";
	case KFPC_ID_CLASS_COM_CTI:						return (const char*)"KFPC_CTI";	
	case KFPC_ID_CLASS_COM_AGENT:					return (const char*)"KFPC_AGENT";
	case KFPC_ID_CLASS_COM_TTS:						return (const char*)"KFPC_TTS";	
	case KFPC_ID_CLASS_COM_VOICE:					return (const char*)"KFPC_VOICE";
	case KFPC_ID_CLASS_COM_FAX:						return (const char*)"KFPC_FAX";
	case KFPC_ID_CLASS_COM_EH:						return (const char*)"KFPC_EH";
	case KFPC_ID_CLASS_COM_LIC:						return (const char*)"KFPC_LICENSE";
	case KFPC_ID_CLASS_COM_BILL:					return (const char*)"KFPC_BILL";
	case KFPC_ID_CLASS_COM_SMS:						return (const char*)"KFPC_SMS";		 
	case KFPC_ID_CLASS_COM_FAXCONVERT:				return (const char*)"KFPC_FAXCONVERT";
	case KFPC_ID_CLASS_COM_GLTSERVER:				return (const char*)"KFPC_GLTSERVER";
	case KFPC_ID_CLASS_COM_SIPSERVER:				return (const char*)"KFPC_SIPSERVER";
	case KFPC_ID_CLASS_COM_SIPRECORD:				return (const char*)"KFPC_SIPRECORD";
	case KFPC_ID_CLASS_COM_NOTIFY:					return (const char*)"KFPC_NOTIFY";
	}

	return (const char*)"";
}