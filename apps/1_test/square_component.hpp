#pragma once

#ifndef SQUARE_COMPONENT_HPP_INCLUDED
#define SQUARE_COMPONENT_HPP_INCLUDED

#include <array>
#include <computer_graphics/triangle_component.hpp>

class SquareComponent final : public computer_graphics::TriangleComponent {
  public:
    explicit SquareComponent(computer_graphics::Game &game);
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

inline SquareComponent::SquareComponent(computer_graphics::Game &game)
    : TriangleComponent(game, Initializer{.vertices = detail::vertices, .indices = detail::indices}) {}

#endif  // SQUARE_COMPONENT_HPP_INCLUDED
