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
    bool IsSurfaceVisible_(const TriangulatedObject::Matrix4xN& coordinates_of_object, Eigen::Vector4d normal,
                           Eigen::Vector4d camera_direction, int surface_index) const;

    bool SimpleBoundingVolumeTest_(const Eigen::Vector4d point0, const Eigen::Vector4d point1,
                                   const Eigen::Vector4d point2, const Eigen::Vector4d point_to_test) const;

    void CalculateSurfacesColors_(const std::vector<TriangulatedObject>& objects,
                                  const std::vector<TriangulatedObject::Matrix4xN>& normals,
                                  const std::vector<std::vector<bool>>& is_surface_visible,
                                  const AmbientLight& ambient_light,
                                  const std::vector<DirectionalLight>& directional_lights,
                                  const Eigen::Matrix4Xd& directional_lights_vectors,
                                  std::vector<std::vector<Color>>& surfaces_colors);

    sf::Color CalculateColorOfPixel_(int row, int column, int width, int height,
                                     const std::vector<TriangulatedObject::Matrix4xN>& coordinates_of_object,
                                     const AmbientLight& ambient_light,
                                     const std::vector<std::vector<Color>>& surfaces_color,
                                     const std::vector<std::vector<bool>>& is_surface_visible);

    Eigen::MatrixXd z_buffer_;
};

}  // namespace ThreeDRenderer
