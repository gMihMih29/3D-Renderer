#pragma once

#include <cmath>
#include <Eigen/Dense>

#include "../Funcs/MathFuncs.h"

namespace ThreeDRenderer {

class Camera {
    using Vector3 = Eigen::Vector3d;
    using Vector4 = Eigen::Vector4d;
    using Matrix4 = Eigen::Matrix4d;
    using HomogeniousTransformation = Eigen::Matrix4d;
    const double kNearPlaneDistance = 0.1;
    const double kHorizontalFieldOfViewAngleRad = DegToRad(100);

public:
    Camera() = default;
    Camera(const Vector3& pos, const Matrix4& directions);

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

    const Vector4& GetPosition() const;
    Vector4 GetForwardDirectionOfCamera() const;
    Vector4 GetRightDirectionOfCamera() const;
    HomogeniousTransformation GetTransformToCameraSpaceMatrix() const;
    const Matrix4& GetDirectionMatrix() const;
    double GetNearPlaneDistance() const;
    double GetHorizontalFieldOfViewRad() const;

private:
    Vector4 position_{0, 0, 0, 0};
    Matrix4 directionMatrix_{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    double near_plane_distance_ = kNearPlaneDistance;
    double horizontal_field_of_view_angle_rad_ = kHorizontalFieldOfViewAngleRad;
};

}  // namespace ThreeDRenderer
