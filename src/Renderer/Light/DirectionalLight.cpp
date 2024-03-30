#include "DirectionalLight.h"

#include <cassert>

#include "../Funcs/MathFuncs.h"

namespace ThreeDRenderer {
DirectionalLight::DirectionalLight(Vector3 dir, sf::Color color)
    : direction_(dir(0), dir(1), dir(2), 0), color_(color) {
    assert(!direction_.isZero() && "Direction of light must be non zero!");
    direction_.normalize();
}

const DirectionalLight::Vector4& DirectionalLight::GetDirection() const {
    return direction_;
}

const Color& DirectionalLight::GetColor() const {
    return color_;
}

}  // namespace ThreeDRenderer