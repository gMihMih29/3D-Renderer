#include "Logger.h"

namespace Utilities {
const Logger Logger::console = Utilities::Logger();
const Logger Logger::consoleTimeSpan = Utilities::Logger(true);
const Logger Logger::loggerFile = Utilities::Logger("../logs/" + Logger::GetCurrentDay_() + ".log", true);

Logger::Logger() : writeToFile_(false), useTimeStamp_(false) {
}

Logger::Logger(bool useTimeStamp) : writeToFile_(false), useTimeStamp_(useTimeStamp) {
}

Logger::Logger(std::string path, bool useTimeStamp)
    : writeToFile_(true), useTimeStamp_(useTimeStamp), path_(path) {
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

void Logger::Log(const char* message) const {
    LogWithType_(message, kEMPTY);
}

void Logger::Error(const char* message) const {
    LogWithType_(message, kERROR);
}

void Logger::Info(const char* message) const {
    LogWithType_(message, kINFO);
}

void Logger::LogWithType_(const char* message, const std::string& type) const {
    if (writeToFile_) {
        auto fout = std::ofstream(path_, std::ios_base::app);
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
}  // namespace Utilities
