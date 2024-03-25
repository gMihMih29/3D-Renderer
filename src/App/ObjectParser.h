#include <string>
#include <string_view>
#include <vector>

#include "../Renderer/TriangularObject.h"

namespace ThreeDRenderer {

class ObjectParser {
public:
    TriangularObject ParseObject(const std::string& path) const;
    sf::Color ParseColor(const std::string& input) const;
    TriangularObject::CoordinatesVector ParsePosition(const std::string& input) const;

private:
};

}  // namespace ThreeDRenderer
