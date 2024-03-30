#include "TriangularObject.h"

#include <cassert>
#include <cmath>

namespace ThreeDRenderer {

TriangularObject::TriangularObject(Vector3 pos, sf::Color color, std::vector<Triangle>&& surfaces)
    : position_(pos(0), pos(1), pos(2), 0), color_(color), surfaces_(surfaces) {
}

TriangularObject::TriangularObject(Vector3 pos, sf::Color color, const std::vector<Vector3>& vertexes,
                                   const std::vector<ConnectionVector>& connections)
    : position_(pos(0), pos(1), pos(2), 0), color_(color){
    assert(vertexes.size() != 0 && "There must be some vertexes for object");
    assert(connections.size() != 0 && "There must be some connections for object");
    size_t count_vertexes = vertexes.size();
    std::vector<Vector3> normals(count_vertexes, Vector3(0, 0, 0));
    for (int i = 0; i < count_vertexes; ++i) {
        std::vector<bool> used(count_vertexes);
        for (int j = 0; j < connections.size(); ++j) {
            assert(connections[j].size() >= 3 && "Surfaces must contain at least 3 vertexes");
            for (int k = 0; k < connections[j].size(); ++k) {
                if (connections[j][k] == i) {
                    int prev = (k - 1) % connections[j].size();
                    if (prev < 0) {
                        prev += connections[j].size();
                    }
                    assert(0 <= prev && prev < connections[j].size() && "prev has incorrect index");
                    int next = (k + 1) % connections[j].size();
                    if (!used[prev]) {
                        normals[i] += vertexes[connections[j][prev]] - vertexes[i];
                        used[prev] = true;
                    }
                    if (!used[next]) {
                        normals[i] += vertexes[connections[j][next]] - vertexes[i];
                        used[next] = true;
                    }
                }
            }
        }
    }
    for (int i = 0; i < count_vertexes; ++i) {
        assert(!normals[i].isZero() && "Normal vector must be non zero");
        normals[i] = -normals[i];
    }
    for (int i = 0; i < connections.size(); ++i) {
        Vector3 surface_normal_vector;
        for (int j = 0; j < connections[i].size(); ++j) {
            surface_normal_vector += normals[connections[i][j]];
        }
        assert(!surface_normal_vector.isZero() && "Normal vector must be non zero");
        surface_normal_vector.normalize();
        for (int j = 1; j + 1 < connections[i].size(); ++j) {
            surfaces_.emplace_back(vertexes[connections[i][0]], vertexes[connections[i][j]],
                                   vertexes[connections[i][j + 1]], surface_normal_vector);
        }
    }
}

void TriangularObject::SetPosition(const Vector3& pos) {
    position_(0) = pos(0);
    position_(1) = pos(1);
    position_(2) = pos(2);
    position_(3) = 0;
}

void TriangularObject::SetColor(sf::Color color) {
    color_ = Color(color);
}

TriangularObject::Vector3 TriangularObject::GetPosition() const {
    return Vector3(position_(0), position_(1), position_(2));
}

const Color& TriangularObject::GetColor() const {
    return color_;
}

TriangularObject::Matrix4xN TriangularObject::MakeVertexesLocal() const {
    Matrix4xN res;
    res.resize(4, 3 * surfaces_.size());
    for (int i = 0; i < surfaces_.size(); ++i) {
        res.col(3 * i) = surfaces_[i].GetPoint(0);
        res.col(3 * i + 1) = surfaces_[i].GetPoint(1);
        res.col(3 * i + 2) = surfaces_[i].GetPoint(2);
    }
    return res;
}

TriangularObject::Matrix4xN TriangularObject::MakeVertexesGlobal() const {
    Matrix4xN res;
    res.resize(4, 3 * surfaces_.size());
    for (int i = 0; i < surfaces_.size(); ++i) {
        res.col(3 * i) = surfaces_[i].GetPoint(0) + position_;
        res.col(3 * i + 1) = surfaces_[i].GetPoint(1) + position_;
        res.col(3 * i + 2) = surfaces_[i].GetPoint(2) + position_;
    }
    return res;
}

std::vector<TriangularObject::Vector4> TriangularObject::MakeNormalVectors() const {
    std::vector<Vector4> res(surfaces_.size());
    for (int i = 0; i < res.size(); ++i) {
        res[i] = surfaces_[i].GetNormalVector();
    }
    return res;
}

TriangularObject::Matrix4xN TriangularObject::MakeNormalVectorMatrix() const {
    Matrix4xN res;
    res.resize(4, surfaces_.size());
    for (int i = 0; i < surfaces_.size(); ++i) {
        res.col(i) = surfaces_[i].GetNormalVector();
    }
    return res;
}

const std::vector<Triangle>& TriangularObject::GetSurfaces() const {
    return surfaces_;
}

}  // namespace ThreeDRenderer
