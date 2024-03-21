#include "World.h"

namespace ThreeDRenderer {
World::World(int cameraWidth, int cameraHeight) : cam_(cameraWidth, cameraHeight) {
}

void World::AddObject(World::Object obj) {
    objects_.push_back(obj);
}

void World::CamMoveForward() {
    cam_.MoveForward(kMOVEMENT_SPEED);
}

void World::CamMoveBackwads() {
    cam_.MoveBackwards(kMOVEMENT_SPEED);
}

void World::CamMoveLeft() {
    cam_.MoveLeft(kMOVEMENT_SPEED);
}

void World::CamMoveRight() {
    cam_.MoveRight(kMOVEMENT_SPEED);
}

void World::CamRotateUp() {
    cam_.RotateUpDeg(kROTATION_SPEED_DEG);
}

void World::CamRotateDown() {
    cam_.RotateDownDeg(kROTATION_SPEED_DEG);
}

void World::CamRotateLeft() {
    cam_.RotateLeftDeg(kROTATION_SPEED_DEG);
}

void World::CamRotateRight() {
    cam_.RotateRightDeg(kROTATION_SPEED_DEG);
}

const std::vector<World::Object>& World::GetObjects() const {
    return objects_;
}

const Camera& World::GetCamera() const {
    return cam_;
}

}  // namespace ThreeDRenderer