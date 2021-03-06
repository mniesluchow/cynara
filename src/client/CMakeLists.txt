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

SET(LIB_CYNARA_VERSION_MAJOR 0)
SET(LIB_CYNARA_VERSION ${LIB_CYNARA_VERSION_MAJOR}.0.2)

SET(CYNARA_LIB_CYNARA_PATH ${CYNARA_PATH}/client)

SET(LIB_CYNARA_SOURCES
    ${CYNARA_LIB_CYNARA_PATH}/api/client-api.cpp
    ${CYNARA_LIB_CYNARA_PATH}/logic/Logic.cpp
    )

INCLUDE_DIRECTORIES(
    ${CYNARA_LIB_CYNARA_PATH}
    )

ADD_LIBRARY(${TARGET_LIB_CYNARA} SHARED ${LIB_CYNARA_SOURCES})

SET_TARGET_PROPERTIES(
    ${TARGET_LIB_CYNARA}
    PROPERTIES
        COMPILE_FLAGS "-D_GNU_SOURCE -fPIC -fvisibility=hidden"
        SOVERSION ${LIB_CYNARA_VERSION_MAJOR}
        VERSION ${LIB_CYNARA_VERSION}
    )

TARGET_LINK_LIBRARIES(${TARGET_LIB_CYNARA}
    ${CYNARA_DEP_LIBRARIES}
    ${TARGET_CYNARA_COMMON}
    )

INSTALL(TARGETS ${TARGET_LIB_CYNARA} DESTINATION ${LIB_INSTALL_DIR})
