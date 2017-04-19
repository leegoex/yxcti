#ifndef kfpc_comapierr_h__
#define kfpc_comapierr_h__
#include "kfpc_id.h"
#include "kfpc_error.h"
/********************************************************************
 * @data:		2012/10/10
 * @details:	10:10:2012   19:20
 * @file: 		D:\MyProgram\通信库\kfpc_com\kfpc_comapierr.h 
 * @author:		KFPC
 * @brief:		通信库错误代码定义
*********************************************************************/
const unsigned int KFPC_RegisterHandleFail	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,1);	/**< 注册处理器失败 */
const unsigned int KFPC_AlreadyInitComLib	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,2);	/**< 已经初始化 */
const unsigned int	KFPC_UnInitComLib		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,3);	/**< 未初始化库 */
const unsigned int	KFPC_CreateFilterFail	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,4);	/**< 创建过滤器失败 */
const unsigned int	KFPC_FilterParamTooMuch	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,5);	/**< 创建过滤器参数太多 */
const unsigned int	KFPC_FilterNotExist		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,6);	/**< 过滤器不存在 */
const unsigned int	KFPC_APPIDNotExist		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,7);	/**< APPID不存在 */
const unsigned int	KFPC_AppNotConnect		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,8);	/**< APP 没有连接 */
const unsigned int	KFPC_SocketIDNotExist	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,9);	/**< SocketID不存在 */
const unsigned int	KFPC_AllocMsgFail		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,10);	/**< 分配消息失败 */
const unsigned int	KFPC_AppGroupIDNotExist =	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,11);	/**< 应用组ID不存在 */
const unsigned int	KFPC_IPErr				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,12);	/**< IP错误 */
const unsigned int	KFPC_MsgFlagErr			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,13);	/**< 消息头错误 */
const unsigned int	KFPC_MsgLenErr			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,14);	/**< 消息长度错误 */
const unsigned int	KFPC_MsgTypeErr			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,15);	/**< 消息类型错误 */
const unsigned int	KFPC_UserCloseSocket	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,16);	/**< 用户关闭Socket */
const unsigned int	KFPC_SocketIDAlreadyExist	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,17);	/**< Socket ID 已经存在 */
const unsigned int	KFPC_SocketIsClosing	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,18);	/**< Socket 正在关闭 */
const unsigned int	KFPC_TimerInvalid		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,19);	/**< 定时器无效 */
const unsigned int	KFPC_SocketIDInvalid	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,20);	/**< SocketID 无效 */
const unsigned int	KFPC_TCPSocketNotEnough	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,21);	/**< Socket不足 */
const unsigned int	KFPC_FilterInvalid		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,22);		/**< 过滤器无效 */
const unsigned int	KFPC_FilterNotEnough	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,23);		/**< 过滤器不足 */
const unsigned int	KFPC_AppMangerAlreadyOpen=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,24);		/**< 应用管理器已经打开 */
const unsigned int	KFPC_AppMangerDoesNotOpen=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,25);		/**< 应用管理器未打开 */
const unsigned int	KFPC_NO_Semaphore		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,26);		/**< 没有信号量 */
const unsigned int	KFPC_ReconnectClose		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,27);		/**< 重连关闭 */
const unsigned int	KFPC_GUID_Inequality	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,28);		/**< GUID 不相同 */
const unsigned int	KFPC_APPID_Conflict		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,29);		/**< APP ID冲突 */
const unsigned int	KFPC_UniqueIdentify_Conflict		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,30);		/**< UniqueIdentif ID冲突 */
const unsigned int	KFPC_MsgLenTooLong			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,31);	/**< 消息长度太长 */

