#pragma once

#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <computer_graphics/box_component.hpp>
#include <computer_graphics/input_key.hpp>

#include "team.hpp"

class Player final : public computer_graphics::BoxComponent {
  public:
    struct ControlKeys {
        computer_graphics::InputKey up;
        computer_graphics::InputKey down;
    };

    explicit Player(
        computer_graphics::Game &game, computer_graphics::math::Color color, Team team, ControlKeys controls);

    [[nodiscard]] Team Team() const;

    void Reset();

    void Update(float delta_time) override;

  private:
    ::Team team_;
    ControlKeys controls_;

    static computer_graphics::math::Vector3 PositionFrom(::Team team);
};

inline Player::Player(
    computer_graphics::Game &game, const computer_graphics::math::Color color,
    const ::Team team, const ControlKeys controls)
    : BoxComponent(game, 0.05f, 0.3f, color, PositionFrom(team)),
      team_{team}, controls_{controls} {}

inline void Player::Reset() {
    Position() = PositionFrom(team_);
}

inline Team Player::Team() const {
    return team_;
}

inline void Player::Update(const float delta_time) {
    const auto *input = Input();
    if (input == nullptr) return;

    auto &position = Position();
    const auto y = static_cast<float>(
        input->IsKeyDown(controls_.up) - input->IsKeyDown(controls_.down));
    const computer_graphics::math::Vector3 movement = computer_graphics::math::Vector3::Up * y;
    constexpr float speed = 2.0f;
    position += speed * movement * delta_time;

    if (position.y > 0.85f) {
        position.y = 0.85f;
    } else if (position.y < -0.85f) {
        position.y = -0.85f;
    }
}

inline computer_graphics::math::Vector3 Player::PositionFrom(const ::Team team) {
    switch (team) {
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
