/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
/*
 * @file        NullPointerException.h
 * @author      Lukasz Wojciechowski <l.wojciechow@partner.samsung.com>
 * @version     1.0
 * @brief       Implementation of OutOfDataException
 */

#ifndef SRC_COMMON_EXCEPTIONS_NULLPOINTEREXCEPTION_H_
#define SRC_COMMON_EXCEPTIONS_NULLPOINTEREXCEPTION_H_

#include <exception>
#include <string>

#include "Exception.h"

namespace Cynara {

class NullPointerException : public Exception {
private:
    std::string m_whatMsg;

public:
    NullPointerException() = delete;
    NullPointerException(const char *varName) {
        m_whatMsg = std::string("unexpected null value in variable <")
                  + std::string(varName)
                  + std::string(">");
    }

    virtual ~NullPointerException() = default;

    virtual const char* what() const noexcept {
        return m_whatMsg.c_str();
    }
};

} // namespace Cynara

#endif /* SRC_COMMON_EXCEPTIONS_NULLPOINTEREXCEPTION_H_ */