static const char* ComErrorCodeToStr(unsigned int ErrorCode,unsigned int Lang = 0)
{
	switch(ErrorCode)
	{
	case	KFPC_RegisterHandleFail	:return (Lang == 0)? "RegisterHandleFail":	"注册处理器失败";
	case	KFPC_AlreadyInitComLib	:return (Lang == 0)? "AlreadyInitComLib" :	"已经初始化";
	case	KFPC_UnInitComLib		:return (Lang == 0)? "UnInitComLib"		 :  "未初始化库";
	case	KFPC_CreateFilterFail	:return (Lang == 0)?"":"创建过滤器失败";
	case	KFPC_FilterParamTooMuch	:return (Lang == 0)?"FilterParamTooMuch":"创建过滤器参数太多";
	case	KFPC_FilterNotExist		:return (Lang == 0)?"FilterNotExist":"过滤器不存在";
	case	KFPC_APPIDNotExist		:return (Lang == 0)?"APPIDNotExist":"APPID不存在";
	case	KFPC_AppNotConnect		:return (Lang == 0)?"AppNotConnect":"APP 没有连接";
	case	KFPC_SocketIDNotExist	:return (Lang == 0)?"SocketIDNotExist":"SocketID不存在";
	case	KFPC_AllocMsgFail		:return (Lang == 0)?"AllocMsgFail":"分配消息失败";
	case	KFPC_AppGroupIDNotExist :return (Lang == 0)?"AppGroupIDNotExist":"应用组ID不存在";
	case	KFPC_IPErr				:return (Lang == 0)?"IPErr":"IP错误";
	case	KFPC_MsgFlagErr			:return (Lang == 0)?"MsgFlagErr	":"消息头错误";
	case	KFPC_MsgLenErr			:return (Lang == 0)?"MsgLenErr":"消息长度错误";
	case	KFPC_MsgTypeErr			:return (Lang == 0)?"MsgTypeErr":"消息类型错误";
	case	KFPC_UserCloseSocket	:return (Lang == 0)?"UserCloseSocket":"用户关闭Socket";
	case	KFPC_SocketIDAlreadyExist	:return (Lang == 0)?"SocketIDAlreadyExist":"Socket ID 已经存在";
	case	KFPC_SocketIsClosing	:return (Lang == 0)?"SocketIsClosing":"Socket 正在关闭";
	case	KFPC_TimerInvalid		:return (Lang == 0)?"TimerInvalid":"定时器无效";
	case	KFPC_SocketIDInvalid	:return (Lang == 0)?"SocketIDInvalid":"SocketID 无效";
	case	KFPC_TCPSocketNotEnough	:return (Lang == 0)?"TCPSocketNotEnough":"Socket不足";
	case	KFPC_FilterInvalid		:return (Lang == 0)?"FilterInvalid":"过滤器无效";
	case	KFPC_FilterNotEnough	:return (Lang == 0)?"ilterNotEnough":" 过滤器不足";
	case	KFPC_AppMangerAlreadyOpen:return (Lang == 0)?"AppMangerAlreadyOpen":"应用管理器已经打开";
	case	KFPC_AppMangerDoesNotOpen:return (Lang == 0)?"AppMangerDoesNotOpen":"应用管理器未打开";
	case	KFPC_NO_Semaphore:return (Lang == 0)?"NOSemaphore":"没有信号量";
	case	KFPC_ReconnectClose:return (Lang == 0)?"ReconnectClose":"重连关闭";
	case	KFPC_GUID_Inequality:return (Lang == 0)?"GUID_Inequality":" GUID 不相同";
	case	KFPC_APPID_Conflict:return (Lang == 0)?"APPID_Conflict":" APP ID冲突";
	case	KFPC_UniqueIdentify_Conflict:return (Lang == 0)?"UniqueIdentify_Conflict":"UniqueIdentif ID冲突";
	case	KFPC_MsgLenTooLong:return (Lang == 0)?"MsgLenTooLong":"消息太长";
	default											:return (Lang == 0)? "Unknown_ErrorType"			:	"未知错误";
	}
}

#endif // kfpc_comapierr_h__
