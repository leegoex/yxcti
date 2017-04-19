#ifndef _Q850_H_
#define	_Q850_H_
#define		Q850_UnallocatedNumber							1			//Cause No. 1 每 Unallocated (unassigned) number
#define		Q850_Noroute									2			//Cause No. 2 每 No route to specified transit network (national use)
#define		Q850_NoRouteToDestination						3			//Cause No. 3 每 No route to destination
#define		Q850_SendSpecialInformationTone					4			//Cause No. 4 每 Send special information tone
#define		Q850_MisdialledTrunkPrefix						5			//Cause No. 5 每 Misdialled trunk prefix (national use)
#define		Q850_ChannelUnacceptable						6			//Cause No. 6 每 Channel unacceptable
#define		Q850_CallAwarded								7			//Cause No. 7 每 Call awarded and being delivered in an established channel
#define		Q850_Preemption									8			//Cause No. 8 每 Preemption
#define		Q850_PreemptionCircuit							9			//Cause No. 9 每 Preemption - circuit reserved for reuse
#define		Q850_NormalCallClearing							16			//Cause No. 16 每 Normal call clearing
#define		Q850_UserBusy									17			//Cause No. 17 每 User busy
#define		Q850_NoUserResponding							18			//Cause No. 18 每 No user responding
#define		Q850_NoAnswerFromUser							19			//Cause No. 19 每 No answer from user (user alerted)
#define		Q850_SubscriberAbsent							20			//Cause No. 20 每 Subscriber absent
#define		Q850_CallRejected								21			//Cause No. 21 每 Call rejected
#define		Q850_NumberChanged								22			//Cause No. 22 每 Number changed
#define		Q850_NonSelectedUserClearing					26			//Cause No. 26 每 Non-selected user clearing
#define		Q850_DestinationOutOfOrder						27			//Cause No. 27 每 Destination out of order
#define		Q850_InvalidNumberFormat						28			//Cause No. 28 每 Invalid number format (address incomplete)
#define		Q850_FacilityRejected							29			//Cause No. 29 每 Facility rejected
#define		Q850_ResponseToSTATUSENQUIRY					30			//Cause No. 30 每 Response to STATUS ENQUIRY
#define		Q850_NormalUnspecified							31			//Cause No. 31 每 Normal, unspecified
#define		Q850_NoCircuit									34			//Cause No. 34 每 No circuit/channel available
#define		Q850_NetworkOutOfOrder							38			//Cause No. 38 每 Network out of order
#define		Q850_PermanentFrameModeConnectionOutOfService	39			//Cause No. 39 每 Permanent frame mode connection out-of-service
#define		Q850_PermanentFrameModeConnectionOperational	40			//Cause No. 40 每 Permanent frame mode connection operational
#define		Q850_TemporaryFailure							41			//Cause No. 41 每 Temporary failure
#define		Q850_SwitchingEquipmentCongestion				42			//Cause No. 42 每 Switching equipment congestion
#define		Q850_AccessInformationDiscarded					43			//Cause No. 43 每 Access information discarded
#define		Q850_ChannelNotAvailable						44			//Cause No. 44 每 Requested circuit/channel not available
#define		Q850_PrecedenceCallBlocked						46			//Cause No. 46 每 Precedence call blocked
#define		Q850_ResourceUnavailable						47			//Cause No. 47 每 Resource unavailable, unspecified
#define		Q850_QualityOfServiceNotAvailable				49			//Cause No. 49 每 Quality of Service not available
#define		Q850_RequestedFacilityNotSubscribed				50			//Cause No. 50 每 Requested facility not subscribed
#define		Q850_OutgoingCallsBarredWithinCUG				53			//Cause No. 53 每 Outgoing calls barred within CUG
#define		Q850_IncomingCallsBarredWithinCUG				55			//Cause No. 55 每 Incoming calls barred within CUG
#define		Q850_BearerCapabilityNotAuthorized				57			//Cause No. 57 每 Bearer capability not authorized
#define		Q850_BearerCapabilityNotPresentlyAvailable		58			//Cause No. 58 每 Bearer capability not presently available
#define		Q850_InconsistencyInformationAndSubscriberClass	62			//Cause No. 62 每 Inconsistency in designated outgoing access information and subscriber class
#define		Q850_ServiceOrOptionNotAvailable				63			//Cause No. 63 每 Service or option not available, unspecified
#define		Q850_BearerCapabilityNotImplemented				65			//Cause No. 65 每 Bearer capability not implemented
#define		Q850_ChannelTypeNotImplemented					66			//Cause No. 66 每 Channel type not implemented
#define		Q850_RequestedFacilityNotImplemented			69			//Cause No. 69 每 Requested facility not implemented
#define		Q850_OnlyRestrictedDigitalInfo					70			//Cause No. 70 每 Only restricted digital information bearer capability is available (national use) 
#define		Q850_ServiceOrOptionNotImplemented				79			//Cause No. 79 每 Service or option not implemented, unspecified
#define		Q850_InvalidCallReferenceValue					81			//Cause No. 81 每 Invalid call reference value
#define		Q850_IdentifiedChannelDoesNotExist				82			//Cause No. 82 每 Identified channel does not exist
#define		Q850_ASuspendedCallExists						83			//Cause No. 83 每 A suspended call exists, but this call identity does not
#define		Q850_CallIdentityInUse							84			//Cause No. 84 每 Call identity in use
#define		Q850_NoCallSuspended							85			//Cause No. 85 每 No call suspended
#define		Q850_CallHavingTheRequested						86			//Cause No. 86 每 Call having the requested call identity has been cleared
#define		Q850_UserNotMemberOfCUG							87			//Cause No. 87 每 User not member of CUG
#define		Q850_IncompatibleDestination					88			//Cause No. 88 每 Incompatible destination
#define		Q850_NonExistentCUG								90			//Cause No. 90 每 Non-existent CUG
#define		Q850_InvalidTransitNetwork						91			//Cause No. 91 每 Invalid transit network selection (national use)
#define		Q850_InvalidMessage								95			//Cause No. 95 每 Invalid message, unspecified
#define		Q850_MandatoryInformation						96			//Cause No. 96 每 Mandatory information element is missing
#define		Q850_MessageTypeNonExistent						97			//Cause No. 97 每 Message type non-existent or not implemented
#define		Q850_MessageNotCompatible						98			//Cause No. 98 每 Message not compatible with call state or message type non-existent or not implemented
#define		Q850_ParameterNonExistent						99			//Cause No. 99 每 Information element/parameter non-existent or not implemented
#define		Q850_InvalidInformationElement					100			//Cause No. 100 每 Invalid information element contents
#define		Q850_MessageNotCompatibleWithCallState			101			//Cause No. 101 每 Message not compatible with call state
#define		Q850_RecoveryOnTimerExpiry						102			//Cause No: 102 每 Recovery on timer expiry
#define		Q850_MessageWithUnrecognizedParameterDiscarded	110			//Cause No: 110 每 Message with unrecognized parameter discarded
#define		Q850_ProtocolError								111			//Cause No. 111 每 Protocol error, unspecified
#define		Q850_Interworking								127			//Cause No. 127 每 interworking, unspecified

#endif


