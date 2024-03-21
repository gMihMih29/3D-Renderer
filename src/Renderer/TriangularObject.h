#pragma once

#include <Eigen/Dense>
#include <vector>

namespace ThreeDRenderer {
class TriangularObject {
    using CoordinatesVector = Eigen::Vector3d;
    using CoordinatesVector4D = Eigen::Vector4d;
    using ConnectionVector = Eigen::Vector3i;
    using ColorVector = Eigen::Vector3i;
    using CoordinatesMatrix = Eigen::MatrixXd;

public:
    TriangularObject() = delete;
    TriangularObject(CoordinatesVector pos, ColorVector color, const std::vector<CoordinatesVector>& vertexes,
                     const std::vector<ConnectionVector>& connections);

    void SetPosition(const CoordinatesVector& pos);

    CoordinatesVector GetPosition() const;
    const ColorVector& GetColor() const;
    const CoordinatesMatrix& GetVertexesLocal() const;
    CoordinatesMatrix GetVertexesGlobal() const;
    const std::vector<ConnectionVector>& GetConnections() const;

private:
    CoordinatesVector4D position_ = CoordinatesVector4D(0, 0, 0, 0);
    ColorVector color_ = ColorVector(0, 0, 0);
    CoordinatesMatrix vertexes_;
    std::vector<ConnectionVector> connections_;
};
}  // namespace ThreeDRenderer
