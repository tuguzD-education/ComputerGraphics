#pragma once

#ifndef PONG_PLAYER_HPP_INCLUDED
#define PONG_PLAYER_HPP_INCLUDED

#include <computer_graphics/box_component.hpp>
#include <computer_graphics/input_key.hpp>
#include <computer_graphics/game.hpp>

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
    [[nodiscard]] ControlKeys Controls() const;

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
: BoxComponent(game, [&] {
                   Initializer initializer{
                       .length = 0.05f, .height = 0.3f,
                       .width = 0.05f, .color = color
                   };
                   initializer.Transform({.position = PositionFrom(team)});
                   return initializer;
               }()),
      team_{team}, controls_{controls} {}

inline Team Player::Team() const {
    return team_;
}

inline Player::ControlKeys Player::Controls() const {
    return controls_;
}

inline void Player::Reset() {
    Transform().position = PositionFrom(team_);
}

inline void Player::Update(const float delta_time) {
    namespace math = computer_graphics::math;

    const auto *input = Game().Input();
    if (input == nullptr) return;

    auto &position = Transform().position;
    const auto y = static_cast<float>(
        input->IsKeyDown(controls_.up) - input->IsKeyDown(controls_.down));
    const math::Vector3 movement = math::Vector3::Up * y;
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
            return {};
    }
}

#endif  // PONG_PLAYER_HPP_INCLUDED
