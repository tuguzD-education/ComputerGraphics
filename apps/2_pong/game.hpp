#pragma once

#ifndef PONG_GAME_HPP_INCLUDED
#define PONG_GAME_HPP_INCLUDED

#include <computer_graphics/game.hpp>
#include <iostream>

#include "ball.hpp"

class Game final : public computer_graphics::Game {
  public:
    explicit Game(computer_graphics::Window &window, computer_graphics::Input &input);

  protected:
    void Update(float delta_time) override;
    void Draw() override;

  private:
    Ball &ball_;

    Player &red_player_;
    std::size_t red_score_;

    Player &blue_player_;
    std::size_t blue_score_;

    Player *won_player = nullptr;
};

inline Game::Game(computer_graphics::Window &window, computer_graphics::Input &input)
    : computer_graphics::Game(window, input),
      ball_{AddComponent<Ball>()},
      red_player_{AddComponent<Player>(
          computer_graphics::math::colors::srgb::Red.v,
          Team::Red, Player::ControlKeys{
              .up = computer_graphics::InputKey::W,
              .down = computer_graphics::InputKey::S,
          })},
      red_score_{},
      blue_player_{AddComponent<Player>(
          computer_graphics::math::colors::srgb::Blue.v, Team::Blue,
          Player::ControlKeys{
              .up = computer_graphics::InputKey::Up,
              .down = computer_graphics::InputKey::Down,
          })},
      blue_score_{} {}

inline void Game::Update(const float delta_time) {
    computer_graphics::Game::Update(delta_time);

    if (const auto &x = ball_.Transform().position.x; x < -0.975f) {
        std::cout << "One point to the BLUE!";
        won_player = &blue_player_;
        blue_score_++;
    } else if (x > 0.975f) {
        std::cout << "One point to the RED!";
        won_player = &red_player_;
        red_score_++;
    } else
        return;

    ball_.Reset(won_player);
    red_player_.Reset();
    blue_player_.Reset();

    std::cout << "\n\tRED:  " << red_score_ << "\n\tBLUE: " << blue_score_ << "\n\n";
}

inline void Game::Draw() {
    computer_graphics::Game::Draw();

    std::string title = "PONG ";
    std::format_to(
        std::back_inserter(title), "[ Red: {} | Blue: {} ]", red_score_, blue_score_);
    Window()->Title(title);
}

#endif  // PONG_GAME_HPP_INCLUDED
