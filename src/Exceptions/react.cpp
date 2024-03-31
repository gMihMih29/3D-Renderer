#include "React.h"

#include "../Utilities/Logger.h"

#include <iostream>

namespace ThreeDRendererExceptions {

void React() {
    try {
        throw;
    } catch (...) {
        Utilities::Logger::kConsoleTimeSpan.Error("Program had do stop due to reasons unrelated to invalid user input.");
    }
}

}  // namespace ThreeDRendererExceptions
