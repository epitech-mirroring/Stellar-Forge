/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include <gtest/gtest.h>

#include "common/json/JsonArray.hpp"
#include "common/json/JsonBoolean.hpp"
#include "common/json/JsonNull.hpp"
#include "common/json/JsonNumber.hpp"
#include "common/json/JsonObject.hpp"
#include "common/json/JsonParser.hpp"
#include "common/json/JsonReader.hpp"
#include "common/json/JsonString.hpp"

TEST(JsonReader, read_empty) {
    auto const parser = json::JsonParser();
    json::JsonReader const reader(&parser);
    const json::IJsonObject *const tmp = reader << "{}";
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    ASSERT_EQ(obj->getValue<json::JsonBoolean>("key"), nullptr);
}

TEST(JsonReader, read_string) {
    auto const parser = json::JsonParser();
    json::JsonReader const reader(&parser);
    const json::IJsonObject *const tmp = reader << R"({"key": "value"})";
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    const auto *const str = obj->getValue<json::JsonString>("key");
    ASSERT_EQ(str->getValue(), "value");
}

TEST(JsonReader, read_int) {
    auto const parser = json::JsonParser();
    json::JsonReader const reader(&parser);
    const json::IJsonObject *const tmp = reader << R"({"key": 42})";
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    const auto *const num = obj->getValue<json::JsonNumber>("key");
    ASSERT_EQ(num->getIntValue(), 42);
}

TEST(JsonReader, read_float) {
    auto const parser = json::JsonParser();
    json::JsonReader const reader(&parser);
    const json::IJsonObject *const tmp = reader << R"({"key": 42.42})";
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    const auto *const num = obj->getValue<json::JsonNumber>("key");
    ASSERT_FLOAT_EQ(num->getFloatValue(), 42.42);
}

TEST(JsonReader, read_array) {
    auto const parser = json::JsonParser();
    json::JsonReader const reader(&parser);
    const json::IJsonObject *const tmp = reader << R"({"key": [1, 2, 3]})";
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    const auto *const arr = obj->getValue<json::JsonArray<json::JsonNumber> >("key");
    ASSERT_EQ(arr->getValues().size(), 3);
    ASSERT_EQ(arr->getValues()[0]->getIntValue(), 1);
    ASSERT_EQ(arr->getValues()[1]->getIntValue(), 2);
    ASSERT_EQ(arr->getValues()[2]->getIntValue(), 3);
}

TEST(JsonReader, read_nested) {
    auto const parser = json::JsonParser();
    json::JsonReader const reader(&parser);
    const json::IJsonObject *const tmp = reader << R"({"key": {"key": "value"}})";
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    const auto *const nested = obj->getValue<json::JsonObject>("key");
    ASSERT_EQ(nested->getValue<json::JsonString>("key")->getValue(), "value");
}

TEST(JsonReader, read_null) {
    auto const parser = json::JsonParser();
    json::JsonReader const reader(&parser);
    const json::IJsonObject *const tmp = reader << R"({"key": null})";
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    const auto *const null = obj->getValue<json::JsonNull>("key");
    ASSERT_EQ(null->getValue(), nullptr);
}

TEST(JsonReader, read_boolean) {
    auto const parser = json::JsonParser();
    json::JsonReader const reader(&parser);
    const json::IJsonObject *const tmp = reader << R"({"key": true})";
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    const auto *const boolean = obj->getValue<json::JsonBoolean>("key");
    ASSERT_EQ(boolean->getValue(), true);
}

TEST(JsonReader, read_boolean_false) {
    auto const parser = json::JsonParser();
    json::JsonReader const reader(&parser);
    const json::IJsonObject *const tmp = reader << R"({"key": false})";
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    const auto *const boolean = obj->getValue<json::JsonBoolean>("key");
    ASSERT_EQ(boolean->getValue(), false);
}

TEST(JsonReader, read_nested_array) {
    auto const parser = json::JsonParser();
    json::JsonReader const reader(&parser);
    const json::IJsonObject *const tmp = reader << R"({"key": [{"key": "value"}]})";
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    const auto *const arr = obj->getValue<json::JsonArray<json::JsonObject> >("key");
    ASSERT_EQ(arr->getValues().size(), 1);
    const auto *const nested = arr->getValues()[0];
    ASSERT_EQ(nested->getValue<json::JsonString>("key")->getValue(), "value");
}
