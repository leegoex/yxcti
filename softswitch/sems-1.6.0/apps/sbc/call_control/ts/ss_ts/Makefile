# Complier
CC = g++ -g -DLINUX  -g -m32 -D_DEBUG -std=gnu++0x  -DUNIX -DLINUX_SERVICE

kfpccom_ld = -lpthread

# public
PUBLIC_FILE = kfpc_compressfiletask \
kfpc_linuxwinapi \
kfpc_log \
kfpc_mempool \
kfpc_scanlogpath \
kfpc_scanuncompressedlogfiletask \
kfpc_sn32 \
kfpc_sn64 \
kfpc_threadpool \
kfpc_threadtask \
kfpc_threadtaskqueue \
kfpc_time \
kfpc_timer \
md5 \
kfpc_guid	\

#EHANG_HOME?=/home/ehang
#ISXAPI_INC=${EHANG_HOME}/inc/isxapi ${EHANG_HOME}/inc/oamapi ${EHANG_HOME}/inc/prdapi
#ISXAPI_LIB=${EHANG_HOME}/lib

#libpcre++
PCRECPP_FILE = pcre++ \
get \
replace \
search \
split \

# TServer
TSERVER_FILE = \
KFPC_Channel \
KFPC_ChMgr \
KFPC_ChRes \
KFPC_TServerConfigFile \
KFPC_MonitorChMgr \
KFPC_NodeMgr \
KFPC_TServer \
KFPC_TServerDef \
KFPC_TServerMain \
KFPC_ExeCmdIDTask \
KFPC_CheckInvalidCallID \
KFPC_MonitorRefreshData \
KFPC_CallAlarmMgr \
KFPC_EH_MsgID	\
kfpc_error	\
kfpc_id	\
KFPC_TSLicSer \
KFPC_TSLicSerMgr \
KFPC_VoiceSer \
KFPC_VoiceSerMgr \
KFPC_ConfChannel \
KFPC_CmdMgr \
KFPC_TrunkGroup \
KFPC_TrunkGroupMgr \
KFPC_EHNode \
KFPC_ComApiHanderImp \
KFPC_EH_ID2Str \
KFPC_TServerAPIHandler \
KFPC_TServerAPIHandlerImp \
KFPC_TServerAPIPack \
KFPC_CmdTimer \


#contact_center_public
CONTACT_CENTER_PUBLIC_FILE= \
DataBaseAccess \
hash \
KFPC_API_Handle \
KFPC_AppMainThread \
KFPC_BaseCmdMgr \
KFPC_BaseCommand \
KFPC_ComApiHandler \
KFPC_ConfigFile \
KFPC_ContactCenterPublicDef \
KFPC_DBAccessInfo \
KFPC_DBTask \
KFPC_DBThreadPool \
KFPC_LinuxDaemon \
KFPC_LoopHandler \
KFPC_NumberAnalyse \
KFPC_StringUtils \
KFPC_LicCtrl \

#LICENSESERAPI
LICENSE_SER_API_FILE = \
KFPC_TSLicenseSerAPIHandlerImp \
KFPC_LicenseSerAPIHandler\


#faxserapi
FAX_SER_API_FILE = \
 \
 \

#voiceserapi
VOICE_SER_API_FILE = \
KFPC_VoiceSerAPIHandler \
KFPC_VoiceSerAPIHandlerImp\


#ttsserapi
TTS_SER_API_FILE = \
 \

#tinyxpath_1_3_1
TINYXPATH_1_3_1_FILE=\
tinystr \
tinyxml \
tinyxmlerror \
tinyxmlparser \
action_store \
lex_util \
node_set \
tokenlist \
xml_util \
xpath_expression \
xpath_processor \
xpath_stack \
xpath_stream \
xpath_syntax \
xpath_static 

# ThirdPark
APR_INC = /usr/include/apr-1/
#APR_FLAGS =  -L/home/ehang/lib

PUB_INC = ./kfpc_inc
API_INC = ./kfpc_api
CONTROL_INC = ./control
CFGMOD_INC = ./cfg_mod
SERVERMGR_INC = ./servermgr

TINYXML_DIR = ./tinyxml 
TINYXPATH_DIR = ./tinyxpath_1_3_1

SSL_INC = ../../ThirdPartyLib\OpenSSL-Win32\include

