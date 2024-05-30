#pragma once

#ifndef SATURN_RING_HPP_INCLUDED
#define SATURN_RING_HPP_INCLUDED

#include <computer_graphics/geometric_primitive_component.hpp>

class SaturnRing final : public computer_graphics::SceneComponent {
  public:
    explicit SaturnRing(computer_graphics::Game &game, const Initializer &initializer = {});

    [[nodiscard]] const computer_graphics::GeometricPrimitiveComponent &Mesh() const;
    [[nodiscard]] computer_graphics::GeometricPrimitiveComponent &Mesh();

  private:
    std::reference_wrapper<computer_graphics::GeometricPrimitiveComponent> mesh_;
};

#endif  // SATURN_RING_HPP_INCLUDED
