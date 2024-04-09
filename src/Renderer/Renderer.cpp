#include "Renderer.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include "../Utilities/GLogger.h"

namespace ThreeDRenderer {

Renderer::Renderer(int screen_height, int screen_width) : z_buffer_(screen_height, screen_width) {
}

void Renderer::Render(const World& w, const Camera& c, PixelScreen& buffer) {
    const double eps = 1e-9;
    int width = buffer.GetWidth();
    int height = buffer.GetHeight();

    double alpha = c.GetHorizontalFieldOfViewRad();
    double focal_length = 1 / std::tan(alpha / 2);
    double display_ratio = static_cast<double>(height) / width;
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
        {0, 0, -1, 0}};

    auto directional_lights = w.GetDirectionalLight();
    auto ambient_light = w.GetAmbientLight();

    auto objects = w.GetObjects();
    std::vector<TriangulatedObject::Matrix4xN> coordinates_of_objects(objects.size());
    std::vector<TriangulatedObject::Matrix4xN> normals(objects.size());
    std::vector<std::vector<bool>> is_surface_visible(objects.size());
    Eigen::Matrix4Xd directional_lights_vectors;
    directional_lights_vectors.resize(4, directional_lights.size());
    std::vector<std::vector<Color>> surfaces_colors_(objects.size());

    for (int i = 0; i < directional_lights.size(); ++i) {
        directional_lights_vectors.col(i) = directional_lights[i].GetDirection();
    }
    directional_lights_vectors = c.GetDirectionMatrix() * directional_lights_vectors;

    for (int i = 0; i < objects.size(); ++i) {
        coordinates_of_objects[i] =
            m_infinite_frustrum * c.GetTransformToCameraSpaceMatrix() * objects[i].MakeVertexesGlobal();
        normals[i] = c.GetDirectionMatrix() * objects[i].MakeNormalVectorMatrix();
        is_surface_visible[i].resize(normals[i].cols(), true);
        surfaces_colors_[i].resize(objects[i].GetSurfaces().size());
    }

    for (int i = 0; i < objects.size(); ++i) {
        for (int j = 0; j < coordinates_of_objects[i].cols(); ++j) {
            coordinates_of_objects[i].col(j) /= coordinates_of_objects[i].col(j)(3);
        }
    }

    for (int i = 0; i < objects.size(); ++i) {
        for (int surf_ind = 0; surf_ind < is_surface_visible[i].size(); ++surf_ind) {
            is_surface_visible[i][surf_ind] = IsSurfaceVisible_(coordinates_of_objects[i], normals[i].col(surf_ind),
                                                                Eigen::Vector4d(0, 0, -1, 0), surf_ind);
        }
    }

    CalculateSurfacesColors_(objects, normals, is_surface_visible, ambient_light, directional_lights,
                             directional_lights_vectors, surfaces_colors_);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            buffer.Pixel(i, j).color = CalculateColorOfPixel_(i, j, width, height, coordinates_of_objects,
                                                              ambient_light, surfaces_colors_, is_surface_visible);
        }
    }
}

bool Renderer::IsSurfaceVisible_(const TriangulatedObject::Matrix4xN& coordinates_of_object, Eigen::Vector4d normal,
                                 Eigen::Vector4d camera_direction, int surface_index) const {
    const double eps = 1e-2;
    if (normal.dot(camera_direction) > 0.8) {
        return false;
    }
    auto p0 = coordinates_of_object.col(3 * surface_index);
    auto p1 = coordinates_of_object.col(3 * surface_index + 1);
    auto p2 = coordinates_of_object.col(3 * surface_index + 2);
    if (1 < p0(2) || 1 < p1(2) || 1 < p2(2) || p0(2) < -1 || p1(2) < -1 || p2(2) < -1) {
        return false;
    }
    int cnt = 0;
    if (-1 <= p0(0) && p0(0) <= 1 && -1 <= p0(1) && p0(1) <= 1 && -1 <= p0(2) && p0(2) <= 1) {
        ++cnt;
    }
    if (-1 <= p1(0) && p1(0) <= 1 && -1 <= p1(1) && p1(1) <= 1 && -1 <= p1(2) && p1(2) <= 1) {
        ++cnt;
    }
    if (-1 <= p2(0) && p2(0) <= 1 && -1 <= p2(1) && p2(1) <= 1 && -1 <= p2(2) && p2(2) <= 1) {
        ++cnt;
    }
    return cnt != 0;
}