CONTACT_CENTER_PUBLIC_INC = ./contact_center_public

LICENSE_SER_API_INC = ./KFPC_LicenseSer
FAX_SER_API_INC = ./KFPC_FaxSer
VOICE_SER_API_INC = ./KFPC_VoiceSer
TTS_SER_API_INC = ./KFPC_TTSSer

BUILD_DIR = .
PUBLIC_DIR = ./kfpc_public
PCREPLUS_DIR = ./libpcre++
CONTACT_CENTER_PUBLIC_DIR = ./contact_center_public

SRC_DIR = .\
../kfpc_com \
${PUBLIC_DIR} \
${PCREPLUS_DIR} \
${CONTACT_CENTER_PUBLIC_DIR} \
${FAX_SER_API_INC} \
${VOICE_SER_API_INC} \
${TTS_SER_API_INC} \
${LICENSE_SER_API_INC} \
${TINYXML_DIR}	\
${PUB_INC}	\
${TINYXPATH_DIR} \
${CFGMOD_INC} \
${SERVERMGR_INC} \
${CONTROL_INC} \
${API_INC} \


INC_DIR = /usr/include /usr/local/include \
			${SRC_DIR} \
			${APR_INC} \
			${PCRE_INC} \
			${PUB_INC} \
			$(API_INC) \
			$(CONTROL_INC) \
			$(CFGMOD_INC) \
			$(SERVERMGR_INC) \
			${CONTACT_CENTER_PUBLIC_INC} \
			${TINYXML_DIR} \
			${ISXAPI_INC} \
			${FAX_SER_API_INC} \
			${VOICE_SER_API_INC} \
			${LICENSE_SER_API_INC} \
			${SSL_INC} \
			${TTS_SER_API_INC} \
			${TINYXPATH_DIR} \
			${PUBLIC_DIR}

OBJ_DIR = ${BUILD_DIR}/.obj

#文件搜索目录
vpath %.cpp ${SRC_DIR}
vpath %.h ${SRC_DIR}
vpath %.o ${OBJ_DIR}
vpath %.c ${SRC_DIR}

#addprefix为每个文件名添加前缀
INCLUDE_FLAG = $(addprefix -I, ${INC_DIR})

#addsuffix 函数会自动的将后缀 SUFFIX 添加到每个文件名的后边

PUBLIC_OBJECT = $(addsuffix .o, ${PUBLIC_FILE})
KFPCCOM_OBJECT = $(addsuffix .o, ${KFPCCOM_FILE})
PCRECPP_OBJECT = $(addsuffix .o, ${PCRECPP_FILE})
TSERVER_OBJECT = $(addsuffix .o, ${TSERVER_FILE})
FAXSERVER_OBJECT = $(addsuffix .o, ${FAX_SER_API_FILE})
TTSSERVER_OBJECT = $(addsuffix .o, ${TTS_SER_API_FILE})
VOICESERVER_OBJECT = $(addsuffix .o, ${VOICE_SER_API_FILE})
LICENSESERVER_OBJECT = $(addsuffix .o, ${LICENSE_SER_API_FILE})
CONTACT_CENTER_PUBLIC_OBJECT = $(addsuffix .o, ${CONTACT_CENTER_PUBLIC_FILE})
TINYXML_OBJECT = $(addsuffix .o, ${TINYXPATH_1_3_1_FILE})


# Command lines

MKOBJDIR = if [ -d ${OBJ_DIR} ]; then exit 0; else mkdir ${OBJ_DIR}; fi

CLEAN = rm -rf ${OBJ_DIR} KFPC_TServer

CPPFLAGS = -DKFPC_LOG_OUTPUT

COMPLIE_CMD = ${CC} ${CPPFLAGS} -c $< -o ${OBJ_DIR}/$@ 	\
	      	${INCLUDE_FLAG} 			\

ECHO_OBJECT_CMD = echo -e "\t" $@

OBJECTS = $(addprefix ${OBJ_DIR}/, ${PUBLIC_OBJECT} 	\
			${KFPCCOM_OBJECT} 		\
			${PCRECPP_OBJECT} 		\
			${TSERVER_OBJECT}		\
			${FAXSERVER_OBJECT}		\
			${TTSSERVER_OBJECT}		\
			${VOICESERVER_OBJECT}		\
			${CONTACT_CENTER_PUBLIC_OBJECT} \
			${LICENSESERVER_OBJECT} \
			${TINYXML_OBJECT}) \

