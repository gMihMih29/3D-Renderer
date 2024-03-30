#pragma once

#include "PixelScreen.h"
#include "World/Camera.h"
#include "World/World.h"

namespace ThreeDRenderer {

class Renderer {
public:
    void Render(const World& w, const Camera& c, PixelScreen& buffer) const;

private:
    bool IsSurfaceVisible_(const TriangularObject::Matrix4xN& coordinates_of_object,
                               Eigen::Vector4d normal, Eigen::Vector4d camera_direction, int surface_index) const;
};

}  // namespace ThreeDRenderer
