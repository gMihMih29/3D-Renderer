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
    static Logger console;
    static Utilities::Logger logger;

    Logger();
    Logger(bool useTimeStamp);
    Logger(std::string path, bool useTimeStamp = false);
    ~Logger();

    void Log(const char* message);
    template <class T>
    void Log(const T& message);

    void Error(const char* message);
    template <class T>
    void Error(const T& message);

    void Info(const char* message);
    template <class T>
    void Info(const T& message);

private:
    void LogWithType_(const char* message, const std::string& type);
    template <class T>
    void LogWithType_(const T& message, const std::string& type);

    static std::string GetCurrentTimeLog_();
    static std::string GetCurrentDay_();

    bool writeToFile_;
    bool useTimeStamp_;
    std::string path_;
    std::ofstream fout_;
};

template <class T>
void Logger::Log(const T& message) {
    LogWithType_(message, kEMPTY);
}

template <class T>
void Logger::Error(const T& message) {
    LogWithType_(message, kERROR);
}

template <class T>
void Logger::Info(const T& message) {
    LogWithType_(message, kINFO);
}

template <class T>
void Logger::LogWithType_(const T& message, const std::string& type) {
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
