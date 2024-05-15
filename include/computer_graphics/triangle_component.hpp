#pragma once

#ifndef TRIANGLE_COMPONENT_HPP_INCLUDED
#define TRIANGLE_COMPONENT_HPP_INCLUDED

#include <VertexTypes.h>

#include <span>

#include "component.hpp"
#include "detail/d3d_ptr.hpp"

namespace computer_graphics {

class TriangleComponent : public Component {
  public:
    using Vertex = DirectX::VertexPositionColor;
    using Index = int;

    explicit TriangleComponent(
        Game &game, std::span<Vertex> vertices, std::span<Index> indices, math::Vector3 position = {});

    [[nodiscard]] const math::Vector3 &Position() const;
    [[nodiscard]] math::Vector3 &Position();

    void Update(float delta_time) override;
    void Draw() override;

  private:
    void InitializeVertexShader();
    void InitializeIndexShader();
    void InitializeInputLayout();
    void InitializeRasterizerState();
    void InitializeVertexBuffer(std::span<Vertex> vertices);
    void InitializeIndexBuffer(std::span<Index> indices);
    void InitializeConstantBuffer(math::Vector3 position);

    detail::D3DPtr<ID3D11RasterizerState> rasterizer_state_;
    detail::D3DPtr<ID3D11InputLayout> input_layout_;

    detail::D3DPtr<ID3D11Buffer> constant_buffer_;
    math::Vector3 position_;

    detail::D3DPtr<ID3D11Buffer> index_buffer_;
    detail::D3DPtr<ID3D11PixelShader> index_shader_;
    detail::D3DPtr<ID3DBlob> index_byte_code_;

    detail::D3DPtr<ID3D11Buffer> vertex_buffer_;
    detail::D3DPtr<ID3D11VertexShader> vertex_shader_;
    detail::D3DPtr<ID3DBlob> vertex_byte_code_;
};

}  // namespace computer_graphics

#endif  // TRIANGLE_COMPONENT_HPP_INCLUDED
