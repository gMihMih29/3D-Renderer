#pragma once

#include <Eigen/Dense>
#include <SFML/Graphics/Color.hpp>
#include <utility>
#include <vector>

#include "Triangle.h"

namespace ThreeDRenderer {

class TriangularObject {
public:
    using ColorVector = sf::Color;
    using ConnectionVector = std::vector<int>;
    using CoordinatesMatrix = Eigen::Matrix4Xd;
    using CoordinatesVector = Eigen::Vector3d;
    using CoordinatesVector4D = Eigen::Vector4d;
    using NormalVector = Eigen::Vector3d;
    using Surface = Triangle;

public:
    TriangularObject(CoordinatesVector pos, ColorVector color, std::vector<Surface>&& surfaces);
    TriangularObject(CoordinatesVector pos, ColorVector color, const std::vector<CoordinatesVector>& vertexes,
                     const std::vector<ConnectionVector>& connections);

    void SetPosition(const CoordinatesVector& pos);
    void SetColor(sf::Color color);
    CoordinatesVector GetPosition() const;
    const ColorVector& GetColor() const;
    CoordinatesMatrix GetVertexesLocal() const;
    CoordinatesMatrix GetVertexesGlobal() const;
    std::vector<NormalVector> GetNormalVectors() const;
    const std::vector<Surface>& GetSurfaces() const;

private:
    CoordinatesVector4D position_ = CoordinatesVector4D(0, 0, 0, 0);
    ColorVector color_ = ColorVector(0, 0, 0);
    std::vector<Surface> surfaces_;
};

}  // namespace ThreeDRenderer
