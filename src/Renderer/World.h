#include <vector>

#include "Camera.h"
#include "TriangularObject.h"

namespace ThreeDRenderer {
class World {
    using Object = TriangularObject;

public:
    World();

    void AddObject(Object obj);

    void CamMoveForward();
    void CamMoveBackwads();
    void CamMoveLeft();
    void CamMoveRight();
    void CamRotateUp();
    void CamRotateDown();
    void CamRotateLeft();
    void CamRotateRight();

    const std::vector<Object> GetObjects() const;
    const Camera& GetCamera() const;

private:
    std::vector<Object> objects_;
    Camera cam_;
};
}  // namespace ThreeDRenderer
