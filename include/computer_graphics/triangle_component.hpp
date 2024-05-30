#pragma once

#ifndef TRIANGLE_COMPONENT_HPP_INCLUDED
#define TRIANGLE_COMPONENT_HPP_INCLUDED

#include <VertexTypes.h>

#include <filesystem>

#include "detail/d3d_ptr.hpp"
#include "light.hpp"
#include "material.hpp"
#include "scene_component.hpp"

namespace computer_graphics {

class TriangleComponent : public SceneComponent {
  public:
    using Vertex = DirectX::VertexPositionNormalColorTexture;
    using Index = std::uint32_t;

    struct Initializer : SceneComponent::Initializer {
        std::span<const Vertex> vertices;
        std::span<const Index> indices;
        bool wireframe = false;

        std::filesystem::path texture_path;
        math::Vector2 tile_count = math::Vector2::One;
        Material material;

        Initializer &Vertices(std::span<const Vertex> vertices);
        Initializer &Indices(std::span<const Index> indices);
        Initializer &Wireframe(bool wireframe);
        Initializer &TexturePath(const std::filesystem::path &texture_path);
        Initializer &TileCount(math::Vector2 tile_count);
        Initializer &Material(const Material &material);
    };

    explicit TriangleComponent(class Game &game, const Initializer &initializer = {});

    void Load(std::span<const Vertex> vertices, std::span<const Index> indices);
    void LoadTexture(const std::filesystem::path &texture_path, math::Vector2 tile_count = math::Vector2::One);

    [[nodiscard]] bool Wireframe() const;
    [[nodiscard]] bool &Wireframe();

    [[nodiscard]] const Material &Material() const;
    [[nodiscard]] class Material &Material();

    void Draw(const Camera *camera) override;

  protected:
    struct alignas(16) VertexShaderConstantBuffer {
        math::Matrix4x4 world;
        math::Matrix4x4 view;
        math::Matrix4x4 projection;
        math::Vector2 tile_count = math::Vector2::One;
    };

    struct alignas(16) PixelShaderConstantBuffer {
        std::uint32_t has_texture = false;
        math::Vector3 view_position;
        class Material material;

        AmbientLight ambient_light;
        DirectionalLight directional_light;
        PointLight point_light;
    };

    virtual void UpdateVertexShaderConstantBuffer(const VertexShaderConstantBuffer &data);
    virtual void UpdatePixelShaderConstantBuffer(const PixelShaderConstantBuffer &data);

    detail::D3DPtr<ID3D11Buffer> index_buffer_;
    detail::D3DPtr<ID3D11Buffer> vertex_buffer_;

    detail::D3DPtr<ID3D11SamplerState> sampler_state_;
    detail::D3DPtr<ID3D11ShaderResourceView> texture_;

    detail::D3DPtr<ID3D11RasterizerState> rasterizer_state_;
    detail::D3DPtr<ID3D11InputLayout> input_layout_;

    detail::D3DPtr<ID3D11Buffer> pixel_shader_constant_buffer_;
    detail::D3DPtr<ID3D11PixelShader> pixel_shader_;
    detail::D3DPtr<ID3DBlob> pixel_byte_code_;

    detail::D3DPtr<ID3D11Buffer> vertex_shader_constant_buffer_;
    detail::D3DPtr<ID3D11VertexShader> vertex_shader_;
    detail::D3DPtr<ID3DBlob> vertex_byte_code_;

    bool wireframe_;
    bool prev_wireframe_;

    math::Vector2 tile_count_;
    class Material material_;

  private:
    void InitializeVertexShader();
    void InitializeVertexShaderConstantBuffer();

    void InitializePixelShader();
    void InitializePixelShaderConstantBuffer();

    void InitializeInputLayout();
    void InitializeRasterizerState();
    void InitializeSamplerState();

    void InitializeVertexBuffer(std::span<const Vertex> vertices);
    void InitializeIndexBuffer(std::span<const Index> indices);
};

}  // namespace computer_graphics

#endif  // TRIANGLE_COMPONENT_HPP_INCLUDED
