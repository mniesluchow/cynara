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
 * @file        buckets.cpp
 * @author      Aleksander Zdyb <a.zdyb@partner.samsung.com>
 * @version     1.0
 * @brief       Tests of buckets in InMemeoryStorageBackend
 */

#include "gmock/gmock.h"

#include "inmemeorystoragebackendfixture.h"
#include "fakeinmemorystoragebackend.h"

#include "types/PolicyResult.h"
#include "types/PolicyBucket.h"

using namespace Cynara;

TEST_F(InMemeoryStorageBackendFixture, addBucket) {
    using ::testing::ReturnRef;
    using ::testing::IsEmpty;

    FakeInMemoryStorageBackend backend;
    EXPECT_CALL(backend, buckets())
        .WillOnce(ReturnRef(m_buckets));

    PolicyResult defaultPolicy(PredefinedPolicyType::ALLOW);
    PolicyBucketId bucketId = "new-bucket";
    backend.createBucket(bucketId, defaultPolicy);

    ASSERT_EQ(1, m_buckets.size());
    ASSERT_NE(m_buckets.end(), m_buckets.find(bucketId));
    ASSERT_EQ(defaultPolicy, m_buckets.at(bucketId).defaultPolicy());
    ASSERT_THAT(m_buckets.at(bucketId).policyCollection(), IsEmpty());
}


TEST_F(InMemeoryStorageBackendFixture, deleteBucket) {
    using ::testing::ReturnRef;
    using ::testing::IsEmpty;

    FakeInMemoryStorageBackend backend;
    EXPECT_CALL(backend, buckets())
        .WillOnce(ReturnRef(m_buckets));

    PolicyBucketId bucketId = "delete-bucket";
    m_buckets.insert({ bucketId, PolicyBucket() });

    backend.deleteBucket(bucketId);

    ASSERT_THAT(m_buckets, IsEmpty());
}

TEST_F(InMemeoryStorageBackendFixture, deleteNonexistentBucket) {
    using ::testing::ReturnRef;

    FakeInMemoryStorageBackend backend;
    EXPECT_CALL(backend, buckets())
        .WillOnce(ReturnRef(m_buckets));

    EXPECT_THROW(backend.deleteBucket("non-existent"), BucketNotExistsException);
}
