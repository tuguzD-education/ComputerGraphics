#pragma once

#ifndef TRIANGLE_COMPONENT_HPP_INCLUDED
#define TRIANGLE_COMPONENT_HPP_INCLUDED

#include <VertexTypes.h>

#include "detail/d3d_ptr.hpp"
#include "scene_component.hpp"

namespace computer_graphics {

class TriangleComponent : public SceneComponent {
  public:
    using Vertex = DirectX::VertexPositionNormalColorTexture;
    using Index = std::uint32_t;

    struct Initializer : SceneComponent::Initializer {
        std::span<const Vertex> vertices;
        std::span<const Index> indices;

        Initializer &Vertices(std::span<const Vertex> vertices);
        Initializer &Indices(std::span<const Index> indices);
    };

    explicit TriangleComponent(class Game &game, const Initializer &initializer = {});

    void Load(std::span<const Vertex> vertices, std::span<const Index> indices);

    void Draw(const Camera *camera) override;

  protected:
    struct alignas(16) ConstantBuffer {
        math::Matrix4x4 world;
        math::Matrix4x4 view;
        math::Matrix4x4 projection;
    };
    virtual void UpdateConstantBuffer(const ConstantBuffer &data);

    detail::D3DPtr<ID3D11Buffer> index_buffer_;
    detail::D3DPtr<ID3D11Buffer> vertex_buffer_;
    detail::D3DPtr<ID3D11Buffer> constant_buffer_;

    detail::D3DPtr<ID3D11RasterizerState> rasterizer_state_;
    detail::D3DPtr<ID3D11InputLayout> input_layout_;

    detail::D3DPtr<ID3D11PixelShader> pixel_shader_;
    detail::D3DPtr<ID3DBlob> pixel_byte_code_;

    detail::D3DPtr<ID3D11VertexShader> vertex_shader_;
    detail::D3DPtr<ID3DBlob> vertex_byte_code_;

  private:
    void InitializeVertexShader();
    void InitializePixelShader();
    void InitializeConstantBuffer();

    void InitializeInputLayout();
    void InitializeRasterizerState();

    void InitializeVertexBuffer(std::span<const Vertex> vertices);
    void InitializeIndexBuffer(std::span<const Index> indices);
};

}  // namespace computer_graphics

#endif  // TRIANGLE_COMPONENT_HPP_INCLUDED
