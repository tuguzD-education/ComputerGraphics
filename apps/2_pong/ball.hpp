#pragma once

#ifndef BALL_HPP_INCLUDED
#define BALL_HPP_INCLUDED

#include <computer_graphics/box_component.hpp>
#include <computer_graphics/game.hpp>
#include <random>

#include "player.hpp"

class Ball final : public computer_graphics::BoxComponent {
  public:
    explicit Ball(computer_graphics::Game &game);

    void Reset(const Player *won_player = nullptr);

    void Update(float delta_time) override;

  private:
    [[nodiscard]] static computer_graphics::math::Vector3 RandomVelocity(const Player *won_player = nullptr);

    computer_graphics::math::Vector3 velocity_;
};

inline Ball::Ball(computer_graphics::Game &game) : BoxComponent(
    game, Initializer{.length = 0.05f, .height = 0.05f, .width = 0.05f}), velocity_{RandomVelocity()} {}

inline void Ball::Reset(const Player *won_player) {
    Transform().position = computer_graphics::math::Vector3{};
    velocity_ = RandomVelocity(won_player);
}

inline void Ball::Update(const float delta_time) {
    velocity_ += computer_graphics::math::Normalize(velocity_) * (0.25f * delta_time);

    auto &position = Transform().position;
    if (std::abs(position.y) > 0.975f) {
        velocity_.y = -velocity_.y;
    }

    for (const auto &component : Game().Components()) {
        const auto player = dynamic_cast<const Player *>(&component.get());
        if (player == nullptr) continue;

        if (player->Intersects(*this)) {
            velocity_.x = -velocity_.x;
        }
    }

    position += velocity_ * delta_time;
}

inline computer_graphics::math::Vector3 Ball::RandomVelocity(const Player *won_player) {
    static std::random_device device;
    static std::default_random_engine engine{device()};
    static std::uniform_real_distribution distribution{-1.0f, 1.0f};

    namespace math = computer_graphics::math;

    const float temp = distribution(engine);
    float x = temp + (temp > 0.0f ? 1.0f : -1.0f);
    const float y = distribution(engine);

    if (won_player != nullptr) {
        if (won_player->Team() == Team::Blue) {
            x = std::abs(x);
        } else if (won_player->Team() == Team::Red) {
            x = -std::abs(x);
        }
    }

    return math::Normalize(math::Vector3{x, y, 0.0f});
}

#endif  // BALL_HPP_INCLUDED
