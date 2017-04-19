#ifndef KFPC_TServerErr_h__
#define KFPC_TServerErr_h__

#include "kfpc_id.h"
#include "kfpc_error.h"

/**
 *	�������ĵ�����ϵͳ��������
 */
#define KFPC_RESULT_TYPE_EH		0x04		/**< EH���������� */
#define KFPC_EH_ERR(x)			KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_EH,0,x)		/**< EH������������� */


const unsigned int KFPC_ERR_TrunkGroupNotFound			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,1);	/**< �м���û���ҵ� */
const unsigned int KFPC_ERR_TrunkGroupNoChannelBlock	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,2);	/**< �м���û��ͨ����Դ */
const unsigned int KFPC_ERR_LookUpIdleChannelTypeErr	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,3);	/**< ��ѯ����ͨ�����ʹ��� */
const unsigned int KFPC_ERR_NotFoundIdleChannel			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,4);	/**< δ�ҵ�����ͨ�� */
const unsigned int KFPC_ERR_VoiceStatusErr			    =	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,5);	/**< IVR ����״̬���� */
const unsigned int KFPC_ERR_StopPlayFailed			    =	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,6);	/**< IVR ֹͣ����ʧ�� */
const unsigned int KFPC_ERR_RecordFileFailed		    =	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,7);	/**< IVR ¼��ʧ�� */
const unsigned int KFPC_ERR_IVRChBusy					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,8);	/**< IVR ͨ��æ */
const unsigned int KFPC_ERR_InvalidDigitsMode			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,9);	/**< IVR ��Ч�պ�ģʽ */
const unsigned int KFPC_ERR_ChResIsNull					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,10);	/**< ͨ����Դ�ǿ� */
const unsigned int KFPC_ERR_MsgIDNotMatch				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,11);	/**< ��ϢID��ƥ�� */
const unsigned int KFPC_ERR_CmdWaitAck					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,12);	/**< ����ִ�еȴ�Ack */
const unsigned int KFPC_ERR_CmdExeCompleted				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,13);	/**< ����ִ����� */
const unsigned int KFPC_ERR_ChannelStautsErr			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,14);	/**< ͨ��״̬ */
const unsigned int KFPC_ERR_InxOverSize 				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,15);	/**< Voice File Oversized */
const unsigned int KFPC_ERR_FileFormatErr 				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,16);	/**< Voice File Format Error */
const unsigned int KFPC_ERR_PlayFileFailed 				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,17);	/**< Play Voice File Failure */
const unsigned int KFPC_ERR_GetRecordSerFailed			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,18);	/**< Get Record Server Failure */
const unsigned int KFPC_ERR_PlayDailToneFailed			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,19);	/**< Play Dial Tone Failure */
const unsigned int KFPC_ERR_StartCollectDigFailed		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,20);	/**< Start Collect Digit Failure */
const unsigned int KFPC_ERR_StopCollectDigFailed		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,21);	/**< Stop Collect Digit Failure */
const unsigned int KFPC_ERR_NoCollectDigitMode			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,22);	/**< No Collect Digit Mode */
const unsigned int KFPC_ERR_NoConfig					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,23);	/**< û������ */
const unsigned int KFPC_ERR_IPMChAssignFailed			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,24);	/**< IPM ͨ��������� */
const unsigned int KFPC_ERR_GetCodeListFailed			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,25);	/**< ��������������� */
const unsigned int KFPC_ERR_GetCmdIDFailed				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,26);	/**< ��Ч��CMDID */
const unsigned int KFPC_ERR_AppIDInvalid				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,27);	/**< ��ʹ�õ�AppID��Ч */
const unsigned int KFPC_ERR_ChIDInvalid					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,28);	/**< Ch ID��Ч */
const unsigned int KFPC_ERR_NoRecordSer					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,29);	/**< Record server��Ч */
const unsigned int KFPC_ERR_DevHandleInvalid			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,30);	/**< Dev handle��Ч */
const unsigned int KFPC_ERR_FailedToGetNode 			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,31);	/**< Node��Ч */
const unsigned int KFPC_ERR_IVRChAssignFailed			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,32);	/**< IVR ͨ��������� */
const unsigned int KFPC_ERR_CalledNoRoute				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,33);	/**< ���к��Ҳ�����·�� */
const unsigned int KFPC_ERR_ScrouteFailed				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,34);	/**<  ����ͨ������ */
const unsigned int KFPC_ERR_AGChStatusErr				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,35);	/**<  ģ��ͨ��״̬���� */
const unsigned int KFPC_ERR_LookupIdleChannelInBlock    =	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,36);	/**<  ��ȡ����ͨ������ */
const unsigned int KFPC_ERR_GenRingFail					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,37);	/**<  ��������ʧ�� */
const unsigned int KFPC_ERR_NoDailTone					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,38);	/**<  û�аκ��� */
const unsigned int KFPC_ERR_OnHookFail					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,39);	/**<  �һ�ʧ�� */
const unsigned int KFPC_ERR_CallIDInvalid				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,40);	/**<  CallID��Ч */
const unsigned int KFPC_ERR_CmdCancel					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,41);	/**<  ����ȡ�� */
const unsigned int KFPC_ERR_NoSwitchRes					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,42);	/**<  û��������Դ */
const unsigned int KFPC_ERR_GetIdleConfFail				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,43);	/**<  ��ÿ��л���IDʧ�� */
const unsigned int KFPC_ERR_ConfSizeTooBig				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,44);	/**<  ���鷽��̫�� */
const unsigned int KFPC_ERR_ConfSizeTooSmall			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,45);	/**<  ���鷽��̫С */
const unsigned int KFPC_ERR_NoConfResBind				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,46);	/**<  û�а������Դ */
const unsigned int KFPC_ERR_CallOutFailed				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,47);	/**<  ����ʧ�� */
const unsigned int KFPC_ERR_AcceptCallFailed			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,48);	/**<  AcceptCallʧ�� */
const unsigned int KFPC_ERR_AnswerCallFailed			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,49);	/**<  AnswerCallʧ�� */
const unsigned int KFPC_ERR_ConfCallIDInvalid			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,50);	/**<  ����ID ��Ч */
const unsigned int KFPC_ERR_NoIdleConfRes				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,51);	/**<  û�п��л�����Դ */
const unsigned int KFPC_ERR_ChannelConfResErr			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,52);	/**<  ͨ��������Դ���� */
const unsigned int KFPC_ERR_VoiceChNotFound			    =	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,53);	/**<  �Ҳ���VoiceCh */
const unsigned int KFPC_ERR_ChannelResBusy			    =	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,54);	/**<  ͨ����Դæ */
const unsigned int KFPC_ERR_NoIVRRes				    =	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,55);	/**<  û��IVR��Դ */
const unsigned int KFPC_ERR_IVRAlreadyConnected			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,56);	/**<  IVR��������״̬*/
const unsigned int KFPC_ERR_NoAvailableFaxSer			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,57);	/**<  �޿��ô��������*/
const unsigned int KFPC_ERR_ChStatusErr					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,58);	/**<  ͨ��״̬����*/
const unsigned int KFPC_ERR_ChRuningCmd					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,59);	/**<  ͨ������ִ��CMD*/
const unsigned int KFPC_ERR_NotStatusToCreateMix		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,60);	/**<  ������״̬������MIX����*/
const unsigned int KFPC_ERR_CallIDConflict				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,61);	/**<  Call id ��ͻ*/
const unsigned int KFPC_ERR_ChConTypeErr				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,62);	/**<  ͨ���������ʹ���*/
const unsigned int KFPC_RetrieveVoiceFileFail			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,63);	/**<  �����ļ���ʧ��*/
const unsigned int KFPC_ERR_VoiceIsInDtmf				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,64);	/**<  �����պ�*/
const unsigned int KFPC_ERR_VoiceIsInPlay				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,65);	/**<  ���ڷ���*/
const unsigned int KFPC_ERR_ChannelAction				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,66);	/**<  ͨ��ACTION����*/
const unsigned int KFPC_ERR_ChannelTypeErr				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,67);	/**<  ͨ�����ʹ���*/
const unsigned int KFPC_ERR_FAXAlreadyConnected			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,68);	/**<  FAX��������״̬*/
const unsigned int KFPC_ERR_ChannelReleased				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,69);	/**<  ͨ���ͷ�*/
const unsigned int KFPC_ERR_DSPERR						=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,70);	/**<  DSP����*/
const unsigned int KFPC_ERR_FAXDisconnected				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,71);	/**<  Fax server ����*/
const unsigned int KFPC_ERR_CmdIDInvalid				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,72);	/**<  CMDID ��Ч*/
const unsigned int KFPC_ERR_VoiceIDInvalid				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,73);	/**<  ����ID ��Ч*/
const unsigned int KFPC_ERR_SipCallOutAddr				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,74);	/**<  SIP����������Ч*/
const unsigned int KFPC_ERR_NoIPMCh						=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,75);	/**<  û��IPM ͨ�� */