bool Renderer::SimpleBoundingVolumeTest_(const Eigen::Vector4d point0, const Eigen::Vector4d point1,
                                         const Eigen::Vector4d point2, const Eigen::Vector4d point_to_test) const {
    double max_y = std::max(point0.y(), point1.y());
    double max_x = std::max(point0.x(), point1.x());
    double min_y = std::min(point0.y(), point1.y());
    double min_x = std::min(point0.x(), point1.x());
    max_y = std::max(max_y, point2.y());
    max_x = std::max(max_x, point2.x());
    min_y = std::min(min_y, point2.y());
    min_x = std::min(min_x, point2.x());
    double x = point_to_test.x();
    double y = point_to_test.y();
    return min_x <= x && x <= max_x && min_y <= y && y <= max_y;
}

void Renderer::CalculateSurfacesColors_(const std::vector<TriangulatedObject>& objects,
                                        const std::vector<TriangulatedObject::Matrix4xN>& normals,
                                        const std::vector<std::vector<bool>>& is_surface_visible,
                                        const AmbientLight& ambient_light,
                                        const std::vector<DirectionalLight>& directional_lights,
                                        const Eigen::Matrix4Xd& directional_lights_vectors,
                                        std::vector<std::vector<Color>>& surfaces_colors) {
    const double eps = 1e-9;
    for (int i = 0; i < objects.size(); ++i) {
        for (int surf_ind = 0; surf_ind < objects[i].GetSurfaces().size(); ++surf_ind) {
            if (!is_surface_visible[i][surf_ind]) {
                continue;
            }
            Color object_color = objects[i].GetColor();
            Color result_color(sf::Color(0, 0, 0));
            result_color += ambient_light.GetColor() * object_color;
            for (int dir_light_ind = 0; dir_light_ind < directional_lights_vectors.cols(); ++dir_light_ind) {
                double product = directional_lights_vectors.col(dir_light_ind).dot(normals[i].col(surf_ind));
                product = -product;
                if (product <= eps) {
                    continue;
                }
                result_color += product * directional_lights[dir_light_ind].GetColor() * object_color;
            }
            surfaces_colors[i][surf_ind] = result_color;
        }
    }
}

sf::Color Renderer::CalculateColorOfPixel_(int row, int column, int width, int height,
                                           const std::vector<TriangulatedObject::Matrix4xN>& coordinates_of_objects,
                                           const AmbientLight& ambient_light,
                                           const std::vector<std::vector<Color>>& surfaces_color,
                                           const std::vector<std::vector<bool>>& is_surface_visible) {

    const double eps = 1e-9;
    Color result_color = ambient_light.GetColor();
    z_buffer_(row, column) = HUGE_VAL;
    double ray_x = 2 * static_cast<double>(column) / width - 1;
    double ray_y = -2 * static_cast<double>(row) / height + 1;
    Eigen::Vector4d ray_start(ray_x, ray_y, -1, 1);
    Eigen::Vector4d ray_direction(0, 0, 1, 0);

    for (int i = 0; i < coordinates_of_objects.size(); ++i) {
        for (int surf_ind = 0; surf_ind < is_surface_visible[i].size(); ++surf_ind) {
            if (!is_surface_visible[i][surf_ind]) {
                continue;
            }
            auto p0 = coordinates_of_objects[i].col(3 * surf_ind);
            auto p1 = coordinates_of_objects[i].col(3 * surf_ind + 1);
            auto p2 = coordinates_of_objects[i].col(3 * surf_ind + 2);
            if (!SimpleBoundingVolumeTest_(p0, p1, p2, ray_start)) {
                continue;
            }
            Eigen::Vector4d norm = (p1 - p0).cross3(p2 - p0);
            Eigen::Vector4d l(norm(0), norm(1), norm(2), -norm.dot(p0));
            if (std::abs(l.dot(ray_direction)) < eps) {
                continue;
            }
            double t = -l.dot(ray_start) / l.dot(ray_direction);

            auto P = ray_start + t * ray_direction;

            if (P(2) > z_buffer_(row, column)) {
                continue;
            }

            auto R = P - p0;
            auto Q_1 = p1 - p0;
            auto Q_2 = p2 - p0;

            Eigen::Matrix2d coef{{Q_1.dot(Q_1), Q_1.dot(Q_2)}, {Q_1.dot(Q_2), Q_2.dot(Q_2)}};
            Eigen::Vector2d b(R.dot(Q_1), R.dot(Q_2));
            Eigen::Vector2d weights = coef.inverse() * b;
            if (weights(0) < 0 || weights(1) < 0 || 1 - weights(0) - weights(1) < 0) {
                continue;
            }
            z_buffer_(row, column) = P(2);
            result_color = surfaces_color[i][surf_ind];
        }
    }
    return result_color.ConvertToHexColor();
}

}  // namespace ThreeDRenderer
