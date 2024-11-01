/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include <iomanip>
#include <gtest/gtest.h>

#include "StellarForge/Common/utils/Logger.hpp"
#include "StellarForge/Common/utils/LoggerScopes.hpp"
#include "StellarForge/Common/utils/StringUtils.hpp"

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

TEST(Logger, scopes) {
    std::stringstream output;
    std::stringstream error;
    LoggerScopes::getInstance()->addScope("test", std::cout, std::cerr);
    LoggerScopes::getInstance()->addScope("test2", output, error);

    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    Logger const logger("test");
    Logger const logger2("test2");

    logger.info("30b9c3f1-109f-4da2-b9c3-f1109feda2df");
    logger2.info("8de2a2d4-5940-4452-a2a2-d459405452ef");
    logger.error("39de41f0-e787-4d15-9e41-f0e787ad151a");
    logger2.error("f4c55f63-e22c-41e9-855f-63e22c11e95a");

    ASSERT_TRUE(StringUtils::endsWith(testing::internal::GetCapturedStdout(),
        "30b9c3f1-109f-4da2-b9c3-f1109feda2df\n"));
    ASSERT_TRUE(StringUtils::endsWith(testing::internal::GetCapturedStderr(),
        "39de41f0-e787-4d15-9e41-f0e787ad151a\n"));
    ASSERT_TRUE(StringUtils::endsWith(output.str(),
        "8de2a2d4-5940-4452-a2a2-d459405452ef\n"));
    ASSERT_TRUE(StringUtils::endsWith(error.str(),
        "f4c55f63-e22c-41e9-855f-63e22c11e95a\n"));
}
