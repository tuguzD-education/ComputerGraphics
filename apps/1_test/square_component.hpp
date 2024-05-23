#pragma once

#ifndef SQUARE_COMPONENT_HPP_INCLUDED
#define SQUARE_COMPONENT_HPP_INCLUDED

#include <array>
#include <computer_graphics/triangle_component.hpp>

class SquareComponent final : public computer_graphics::TriangleComponent {
  public:
    explicit SquareComponent(computer_graphics::Game &game, const Initializer &initializer = {});
};

namespace detail {

const std::array vertices{
    computer_graphics::TriangleComponent::Vertex{
        computer_graphics::math::Vector3{0.5f, 0.5f, 0.0f},
        computer_graphics::math::Vector3{0.0f, 0.0f, 1.0f},
        computer_graphics::math::colors::linear::Red,
        computer_graphics::math::Vector2{1.0f, 0.0f},
    },
    computer_graphics::TriangleComponent::Vertex{
        computer_graphics::math::Vector3{-0.5f, -0.5f, 0.0f},
        computer_graphics::math::Vector3{0.0f, 0.0f, 1.0f},
        computer_graphics::math::colors::linear::Blue,
        computer_graphics::math::Vector2{0.0f, 1.0f},
    },
    computer_graphics::TriangleComponent::Vertex{
        computer_graphics::math::Vector3{0.5f, -0.5f, 0.0f},
        computer_graphics::math::Vector3{0.0f, 0.0f, 1.0f},
        computer_graphics::math::colors::linear::Lime,
        computer_graphics::math::Vector2{1.0f, 1.0f},
    },
    computer_graphics::TriangleComponent::Vertex{
        computer_graphics::math::Vector3{-0.5f, 0.5f, 0.0f},
        computer_graphics::math::Vector3{0.0f, 0.0f, 1.0f},
        computer_graphics::math::colors::linear::White,
        computer_graphics::math::Vector2{0.0f, 0.0f},
    },
};

constexpr std::array<SquareComponent::Index, 6> indices{0, 1, 2, 1, 0, 3};

}  // namespace detail

inline SquareComponent::SquareComponent(computer_graphics::Game &game, const Initializer &initializer)
    : TriangleComponent(game, [initializer] {
          Initializer new_initializer{initializer};
          new_initializer.vertices = detail::vertices;
          new_initializer.indices = detail::indices;
          return new_initializer;
      }()) {
    if (initializer.name == "component") {
        Name() = "square_component";
    }
}

#endif  // SQUARE_COMPONENT_HPP_INCLUDED
