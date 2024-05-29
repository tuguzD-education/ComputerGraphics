#pragma once

#ifndef FIELD_HPP_INCLUDED
#define FIELD_HPP_INCLUDED

#include <computer_graphics/box_component.hpp>

class Background final : public computer_graphics::BoxComponent {
  public:
    explicit Background(computer_graphics::Game& game);
};

inline Background::Background(computer_graphics::Game &game)
    : BoxComponent(game, [] {
          Initializer initializer{
              .length = 2.0f,
              .height = 2.0f,
              .width = 0.0f,
          };
          initializer.texture_path = "resources/textures/labyrinth.jpg";
          initializer.tile_count = computer_graphics::math::Vector2::One * 6.0f;
          return initializer;
      }()) {}

#endif //FIELD_HPP_INCLUDED
