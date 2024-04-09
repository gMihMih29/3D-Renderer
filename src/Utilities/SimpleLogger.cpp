#include "SimpleLogger.h"

namespace Utilities {
    
const SimpleLogger SimpleLogger::kConsole = Utilities::SimpleLogger();
const SimpleLogger SimpleLogger::kConsoleTimeSpan = Utilities::SimpleLogger(true);
const SimpleLogger SimpleLogger::kLoggerFile = Utilities::SimpleLogger("../logs/" + SimpleLogger::GetCurrentDay_() + ".log", true);

SimpleLogger::SimpleLogger() : write_to_file_(false), use_time_stamp_(false) {
}

SimpleLogger::SimpleLogger(bool use_time_stamp) : write_to_file_(false), use_time_stamp_(use_time_stamp) {
}

SimpleLogger::SimpleLogger(std::string path, bool use_time_stamp)
    : write_to_file_(true), use_time_stamp_(use_time_stamp), path_(path) {
}

std::string SimpleLogger::GetCurrentTimeLog_() {
    const int start_year = 1900;
    const int limit_for_one_char_number = 10;
    std::string res;
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    res += '[';
    res += std::to_string(now->tm_year + start_year);
    res += '/';
    if (now->tm_mon < limit_for_one_char_number) {
        res += '0';
    }
    res += std::to_string(now->tm_mon);
    res += '/';
    if (now->tm_mday < limit_for_one_char_number) {
        res += '0';
    }
    res += std::to_string(now->tm_mday);
    res += ' ';
    if (now->tm_hour < limit_for_one_char_number) {
        res += '0';
    }
    res += std::to_string(now->tm_hour);
    res += ':';
    if (now->tm_min < limit_for_one_char_number) {
        res += '0';
    }
    res += std::to_string(now->tm_min);
    res += ':';
    if (now->tm_sec < limit_for_one_char_number) {
        res += '0';
    }
    res += std::to_string(now->tm_sec);
    res += "] ";
    return res;
}

std::string SimpleLogger::GetCurrentDay_() {
    const int start_year = 1900;
    const int limit_for_one_char_number = 10;
    std::string res;
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    res += std::to_string(now->tm_year + start_year);
    res += '-';
    if (now->tm_mon < limit_for_one_char_number) {
        res += '0';
    }
    res += std::to_string(now->tm_mon);
    res += '-';
    if (now->tm_mday < limit_for_one_char_number) {
        res += '0';
    }
    res += std::to_string(now->tm_mday);
    return res;
}

void SimpleLogger::Log(const char* message) const {
    LogWithType_(message, kEmpty);
}

void SimpleLogger::Error(const char* message) const {
    LogWithType_(message, kError);
}

void SimpleLogger::Info(const char* message) const {
    LogWithType_(message, kInfo);
}

void SimpleLogger::LogWithType_(const char* message, const std::string& type) const {
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

}  // namespace Utilities
