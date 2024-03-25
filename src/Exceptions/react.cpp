#include "react.h"

#include <iostream>
namespace ThreeDRendererExceptions {

void react() {
    try {
        throw;
    } catch (...) {
        std::cout << "Soon there will be better try-catch";
    }
}

}