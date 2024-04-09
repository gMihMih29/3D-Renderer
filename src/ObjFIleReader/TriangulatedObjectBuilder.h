#include <Eigen/Dense>
#include <vector>

#include "../Renderer/Primitives/TriangulatedObject.h"
#include "FaceElement.h"
#include "../Utilities/Response.h"

namespace ThreeDRenderer {
class TriangulatedObjectBuilder {
    using Vector3 = Eigen::Vector3d;
    using Response = Utilities::Response<TriangulatedObject>;

public:
    void AddVertex(Vector3&& vertex);
    void AddNormal(Vector3&& normal);
    void AddFaceElement(FaceElement&& face);
    Response Build() const;

    int GetVertexesQuatity() const;
    int GetNormalsQuatity() const;

private:
    Vector3 FindNormalForFaceElemBruteForce_(int index_of_face_elem) const;
    Vector3 FindNormalForPoint_(int index) const;

    std::vector<Vector3> vertexes_;
    std::vector<Vector3> normals_;
    std::vector<FaceElement> faces_;
};
}  // namespace ThreeDRenderer
