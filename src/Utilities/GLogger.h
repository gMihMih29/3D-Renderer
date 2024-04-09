#pragma once

#include "LoggerInstances.h"

namespace Utilities {

template <class LoggerInstance>
class GLogger : public LoggerInstance {
public:
    using LoggerInstance::LoggerInstance;

    friend const GLogger& operator<<(const GLogger& logger, const std::string& message) {
        LoggerInstance::Instance() << message;
        return logger;
    }

    void Log(const std::string& msg) const {
        LoggerInstance::Instance().Log(msg);
    }

    void Error(const std::string& msg) const {
        LoggerInstance::Instance().Error(msg);
    }

    void Info(const std::string& msg) const {
        LoggerInstance::Instance().Info(msg);
    }
};

}  // namespace Utilities
