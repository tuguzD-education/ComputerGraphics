#pragma once

#ifndef VENUS_HPP_INCLUDED
#define VENUS_HPP_INCLUDED

#include <computer_graphics/collision.hpp>
#include <computer_graphics/geometric_primitive_component.hpp>

class Venus final : public computer_graphics::SceneComponent, public computer_graphics::Collision {
  public:
    explicit Venus(computer_graphics::Game &game, const Initializer &initializer = {});

    [[nodiscard]] const computer_graphics::GeometricPrimitiveComponent &Mesh() const;
    [[nodiscard]] computer_graphics::GeometricPrimitiveComponent &Mesh();

    [[nodiscard]] bool Intersects(const Collision &other) const override;
    [[nodiscard]] bool Intersects(const computer_graphics::math::Ray &ray, float &dist) const override;

    [[nodiscard]] computer_graphics::BoxCollision CollisionPrimitive() const;

    // void Draw(const computer_graphics::Camera* camera) override;

  private:
    std::reference_wrapper<computer_graphics::GeometricPrimitiveComponent> mesh_;
};

#endif  // VENUS_HPP_INCLUDED
