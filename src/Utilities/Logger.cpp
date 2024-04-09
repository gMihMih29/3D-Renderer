#include "Logger.h"

#include <cassert>
#include <cstring>

namespace Utilities {

Logger::Logger(bool use_time_span) : log_(LogToConsole) {
    if (use_time_span) {
        time_span_ = CurrentTime;
    }
}

Logger::Logger(const std::string& path) : log_(LogToFile), path_(StringContainer(path)) {
}

Logger::Logger(const std::string& path, bool use_time_span) : log_(LogToFile), path_(StringContainer(path)) {
    if (use_time_span) {
        time_span_ = CurrentTime;
    }
}

void Logger::Log(const std::string& message) const {
    assert(log_ && "Log method must be non null.");
    log_(this, message.data(), kEmpty);
}

void Logger::Error(const std::string& message) const {
    assert(log_ && "Log method must be non null.");
    log_(this, message.data(), kError);
}

void Logger::Info(const std::string& message) const {
    assert(log_ && "Log method must be non null.");
    log_(this, message.data(), kInfo);
}

void Logger::Log(const char* message) const {
    assert(log_ && "Log method must be non null.");
    log_(this, message, kEmpty);
}

void Logger::Error(const char* message) const {
    assert(log_ && "Log method must be non null.");
    log_(this, message, kError);
}

void Logger::Info(const char* message) const {
    assert(log_ && "Log method must be non null.");
    log_(this, message, kInfo);
}

void Logger::LogToConsole(const Logger* logger, const char* message, const char* type) {
    assert(logger && "Logger ptr must be non null.");
    if (strcmp(type, "") != 0) {
        std::cout << "[" << type << "] ";
    }
    std::cout << logger->time_span_() << message << std::endl;
    std::cout.flush();
}

void Logger::LogToFile(const Logger* logger, const char* message, const char* type) {
    assert(logger && "Logger ptr must be non null.");
    assert(logger->path_ && "Path to file must be non null.");
    std::ofstream fout(logger->path_(), std::ios_base::app);
    if (!fout.is_open()) {
        return;
    }
    if (strcmp(type, "") != 0) {
        fout << "[" << type << "] ";
    }
    fout << logger->time_span_() << message << std::endl;
    fout.close();
}

std::string Logger::EmptyString() {
    return "";
}

std::string Logger::CurrentTime() {
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

};  // namespace Utilities
