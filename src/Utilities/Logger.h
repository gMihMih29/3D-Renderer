#pragma once

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

namespace Utilities {
class Logger {
    const std::string kEMPTY = "";
    const std::string kERROR = "ERROR";
    const std::string kINFO = "INFO";
public:
    static const Logger console;
    static const Logger consoleTimeSpan;
    static const Logger loggerFile;

    Logger();
    Logger(bool useTimeStamp);
    Logger(std::string path, bool useTimeStamp = false);

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

    bool writeToFile_;
    bool useTimeStamp_;
    std::string path_;
    // std::ofstream fout_;
};

template <class T>
void Logger::Log(const T& message) const {
    LogWithType_(message, kEMPTY);
}

template <class T>
void Logger::Error(const T& message) const {
    LogWithType_(message, kERROR);
}

template <class T>
void Logger::Info(const T& message) const {
    LogWithType_(message, kINFO);
}

template <class T>
void Logger::LogWithType_(const T& message, const std::string& type) const {
    if (writeToFile_) {
        auto fout = std::ofstream(path_);
        if (!type.empty()) {
            fout << "[" << type << "] ";
        }
        if (useTimeStamp_) {
            fout << GetCurrentTimeLog_();
        }
        fout << message << std::endl;
        fout.flush();
        fout.close();
    } else {
        if (!type.empty()) {
            std::cout << "[" << type << "] ";
        }
        if (useTimeStamp_) {
            std::cout << GetCurrentTimeLog_();
        }
        std::cout << message << std::endl;
        std::cout.flush();
    }
}
};  // namespace Utilities
