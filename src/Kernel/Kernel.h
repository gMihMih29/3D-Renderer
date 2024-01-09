#pragma once

#include "../Observer/Observer.h"
#include "../View/PixelScreen.h"

namespace ThreeDRenderer {
    
class Kernel : public CObservable<PixelScreen> {
public:
    Kernel();
    const PixelScreen& GetScreen();
};

}  // namespace ThreeDRenderer