static const char* ErrorCodeToStr(unsigned int ErrorCode,unsigned int Lang = 0)
{
	switch(ErrorCode)
	{
	case 0											:return (Lang == 0)? "successful"					:	"�ɹ� ";
	case KFPC_ERR_TrunkGroupNotFound				:return (Lang == 0)? "TrunkGroupNotFound"			:	"�м��� ";
	case KFPC_ERR_TrunkGroupNoChannelBlock			:return (Lang == 0)? "TrunkGroupNoChannelBlock"		:	"û���ҵ��м���û��ͨ����Դ";
	case KFPC_ERR_LookUpIdleChannelTypeErr			:return (Lang == 0)? "LookUpIdleChannelTypeErr"		:	"��ѯ����ͨ�����ʹ��� ";
	case KFPC_ERR_NotFoundIdleChannel				:return (Lang == 0)? "NotFoundIdleChannel"			:	"δ�ҵ�����ͨ�� ";
	case KFPC_ERR_VoiceStatusErr    				:return (Lang == 0)? "VoiceStatusErr"				:	"IVR ����״̬���� ";
	case KFPC_ERR_StopPlayFailed    				:return (Lang == 0)? "StopPlayFailed"				:	"IVR ֹͣ����ʧ�� ";
	case KFPC_ERR_RecordFileFailed    				:return (Lang == 0)? "RecordFileFailed"				:	"IVR ¼��ʧ�� ";
	case KFPC_ERR_IVRChBusy							:return (Lang == 0)? "IVRChBusy"					:	"IVR ͨ��æ ";
	case KFPC_ERR_InvalidDigitsMode					:return (Lang == 0)? "InvalidDigitsMode"			:	"IVR ��Ч�պ�ģʽ ";
	case KFPC_ERR_ChResIsNull						:return (Lang == 0)? "ChResIsNull"					:	"ͨ����Դ�ǿ� ";
	case KFPC_ERR_MsgIDNotMatch						:return (Lang == 0)? "MsgIDNotMatch"				:	"��ϢID��ƥ�� ";
	case KFPC_ERR_CmdWaitAck						:return (Lang == 0)? "CmdWaitAck"					:	"����ִ�еȴ�Ack ";
	case KFPC_ERR_CmdExeCompleted					:return (Lang == 0)? "CmdExeCompleted"				:	"����ִ����� ";
	case KFPC_ERR_ChannelStautsErr					:return (Lang == 0)? "ChannelStautsErr"				:	"ͨ��״̬���� ";
	case KFPC_ERR_InxOverSize 						:return (Lang == 0)? "InxOverSize"					:	"Voice File Oversized ";
	case KFPC_ERR_FileFormatErr 					:return (Lang == 0)? "FileFormatErr"				:	"Voice File Format Errore ";
	case KFPC_ERR_PlayFileFailed 					:return (Lang == 0)? "PlayFileFailed"				:	"Play Voice File Failur ";
	case KFPC_ERR_GetRecordSerFailed				:return (Lang == 0)? "GetRecordSerFailed"			:	"Get Record Server Failure ";
	case KFPC_ERR_PlayDailToneFailed				:return (Lang == 0)? "PlayDailToneFailed"			:	"Play Dial Tone Failure ";
	case KFPC_ERR_StartCollectDigFailed				:return (Lang == 0)? "StartCollectDigFailed"		:	"Start Collect Digit Failure ";
	case KFPC_ERR_StopCollectDigFailed				:return (Lang == 0)? "StopCollectDigFailed"			:	"Stop Collect Digit Failure ";
	case KFPC_ERR_NoCollectDigitMode				:return (Lang == 0)? "NoCollectDigitMode"			:	"No Collect Digit Mode ";
	case KFPC_ERR_NoConfig							:return (Lang == 0)? "NoConfig"						:	"û������ ";
	case KFPC_ERR_IPMChAssignFailed					:return (Lang == 0)? "IPMChAssignFailed"			:	"IPM ͨ��������� ";
	case KFPC_ERR_GetCodeListFailed					:return (Lang == 0)? "GetCodeListFailed"			:	"��������������� ";
	case KFPC_ERR_GetCmdIDFailed					:return (Lang == 0)? "GetCmdIDFailed"				:	"��Ч��CMDID ";
	case KFPC_ERR_AppIDInvalid						:return (Lang == 0)? "AppIDInvalid"					:	"��ʹ�õ�AppID��Ч ";
	case KFPC_ERR_ChIDInvalid						:return (Lang == 0)? "ChIDInvalid"					:	"Ch ID��Ч ";
	case KFPC_ERR_NoRecordSer						:return (Lang == 0)? "NoRecordSer"					:	"Record server��Ч ";
	case KFPC_ERR_DevHandleInvalid					:return (Lang == 0)? "DevHandleInvalid"				:	"Dev handle��Ч";
	case KFPC_ERR_FailedToGetNode 					:return (Lang == 0)? "FailedToGetNode"				:	"Node��Ч";
	case KFPC_ERR_IVRChAssignFailed					:return (Lang == 0)? "IVRChAssignFailed"			:	"IVRͨ���������";
	case KFPC_ERR_CalledNoRoute						:return (Lang == 0)? "CalledNoRoute"				:	"���к��Ҳ�����·��";
	case KFPC_ERR_ScrouteFailed						:return (Lang == 0)? "ScrouteFailed"				:	"����ͨ������";
	case KFPC_ERR_AGChStatusErr						:return (Lang == 0)? "AGChStatusErr"				:	"ģ��ͨ��״̬����";
	case KFPC_ERR_LookupIdleChannelInBlock    		:return (Lang == 0)? "LookupIdleChannelInBlock"		:	"��ȡ����ͨ������";
	case KFPC_ERR_GenRingFail						:return (Lang == 0)? "GenRingFail"					:	"��������ʧ��";
	case KFPC_ERR_NoDailTone						:return (Lang == 0)? "NoDailTone"					:	"û�аκ���";
	case KFPC_ERR_OnHookFail						:return (Lang == 0)? "OnHookFail"					:	"�һ�ʧ��";
	case KFPC_ERR_CallIDInvalid						:return (Lang == 0)? "CallIDInvalid"				:	"CallID��Ч";
	case KFPC_ERR_CmdCancel							:return (Lang == 0)? "CmdCancel"					:	"����ȡ��";
	case KFPC_ERR_NoSwitchRes						:return (Lang == 0)? "NoSwitchRes"					:	"û��������Դ";
	case KFPC_ERR_GetIdleConfFail					:return (Lang == 0)? "GetIdleConfFail"				:	"��ÿ��л���IDʧ��";
	case KFPC_ERR_ConfSizeTooBig					:return (Lang == 0)? "ConfSizeTooBig"				:	"���鷽��̫��";
	case KFPC_ERR_ConfSizeTooSmall					:return (Lang == 0)? "ConfSizeTooSmall"				:	"���鷽��̫С";
	case KFPC_ERR_NoConfResBind						:return (Lang == 0)? "NoConfResBind"				:	"û�а󶨻�����Դ";
	case KFPC_ERR_CallOutFailed						:return (Lang == 0)? "CallOutFailed"				:	"����ʧ��";
	case KFPC_ERR_AcceptCallFailed					:return (Lang == 0)? "AcceptCallFailed"				:	"AcceptCallʧ��";
	case KFPC_ERR_AnswerCallFailed					:return (Lang == 0)? "AnswerCallFailed"				:	"AnswerCallʧ��";
	case KFPC_ERR_ConfCallIDInvalid					:return (Lang == 0)? "ConfCallIDInvalid"			:	"����ID��Ч";
	case KFPC_ERR_NoIdleConfRes						:return (Lang == 0)? "NoIdleConfRes"				:	"û�п��л�����Դ";
	case KFPC_ERR_ChannelConfResErr					:return (Lang == 0)? "ChannelConfResErr"			:	"ͨ��������Դ����";
	case KFPC_ERR_VoiceChNotFound					:return (Lang == 0)? "VoiceChNotFound"				:	"�Ҳ���VoiceCh";
	case KFPC_ERR_ChannelResBusy					:return (Lang == 0)? "ChannelResBusy"				:	"ͨ����Դæ";
	case KFPC_ERR_NoIVRRes							:return (Lang == 0)? "NoIVRRes"						:	"û��IVR��Դ";
	case KFPC_ERR_NoAvailableFaxSer					:return (Lang == 0)? "NoAvailableFaxSer"			:	"IVR��������״̬��";
	case KFPC_ERR_IVRAlreadyConnected				:return (Lang == 0)? "KFPC_ERR_IVRAlreadyConnected"	:	"�޿��ô������";
	case KFPC_ERR_ChStatusErr						:return (Lang == 0)? "KFPC_ERR_ChStatusErr"			:	"ͨ��״̬����";
	case KFPC_ERR_ChRuningCmd						:return (Lang == 0)? "ChRuningCmd"					:	"ͨ������ִ��CMD";
	case KFPC_ERR_CallIDConflict					:return (Lang == 0)? "CallIDConflict"				:	"Callid��ͻ";
	case KFPC_ERR_ChConTypeErr						:return (Lang == 0)? "ChConTypeErr"					:	"ͨ���������ʹ���";
	case KFPC_RetrieveVoiceFileFail					:return (Lang == 0)? "RetrieveVoiceFileFail"		:	"�����ļ���ʧ��";
	case KFPC_ERR_VoiceIsInDtmf						:return (Lang == 0)? "VoiceIsInDtmf"				:	"�����պ�";
	case KFPC_ERR_VoiceIsInPlay						:return (Lang == 0)? "VoiceIsInPlay"				:	"���ڷ���";
	case KFPC_ERR_ChannelAction						:return (Lang == 0)? "ChannelAction"				:	"ͨ��ACTION����";
	case KFPC_ERR_ChannelTypeErr					:return (Lang == 0)? "ChannelTypeErr"				:	"ͨ�����ʹ���";
	case KFPC_ERR_FAXAlreadyConnected				:return (Lang == 0)? "FAXAlreadyConnected"			:	"FAX��������״̬";
	case KFPC_ERR_ChannelReleased					:return (Lang == 0)? "ChannelReleased"				:	"ͨ���ͷ�";
	case KFPC_ERR_DSPERR							:return (Lang == 0)? "DSPERR"						:	"DSP����";
	case KFPC_ERR_FAXDisconnected					:return (Lang == 0)? "FaxServerDisconnected"		:	"Faxserver����";
	case KFPC_ERR_CmdIDInvalid						:return (Lang == 0)? "CmdIDInvalid"					:	"CMD ID��Ч";
	case KFPC_ERR_VoiceIDInvalid					:return (Lang == 0)? "VoiceIDInvalid"				:	"����ID ��Ч";
	case KFPC_ERR_SipCallOutAddr					:return (Lang == 0)? "SipCallOutAddrInvalid"		:	"SIP����������Ч";
	case KFPC_ERR_NoIPMCh							:return (Lang == 0)? "NoIPMCh"						:	"û��IPM ͨ��";
	default											:return (Lang == 0)? "Unknown_ErrorType"			:	"δ֪����";

	}
}
#endif // KFPC_TServerErr_h__
