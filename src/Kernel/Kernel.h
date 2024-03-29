#pragma once

#include "../Renderer/PixelScreen.h"
#include "../Renderer/World/Camera.h"
#include "../Renderer/World/World.h"

namespace ThreeDRenderer {

class Kernel {
    static const int kCamWidth = 800;
    static const int kCamHeight = 600;
    static constexpr double kMovementSpeed = 0.25;
    static constexpr double kRotationSpeedDeg = 1;

public:
    Kernel();
    Kernel(int cam_width, int cam_height);

    void CamMoveForward();
    void CamMoveBackwads();
    void CamMoveLeft();
    void CamMoveRight();
    void CamRotateUp();
    void CamRotateDown();
    void CamRotateLeft();
    void CamRotateRight();
    void AddObject(TriangularObject&& obj);

    const PixelScreen& MakeScene();

private:
    Camera cam_;
    World world_;
    PixelScreen screen_buffer_;
};

}  // namespace ThreeDRenderer
