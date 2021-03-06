/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *  Contact: Lukasz Wojciechowski <l.wojciechow@partner.samsung.com>
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
 * @file        ProtocolSerializer.cpp
 * @author      Adam Malinowski <a.malinowsk2@partner.samsung.com>
 * @version     1.0
 * @brief       Implementation of protocol frame (de)serializer class.
 */

#include <exceptions/InvalidProtocolException.h>
#include <exceptions/OutOfDataException.h>

#include "ProtocolFrameSerializer.h"

namespace Cynara {

void ProtocolFrameSerializer::deserializeHeader(ProtocolFrameHeader &frameHeader,
                                                BinaryQueue &data) {
    if (!frameHeader.isHeaderComplete()) {
        if ((data.size() < ProtocolFrameHeader::frameHeaderLength())) {
            return;
        }

        frameHeader.setHeaderContent(BinaryQueuePtr(&data, [=] (BinaryQueue *) {}));

        ProtocolFrameSignature signature;
        ProtocolDeserialization::deserialize(frameHeader, frameHeader.m_signature.length(),
                signature);
        if (ProtocolFrameHeader::m_signature != signature) {
            throw InvalidProtocolException(InvalidProtocolException::InvalidSignature);
        }

        ProtocolDeserialization::deserialize(frameHeader, frameHeader.m_frameLength);
        ProtocolDeserialization::deserialize(frameHeader, frameHeader.m_sequenceNumber);

        frameHeader.setHeaderComplete();
    }

    if (data.size() >= (frameHeader.frameLength() - ProtocolFrameHeader::frameHeaderLength())) {
        frameHeader.setBodyComplete();
    }
}

ProtocolFramePtr ProtocolFrameSerializer::startSerialization(ProtocolFrameSequenceNumber sequenceNumber) {
    BinaryQueuePtr headerQueue = std::make_shared<BinaryQueue>();
    BinaryQueuePtr bodyQueue = std::make_shared<BinaryQueue>();
    ProtocolFrameHeaderPtr header = std::make_shared<ProtocolFrameHeader>(headerQueue);
    header->setSequenceNumber(sequenceNumber);
    header->increaseFrameLength(ProtocolFrameHeader::frameHeaderLength());
    return std::make_shared<ProtocolFrame>(header, bodyQueue);
}

void ProtocolFrameSerializer::finishSerialization(ProtocolFramePtr frame, BinaryQueue &data) {
    ProtocolFrameHeader &frameHeader = *frame->frameHeader();
    ProtocolSerialization::serializeNoSize(frameHeader, ProtocolFrameHeader::m_signature);
    ProtocolSerialization::serialize(frameHeader, frameHeader.m_frameLength);
    ProtocolSerialization::serialize(frameHeader, frameHeader.m_sequenceNumber);

    data.appendMoveFrom(frameHeader.headerContent());
    data.appendMoveFrom(frame->bodyContent());
}

} /* namespace Cynara */
