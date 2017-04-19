#ifndef _Q850_H_
#define	_Q850_H_
#define		Q850_UnallocatedNumber							1			//Cause No. 1 �C Unallocated (unassigned) number
#define		Q850_Noroute									2			//Cause No. 2 �C No route to specified transit network (national use)
#define		Q850_NoRouteToDestination						3			//Cause No. 3 �C No route to destination
#define		Q850_SendSpecialInformationTone					4			//Cause No. 4 �C Send special information tone
#define		Q850_MisdialledTrunkPrefix						5			//Cause No. 5 �C Misdialled trunk prefix (national use)
#define		Q850_ChannelUnacceptable						6			//Cause No. 6 �C Channel unacceptable
#define		Q850_CallAwarded								7			//Cause No. 7 �C Call awarded and being delivered in an established channel
#define		Q850_Preemption									8			//Cause No. 8 �C Preemption
#define		Q850_PreemptionCircuit							9			//Cause No. 9 �C Preemption - circuit reserved for reuse
#define		Q850_NormalCallClearing							16			//Cause No. 16 �C Normal call clearing
#define		Q850_UserBusy									17			//Cause No. 17 �C User busy
#define		Q850_NoUserResponding							18			//Cause No. 18 �C No user responding
#define		Q850_NoAnswerFromUser							19			//Cause No. 19 �C No answer from user (user alerted)
#define		Q850_SubscriberAbsent							20			//Cause No. 20 �C Subscriber absent
#define		Q850_CallRejected								21			//Cause No. 21 �C Call rejected
#define		Q850_NumberChanged								22			//Cause No. 22 �C Number changed
#define		Q850_NonSelectedUserClearing					26			//Cause No. 26 �C Non-selected user clearing
#define		Q850_DestinationOutOfOrder						27			//Cause No. 27 �C Destination out of order
#define		Q850_InvalidNumberFormat						28			//Cause No. 28 �C Invalid number format (address incomplete)
#define		Q850_FacilityRejected							29			//Cause No. 29 �C Facility rejected
#define		Q850_ResponseToSTATUSENQUIRY					30			//Cause No. 30 �C Response to STATUS ENQUIRY
#define		Q850_NormalUnspecified							31			//Cause No. 31 �C Normal, unspecified
#define		Q850_NoCircuit									34			//Cause No. 34 �C No circuit/channel available
#define		Q850_NetworkOutOfOrder							38			//Cause No. 38 �C Network out of order
#define		Q850_PermanentFrameModeConnectionOutOfService	39			//Cause No. 39 �C Permanent frame mode connection out-of-service
#define		Q850_PermanentFrameModeConnectionOperational	40			//Cause No. 40 �C Permanent frame mode connection operational
#define		Q850_TemporaryFailure							41			//Cause No. 41 �C Temporary failure
#define		Q850_SwitchingEquipmentCongestion				42			//Cause No. 42 �C Switching equipment congestion
#define		Q850_AccessInformationDiscarded					43			//Cause No. 43 �C Access information discarded
#define		Q850_ChannelNotAvailable						44			//Cause No. 44 �C Requested circuit/channel not available
#define		Q850_PrecedenceCallBlocked						46			//Cause No. 46 �C Precedence call blocked
#define		Q850_ResourceUnavailable						47			//Cause No. 47 �C Resource unavailable, unspecified
#define		Q850_QualityOfServiceNotAvailable				49			//Cause No. 49 �C Quality of Service not available
#define		Q850_RequestedFacilityNotSubscribed				50			//Cause No. 50 �C Requested facility not subscribed
#define		Q850_OutgoingCallsBarredWithinCUG				53			//Cause No. 53 �C Outgoing calls barred within CUG
#define		Q850_IncomingCallsBarredWithinCUG				55			//Cause No. 55 �C Incoming calls barred within CUG
#define		Q850_BearerCapabilityNotAuthorized				57			//Cause No. 57 �C Bearer capability not authorized
#define		Q850_BearerCapabilityNotPresentlyAvailable		58			//Cause No. 58 �C Bearer capability not presently available
#define		Q850_InconsistencyInformationAndSubscriberClass	62			//Cause No. 62 �C Inconsistency in designated outgoing access information and subscriber class
#define		Q850_ServiceOrOptionNotAvailable				63			//Cause No. 63 �C Service or option not available, unspecified
#define		Q850_BearerCapabilityNotImplemented				65			//Cause No. 65 �C Bearer capability not implemented
#define		Q850_ChannelTypeNotImplemented					66			//Cause No. 66 �C Channel type not implemented
#define		Q850_RequestedFacilityNotImplemented			69			//Cause No. 69 �C Requested facility not implemented
#define		Q850_OnlyRestrictedDigitalInfo					70			//Cause No. 70 �C Only restricted digital information bearer capability is available (national use) 
#define		Q850_ServiceOrOptionNotImplemented				79			//Cause No. 79 �C Service or option not implemented, unspecified
#define		Q850_InvalidCallReferenceValue					81			//Cause No. 81 �C Invalid call reference value
#define		Q850_IdentifiedChannelDoesNotExist				82			//Cause No. 82 �C Identified channel does not exist
#define		Q850_ASuspendedCallExists						83			//Cause No. 83 �C A suspended call exists, but this call identity does not
#define		Q850_CallIdentityInUse							84			//Cause No. 84 �C Call identity in use
#define		Q850_NoCallSuspended							85			//Cause No. 85 �C No call suspended
#define		Q850_CallHavingTheRequested						86			//Cause No. 86 �C Call having the requested call identity has been cleared
#define		Q850_UserNotMemberOfCUG							87			//Cause No. 87 �C User not member of CUG
#define		Q850_IncompatibleDestination					88			//Cause No. 88 �C Incompatible destination
#define		Q850_NonExistentCUG								90			//Cause No. 90 �C Non-existent CUG
#define		Q850_InvalidTransitNetwork						91			//Cause No. 91 �C Invalid transit network selection (national use)
#define		Q850_InvalidMessage								95			//Cause No. 95 �C Invalid message, unspecified
#define		Q850_MandatoryInformation						96			//Cause No. 96 �C Mandatory information element is missing
#define		Q850_MessageTypeNonExistent						97			//Cause No. 97 �C Message type non-existent or not implemented
#define		Q850_MessageNotCompatible						98			//Cause No. 98 �C Message not compatible with call state or message type non-existent or not implemented
#define		Q850_ParameterNonExistent						99			//Cause No. 99 �C Information element/parameter non-existent or not implemented
#define		Q850_InvalidInformationElement					100			//Cause No. 100 �C Invalid information element contents
#define		Q850_MessageNotCompatibleWithCallState			101			//Cause No. 101 �C Message not compatible with call state
#define		Q850_RecoveryOnTimerExpiry						102			//Cause No: 102 �C Recovery on timer expiry
#define		Q850_MessageWithUnrecognizedParameterDiscarded	110			//Cause No: 110 �C Message with unrecognized parameter discarded
#define		Q850_ProtocolError								111			//Cause No. 111 �C Protocol error, unspecified
#define		Q850_Interworking								127			//Cause No. 127 �C interworking, unspecified

#endif


