#pragma once

#ifndef COLLISION_HPP_INCLUDED
#define COLLISION_HPP_INCLUDED

#include "math.hpp"

namespace computer_graphics {

class Collision {
  public:
    virtual ~Collision();

    [[nodiscard]] virtual bool Intersects(const Collision &other) const = 0;
    [[nodiscard]] virtual bool Intersects(const math::Ray &ray, float &dist) const = 0;
};

class BoxCollision final : public Collision {
public:
    using PrimitiveType = math::Box;

    explicit BoxCollision(const PrimitiveType &primitive);

    [[nodiscard]] const PrimitiveType &Primitive() const;
    [[nodiscard]] PrimitiveType &Primitive();

    [[nodiscard]] bool Intersects(const Collision &other) const override;
    [[nodiscard]] bool Intersects(const math::Ray &ray, float &dist) const override;

private:
    PrimitiveType box_;
};

}  // namespace computer_graphics

#endif  // COLLISION_HPP_INCLUDED
