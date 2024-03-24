#include "Triangle.h"

#include <cassert>

namespace ThreeDRenderer {
Triangle::Triangle(PositionVector p1, PositionVector p2, PositionVector p3, NormalVector direction) {
    point1_ << p1(0), p1(1), p1(2), 1;
    point2_ << p2(0), p2(1), p2(2), 1;
    point3_ << p3(0), p3(1), p3(2), 1;
    normal_ = direction / direction.dot(direction);
}

const Triangle::PositionVector4D& Triangle::GetPoint(int index) const {
    assert(0 <= index && index < 3 && "Index of point must be in [0;3).");
    if (index == 0) {
        return point1_;
    }
    if (index == 1) {
        return point2_;
    }
    return point3_;
}

Triangle::PositionMatrix Triangle::GetPositionMatrix() const {
    PositionMatrix res;
    res.col(0) = point1_;
    res.col(1) = point2_;
    res.col(2) = point3_;
    return res;
}

const Triangle::NormalVector& Triangle::GetNormalVector() const {
    return normal_;
}

}  // namespace ThreeDRenderer
