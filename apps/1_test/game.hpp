#pragma once

#ifndef TEST_GAME_HPP_INCLUDED
#define TEST_GAME_HPP_INCLUDED

#include <computer_graphics/game.hpp>
#include <iostream>

class Game final : public computer_graphics::Game {
  public:
    explicit Game(computer_graphics::Window &window, computer_graphics::Input &input);
    ~Game() override;

  protected:
    void Draw() override;

  private:
    void OnKeyDown(computer_graphics::InputKey key);

    std::string initial_title_;
};

inline Game::Game(computer_graphics::Window &window, computer_graphics::Input &input)
    : computer_graphics::Game(window, input), initial_title_{window.Title()} {
    input.OnInputKeyDown().AddRaw(this, &Game::OnKeyDown);
}

inline Game::~Game() {
    const auto input = Input();
    if (input == nullptr) return;

    input->OnInputKeyDown().RemoveByOwner(this);
}

inline void Game::Draw() {
    const float start_time = Timer().StartTime();
    const float red = start_time - std::floor(start_time);
    ClearColor() = computer_graphics::math::Color{0.5f - red, 0.5f - red, 0.5f - red, 1.0f};

    const auto window = Window();
    if (float fps = Timer().FramesPerSecond(); window != nullptr && fps > 0) {
        std::string title = initial_title_;
        std::format_to(std::back_inserter(title), " (FPS: {})", fps);
        window->Title(title);
    }

    computer_graphics::Game::Draw();
}

inline void Game::OnKeyDown(computer_graphics::InputKey key) {
    std::cout << "Key: " << static_cast<std::uint16_t>(key) << std::endl;
    if (key == computer_graphics::InputKey::Escape) {
        Exit();
    }
}

#endif  // TEST_GAME_HPP_INCLUDED
