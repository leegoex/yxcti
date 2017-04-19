#ifndef kfpc_api_h__
#define kfpc_api_h__
/********************************************************************
 * @data:		2012/09/26
 * @details:	26:9:2012   14:52
 * @file: 		D:\MyProgram\ͨ�ſ�\kfpc_com\kfpc_api.h 
 * @author:		KFPC
 * @brief:		ͨ�ſ�API����
*********************************************************************/


//����Ϊ��ȷ���壬����C++/C===============
#ifdef KFPC_COM_EXPORTS
	#ifdef WIN32
		#define KFPC_COM_API __declspec(dllexport)
	#else
		#define KFPC_COM_API extern "C" 
	#endif
#else

	#ifdef WIN32
		#define KFPC_COM_API	__declspec( dllimport )
	#else
		#ifdef __cplusplus
			#define KFPC_COM_API extern "C" 
		#else
			#define KFPC_COM_API
		#endif
	#endif
#endif


//=========================================

//����ֻ������C++,����˵����ȷ
//#ifdef KFPC_COM_EXPORTS
//	#ifdef WIN32
//		#define KFPC_COM_API __declspec(dllexport)
//	#else
//		#define KFPC_COM_API extern "C" 
//	#endif
//#else
//
//	#ifdef WIN32
//		#define KFPC_COM_API	
//	#else
//		#define KFPC_COM_API
//	#endif
//#endif



#include "kfpc_error.h"
#include "kfpc_id.h"
#include "kfpc_msg.h"


/**
 *	API library message IDs 
 */ 
	#define	KFPC_MSG_ID_API_REMOTE_APP_ONLINE						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x01)		/**< Զ��Ӧ������ */
	#define	KFPC_MSG_ID_API_REMOTE_APP_OFFLINE						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x02)		/**< Զ��Ӧ������ */
	#define	KFPC_MSG_ID_API_LOCAL_CONNECTED							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x03)		/**< ���ؿͻ������ӳɹ�*/
	#define	KFPC_MSG_ID_API_REMOTE_CONNECTED						KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x04)		/**< Զ��Ӧ������ */
	#define	KFPC_MSG_ID_API_APP_DISCONNECT							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x05)		/**< Ӧ�öϿ�����,����Զ��,���� */
	#define	KFPC_MSG_ID_API_LOCAL_REDUNDANCE_STATUS_CHANGE			KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x06)		/**< ��������״̬�ı��¼�*/
	#define	KFPC_MSG_ID_API_REMOTE_APP_REDUNDANCE_STATUS_CHANGE		KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x07)		/**< Զ������״̬�ı��¼�*/
	#define	KFPC_MSG_ID_API_TEST_MSG								KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x08)		/**< ������Ϣ*/
    #define	KFPC_MSG_ID_API_APPID_CONFLICT							KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x09)		/**< APP��ͻID*/
	#define	KFPC_MSG_ID_API_END										KFPC_MSG_ID_GEN (KFPC_ID_CLASS_COM_API, 0x0a)		/**< ����ID �ǳ���Ҫ*/
	
	#define KFPC_MAX_MSG_ID_API                                     KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_API_END)          /**< ����API_ID��*/
static __inline const char* KFPC_MSG_ID_API_TO_STRING( unsigned int in_un32MsgId )
{
	
	switch( in_un32MsgId )
	{
	case KFPC_MSG_ID_API_REMOTE_APP_ONLINE:										return (const char*)"REMOTE_APP_ONLINE";
	case KFPC_MSG_ID_API_REMOTE_APP_OFFLINE:									return (const char*)"REMOTE_APP_OFFLINE";
	case KFPC_MSG_ID_API_LOCAL_CONNECTED:										return (const char*)"LOCAL_CONNECTED";
	case KFPC_MSG_ID_API_REMOTE_CONNECTED:										return (const char*)"REMOTE_CONNECTED";
	case KFPC_MSG_ID_API_APP_DISCONNECT	:										return (const char*)"APP_DISCONNECT";
	case KFPC_MSG_ID_API_LOCAL_REDUNDANCE_STATUS_CHANGE:						return (const char*)"LOCAL_REDUNDANCE_STATUS_CHANGE";
	case KFPC_MSG_ID_API_REMOTE_APP_REDUNDANCE_STATUS_CHANGE:					return (const char*)"REMOTE_APP_REDUNDANCE_STATUS_CHANGE";
	case KFPC_MSG_ID_API_TEST_MSG:												return (const char*)"TEST_MSG";
	case KFPC_MSG_ID_API_APPID_CONFLICT:										return (const char*)"APPID_CONFLICT";
	}

	return (const char*)"";
}

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Defines
 *------------------------------------------------------------------------------------------------------------------------------*/
