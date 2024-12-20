/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "Logger.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <chrono>

#include "LoggerScopes.hpp"

Logger::Logger(std::ostream *output, std::ostream *error) noexcept: _output(output),
    _error(error), debug(DebugLevel(&_output)), info(InfoLevel(&_output)),
    warn(WarningLevel(&_output)), error(ErrorLevel(&_error)) {
}

Logger::Logger(const Logger &other) : _output(other._output), _error(other._error),
                                      debug(&_output),
                                      info(&_output),
                                      warn(&_output),
                                      error(&_error) {
}


Logger::Logger(const std::string &scope): debug(DebugLevel(&_output)),
                                          info(InfoLevel(&_output)),
                                          warn(WarningLevel(&_output)),
                                          error(ErrorLevel(&_error)) {
    if (LoggerScopes::getInstance()->hasScope(scope)) {
        auto [output, error] = LoggerScopes::getInstance()->getScope(scope);
        _output = &output;
        _error = &error;
    } else {
        _output = &std::cout;
        _error = &std::cerr;
    }
}


static std::string getCurrentTimeToString() {
    const auto now = std::chrono::system_clock::now();
#if defined(__APPLE__) || defined(__linux__)
    std::time_t const now_c = std::chrono::system_clock::to_time_t(now);
    tm time{};
    tm *time_ptr = &time;
    time_ptr = localtime_r(&now_c, time_ptr);
    std::stringstream inSS;
    inSS << std::put_time(time_ptr, "%Y-%m-%d %H:%M:%S");
    return inSS.str();
#else
#if defined(_WIN32) || defined(_WIN64)
#include <time.h>
    struct tm timeinfo;
    __int64 now_c = std::chrono::system_clock::to_time_t(now);
    localtime_s(&timeinfo, &now_c);
    std::stringstream inSS;
    inSS << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
    return inSS.str();
#else
    return "time not supported";
#endif
#endif
}

void Logger::log(const std::string &message, const Level level) const {
    switch (level) {
        case Level::LOG_DEBUG:
            this->debug << message;
            break;
        default:
        case Level::LOG_INFO:
            this->info << message;
            break;
        case Level::LOG_WARNING:
            this->warn << message;
            break;
        case Level::LOG_ERROR:
            this->error << message;
            break;
    }
}

Logger &Logger::operator=(const Logger &other) {
    if (this == &other) {
        return *this;
    }
    _output = other._output;
    _error = other._error;
    return *this;
}


AbstractLoggerLevel::AbstractLoggerLevel(
    std::ostream **output) noexcept: _output(output) {
}

const ILoggerLevel &AbstractLoggerLevel::operator<<(const std::string &message) const {
    _buffer << message;
    if (message.find('\n') != std::string::npos) {
        flush();
    }
    return *this;
}

void AbstractLoggerLevel::flush() const {
    **_output << "[" << getCurrentTimeToString() << "] ";
    _log(_buffer.str());
    _buffer.str("");
    _buffer.clear();
}


void AbstractLoggerLevel::operator()(const std::string &message) const {
    *this << message << '\n';
}

void AbstractLoggerLevel::operator()(const char *message) const {
    *this << message << '\n';
}

const ILoggerLevel &AbstractLoggerLevel::operator<<(const char *message) const {
    return this->operator<<(std::string(message));
}

const ILoggerLevel &AbstractLoggerLevel::operator<<(const char character) const {
    return this->operator<<(std::string(1, character));
}

void AbstractLoggerLevel::operator()(const char character) const {
    *this << character << '\n';
}

const ILoggerLevel &AbstractLoggerLevel::operator<<(const int number) const {
    return this->operator<<(std::to_string(number));
}

void AbstractLoggerLevel::operator()(const int number) const {
    *this << number << '\n';
}

const ILoggerLevel &AbstractLoggerLevel::operator<<(
    const std::filesystem::path &path) const {
    return this->operator<<(path.string());
}

void AbstractLoggerLevel::operator()(const std::filesystem::path &path) const {
    *this << path.string() << '\n';
}

const ILoggerLevel &AbstractLoggerLevel::operator
<<(const std::exception &exception) const {
    return this->operator<<(exception.what());
}

void AbstractLoggerLevel::operator()(const std::exception &exception) const {
    *this << exception.what() << '\n';
}

DebugLevel::DebugLevel(std::ostream **output) noexcept: AbstractLoggerLevel(output) {
}

void DebugLevel::_log(const std::string &message) const {
    **_output << "[DEBUG] " << message;
}

InfoLevel::InfoLevel(std::ostream **output) noexcept: AbstractLoggerLevel(output) {
}

void InfoLevel::_log(const std::string &message) const {
    **_output << "[INFO] " << message;
}

ErrorLevel::ErrorLevel(std::ostream **output) noexcept: AbstractLoggerLevel(output) {
}

void ErrorLevel::_log(const std::string &message) const {
    **_output << "[ERROR] " << message;
}

WarningLevel::WarningLevel(std::ostream **output) noexcept: AbstractLoggerLevel(output) {
}

void WarningLevel::_log(const std::string &message) const {
    **_output << "[WARNING] " << message;
}
