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
#include "common/json/JsonPrettyWriter.hpp"
#include "common/json/JsonString.hpp"

TEST(JsonPrettyWriter, write_empty) {
  json::JsonParser const parser;
  const auto *const tmp = parser.parse(R"({})");
  std::ostringstream output;
  json::JsonPrettyWriter const writer(tmp);
  output << writer;
  ASSERT_STREQ(output.str().c_str(), "{\n  \n}");
}

TEST(JsonPrettyWriter, write_string) {
  json::JsonParser const parser;
  const auto *const tmp = parser.parse(R"({"key": "value"})");
  std::ostringstream output;
  json::JsonPrettyWriter const writer(tmp);
  output << writer;
  ASSERT_STREQ(output.str().c_str(), R"({
  "key": "value"
})");
}

TEST(JsonPrettyWriter, write_int) {
  json::JsonParser const parser;
  const auto *const tmp = parser.parse(R"({"key": 42})");
  std::ostringstream output;
  json::JsonPrettyWriter const writer(tmp);
  output << writer;
  ASSERT_STREQ(output.str().c_str(), R"({
  "key": 42
})");
}

TEST(JsonPrettyWriter, write_array) {
  json::JsonParser const parser;
  const auto *const tmp = parser.parse(R"({"key": [1, 2, 3]})");
  std::ostringstream output;
  json::JsonPrettyWriter const writer(tmp);
  output << writer;
  ASSERT_STREQ(output.str().c_str(), R"({
  "key": [
    1,
    2,
    3
  ]
})");
}

TEST(JsonPrettyWriter, write_nested) {
  json::JsonParser const parser;
  const auto *const tmp = parser.parse(R"({"key": {"key": "value"}})");
  std::ostringstream output;
  json::JsonPrettyWriter const writer(tmp);
  output << writer;
  ASSERT_STREQ(output.str().c_str(), R"({
  "key": {
    "key": "value"
  }
})");
}

TEST(JsonPrettyWriter, write_nested_array) {
  json::JsonParser const parser;
  const auto *const tmp = parser.parse(R"({"key": [{"key": "value"}]})");
  std::ostringstream output;
  json::JsonPrettyWriter const writer(tmp);
  output << writer;
  ASSERT_STREQ(output.str().c_str(), R"({
  "key": [
    {
      "key": "value"
    }
  ]
})");
}

TEST(JsonPrettyWriter, write_boolean) {
  json::JsonParser const parser;
  const auto *const tmp = parser.parse(R"({"key": true})");
  std::ostringstream output;
  json::JsonPrettyWriter const writer(tmp);
  output << writer;
  ASSERT_STREQ(output.str().c_str(), R"({
  "key": true
})");
}

TEST(JsonPrettyWriter, write_null) {
  json::JsonParser const parser;
  const auto *const tmp = parser.parse(R"({"key": null})");
  std::ostringstream output;
  json::JsonPrettyWriter const writer(tmp);
  output << writer;
  ASSERT_STREQ(output.str().c_str(), R"({
  "key": null
})");
}
