#pragma once

#ifndef WINDOW_TITLE_COMPONENT_HPP_INCLUDED
#define WINDOW_TITLE_COMPONENT_HPP_INCLUDED

#include <computer_graphics/triangle_component.hpp>

class WindowTitleComponent : public computer_graphics::Component {
  public:
    explicit WindowTitleComponent(computer_graphics::Game &game);

    void Update(float delta_time) override;
    void Draw() override;

  private:
    std::string initial_title_;
};

WindowTitleComponent::WindowTitleComponent(computer_graphics::Game &game) : Component(game) {}

void WindowTitleComponent::Update(float delta_time) {}

void WindowTitleComponent::Draw() {
    computer_graphics::Window *window = Window();
    if (window == nullptr) {
        return;
    }

    float fps = Timer().FramesPerSecond();
    if (fps <= 0) {
        initial_title_ = window->Title();
        return;
    }

    std::string title = initial_title_;
    std::format_to(std::back_inserter(title), " (FPS: {})", fps);
    window->Title(title);
}

#endif  // WINDOW_TITLE_COMPONENT_HPP_INCLUDED
