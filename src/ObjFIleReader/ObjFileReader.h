#include "../Renderer/Primitives/TriangulatedObject.h"
#include "../Utilities/Logger.h"

namespace ThreeDRenderer {

class ObjFileReader {
    using Logger = Utilities::Logger;

public:
    static TriangulatedObject ReadFile(const std::string& path_to_file);
};

}  // namespace ThreeDRenderer
