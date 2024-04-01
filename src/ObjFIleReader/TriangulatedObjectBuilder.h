#include <Eigen/Dense>
#include <vector>

#include "../Renderer/Primitives/TriangulatedObject.h"
#include "FaceElement.h"

namespace ThreeDRenderer {
class TriangulatedObjectBuilder {
    using Vector3 = Eigen::Vector3d;

public:
    void AddVertex(const Vector3& vertex);
    void AddNormal(const Vector3& normal);
    void AddFaceElement(FaceElement&& face);
    TriangulatedObject Build();

    int GetVertexesQuatity() const;
    int GetNormalsQuatity() const;

private:
    std::vector<Vector3> vertexes_;
    std::vector<Vector3> normals_;
    std::vector<FaceElement> faces_;
};
}  // namespace ThreeDRenderer
