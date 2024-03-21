#include "Kernel.h"

namespace ThreeDRenderer {

Kernel::Kernel() : Kernel(kCamWidth, kCamHeight) {
}

Kernel::Kernel(int camWidth, int camHeight) : cam_(camWidth, camHeight), world_() {
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

void Kernel::AddObject(TriangularObject obj) {
    world_.AddObject(obj);
}

PixelScreen Kernel::GetScene() {
    PixelScreen ps = PixelScreen(kCamWidth, kCamHeight);
    int k = 0;
    for (int i = 0; i < ps.GetHeigth(); ++i) {
        for (int j = 0; j < ps.GetWidth(); ++j) {
            ps.GetPixel(j, i).color = sf::Color(k % 256, k / 256 % 256, k / 256 / 256 % 256);
            ++k;
        }
    }
    return ps;
}

}  // namespace ThreeDRenderer
