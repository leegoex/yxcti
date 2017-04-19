#include "KFPC_ContactCenterPublicDef.h"
#include <string>
#include <time.h>
#include "kfpc_id.h"
#include "kfpc_api.h"
#include "kfpc_tserver_api.h"
#include "KFPC_EH_MsgID.h"
//#include "kfpc_fax_api.h"
#include "kfpc_voiceser_api.h"
//#include "kfpc_ttsser_api.h"
//#include "kfpc_agent_api.h"
//#include "KFPC_CCSErr.h"
#include "KFPC_TServerErr.h"
#include "kfpc_comapierr.h"
#include "KFPC_SIPReasonStatus.h"
#include "KFPC_Q850.h"
//#include "kfpc_sipserver_api.h"

const char* ChStatusToStr(int ID)
{
	switch(ID)
	{
	case KFPC_CH_Status_Unready:					return "Unready";
	case KFPC_CH_Status_CallOffer:					return "CallOffer";
	case KFPC_CH_Status_CallOut:					return "CallOut";
	case KFPC_CH_Status_Accept:						return "Accept";
	case KFPC_CH_Status_Alerting:					return "Altering";
	case KFPC_CH_Status_Connect:					return "Connect";
	case KFPC_CH_Status_Release:					return "Release";
	case KFPC_CH_Status_Failed:						return "Failed";
	case KFPC_CH_Status_OutofService:				return "OutofService";
	case KFPC_CH_Status_LocalBlock:					return "LocalBlock";
	case KFPC_CH_Status_Idle:						return "Idle";
	case KFPC_CH_Status_RemoteBlock:				return "RemoteBlock";
	case KFPC_CH_Status_HardwareFailureBlock:		return "HardwareFailureBlock";
	case KFPC_CH_Status_OffHook:					return "OffHook";
	case KFPC_CH_Status_OnHook:						return "OnHook";
	case KFPC_CH_Status_WaitMoreInfo:				return "WaitMoreInfo";
	default:										return "UNKNOWN_CH_STATUS";
	}
}

const char* SignalTypeToStr(int SignalType)
{
	switch(SignalType)
	{
	case KFPC_SignalType_ClearChannel	:return "CLEARCHANNEL";
	case KFPC_SignalType_FXS			:return "FXS";
	case KFPC_SignalType_FXO			:return "FXO";
	case KFPC_SignalType_ISDN_N			:return "PRI";
	case KFPC_SignalType_SS7_ISUP			:return "SS7";
	case KFPC_SignalType_SIP			:return "SIP";
	default						:return "UNKNOWN_SignalType";
	}
}

const char* MsgIDToStr( unsigned int MsgID,char* pStr )
{
	switch(KFPC_MSG_ID_GET_GROUP(MsgID))
	{
	case KFPC_ID_CLASS_COM_API:	return KFPC_MSG_ID_API_TO_STRING(MsgID);
	case KFPC_ID_CLASS_COM_TSERVER:	return TSMsgIDToStr(MsgID);
	case KFPC_ID_CLASS_COM_CTI:		return KFPC_ID_CLASS_COM_TO_STRING(MsgID);
	//case KFPC_ID_CLASS_COM_AGENT:	return AgentMsgIDToStr(MsgID);
	//case KFPC_ID_CLASS_COM_TTS:		return KFPC_MSG_ID_TTS_TO_STRING(MsgID);
	case KFPC_ID_CLASS_COM_VOICE:	return KFPC_MSG_ID_VOICE_TO_STRING(MsgID);
	//case KFPC_ID_CLASS_COM_FAX:		return KFPC_MSG_ID_FAX_TO_STRING(MsgID);
	case KFPC_ID_CLASS_COM_EH:		return EHMsgIDToStr(MsgID);
	//case KFPC_ID_CLASS_COM_SIPSERVER:return SIPMsgIDToStr(MsgID);
	default:
		{
			sprintf(pStr,"unknow msg id:0x%x",MsgID);
			return pStr;
		}
	}
}

unsigned short CallIDToChannel( unsigned long long& CallID )
{
	KFPC_CallID*	pCallID = (KFPC_CallID*)&CallID;
	return pCallID->CallIDInfo.ChID;
}

unsigned int ParsePlayContent(VoiceItemList_t &VoiceItemList,char *pPlayContent)
{
	if(pPlayContent == NULL)
	{
		return -1;
	}
	else
	{
		char* pPos = strtok(pPlayContent,"|");

		while(pPos != NULL)
		{
			char *pColonPos = strchr(pPos,':');
			if(pColonPos == NULL)
			{
				VoiceItemList.clear();
				return -1;
			}
			else
			{
				char TempPlayType[10] = {0};
				strncpy(TempPlayType,pPos,pColonPos-pPos);

				KFPC_VoiceItem VoiceItem;
				memset(&VoiceItem,0,sizeof(KFPC_VoiceItem));

				if(strcmp(TempPlayType,"FileName") == 0)
				{
					VoiceItem.PlayType = IVR_PLAY_TYPE_FILE;
				}
				else if(strcmp(TempPlayType,"TTS") == 0)
				{
					VoiceItem.PlayType = IVR_PLAY_TYPE_TEXT;
				}
				else
				{
					VoiceItemList.clear();
					return -1;
				}

				strncpy(VoiceItem.BeforeTranContent,pColonPos+1,KFPC_MAX_PLAY_CONTENT);

				VoiceItemList.push_back(VoiceItem);
			}

			pPos = strtok(NULL,"|");
		}
	}

	return 0;
}


