#pragma once

#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

namespace Utilities {

class SimpleLogger {
    static constexpr const char* kEmpty = "";
    static constexpr const char* kError = "ERROR";
    static constexpr const char* kInfo = "INFO";

public:
    static const SimpleLogger kConsole;
    static const SimpleLogger kConsoleTimeSpan;
    static const SimpleLogger kLoggerFile;

    SimpleLogger();
    explicit SimpleLogger(bool use_time_span);
    explicit SimpleLogger(std::string path, bool use_time_span = false);

    void Log(const char* message) const;
    template <class T>
    void Log(const T& message) const;

    void Error(const char* message) const;
    template <class T>
    void Error(const T& message) const;

    void Info(const char* message) const;
    template <class T>
    void Info(const T& message) const;

private:
    void LogWithType_(const char* message, const std::string& type) const;
    template <class T>
    void LogWithType_(const T& message, const std::string& type) const;

    static std::string GetCurrentTimeLog_();
    static std::string GetCurrentDay_();

    bool write_to_file_;
    bool use_time_stamp_;
    std::string path_;
};

template <class T>
void SimpleLogger::Log(const T& message) const {
    LogWithType_(message, kEmpty);
}

template <class T>
void SimpleLogger::Error(const T& message) const {
    LogWithType_(message, kError);
}

template <class T>
void SimpleLogger::Info(const T& message) const {
    LogWithType_(message, kInfo);
}

template <class T>
void SimpleLogger::LogWithType_(const T& message, const std::string& type) const {
    if (write_to_file_) {
        std::ofstream fout(path_, std::ios_base::app);
        if (!fout.is_open()) {
            return;
        }
        if (!type.empty()) {
            fout << "[" << type << "] ";
        }
        if (use_time_stamp_) {
            fout << GetCurrentTimeLog_();
        }
        fout << message << std::endl;
        fout.close();
    } else {
        if (!type.empty()) {
            std::cout << "[" << type << "] ";
        }
        if (use_time_stamp_) {
            std::cout << GetCurrentTimeLog_();
        }
        std::cout << message << std::endl;
        std::cout.flush();
    }
}

};  // namespace Utilities
