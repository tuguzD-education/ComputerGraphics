#pragma once

#ifndef BOX_COMPONENT_HPP_INCLUDED
#define BOX_COMPONENT_HPP_INCLUDED

#include "collision.hpp"
#include "triangle_component.hpp"

namespace computer_graphics {

class BoxComponent : public TriangleComponent, public Collision {
  public:
    struct Initializer : TriangleComponent::Initializer {
        float length = 1.0f;
        float height = 1.0f;
        float width = 1.0f;
        math::Color color{math::colors::linear::White};

        Initializer& Length(float length);
        Initializer& Height(float height);
        Initializer& Width(float width);
        Initializer& Color(math::Color color);
    };

    explicit BoxComponent(class Game& game, const Initializer& initializer = {});

    [[nodiscard]] float Length() const;
    [[nodiscard]] float Height() const;
    [[nodiscard]] float Width() const;

    [[nodiscard]] bool Intersects(const Collision& other) const override;
    [[nodiscard]] bool Intersects(const math::Ray& ray, float& dist) const override;

  private:
    [[nodiscard]] BoxCollision CollisionPrimitive() const;

    float length_;
    float height_;
    float width_;
};

}  // namespace computer_graphics

#endif  // BOX_COMPONENT_HPP_INCLUDED