const char* GetKFPCErrorCause(unsigned int ErrorCode,bool IsChinese)
{
	switch(ErrorCode)
	{
	case  KFPC_RegisterHandleFail:
		{
			if(IsChinese){return "ע�ᴦ����ʧ��";}
			else{return "Failed to register handler";}
		}
	case  KFPC_AlreadyInitComLib:
		{
			if(IsChinese){return "ͨ�ſ��Ѿ���ʼ��";}
			else{return "Communication library has been initialized";}
		}
	case  KFPC_UnInitComLib:
		{
			if(IsChinese){return "ͨ�ſ�δ��ʼ��";}
			else{return "Communication library is not initialized";}
		}
	case  KFPC_CreateFilterFail:
		{
			if(IsChinese){return "����������ʧ��";}
			else{return "Failed to create filter";}
		}
	case  KFPC_FilterParamTooMuch:
		{
			if(IsChinese){return "����������̫��";}
			else{return "Filter has too many parameters";}
		}
	case  KFPC_FilterNotExist:
		{
			if(IsChinese){return "������������";}
			else{return "Filter is not exist";}
		}
	case  KFPC_APPIDNotExist:
		{
			if(IsChinese){return "Ӧ�ó���ID������";}
			else{return "AppID is not exist";}
		}
	case  KFPC_AppNotConnect:
		{
			if(IsChinese){return "Ӧ�ó���û������";}
			else{return "The application is not connected";}
		}
	case  KFPC_SocketIDNotExist:
		{
			if(IsChinese){return "�׽���ID������";}
			else{return "The socketID is not exist";}
		}
	case  KFPC_AllocMsgFail:
		{
			if(IsChinese){return "������Ϣʧ��";}
			else{return "Failed to alloc message";}
		}
	case  KFPC_AppGroupIDNotExist:
		{
			if(IsChinese){return "Ӧ����ID������";}
			else{return "The AppGroupID is not exist";}
		}
	case  KFPC_IPErr:
		{
			if(IsChinese){return "IP��ַ����";}
			else{return "IP address error";}
		}
	case  KFPC_MsgFlagErr:
		{
			if(IsChinese){return "��Ϣͷ����";}
			else{return "Message head error";}
		}
	case  KFPC_MsgLenErr:
		{
			if(IsChinese){return "��Ϣ���ȴ���";}
			else{return "Message length error";}
		}
	case  KFPC_MsgTypeErr:
		{
			if(IsChinese){return "��Ϣ���ȴ���";}
			else{return "Message type error";}
		}
	case  KFPC_UserCloseSocket:
		{
			if(IsChinese){return "�׽����Ѿ����ر�";}
			else{return "Socket has been closed";}
		}
	case  KFPC_SocketIDAlreadyExist:
		{
			if(IsChinese){return "�׽���ID�Ѿ�����";}
			else{return "Socket ID is already exist";}
		}
	case  KFPC_SocketIsClosing:
		{
			if(IsChinese){return "�׽������ڹر�";}
			else{return "The socket being closed";}
		}
	case  KFPC_TimerInvalid:
		{
			if(IsChinese){return "��ʱ����Ч";}
			else{return "Invalid timer";}
		}
	case  KFPC_SocketIDInvalid:
		{
			if(IsChinese){return "�׽���ID��Ч";}
			else{return "Invalid socket ID";}
		}
	case  KFPC_TCPSocketNotEnough:
		{
			if(IsChinese){return "�׽��ֲ���";}
			else{return "No more sockets";}
		}
	case  KFPC_FilterInvalid:
		{
			if(IsChinese){return "��������Ч";}
			else{return "Invalid filter";}
		}
	case  KFPC_FilterNotEnough:
		{
			if(IsChinese){return "����������";}
			else{return "No more filter";}
		}
	case  KFPC_AppMangerAlreadyOpen:
		{
			if(IsChinese){return "Ӧ�ù������Ѿ���";}
			else{return "Application Manager is already open";}
		}
	case  KFPC_AppMangerDoesNotOpen:
		{
			if(IsChinese){return "Ӧ�ù�����δ��";}
			else{return "Application Manager did not open";}
		}
	case  KFPC_NO_Semaphore:
		{
			if(IsChinese){return "û���ź���";}
			else{return "No more semaphore";}
		}
	case  KFPC_ReconnectClose:
		{
			if(IsChinese){return "����Ȩ�ޱ��ر�";}
			else{return "Reconnect permission is closed";}
		}
	case  KFPC_GUID_Inequality:
		{
			if(IsChinese){return "GUID ����ͬ";}
			else{return "GUID is inequalitye";}
		}
	case  KFPC_APPID_Conflict:
		{
			if(IsChinese){return "APP ID��ͻ";}
			else{return "The AppID is conflict";}
		}
	case  KFPC_UniqueIdentify_Conflict:
		{
			if(IsChinese){return "UniqueIdentif ID��ͻ";}
			else{return "The UniqueIdentify is conflict";}
		}
	default:
		{
			if(IsChinese){return "δ֪����";}
			else{return "Unknown error";}
		}
	}
}


