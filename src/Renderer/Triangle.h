#pragma once

#include <Eigen/Dense>

namespace ThreeDRenderer {
class Triangle {
    using PositionVector = Eigen::Vector3d;
    using PositionVector4D = Eigen::Vector4d;
    using NormalVector = Eigen::Vector3d;
    using PositionMatrix = Eigen::Matrix<double, 4, 3>;

public:
    Triangle(PositionVector p1, PositionVector p2, PositionVector p3, NormalVector direction);

    const PositionVector4D& GetPoint(int index) const;
    PositionMatrix GetPositionMatrix() const;
    const NormalVector& GetNormalVector() const;

private:
    PositionVector4D point1_;
    PositionVector4D point2_;
    PositionVector4D point3_;
    NormalVector normal_;
};
}  // namespace ThreeDRenderer
