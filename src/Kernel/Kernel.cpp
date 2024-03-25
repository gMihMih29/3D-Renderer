#include "Kernel.h"

#include <utility>

namespace ThreeDRenderer {

Kernel::Kernel() : Kernel(kCamWidth, kCamHeight) {
}

Kernel::Kernel(int cam_width, int cam_height) : cam_(cam_width, cam_height), world_() {
}

void Kernel::CamMoveForward() {
    cam_.MoveForward(kMovementSpeed);
}

void Kernel::CamMoveBackwads() {
    cam_.MoveBackwards(kMovementSpeed);
}

void Kernel::CamMoveLeft() {
    cam_.MoveLeft(kMovementSpeed);
}

void Kernel::CamMoveRight() {
    cam_.MoveRight(kMovementSpeed);
}

void Kernel::CamRotateUp() {
    cam_.RotateUpDeg(kRotationSpeedDeg);
}

void Kernel::CamRotateDown() {
    cam_.RotateDownDeg(kRotationSpeedDeg);
}

void Kernel::CamRotateLeft() {
    cam_.RotateLeftDeg(kRotationSpeedDeg);
}

void Kernel::CamRotateRight() {
    cam_.RotateRightDeg(kRotationSpeedDeg);
}

void Kernel::AddObject(TriangularObject&& obj) {
    world_.AddObject(std::move(obj));
}

PixelScreen Kernel::GetScene() {
    return Renderer::Render(world_, cam_);
}

}  // namespace ThreeDRenderer
