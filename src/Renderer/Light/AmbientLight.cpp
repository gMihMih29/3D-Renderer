#include "AmbientLight.h"
#include "../Funcs/MathFuncs.h"

namespace ThreeDRenderer {
AmbientLight::AmbientLight(sf::Color color) : color_(color) {
}

const AmbientLight::ColorVector& AmbientLight::GetColor() const {
    return color_;
}
}  // namespace ThreeDRenderer