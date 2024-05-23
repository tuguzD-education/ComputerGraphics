#pragma once

#ifndef PONG_PLAYER_HPP_INCLUDED
#define PONG_PLAYER_HPP_INCLUDED

#include <computer_graphics/box_component.hpp>
#include <computer_graphics/game.hpp>
#include <computer_graphics/input_key.hpp>

#include "team.hpp"

class Player final : public computer_graphics::BoxComponent {
  public:
    struct ControlKeys {
        computer_graphics::InputKey up;
        computer_graphics::InputKey down;
    };

    struct Initializer : BoxComponent::Initializer {
        Team team;
        ControlKeys controls;
    };

    explicit Player(computer_graphics::Game &game, const Initializer &initializer = {});

    [[nodiscard]] Team Team() const;
    [[nodiscard]] ControlKeys Controls() const;

    void Reset();

    void Update(float delta_time) override;

  private:
    ::Team team_;
    ControlKeys controls_;

    static computer_graphics::math::Vector3 PositionFrom(::Team team);
};

inline Player::Player(computer_graphics::Game &game, const Initializer &initializer)
    : BoxComponent(game,
                   [&] {
                       Initializer initializer_{initializer};
                       initializer_.length = 0.05f;
                       initializer_.height = 0.3f;
                       initializer_.width = 0.05f;
                       initializer_.transform.position = PositionFrom(initializer.team);
                       return initializer_;
                   }()),
      team_{initializer.team},
      controls_{initializer.controls} {
    if (initializer.name == "component") {
        Name() = "pong_player";
    }
}

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
    const auto y = static_cast<float>(input->IsKeyDown(controls_.up) - input->IsKeyDown(controls_.down));
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
