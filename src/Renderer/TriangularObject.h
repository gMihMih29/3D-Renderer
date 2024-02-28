#include <Eigen/Dense>
#include <vector>

namespace ThreeDRenderer {
class TriangularObject {
    using CoordinatesVector = Eigen::Vector3d;
    using ConnectionVector = Eigen::Vector3i;
    using ColorVector = Eigen::Vector3i;
    using CoordinatesMatrix = Eigen::MatrixXd;

public:
    TriangularObject();
    TriangularObject(CoordinatesVector pos, ColorVector color, const std::vector<CoordinatesVector>& vertexes,
                     const std::vector<ConnectionVector>& connections);

    void SetPosition(const CoordinatesVector& pos);
    void AddVertex(const CoordinatesVector& pos);
    void AddConnection(const ConnectionVector& connection);

    const CoordinatesVector& GetPosition() const;
    const ColorVector& GetColor() const;
    const CoordinatesMatrix& GetVertexesLocal() const;
    CoordinatesMatrix GetVertexesGlobal() const;
    const std::vector<ConnectionVector>& GetConnections() const;

private:
    CoordinatesVector position_ = CoordinatesVector(0, 0, 0);
    ColorVector color_ = ColorVector(0, 0, 0);
    CoordinatesMatrix vertexes_;
    std::vector<ConnectionVector> connections_;
};
}  // namespace ThreeDRenderer
