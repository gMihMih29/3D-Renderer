#pragma once

#include <chrono>

namespace Utilities {

class Timer {
public:
    Timer();

    int64_t GetMilliseconds() const;
    void Reset();

private:
    std::chrono::_V2::system_clock::time_point start_;
};

}  // namespace Utilities
