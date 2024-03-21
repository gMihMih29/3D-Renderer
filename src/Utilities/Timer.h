#include <chrono>

namespace Utilities {
class Timer {
private:
    std::chrono::_V2::system_clock::time_point start_;

public:
    Timer();

    long long GetTime();

    void Reset();

    ~Timer() = default;
};
}  // namespace Utilities
