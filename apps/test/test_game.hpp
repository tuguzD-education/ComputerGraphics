#pragma once

#ifndef TEST_GAME_HPP_INCLUDED
#define TEST_GAME_HPP_INCLUDED

#include "computer_graphics/game.hpp"

class TestGame final : public computer_graphics::Game {
  public:
    explicit TestGame(computer_graphics::Window &window, computer_graphics::InputDevice &input_device);

  protected:
    void Draw() override;

  private:
    void UpdateTitle();
    void UpdateClearColor();

    std::string initial_title_;
};

inline TestGame::TestGame(computer_graphics::Window &window, computer_graphics::InputDevice &input_device)
    : Game(window, input_device) {}

inline void TestGame::Draw() {
    Game::Draw();

    UpdateTitle();
    UpdateClearColor();
}

inline void TestGame::UpdateTitle() {
    float fps = Timer().FramesPerSecond();
    if (fps <= 0) {
        initial_title_ = Window()->Title();
        return;
    }

    std::string title = initial_title_;
    std::format_to(std::back_inserter(title), " (FPS: {})", fps);
    Window()->Title(title);
}

inline void TestGame::UpdateClearColor() {
    const float start_time = Timer().StartTime();
    const float red = start_time - std::floor(start_time);

    ClearColor() = computer_graphics::math::Color{red, 0.1f, 0.1f, 1.0f};
}

#endif  // TEST_GAME_HPP_INCLUDED
