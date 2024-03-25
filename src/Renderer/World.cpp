#include "World.h"

namespace ThreeDRenderer {
void World::AddObject(World::Object&& obj) {
    objects_.push_back(std::move(obj));
}

const std::vector<World::Object>& World::GetObjects() const {
    return objects_;
}

}  // namespace ThreeDRenderer
