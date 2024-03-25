#pragma once

#include "PixelScreen.h"
#include "World/Camera.h"
#include "World/World.h"

namespace ThreeDRenderer {

class Renderer {
public:
    PixelScreen Render(World w, Camera c) const;
};

}  // namespace ThreeDRenderer
