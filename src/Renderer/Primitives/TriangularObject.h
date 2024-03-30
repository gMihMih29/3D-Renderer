#pragma once

#include <Eigen/Dense>
#include <SFML/Graphics/Color.hpp>
#include <utility>
#include <vector>

#include "Triangle.h"
#include "../Light/Color.h"

namespace ThreeDRenderer {

class TriangularObject {
public:
    using ConnectionVector = std::vector<int>;
    using Matrix4xN = Eigen::Matrix4Xd;
    using Vector3 = Eigen::Vector3d;
    using Vector4 = Eigen::Vector4d;
    using Matrix3xN = Eigen::Matrix3Xd;

public:
    TriangularObject(Vector3 pos, sf::Color color, std::vector<Triangle>&& surfaces);
    TriangularObject(Vector3 pos, sf::Color color, const std::vector<Vector3>& vertexes,
                     const std::vector<ConnectionVector>& connections);

    void SetPosition(const Vector3& pos);
    void SetColor(sf::Color color);
    Vector3 GetPosition() const;
    const Color& GetColor() const;
    Matrix4xN MakeVertexesLocal() const;
    Matrix4xN MakeVertexesGlobal() const;
    std::vector<Vector4> MakeNormalVectors() const;
    Matrix4xN MakeNormalVectorMatrix() const;
    const std::vector<Triangle>& GetSurfaces() const;

private:
    Vector4 position_ = Vector4(0, 0, 0, 0);
    Color color_;
    std::vector<Triangle> surfaces_;
};

}  // namespace ThreeDRenderer
