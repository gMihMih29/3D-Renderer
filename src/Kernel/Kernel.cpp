#include "Kernel.h"

namespace ThreeDRenderer {

Kernel::Kernel() : Kernel(kCAM_WIDTH, kCAM_HEIGHT) {
}

Kernel::Kernel(int camWidth, int camHeight) : cam_(camWidth, camHeight), world_() {
}

void Kernel::CamMoveForward() {
    cam_.MoveForward(kMOVEMENT_SPEED);
}

void Kernel::CamMoveBackwads() {
    cam_.MoveBackwards(kMOVEMENT_SPEED);
}

void Kernel::CamMoveLeft() {
    cam_.MoveLeft(kMOVEMENT_SPEED);
}

void Kernel::CamMoveRight() {
    cam_.MoveRight(kMOVEMENT_SPEED);
}

void Kernel::CamRotateUp() {
    cam_.RotateUpDeg(kROTATION_SPEED_DEG);
}

void Kernel::CamRotateDown() {
    cam_.RotateDownDeg(kROTATION_SPEED_DEG);
}

void Kernel::CamRotateLeft() {
    cam_.RotateLeftDeg(kROTATION_SPEED_DEG);
}

void Kernel::CamRotateRight() {
    cam_.RotateRightDeg(kROTATION_SPEED_DEG);
}

void Kernel::AddObject(TriangularObject obj) {
    world_.AddObject(obj);
}

PixelScreen Kernel::GetScene() {
    PixelScreen ps = PixelScreen(kCAM_WIDTH, kCAM_HEIGHT);
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
