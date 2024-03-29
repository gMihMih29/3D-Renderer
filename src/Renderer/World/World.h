#pragma once

#include <vector>

#include "Camera.h"
#include "../Primitives/TriangularObject.h"
#include "../Light/AmbientLight.h"
#include "../Light/DirectionalLight.h"

namespace ThreeDRenderer {

class World {
    using Object = TriangularObject;

public:
    World() = default;

    void AddObject(Object&& obj);
    void AddDirectionalLight(DirectionalLight light);
    void SetAmbientLight(AmbientLight light);
    const std::vector<Object>& GetObjects() const;
    const std::vector<DirectionalLight>& GetDirectionalLight() const;
    const AmbientLight& GetAmbientLight() const;

private:
    std::vector<Object> objects_;
    std::vector<DirectionalLight> directional_light_sources_;
    AmbientLight ambient_light_;
};

}  // namespace ThreeDRenderer
