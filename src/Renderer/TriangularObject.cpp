#include "TriangularObject.h"

#include <cassert>
#include <cmath>

#include "../Utilities/Logger.h"

namespace ThreeDRenderer {

TriangularObject::TriangularObject(CoordinatesVector pos, ColorVector color, std::vector<Surface>&& surfaces) {
    position_ = CoordinatesVector4D(pos(0), pos(1), pos(2), 0);
    color_ = color;
    surfaces_ = surfaces;
}

TriangularObject::TriangularObject(CoordinatesVector pos, ColorVector color,
                                   const std::vector<CoordinatesVector>& vertexes,
                                   const std::vector<ConnectionVector>& connections) {
    assert(vertexes.size() != 0 && "There must be some vertexes for object");
    assert(connections.size() != 0 && "There must be some connections for object");
    position_ = CoordinatesVector4D(pos(0), pos(1), pos(2), 0);
    color_ = color;
    size_t count_vertexes = vertexes.size();
    std::vector<NormalVector> normals(count_vertexes, NormalVector(0, 0, 0));
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
        // normals[i].normalize();
    }
    for (int i = 0; i < connections.size(); ++i) {
        NormalVector surface_normal_vector;
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

void TriangularObject::SetPosition(const CoordinatesVector& pos) {
    position_(0) = pos(0);
    position_(1) = pos(1);
    position_(2) = pos(2);
    position_(3) = 0;
}

void TriangularObject::SetColor(sf::Color color) {
    color_ = color;
}

TriangularObject::CoordinatesVector TriangularObject::GetPosition() const {
    return CoordinatesVector(position_(0), position_(1), position_(2));
}

const TriangularObject::ColorVector& TriangularObject::GetColor() const {
    return color_;
}

TriangularObject::CoordinatesMatrix TriangularObject::GetVertexesLocal() const {
    CoordinatesMatrix res;
    res.resize(4, 3 * surfaces_.size());
    for (int i = 0; i < surfaces_.size(); ++i) {
        res.col(3 * i) = surfaces_[i].GetPoint(0);
        res.col(3 * i + 1) = surfaces_[i].GetPoint(1);
        res.col(3 * i + 2) = surfaces_[i].GetPoint(2);
    }
    return res;
}

TriangularObject::CoordinatesMatrix TriangularObject::GetVertexesGlobal() const {
    CoordinatesMatrix res;
    res.resize(4, 3 * surfaces_.size());
    for (int i = 0; i < surfaces_.size(); ++i) {
        res.col(3 * i) = surfaces_[i].GetPoint(0) + position_;
        res.col(3 * i + 1) = surfaces_[i].GetPoint(1) + position_;
        res.col(3 * i + 2) = surfaces_[i].GetPoint(2) + position_;
    }
    return res;
}

std::vector<TriangularObject::NormalVector> TriangularObject::GetNormalVectors() const {
    std::vector<NormalVector> res(surfaces_.size());
    for (int i = 0; i < res.size(); ++i) {
        res[i] = surfaces_[i].GetNormalVector();
    }
    return res;
}

const std::vector<TriangularObject::Surface>& TriangularObject::GetSurfaces() const {
    return surfaces_;
}

}  // namespace ThreeDRenderer
