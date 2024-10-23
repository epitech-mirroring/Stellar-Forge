/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include <iomanip>
#include <gtest/gtest.h>

#include "common/utils/Logger.hpp"

TEST(Logger, info) {
    const Logger logger;
    testing::internal::CaptureStdout();
    std::chrono::time_point<std::chrono::system_clock> const now =
            std::chrono::system_clock::now();
    logger.info("test");
    const std::string output = testing::internal::GetCapturedStdout();
    const std::string time = output.substr(output.find('[') + 1, output.find(']') - 1);
    const std::size_t timeEnd = output.find(']');
    const std::size_t levelStart = output.find('[', timeEnd);
    const std::size_t end = output.find(']', levelStart);
    const std::string level = output.substr(levelStart + 1, end - levelStart - 1);
    const std::string message = output.substr(end + 1, output.size() - end - 1);
    std::tm parsedTime{};
    std::istringstream stringStream(time);
    stringStream >> std::get_time(&parsedTime, "%Y-%m-%d %H:%M:%S");
    const auto timePoint = std::chrono::system_clock::from_time_t(
        std::mktime(&parsedTime));
    ASSERT_TRUE(
        std::chrono::duration_cast<std::chrono::seconds>(now - timePoint).count() < 1);
    ASSERT_EQ(level, "INFO");
    ASSERT_EQ(message, " test\n");
}

TEST(Logger, debug) {
    const Logger logger;
    testing::internal::CaptureStdout();
    std::chrono::time_point<std::chrono::system_clock> const now =
            std::chrono::system_clock::now();
    logger.debug("test");
    const std::string output = testing::internal::GetCapturedStdout();
    const std::string time = output.substr(output.find('[') + 1, output.find(']') - 1);
    const std::size_t timeEnd = output.find(']');
    const std::size_t levelStart = output.find('[', timeEnd);
    const std::size_t end = output.find(']', levelStart);
    const std::string level = output.substr(levelStart + 1, end - levelStart - 1);
    const std::string message = output.substr(end + 1, output.size() - end - 1);
    std::tm parsedTime{};
    std::istringstream stringStream(time);
    stringStream >> std::get_time(&parsedTime, "%Y-%m-%d %H:%M:%S");
    const auto timePoint = std::chrono::system_clock::from_time_t(
        std::mktime(&parsedTime));
    ASSERT_TRUE(
        std::chrono::duration_cast<std::chrono::seconds>(now - timePoint).count() < 1);
    ASSERT_EQ(level, "DEBUG");
    ASSERT_EQ(message, " test\n");
}

TEST(Logger, warn) {
    const Logger logger;
    testing::internal::CaptureStdout();
    std::chrono::time_point<std::chrono::system_clock> const now =
            std::chrono::system_clock::now();
    logger.warn("test");
    const std::string output = testing::internal::GetCapturedStdout();
    const std::string time = output.substr(output.find('[') + 1, output.find(']') - 1);
    const std::size_t timeEnd = output.find(']');
    const std::size_t levelStart = output.find('[', timeEnd);
    const std::size_t end = output.find(']', levelStart);
    const std::string level = output.substr(levelStart + 1, end - levelStart - 1);
    const std::string message = output.substr(end + 1, output.size() - end - 1);
    std::tm parsedTime{};
    std::istringstream stringStream(time);
    stringStream >> std::get_time(&parsedTime, "%Y-%m-%d %H:%M:%S");
    const auto timePoint = std::chrono::system_clock::from_time_t(
        std::mktime(&parsedTime));
    ASSERT_TRUE(
        std::chrono::duration_cast<std::chrono::seconds>(now - timePoint).count() < 1);
    ASSERT_EQ(level, "WARNING");
    ASSERT_EQ(message, " test\n");
}

TEST(Logger, error) {
    const Logger logger;
    testing::internal::CaptureStderr();
    std::chrono::time_point<std::chrono::system_clock> const now =
            std::chrono::system_clock::now();
    logger.error("test");
    const std::string output = testing::internal::GetCapturedStderr();
    const std::string time = output.substr(output.find('[') + 1, output.find(']') - 1);
    const std::size_t timeEnd = output.find(']');
    const std::size_t levelStart = output.find('[', timeEnd);
    const std::size_t end = output.find(']', levelStart);
    const std::string level = output.substr(levelStart + 1, end - levelStart - 1);
    const std::string message = output.substr(end + 1, output.size() - end - 1);
    std::tm parsedTime{};
    std::istringstream stringStream(time);
    stringStream >> std::get_time(&parsedTime, "%Y-%m-%d %H:%M:%S");
    const auto timePoint = std::chrono::system_clock::from_time_t(
        std::mktime(&parsedTime));
    ASSERT_TRUE(
        std::chrono::duration_cast<std::chrono::seconds>(now - timePoint).count() < 1);
    ASSERT_EQ(level, "ERROR");
    ASSERT_EQ(message, " test\n");
}

TEST(Logger, errorException) {
    const Logger logger;
    testing::internal::CaptureStderr();
    std::chrono::time_point<std::chrono::system_clock> const now =
            std::chrono::system_clock::now();
    logger.error(std::runtime_error("test"));
    const std::string output = testing::internal::GetCapturedStderr();
    const std::string time = output.substr(output.find('[') + 1, output.find(']') - 1);
    const std::size_t timeEnd = output.find(']');
    const std::size_t levelStart = output.find('[', timeEnd);
    const std::size_t end = output.find(']', levelStart);
    const std::string level = output.substr(levelStart + 1, end - levelStart - 1);
    const std::string message = output.substr(end + 1, output.size() - end - 1);
    std::tm parsedTime{};
    std::istringstream stringStream(time);
    stringStream >> std::get_time(&parsedTime, "%Y-%m-%d %H:%M:%S");
    const auto timePoint = std::chrono::system_clock::from_time_t(
        std::mktime(&parsedTime));
    ASSERT_TRUE(
        std::chrono::duration_cast<std::chrono::seconds>(now - timePoint).count() < 1);
    ASSERT_EQ(level, "ERROR");
    ASSERT_EQ(message, " test\n");
}
