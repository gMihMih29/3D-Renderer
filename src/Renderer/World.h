#pragma once

#include <vector>

#include "Camera.h"
#include "TriangularObject.h"

namespace ThreeDRenderer {

class World {
    using Object = TriangularObject;

public:
    World() = default;

    void AddObject(Object&& obj);
    const std::vector<Object>& GetObjects() const;

private:
    std::vector<Object> objects_;
};

}  // namespace ThreeDRenderer
