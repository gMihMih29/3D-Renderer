#pragma once

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>

#include "Color.h"

namespace ThreeDRenderer {

class AmbientLight {
    using ColorVector = Color;

public:
    AmbientLight() = default;
    AmbientLight(sf::Color color);

    const ColorVector& GetColor() const;

private:
    ColorVector color_;
};

}  // namespace ThreeDRenderer
