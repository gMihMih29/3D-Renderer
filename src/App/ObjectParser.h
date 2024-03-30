#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "../Renderer/Primitives/TriangulatedObject.h"

namespace ThreeDRenderer {

class ObjectParser {
public:
    TriangulatedObject ParseObject(const std::string& path) const;
    sf::Color ParseColor(const std::string& input) const;
    TriangulatedObject::Vector3 ParsePosition(const std::string& input) const;

private:
};

}  // namespace ThreeDRenderer
