#pragma once

#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <computer_graphics/box_component.hpp>
#include <computer_graphics/input_key.hpp>

#include "direction.hpp"

class Player : public computer_graphics::BoxComponent {
  public:
    struct ControlKeys {
        computer_graphics::InputKey up;
        computer_graphics::InputKey down;
    };

    explicit Player(computer_graphics::Game &game, Direction direction, ControlKeys controls);

    [[nodiscard]] Direction Direction() const;
    [[nodiscard]] ControlKeys Controls() const;

    void Update(float delta_time) override;

  private:
    ::Direction direction_;
    ControlKeys controls_;

    static computer_graphics::math::Vector3 PositionFrom(::Direction direction);
};

Player::Player(computer_graphics::Game &game, ::Direction direction, ControlKeys controls)
    : BoxComponent(game, 0.05f, 0.3f,
        computer_graphics::math::Color{1.0f, 1.0f, 1.0f}, PositionFrom(direction)),
      direction_{direction},
      controls_{controls} {}

Direction Player::Direction() const {
    return direction_;
}

Player::ControlKeys Player::Controls() const {
    return controls_;
}

void Player::Update(float delta_time) {
    auto *input_device = InputDevice();
    if (input_device == nullptr) {
        return;
    }

    auto &position = Position();
    if (input_device->IsKeyDown(controls_.up)) {
        position += computer_graphics::math::Vector3::Up * (2.0f * delta_time);
    }
    if (input_device->IsKeyDown(controls_.down)) {
        position += computer_graphics::math::Vector3::Down * (2.0f * delta_time);
    }

    if (position.y > 0.85f) {
        position.y = 0.85f;
    } else if (position.y < -0.85f) {
        position.y = -0.85f;
    }
}

computer_graphics::math::Vector3 Player::PositionFrom(::Direction direction) {
    switch (direction) {
        case Direction::Left: {
            return {-0.9f, 0.0f, 0.0f};
        }
        case Direction::Right: {
            return {0.9f, 0.0f, 0.0f};
        }
    }
}

#endif  // PLAYER_HPP_INCLUDED
