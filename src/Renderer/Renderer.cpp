#include "Renderer.h"

#include <cassert>
#include <cmath>

#include "../Utilities/Logger.h"

namespace ThreeDRenderer {

void Renderer::Render(const World& w, const Camera& c, PixelScreen& buffer) const {
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

    for (int i = 0; i < directional_lights.size(); ++i) {
        directional_lights_vectors.col(i) = directional_lights[i].GetDirection();
    }
    directional_lights_vectors = c.GetDirectionMatrix() * directional_lights_vectors;
    for (int i = 0; i < objects.size(); ++i) {
        coordinates_of_objects[i] = objects[i].MakeVertexesGlobal();
        normals[i] = objects[i].MakeNormalVectorMatrix();
        is_surface_visible[i].resize(normals[i].cols(), true);
    }
    for (int i = 0; i < objects.size(); ++i) {
        coordinates_of_objects[i] =
            m_infinite_frustrum * c.GetTransformToCameraSpaceMatrix() * coordinates_of_objects[i];
        normals[i] = c.GetDirectionMatrix() * normals[i];
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

    Eigen::MatrixXd z_buffer(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            z_buffer(i, j) = HUGE_VAL;
            buffer.Pixel(i, j).color = ambient_light.GetColor().ConvertToHexColor();
            double ray_x = 2 * static_cast<double>(j) / width - 1;
            double ray_y = -2 * static_cast<double>(i) / height + 1;
            Eigen::Vector4d ray_start(ray_x, ray_y, -1, 1);
            Eigen::Vector4d ray_direction(0, 0, 1, 0);

            for (int k = 0; k < objects.size(); ++k) {
                for (int surf_ind = 0; surf_ind < is_surface_visible[k].size(); ++surf_ind) {
                    if (!is_surface_visible[k][surf_ind]) {
                        continue;
                    }
                    auto p0 = coordinates_of_objects[k].col(3 * surf_ind);
                    auto p1 = coordinates_of_objects[k].col(3 * surf_ind + 1);
                    auto p2 = coordinates_of_objects[k].col(3 * surf_ind + 2);
                    Eigen::Vector4d norm = (p1 - p0).cross3(p2 - p0);
                    Eigen::Vector4d l(norm(0), norm(1), norm(2), -norm.dot(p0));
                    if (std::abs(l.dot(ray_direction)) < eps) {
                        continue;
                    }
                    double t = -l.dot(ray_start) / l.dot(ray_direction);

                    auto P = ray_start + t * ray_direction;

                    if (P(2) > z_buffer(i, j)) {
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
                    Color object_color = objects[k].GetColor();
                    Color result_color(sf::Color(0, 0, 0));
                    result_color += ambient_light.GetColor() * object_color;
                    for (int dir_light_ind = 0; dir_light_ind < directional_lights_vectors.cols(); ++dir_light_ind) {
                        double product = directional_lights_vectors.col(dir_light_ind).dot(normals[k].col(surf_ind));
                        product = -product;
                        if (product <= eps) {
                            continue;
                        }
                        result_color += product * directional_lights[dir_light_ind].GetColor() * object_color;
                    }
                    z_buffer(i, j) = P(2);
                    buffer.Pixel(i, j).color = result_color.ConvertToHexColor();
                }
            }
        }
    }
}

bool Renderer::IsSurfaceVisible_(const TriangulatedObject::Matrix4xN& coordinates_of_object, Eigen::Vector4d normal,
                                 Eigen::Vector4d camera_direction, int surface_index) const {
    const double eps = 1e-9;
    if (std::abs(normal.dot(camera_direction) - 1) < eps) {
        return false;
    }
    auto p0 = coordinates_of_object.col(3 * surface_index);
    auto p1 = coordinates_of_object.col(3 * surface_index + 1);
    auto p2 = coordinates_of_object.col(3 * surface_index + 2);
    if (1 < p0(2) || 1 < p1(2) || 1 < p2(2)) {
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

}  // namespace ThreeDRenderer
