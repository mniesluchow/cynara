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
 * @file        pointers.h
 * @author      Lukasz Wojciechowski <l.wojciechow@partner.samsung.com>
 * @version     1.0
 * @brief       This file defines request base class
 */

#ifndef SRC_SERVICE_MAIN_POINTERS_H_
#define SRC_SERVICE_MAIN_POINTERS_H_

#include <memory>

namespace Cynara {

class Logic;
typedef std::shared_ptr<Logic> LogicPtr;

class SocketManager;
typedef std::shared_ptr<SocketManager> SocketManagerPtr;

class Storage;
typedef std::shared_ptr<Storage> StoragePtr;

class StorageBackend;
typedef std::shared_ptr<StorageBackend> StorageBackendPtr;

} // namespace Cynara

#endif /* SRC_SERVICE_MAIN_POINTERS_H_ */
