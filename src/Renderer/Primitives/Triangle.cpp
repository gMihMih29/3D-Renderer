#include "Triangle.h"

#include <cassert>

namespace ThreeDRenderer {

Triangle::Triangle(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 direction)
    : point0_(p0(0), p0(1), p0(2), 1),
      point1_(p1(0), p1(1), p1(2), 1),
      point2_(p2(0), p2(1), p2(2), 1),
      normal_(direction(0), direction(1), direction(2), 0) {
    assert(!normal_.isZero() && "Normal vector must be non zero");
    normal_.normalize();
}

const Triangle::Vector4& Triangle::GetPoint(int index) const {
    assert(0 <= index && index < 3 && "Index of point must be in [0;3).");
    if (index == 0) {
        return point0_;
    }
    if (index == 1) {
        return point1_;
    }
    return point2_;
}

Triangle::Matrix4x3 Triangle::MakePositionMatrix() const {
    Matrix4x3 res;
    res.col(0) = point0_;
    res.col(1) = point1_;
    res.col(2) = point2_;
    return res;
}

const Triangle::Vector4& Triangle::GetNormalVector() const {
    return normal_;
}

}  // namespace ThreeDRenderer
