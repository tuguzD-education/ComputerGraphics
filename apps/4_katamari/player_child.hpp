#pragma once

#ifndef PLAYER_CHILD_HPP_INCLUDED
#define PLAYER_CHILD_HPP_INCLUDED

#include <computer_graphics/triangle_component.hpp>

class PlayerChild final : public computer_graphics::TriangleComponent {
  public:
    explicit PlayerChild(computer_graphics::Game& game, const Initializer& initializer = {});

  private:
    struct alignas(16) VertexShaderConstantBuffer : TriangleComponent::VertexShaderConstantBuffer {
        float time = 0.0f;
    };

    void ReInitializeVertexShader();
    void ReInitializeVertexShaderConstantBuffer();

    void UpdateVertexShaderConstantBuffer(const TriangleComponent::VertexShaderConstantBuffer& data) override;
};

#endif  // PLAYER_CHILD_HPP_INCLUDED
