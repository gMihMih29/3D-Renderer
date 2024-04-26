#pragma once

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>

#include "Color.h"

namespace ThreeDRenderer {

class DirectionalLight {
    using Vector3 = Eigen::Vector3d;
    using Vector4 = Eigen::Vector4d;

public:
    DirectionalLight(Vector3 dir, sf::Color color);

    const Vector4& GetDirection() const;
    const Color& GetColor() const;

private:
    Vector4 direction_;
    Color color_;
};

}  // namespace ThreeDRenderer
