#include "computer_graphics/camera_manager.hpp"

namespace computer_graphics {

CameraManager::CameraManager(class Game &game, const Initializer &initializer) : Component(game, initializer) {}

const Camera *CameraManager::MainCamera() const {
    return nullptr;
}

Camera *CameraManager::MainCamera() {
    return nullptr;
}

}  // namespace computer_graphics
