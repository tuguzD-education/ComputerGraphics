#pragma once

#ifndef FIELD_HPP_INCLUDED
#define FIELD_HPP_INCLUDED

#include <computer_graphics/box_component.hpp>

class Field final : public computer_graphics::BoxComponent {
  public:
    explicit Field(computer_graphics::Game& game);
};

inline Field::Field(computer_graphics::Game& game)
    : BoxComponent(game, [] {
        Initializer initializer{
            .length = 150.0f,
            .height = 0.0f,
            .width = 150.0f,
        };
        initializer.texture_path = "resources/textures/chess.jpg";
        initializer.tile_count = computer_graphics::math::Vector2::One * 150.0f;
        initializer.material.specular = computer_graphics::math::colors::linear::White * 0.25f;
        return initializer;
    }()) {}

#endif  // FIELD_HPP_INCLUDED
