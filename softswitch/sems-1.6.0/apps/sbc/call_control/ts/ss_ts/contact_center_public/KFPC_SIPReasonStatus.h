#pragma once
															//1xx = ֪ͨ��Ӧ��
#define SIP_STATUS_Trying									100		//���ڳ���



#define SIP_STATUS_Ringing									180		//���ڲ���
#define SIP_STATUS_CallBeingForwarded						181		//����ת��
#define SIP_STATUS_CallQueued								182		//�����Ŷ�
#define SIP_STATUS_SessionProgress							183		//ͨ����չ
															//2xx		//= �ɹ�Ӧ��
#define SIP_STATUS_OK										200		//OK
#define SIP_STATUS_Accepted									202		//�����ܣ�����ת��
															
															//3xx		//= ת��Ӧ��
#define SIP_STATUS_MultipleChoices							300		//����ѡ��
#define SIP_STATUS_MovedPermanently							301		//������Ǩ��
#define SIP_STATUS_MovedTemporarily							302		//����ʱǨ��
#define SIP_STATUS_UseProxy									305		//ʹ�ô��������
#define SIP_STATUS_AlternativeService						380		//�������
															   		//
		 													//4xx		//= ����ʧ��
#define SIP_STATUS_BadRequest								400		//���в���
#define SIP_STATUS_Unauthorized								401		//δ����Ȩ��ֻ��ע�����ʹ�ã����������Ӧʹ�ô����������Ȩ407
#define SIP_STATUS_PaymentRequired							402		//Ҫ�󸶷ѣ�Ԥ��Ϊ����ʹ��)
#define SIP_STATUS_Forbidden								403		//����ֹ��
#define SIP_STATUS_NotFound									404		//δ���֣�δ�����û�
#define SIP_STATUS_MethodNotAllowed							405		//������ķ���
#define SIP_STATUS_NotAcceptable							406		//���ɽ���
#define SIP_STATUS_ProxyAuthenticationRequired				407		//��Ҫ�����������Ȩ
#define SIP_STATUS_RequestTimeout							408		//���г�ʱ����Ԥ��ʱ�����޷��ҵ��û�
#define SIP_STATUS_Conflict									409   		//
#define SIP_STATUS_Gone										410		//����ʧ���û��������ڣ����ѴӴ˴���ʧ
#define SIP_STATUS_LengthRequired							411   		//
#define SIP_STATUS_RequestEntityTooLarge					413		//����ʵ�����
#define SIP_STATUS_RequestURITooLong						414		//����URI����
#define SIP_STATUS_UnsupportedMediaType						415		//��֧�ֵ�ý������
#define SIP_STATUS_UnsupportedURIScheme						416		//��֧�ֵ�URI����
#define SIP_STATUS_BadExtension								420		//������չ��ʹ���˲���SIPЭ����չ���������޷�������չ
#define SIP_STATUS_ExtensionRequired						421		//��Ҫ��չ
#define SIP_STATUS_IntervalTooBrief							423		//ʱ��������
#define SIP_STATUS_TemporarilyUnavailable					480		//��ʱ����ʹ��
#define SIP_STATUS_Call_TransactionDoesNotExist				481		//ͨ��/���񲻴���
#define SIP_STATUS_LoopDetected								482		//��⵽ѭ��
#define SIP_STATUS_TooManyHops								483		//��������
#define SIP_STATUS_AddressIncomplete						484		//��ַ��ȫ
#define SIP_STATUS_Ambiguous								485		//ģ������
#define SIP_STATUS_BusyHere									486		//�˴�̫æ
#define SIP_STATUS_RequestTerminated						487		//���б���ֹ
#define SIP_STATUS_NotAcceptableHere						488		//�˴����ɽ���
#define SIP_STATUS_RequestPending							491		//���д���
#define SIP_STATUS_Undecipherable							493		//�޷�������޷���� S/MIME���岿��

		 													//5xx		//= ������ʧ��
#define SIP_STATUS_ServerInternalError						500		//�������ڲ�����
#define SIP_STATUS_NotImplemented							501		//�޷�ʵʩ��SIP���з����ڴ˴��޷�ʵʩ
#define SIP_STATUS_BadGateway								502		//��������
#define SIP_STATUS_ServiceUnavailable						503		//���񲻿�ʹ��
#define SIP_STATUS_ServerTimeOut							504		//��������ʱ
#define SIP_STATUS_VersionNotSupported						505		//��֧�ָð汾����������֧��SIPЭ�������汾
#define SIP_STATUS_MessageTooLarge							513		//��Ϣ����
	    													   		//
		 													//6xx		//= ȫ��ʧ��
#define SIP_STATUS_BusyEverywhere							600		//������æ
#define SIP_STATUS_Declined									603		//�ܾ�
#define SIP_STATUS_DoesNotExistAnywhere						604		//�޴�����
#define SIP_STATUS_NotAcceptable2							606		//����ʹ��

















































































































