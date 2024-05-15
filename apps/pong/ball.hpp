#pragma once

#ifndef BALL_HPP_INCLUDED
#define BALL_HPP_INCLUDED

#include <random>

#include "player.hpp"

class Ball : public computer_graphics::BoxComponent {
  public:
    explicit Ball(computer_graphics::Game &game);

    void Reset();

    void Update(float delta_time) override;

  private:
    [[nodiscard]] static computer_graphics::math::Vector3 RandomVelocity();

    computer_graphics::math::Vector3 velocity_;
};

Ball::Ball(computer_graphics::Game &game)
    : BoxComponent(game, 0.05f, 0.05f,
        computer_graphics::math::Color{1.0f, 1.0f, 1.0f}), velocity_{RandomVelocity()} {}

void Ball::Reset() {
    Position() = computer_graphics::math::Vector3{};
    velocity_ = RandomVelocity();
}

void Ball::Update(float delta_time) {
    computer_graphics::math::Vector3 normal;
    velocity_.Normalize(normal);
    velocity_ += normal * (0.25f * delta_time);

    auto &position = Position();
    if (std::abs(position.y) > 0.975f) {
        velocity_.y = -velocity_.y;
    }

    for (const auto &component : Components()) {
        auto player = dynamic_cast<const Player *>(component.get());
        if (player == nullptr) {
            continue;
        }

        Box box = Collision();
        Box player_box = player->Collision();
        if (box.Intersects(player_box)) {
            velocity_.x = -velocity_.x;
        }
    }

    position += velocity_ * delta_time;
}

computer_graphics::math::Vector3 Ball::RandomVelocity() {
    static std::random_device device;
    static std::default_random_engine engine{device()};
    static std::uniform_real_distribution distribution{-1.0f, 1.0f};

    float x = distribution(engine);
    x += (x < 0) ? -1 : 1;
    float y = distribution(engine);
    computer_graphics::math::Vector3 vector{x, y, 0.0f};
    vector.Normalize();
    return vector;
}

#endif  // BALL_HPP_INCLUDED
