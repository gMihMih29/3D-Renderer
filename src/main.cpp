#include "App/App.h"

#include <iostream>

void react() {
    try {
        throw;
    } catch (...) {
        std::cout << "Soon there will be better try-catch";
    }
}

int main() {
    try {
        ThreeDRenderer::App app;
        app.Run();

    } catch (...) {
        react();
    }
    return 0;
}
