#include <string>
#include <string_view>
#include <vector>

#include "../Renderer/TriangularObject.h"

namespace ThreeDRenderer {

class ObjectParser {
public:
    TriangularObject Read(const std::string& path) const;

private:
    std::vector<std::string_view> Split_(std::string_view str, char separator) const;
};

}  // namespace ThreeDRenderer
