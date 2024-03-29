#include "DirectionalLight.h"
#include "../Funcs/MathFuncs.h"

#include <cassert>

namespace ThreeDRenderer {
DirectionalLight::DirectionalLight(Vector4 dir, sf::Color color) : direction_(dir), color_(color) {
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