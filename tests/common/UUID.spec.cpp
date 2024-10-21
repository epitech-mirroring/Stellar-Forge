/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include <gtest/gtest.h>
#include <unordered_set>
#include "common/UUID.hpp"
#include "common/UUIDException.hpp"

// NOLINTBEGIN
TEST(UUID, constructor) {
    const UUID uuid;
    ASSERT_EQ(uuid.isNullUuid(), true);
    ASSERT_EQ(uuid.getUuidString(), "00000000-0000-0000-0000-000000000000");
    const UUID uuid2;
    ASSERT_EQ(uuid.operator==(uuid2), true);
}

TEST(UUID, copyConstructor) {
    UUID uuid;
    uuid.generateUuid();
    const UUID uuid2(uuid);
    ASSERT_EQ(uuid.isNullUuid(), false);
    ASSERT_EQ(uuid2.isNullUuid(), false);
    ASSERT_EQ(uuid.getUuidString(), uuid2.getUuidString());
}

TEST(UUID, moveConstructor) {
    UUID uuid;
    uuid.generateUuid();
    const UUID uuid2(std::move(uuid));
    ASSERT_EQ(uuid.isNullUuid(), true);
    ASSERT_EQ(uuid2.isNullUuid(), false);
}

TEST(UUID, generateUuid) {
    UUID uuid;
    uuid.generateUuid();
    ASSERT_EQ(uuid.isNullUuid(), false);
    ASSERT_EQ(uuid.getUuidString().size(), 36);
}

TEST(UUID, setUuidFromString) {
    UUID uuid;
    uuid.setUuidFromString("f47ac10b-58cc-4372-a567-0e02b2c3d479");
    ASSERT_EQ(uuid.isNullUuid(), false);
    ASSERT_EQ(uuid.getUuidString(), "f47ac10b-58cc-4372-a567-0e02b2c3d479");
}

TEST(UUID, setUuidFromStringException) {
    UUID uuid;
    ASSERT_THROW(uuid.setUuidFromString("1"), UUIDException);
    ASSERT_THROW(uuid.setUuidFromString("f47ac10b-58cc-4372-a567-0e02b2c3d4791"), UUIDException);
    ASSERT_THROW(uuid.setUuidFromString("f47ac10b-58cc-4372-a567a0e02b2c3d479"), UUIDException);
    ASSERT_THROW(uuid.setUuidFromString("f47ac10b-58cc-4372-a567-0e02z2c3d479"), UUIDException);
}

TEST(UUID, copyUuid) {
    UUID uuid;
    UUID uuid2;
    uuid.generateUuid();
    ASSERT_NE(uuid.getUuidString(), uuid2.getUuidString());
    uuid2.copyUuid(uuid);
    ASSERT_EQ(uuid.isNullUuid(), false);
    ASSERT_EQ(uuid2.isNullUuid(), false);
    ASSERT_EQ(uuid.getUuidString(), uuid2.getUuidString());
}

TEST(UUID, operatorEqual) {
    UUID uuid;
    UUID uuid2;
    ASSERT_EQ(uuid.operator==(uuid2), true);
    uuid.generateUuid();
    ASSERT_EQ(uuid.operator==(uuid2), false);
    uuid2.copyUuid(uuid);
    ASSERT_EQ(uuid.operator==(uuid2), true);
}

TEST(UUID, operatorNotEqual) {
    UUID uuid;
    UUID uuid2;
    ASSERT_EQ(uuid.operator!=(uuid2), false);
    uuid.generateUuid();
    ASSERT_EQ(uuid.operator!=(uuid2), true);
    uuid2.copyUuid(uuid);
    ASSERT_EQ(uuid.operator!=(uuid2), false);
}

TEST(UUID, compareUuid) {
    UUID uuid;
    UUID uuid2;
    ASSERT_EQ(uuid.compareUuid(uuid2), true);
    uuid.generateUuid();
    ASSERT_EQ(uuid.compareUuid(uuid2), false);
    uuid2.copyUuid(uuid);
    ASSERT_EQ(uuid.compareUuid(uuid2), true);
}

TEST(UUID, copyOperator) {
    UUID uuid;
    UUID uuid2;
    uuid.generateUuid();
    ASSERT_NE(uuid.getUuidString(), uuid2.getUuidString());
    ASSERT_EQ(uuid.isNullUuid(), false);
    ASSERT_EQ(uuid2.isNullUuid(), true);
    uuid2 = uuid;
    ASSERT_EQ(uuid.isNullUuid(), false);
    ASSERT_EQ(uuid2.isNullUuid(), false);
    ASSERT_EQ(uuid.getUuidString(), uuid2.getUuidString());
    uuid2 = uuid2;
    ASSERT_EQ(uuid.isNullUuid(), false);
    ASSERT_EQ(uuid2.isNullUuid(), false);
    ASSERT_EQ(uuid.getUuidString(), uuid2.getUuidString());
}

TEST(UUID, moveOperator) {
    UUID uuid;
    UUID uuid2;
    uuid.generateUuid();
    ASSERT_NE(uuid.getUuidString(), uuid2.getUuidString());
    ASSERT_EQ(uuid.isNullUuid(), false);
    ASSERT_EQ(uuid2.isNullUuid(), true);
    uuid2 = std::move(uuid);
    ASSERT_EQ(uuid.isNullUuid(), true);
    ASSERT_EQ(uuid2.isNullUuid(), false);
}

TEST(UUID, lesserOperator) {
    UUID uuid;
    UUID uuid2;
    uuid.setUuidFromString("11111111-1111-1111-1111-111111111111");
    uuid2.setUuidFromString("22222222-2222-2222-2222-222222222222");
    ASSERT_EQ(uuid < uuid2, true);
    ASSERT_EQ(uuid2 < uuid, false);
    uuid2.setUuidFromString("11111111-1111-1111-1111-111111111111");
    ASSERT_EQ(uuid < uuid2, false);
    ASSERT_EQ(uuid2 < uuid, false);
}

TEST(UUID, ostreamOperator) {
    UUID uuid;
    uuid.setUuidFromString("f47ac10b-58cc-4372-a567-0e02b2c3d479");
    std::stringstream ss;
    ss << uuid;
    ASSERT_EQ(ss.str(), "f47ac10b-58cc-4372-a567-0e02b2c3d479");
}

TEST(UUID, checkUniqueness) {
    std::unordered_set<UUID> uuids;

    for (int i = 0; i < 100; i++) {
        UUID uuid;
        uuid.generateUuid();
        uuids.insert(uuid);
    }
    ASSERT_EQ(uuids.size(), 100);
}
// NOLINTEND
