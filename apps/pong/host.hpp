#pragma once

#ifndef HOST_HPP_INCLUDED
#define HOST_HPP_INCLUDED

#include <iostream>

class Host : public computer_graphics::Component {
  public:
    explicit Host(computer_graphics::Game& game);

    void Update(float delta_time) override;
    void Draw() override;

  private:
    std::size_t left_score_;
    std::size_t right_score_;
};

Host::Host(computer_graphics::Game& game) : Component(game), left_score_{}, right_score_{} {}

void Host::Update(float delta_time) {
    Ball* ball = nullptr;
    for (auto& component : Components()) {
        if (ball == nullptr) ball = dynamic_cast<Ball*>(component.get());
    }
    if (ball == nullptr) return;

    const auto& position = ball->Position();
    if (position.x < -1.0f) {
        right_score_++;
    } else if (position.x > 1.0f) {
        left_score_++;
    } else
        return;

    ball->Reset();
    std::cout << "Score:"
              << "\n\tLeft: " << left_score_
              << "\n\tRight: " << right_score_
              << std::endl;
}

void Host::Draw() {}

#endif  // HOST_HPP_INCLUDED
