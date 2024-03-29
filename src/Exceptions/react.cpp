#include "React.h"

#include <iostream>

namespace ThreeDRendererExceptions {

void React() {
    try {
        throw;
    } catch (...) {
        std::cout << "Soon there will be better try-catch\n";
    }
}

}  // namespace ThreeDRendererExceptions
