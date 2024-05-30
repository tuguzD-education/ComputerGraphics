#pragma once

#ifndef URANUS_RING_HPP_INCLUDED
#define URANUS_RING_HPP_INCLUDED

#include <computer_graphics/geometric_primitive_component.hpp>

class UranusRing final : public computer_graphics::SceneComponent {
  public:
    explicit UranusRing(computer_graphics::Game &game, const Initializer &initializer = {});

    [[nodiscard]] const computer_graphics::GeometricPrimitiveComponent &Mesh() const;
    [[nodiscard]] computer_graphics::GeometricPrimitiveComponent &Mesh();

  private:
    std::reference_wrapper<computer_graphics::GeometricPrimitiveComponent> mesh_;
};

#endif  // URANUS_RING_HPP_INCLUDED
