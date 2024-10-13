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
#include "common/json/JsonString.hpp"

TEST(JsonParser, parse_empty) {
    json::JsonParser const parser;
    const auto *const tmp = parser.parse(R"({})");
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    ASSERT_EQ(obj->getValue<json::JsonBoolean>("key"), nullptr);
}

TEST(JsonParser, parse_string) {
    json::JsonParser const parser;
    const auto *const tmp = parser.parse(R"({"key": "value"})");
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    ASSERT_STREQ(obj->getValue<json::JsonString>("key")->getValue().c_str(), "value");
}

TEST(JsonParser, parse_int) {
    json::JsonParser const parser;
    const auto *const tmp = parser.parse(R"({"key": 42})");
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    ASSERT_EQ(obj->getValue<json::JsonNumber>("key")->getIntValue(), 42);
    ASSERT_FALSE(obj->getValue<json::JsonNumber>("key")->isFloat());
}

TEST(JsonParser, parse_float) {
    json::JsonParser const parser;
    const auto *const tmp = parser.parse(R"({"key": 42.42})");
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    ASSERT_FLOAT_EQ(obj->getValue<json::JsonNumber>("key")->getFloatValue(), 42.42);
    ASSERT_TRUE(obj->getValue<json::JsonNumber>("key")->isFloat());
}

TEST(JsonParser, parse_array) {
    json::JsonParser const parser;
    const auto *const tmp = parser.parse(R"({"key": [1, 2, 3]})");
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    const auto *const arr = obj->getValue<json::JsonArray<json::JsonNumber> >("key");
    ASSERT_EQ(arr->size(), 3);
    ASSERT_EQ(arr->at(0)->getIntValue(), 1);
    ASSERT_EQ(arr->at(1)->getIntValue(), 2);
    ASSERT_EQ(arr->at(2)->getIntValue(), 3);
}

TEST(JsonParser, parse_nul) {
    json::JsonParser const parser;
    const auto *const tmp = parser.parse(R"({"key": null})");
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    const auto *const nul = obj->getValue<json::JsonNull>("key");
    ASSERT_EQ(nul->getType(), json::NULL_VALUE);
}

TEST(JsonParser, parse_bool) {
    json::JsonParser const parser;
    const auto *const tmp = parser.parse(R"({"key": true})");
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    const auto *const bol = obj->getValue<json::JsonBoolean>("key");
    ASSERT_EQ(bol->getType(), json::BOOLEAN);
    ASSERT_TRUE(bol->getValue());
}

TEST(JsonParser, parse_bool_false) {
    json::JsonParser const parser;
    const auto *const tmp = parser.parse(R"({"key": false})");
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    const auto *const bol = obj->getValue<json::JsonBoolean>("key");
    ASSERT_EQ(bol->getType(), json::BOOLEAN);
    ASSERT_FALSE(bol->getValue());
}

TEST(JsonParser, parse_nested) {
    json::JsonParser const parser;
    const auto *const tmp = parser.parse(R"({"key": {"key": "value"}})");
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    const auto *const nested = obj->getValue<json::JsonObject>("key");
    ASSERT_STREQ(nested->getValue<json::JsonString>("key")->getValue().c_str(), "value");
}

TEST(JsonParser, parse_array_nested) {
    json::JsonParser const parser;
    const auto *const tmp = parser.parse(R"({"key": [{"key": "value"}]})");
    ASSERT_EQ(tmp->getType(), json::OBJECT);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const obj = dynamic_cast<const json::JsonObject *>(tmp);
    const auto *const arr = obj->getValue<json::JsonArray<json::JsonObject> >("key");
    const auto *const nested = arr->at(0);
    ASSERT_STREQ(nested->getValue<json::JsonString>("key")->getValue().c_str(), "value");
}

TEST(JsonParser, root_array) {
    json::JsonParser const parser;
    const auto *const tmp = parser.parse(R"([1, 2, 3])");
    ASSERT_EQ(tmp->getType(), json::ARRAY);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const arr = dynamic_cast<const json::JsonArray<json::JsonNumber> *>(tmp);
    ASSERT_EQ(arr->size(), 3);
    ASSERT_EQ(arr->at(0)->getIntValue(), 1);
    ASSERT_EQ(arr->at(1)->getIntValue(), 2);
    ASSERT_EQ(arr->at(2)->getIntValue(), 3);
}

TEST(JsonParser, array_of_objects) {
    json::JsonParser const parser;
    const auto *const tmp = parser.parse(R"([{"key": "value1"}, {"key": "value2"}])");
    ASSERT_EQ(tmp->getType(), json::ARRAY);
    ASSERT_EQ(tmp->getName(), "");
    const auto *const arr = dynamic_cast<const json::JsonArray<json::JsonObject> *>(tmp);
    ASSERT_EQ(arr->size(), 2);
    ASSERT_STREQ(arr->at(0)->getValue<json::JsonString>("key")->getValue().c_str(),
                 "value1");
    ASSERT_STREQ(arr->at(1)->getValue<json::JsonString>("key")->getValue().c_str(),
                 "value2");
}
