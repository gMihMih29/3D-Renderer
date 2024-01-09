#include "Kernel.h"

#include <functional>

Kernel::Kernel() : CObservable<PixelScreen>([this]() { return GetScreen(); }) {
}

const PixelScreen& Kernel::GetScreen() {
    return PixelScreen();
}