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
 * @file        Cynara.cpp
 * @author      Lukasz Wojciechowski <l.wojciechow@partner.samsung.com>
 * @version     1.0
 * @brief       This file implements main class of cynara service
 */

#include <memory>
#include <stddef.h>

#include <exceptions/InitException.h>

#include <logic/Logic.h>
#include <sockets/SocketManager.h>
#include <storage/InMemoryStorageBackend.h>
#include <storage/Storage.h>
#include <storage/StorageBackend.h>

#include "Cynara.h"

namespace Cynara {

Cynara::Cynara()
    : m_logic(nullptr), m_socketManager(nullptr), m_storage(nullptr), m_storageBackend(nullptr) {
}

Cynara::~Cynara() {
    finalize();
}

void Cynara::init(void) {
    m_logic = std::make_shared<Logic>();
    m_socketManager = std::make_shared<SocketManager>();
    m_storageBackend = std::make_shared<InMemoryStorageBackend>();
    m_storage = std::make_shared<Storage>(*m_storageBackend);

    m_logic->bindStorage(m_storage);
    m_logic->bindSocketManager(m_socketManager);

    m_socketManager->bindLogic(m_logic);
}

void Cynara::run(void) {
    m_socketManager->run();
}

void Cynara::finalize(void) {
    m_logic->unbindAll();
    m_socketManager->unbindAll();

    m_logic.reset();
    m_socketManager.reset();
    m_storageBackend.reset();
    m_storage.reset();
}

} // namespace Cynara
