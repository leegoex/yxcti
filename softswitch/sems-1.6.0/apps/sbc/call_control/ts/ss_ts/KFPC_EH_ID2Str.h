#ifndef IDTOSTR_H
#define IDTOSTR_H
const char* ToneIDToStr(int ID);
const char* MessageMaskIDToStr(int ID);
const char* ChActionToStr(int ID);
const char* ChStatusToStr(int ID);
const char* SignalTypeToStr(int SignalType);
const char* StatusToStr(unsigned char ucStatus);
const char* SIPReasonStatusToStr(long ccValue);
unsigned char StrToAudioCodeID(const char* pCodeID);
//unsigned char StrToPayloadID(const char* pCodeID);

const char*	TermToStr(unsigned long mask);

const char* OperToStr(int val);
const char* CallTermMaskToStr(int val);
const char* ReleaseCallReason(long ccValue);
const char* SYSEvtToStr(unsigned int Evt);

const char* DevTypeToStr(int val);
//const char* KFPC_PayloadIDToAudioCode(int PayloadID);
const char* KFPC_CodeIDToAudioCode(unsigned char CodeID);
const char* EHProtocol2Str(unsigned int Pro);
#endif
