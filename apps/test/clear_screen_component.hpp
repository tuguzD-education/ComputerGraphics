#pragma once

#ifndef CLEAR_SCREEN_COMPONENT_HPP_INCLUDED
#define CLEAR_SCREEN_COMPONENT_HPP_INCLUDED

#include "computer_graphics/component.hpp"

class ClearScreenComponent : public computer_graphics::Component {
  public:
    explicit ClearScreenComponent(computer_graphics::Game &game);

    void Update(float delta_time) override;
    void Draw() override;
};

ClearScreenComponent::ClearScreenComponent(computer_graphics::Game &game) : Component(game) {}

void ClearScreenComponent::Update(float delta_time) {}

void ClearScreenComponent::Draw() {
    float start_time = Timer().StartTime();
    float red = start_time - std::floor(start_time);

    ClearColor() = computer_graphics::math::Color{red, 0.1f, 0.1f, 1.0f};
}

#endif  // CLEAR_SCREEN_COMPONENT_HPP_INCLUDED
