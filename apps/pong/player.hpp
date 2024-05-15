#pragma once

#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <computer_graphics/box_component.hpp>
#include <computer_graphics/input_key.hpp>

#include "team.hpp"

class Player : public computer_graphics::BoxComponent {
  public:
    struct ControlKeys {
        computer_graphics::InputKey up;
        computer_graphics::InputKey down;
    };

    explicit Player(computer_graphics::Game &game, computer_graphics::math::Color color, Team team,
                    ControlKeys controls);

    [[nodiscard]] Team Team() const;
    [[nodiscard]] ControlKeys Controls() const;

    void Update(float delta_time) override;

  private:
    ::Team team_;
    ControlKeys controls_;

    static computer_graphics::math::Vector3 PositionFrom(::Team direction);
};

inline Player::Player(
    computer_graphics::Game &game, computer_graphics::math::Color color,
    ::Team team, ControlKeys controls)
    : BoxComponent(game, 0.05f, 0.3f, color, PositionFrom(team)), team_{team}, controls_{controls} {}

inline Team Player::Team() const {
    return team_;
}

inline Player::ControlKeys Player::Controls() const {
    return controls_;
}

inline void Player::Update(float delta_time) {
    auto *input_device = InputDevice();
    if (input_device == nullptr) {
        return;
    }

    auto &position = Position();
    const auto y = static_cast<float>(input_device->IsKeyDown(controls_.up) - input_device->IsKeyDown(controls_.down));
    const computer_graphics::math::Vector3 movement = computer_graphics::math::Vector3::Up * y;
    constexpr float speed = 2.0f;
    position += speed * movement * delta_time;

    if (position.y > 0.85f) {
        position.y = 0.85f;
    } else if (position.y < -0.85f) {
        position.y = -0.85f;
    }
}

inline computer_graphics::math::Vector3 Player::PositionFrom(::Team direction) {
    switch (direction) {
        case Team::Red: {
            return {-0.975f, 0.0f, 0.0f};
        }
        case Team::Blue: {
            return {0.975f, 0.0f, 0.0f};
        }
        default:
            return {0.0f, 0.0f, 0.0f};
    }
}

#endif  // PLAYER_HPP_INCLUDED
