#pragma once

#include "Camera.h"
#include "PixelScreen.h"
#include "World.h"

namespace ThreeDRenderer {

class Renderer {
public:
    static PixelScreen Render(World w, Camera c);
};

}  // namespace ThreeDRenderer
