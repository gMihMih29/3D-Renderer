#include "../Renderer/Primitives/TriangulatedObject.h"
#include "../Utilities/Logger.h"
#include "../Utilities/Response.h"

namespace ThreeDRenderer {

class ObjFileReader {
    using Logger = Utilities::Logger;
    using Response = Utilities::Response<TriangulatedObject>;

public:
    static Response ReadFile(const std::string& path_to_file);
};

}  // namespace ThreeDRenderer
