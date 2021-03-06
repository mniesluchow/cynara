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
 * @file        policybucket.cpp
 * @author      Aleksander Zdyb <a.zdyb@partner.samsung.com>
 * @version     1.0
 * @brief       Tests for Cynara::PolicyBucket
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "types/PolicyBucket.h"
#include "types/PolicyKey.h"
#include "types/PolicyCollection.h"

#include "../../helpers.h"

#include <algorithm>
#include <tuple>

using namespace Cynara;

class PolicyBucketFixture : public ::testing::Test {
public:
    virtual ~PolicyBucketFixture() {}

protected:
    const PolicyKey pk1 = Helpers::generatePolicyKey("1");
    const PolicyKey otherPk = Helpers::generatePolicyKey("_");

    const PolicyCollection pk1Policies = {
        Policy::simpleWithKey(pk1, PredefinedPolicyType::ALLOW),
        Policy::simpleWithKey(pk1, PredefinedPolicyType::ALLOW),
        Policy::simpleWithKey(pk1, PredefinedPolicyType::ALLOW)
    };

    const PolicyCollection wildcardPolicies = {
        Policy::simpleWithKey(PolicyKey("c1", "u1", "p1"), PredefinedPolicyType::ALLOW),
        Policy::simpleWithKey(PolicyKey("c1", "u1", "p2"), PredefinedPolicyType::ALLOW),
        Policy::simpleWithKey(PolicyKey("c2", "u1", "p1"), PredefinedPolicyType::ALLOW)
    };

    PolicyCollection filterHelper(const PolicyCollection &original,
            std::function<bool(const PolicyCollection::value_type &)> pred) {
        PolicyCollection filtered(original.size());
        auto endIt = std::copy_if(std::begin(original), std::end(original),
            std::begin(filtered), pred);
        filtered.resize(std::distance(std::begin(filtered), endIt));
        return filtered;
    }
};

TEST_F(PolicyBucketFixture, filtered) {
    using ::testing::UnorderedElementsAreArray;
    using ::testing::UnorderedElementsAre;
    using ::testing::IsEmpty;

    PolicyBucket bucket(pk1Policies);
    bucket.setDefaultPolicy(PredefinedPolicyType::DENY);
    auto filtered = bucket.filtered(pk1);

    // Elements match
    ASSERT_THAT(filtered.policyCollection(), UnorderedElementsAreArray(pk1Policies));

    // default policy matches
    ASSERT_EQ(PredefinedPolicyType::DENY, filtered.defaultPolicy());
}

TEST_F(PolicyBucketFixture, filtered_other) {
    using ::testing::UnorderedElementsAreArray;
    using ::testing::UnorderedElementsAre;
    using ::testing::IsEmpty;

    PolicyBucket bucket(pk1Policies);
    bucket.setDefaultPolicy(PredefinedPolicyType::DENY);
    auto filtered = bucket.filtered(otherPk);

    // No policies should be found
    ASSERT_THAT(filtered.policyCollection(), IsEmpty());

    // default policy should be preserved
    ASSERT_EQ(PredefinedPolicyType::DENY, filtered.defaultPolicy());
}

TEST_F(PolicyBucketFixture, filtered_wildcard_privilege) {
    using ::testing::UnorderedElementsAreArray;

    // Leave policies with given client, given user and any privilege
    auto policiesToStay = filterHelper(wildcardPolicies,
        [] (const PolicyCollection::value_type &privilege) {
            const auto &key = privilege->key();
            return std::tie("c1", "u1") == std::tie(key.client(), key.user());
        });

    PolicyBucket bucket(wildcardPolicies);
    auto filtered = bucket.filtered(PolicyKey("c1", "u1", "*"));
    ASSERT_THAT(filtered.policyCollection(), UnorderedElementsAreArray(policiesToStay));
}

TEST_F(PolicyBucketFixture, filtered_wildcard_client) {
    using ::testing::UnorderedElementsAreArray;

    // Leave policies with given client, given user and any privilege
    auto policiesToStay = filterHelper(wildcardPolicies,
        [] (const PolicyCollection::value_type &privilege) {
            const auto &key = privilege->key();
            return std::tie("u1", "p1") == std::tie(key.user(), key.privilege());
        });

    PolicyBucket bucket(wildcardPolicies);
    auto filtered = bucket.filtered(PolicyKey("*", "u1", "p1"));
    ASSERT_THAT(filtered.policyCollection(), UnorderedElementsAreArray(policiesToStay));
}

TEST_F(PolicyBucketFixture, filtered_wildcard_client_privilege) {
    using ::testing::UnorderedElementsAreArray;

    // Leave policies with given client, given user and any privilege
    auto policiesToStay = filterHelper(wildcardPolicies,
        [] (const PolicyCollection::value_type &privilege) {
            const auto &key = privilege->key();
            return key.user() == "u1";
        });

    PolicyBucket bucket(wildcardPolicies);
    auto filtered = bucket.filtered(PolicyKey("*", "u1", "*"));
    ASSERT_THAT(filtered.policyCollection(), UnorderedElementsAreArray(policiesToStay));
}

TEST_F(PolicyBucketFixture, filtered_wildcard_none) {
    using ::testing::IsEmpty;

    PolicyBucket bucket(wildcardPolicies);
    auto filtered = bucket.filtered(PolicyKey("*", "u2", "*"));
    ASSERT_THAT(filtered.policyCollection(), IsEmpty());
}