# LD_FLAGS = $(kfpccom_ld) -lisxapi -loamapi -lkfpc_com -lz -lpcre -L ../../kfpc_com/kfpc_com -L${ISXAPI_LIB} -lodbc -lapr-0 -ldl -lssl
LD_FLAGS = $(kfpccom_ld) -L./lib -lkfpc_com -lz -lpcre  -lodbc -lapr-1 -ldl -lssl

LINK_CMD = ${CC} -o $@ ${OBJECTS} ${APR_FLAGS} ${LD_FLAGS}  ${CPPFLAGS}

#PHONY 来显示的指名一个目标是伪目标，有两个作用一个是改善性能，另外一个是来避免冲突。
.PHONY: all

all: TempDir SS_TServer 

TempDir:
	@${MKOBJDIR}

SS_TServer: ${PUBLIC_OBJECT} ${PCRECPP_OBJECT} ${KFPCCOM_OBJECT} ${TSERVER_OBJECT} ${LICENSESERVER_OBJECT} ${FAXSERVER_OBJECT} ${TTSSERVER_OBJECT} ${VOICESERVER_OBJECT} ${CONTACT_CENTER_PUBLIC_OBJECT} ${TINYXML_OBJECT}
	@echo "Complier complete. Linking ....\n"
	
	${LINK_CMD}
	/bin/cp -f -R $@ /home/CloudShare/bin
clean:
	@${CLEAN}

# public
kfpc_compressfiletask.o:${PUBLIC_DIR}/kfpc_compressfiletask.cpp \
${PUBLIC_DIR}/kfpc_compressfiletask.h
	
	${COMPLIE_CMD} 

kfpc_linuxwinapi.o:${PUBLIC_DIR}/kfpc_linuxwinapi.cpp ${PUBLIC_DIR}/kfpc_linuxwinapi.h
	
	${COMPLIE_CMD} 

kfpc_log.o:${PUBLIC_DIR}/kfpc_log.cpp ${PUBLIC_DIR}/kfpc_log.h
	
	${COMPLIE_CMD} 

kfpc_mempool.o:${PUBLIC_DIR}/kfpc_mempool.cpp ${PUBLIC_DIR}/kfpc_mempool.h
	
	${COMPLIE_CMD} 

kfpc_scanlogpath.o:${PUBLIC_DIR}/kfpc_scanlogpath.cpp ${PUBLIC_DIR}/kfpc_scanlogpath.h
	
	${COMPLIE_CMD} 

kfpc_scanuncompressedlogfiletask.o:${PUBLIC_DIR}/kfpc_scanuncompressedlogfiletask.cpp ${PUBLIC_DIR}/kfpc_scanuncompressedlogfiletask.h
	
	${COMPLIE_CMD} 

kfpc_sn32.o:${PUBLIC_DIR}/kfpc_sn32.cpp ${PUBLIC_DIR}/kfpc_sn32.h
	
	${COMPLIE_CMD} 

kfpc_sn64.o:${PUBLIC_DIR}/kfpc_sn64.cpp ${PUBLIC_DIR}/kfpc_sn64.h
	
	${COMPLIE_CMD} 

kfpc_threadpool.o:${PUBLIC_DIR}/kfpc_threadpool.cpp ${PUBLIC_DIR}/kfpc_threadpool.h
	
	${COMPLIE_CMD} 

kfpc_threadtask.o:${PUBLIC_DIR}/kfpc_threadtask.cpp ${PUBLIC_DIR}/kfpc_threadtask.h
	
	${COMPLIE_CMD} 

kfpc_threadtaskqueue.o:${PUBLIC_DIR}/kfpc_threadtaskqueue.cpp ${PUBLIC_DIR}/kfpc_threadtaskqueue.h
	
	${COMPLIE_CMD} 

kfpc_timer.o:${PUBLIC_DIR}/kfpc_timer.cpp ${PUBLIC_DIR}/kfpc_timer.h
	
	${COMPLIE_CMD} 

kfpc_time.o:${PUBLIC_DIR}/kfpc_time.cpp ${PUBLIC_DIR}/kfpc_time.h
	
	${COMPLIE_CMD} 

md5.o:${PUBLIC_DIR}/md5.c ${PUBLIC_DIR}/md5.h
	
	@${COMPLIE_CMD}

