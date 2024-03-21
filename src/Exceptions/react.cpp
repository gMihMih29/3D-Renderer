#include "react.h"

#include <iostream>

void react() {
    try {
        throw;
    } catch (...) {
        std::cout << "Soon there will be better try-catch";
    }
}
