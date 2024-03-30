#pragma once

#include "../Renderer/Light/AmbientLight.h"
#include "../Renderer/Light/DirectionalLight.h"
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

    void MoveCameraForward();
    void MoveCameraBackwads();
    void MoveCameraLeft();
    void MoveCameraRight();
    void RotateCameraUp();
    void RotateCameraDown();
    void RotateCameraLeft();
    void RotateCameraRight();
    
    void AddObject(TriangularObject&& obj);
    void SetAmbientLight(AmbientLight&& light);
    void AddDirectionalLight(DirectionalLight&& light);

    const PixelScreen& MakeScene();

private:
    Camera cam_;
    World world_;
    PixelScreen screen_buffer_;
};

}  // namespace ThreeDRenderer
