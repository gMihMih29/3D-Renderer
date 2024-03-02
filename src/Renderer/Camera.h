#pragma once

#include <Eigen/Dense>
#include <cmath>

namespace ThreeDRenderer {
class Camera {
    using CoordinatesVector = Eigen::Vector3d;
    using DirectionVector = Eigen::Vector3d;
    using DirectionMatrix = Eigen::Matrix3d;

public:
    Camera() = default;
    Camera(int width, int height);
    Camera(int width, int height, const CoordinatesVector& pos, const DirectionMatrix& directions);

    void MoveForward(double distance);
    void MoveBackwards(double distance);
    void MoveLeft(double distance);
    void MoveRight(double distance);

    void RotateUpRad(double angle);
    void RotateUpDeg(double angle);
    void RotateDownRad(double angle);
    void RotateDownDeg(double angle);
    void RotateLeftRad(double angle);
    void RotateLeftDeg(double angle);
    void RotateRightRad(double angle);
    void RotateRightDeg(double angle);

    const CoordinatesVector& GetPosition() const;
    const DirectionVector& GetDirection() const;
    size_t GetWidth() const;
    size_t GetHeight() const;

private:
    CoordinatesVector position_ = CoordinatesVector(0, 0, 0);
    DirectionMatrix directionMatrix_{1, 0, 0, 0, 1, 0, 0, 0, -1};
    int width_ = 800;
    int height_ = 600;
};
}  // namespace ThreeDRenderer
