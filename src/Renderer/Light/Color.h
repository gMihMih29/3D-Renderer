#pragma once

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>

namespace ThreeDRenderer {
class Color {
    using Vector3 = Eigen::Vector3d;

public:
    Color() = default;
    Color(sf::Color color);
    Color(Vector3 color);

    const Vector3& GetColorVector() const;
    sf::Color ConvertToHexColor() const;

    Color& operator+=(const Color& other) {
        color_vector_(0) += other.color_vector_(0);
        color_vector_(1) += other.color_vector_(1);
        color_vector_(2) += other.color_vector_(2);
        return *this;
    }

    Color& operator*=(const Color& other) {
        color_vector_(0) *= other.color_vector_(0);
        color_vector_(1) *= other.color_vector_(1);
        color_vector_(2) *= other.color_vector_(2);
        return *this;
    }

    Color& operator*=(double coef) {
        color_vector_(0) *= coef;
        color_vector_(1) *= coef;
        color_vector_(2) *= coef;
        return *this;
    }

    friend Color operator+(const Color& lhv, const Color& rhv) {
        Color tmp(lhv);
        return tmp += rhv;
    }

    friend Color operator*(const Color& lhv, const Color& rhv) {
        Color tmp(lhv);
        return tmp *= rhv;
    }

    friend Color operator*(double coef, const Color& color) {
        Color tmp(color);
        return tmp *= coef;
    }

private:
    Vector3 color_vector_;
};
}  // namespace ThreeDRenderer