#include "Kernel.h"

#include <utility>

#include "../Renderer/Primitives/TriangularObject.h"
#include "../Renderer/Renderer.h"

namespace ThreeDRenderer {

Kernel::Kernel() : Kernel(kCamWidth, kCamHeight) {
}

Kernel::Kernel(int cam_width, int cam_height) : cam_(), world_(), screen_buffer_(cam_width, cam_height) {
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

const PixelScreen& Kernel::MakeScene() {
    Renderer renderer;
    renderer.Render(world_, cam_, screen_buffer_);
    return screen_buffer_;
}

}  // namespace ThreeDRenderer
