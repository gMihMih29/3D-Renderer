#pragma once

#include <vector>

#include "Camera.h"
#include "../Primitives/TriangulatedObject.h"
#include "../Light/AmbientLight.h"
#include "../Light/DirectionalLight.h"

namespace ThreeDRenderer {

class World {
    using Object = TriangulatedObject;

public:
    World() = default;

    void SetAmbientLight(AmbientLight light);
    void AddObject(Object&& obj);
    void AddDirectionalLight(DirectionalLight light);

    const std::vector<Object>& GetObjects() const;
    const std::vector<DirectionalLight>& GetDirectionalLight() const;
    const AmbientLight& GetAmbientLight() const;

private:
    std::vector<Object> objects_;
    std::vector<DirectionalLight> directional_light_sources_;
    AmbientLight ambient_light_;
};

}  // namespace ThreeDRenderer
