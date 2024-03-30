#pragma once

#include "PixelScreen.h"
#include "World/Camera.h"
#include "World/World.h"

namespace ThreeDRenderer {

class Renderer {
public:
    Renderer(int screen_height, int screen_width);

    void Render(const World& w, const Camera& c, PixelScreen& buffer);

private:
    bool IsSurfaceVisible_(const TriangulatedObject::Matrix4xN& coordinates_of_object,
                               Eigen::Vector4d normal, Eigen::Vector4d camera_direction, int surface_index) const;

    Eigen::MatrixXd z_buffer_;
};

}  // namespace ThreeDRenderer
