#include <Eigen/Dense>

#include "FaceElement.h"

namespace ThreeDRenderer {

class ObjParser {
    using Vector3 = Eigen::Vector3d;

public:
    static Vector3 ParseVector(const std::string& input);
    static FaceElement ParseFaceElement(const std::string& input, int vertex_count, int normals_count);

private:
    static bool IsNumber_(std::string_view str);
};

}  // namespace ThreeDRenderer
