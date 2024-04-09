#include "React.h"

#include "../Utilities/GLogger.h"

#include <iostream>

namespace ThreeDRendererExceptions {

void React() {
    static Utilities::GLogger<Utilities::ConsoleTimeSpanLoggerInstance> logger;
    try {
        throw;
    } catch (...) {
        logger.Error("Program had do stop due to reasons unrelated to invalid user input.");
    }
}

}  // namespace ThreeDRendererExceptions
