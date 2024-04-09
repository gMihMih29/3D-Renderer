#pragma once

#include "Logger.h"

namespace Utilities {

class ConsoleLoggerInstance {
protected:
    static Logger& Instance() {
        static Logger logger;
        return logger;
    }
};

class ConsoleTimeSpanLoggerInstance {
protected:
    static Logger& Instance() {
        static Logger logger(true);
        return logger;
    }
};

class FileLoggerInstance {
public:
    FileLoggerInstance(const std::string& path) {
        Instance(path);
    }

protected:
    static Logger& Instance(const std::string& path = "") {
        static Logger logger(path, true);
        return logger;
    }
};

}  // namespace Utilities
