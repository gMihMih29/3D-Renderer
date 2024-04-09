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
    static const Logger& Instance() {
        static Logger logger(true);
        return logger;
    }
};

class FileLoggerInstance {
public:
    FileLoggerInstance(const std::string& path) : logger_(path, true) {
    }

protected:
    const Logger& Instance() const {
        return logger_;
    }
private:
    Logger logger_;
};

}  // namespace Utilities
