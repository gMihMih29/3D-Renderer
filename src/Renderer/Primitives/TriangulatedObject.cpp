#include "TriangulatedObject.h"

#include <cassert>
#include <cmath>

namespace ThreeDRenderer {

TriangulatedObject::TriangulatedObject(std::vector<Triangle>&& surfaces, Vector3 pos, sf::Color color)
    : position_(pos(0), pos(1), pos(2), 0), color_(color), surfaces_(surfaces) {
}

void TriangulatedObject::SetPosition(const Vector3& pos) {
    position_(0) = pos(0);
    position_(1) = pos(1);
    position_(2) = pos(2);
    position_(3) = 0;
}

void TriangulatedObject::SetColor(sf::Color color) {
    color_ = Color(color);
}

const TriangulatedObject::Vector4& TriangulatedObject::GetPosition() const {
    return position_;
}

const Color& TriangulatedObject::GetColor() const {
    return color_;
}

TriangulatedObject::Matrix4xN TriangulatedObject::MakeVertexesLocal() const {
    Matrix4xN res;
    res.resize(4, 3 * surfaces_.size());
    for (int i = 0; i < surfaces_.size(); ++i) {
        res.col(3 * i) = surfaces_[i].GetPoint(0);
        res.col(3 * i + 1) = surfaces_[i].GetPoint(1);
        res.col(3 * i + 2) = surfaces_[i].GetPoint(2);
    }
    return res;
}

TriangulatedObject::Matrix4xN TriangulatedObject::MakeVertexesGlobal() const {
    Matrix4xN res;
    res.resize(4, 3 * surfaces_.size());
    for (int i = 0; i < surfaces_.size(); ++i) {
        res.col(3 * i) = surfaces_[i].GetPoint(0) + position_;
        res.col(3 * i + 1) = surfaces_[i].GetPoint(1) + position_;
        res.col(3 * i + 2) = surfaces_[i].GetPoint(2) + position_;
    }
    return res;
}

std::vector<TriangulatedObject::Vector4> TriangulatedObject::MakeNormalVectors() const {
    std::vector<Vector4> res(surfaces_.size());
    for (int i = 0; i < res.size(); ++i) {
        res[i] = surfaces_[i].GetNormalVector();
    }
    return res;
}

TriangulatedObject::Matrix4xN TriangulatedObject::MakeNormalVectorMatrix() const {
    Matrix4xN res;
    res.resize(4, surfaces_.size());
    for (int i = 0; i < surfaces_.size(); ++i) {
        res.col(i) = surfaces_[i].GetNormalVector();
    }
    return res;
}

const std::vector<Triangle>& TriangulatedObject::GetSurfaces() const {
    return surfaces_;
}

bool TriangulatedObject::IsEmpty() const {
    return surfaces_.empty();
}

}  // namespace ThreeDRenderer
