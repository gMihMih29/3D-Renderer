#include "Kernel.h"

#include <utility>

#include "../Renderer/Primitives/TriangulatedObject.h"
#include "../Renderer/Renderer.h"

namespace ThreeDRenderer {

Kernel::Kernel() : Kernel(kCamWidth, kCamHeight) {
}

Kernel::Kernel(int cam_width, int cam_height) : cam_(), world_(), screen_buffer_(cam_width, cam_height) {
    SetAmbientLight(AmbientLight({128, 128, 128}));

}

void Kernel::MoveCameraForward() {
    cam_.MoveForward(kMovementSpeed);
}

void Kernel::MoveCameraBackwads() {
    cam_.MoveBackwards(kMovementSpeed);
}

void Kernel::MoveCameraLeft() {
    cam_.MoveLeft(kMovementSpeed);
}

void Kernel::MoveCameraRight() {
    cam_.MoveRight(kMovementSpeed);
}

void Kernel::RotateCameraUp() {
    cam_.RotateUpDeg(kRotationSpeedDeg);
}

void Kernel::RotateCameraDown() {
    cam_.RotateDownDeg(kRotationSpeedDeg);
}

void Kernel::RotateCameraLeft() {
    cam_.RotateLeftDeg(kRotationSpeedDeg);
}

void Kernel::RotateCameraRight() {
    cam_.RotateRightDeg(kRotationSpeedDeg);
}

void Kernel::AddObject(TriangulatedObject&& obj) {
    world_.AddObject(std::move(obj));
}

void Kernel::SetAmbientLight(AmbientLight&& light) {
    world_.SetAmbientLight(light);
}

void Kernel::AddDirectionalLight(DirectionalLight&& light) {
    world_.AddDirectionalLight(light);
}

const PixelScreen& Kernel::MakeScene() {
    Renderer renderer;
    renderer.Render(world_, cam_, screen_buffer_);
    return screen_buffer_;
}

}  // namespace ThreeDRenderer