//#define	MAX_FILTER_PARAM_COUNT		8		/**< ���������������� */
//#define MAX_APPGROUP_COUNT			1024	/**< ����APP ��ID���� */
/*--------------------------------------------------------------------------------------------------------------------------------
 |  Types
 *------------------------------------------------------------------------------------------------------------------------------*/

	/**
	 *	Ӧ����Ϣ
	 */
	typedef struct KFPC_AppInfo
	{
		char			AppName[KFPC_API_NAME_MAX_LEN];					/**< Ӧ�ó�������*/
		unsigned int	AppID;											/**< Ӧ�ó���ID*/
		unsigned int	AppType;										/**< Ӧ������*/
		unsigned int	AppGroupID;										/**< Ӧ��������,���Ϊ0�������κ���*/ 
		unsigned int	MasterFlag;										/**< �������� 1Ϊ����0Ϊ�ӣ�2 �Ͳ��ٲ������Ӿ���*/
		unsigned int	ListenPort;										/**< �����˿��� < 65535��0ΪĬ��,�ͻ���Ϊ-1������Ҫ���� */
		char			PeerIp[KFPC_MAX_IP_LEN];						/**< Զ��IP���� */
		unsigned char	UniqueIdentify[KFPC_MAX_GUID_LEN]; 
	}KFPC_AppInfo, *PKFPC_AppInfo;



	/**
	 *	�����
	 */
	typedef struct KFPC_LIB_PARAMS
	{
		KFPC_AppInfo	AppInfo;						
		unsigned int	MulticastPort;									/**< �ಥ�˿� */
		char			MutticastIP[KFPC_MAX_IP_LEN];					/**< �ಥIP */
		char			AuthPassWord[KFPC_MAX_PASSWD_LEN];				/**< ������������� */
		unsigned int	ThreadPoolSize;									/**< �̳߳����� ��32*/
		unsigned int	KeepLiveTime;									/**< ����ʱ�� */
		unsigned int	KeepLiveTimeCount;								/**< ��������,������3�� */
		unsigned int	MaxSocketCount;									/**< ���Socket�� ���65535*/
		unsigned int	MsgFilterCount;									/**< ��Ϣ���������� */
		unsigned int	LogOutputMode;									/**< �ռ����ģʽ LOM_FILE|LOM_CONSOLE*/
		unsigned int	FileLogLevel;									/**< �ļ��ռ�������� �ο�KFPC_LOG_LEVEL*/
		unsigned int	ConsoleLogLevel;								/**< ����̨����ռǼ��� �ο�KFPC_LOG_LEVEL*/
	}KFPC_LIB_PARAMS,*PKFPC_LIB_PARAMS;

	/**
	 *	 Message filtering selection 
	 */
	typedef enum KFPC_FILTER
	{
		KFPC_FILTER_NONE					= 0,			/**<  No filter criteria (capture all messages) */
		KFPC_FILTER_MSG_SRCAPPID			= (1<<0),		/**< Match source app id */
		KFPC_FILTER_MSG_TYPE				= (1<<1),		/**< Match MsgType (Bitwise ORed) */
		KFPC_FILTER_MSG_ID					= (1<<2),		/**< Match MsgId */
		KFPC_FILTER_MSG_GROUP				= (1<<3),		/**< Match MsgGroup */
		KFPC_FILTER_MSG_SERIAL_NUMBER		= (1<<4),		/**< Match message's serial number (implicit filtering) */
		KFPC_FILTER_MSG_USER_CONTEXT1		= (1<<5),		/**< Match UserContext1 */
		KFPC_FILTER_MSG_USER_CONTEXT2		= (1<<6),		/**< Match UserContext2 */
		KFPC_FILTER_MSG_DSTAPPID			= (1<<7),		/**< Match destination id */

		KFPC_FILTER_ALL						= 0xffffffff,	/**< All positive criteria must match */

		KFPC_FILTER_NOT_MSG_SRCAPPID		= (1<<8),		/**< Does not match Adapter Handle */
		KFPC_FILTER_NOT_MSG_TYPE			= (1<<9),		/**< Does not match MsgType (Bitwise ORed) */
		KFPC_FILTER_NOT_MSG_ID				= (1<<10),		/**< Does not match MsgId */
		KFPC_FILTER_NOT_MSG_GROUP			= (1<<11),		/**< Does not match MsgGroup */
		KFPC_FILTER_NOT_MSG_SERIAL_NUMBER	= (1<<12),		/**< Does not match message's serial number (implicit filtering) */
		KFPC_FILTER_NOT_MSG_USER_CONTEXT1	= (1<<13),		/**< Does not match UserContext1 */
		KFPC_FILTER_NOT_MSG_USER_CONTEXT2	= (1<<14),		/**< Does not match UserContext2 */
		KFPC_FILTER_NOT_MSG_DSTAPPID		= (1<<15),

		KFPC_FILTER_NEGATIVE				= (1<<30)		/* When a filter parameter with this flag set matches an incoming message
																it prevents that message to match the filter */

	} KFPC_FILTER, *PKFPC_FILTER;



	/**
	 *	��һ��Ӧ���ж��SOCKET����ʱ����ͨ�����·��Ͳ���ѡ��SOCKET
	 */
	typedef enum KFPC_SendPolicy
	{
		KFPC_SP_FirstSocket = 1, // ��һ��SOCKET
		KFPC_SP_Broadcast =2 // �㲥
	}KFPC_SendPolicy;

	/**
	 * ����������
	 */
	typedef struct KFPC_FILTER_PARAMS 
	{ 
		/*@{*/
		unsigned int        FilterMask; 
		unsigned int		un32MsgId;							/**< Must be kept first */
		unsigned int		un32MsgType;						/**< Message type */
		unsigned int		un32Length;						/**< The total length of the message,��������Ϣͷ */
		unsigned int		un32SerialNumber;				/**< This buffer's unique serial number */
		unsigned int		un32UserContext1;				/**< User Ctx #1 (filterable) �û�������1*/
		unsigned int		un32UserContext2;				/**< User Ctx #2 (filterable) �û�������2*/
		unsigned int		un32SrcAPPId;						/**< Unique application identifier ӦAPP ID*/
		unsigned int		un32DstAPPId;						/**< Unique application identifier ӦAPP ID*/

		/*@}*/
	} KFPC_FILTER_PARAMS, *PKFPC_FILTER_PARAMS; 


	/**
	 *	ͨ�ſ�ͳ������
	 */
	typedef struct KFPC_ComLibStatistics
	{
		unsigned int	AppCount;			/**< App���� */
		unsigned int	MemAllocCount;		/**< �ڴ������ */
		unsigned int	MsgAllocCount;		/**< ��Ϣ������ */
		unsigned int	CreateAcceptObjCount;		/**< Accept���󴴽����� */
		unsigned int	CreateClientObjCount;		/**< Client���󴴽����� */
		unsigned int	CreateConnectObjCount;	/**< Connect���󴴽����� */
		unsigned int	TcpSocketCount;		/**< ϵͳ��TcpSocket�������� */
		unsigned int	CreateFilterCount;	/**< �������������� */
		unsigned int	SocketHandleCount;		/**< Socket����� */
		unsigned int	MsgMemSN;			/**< ��Ϣ�ڴ������� */
	}KFPC_ComLibStatistics;

