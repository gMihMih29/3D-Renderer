#include "Camera.h"

#include "../Funcs/MathFuncs.h"

namespace ThreeDRenderer {

Camera::Camera(const Vector4& pos, const Matrix4& directions) : position_(pos), directionMatrix_(directions) {
}

void Camera::MoveForward(double distance) {
    distance = -distance;
    position_ += distance * GetForwardDirectionOfCamera();
}

void Camera::MoveBackwards(double distance) {
    MoveForward(-distance);
}

void Camera::MoveLeft(double distance) {
    MoveRight(-distance);
}

void Camera::MoveRight(double distance) {
    position_ += distance * GetRightDirectionOfCamera();
}

void Camera::RotateDownRad(double angle) {
    double s = std::sin(angle);
    double c = std::cos(angle);
    Eigen::Matrix4d rx{{1, 0, 0, 0}, {0, c, -s, 0}, {0, s, c, 0}, {0, 0, 0, 1}};
    directionMatrix_ = rx * directionMatrix_;
}

void Camera::RotateLeftRad(double angle) {
    RotateRightRad(-angle);
}

void Camera::RotateUpDeg(double angle) {
    RotateUpRad(DegToRad(angle));
}

void Camera::RotateUpRad(double angle) {
    RotateDownRad(-angle);
}

void Camera::RotateDownDeg(double angle) {
    RotateDownRad(DegToRad(angle));
}

void Camera::RotateLeftDeg(double angle) {
    RotateLeftRad(DegToRad(angle));
}

void Camera::RotateRightRad(double angle) {
    double s = std::sin(angle);
    double c = std::cos(angle);
    Eigen::Matrix4d ry{{c, 0, s, 0}, {0, 1, 0, 0}, {-s, 0, c, 0}, {0, 0, 0, 1}};
    directionMatrix_ = ry * directionMatrix_;
}

void Camera::RotateRightDeg(double angle) {
    RotateRightRad(DegToRad(angle));
}

const Camera::Vector4& Camera::GetPosition() const {
    return position_;
}

Camera::Vector4 Camera::GetForwardDirectionOfCamera() const {
    return directionMatrix_.inverse() * Vector4(0, 0, -1, 0);
}

Camera::Vector4 Camera::GetRightDirectionOfCamera() const {
    return directionMatrix_.inverse() * Vector4(-1, 0, 0, 0);
}

Camera::HomogeniousTransformation Camera::GetTransformToCameraSpaceMatrix() const {
    HomogeniousTransformation res{{directionMatrix_(0, 0), directionMatrix_(0, 1), directionMatrix_(0, 2), 0},
                                  {directionMatrix_(1, 0), directionMatrix_(1, 1), directionMatrix_(1, 2), 0},
                                  {directionMatrix_(2, 0), directionMatrix_(2, 1), directionMatrix_(2, 2), 0},
                                  {0, 0, 0, 1}};
    return res;
}

const Camera::Matrix4& Camera::GetDirectionMatrix() const {
    return directionMatrix_;
}

double Camera::GetNearPlaneDistance() const {
    return near_plane_distance_;
}

double Camera::GetHorizontalFieldOfViewRad() const {
    return horizontal_field_of_view_angle_rad_;
}

}  // namespace ThreeDRenderer
