#pragma once

#ifndef COMPONENT_HPP_INCLUDED
#define COMPONENT_HPP_INCLUDED

#include <functional>

#include "game.hpp"

namespace computer_graphics {

class Component {
  public:
    explicit Component(Game &game);
    virtual ~Component();

    virtual void Update(float delta_time) = 0;
    virtual void Draw() = 0;

  protected:
    [[nodiscard]] InputDevice *InputDevice();
    [[nodiscard]] const computer_graphics::InputDevice *InputDevice() const;

    [[nodiscard]] Window *Window();
    [[nodiscard]] const computer_graphics::Window *Window() const;

    [[nodiscard]] ID3D11DeviceContext *DeviceContext();
    [[nodiscard]] const ID3D11DeviceContext *DeviceContext() const;

    [[nodiscard]] ID3D11Device *Device();
    [[nodiscard]] const ID3D11Device *Device() const;

    [[nodiscard]] const math::Color &ClearColor() const;
    [[nodiscard]] math::Color &ClearColor();

    [[nodiscard]] const Timer &Timer() const;

  private:
    std::reference_wrapper<Game> game_;
};

}  // namespace computer_graphics

#endif  // COMPONENT_HPP_INCLUDED
