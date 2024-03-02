#include "Camera.h"

#include "MathFuncs.h"

namespace ThreeDRenderer {
Camera::Camera(int width, int height) : width_(width), height_(height) {
}

Camera::Camera(int width, int height, const CoordinatesVector& pos, const DirectionMatrix& directions)
    : width_(width), height_(height), position_(pos), directionMatrix_(directions) {
}

void Camera::MoveForward(double distance) {
    position_ += distance * directionMatrix_.col(2);
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

void Camera::RotateUpRad(double angle) {
    // TODO
}

void Camera::RotateRightRad(double angle) {
    // TODO
}

void Camera::RotateDownDeg(double angle) {
    RotateDownRad(DegToRad(angle));
}

void Camera::RotateUpDeg(double angle) {
    RotateUpRad(DegToRad(angle));
}

void Camera::RotateLeftDeg(double angle) {
    RotateLeftRad(DegToRad(angle));
}

void Camera::RotateRightDeg(double angle) {
    RotateRightRad(DegToRad(angle));
}

void Camera::RotateDownRad(double angle) {
    RotateUpRad(-angle);
}

void Camera::RotateRightRad(double angle) {
    RotateRightRad(-angle);
}

}  // namespace ThreeDRenderer
