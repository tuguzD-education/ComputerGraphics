#pragma once

#ifndef SUN_HPP_INCLUDED
#define SUN_HPP_INCLUDED

#include <computer_graphics/box_component.hpp>
#include <computer_graphics/collision.hpp>

class Sun final : public computer_graphics::SceneComponent, public computer_graphics::Collision {
  public:
    explicit Sun(computer_graphics::Game &game, const Initializer &initializer = {});

    [[nodiscard]] const computer_graphics::BoxComponent &Mesh() const;
    [[nodiscard]] computer_graphics::BoxComponent &Mesh();

    [[nodiscard]] bool Intersects(const Collision &other) const override;
    [[nodiscard]] bool Intersects(const computer_graphics::math::Ray &ray, float &dist) const override;

  private:
    [[nodiscard]] computer_graphics::BoxCollision CollisionPrimitive() const;

    std::reference_wrapper<computer_graphics::BoxComponent> mesh_;
};

#endif  // SUN_HPP_INCLUDED