/************************************************************************/
/* ��Ϣ�ӿڶ���                                                         */
/************************************************************************/

	/**
	 *	Զ��Ӧ������
	 */
	typedef struct KFPC_EVT_API_REMOTE_APP_ONLINE
	{
		KFPC_MSG_HEADER			Header;				/**< ��Ϣͷ */
		KFPC_AppInfo			AppInfo;		
	}KFPC_EVT_API_REMOTE_APP_ONLINE;

	/**
	 *	Զ��Ӧ������
	 */
	typedef struct KFPC_EVT_API_REMOTE_APP_OFFLINE
	{
		KFPC_MSG_HEADER			Header;				/**< ��Ϣͷ */
		KFPC_AppInfo			AppInfo;
	}KFPC_EVT_API_REMOTE_APP_OFFLINE;

	/**
	 *	�������ӷ���
	 */
	typedef struct KFPC_EVT_API_LOCAL_CONNECTED
	{
		KFPC_MSG_HEADER			Header;				/**< ��Ϣͷ */
		unsigned int			Result;				/**< ��� */
		unsigned int			RemoteAppID;		/**< Զ��APPID������Ҫ��Ϊ���Զ����ID�� */
		unsigned int			LocalAppID;			/**< ������IDΪ�Զ���ȡʱ�����ӵ�����ʱ���ᱻ���� */
		unsigned int			ConnectCount;		/**< ���Ӵ������������Ϊ1˵���ǵ�һ�Σ�����Ϊ�Ͽ������� */
		unsigned int			SocketSN;			/**< SocketSN */
		KFPC_AppInfo			AppInfo;
	}KFPC_EVT_API_LOCAL_CONNECTED;

	/**
	 *	Զ�̿ͻ�����������
	 */
	typedef struct KFPC_EVT_API_REMOTE_CONNECTED
	{
		KFPC_MSG_HEADER			Header;				/**< ��Ϣͷ */
		KFPC_AppInfo			AppInfo;
		unsigned int			SocketSN;			/**< SocketSN */
	}KFPC_EVT_API_REMOTE_CONNECTED;

	/**
	 *	Ӧ�öϿ����Ӱ����������Ӻ�Զ������
	 */
	typedef struct KFPC_EVT_API_APP_DISCONNECT
	{
		KFPC_MSG_HEADER			Header;				/**< ��Ϣͷ */
		unsigned int			LocalConnect;		/**< 1Ϊ�������ӣ�0ΪԶ������ */
		unsigned int			DiscountCount;		/**< ����Ǳ������ӣ��������˵���Ͽ����Ӵ�������Ϊ�������Ӿ����Զ����ӹ��� */
		unsigned int			SocketSN;			/**< SocketSN */
		unsigned int			AppType;			/**< Ӧ������*/
		unsigned int			AppGroupID;			/**< Ӧ��������,���Ϊ0�������κ���*/ 
	}KFPC_EVT_API_APP_DISCONNECT;



	/**
	 *	AppID��ͻ�¼�,
	 */
	typedef struct KFPC_EVT_APPID_CONFLICTED
	{
		KFPC_MSG_HEADER			Header;				/**< ��Ϣͷ */
		unsigned int			ConflictFlag;		/**< ��ͻ����, 1- ��ͻ*/
		char PeerIP[KFPC_MAX_IP_LEN];
	}KFPC_EVT_APPID_CONFLICTED;


	/**
	 *	��������״̬�ı�,������ԭ���Ĵ�-->��
	 */
	typedef struct KFPC_EVT_LOCAL_REDUNDANCE_STATUS_CHANGE
	{
		KFPC_MSG_HEADER			Header;				/**< ��Ϣͷ */
		unsigned int			MasterFlag;			/**< ��������*/
	}KFPC_EVT_LOCAL_REDUNDANCE_STATUS_CHANGE;

	/**
	 *	Զ��Ӧ�õ����ӱ仯
	 */
	typedef struct KFPC_EVT_API_REMOTE_APP_REDUNDANCE_STATUS_CHANGE
	{
		KFPC_MSG_HEADER			Header;				/**< ��Ϣͷ */
		unsigned int			RemoteAppID;		/**< Զ��APPID */
		unsigned int			MasterFlag;			/**< ��������*/
	}KFPC_EVT_API_REMOTE_APP_REDUNDANCE_STATUS_CHANGE;

	typedef struct KFPC_REQ_API_TEST_MSG
	{
		KFPC_MSG_HEADER			Header;						/**< ��Ϣͷ */
		char					StrBuf[KFPC_MAX_MSG_BODY];	/**< �ַ������� */
	}KFPC_REQ_API_TEST_MSG;

	typedef struct KFPC_RSP_API_TEST_MSG
	{
		KFPC_MSG_HEADER			Header;						/**< ��Ϣͷ */
		char					StrBuf[KFPC_MAX_MSG_BODY];	/**< �ַ������� */
	}KFPC_RSP_API_TEST_MSG;


	typedef struct KFPC_API_MSG
	{
		KFPC_MSG_HEADER			Header;						/**< ��Ϣͷ */
		char					StrBuf[KFPC_MAX_MSG_BODY];	/**< �ַ������� */
	}KFPC_API_MSG;
