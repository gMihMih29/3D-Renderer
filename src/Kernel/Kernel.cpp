#include "Kernel.h"

#include <utility>

#include "../Renderer/Primitives/TriangulatedObject.h"
#include "../Renderer/Renderer.h"

namespace ThreeDRenderer {

Kernel::Kernel() : Kernel(kScreenHeight, kScreenWidth) {
}

Kernel::Kernel(int screen_height, int screen_width)
    : cam_(), world_(), screen_buffer_(screen_height, screen_width), renderer_(screen_height, screen_width) {
    SetAmbientLight(AmbientLight({64, 64, 64}));
    AddDirectionalLight(DirectionalLight({0, 0, -1}, {255, 0, 0}));
    AddDirectionalLight(DirectionalLight({1, 0, 0}, {0, 0, 255}));
    AddDirectionalLight(DirectionalLight({1, -1, 1}, {0, 255, 0}));
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
    renderer_.Render(world_, cam_, screen_buffer_);
    return screen_buffer_;
}

}  // namespace ThreeDRenderer
