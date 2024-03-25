#include "Renderer.h"

#include <cmath>

#include "../Utilities/Logger.h"

namespace ThreeDRenderer {

PixelScreen Renderer::Render(World w, Camera c) const {
    auto objects = w.GetObjects();
    std::vector<TriangularObject::CoordinatesMatrix> coordinates_of_objects(objects.size());
    std::vector<TriangularObject::NormalVectorMatrix> normals(objects.size());
    for (int i = 0; i < objects.size(); ++i) {
        coordinates_of_objects[i] = objects[i].GetVertexesGlobal();
        normals[i] = objects[i].GetNormalVectorMatrix();
    }
    for (int i = 0; i < objects.size(); ++i) {
        coordinates_of_objects[i] = c.GetTransformToCameraSpaceMatrix() * coordinates_of_objects[i];
        normals[i] = c.GetDirectionMatrix() * normals[i];
    }

    double alpha = c.GetHorizontalFieldOfViewRad();
    double focal_length = 1 / std::tan(alpha / 2);
    double display_ratio = static_cast<double>(c.GetHeight()) / c.GetWidth();
    double beta = 2 * std::atan2(display_ratio, focal_length);
    double near_plane_dist = c.GetNearPlaneDistance();

    double horizontal_left_edge = -near_plane_dist / focal_length;
    double horizontal_rigth_edge = near_plane_dist / focal_length;

    double vertical_top_edge = display_ratio * near_plane_dist / focal_length;
    double vertical_bottom_edge = -display_ratio * near_plane_dist / focal_length;

    Eigen::Matrix4d m_infinite_frustrum{
        {2 * near_plane_dist / (horizontal_rigth_edge - horizontal_left_edge), 0,
         (horizontal_rigth_edge + horizontal_left_edge) / (horizontal_rigth_edge - horizontal_left_edge), 0},
        {0, 2 * near_plane_dist / (vertical_top_edge - vertical_bottom_edge),
         (vertical_top_edge + vertical_bottom_edge) / (vertical_top_edge - vertical_bottom_edge), 0},
        {0, 0, -1, -2 * near_plane_dist},
        {0, 0, -1, 0}
    };
    for (int i = 0; i < objects.size(); ++i) {
        coordinates_of_objects[i] = m_infinite_frustrum * coordinates_of_objects[i];
        Utilities::Logger::kConsoleTimeSpan.Info("Homogenoues coords for object " + std::to_string(i));
        Utilities::Logger::kConsole.Log(coordinates_of_objects[i]);
    }

    PixelScreen ps = PixelScreen(c.GetWidth(), c.GetHeight());
    int k = 0;
    for (int i = 0; i < ps.GetHeigth(); ++i) {
        for (int j = 0; j < ps.GetWidth(); ++j) {
            ps.GetPixel(j, i).color = sf::Color(k % 256, k / 256 % 256, k / 256 / 256 % 256);
            ++k;
        }
    }
    return ps;
}

}  // namespace ThreeDRenderer
