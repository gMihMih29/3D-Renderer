#include "TriangulatedObject.h"

#include <cassert>
#include <cmath>

namespace ThreeDRenderer {

TriangulatedObject::TriangulatedObject(std::vector<Triangle>&& surfaces, Vector3 pos, sf::Color color)
    : position_(pos(0), pos(1), pos(2), 0), color_(color), surfaces_(surfaces) {
}

// TriangulatedObject::TriangulatedObject(Vector3 pos, sf::Color color, const std::vector<Vector3>& vertexes,
//                                        const std::vector<ConnectionVector>& connections)
//     : position_(pos(0), pos(1), pos(2), 0), color_(color) {
//     assert(vertexes.size() != 0 && "There must be some vertexes for object");
//     assert(connections.size() != 0 && "There must be some connections for object");
//     size_t count_vertexes = vertexes.size();
//     std::vector<Vector3> normals(count_vertexes, Vector3(0, 0, 0));
//     for (int i = 0; i < count_vertexes; ++i) {
//         std::vector<bool> used(count_vertexes);
//         for (int j = 0; j < connections.size(); ++j) {
//             assert(connections[j].size() >= 3 && "Surfaces must contain at least 3 vertexes");
//             for (int k = 0; k < connections[j].size(); ++k) {
//                 if (connections[j][k] == i) {
//                     int prev = (k - 1) % connections[j].size();
//                     if (prev < 0) {
//                         prev += connections[j].size();
//                     }
//                     assert(0 <= prev && prev < connections[j].size() && "prev has incorrect index");
//                     int next = (k + 1) % connections[j].size();
//                     if (!used[prev]) {
//                         normals[i] += vertexes[connections[j][prev]] - vertexes[i];
//                         used[prev] = true;
//                     }
//                     if (!used[next]) {
//                         normals[i] += vertexes[connections[j][next]] - vertexes[i];
//                         used[next] = true;
//                     }
//                 }
//             }
//         }
//     }
//     for (int i = 0; i < count_vertexes; ++i) {
//         assert(!normals[i].isZero() && "Normal vector must be non zero");
//         normals[i] = -normals[i];
//     }
//     for (int i = 0; i < connections.size(); ++i) {
//         Vector3 surface_normal_vector;
//         for (int j = 0; j < connections[i].size(); ++j) {
//             surface_normal_vector += normals[connections[i][j]];
//         }
//         assert(!surface_normal_vector.isZero() && "Normal vector must be non zero");
//         surface_normal_vector.normalize();
//         for (int j = 1; j + 1 < connections[i].size(); ++j) {
//             surfaces_.emplace_back(vertexes[connections[i][0]], vertexes[connections[i][j]],
//                                    vertexes[connections[i][j + 1]], surface_normal_vector);
//         }
//     }
// }

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
