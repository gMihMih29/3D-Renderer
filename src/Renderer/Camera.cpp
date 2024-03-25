#include "Camera.h"

#include "MathFuncs.h"

namespace ThreeDRenderer {

Camera::Camera(int width, int height) : width_(width), height_(height) {
}

Camera::Camera(int width, int height, const CoordinatesVector& pos, const DirectionMatrix& directions)
    : width_(width), height_(height), position_(pos), directionMatrix_(directions) {
}

void Camera::MoveForward(double distance) {
    position_ += distance * GetDirectionOfCamera();
}

void Camera::MoveBackwards(double distance) {
    MoveForward(-distance);
}

void Camera::MoveLeft(double distance) {
    MoveRight(-distance);
}

void Camera::MoveRight(double distance) {
    position_ += distance * directionMatrix_.col(0);
}

void Camera::RotateDownRad(double angle) {
    double s = std::sin(angle);
    double c = std::cos(angle);
    DirectionMatrix rx{{1, 0, 0}, {0, c, -s}, {0, s, c}};
    directionMatrix_ = rx * directionMatrix_;
}

void Camera::RotateLeftRad(double angle) {
    double s = std::sin(angle);
    double c = std::cos(angle);
    DirectionMatrix ry{{c, 0, s}, {0, 1, 0}, {-s, 0, c}};
    directionMatrix_ = ry * directionMatrix_;
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
    RotateLeftRad(-angle);
}

void Camera::RotateRightDeg(double angle) {
    RotateRightRad(DegToRad(angle));
}

const Camera::CoordinatesVector& Camera::GetPosition() const {
    return position_;
}

Camera::DirectionVector Camera::GetDirectionOfCamera() const {
    return -directionMatrix_.col(2);
}

Camera::CameraSpaceTransfromMatrix Camera::GetTransformToCameraSpaceMatrix() const {
    CameraSpaceTransfromMatrix res{
        {directionMatrix_(0, 0), directionMatrix_(0, 1), directionMatrix_(0, 2), position_(0)},
        {directionMatrix_(1, 0), directionMatrix_(1, 1), directionMatrix_(1, 2), position_(1)},
        {directionMatrix_(2, 0), directionMatrix_(2, 1), directionMatrix_(2, 2), position_(2)},
        {0, 0, 0, 1}};
    return res;
}

const Camera::DirectionMatrix& Camera::GetDirectionMatrix() const {
    return directionMatrix_;
}

int Camera::GetWidth() const {
    return width_;
}

int Camera::GetHeight() const {
    return height_;
}

}  // namespace ThreeDRenderer
