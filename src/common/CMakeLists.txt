# Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#
# @file        CMakeLists.txt
# @author      Lukasz Wojciechowski <l.wojciechow@partner.samsung.com>
#

SET(CYNARA_COMMON_VERSION_MAJOR 0)
SET(CYNARA_COMMON_VERSION ${CYNARA_COMMON_VERSION_MAJOR}.0.1)

SET(COMMON_PATH ${CYNARA_PATH}/common)

SET(COMMON_SOURCES
    ${COMMON_PATH}/containers/BinaryQueue.cpp
    ${COMMON_PATH}/log/log.cpp
    ${COMMON_PATH}/protocol/ProtocolAdmin.cpp
    ${COMMON_PATH}/protocol/ProtocolClient.cpp
    ${COMMON_PATH}/protocol/ProtocolFrame.cpp
    ${COMMON_PATH}/protocol/ProtocolFrameHeader.cpp
    ${COMMON_PATH}/protocol/ProtocolFrameSerializer.cpp
    ${COMMON_PATH}/protocol/ProtocolSerialization.cpp
    ${COMMON_PATH}/protocol/ProtocolSignal.cpp
    ${COMMON_PATH}/request/CheckRequest.cpp
    ${COMMON_PATH}/request/RequestTaker.cpp
    ${COMMON_PATH}/response/CheckResponse.cpp
    ${COMMON_PATH}/response/ResponseTaker.cpp
    ${COMMON_PATH}/sockets/Socket.cpp
    ${COMMON_PATH}/sockets/SocketClient.cpp
    ${COMMON_PATH}/types/PolicyBucket.cpp
    ${COMMON_PATH}/types/PolicyKey.cpp
    )

IF (CMAKE_BUILD_TYPE MATCHES "DEBUG")
SET(COMMON_SOURCES ${COMMON_SOURCES}
    ${COMMON_PATH}/log/Backtrace.cpp
    )
ENDIF (CMAKE_BUILD_TYPE MATCHES "DEBUG")

ADD_LIBRARY(${TARGET_CYNARA_COMMON} SHARED ${COMMON_SOURCES})

SET_TARGET_PROPERTIES(
    ${TARGET_CYNARA_COMMON}
    PROPERTIES
        COMPILE_FLAGS "-D_GNU_SOURCE -fPIC -fvisibility=default"
        SOVERSION ${CYNARA_COMMON_VERSION_MAJOR}
        VERSION ${CYNARA_COMMON_VERSION}
    )

IF (CMAKE_BUILD_TYPE MATCHES "DEBUG")
SET(CYNARA_DBG_LIBRARIES
    ${CYNARA_DEP_LIBRARIES}
    )
ENDIF (CMAKE_BUILD_TYPE MATCHES "DEBUG")

TARGET_LINK_LIBRARIES(${TARGET_CYNARA_COMMON}
    ${CYNARA_DEP_LIBRARIES}
    ${CYNARA_DBG_LIBRARIES}
    )

INSTALL(TARGETS ${TARGET_CYNARA_COMMON} DESTINATION ${LIB_INSTALL_DIR})
