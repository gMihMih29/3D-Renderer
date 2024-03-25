#include "Timer.h"

namespace Utilities {
Timer::Timer() {
    Reset();
}

int64_t Timer::GetTime() {
    auto elapsed = std::chrono::high_resolution_clock::now() - start_;
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
}

void Timer::Reset() {
    start_ = std::chrono::high_resolution_clock::now();
}
}  // namespace Utilities
