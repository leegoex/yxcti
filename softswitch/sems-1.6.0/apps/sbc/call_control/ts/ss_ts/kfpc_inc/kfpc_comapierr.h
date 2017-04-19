#ifndef kfpc_comapierr_h__
#define kfpc_comapierr_h__
#include "kfpc_id.h"
#include "kfpc_error.h"
/********************************************************************
 * @data:		2012/10/10
 * @details:	10:10:2012   19:20
 * @file: 		D:\MyProgram\ͨ�ſ�\kfpc_com\kfpc_comapierr.h 
 * @author:		KFPC
 * @brief:		ͨ�ſ������붨��
*********************************************************************/
const unsigned int KFPC_RegisterHandleFail	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,1);	/**< ע�ᴦ����ʧ�� */
const unsigned int KFPC_AlreadyInitComLib	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,2);	/**< �Ѿ���ʼ�� */
const unsigned int	KFPC_UnInitComLib		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,3);	/**< δ��ʼ���� */
const unsigned int	KFPC_CreateFilterFail	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,4);	/**< ����������ʧ�� */
const unsigned int	KFPC_FilterParamTooMuch	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,5);	/**< ��������������̫�� */
const unsigned int	KFPC_FilterNotExist		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,6);	/**< ������������ */
const unsigned int	KFPC_APPIDNotExist		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,7);	/**< APPID������ */
const unsigned int	KFPC_AppNotConnect		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,8);	/**< APP û������ */
const unsigned int	KFPC_SocketIDNotExist	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,9);	/**< SocketID������ */
const unsigned int	KFPC_AllocMsgFail		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,10);	/**< ������Ϣʧ�� */
const unsigned int	KFPC_AppGroupIDNotExist =	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,11);	/**< Ӧ����ID������ */
const unsigned int	KFPC_IPErr				=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,12);	/**< IP���� */
const unsigned int	KFPC_MsgFlagErr			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,13);	/**< ��Ϣͷ���� */
const unsigned int	KFPC_MsgLenErr			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,14);	/**< ��Ϣ���ȴ��� */
const unsigned int	KFPC_MsgTypeErr			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,15);	/**< ��Ϣ���ʹ��� */
const unsigned int	KFPC_UserCloseSocket	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,16);	/**< �û��ر�Socket */
const unsigned int	KFPC_SocketIDAlreadyExist	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,17);	/**< Socket ID �Ѿ����� */
const unsigned int	KFPC_SocketIsClosing	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,18);	/**< Socket ���ڹر� */
const unsigned int	KFPC_TimerInvalid		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,19);	/**< ��ʱ����Ч */
const unsigned int	KFPC_SocketIDInvalid	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,20);	/**< SocketID ��Ч */
const unsigned int	KFPC_TCPSocketNotEnough	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,21);	/**< Socket���� */
const unsigned int	KFPC_FilterInvalid		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,22);		/**< ��������Ч */
const unsigned int	KFPC_FilterNotEnough	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,23);		/**< ���������� */
const unsigned int	KFPC_AppMangerAlreadyOpen=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,24);		/**< Ӧ�ù������Ѿ��� */
const unsigned int	KFPC_AppMangerDoesNotOpen=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,25);		/**< Ӧ�ù�����δ�� */
const unsigned int	KFPC_NO_Semaphore		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,26);		/**< û���ź��� */
const unsigned int	KFPC_ReconnectClose		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,27);		/**< �����ر� */
const unsigned int	KFPC_GUID_Inequality	=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,28);		/**< GUID ����ͬ */
const unsigned int	KFPC_APPID_Conflict		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,29);		/**< APP ID��ͻ */
const unsigned int	KFPC_UniqueIdentify_Conflict		=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,30);		/**< UniqueIdentif ID��ͻ */
const unsigned int	KFPC_MsgLenTooLong			=	KFPC_RESULT_CREATE(KFPC_RESULT_TYPE_ERROR,KFPC_ID_CLASS_COM_API,31);	/**< ��Ϣ����̫�� */