kfpc_guid.o:${PUBLIC_DIR}/kfpc_guid.cpp ${PUBLIC_DIR}/kfpc_guid.h
	
	${COMPLIE_CMD} 

# pcre++
pcre++.o:${PCREPLUS_DIR}/pcre++.cc ${PCREPLUS_DIR}/pcre++.h
	
	${COMPLIE_CMD} 

get.o:${PCREPLUS_DIR}/get.cc
	
	${COMPLIE_CMD} 

replace.o:${PCREPLUS_DIR}/replace.cc 
	
	${COMPLIE_CMD} 

search.o:${PCREPLUS_DIR}/search.cc 
	
	@${COMPLIE_CMD}

split.o:${PCREPLUS_DIR}/split.cc 
	
	@${COMPLIE_CMD}

# TServer
KFPC_Channel.o:KFPC_Channel.cpp	
	${COMPLIE_CMD} 

KFPC_ChMgr.o:KFPC_ChMgr.cpp
	
	${COMPLIE_CMD} 

KFPC_ChRes.o:KFPC_ChRes.cpp
	
	${COMPLIE_CMD} 

KFPC_MonitorChMgr.o:KFPC_MonitorChMgr.cpp
	
	${COMPLIE_CMD}   

KFPC_NodeMgr.o:KFPC_NodeMgr.cpp
	
	${COMPLIE_CMD} 

KFPC_TServer.o:KFPC_TServer.cpp
	
	${COMPLIE_CMD} 

KFPC_TServerDef.o:KFPC_TServerDef.cpp
	
	${COMPLIE_CMD} 

KFPC_TServerMain.o:KFPC_TServerMain.cpp
	
	${COMPLIE_CMD} 

#LicenseSerApi
	
#faxserapi

#voiceserapi

#ttsserapi

#contact_center_public
hash.o:hash.cpp
	
	${COMPLIE_CMD} 

KFPC_API_Handle.o:KFPC_API_Handle.cpp
	
	${COMPLIE_CMD} 

KFPC_AppMainThread.o:KFPC_AppMainThread.cpp
	
	${COMPLIE_CMD} 

KFPC_ComApiHandler.o:KFPC_ComApiHandler.cpp
	
	${COMPLIE_CMD} 

KFPC_BaseCmdMgr.o:KFPC_BaseCmdMgr.cpp
	
	${COMPLIE_CMD}
	
KFPC_BaseCommand.o:KFPC_BaseCommand.cpp
	
	${COMPLIE_CMD}	
	
KFPC_ConfigFile.o:KFPC_ConfigFile.cpp
	
	${COMPLIE_CMD} 

KFPC_ContactCenterPublicDef.o:KFPC_ContactCenterPublicDef.cpp	
	
	${COMPLIE_CMD} 

KFPC_ExeCmdIDTask.o:KFPC_ExeCmdIDTask.cpp
	${COMPLIE_CMD} 


KFPC_DBTask.o:KFPC_DBTask.cpp
	
	${COMPLIE_CMD} 

KFPC_DBThreadPool.o:KFPC_DBThreadPool.cpp
	
	${COMPLIE_CMD} 

KFPC_LinuxDaemon.o:KFPC_LinuxDaemon.cpp
	
	${COMPLIE_CMD} 

KFPC_LoopHandler.o:KFPC_LoopHandler.cpp
	
	${COMPLIE_CMD} 

KFPC_NumberAnalyse.o:KFPC_NumberAnalyse.cpp
	
	${COMPLIE_CMD} 

KFPC_StringUtils.o:KFPC_StringUtils.cpp
	
	${COMPLIE_CMD} 

KFPC_LicCtrl.o:KFPC_LicCtrl.cpp
	
	${COMPLIE_CMD} 
	
DataBaseAccess.o:DataBaseAccess.cpp
	
	${COMPLIE_CMD} 

KFPC_DBAccessInfo.o:KFPC_DBAccessInfo.cpp
	
	${COMPLIE_CMD} 

KFPC_CheckInvalidCallID.o:KFPC_CheckInvalidCallID.cpp
	${COMPLIE_CMD} 

KFPC_MonitorRefreshData.o:KFPC_MonitorRefreshData.cpp
	${COMPLIE_CMD} 
KFPC_CallAlarmMgr.o:KFPC_CallAlarmMgr.cpp
	${COMPLIE_CMD} 

