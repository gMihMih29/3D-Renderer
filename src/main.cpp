#include "App/App.h"
#include "Exceptions/react.h"

int main() {
    try {
        ThreeDRenderer::App app;
        app.Run();

    } catch (...) {
        react();
    }
    return 0;
}
