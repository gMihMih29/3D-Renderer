#include "../Renderer/Primitives/TriangulatedObject.h"
#include "../Utilities/Logger.h"
#include "Response.h"

namespace ThreeDRenderer {

class ObjFileReader {
    using Logger = Utilities::Logger;
    using Response = Response<TriangulatedObject>;

public:
    static Response ReadFile(const std::string& path_to_file);
};

}  // namespace ThreeDRenderer