const char* GetErrorStr(unsigned int ErrorCode,unsigned int Lang)
{
	unsigned int ClassID = 0;	
	ClassID = KFPC_RESULT_GET_CLASS(ErrorCode);
	switch(ClassID)
	{
	//case  KFPC_ID_CLASS_COM_AGENT:
	//	{
	//		return CCSErrorCodeToStr(ErrorCode,Lang);
	//	}
	case KFPC_ID_CLASS_COM_TSERVER:
		{
			return ErrorCodeToStr(ErrorCode,Lang);
		}	
	case  KFPC_ID_CLASS_COM_API:
		{
			return ComErrorCodeToStr(ErrorCode,Lang);
		}		
	default:
		{
			return BaseErrorCodeToStr(ErrorCode,Lang);
			//return (Lang == 0)? "Unknown Error Class"			:	"δ֪��������";
		}	
	}
}

const char* GetCauseStr(unsigned int Cause,unsigned int Lang)
{
	if (Cause < 200)
	{
		return GetQ850CauseDes(Cause,(Lang == 0)?false:true);
	}
	else
	{
		return GetSIPCauseDes(Cause,(Lang == 0)?false:true);
	}

}

const char* GetSIPCauseDes(unsigned int Cause,bool IsChinese)
{
	switch(Cause)
	{
	case  SIP_STATUS_OK:
		{
			if(IsChinese){return "ok";}
			else{return "ok";}
		}
	case  SIP_STATUS_Accepted:
		{
			if(IsChinese){return "������";}
			else{return "Accepted";}
		}
	case SIP_STATUS_MultipleChoices:								//����ѡ��
		{
			if(IsChinese){return "������";}
			else{return "MultipleChoices";}
		}
	case SIP_STATUS_MovedPermanently:								//������Ǩ��
		{
			if(IsChinese){return "������Ǩ��";}
			else{return "MovedPermanently";}
		}
	case SIP_STATUS_MovedTemporarily:								//����ʱǨ��
		{
			if(IsChinese){return "����ʱǨ��";}
			else{return "MovedTemporarily";}
		}
	case SIP_STATUS_UseProxy:										//ʹ�ô��������
		{
			if(IsChinese){return "ʹ�ô��������";}
			else{return "UseProxy";}
		}
	case SIP_STATUS_AlternativeService:								//�������
		{
			if(IsChinese){return "�������";}
			else{return "AlternativeService";}
		}
	case SIP_STATUS_BadRequest:		//���в���
		{
			if(IsChinese){return "���в���";}
			else{return "BadRequest";}
		}
	case SIP_STATUS_Unauthorized:		//δ����Ȩ��ֻ��ע�����ʹ�ã����������Ӧʹ�ô����������Ȩ407
		{
			if(IsChinese){return "δ����Ȩ";}
			else{return "Unauthorized";}
		}
	case SIP_STATUS_PaymentRequired:		//Ҫ�󸶷ѣ�Ԥ��Ϊ����ʹ��)
		{
			if(IsChinese){return "Ҫ�󸶷�";}
			else{return "PaymentRequired";}
		}
	case SIP_STATUS_Forbidden:		//����ֹ��
		{
			if(IsChinese){return "����ֹ��";}
			else{return "Forbidden";}
		}
	case SIP_STATUS_NotFound:	//δ���֣�δ�����û�
		{
			if(IsChinese){return "δ�����û�";}
			else{return "NotFound";}
		}
	case SIP_STATUS_MethodNotAllowed:		//������ķ���
		{
			if(IsChinese){return "������ķ���";}
			else{return "MethodNotAllowed";}
		}
	case SIP_STATUS_NotAcceptable:		//���ɽ���
		{
			if(IsChinese){return "���ɽ���";}
			else{return "NotAcceptable";}
		}
	case SIP_STATUS_ProxyAuthenticationRequired:		//��Ҫ�����������Ȩ
		{
			if(IsChinese){return "��Ҫ�����������Ȩ";}
			else{return "ProxyAuthenticationRequired";}
		}
	case SIP_STATUS_RequestTimeout:		//���г�ʱ����Ԥ��ʱ�����޷��ҵ��û�
		{
			if(IsChinese){return "���г�ʱ����Ԥ��ʱ�����޷��ҵ��û�";}
			else{return "RequestTimeout";}
		}
	case SIP_STATUS_Conflict:
		{
			if(IsChinese){return "��ͻ";}
			else{return "Conflict";}
		}
	case SIP_STATUS_Gone://����ʧ���û��������ڣ����ѴӴ˴���ʧ
		{
			if(IsChinese){return "�û�����ʧ";}
			else{return "User Gone";}
		}

	case SIP_STATUS_LengthRequired:
		{
			if(IsChinese){return "��Ҫ����";}
			else{return "LengthRequired";}
		}
	case SIP_STATUS_RequestEntityTooLarge:		//����ʵ�����
		{
			if(IsChinese){return "����ʵ�����";}
			else{return "RequestEntityTooLarge";}
		}
	case SIP_STATUS_RequestURITooLong:	//����URI����
		{
			if(IsChinese){return "����URI����";}
			else{return "RequestURITooLong";}
		}
	case SIP_STATUS_UnsupportedMediaType:	//��֧�ֵ�ý������
		{
			if(IsChinese){return "��֧�ֵ�ý������";}
			else{return "UnsupportedMediaType";}
		}
	case SIP_STATUS_UnsupportedURIScheme:		//��֧�ֵ�URI����
		{
			if(IsChinese){return "��֧�ֵ�URI����";}
			else{return "UnsupportedURIScheme";}
		}
	case SIP_STATUS_BadExtension:	//������չ��ʹ���˲���SIPЭ����չ���������޷�������չ
		{
			if(IsChinese){return "������չ";}
			else{return "BadExtension";}
		}
	case SIP_STATUS_ExtensionRequired:	//��Ҫ��չ
		{
			if(IsChinese){return "��Ҫ��չ";}
			else{return "ExtensionRequired";}
		}
	case SIP_STATUS_IntervalTooBrief:	//ʱ��������
		{
			if(IsChinese){return "ʱ��������";}
			else{return "IntervalTooBrief";}
		}
	case SIP_STATUS_TemporarilyUnavailable:	//��ʱ����ʹ��
		{
			if(IsChinese){return "��ʱ����ʹ��";}
			else{return "TemporarilyUnavailable";}
		}
	case SIP_STATUS_Call_TransactionDoesNotExist:		//ͨ��/���񲻴���
		{
			if(IsChinese){return "���񲻴���";}
			else{return "TransactionDoesNotExist";}
		}
	case SIP_STATUS_LoopDetected:		//��⵽ѭ��
		{
			if(IsChinese){return "��⵽ѭ��";}
			else{return "LoopDetected";}
		}
	case SIP_STATUS_TooManyHops:	//��������
		{
			if(IsChinese){return "��������";}
			else{return "TooManyHops";}
		}
	case SIP_STATUS_AddressIncomplete:	//��ַ��ȫ
		{
			if(IsChinese){return "��ַ��ȫ";}
			else{return "AddressIncomplete";}
		}
	case SIP_STATUS_Ambiguous:		//ģ������
		{
			if(IsChinese){return "ģ������";}
			else{return "Ambiguous";}
		}
	case SIP_STATUS_BusyHere:	//�˴�̫æ
		{
			if(IsChinese){return "�˴�̫æ";}
			else{return "BusyHere";}
		}
	case SIP_STATUS_RequestTerminated:		//���б���ֹ
		{
			if(IsChinese){return "���б���ֹ";}
			else{return "RequestTerminated";}
		}
	case SIP_STATUS_NotAcceptableHere:		//�˴����ɽ���
		{
			if(IsChinese){return "�˴����ɽ���";}
			else{return "NotAcceptableHere";}
		}
	case SIP_STATUS_RequestPending:		//���д���
		{
			if(IsChinese){return "���д���";}
			else{return "RequestPending";}
		}
	case SIP_STATUS_Undecipherable:	//�޷�������޷���� S/MIME���岿��
		{
			if(IsChinese){return "�޷����";}
			else{return "Undecipherable";}
		}
	case SIP_STATUS_ServerInternalError:		//�������ڲ�����
		{
			if(IsChinese){return "�������ڲ�����";}
			else{return "ServerInternalError";}
		}
	case SIP_STATUS_NotImplemented:		//�޷�ʵʩ��SIP���з����ڴ˴��޷�ʵʩ
		{
			if(IsChinese){return "�޷�ʵʩ";}
			else{return "NotImplemented";}
		}
	case SIP_STATUS_BadGateway:		//��������
		{
			if(IsChinese){return "��������";}
			else{return "BadGateway";}
		}
	case SIP_STATUS_ServiceUnavailable:		//���񲻿�ʹ��
		{
			if(IsChinese){return "���񲻿�ʹ��";}
			else{return "ServiceUnavailable";}
		}
	case SIP_STATUS_ServerTimeOut:		//��������ʱ
		{
			if(IsChinese){return "��������ʱ";}
			else{return "ServerTime-Out";}
		}
	case SIP_STATUS_VersionNotSupported:	//��֧�ָð汾����������֧��SIPЭ�������汾
		{
			if(IsChinese){return "��֧�ָð汾";}
			else{return "VersionNotSupported";}
		}
	case SIP_STATUS_MessageTooLarge:		//��Ϣ����
		{
			if(IsChinese){return "��Ϣ����";}
			else{return "MessageTooLarge";}
		}			
	case SIP_STATUS_BusyEverywhere:		//������æ
		{
			if(IsChinese){return "������æ";}
			else{return "BusyEverywhere";}
		}
	case SIP_STATUS_Declined:		//�ܾ�
		{
			if(IsChinese){return "�ܾ�";}
			else{return "Declined";}
		}
	case SIP_STATUS_DoesNotExistAnywhere:		//�޴�����
		{
			if(IsChinese){return "�޴�����";}
			else{return "DoesNotExistAnywhere";}
		}
	case SIP_STATUS_NotAcceptable2:		//����ʹ��
		{
			if(IsChinese){return "����ʹ��";}
			else{return "NotAcceptable";}
		}
	default:
		{
			if(IsChinese){return "δ֪ԭ��ֵ";}
			else{return "Unknown cause";}
		}
	}
}

