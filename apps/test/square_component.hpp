#pragma once

#ifndef SQUARE_COMPONENT_HPP_INCLUDED
#define SQUARE_COMPONENT_HPP_INCLUDED

#include <array>

#include <computer_graphics/triangle_component.hpp>

class SquareComponent : public computer_graphics::TriangleComponent {
  public:
    explicit SquareComponent(computer_graphics::Game &game);

  private:
    static std::array<Vertex, 4> vertices;
    static std::array<Index, 6> indices;
};

SquareComponent::SquareComponent(computer_graphics::Game &game) : TriangleComponent{game, vertices, indices} {}

std::array<SquareComponent::Vertex, 4> SquareComponent::vertices{
    Vertex{
        computer_graphics::math::Vector3{0.5f, 0.5f, 0.0f},
        computer_graphics::math::Color{1.0f, 0.0f, 0.0f, 1.0f},
    },
    Vertex{
        computer_graphics::math::Vector3{-0.5f, -0.5f, 0.0f},
        computer_graphics::math::Color{0.0f, 0.0f, 1.0f, 1.0f},
    },
    Vertex{
        computer_graphics::math::Vector3{0.5f, -0.5f, 0.0f},
        computer_graphics::math::Color{0.0f, 1.0f, 0.0f, 1.0f},
    },
    Vertex{
        computer_graphics::math::Vector3{-0.5f, 0.5f, 0.0f},
        computer_graphics::math::Color{1.0f, 1.0f, 1.0f, 1.0f},
    },
};

std::array<SquareComponent::Index, 6> SquareComponent::indices{0, 1, 2, 1, 0, 3};

#endif  // SQUARE_COMPONENT_HPP_INCLUDED
