#include "Kernel.h"

#include <functional>

namespace ThreeDRenderer {

Kernel::Kernel() : observable_() {
}

void Kernel::SubscribeToCameraUpdates(CObserver<PixelScreen>* observer) {
    observable_.Subscribe(observer);
}

}
