#pragma once

#ifndef CAMERA_MANAGER_HPP_INCLUDED
#define CAMERA_MANAGER_HPP_INCLUDED

#include "component.hpp"

namespace computer_graphics {

class CameraManager : public Component {
  public:
    struct Initializer : Component::Initializer {};

    explicit CameraManager(class Game &game, const Initializer &initializer = {});

    [[nodiscard]] virtual const Camera *MainCamera() const;
    [[nodiscard]] virtual Camera *MainCamera();
};

}  // namespace computer_graphics

#endif  // CAMERA_MANAGER_HPP_INCLUDED
