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

        bool is_casting_shadow = false;
    };

    explicit TriangleComponent(class Game &game, const Initializer &initializer = {});

    void Load(std::span<const Vertex> vertices, std::span<const Index> indices);
    void LoadTexture(
        const std::filesystem::path &texture_path, math::Vector2 tile_count = math::Vector2::One);

    [[nodiscard]] bool Wireframe() const;
    [[nodiscard]] bool &Wireframe();

    [[nodiscard]] bool IsCastingShadow() const;
    [[nodiscard]] bool &IsCastingShadow();

    [[nodiscard]] const Material &Material() const;
    [[nodiscard]] class Material &Material();

    virtual void DrawInShadowMap(const Camera *camera);
    void Draw(const Camera *camera) override;

  protected:
    struct alignas(16) VertexShaderConstantBuffer {
        math::Matrix4x4 world;
        math::Matrix4x4 view;
        math::Matrix4x4 projection;

        math::Matrix4x4 directional_light_shadow_map_view_projection;
        alignas(16) math::Vector2 tile_count = math::Vector2::One;
    };

    struct alignas(16) PixelShaderConstantBuffer {
        std::uint32_t has_texture = false;
        math::Vector3 view_position;
        class Material material;

        DirectionalLight directional_light;
        PointLight point_light;
    };

    virtual void UpdateVertexShaderConstantBuffer(const VertexShaderConstantBuffer &data);
    virtual void UpdatePixelShaderConstantBuffer(const PixelShaderConstantBuffer &data);

    detail::D3DPtr<ID3D11Buffer> index_buffer_;
    detail::D3DPtr<ID3D11Buffer> vertex_buffer_;

    detail::D3DPtr<ID3D11SamplerState> texture_sampler_state_;
    detail::D3DPtr<ID3D11ShaderResourceView> texture_;

    detail::D3DPtr<ID3D11RasterizerState> shadow_map_rasterizer_state_;
    detail::D3DPtr<ID3D11RasterizerState> rasterizer_state_;
    detail::D3DPtr<ID3D11InputLayout> input_layout_;

    detail::D3DPtr<ID3D11PixelShader> shadow_map_pixel_shader_;
    detail::D3DPtr<ID3DBlob> shadow_map_pixel_shader_byte_code_;

    detail::D3DPtr<ID3D11VertexShader> shadow_map_vertex_shader_;
    detail::D3DPtr<ID3DBlob> shadow_map_vertex_shader_byte_code_;

    detail::D3DPtr<ID3D11Buffer> pixel_shader_constant_buffer_;
    detail::D3DPtr<ID3D11PixelShader> pixel_shader_;
    detail::D3DPtr<ID3DBlob> pixel_shader_byte_code_;

    detail::D3DPtr<ID3D11Buffer> vertex_shader_constant_buffer_;
    detail::D3DPtr<ID3D11VertexShader> vertex_shader_;
    detail::D3DPtr<ID3DBlob> vertex_shader_byte_code_;

    math::Matrix4x4 directional_light_shadow_map_view_projection_;

    bool wireframe_;
    bool prev_wireframe_;

    math::Vector2 tile_count_;
    class Material material_;

    bool is_casting_shadow_;

  private:
    void InitializeVertexShader();
    void InitializeVertexShaderConstantBuffer();

    void InitializePixelShader();
    void InitializePixelShaderConstantBuffer();

    void InitializeShadowMapVertexShader();
    void InitializeShadowMapPixelShader();
    void InitializeShadowMapRasterizerState();

    void InitializeInputLayout();
    void InitializeRasterizerState();
    void InitializeTextureSamplerState();

    void InitializeVertexBuffer(std::span<const Vertex> vertices);
    void InitializeIndexBuffer(std::span<const Index> indices);
};

}  // namespace computer_graphics

#endif  // TRIANGLE_COMPONENT_HPP_INCLUDED