static const char* ComErrorCodeToStr(unsigned int ErrorCode,unsigned int Lang = 0)
{
	switch(ErrorCode)
	{
	case	KFPC_RegisterHandleFail	:return (Lang == 0)? "RegisterHandleFail":	"ע�ᴦ����ʧ��";
	case	KFPC_AlreadyInitComLib	:return (Lang == 0)? "AlreadyInitComLib" :	"�Ѿ���ʼ��";
	case	KFPC_UnInitComLib		:return (Lang == 0)? "UnInitComLib"		 :  "δ��ʼ����";
	case	KFPC_CreateFilterFail	:return (Lang == 0)?"":"����������ʧ��";
	case	KFPC_FilterParamTooMuch	:return (Lang == 0)?"FilterParamTooMuch":"��������������̫��";
	case	KFPC_FilterNotExist		:return (Lang == 0)?"FilterNotExist":"������������";
	case	KFPC_APPIDNotExist		:return (Lang == 0)?"APPIDNotExist":"APPID������";
	case	KFPC_AppNotConnect		:return (Lang == 0)?"AppNotConnect":"APP û������";
	case	KFPC_SocketIDNotExist	:return (Lang == 0)?"SocketIDNotExist":"SocketID������";
	case	KFPC_AllocMsgFail		:return (Lang == 0)?"AllocMsgFail":"������Ϣʧ��";
	case	KFPC_AppGroupIDNotExist :return (Lang == 0)?"AppGroupIDNotExist":"Ӧ����ID������";
	case	KFPC_IPErr				:return (Lang == 0)?"IPErr":"IP����";
	case	KFPC_MsgFlagErr			:return (Lang == 0)?"MsgFlagErr	":"��Ϣͷ����";
	case	KFPC_MsgLenErr			:return (Lang == 0)?"MsgLenErr":"��Ϣ���ȴ���";
	case	KFPC_MsgTypeErr			:return (Lang == 0)?"MsgTypeErr":"��Ϣ���ʹ���";
	case	KFPC_UserCloseSocket	:return (Lang == 0)?"UserCloseSocket":"�û��ر�Socket";
	case	KFPC_SocketIDAlreadyExist	:return (Lang == 0)?"SocketIDAlreadyExist":"Socket ID �Ѿ�����";
	case	KFPC_SocketIsClosing	:return (Lang == 0)?"SocketIsClosing":"Socket ���ڹر�";
	case	KFPC_TimerInvalid		:return (Lang == 0)?"TimerInvalid":"��ʱ����Ч";
	case	KFPC_SocketIDInvalid	:return (Lang == 0)?"SocketIDInvalid":"SocketID ��Ч";
	case	KFPC_TCPSocketNotEnough	:return (Lang == 0)?"TCPSocketNotEnough":"Socket����";
	case	KFPC_FilterInvalid		:return (Lang == 0)?"FilterInvalid":"��������Ч";
	case	KFPC_FilterNotEnough	:return (Lang == 0)?"ilterNotEnough":" ����������";
	case	KFPC_AppMangerAlreadyOpen:return (Lang == 0)?"AppMangerAlreadyOpen":"Ӧ�ù������Ѿ���";
	case	KFPC_AppMangerDoesNotOpen:return (Lang == 0)?"AppMangerDoesNotOpen":"Ӧ�ù�����δ��";
	case	KFPC_NO_Semaphore:return (Lang == 0)?"NOSemaphore":"û���ź���";
	case	KFPC_ReconnectClose:return (Lang == 0)?"ReconnectClose":"�����ر�";
	case	KFPC_GUID_Inequality:return (Lang == 0)?"GUID_Inequality":" GUID ����ͬ";
	case	KFPC_APPID_Conflict:return (Lang == 0)?"APPID_Conflict":" APP ID��ͻ";
	case	KFPC_UniqueIdentify_Conflict:return (Lang == 0)?"UniqueIdentify_Conflict":"UniqueIdentif ID��ͻ";
	case	KFPC_MsgLenTooLong:return (Lang == 0)?"MsgLenTooLong":"��Ϣ̫��";
	default											:return (Lang == 0)? "Unknown_ErrorType"			:	"δ֪����";
	}
}

#endif // kfpc_comapierr_h__
