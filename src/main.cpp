#include "App/App.h"
#include "Exceptions/React.h"

int main() {
    try {
        ThreeDRenderer::App app;
        app.Run();

    } catch (...) {
        ThreeDRendererExceptions::React();
    }
    return 0;
}