#tinyxpath_1_3_1

tinystr.o:tinystr.cpp
	
	${COMPLIE_CMD} 

tinyxml.o:tinyxml.cpp
	
	${COMPLIE_CMD} 

tinyxmlerror.o:tinyxmlerror.cpp
	
	${COMPLIE_CMD} 

tinyxmlparser.o:tinyxmlparser.cpp
	
	${COMPLIE_CMD} 

action_store.o:action_store.cpp
	
	${COMPLIE_CMD} 

lex_util.o:lex_util.cpp
	
	${COMPLIE_CMD} 

node_set.o:node_set.cpp
	
	${COMPLIE_CMD} 

tokenlist.o:tokenlist.cpp
	
	${COMPLIE_CMD} 

xml_util.o:xml_util.cpp
	
	${COMPLIE_CMD} 

xpath_expression.o:xpath_expression.cpp
	
	${COMPLIE_CMD} 

xpath_processor.o:xpath_processor.cpp
	
	${COMPLIE_CMD} 

xpath_stack.o:xpath_stack.cpp
	
	${COMPLIE_CMD} 

xpath_stream.o:xpath_stream.cpp
	
	${COMPLIE_CMD} 

xpath_syntax.o:xpath_syntax.cpp
	
	${COMPLIE_CMD} 

xpath_static.o: xpath_static.cpp
	
	${COMPLIE_CMD} 

KFPC_EH_MsgID.o:KFPC_EH_MsgID.c
	${COMPLIE_CMD} 

kfpc_error.o:kfpc_error.c
	${COMPLIE_CMD} 

kfpc_id.o:kfpc_id.c
	${COMPLIE_CMD} 

KFPC_TServerConfigFile.o:KFPC_TServerConfigFile.cpp	
	${COMPLIE_CMD} 

KFPC_TSLicSer.o:KFPC_TSLicSer.cpp
	
	${COMPLIE_CMD} 
	
KFPC_TSLicSerMgr.o:KFPC_TSLicSerMgr.cpp
	
	${COMPLIE_CMD} 

KFPC_VoiceSer.o:KFPC_VoiceSer.cpp
	
	${COMPLIE_CMD} 

KFPC_VoiceSerMgr.o:KFPC_VoiceSerMgr.cpp
	
	${COMPLIE_CMD} 

KFPC_VoiceSerAPIHandlerImp.o:KFPC_VoiceSerAPIHandlerImp.cpp
	
	${COMPLIE_CMD} 

KFPC_TSLicenseSerAPIHandlerImp.o:KFPC_TSLicenseSerAPIHandlerImp.cpp	
	${COMPLIE_CMD} 	

KFPC_LicenseSerAPIHandler.o:KFPC_LicenseSerAPIHandler.cpp	
	${COMPLIE_CMD} 

KFPC_VoiceSerAPIHandler.o:KFPC_VoiceSerAPIHandler.cpp	
	${COMPLIE_CMD} 

KFPC_ConfChannel.o:KFPC_ConfChannel.cpp
	${COMPLIE_CMD} 

KFPC_CmdMgr.o:KFPC_CmdMgr.cpp	
	${COMPLIE_CMD} 

KFPC_TrunkGroup.o:KFPC_TrunkGroup.cpp	
	${COMPLIE_CMD} 

KFPC_TrunkGroupMgr.o:KFPC_TrunkGroupMgr.cpp	
	${COMPLIE_CMD} 

KFPC_ComApiHanderImp.o:KFPC_ComApiHanderImp.cpp	
	${COMPLIE_CMD}

KFPC_EHNode.o:KFPC_EHNode.cpp	
	${COMPLIE_CMD} 

KFPC_EH_ID2Str.o:KFPC_EH_ID2Str.cpp
	${COMPLIE_CMD} 

KFPC_TServerAPIHandler.o:KFPC_TServerAPIHandler.cpp	
	${COMPLIE_CMD} 

KFPC_TServerAPIHandlerImp.o:KFPC_TServerAPIHandlerImp.cpp	
	${COMPLIE_CMD} 

KFPC_TServerAPIPack.o:KFPC_TServerAPIPack.cpp	
	${COMPLIE_CMD} 

KFPC_CmdTimer.o:KFPC_CmdTimer.cpp
	${COMPLIE_CMD} 