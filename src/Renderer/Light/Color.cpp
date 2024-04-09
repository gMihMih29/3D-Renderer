#include "Color.h"

#include <algorithm>
#include <Eigen/Dense>
#include <SFML/Graphics.hpp>

namespace ThreeDRenderer {

Color::Color(sf::Color color) {
    double red = static_cast<double>(color.r) / 255;
    double green = static_cast<double>(color.g) / 255;
    double blue = static_cast<double>(color.b) / 255;
    color_vector_(0) = red;
    color_vector_(1) = green;
    color_vector_(2) = blue;
}

Color::Color(Vector3 color) : color_vector_(color) {
    Normalize_();
}

const Color::Vector3& Color::GetColorVector() const {
    return color_vector_;
}

sf::Color Color::ConvertToHexColor() const {
    uint8_t red = static_cast<uint8_t>(color_vector_(0) * 255);
    uint8_t green = static_cast<uint8_t>(color_vector_(1) * 255);
    uint8_t blue = static_cast<uint8_t>(color_vector_(2) * 255);
    return sf::Color(red, green, blue);
}

void Color::Normalize_() {
    color_vector_(0) = std::min(1., color_vector_(0));
    color_vector_(1) = std::min(1., color_vector_(1));
    color_vector_(2) = std::min(1., color_vector_(2));
}

}  // namespace ThreeDRenderer
