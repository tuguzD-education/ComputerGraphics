#pragma once

#ifndef BOX_COMPONENT_HPP_INCLUDED
#define BOX_COMPONENT_HPP_INCLUDED

#include <DirectXCollision.h>

#include "triangle_component.hpp"

namespace computer_graphics {

class BoxComponent : public TriangleComponent {
  public:
    using Box = DirectX::BoundingBox;

    explicit BoxComponent(
        Game &game, float width, float height, math::Color color, math::Vector3 position = {});

    [[nodiscard]] float Width() const;
    [[nodiscard]] float Height() const;
    [[nodiscard]] Box Collision() const;

  private:
    float width_;
    float height_;
};

}  // namespace computer_graphics

#endif  // BOX_COMPONENT_HPP_INCLUDED
