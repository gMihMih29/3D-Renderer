#pragma once

#include "../Observer/Observer.h"
#include "../View/PixelScreen.h"

namespace ThreeDRenderer {

class Kernel {
public:
    Kernel();
    PixelScreen GetScene(int, int);
private:
    
};

}  // namespace ThreeDRenderer
