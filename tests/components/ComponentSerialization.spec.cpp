/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include <gtest/gtest.h>

#include "common/components/Transform.hpp"
#include "common/json/JsonArray.hpp"
#include "common/json/JsonBoolean.hpp"
#include "common/json/JsonNumber.hpp"
#include "common/json/JsonString.hpp"

TEST(ComponentSerialization, Transform) {
    Transform transform(nullptr);
    transform.setPosition({1, 2, 3});
    transform.setRotation(glm::quat(glm::vec3(4, 5, 6)));
    transform.setScale({7, 8, 9});

    const auto *const json = transform.serialize();

    ASSERT_EQ(json->getType(), json::JsonType::OBJECT);
    ASSERT_EQ(json->getName(), "root");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(json);
    ASSERT_NE(obj, nullptr);
    ASSERT_TRUE(obj->contains("type"));
    ASSERT_TRUE(obj->contains("isActive"));
    ASSERT_EQ(obj->getValue<json::JsonString>("type")->getValue(), "Transform");
    ASSERT_EQ(obj->getValue<json::JsonBoolean>("isActive")->getValue(), true);
    ASSERT_TRUE(obj->contains("data"));
    const auto *const data = obj->getValue<json::JsonObject>("data");
    ASSERT_NE(data, nullptr);
    ASSERT_TRUE(data->contains("invisible"));
    const auto *const fieldGroup = data->getValue<json::JsonObject>("invisible");
    ASSERT_NE(fieldGroup, nullptr);
    ASSERT_TRUE(fieldGroup->contains("Position"));
    ASSERT_TRUE(fieldGroup->contains("Rotation"));
    ASSERT_TRUE(fieldGroup->contains("Scale"));
    const auto *const position = fieldGroup->getValue<json::JsonObject>("Position");
    const auto *const rotation = fieldGroup->getValue<json::JsonObject>("Rotation");
    const auto *const scale = fieldGroup->getValue<json::JsonObject>("Scale");
    ASSERT_NE(position, nullptr);
    ASSERT_NE(rotation, nullptr);
    ASSERT_NE(scale, nullptr);
    ASSERT_FLOAT_EQ(position->getValue<json::JsonNumber>("x")->getFloatValue(), 1);
    ASSERT_FLOAT_EQ(position->getValue<json::JsonNumber>("y")->getFloatValue(), 2);
    ASSERT_FLOAT_EQ(position->getValue<json::JsonNumber>("z")->getFloatValue(), 3);
    // ASSERT_FLOAT_EQ(rotation->getValue<json::JsonNumber>("x")->getFloatValue(), 4);
    // ASSERT_FLOAT_EQ(rotation->getValue<json::JsonNumber>("y")->getFloatValue(), 5);
    // ASSERT_FLOAT_EQ(rotation->getValue<json::JsonNumber>("z")->getFloatValue(), 6);
    ASSERT_FLOAT_EQ(scale->getValue<json::JsonNumber>("x")->getFloatValue(), 7);
    ASSERT_FLOAT_EQ(scale->getValue<json::JsonNumber>("y")->getFloatValue(), 8);
    ASSERT_FLOAT_EQ(scale->getValue<json::JsonNumber>("z")->getFloatValue(), 9);
}