/*--------------------------------------------------------------------------------------------------------------------------------
 |  Function Prototypes
 *------------------------------------------------------------------------------------------------------------------------------*/
	
	/**
	 * FullName:  	KFPC_InitServerLibParam
	 * @brief 		��ʼ������˿����
	 * @param[in,out] KFPC_LIB_PARAMS * LibParam
	 * @return   	KFPC_COM_API	int
	 */
	KFPC_COM_API	int KFPC_InitServerLibParam( KFPC_LIB_PARAMS* LibParam,const char* pAppName,unsigned int AppID,unsigned int AppGroupID);


	/**
	 * FullName:  	KFPC_InitClientLibParam
	 * @brief 		��ʼ���ͻ��˲���
	 * @param[in,out] KFPC_LIB_PARAMS * LibParam
	 * @return   	KFPC_COM_API	int
	 */
	KFPC_COM_API	int KFPC_InitClientLibParam( KFPC_LIB_PARAMS* LibParam,const char* pAppName);

	/**
	 * FullName:  	InitComLib
	 * @brief 		��ʼ��ͨ�ſ�
	 * @param[in]	KFPC_KFPC_LIB_PARAMS * LibParam
	 * @return   	int �ɹ�����0
	 */
	KFPC_COM_API	int KFPC_InitComLib( KFPC_LIB_PARAMS* LibParam);

	KFPC_COM_API	KFPC_LIB_PARAMS* KFPC_GetLibParam();

	/**
	 * FullName:  	KFPC_GetComLibStatistics
	 * @brief 		ͨ�ſ�ͳ��
	 * @param[in,out] KFPC_ComLibStatistics * pComLibStatistics
	 * @return   	int
	 */
	KFPC_COM_API	int KFPC_GetComLibStatistics(KFPC_ComLibStatistics* pComLibStatistics);

	/**
	 * FullName:  	CloseComLib
	 * @brief 		�ر�ͨ�ſ�
	 * @return   	int �ɹ�����0
	 */
	KFPC_COM_API	int KFPC_CloseComLib();

	/**
	 * FullName:  	CreateMsgFilter
	 * @brief 		����������
	 * @param[in]	unsigned int FiltersCount ��������������
	 * @param[in]	KFPC_FILTER_PARAMS FilterParams[] ����������
	 * @param[out]	unsigned int * FilterID	������ID
	 * @return   	int �ɹ�����0
	 */
	KFPC_COM_API	int KFPC_CreateMsgFilter(KFPC_FILTER_PARAMS*	FilterParams,
						unsigned int*		FilterID  );


	/**
	 * FullName:  	KFPC_GetMsgFilterParam
	 * @brief 		���ع���������
	 * @param[in]	unsigned int FilterID
	 * @param[out]	unsigned int FiltersCount
	 * @param[out]	KFPC_FILTER_PARAMS FilterParams[]
	 * @return   	int
	 */
	KFPC_COM_API	int KFPC_GetMsgFilterParam (unsigned int		FilterID,KFPC_FILTER_PARAMS*	FilterParams);



	/**
	 * FullName:  	KFPC_DestroyMsgFilter
	 * @brief 		���ٹ�����
	 * @param[in]	unsigned int FilterID	������ID
	 * @return   	int
	 */
	KFPC_COM_API	int	KFPC_DestroyMsgFilter (unsigned int	FilterID);

	/**
	 * FullName:  	KFPC_WakeMsgFilter
	 * @brief 		���ѹ�����,
	 * @param[in,out] unsigned int FilterID
	 * @return   	int
	 */
	KFPC_COM_API	int KFPC_WakeMsgFilter (unsigned int	FilterID);

	/**
	 * FullName:  	KFPC_SendMsg
	 * @brief 		������Ϣ
	 * @param[in]	PKFPC_MSG_HEADER Msg	��Ϣָ��
	 * @param[in,out] unsigned int * FilterID	����������ΪNULL�����������첽���ͣ����ķ�����Ϣ����ϵͳĬ�ϵĹ��������
	 *											������������ΪNULL����ô���ͳɹ���᷵��һ��������ID���ڽ��պ�����������������������պ��������յ�Ψһ�ķ�����Ϣ��������ͬ����
	 *											�յ���Ϣ��Ҫ���ٹ�������ͨ��KFPC_DestroyMsgFilter��
	 * @return   	int
	 */


	KFPC_COM_API	int KFPC_SendMsg (PKFPC_MSG_HEADER	Msg,
#ifdef __cplusplus		
		unsigned int*	FilterID = NULL
#else
		unsigned int*	FilterID
#endif
		);

	KFPC_COM_API	int KFPC_SendMsgEx (unsigned int SocketSN,PKFPC_MSG_HEADER	Msg,
#ifdef __cplusplus			
		unsigned int*	FilterID = NULL
#else
		unsigned int*	FilterID
#endif
		);


	/**
	 * FullName:  	KFPC_SendMsgToAppGroup
	 * @brief 		������Ϣ��Ӧ����
	 * @param[in] unsigned int AppGroupID
	 * @param[in] PKFPC_MSG_HEADER Msg
	 * @return   	KFPC_COM_API	int
	 */
	KFPC_COM_API	int KFPC_SendMsgToAppGroup (unsigned int AppGroupID,unsigned int AppType,PKFPC_MSG_HEADER	Msg);

	/**
	 * FullName:  	KFPC_ReceiveMsg
	 * @brief 		��Ϣ���պ���
	 * @param[in,out] unsigned int FilterID	������ID IDΪ-1ΪĬ�Ϲ�����
	 * @param[in,out] int TimeoutMSec			��ʱ����,����
	 * @param[in,out] KFPC_MSG_HEADER * * phMsg	��Ϣ
	 * @return   	int
	 */
	KFPC_COM_API	int	KFPC_ReceiveMsg (unsigned int		FilterID,
						int					TimeoutMSec,
						KFPC_MSG_HEADER**	pMsg);

	/**
	 * FullName:  	KFPC_WaitMsg
	 * @brief 		�ȴ��������� ��Ҫ�����ж��Ƿ�����Ϣ
	 * @param[in,out] unsigned int FilterID	������ID
	 * @param[in,out] int TimeoutMSec	��ʱ����,����
	 * @param[in,out] unsigned int * MsgCount	��������Ϣ����
	 * @return   	int	�ɹ�����0
	 *					��ʱ���� KFPC_RESULT_TIMEOUT
	 */
	KFPC_COM_API	int	KFPC_WaitMsg (	unsigned int		FilterID,
						int					TimeoutMSec,
						unsigned int*		MsgCount);

	/**
	 * FullName:  	KFPC_AllocMsg
	 * @brief 		������Ϣ
	 * @param[in,out] unsigned int MsgSize	��Ϣ��С
	 * @param[out] KFPC_MSG_HEADER * * pMsg	�����Ϣָ��
	 * @param[in] unsigned int MsgID		��ϢID
	 * @param[in] KFPC_MSG_TYPE MsgType		��Ϣ����
	 * @param[in] unsigned int DstAppID		Ŀ��Ӧ��ID
	 * @param[in] unsigned int SrcAPPId		ԴӦ��ID
	 * @param[in] unsigned int UserContext1	�û�������1
	 * @param[in] unsigned int UserContext2	�û�������2
	 * @param[in] unsigned int SN			��Ϣ���
	 * @return   	KFPC_COM_API	int
	 */
	KFPC_COM_API	int KFPC_AllocMsg ( unsigned int MsgSize,  
		KFPC_MSG_HEADER** pMsg,
		unsigned int MsgID,
		KFPC_MSG_TYPE	MsgType,
		unsigned int DstAppID,
		unsigned int SrcAPPId,
		unsigned int UserContext1,
		unsigned int UserContext2,

#ifdef __cplusplus	
		unsigned int SN = 0
#else
		unsigned int SN
#endif

		);

	/**
	 * FullName:  	KFPC_ReleaseMsg
	 * @brief 		������Ϣ
	 * @param[in,out] KFPC_MSG_HEADER * pMsg
	 * @return   	int
	 */
	KFPC_COM_API	int	KFPC_ReleaseMsg (KFPC_MSG_HEADER*	pMsg);

	/**
	 * FullName:  	KFPC_GetErrorString
	 * @brief 		���ش����ַ���
	 * @param[in]	unsigned int Result
	 * @return   	const char*
	 */
	KFPC_COM_API	const char* KFPC_GetErrorString (unsigned int	Result);

	/**
	 * FullName:  	KFPC_GetAPPList
	 * @brief 		��õ�ǰӦ���б�
	 * @param[in,out] unsigned int * AppCount	�������APPIDs�Ĵ�С�������ЧAPPID����
	 * @param[out] unsigned int APPIDs[]	����Ӧ��ID��������
	 * @return   	int
	 */
	KFPC_COM_API	int	KFPC_GetAPPList (unsigned int*	AppCount,
						unsigned int	APPIDs[]);

	/**
	 * FullName:  	KFPC_GetAppInfo
	 * @brief 		����ID���APP��Ϣ
	 * @param[in,out] unsigned int APPID
	 * @param[in,out] PKFPC_AppInfo pAppInfo
	 * @return   	int
	 */
	KFPC_COM_API	int KFPC_GetAppInfo (	unsigned int	APPID,
							PKFPC_AppInfo	pAppInfo);


	/**
	 * FullName:  	KFPC_Connect
	 * @brief 		��Զ������
	 * @param[in]	const char * Ip		Զ��IP
	 * @param[in]	unsigned short Port	Զ�̶˿�
	 * @param[in]	const char* pConnectPasswd ��������
	 * @param[in]	unsigned int UserContext1 �û�������1
	 * @param[in]	unsigned int UserContext2
	 * @param[in]	bool SYNC	�Ƿ�ͬ�������ͬ����������ʱ��֪���ӳɹ����������첽�͵ȴ�Զ�������¼�
	 * @return  	int
	 */


	KFPC_COM_API	int KFPC_Connect(const char* Ip,
		unsigned short Port,
		const char* pConnectPasswd,
		unsigned int UserContext1,
		unsigned int UserContext2,
		unsigned int* SocketSN,
		
#ifdef __cplusplus	
		bool			AutoReConnect,
		bool			SYNC= false,
		unsigned int	TimeOut = 0,
		unsigned int	ConIndex = 0
#else
		int				AutoReConnect,
		int				SYNC,			/*= false*/
		unsigned int	TimeOut,		/*= 0*/
		unsigned int	ConIndex		/*= 0*/
#endif

		);

	/**
	 * FullName:  	KFPC_CloseAPP
	 * @brief 		�ر�APP
	 * @param[in]	unsigned int APPID
	 * @return   	int
	 */
	KFPC_COM_API	int KFPC_CloseAPP(unsigned int APPID);
	

	/**
	 * FullName:  	KFPC_CloseSocket
	 * @brief 		�رյ���SocketID
	 * @param[in]	Socket_t SocketID
	 * @return   	KFPC_COM_API	int
	 */
	KFPC_COM_API	int KFPC_CloseSocket( int SocketID );

	KFPC_COM_API	int KFPC_CheckAppID (	unsigned int	APPID);
	KFPC_COM_API	int KFPC_DupMsg(KFPC_MSG_HEADER* pSrcMsg,KFPC_MSG_HEADER** pNewMsg );

#endif // kfpc_api_h__
