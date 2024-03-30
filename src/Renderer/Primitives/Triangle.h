#pragma once

#include <Eigen/Dense>

namespace ThreeDRenderer {

class Triangle {
    using Vector3 = Eigen::Vector3d;
    using Vector4 = Eigen::Vector4d;
    using Matrix4x3 = Eigen::Matrix<double, 4, 3>;

public:
    Triangle(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 direction);

    const Vector4& GetPoint(int index) const;
    const Vector4& GetNormalVector() const;
    
    Matrix4x3 MakePositionMatrix() const;

private:
    Vector4 point0_;
    Vector4 point1_;
    Vector4 point2_;
    Vector4 normal_;
};

}  // namespace ThreeDRenderer
