#include <Eigen/Dense>

#include "FaceElement.h"
#include "../Utilities/Response.h"

namespace ThreeDRenderer {

class ObjParser {
    using Vector3 = Eigen::Vector3d;
    using ResponseVector3 = Utilities::Response<Eigen::Vector3d>;
    using ResponseFaceElem = Utilities::Response<FaceElement>;

public:
    static ResponseVector3 ParseVector(const std::string& input);
    static ResponseFaceElem ParseFaceElement(const std::string& input, int vertex_count, int normals_count);

private:
    static bool IsNumber_(std::string_view str);
};

}  // namespace ThreeDRenderer
