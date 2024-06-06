#pragma once

#ifndef MARS_HPP_INCLUDED
#define MARS_HPP_INCLUDED

#include <computer_graphics/collision.hpp>
#include <computer_graphics/geometric_primitive_component.hpp>

class Mars final : public computer_graphics::SceneComponent, public computer_graphics::Collision {
  public:
    explicit Mars(computer_graphics::Game &game, const Initializer &initializer = {});

    [[nodiscard]] const computer_graphics::GeometricPrimitiveComponent &Mesh() const;
    [[nodiscard]] computer_graphics::GeometricPrimitiveComponent &Mesh();

    [[nodiscard]] bool Intersects(const Collision &other) const override;
    [[nodiscard]] bool Intersects(const computer_graphics::math::Ray &ray, float &dist) const override;

    [[nodiscard]] computer_graphics::SphereCollision CollisionPrimitive() const;

  private:
    std::reference_wrapper<computer_graphics::GeometricPrimitiveComponent> mesh_;
};

#endif  // MARS_HPP_INCLUDED
