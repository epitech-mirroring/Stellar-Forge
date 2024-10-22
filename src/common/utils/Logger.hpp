/*
** EPITECH PROJECT, 2024
** StellarForge
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <iostream>
#include <string>
#include <exception>
#include <sstream>

class ILoggerLevel {
public:
    virtual ~ILoggerLevel() = default;

    virtual const ILoggerLevel &operator<<(const std::string &message) const = 0;

    virtual void operator()(const std::string &message) const = 0;

    virtual const ILoggerLevel &operator<<(const char *message) const = 0;

    virtual void operator()(const char *message) const = 0;

    virtual const ILoggerLevel &operator<<(const std::exception &exception) const = 0;

    virtual void operator()(const std::exception &exception) const = 0;

    virtual const ILoggerLevel &operator<<(char character) const = 0;

    virtual void operator()(char character) const = 0;

    virtual const ILoggerLevel &operator<<(int number) const = 0;

    virtual void operator()(int number) const = 0;
};

class AbstractLoggerLevel : public virtual ILoggerLevel {
protected:
    std::ostream *_output;
    mutable std::stringstream _buffer;

    virtual void _log(const std::string &message) const = 0;

public:
    explicit AbstractLoggerLevel(std::ostream *output) noexcept;

    ~AbstractLoggerLevel() override = default;

    const ILoggerLevel &operator<<(const std::string &message) const override;

    void operator()(const std::string &message) const override;

    const ILoggerLevel &operator<<(const char *message) const override;

    void operator()(const char *message) const override;

    const ILoggerLevel &operator<<(const std::exception &exception) const override;

    void operator()(const std::exception &exception) const override;

    const ILoggerLevel &operator<<(char character) const override;

    void operator()(char character) const override;

    const ILoggerLevel &operator<<(int number) const override;

    void operator()(int number) const override;

    void flush() const;
};

class DebugLevel final : public AbstractLoggerLevel {
protected:
    void _log(const std::string &message) const override;

public:
    explicit DebugLevel(std::ostream *output = &std::cout) noexcept;

    ~DebugLevel() override = default;
};

class InfoLevel final : public AbstractLoggerLevel {
protected:
    void _log(const std::string &message) const override;

public:
    explicit InfoLevel(std::ostream *output = &std::cout) noexcept;

    ~InfoLevel() override = default;
};

class WarningLevel final : public AbstractLoggerLevel {
protected:
    void _log(const std::string &message) const override;

public:
    explicit WarningLevel(std::ostream *output = &std::cout) noexcept;

    ~WarningLevel() override = default;
};

class ErrorLevel final : public AbstractLoggerLevel {
protected:
    void _log(const std::string &message) const override;

public:
    explicit ErrorLevel(std::ostream *output = &std::cerr) noexcept;

    ~ErrorLevel() override = default;
};

class Logger {
protected:
    std::ostream *_output;
    std::ostream *_error;

public:
    DebugLevel debug;
    InfoLevel info;
    WarningLevel warn;
    ErrorLevel error;

    enum class Level: uint8_t {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    explicit Logger(std::ostream *output = &std::cout,
                    std::ostream *error = &std::cerr) noexcept;

    ~Logger() = default;

    void log(const std::string &message, Level level = Level::INFO) const;
};

#endif //LOGGER_HPP