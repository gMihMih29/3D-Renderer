#include "Logger.h"

namespace Utilities {
Logger Logger::console = Utilities::Logger();
Logger Logger::consoleTimeSpan = Utilities::Logger(true);
Logger Logger::loggerFile = Utilities::Logger("../logs/" + Logger::GetCurrentDay_() + ".log", true);

Logger::Logger() : writeToFile_(false), useTimeStamp_(false) {
}

Logger::Logger(bool useTimeStamp) : writeToFile_(false), useTimeStamp_(useTimeStamp) {
}

Logger::Logger(std::string path, bool useTimeStamp)
    : writeToFile_(true), useTimeStamp_(useTimeStamp), path_(path), fout_(std::ofstream(path, std::ios_base::app))  {
}

Logger::~Logger() {
    fout_.close();
}

std::string Logger::GetCurrentTimeLog_() {
    std::string res;
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    res += '[';
    res += std::to_string(now->tm_year + 1900);
    res += '/';
    if (now->tm_mon < 10) {
        res += '0';
    }
    res += std::to_string(now->tm_mon);
    res += '/';
    if (now->tm_mday < 10) {
        res += '0';
    }
    res += std::to_string(now->tm_mday);
    res += ' ';
    if (now->tm_hour < 10) {
        res += '0';
    }
    res += std::to_string(now->tm_hour);
    res += ':';
    if (now->tm_min < 10) {
        res += '0';
    }
    res += std::to_string(now->tm_min);
    res += ':';
    if (now->tm_sec < 10) {
        res += '0';
    }
    res += std::to_string(now->tm_sec);
    res += "] ";
    return res;
}

std::string Logger::GetCurrentDay_() {
    std::string res;
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    res += std::to_string(now->tm_year + 1900);
    res += '-';
    if (now->tm_mon < 10) {
        res += '0';
    }
    res += std::to_string(now->tm_mon);
    res += '-';
    if (now->tm_mday < 10) {
        res += '0';
    }
    res += std::to_string(now->tm_mday);
    return res;
}

void Logger::Log(const char* message) {
    LogWithType_(message, kEMPTY);
}

void Logger::Error(const char* message) {
    LogWithType_(message, kERROR);
}

void Logger::Info(const char* message) {
    LogWithType_(message, kINFO);
}

void Logger::LogWithType_(const char* message, const std::string& type) {
    if (writeToFile_) {
        if (!type.empty()) {
            fout_ << "[" << type << "] ";
        }
        if (useTimeStamp_) {
            fout_ << GetCurrentTimeLog_();
        }
        fout_ << message << std::endl;
        fout_.flush();
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
}  // namespace Utilities
