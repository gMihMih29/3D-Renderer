#pragma once

#include <cstring>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>

namespace Utilities {

class StringContainer {
public:
    StringContainer() = default;
    StringContainer(const std::string& str) : str_(str) {
    }

    std::string operator()() {
        return str_;
    }

private:
    std::string str_;
};

class Logger {
    static constexpr const char* kEmpty = "";
    static constexpr const char* kError = "ERROR";
    static constexpr const char* kInfo = "INFO";
    using LoggingAction = std::function<void(const Logger*, const char*, const char*)>;
    using StringFunc = std::function<std::string()>;

public:
    Logger() = default;
    Logger(bool use_time_span);
    Logger(const std::string& path);
    Logger(const std::string& path, bool use_time_span);

    void Log(const std::string& message) const;
    void Error(const std::string& message) const;
    void Info(const std::string& message) const;
    void Log(const char* message) const;
    void Error(const char* message) const;
    void Info(const char* message) const;

    friend const Logger& operator<<(const Logger& logger, const std::string& message) {
        logger.Log(message);
        return logger;
    }

private:
    static void LogToConsole(const Logger* logger, const char* message, const char* type);
    static void LogToFile(const Logger* logger, const char* message, const char* type);
    static std::string EmptyString();
    static std::string CurrentTime();

    LoggingAction log_ = LogToConsole;
    StringFunc time_span_ = EmptyString;
    StringFunc path_ = EmptyString;
};

};  // namespace Utilities
