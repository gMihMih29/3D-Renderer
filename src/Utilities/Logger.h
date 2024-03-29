#pragma once

#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

namespace Utilities {

class Logger {
    static constexpr const char* kEmpty = "";
    static constexpr const char* kError = "ERROR";
    static constexpr const char* kInfo = "INFO";

public:
    static const Logger kConsole;
    static const Logger kConsoleTimeSpan;
    static const Logger kLoggerFile;

    Logger();
    explicit Logger(bool use_time_span);
    explicit Logger(std::string path, bool use_time_span = false);

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
    // std::ofstream fout_;
};

template <class T>
void Logger::Log(const T& message) const {
    LogWithType_(message, kEmpty);
}

template <class T>
void Logger::Error(const T& message) const {
    LogWithType_(message, kError);
}

template <class T>
void Logger::Info(const T& message) const {
    LogWithType_(message, kInfo);
}

template <class T>
void Logger::LogWithType_(const T& message, const std::string& type) const {
    if (write_to_file_) {
        auto fout = std::ofstream(path_);
        if (!type.empty()) {
            fout << "[" << type << "] ";
        }
        if (use_time_stamp_) {
            fout << GetCurrentTimeLog_();
        }
        fout << message << std::endl;
        fout.flush();
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
