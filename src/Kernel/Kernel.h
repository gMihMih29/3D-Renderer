#pragma once

#include "../Observer/Observer.h"
#include "../Renderer/PixelScreen.h"
#include "../Renderer/TriangularObject.h"
#include "../Renderer/World.h"

namespace ThreeDRenderer {

class Kernel {
    static const int kCamWidth = 800;
    static const int kCamHeight = 600;
    static constexpr double  kMovementSpeed = 0.25;
    static constexpr double kRotationSpeedDeg = 10;

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
