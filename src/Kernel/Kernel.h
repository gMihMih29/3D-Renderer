#pragma once

#include "../Observer/Observer.h"
#include "../Renderer/PixelScreen.h"

namespace ThreeDRenderer {

class Kernel {
public:
    Kernel();
    PixelScreen GetScene(int, int);
private:
    
};

}  // namespace ThreeDRenderer
