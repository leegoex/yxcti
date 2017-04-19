#ifndef KFPC_TServerErr_h__
#define KFPC_TServerErr_h__

#include "kfpc_id.h"
#include "kfpc_error.h"

/**
 *	联络中心第三方系统错误类型
 */
#define KFPC_RESULT_TYPE_EH		0x04		/**< EH交换机错误 */
#define KFPC_EH_ERR(x)			KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_EH,0,x)		/**< EH交换机错误代码 */


const unsigned int KFPC_ERR_TrunkGroupNotFound			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,1);	/**< 中继组没有找到 */
const unsigned int KFPC_ERR_TrunkGroupNoChannelBlock	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,2);	/**< 中继组没有通道资源 */
const unsigned int KFPC_ERR_LookUpIdleChannelTypeErr	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,3);	/**< 查询空闲通道类型错误 */
const unsigned int KFPC_ERR_NotFoundIdleChannel			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,4);	/**< 未找到空闲通道 */
const unsigned int KFPC_ERR_VoiceStatusErr			    =	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,5);	/**< IVR 语音状态错误 */
const unsigned int KFPC_ERR_StopPlayFailed			    =	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,6);	/**< IVR 停止放音失败 */
const unsigned int KFPC_ERR_RecordFileFailed		    =	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,7);	/**< IVR 录音失败 */
const unsigned int KFPC_ERR_IVRChBusy					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,8);	/**< IVR 通道忙 */
const unsigned int KFPC_ERR_InvalidDigitsMode			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,9);	/**< IVR 无效收号模式 */
const unsigned int KFPC_ERR_ChResIsNull					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,10);	/**< 通道资源是空 */
const unsigned int KFPC_ERR_MsgIDNotMatch				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,11);	/**< 消息ID不匹配 */
const unsigned int KFPC_ERR_CmdWaitAck					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,12);	/**< 命令执行等待Ack */
const unsigned int KFPC_ERR_CmdExeCompleted				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,13);	/**< 命令执行完成 */
const unsigned int KFPC_ERR_ChannelStautsErr			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,14);	/**< 通道状态 */
const unsigned int KFPC_ERR_InxOverSize 				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,15);	/**< Voice File Oversized */
const unsigned int KFPC_ERR_FileFormatErr 				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,16);	/**< Voice File Format Error */
const unsigned int KFPC_ERR_PlayFileFailed 				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,17);	/**< Play Voice File Failure */
const unsigned int KFPC_ERR_GetRecordSerFailed			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,18);	/**< Get Record Server Failure */
const unsigned int KFPC_ERR_PlayDailToneFailed			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,19);	/**< Play Dial Tone Failure */
const unsigned int KFPC_ERR_StartCollectDigFailed		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,20);	/**< Start Collect Digit Failure */
const unsigned int KFPC_ERR_StopCollectDigFailed		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,21);	/**< Stop Collect Digit Failure */
const unsigned int KFPC_ERR_NoCollectDigitMode			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,22);	/**< No Collect Digit Mode */
const unsigned int KFPC_ERR_NoConfig					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,23);	/**< 没有配置 */
const unsigned int KFPC_ERR_IPMChAssignFailed			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,24);	/**< IPM 通道分配错误 */
const unsigned int KFPC_ERR_GetCodeListFailed			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,25);	/**< 查找语音编码错误 */
const unsigned int KFPC_ERR_GetCmdIDFailed				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,26);	/**< 无效的CMDID */
const unsigned int KFPC_ERR_AppIDInvalid				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,27);	/**< 需使用的AppID无效 */
const unsigned int KFPC_ERR_ChIDInvalid					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,28);	/**< Ch ID无效 */
const unsigned int KFPC_ERR_NoRecordSer					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,29);	/**< Record server无效 */
const unsigned int KFPC_ERR_DevHandleInvalid			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,30);	/**< Dev handle无效 */
const unsigned int KFPC_ERR_FailedToGetNode 			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,31);	/**< Node无效 */
const unsigned int KFPC_ERR_IVRChAssignFailed			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,32);	/**< IVR 通道分配错误 */
const unsigned int KFPC_ERR_CalledNoRoute				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,33);	/**< 被叫号找不到出路由 */
const unsigned int KFPC_ERR_ScrouteFailed				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,34);	/**<  交换通道错误 */
const unsigned int KFPC_ERR_AGChStatusErr				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,35);	/**<  模拟通道状态错误 */
const unsigned int KFPC_ERR_LookupIdleChannelInBlock    =	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,36);	/**<  获取空闲通道错误 */
const unsigned int KFPC_ERR_GenRingFail					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,37);	/**<  产生振铃失败 */
const unsigned int KFPC_ERR_NoDailTone					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,38);	/**<  没有拔号音 */
const unsigned int KFPC_ERR_OnHookFail					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,39);	/**<  挂机失败 */
const unsigned int KFPC_ERR_CallIDInvalid				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,40);	/**<  CallID无效 */
const unsigned int KFPC_ERR_CmdCancel					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,41);	/**<  命令取消 */
const unsigned int KFPC_ERR_NoSwitchRes					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,42);	/**<  没有连接资源 */
const unsigned int KFPC_ERR_GetIdleConfFail				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,43);	/**<  获得空闲会议ID失败 */
const unsigned int KFPC_ERR_ConfSizeTooBig				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,44);	/**<  会议方数太大 */
const unsigned int KFPC_ERR_ConfSizeTooSmall			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,45);	/**<  会议方数太小 */
const unsigned int KFPC_ERR_NoConfResBind				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,46);	/**<  没有邦定会议资源 */
const unsigned int KFPC_ERR_CallOutFailed				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,47);	/**<  呼出失败 */
const unsigned int KFPC_ERR_AcceptCallFailed			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,48);	/**<  AcceptCall失败 */
const unsigned int KFPC_ERR_AnswerCallFailed			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,49);	/**<  AnswerCall失败 */
const unsigned int KFPC_ERR_ConfCallIDInvalid			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,50);	/**<  会议ID 无效 */
const unsigned int KFPC_ERR_NoIdleConfRes				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,51);	/**<  没有空闲会议资源 */
const unsigned int KFPC_ERR_ChannelConfResErr			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,52);	/**<  通道会议资源错误 */
const unsigned int KFPC_ERR_VoiceChNotFound			    =	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,53);	/**<  找不到VoiceCh */
const unsigned int KFPC_ERR_ChannelResBusy			    =	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,54);	/**<  通道资源忙 */
const unsigned int KFPC_ERR_NoIVRRes				    =	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,55);	/**<  没有IVR资源 */
const unsigned int KFPC_ERR_IVRAlreadyConnected			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,56);	/**<  IVR已是连接状态*/
const unsigned int KFPC_ERR_NoAvailableFaxSer			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,57);	/**<  无可用传真服务器*/
const unsigned int KFPC_ERR_ChStatusErr					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,58);	/**<  通道状态错误*/
const unsigned int KFPC_ERR_ChRuningCmd					=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,59);	/**<  通道正在执行CMD*/
const unsigned int KFPC_ERR_NotStatusToCreateMix		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,60);	/**<  非正常状态下生成MIX会议*/
const unsigned int KFPC_ERR_CallIDConflict				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,61);	/**<  Call id 冲突*/
const unsigned int KFPC_ERR_ChConTypeErr				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,62);	/**<  通道连接类型错误*/
const unsigned int KFPC_RetrieveVoiceFileFail			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,63);	/**<  分析文件名失败*/
const unsigned int KFPC_ERR_VoiceIsInDtmf				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,64);	/**<  正在收号*/
const unsigned int KFPC_ERR_VoiceIsInPlay				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,65);	/**<  正在放音*/
const unsigned int KFPC_ERR_ChannelAction				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,66);	/**<  通道ACTION错误*/
const unsigned int KFPC_ERR_ChannelTypeErr				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,67);	/**<  通道类型错误*/
const unsigned int KFPC_ERR_FAXAlreadyConnected			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,68);	/**<  FAX已是连接状态*/
const unsigned int KFPC_ERR_ChannelReleased				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,69);	/**<  通道释放*/
const unsigned int KFPC_ERR_DSPERR						=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,70);	/**<  DSP错误*/
const unsigned int KFPC_ERR_FAXDisconnected				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,71);	/**<  Fax server 下线*/
const unsigned int KFPC_ERR_CmdIDInvalid				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,72);	/**<  CMDID 无效*/
const unsigned int KFPC_ERR_VoiceIDInvalid				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,73);	/**<  语音ID 无效*/
const unsigned int KFPC_ERR_SipCallOutAddr				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,74);	/**<  SIP呼出参数无效*/
const unsigned int KFPC_ERR_NoIPMCh						=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_WARNING,KFPC_ID_CLASS_COM_TSERVER,75);	/**<  没有IPM 通道 */

