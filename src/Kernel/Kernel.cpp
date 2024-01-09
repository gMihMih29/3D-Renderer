#include "Kernel.h"

#include <functional>

namespace ThreeDRenderer {

Kernel::Kernel() : CObservable<PixelScreen>([this]() { return GetScreen(); }) {
}

const PixelScreen& Kernel::GetScreen() {
    return PixelScreen();
}

}