const char* GetQ850CauseDes(unsigned int Cause,bool IsChinese)
{
	switch(Cause)
	{	
	case	Q850_UnallocatedNumber:		//Cause No. 1 �C Unallocated (unassigned) number
		{
			if(IsChinese){return "Unallocated Number";}
			else{return "Unallocated Number";}
		}
	case		Q850_Noroute://Cause No. 2 �C No route to specified transit network (national use)
		{
			if(IsChinese){return "No route to specified transit network";}
			else{return "No route to specified transit network";}
		}
	case		Q850_NoRouteToDestination:		//Cause No. 3 �C No route to destination
		{
			if(IsChinese){return "��·��";}
			else{return "No route to destination";}
		}
	case		Q850_SendSpecialInformationTone:	//Cause No. 4 �C Send special information tone
		{
			if(IsChinese){return "Send special information tone";}
			else{return "Send special information tone";}
		}
	case		Q850_MisdialledTrunkPrefix:	//Cause No. 5 �C Misdialled trunk prefix (national use)
		{
			if(IsChinese){return "Misdialled trunk prefix";}
			else{return "Misdialled trunk prefix";}
		}
	case		Q850_ChannelUnacceptable:		//Cause No. 6 �C Channel unacceptable
		{
			if(IsChinese){return "Channel Unacceptable";}
			else{return "Channel Unacceptable";}
		}
	case		Q850_CallAwarded:	//Cause No. 7 �C Call awarded and being delivered in an established channel
		{
			if(IsChinese){return "Call awarded and being delivered in an established channel";}
			else{return "Call awarded and being delivered in an established channel";}
		}
	case		Q850_Preemption:			//Cause No. 8 �C Preemption
		{
			if(IsChinese){return "Preemption";}
			else{return "Preemption";}
		}
	case		Q850_PreemptionCircuit:		//Cause No. 9 �C Preemption - circuit reserved for reuse
		{
			if(IsChinese){return "Preemption - circuit reserved for reuse";}
			else{return "Preemption - circuit reserved for reuse";}
		}
	case		Q850_NormalCallClearing:		//Cause No. 16 �C Normal call clearing
		{
			if(IsChinese){return "Normal call clearing";}
			else{return "Normal call clearing";}
		}
	case		Q850_UserBusy:			//Cause No. 17 �C User busy
		{
			if(IsChinese){return "����æ";}
			else{return "UserBusy";}
		}
	case		Q850_NoUserResponding:			//Cause No. 18 �C No user responding
		{
			if(IsChinese){return "����Ӧ";}
			else{return "NoUserResponding";}
		}
	case		Q850_NoAnswerFromUser:			//Cause No. 19 �C No answer from user (user alerted)
		{
			if(IsChinese){return "��Ӧ��";}
			else{return "NoAnswerFromUser";}
		}
	case		Q850_SubscriberAbsent:		//Cause No. 20 �C Subscriber absent
		{
			if(IsChinese){return "Subscriber Absent";}
			else{return "Subscriber Absent";}
		}
	case		Q850_CallRejected:			//Cause No. 21 �C Call rejected
		{
			if(IsChinese){return "���б��ܾ�";}
			else{return "Call Rejected";}
		}
	case		Q850_NumberChanged:		//Cause No. 22 �C Number changed
		{
			if(IsChinese){return "Number Changed";}
			else{return "Number Changed";}
		}
	case		Q850_NonSelectedUserClearing:			//Cause No. 26 �C Non-selected user clearing
		{
			if(IsChinese){return "Non-selected user clearing";}
			else{return "Non-selected user clearing";}
		}
	case		Q850_DestinationOutOfOrder:	//Cause No. 27 �C Destination out of order
		{
			if(IsChinese){return " Destination out of order";}
			else{return " Destination out of order";}
		}
	case		Q850_InvalidNumberFormat:			//Cause No. 28 �C Invalid number format (address incomplete)
		{
			if(IsChinese){return "Invalid Number Format";}
			else{return "Invalid Number Format";}
		}
	case		Q850_FacilityRejected:			//Cause No. 29 �C Facility rejected
		{
			if(IsChinese){return "Facility rejected";}
			else{return "Facility rejected";}
		}
	case		Q850_ResponseToSTATUSENQUIRY:			//Cause No. 30 �C Response to STATUS ENQUIRY
		{
			if(IsChinese){return "Response to STATUS ENQUIRY";}
			else{return "Response to STATUS ENQUIRY";}
		}
	case		Q850_NormalUnspecified:			//Cause No. 31 �C Normal, unspecified
		{
			if(IsChinese){return "NormalUnspecified";}
			else{return "NormalUnspecified";}
		}
	case		Q850_NoCircuit:			//Cause No. 34 �C No circuit/channel available
		{
			if(IsChinese){return "No circuit/channel available";}
			else{return "No circuit/channel available";}
		}
	case		Q850_NetworkOutOfOrder:		//Cause No. 38 �C Network out of order
		{
			if(IsChinese){return "Network out of order";}
			else{return "Network out of order";}
		}
	case		Q850_PermanentFrameModeConnectionOutOfService://Cause No. 39 �C Permanent frame mode connection out-of-service
		{
			if(IsChinese){return "Permanent frame mode connection out-of-service";}
			else{return "Permanent frame mode connection out-of-service";}
		}
	case		Q850_PermanentFrameModeConnectionOperational://Cause No. 40 �C Permanent frame mode connection operational
		{
			if(IsChinese){return "Permanent frame mode connection operational";}
			else{return "Permanent frame mode connection operational";}
		}
	case		Q850_TemporaryFailure:		//Cause No. 41 �C Temporary failure
		{
			if(IsChinese){return "Temporary failure";}
			else{return "Temporary failure";}
		}
	case		Q850_SwitchingEquipmentCongestion:			//Cause No. 42 �C Switching equipment congestion
		{
			if(IsChinese){return "Switching equipment congestion";}
			else{return "Switching equipment congestion";}
		}
	case		Q850_AccessInformationDiscarded:			//Cause No. 43 �C Access information discarded
		{
			if(IsChinese){return "Access information discarded";}
			else{return "Access information discarded";}
		}
	case		Q850_ChannelNotAvailable:			//Cause No. 44 �C Requested circuit/channel not available
		{
			if(IsChinese){return "Requested circuit/channel not available";}
			else{return "Requested circuit/channel not available";}
		}
	case		Q850_PrecedenceCallBlocked:			//Cause No. 46 �C Precedence call blocked
		{
			if(IsChinese){return "Precedence call blocked";}
			else{return "Precedence call blocked";}
		}
	case		Q850_ResourceUnavailable:		//Cause No. 47 �C Resource unavailable, unspecified
		{
			if(IsChinese){return "Resource unavailable, unspecified";}
			else{return "Resource unavailable, unspecified";}
		}
	case		Q850_QualityOfServiceNotAvailable:		//Cause No. 49 �C Quality of Service not available
		{
			if(IsChinese){return "Quality of Service not available";}
			else{return "Quality of Service not available";}
		}
	case		Q850_RequestedFacilityNotSubscribed:		//Cause No. 50 �C Requested facility not subscribed
		{
			if(IsChinese){return "Requested facility not subscribed";}
			else{return "Requested facility not subscribed";}
		}
	case		Q850_OutgoingCallsBarredWithinCUG:		//Cause No. 53 �C Outgoing calls barred within CUG
		{
			if(IsChinese){return "Outgoing calls barred within CUG";}
			else{return "Outgoing calls barred within CUG";}
		}
	case		Q850_IncomingCallsBarredWithinCUG:			//Cause No. 55 �C Incoming calls barred within CUG
		{
			if(IsChinese){return "Incoming calls barred within CUG";}
			else{return "Incoming calls barred within CUG";}
		}
	case		Q850_BearerCapabilityNotAuthorized:			//Cause No. 57 �C Bearer capability not authorized
		{
			if(IsChinese){return "Bearer capability not authorized";}
			else{return "Bearer capability not authorized";}
		}
	case		Q850_BearerCapabilityNotPresentlyAvailable:		//Cause No. 58 �C Bearer capability not presently available
		{
			if(IsChinese){return "Bearer capability not presently available";}
			else{return "Bearer capability not presently available";}
		}
	case		Q850_InconsistencyInformationAndSubscriberClass	:	//Cause No. 62 �C Inconsistency in designated outgoing access information and subscriber class
		{
			if(IsChinese){return "Inconsistency in designated outgoing access information and subscriber class";}
			else{return "Inconsistency in designated outgoing access information and subscriber class";}
		}
	case		Q850_ServiceOrOptionNotAvailable:		//Cause No. 63 �C Service or option not available, unspecified
		{
			if(IsChinese){return "Service or option not available, unspecified";}
			else{return "Service or option not available, unspecified";}
		}
	case		Q850_BearerCapabilityNotImplemented:		//Cause No. 65 �C Bearer capability not implemented
		{
			if(IsChinese){return "Bearer capability not implemented";}
			else{return "Bearer capability not implemented";}
		}
	case		Q850_ChannelTypeNotImplemented:	//Cause No. 66 �C Channel type not implemented
		{
			if(IsChinese){return "Channel type not implemented";}
			else{return "Channel type not implemented";}
		}
	case		Q850_RequestedFacilityNotImplemented:	//Cause No. 69 �C Requested facility not implemented
		{
			if(IsChinese){return "Requested facility not implemented";}
			else{return "Requested facility not implemented";}
		}
	case		Q850_OnlyRestrictedDigitalInfo:		//Cause No. 70 �C Only restricted digital information bearer capability is available (national use) 
		{
			if(IsChinese){return "Only restricted digital information bearer capability is available (national use)";}
			else{return "Only restricted digital information bearer capability is available (national use)";}
		}
	case		Q850_ServiceOrOptionNotImplemented:	//Cause No. 79 �C Service or option not implemented, unspecified
		{
			if(IsChinese){return "Service or option not implemented, unspecified";}
			else{return "Service or option not implemented, unspecified";}
		}
	case		Q850_InvalidCallReferenceValue:		//Cause No. 81 �C Invalid call reference value
		{
			if(IsChinese){return "Invalid call reference value";}
			else{return "Invalid call reference value";}
		}
	case		Q850_IdentifiedChannelDoesNotExist:		//Cause No. 82 �C Identified channel does not exist
		{
			if(IsChinese){return "Identified channel does not exist";}
			else{return "Identified channel does not exist";}
		}
	case		Q850_ASuspendedCallExists:		//Cause No. 83 �C A suspended call exists, but this call identity does not
		{
			if(IsChinese){return "A suspended call exists, but this call identity does not";}
			else{return "A suspended call exists, but this call identity does not";}
		}
	case		Q850_CallIdentityInUse:			//Cause No. 84 �C Call identity in use
		{
			if(IsChinese){return "Call identity in use";}
			else{return "Call identity in use";}
		}
	case		Q850_NoCallSuspended:		//Cause No. 85 �C No call suspended
		{
			if(IsChinese){return "No call suspended";}
			else{return "No call suspended";}
		}
	case		Q850_CallHavingTheRequested:		//Cause No. 86 �C Call having the requested call identity has been cleared
		{
			if(IsChinese){return "Call having the requested call identity has been cleared";}
			else{return "Call having the requested call identity has been cleared";}
		}
	case		Q850_UserNotMemberOfCUG:		//Cause No. 87 �C User not member of CUG
		{
			if(IsChinese){return "User not member of CUG";}
			else{return "User not member of CUG";}
		}
	case		Q850_IncompatibleDestination:			//Cause No. 88 �C Incompatible destination
		{
			if(IsChinese){return "Incompatible destination";}
			else{return "Incompatible destination";}
		}
	case		Q850_NonExistentCUG:			//Cause No. 90 �C Non-existent CUG
		{
			if(IsChinese){return "Non-existent CUG";}
			else{return "Non-existent CUG";}
		}
	case		Q850_InvalidTransitNetwork:		//Cause No. 91 �C Invalid transit network selection (national use)
		{
			if(IsChinese){return "Invalid transit network selection (national use)";}
			else{return "Invalid transit network selection (national use)";}
		}
	case		Q850_InvalidMessage:		//Cause No. 95 �C Invalid message, unspecified
		{
			if(IsChinese){return "Invalid message, unspecified";}
			else{return "Invalid message, unspecified";}
		}
	case		Q850_MandatoryInformation:			//Cause No. 96 �C Mandatory information element is missing
		{
			if(IsChinese){return "Mandatory information element is missing";}
			else{return "Mandatory information element is missing";}
		}
	case		Q850_MessageTypeNonExistent:		//Cause No. 97 �C Message type non-existent or not implemented
		{
			if(IsChinese){return " Message type non-existent or not implemented";}
			else{return " Message type non-existent or not implemented";}
		}
	case		Q850_MessageNotCompatible:		//Cause No. 98 �C Message not compatible with call state or message type non-existent or not implemented
		{
			if(IsChinese){return "Message not compatible with call state or message type non-existent or not implemented";}
			else{return "Message not compatible with call state or message type non-existent or not implemented";}
		}
	case		Q850_ParameterNonExistent:			//Cause No. 99 �C Information element/parameter non-existent or not implemented
		{
			if(IsChinese){return "Information element/parameter non-existent or not implemented";}
			else{return "Information element/parameter non-existent or not implemented";}
		}
	case		Q850_InvalidInformationElement:			//Cause No. 100 �C Invalid information element contents
		{
			if(IsChinese){return "Invalid information element contents";}
			else{return "Invalid information element contents";}
		}
	case		Q850_MessageNotCompatibleWithCallState:		//Cause No. 101 �C Message not compatible with call state
		{
			if(IsChinese){return "Message not compatible with call state";}
			else{return "Message not compatible with call state";}
		}
	case		Q850_RecoveryOnTimerExpiry:		//Cause No: 102 �C Recovery on timer expiry
		{
			if(IsChinese){return "Recovery on timer expiry";}
			else{return "Recovery on timer expiry";}
		}
	case		Q850_MessageWithUnrecognizedParameterDiscarded:		//Cause No: 110 �C Message with unrecognized parameter discarded
		{
			if(IsChinese){return "Message with unrecognized parameter discarded";}
			else{return "Message with unrecognized parameter discarded";}
		}
	case		Q850_ProtocolError:		//Cause No. 111 �C Protocol error, unspecified
		{
			if(IsChinese){return "Protocol error, unspecified";}
			else{return "Protocol error, unspecified";}
		}
	case		Q850_Interworking:		//Cause No. 127 �C interworking, unspecified
		{
			if(IsChinese){return "interworking, unspecified";}
			else{return "interworking, unspecified";}
		}
	default:
		{
			if(IsChinese){return "Q850δ֪ԭ��ֵ";}
			else{return "Q850 Unknown cause";}
		}
	}
}

