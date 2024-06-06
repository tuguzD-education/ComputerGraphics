#pragma once

#ifndef SKYBOX_HPP_INCLUDED
#define SKYBOX_HPP_INCLUDED

#include "computer_graphics/box_component.hpp"
#include "computer_graphics/scene_component.hpp"

class Skybox : public computer_graphics::SceneComponent {
  public:
    explicit Skybox(computer_graphics::Game& game, const Initializer& initializer = {});

  private:
    computer_graphics::BoxComponent& front_;
    computer_graphics::BoxComponent& back_;
    computer_graphics::BoxComponent& left_;
    computer_graphics::BoxComponent& right_;
    computer_graphics::BoxComponent& top_;
    computer_graphics::BoxComponent& bottom_;
};

#endif  // SKYBOX_HPP_INCLUDED
