#pragma once

#include <Eigen/Dense>
#include <SFML/Graphics/Color.hpp>
#include <utility>
#include <vector>

#include "../Light/Color.h"
#include "Triangle.h"

namespace ThreeDRenderer {

class TriangulatedObject {
public:
    using ConnectionVector = std::vector<int>;
    using Matrix4xN = Eigen::Matrix4Xd;
    using Vector3 = Eigen::Vector3d;
    using Vector4 = Eigen::Vector4d;
    using Matrix3xN = Eigen::Matrix3Xd;

public:
    TriangulatedObject() = default;
    TriangulatedObject(std::vector<Triangle>&& surfaces, Vector3 pos = Vector3(0, 0, 0),
                       sf::Color color = sf::Color(0, 0, 0));

    void SetPosition(const Vector3& pos);
    void SetColor(sf::Color color);

    const Vector4& GetPosition() const;
    const Color& GetColor() const;
    const std::vector<Triangle>& GetSurfaces() const;

    Matrix4xN MakeVertexesLocal() const;
    Matrix4xN MakeVertexesGlobal() const;
    Matrix4xN MakeNormalVectorMatrix() const;
    std::vector<Vector4> MakeNormalVectors() const;

    bool IsEmpty() const;

private:
    Vector4 position_ = Vector4(0, 0, 0, 0);
    Color color_ = Color(sf::Color(0, 0, 0));
    std::vector<Triangle> surfaces_;
};

}  // namespace ThreeDRenderer