const char* CallFlag2Str( KFPC_CALL_FLAG ct )
{
	switch(ct)
	{
	case CALL_FLAG_OUT:	return "OUT";
	case CALL_FLAG_IN:	return "IN";
	case CALL_FLAG_CONF:return "CONF";
	default:return "IN";
	}

}

time_t GetCallID_TIME( unsigned long long CallID )
{
	//	char TimeStr[128];
	//	TimeToStr(TimeStr,GetCallID_TIME()+KFPC_START_TIME);

	KFPC_CallID*	pCallID;

	pCallID = (KFPC_CallID*)&CallID;

	return pCallID->CallIDInfo.Time+KFPC_START_TIME;
}

const char* CallWaitTypeToStr( CallWaitType_t cwt )
{
	switch(cwt)
	{
	case CWT_NULL:		return "NULL";
	case CWT_ROUTEING:	return "ROUTEING";
	case CWT_QUEUE:		return "QUEUE";
	case CWT_HOLD:		return "HOLD";
	case CWT_RING:		return "RING";
	default:			return "NULL";
	}
}

unsigned int GetExp( unsigned int Val )
{
	unsigned int Count = 0;
	while(Val > 0)
	{
		Val = Val >> 1;
		Count ++;
	}
	return Count;
}

KFPC_SignalType IntToSignalType( unsigned int val )
{
	switch(val)
	{
	case KFPC_SignalType_R2_CHINA:					/**< R2 */
	case KFPC_SignalType_R2_BASEIC:			/**< R2 */
	case KFPC_SignalType_ISDN_N:				/**< ISDN */
	case KFPC_SignalType_ISDN_U:				/**< ISDN */
	case KFPC_SignalType_SS7_TUP:				/**< SS7 */
	case KFPC_SignalType_SS7_ISUP:				/**< SS7 */
	case KFPC_SignalType_ClearChannel:		/**< ͸��ͨ�� */
	case KFPC_SignalType_FXS:				/**< ���� */
	case KFPC_SignalType_SIP:				/**< SIP */
	case KFPC_SignalType_FXO:				/**< ���� */
		return (KFPC_SignalType) val;
	default: return KFPC_SignalType_ISDN_N;
	}
}

const char* ExtTypeToStr( EXT_TYPE_t et )
{
	switch(et)
	{
	case EXT_TYPE_NULL:
		{
			return "NULL";
		}
		break;
	case EXT_TYPE_GENERAL:
		{
			return "GENERAL";
		}
		break;
	case EXT_TYPE_VIRTUAL:	//����ֻ�
		{
			return "VIRTUAL";
		}
		break;
	default:	return "NULL";
	}
}

EXT_TYPE_t IntToExtType( unsigned int val )
{
	switch(val)
	{
	case 0: return EXT_TYPE_NULL;
	case 1: return EXT_TYPE_GENERAL;
	case 2: return EXT_TYPE_VIRTUAL;
	default:return EXT_TYPE_GENERAL;
	}
}

const char* OperateTypeToStr( KFPC_DB_OPERATE_TYPE t )
{
	switch(t)
	{
	case KFPC_Operate_Initialize:
		{
			return "Initialize";
		}
		break;
	case KFPC_Operate_Insert:
		{
			return "Insert";
		}
		break;
	case KFPC_Operate_Update:
		{
			return "Update";
		}
		break;
	case KFPC_Operate_Delete:
		{
			return "Delete";
		}
		break;
	default:
		return "NULL";
	}
}