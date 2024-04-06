#include <Eigen/Dense>

#include "FaceElement.h"
#include "Response.h"

namespace ThreeDRenderer {

class ObjParser {
    using Vector3 = Eigen::Vector3d;

public:
    static Response<Vector3> ParseVector(const std::string& input);
    static Response<FaceElement> ParseFaceElement(const std::string& input, int vertex_count, int normals_count);

private:
    static bool IsNumber_(std::string_view str);
};

}  // namespace ThreeDRenderer