static const char* ErrorCodeToStr(unsigned int ErrorCode,unsigned int Lang = 0)
{
	switch(ErrorCode)
	{
	case 0											:return (Lang == 0)? "successful"					:	"成功 ";
	case KFPC_ERR_TrunkGroupNotFound				:return (Lang == 0)? "TrunkGroupNotFound"			:	"中继组 ";
	case KFPC_ERR_TrunkGroupNoChannelBlock			:return (Lang == 0)? "TrunkGroupNoChannelBlock"		:	"没有找到中继组没有通道资源";
	case KFPC_ERR_LookUpIdleChannelTypeErr			:return (Lang == 0)? "LookUpIdleChannelTypeErr"		:	"查询空闲通道类型错误 ";
	case KFPC_ERR_NotFoundIdleChannel				:return (Lang == 0)? "NotFoundIdleChannel"			:	"未找到空闲通道 ";
	case KFPC_ERR_VoiceStatusErr    				:return (Lang == 0)? "VoiceStatusErr"				:	"IVR 语音状态错误 ";
	case KFPC_ERR_StopPlayFailed    				:return (Lang == 0)? "StopPlayFailed"				:	"IVR 停止放音失败 ";
	case KFPC_ERR_RecordFileFailed    				:return (Lang == 0)? "RecordFileFailed"				:	"IVR 录音失败 ";
	case KFPC_ERR_IVRChBusy							:return (Lang == 0)? "IVRChBusy"					:	"IVR 通道忙 ";
	case KFPC_ERR_InvalidDigitsMode					:return (Lang == 0)? "InvalidDigitsMode"			:	"IVR 无效收号模式 ";
	case KFPC_ERR_ChResIsNull						:return (Lang == 0)? "ChResIsNull"					:	"通道资源是空 ";
	case KFPC_ERR_MsgIDNotMatch						:return (Lang == 0)? "MsgIDNotMatch"				:	"消息ID不匹配 ";
	case KFPC_ERR_CmdWaitAck						:return (Lang == 0)? "CmdWaitAck"					:	"命令执行等待Ack ";
	case KFPC_ERR_CmdExeCompleted					:return (Lang == 0)? "CmdExeCompleted"				:	"命令执行完成 ";
	case KFPC_ERR_ChannelStautsErr					:return (Lang == 0)? "ChannelStautsErr"				:	"通道状态错误 ";
	case KFPC_ERR_InxOverSize 						:return (Lang == 0)? "InxOverSize"					:	"Voice File Oversized ";
	case KFPC_ERR_FileFormatErr 					:return (Lang == 0)? "FileFormatErr"				:	"Voice File Format Errore ";
	case KFPC_ERR_PlayFileFailed 					:return (Lang == 0)? "PlayFileFailed"				:	"Play Voice File Failur ";
	case KFPC_ERR_GetRecordSerFailed				:return (Lang == 0)? "GetRecordSerFailed"			:	"Get Record Server Failure ";
	case KFPC_ERR_PlayDailToneFailed				:return (Lang == 0)? "PlayDailToneFailed"			:	"Play Dial Tone Failure ";
	case KFPC_ERR_StartCollectDigFailed				:return (Lang == 0)? "StartCollectDigFailed"		:	"Start Collect Digit Failure ";
	case KFPC_ERR_StopCollectDigFailed				:return (Lang == 0)? "StopCollectDigFailed"			:	"Stop Collect Digit Failure ";
	case KFPC_ERR_NoCollectDigitMode				:return (Lang == 0)? "NoCollectDigitMode"			:	"No Collect Digit Mode ";
	case KFPC_ERR_NoConfig							:return (Lang == 0)? "NoConfig"						:	"没有配置 ";
	case KFPC_ERR_IPMChAssignFailed					:return (Lang == 0)? "IPMChAssignFailed"			:	"IPM 通道分配错误 ";
	case KFPC_ERR_GetCodeListFailed					:return (Lang == 0)? "GetCodeListFailed"			:	"查找语音编码错误 ";
	case KFPC_ERR_GetCmdIDFailed					:return (Lang == 0)? "GetCmdIDFailed"				:	"无效的CMDID ";
	case KFPC_ERR_AppIDInvalid						:return (Lang == 0)? "AppIDInvalid"					:	"需使用的AppID无效 ";
	case KFPC_ERR_ChIDInvalid						:return (Lang == 0)? "ChIDInvalid"					:	"Ch ID无效 ";
	case KFPC_ERR_NoRecordSer						:return (Lang == 0)? "NoRecordSer"					:	"Record server无效 ";
	case KFPC_ERR_DevHandleInvalid					:return (Lang == 0)? "DevHandleInvalid"				:	"Dev handle无效";
	case KFPC_ERR_FailedToGetNode 					:return (Lang == 0)? "FailedToGetNode"				:	"Node无效";
	case KFPC_ERR_IVRChAssignFailed					:return (Lang == 0)? "IVRChAssignFailed"			:	"IVR通道分配错误";
	case KFPC_ERR_CalledNoRoute						:return (Lang == 0)? "CalledNoRoute"				:	"被叫号找不到出路由";
	case KFPC_ERR_ScrouteFailed						:return (Lang == 0)? "ScrouteFailed"				:	"交换通道错误";
	case KFPC_ERR_AGChStatusErr						:return (Lang == 0)? "AGChStatusErr"				:	"模拟通道状态错误";
	case KFPC_ERR_LookupIdleChannelInBlock    		:return (Lang == 0)? "LookupIdleChannelInBlock"		:	"获取空闲通道错误";
	case KFPC_ERR_GenRingFail						:return (Lang == 0)? "GenRingFail"					:	"产生振铃失败";
	case KFPC_ERR_NoDailTone						:return (Lang == 0)? "NoDailTone"					:	"没有拔号音";
	case KFPC_ERR_OnHookFail						:return (Lang == 0)? "OnHookFail"					:	"挂机失败";
	case KFPC_ERR_CallIDInvalid						:return (Lang == 0)? "CallIDInvalid"				:	"CallID无效";
	case KFPC_ERR_CmdCancel							:return (Lang == 0)? "CmdCancel"					:	"命令取消";
	case KFPC_ERR_NoSwitchRes						:return (Lang == 0)? "NoSwitchRes"					:	"没有连接资源";
	case KFPC_ERR_GetIdleConfFail					:return (Lang == 0)? "GetIdleConfFail"				:	"获得空闲会议ID失败";
	case KFPC_ERR_ConfSizeTooBig					:return (Lang == 0)? "ConfSizeTooBig"				:	"会议方数太大";
	case KFPC_ERR_ConfSizeTooSmall					:return (Lang == 0)? "ConfSizeTooSmall"				:	"会议方数太小";
	case KFPC_ERR_NoConfResBind						:return (Lang == 0)? "NoConfResBind"				:	"没有绑定会议资源";
	case KFPC_ERR_CallOutFailed						:return (Lang == 0)? "CallOutFailed"				:	"呼出失败";
	case KFPC_ERR_AcceptCallFailed					:return (Lang == 0)? "AcceptCallFailed"				:	"AcceptCall失败";
	case KFPC_ERR_AnswerCallFailed					:return (Lang == 0)? "AnswerCallFailed"				:	"AnswerCall失败";
	case KFPC_ERR_ConfCallIDInvalid					:return (Lang == 0)? "ConfCallIDInvalid"			:	"会议ID无效";
	case KFPC_ERR_NoIdleConfRes						:return (Lang == 0)? "NoIdleConfRes"				:	"没有空闲会议资源";
	case KFPC_ERR_ChannelConfResErr					:return (Lang == 0)? "ChannelConfResErr"			:	"通道会议资源错误";
	case KFPC_ERR_VoiceChNotFound					:return (Lang == 0)? "VoiceChNotFound"				:	"找不到VoiceCh";
	case KFPC_ERR_ChannelResBusy					:return (Lang == 0)? "ChannelResBusy"				:	"通道资源忙";
	case KFPC_ERR_NoIVRRes							:return (Lang == 0)? "NoIVRRes"						:	"没有IVR资源";
	case KFPC_ERR_NoAvailableFaxSer					:return (Lang == 0)? "NoAvailableFaxSer"			:	"IVR已是连接状态器";
	case KFPC_ERR_IVRAlreadyConnected				:return (Lang == 0)? "KFPC_ERR_IVRAlreadyConnected"	:	"无可用传真服务";
	case KFPC_ERR_ChStatusErr						:return (Lang == 0)? "KFPC_ERR_ChStatusErr"			:	"通道状态错误";
	case KFPC_ERR_ChRuningCmd						:return (Lang == 0)? "ChRuningCmd"					:	"通道正在执行CMD";
	case KFPC_ERR_CallIDConflict					:return (Lang == 0)? "CallIDConflict"				:	"Callid冲突";
	case KFPC_ERR_ChConTypeErr						:return (Lang == 0)? "ChConTypeErr"					:	"通道连接类型错误";
	case KFPC_RetrieveVoiceFileFail					:return (Lang == 0)? "RetrieveVoiceFileFail"		:	"分析文件名失败";
	case KFPC_ERR_VoiceIsInDtmf						:return (Lang == 0)? "VoiceIsInDtmf"				:	"正在收号";
	case KFPC_ERR_VoiceIsInPlay						:return (Lang == 0)? "VoiceIsInPlay"				:	"正在放音";
	case KFPC_ERR_ChannelAction						:return (Lang == 0)? "ChannelAction"				:	"通道ACTION错误";
	case KFPC_ERR_ChannelTypeErr					:return (Lang == 0)? "ChannelTypeErr"				:	"通道类型错误";
	case KFPC_ERR_FAXAlreadyConnected				:return (Lang == 0)? "FAXAlreadyConnected"			:	"FAX已是连接状态";
	case KFPC_ERR_ChannelReleased					:return (Lang == 0)? "ChannelReleased"				:	"通道释放";
	case KFPC_ERR_DSPERR							:return (Lang == 0)? "DSPERR"						:	"DSP错误";
	case KFPC_ERR_FAXDisconnected					:return (Lang == 0)? "FaxServerDisconnected"		:	"Faxserver下线";
	case KFPC_ERR_CmdIDInvalid						:return (Lang == 0)? "CmdIDInvalid"					:	"CMD ID无效";
	case KFPC_ERR_VoiceIDInvalid					:return (Lang == 0)? "VoiceIDInvalid"				:	"语音ID 无效";
	case KFPC_ERR_SipCallOutAddr					:return (Lang == 0)? "SipCallOutAddrInvalid"		:	"SIP呼出参数无效";
	case KFPC_ERR_NoIPMCh							:return (Lang == 0)? "NoIPMCh"						:	"没有IPM 通道";
	default											:return (Lang == 0)? "Unknown_ErrorType"			:	"未知错误";

	}
}
#endif // KFPC_TServerErr_h__
