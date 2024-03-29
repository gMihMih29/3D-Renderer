#pragma once

#include <cmath>
#include <Eigen/Dense>

#include "../Funcs/MathFuncs.h"

namespace ThreeDRenderer {

class Camera {
    using CoordinatesVector = Eigen::Vector3d;
    using DirectionVector = Eigen::Vector3d;
    using CameraSpaceTransfromMatrix = Eigen::Matrix4d;
    using DirectionMatrix = Eigen::Matrix3d;
    const int kWidth = 800;
    const int kHeight = 600;
    const double kNearPlaneDistance = 1;
    const double kHorizontalFieldOfViewAngleRad = DegToRad(120);

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
    DirectionVector GetDirectionOfCamera() const;
    CameraSpaceTransfromMatrix GetTransformToCameraSpaceMatrix() const;
    const DirectionMatrix& GetDirectionMatrix() const;
    int GetWidth() const;
    int GetHeight() const;
    double GetNearPlaneDistance() const;
    double GetHorizontalFieldOfViewRad() const;

private:
    CoordinatesVector position_ = CoordinatesVector(0, 0, 0);
    DirectionMatrix directionMatrix_{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    int width_ = kWidth;
    int height_ = kHeight;
    double near_plane_distance_ = kNearPlaneDistance;
    double horizontal_field_of_view_angle_rad_ = kHorizontalFieldOfViewAngleRad;
};

}  // namespace ThreeDRenderer