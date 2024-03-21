#pragma once

#include "../Observer/Observer.h"
#include "../Renderer/PixelScreen.h"
#include "../Renderer/TriangularObject.h"
#include "../Renderer/World.h"

namespace ThreeDRenderer {

class Kernel {
    const int kCAM_WIDTH = 800;
    const int kCAM_HEIGHT = 600;
    const double kMOVEMENT_SPEED = 0.25;
    const double kROTATION_SPEED_DEG = 10;

public:
    Kernel();
    Kernel(int camWidth, int camHeight);

    void CamMoveForward();
    void CamMoveBackwads();
    void CamMoveLeft();
    void CamMoveRight();
    void CamRotateUp();
    void CamRotateDown();
    void CamRotateLeft();
    void CamRotateRight();
    void AddObject(TriangularObject obj);

    PixelScreen GetScene();

private:
    Camera cam_;
    World world_;
};

}  // namespace ThreeDRenderer
