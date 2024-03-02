#pragma once

#include <Eigen/Dense>

namespace ThreeDRenderer {
class Camera {
    using CoordinatesVector = Eigen::Vector3d;
    using DirectionVector = Eigen::Vector3d;

public:
    Camera() = default;
    Camera(int width, int height);
    Camera(int width, int height, const CoordinatesVector& pos, const DirectionVector direction);

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
    DirectionVector direction_ = DirectionVector(1, 0, 0);
    int width_ = 800;
    int height_ = 600;
};
}  // namespace ThreeDRenderer
