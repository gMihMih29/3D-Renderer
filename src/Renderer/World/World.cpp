#include "World.h"

namespace ThreeDRenderer {

void World::AddObject(World::Object&& obj) {
    objects_.push_back(std::move(obj));
}

void World::AddDirectionalLight(DirectionalLight light) {
    directional_light_sources_.push_back(light);
}

void World::SetAmbientLight(AmbientLight light) {
    ambient_light_ = light;
}

const std::vector<World::Object>& World::GetObjects() const {
    return objects_;
}

const std::vector<DirectionalLight>& World::GetDirectionalLight() const {
    return directional_light_sources_;
}

const AmbientLight& World::GetAmbientLight() const {
    return ambient_light_;
}

}  // namespace ThreeDRenderer
