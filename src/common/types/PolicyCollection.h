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
 * @file        PolicyCollection.h
 * @author      Lukasz Wojciechowski <l.wojciechow@partner.samsung.com>
 * @author      Aleksander Zdyb <a.zdyb@partner.samsung.com>
 * @version     1.0
 * @brief       This file defines a collection of policies
 */

#ifndef CYNARA_COMMON_TYPES_POLICYCOLLECTION_H
#define CYNARA_COMMON_TYPES_POLICYCOLLECTION_H

#include "types/pointers.h"

#include <vector>

namespace Cynara {

typedef std::vector<PolicyPtr> PolicyCollection;

} // namespace Cynara

#endif /* CYNARA_COMMON_TYPES_POLICYCOLLECTION_H     */
