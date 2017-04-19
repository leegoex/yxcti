#pragma once
															//1xx = 通知性应答
#define SIP_STATUS_Trying									100		//正在尝试



#define SIP_STATUS_Ringing									180		//正在拨打
#define SIP_STATUS_CallBeingForwarded						181		//正被转接
#define SIP_STATUS_CallQueued								182		//正在排队
#define SIP_STATUS_SessionProgress							183		//通话进展
															//2xx		//= 成功应答
#define SIP_STATUS_OK										200		//OK
#define SIP_STATUS_Accepted									202		//被接受：用于转介
															
															//3xx		//= 转接应答
#define SIP_STATUS_MultipleChoices							300		//多项选择
#define SIP_STATUS_MovedPermanently							301		//被永久迁移
#define SIP_STATUS_MovedTemporarily							302		//被暂时迁移
#define SIP_STATUS_UseProxy									305		//使用代理服务器
#define SIP_STATUS_AlternativeService						380		//替代服务
															   		//
		 													//4xx		//= 呼叫失败
#define SIP_STATUS_BadRequest								400		//呼叫不当
#define SIP_STATUS_Unauthorized								401		//未经授权：只供注册机构使用，代理服务器应使用代理服务器授权407
#define SIP_STATUS_PaymentRequired							402		//要求付费（预订为将来使用)
#define SIP_STATUS_Forbidden								403		//被禁止的
#define SIP_STATUS_NotFound									404		//未发现：未发现用户
#define SIP_STATUS_MethodNotAllowed							405		//不允许的方法
#define SIP_STATUS_NotAcceptable							406		//不可接受
#define SIP_STATUS_ProxyAuthenticationRequired				407		//需要代理服务器授权
#define SIP_STATUS_RequestTimeout							408		//呼叫超时：在预定时间内无法找到用户
#define SIP_STATUS_Conflict									409   		//
#define SIP_STATUS_Gone										410		//已消失：用户曾经存在，但已从此处消失
#define SIP_STATUS_LengthRequired							411   		//
#define SIP_STATUS_RequestEntityTooLarge					413		//呼叫实体过大
#define SIP_STATUS_RequestURITooLong						414		//呼叫URI过长
#define SIP_STATUS_UnsupportedMediaType						415		//不支持的媒体类型
#define SIP_STATUS_UnsupportedURIScheme						416		//不支持的URI方案
#define SIP_STATUS_BadExtension								420		//不当扩展：使用了不当SIP协议扩展，服务器无法理解该扩展
#define SIP_STATUS_ExtensionRequired						421		//需要扩展
#define SIP_STATUS_IntervalTooBrief							423		//时间间隔过短
#define SIP_STATUS_TemporarilyUnavailable					480		//暂时不可使用
#define SIP_STATUS_Call_TransactionDoesNotExist				481		//通话/事务不存在
#define SIP_STATUS_LoopDetected								482		//检测到循环
#define SIP_STATUS_TooManyHops								483		//跳数过多
#define SIP_STATUS_AddressIncomplete						484		//地址不全
#define SIP_STATUS_Ambiguous								485		//模糊不清
#define SIP_STATUS_BusyHere									486		//此处太忙
#define SIP_STATUS_RequestTerminated						487		//呼叫被终止
#define SIP_STATUS_NotAcceptableHere						488		//此处不可接受
#define SIP_STATUS_RequestPending							491		//呼叫待批
#define SIP_STATUS_Undecipherable							493		//无法解读：无法解读 S/MIME文体部分

		 													//5xx		//= 服务器失败
#define SIP_STATUS_ServerInternalError						500		//服务器内部错误
#define SIP_STATUS_NotImplemented							501		//无法实施：SIP呼叫方法在此处无法实施
#define SIP_STATUS_BadGateway								502		//不当网关
#define SIP_STATUS_ServiceUnavailable						503		//服务不可使用
#define SIP_STATUS_ServerTimeOut							504		//服务器超时
#define SIP_STATUS_VersionNotSupported						505		//不支持该版本：服务器不支持SIP协议的这个版本
#define SIP_STATUS_MessageTooLarge							513		//消息过长
	    													   		//
		 													//6xx		//= 全局失败
#define SIP_STATUS_BusyEverywhere							600		//各处均忙
#define SIP_STATUS_Declined									603		//拒绝
#define SIP_STATUS_DoesNotExistAnywhere						604		//无处存在
#define SIP_STATUS_NotAcceptable2							606		//不可使用

















































































































