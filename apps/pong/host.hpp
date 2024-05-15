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
    std::size_t red_score_;
    std::size_t blue_score_;
};

Host::Host(computer_graphics::Game& game) : Component(game), red_score_{}, blue_score_{} {}

void Host::Update(float delta_time) {
    Ball* ball = nullptr;
    for (auto& component : Components()) {
        if (ball == nullptr) ball = dynamic_cast<Ball*>(component.get());
    }
    if (ball == nullptr) return;

    const auto& position = ball->Position();
    if (position.x < -1.0f) {
        blue_score_++;
    } else if (position.x > 1.0f) {
        red_score_++;
    } else
        return;

    ball->Reset();
    std::cout << "Score:"
              << "\n\tRed: " << red_score_
              << "\n\tBlue: " << blue_score_
              << std::endl;
}

void Host::Draw() {
    computer_graphics::Window *window = Window();
    if (window == nullptr) {
        return;
    }

    std::string title = "PONG ";
    std::format_to(std::back_inserter(title),
        "[ Red: {} | Blue: {} ]", red_score_, blue_score_);
    window->Title(title);
}

#endif  // HOST_HPP_INCLUDED
