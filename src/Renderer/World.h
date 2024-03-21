#pragma once

#include <vector>

#include "Camera.h"
#include "TriangularObject.h"

namespace ThreeDRenderer {
class World {
    using Object = TriangularObject;
    const double kMOVEMENT_SPEED = 0.25;
    const double kROTATION_SPEED_DEG = 10;
public:
    World() = default;

    void AddObject(Object obj);

    void CamMoveForward();
    void CamMoveBackwads();
    void CamMoveLeft();
    void CamMoveRight();
    void CamRotateUp();
    void CamRotateDown();
    void CamRotateLeft();
    void CamRotateRight();

    const std::vector<Object>& GetObjects() const;
    const Camera& GetCamera() const;

private:
    std::vector<Object> objects_;
    Camera cam_;
};
}  // namespace ThreeDRenderer
