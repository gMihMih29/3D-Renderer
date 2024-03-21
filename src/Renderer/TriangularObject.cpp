#include "TriangularObject.h"

namespace ThreeDRenderer {
TriangularObject::TriangularObject(CoordinatesVector pos, ColorVector color,
                                   const std::vector<CoordinatesVector>& vertexes,
                                   const std::vector<ConnectionVector>& connections) {
    SetPosition(pos);
    connections_ = connections;
    color_ = color;
    for (int i = 0; i < 3; ++i) {
        while (color_(i) < 0) {
            color_(i) += 256;
        }
        color(i) %= 256;
    }
    vertexes_.resize(4, vertexes.size());
    for (int i = 0; i < vertexes.size(); ++i) {
        vertexes_(0, i) = vertexes[i](0);
        vertexes_(1, i) = vertexes[i](1);
        vertexes_(2, i) = vertexes[i](2);
        vertexes_(3, i) = 1;
    }
    for (int i = 0; i < connections_.size(); ++i) {
        while (connections_[i](0) < 0) {
            connections_[i](0) += vertexes_.cols();
        }
        connections_[i](0) %= vertexes_.cols();
        while (connections_[i](1) < 0) {
            connections_[i](1) += vertexes_.cols();
        }
        connections_[i](1) %= vertexes_.cols();
        while (connections_[i](2) < 0) {
            connections_[i](2) += vertexes_.cols();
        }
        connections_[i](2) %= vertexes_.cols();
    }
}

void TriangularObject::SetPosition(const CoordinatesVector& pos) {
    position_(0) = pos(0);
    position_(1) = pos(1);
    position_(2) = pos(2);
    position_(3) = 0;
}

TriangularObject::CoordinatesVector TriangularObject::GetPosition() const {
    return CoordinatesVector(position_(0), position_(1), position_(2));
}

const TriangularObject::ColorVector& TriangularObject::GetColor() const {
    return color_;
}

const TriangularObject::CoordinatesMatrix& TriangularObject::GetVertexesLocal() const {
    return vertexes_;
}

const std::vector<TriangularObject::ConnectionVector>& TriangularObject::GetConnections() const {
    return connections_;
}

TriangularObject::CoordinatesMatrix TriangularObject::GetVertexesGlobal() const {
    CoordinatesMatrix res = vertexes_;
    for (int i = 0; i < res.cols(); ++i) {
        res.col(i) += position_;
    }
    return res;
}
}  // namespace ThreeDRenderer