#pragma once

#ifndef PONG_GAME_HPP_INCLUDED
#define PONG_GAME_HPP_INCLUDED

#include <computer_graphics/game.hpp>
#include <iostream>

#include "ball.hpp"
#include "field.hpp"

class Game final : public computer_graphics::Game {
  public:
    explicit Game(computer_graphics::Window &window, computer_graphics::Input &input);

  protected:
    void Update(float delta_time) override;
    void Draw() override;

  private:
    void OnKeyDown(computer_graphics::InputKey key);

    std::reference_wrapper<Field> field_;

    std::string initial_title_;
    std::size_t red_score_;
    std::size_t blue_score_;

    Ball &ball_;
    Player &red_player_;
    Player &blue_player_;

    Player *won_player = nullptr;
};

inline Game::Game(computer_graphics::Window &window, computer_graphics::Input &input)
    : computer_graphics::Game(window, input),
      field_{AddComponent<Field>()},
      initial_title_{window.Title()},
      red_score_{},
      blue_score_{},
      ball_{AddComponent<Ball>([] {
          Ball::Initializer initializer{};
          initializer.name = "white_ball";
          return initializer;
      }())},
      red_player_{AddComponent<Player>([] {
          Player::Initializer initializer{};
          initializer.name = "red_player";
          initializer.color = computer_graphics::math::colors::linear::Red;
          initializer.team = Team::Red;
          initializer.controls = Player::ControlKeys{
              .up = computer_graphics::InputKey::W,
              .down = computer_graphics::InputKey::S,
          };
          return initializer;
      }())},
      blue_player_{AddComponent<Player>([] {
          Player::Initializer initializer{};
          initializer.name = "blue_player";
          initializer.color = computer_graphics::math::colors::linear::Blue;
          initializer.team = Team::Blue;
          initializer.controls = Player::ControlKeys{
              .up = computer_graphics::InputKey::Up,
              .down = computer_graphics::InputKey::Down,
          };
          return initializer;
      }())} {
    input.OnInputKeyDown().AddRaw(this, &Game::OnKeyDown);
}

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

    std::string title = initial_title_;
    std::format_to(std::back_inserter(title), " [ Red: {} | Blue: {} ]", red_score_, blue_score_);
    Window()->Title(title);
}

// ReSharper disable once CppParameterMayBeConst
inline void Game::OnKeyDown(computer_graphics::InputKey key) {
    if (key == computer_graphics::InputKey::Escape) Exit();
}

#endif  // PONG_GAME_HPP_INCLUDED
