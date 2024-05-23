#include "computer_graphics/triangle_component.hpp"

#include <d3dcompiler.h>

#include <array>

#include "computer_graphics/camera.hpp"
#include "computer_graphics/detail/check_result.hpp"
#include "computer_graphics/detail/shader.hpp"
#include "computer_graphics/game.hpp"

namespace computer_graphics {

auto TriangleComponent::Initializer::Vertices(const std::span<const Vertex> vertices) -> Initializer & {
    this->vertices = vertices;
    return *this;
}

auto TriangleComponent::Initializer::Indices(const std::span<const Index> indices) -> Initializer & {
    this->indices = indices;
    return *this;
}

TriangleComponent::TriangleComponent(class Game &game, const Initializer &initializer)
    : SceneComponent(game, initializer) {
    InitializeVertexShader();
    InitializeConstantBuffer();
    InitializePixelShader();

    InitializeInputLayout();
    InitializeRasterizerState();

    Load(initializer.vertices, initializer.indices);

    if (initializer.name == "component") {
        Name() = "triangle_component";
    }
}

void TriangleComponent::Load(const std::span<const Vertex> vertices, const std::span<const Index> indices) {
    InitializeVertexBuffer(vertices);
    InitializeIndexBuffer(indices);
}

void TriangleComponent::Draw(const Camera *camera) {
    if (vertex_buffer_ == nullptr || index_buffer_ == nullptr) {
        return;
    }
    ID3D11DeviceContext &device_context = DeviceContext();

    device_context.RSSetState(rasterizer_state_.Get());
    device_context.IASetInputLayout(input_layout_.Get());
    device_context.IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    const std::array vertex_buffers = {vertex_buffer_.Get()};
    constexpr std::array<std::uint32_t, vertex_buffers.size()> strides{sizeof(Vertex)};
    constexpr std::array<std::uint32_t, vertex_buffers.size()> offsets{};

    device_context.IASetVertexBuffers(
            0, vertex_buffers.size(),
            vertex_buffers.data(),
            strides.data(), offsets.data());
    device_context.IASetIndexBuffer(index_buffer_.Get(), DXGI_FORMAT_R32_UINT, 0);

    device_context.VSSetShader(vertex_shader_.Get(), nullptr, 0);
    device_context.PSSetShader(pixel_shader_.Get(), nullptr, 0);

    const ConstantBuffer constant_buffer{
        .world = WorldTransform().ToMatrix(),
        .view = (camera != nullptr) ? camera->View() : math::Matrix4x4::Identity,
        .projection = (camera != nullptr) ? camera->Projection() : math::Matrix4x4::Identity,
    };
    UpdateConstantBuffer(constant_buffer);

    const std::array constant_buffers{constant_buffer_.Get()};
    device_context.VSSetConstantBuffers(
        0, constant_buffers.size(), constant_buffers.data());

    D3D11_BUFFER_DESC index_buffer_desc;
    index_buffer_->GetDesc(&index_buffer_desc);
    const std::uint32_t index_count = index_buffer_desc.ByteWidth / sizeof(Index);
    device_context.DrawIndexed(index_count, 0, 0);
}

void TriangleComponent::InitializeVertexShader() {
    vertex_byte_code_ =
        detail::ShaderFromFile(
            "resources/shaders/shader.hlsl", nullptr /*macros*/,
            D3D_COMPILE_STANDARD_FILE_INCLUDE /*include*/, "VSMain", "vs_5_0",
            D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0);

    const HRESULT result = Device().CreateVertexShader(
        vertex_byte_code_->GetBufferPointer(), vertex_byte_code_->GetBufferSize(),
        nullptr, &vertex_shader_);
    detail::CheckResult(result, "Failed to create vertex shader from byte code");
}

void TriangleComponent::InitializeConstantBuffer() {
    constexpr D3D11_BUFFER_DESC buffer_desc{
        .ByteWidth = sizeof(ConstantBuffer),
        .Usage = D3D11_USAGE_DYNAMIC,
        .BindFlags = D3D11_BIND_CONSTANT_BUFFER,
        .CPUAccessFlags = D3D11_CPU_ACCESS_WRITE,
        .MiscFlags = 0,
        .StructureByteStride = 0,
    };

    const HRESULT result = Device().CreateBuffer(
        &buffer_desc, nullptr, &constant_buffer_);
    detail::CheckResult(result, "Failed to create constant buffer");
}

void TriangleComponent::InitializePixelShader() {
    constexpr std::array shader_macros{
        D3D_SHADER_MACRO{.Name = "TEST", .Definition = "1"},
        D3D_SHADER_MACRO{.Name = "TCOLOR", .Definition = "float4(0.0f, 1.0f, 0.0f, 1.0f)"},
        D3D_SHADER_MACRO{.Name = nullptr, .Definition = nullptr},
    };
    pixel_byte_code_ =
        detail::ShaderFromFile(
            "resources/shaders/shader.hlsl", shader_macros.data() /*macros*/,
            D3D_COMPILE_STANDARD_FILE_INCLUDE /*include*/, "PSMain", "ps_5_0",
            D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0);

    const HRESULT result = Device().CreatePixelShader(
        pixel_byte_code_->GetBufferPointer(), pixel_byte_code_->GetBufferSize(),
        nullptr, &pixel_shader_);
    detail::CheckResult(result, "Failed to create index shader from byte code");
}

void TriangleComponent::InitializeInputLayout() {
    std::array input_elements = std::to_array(Vertex::InputElements);
    input_elements[0].SemanticName = "POSITION";

    const HRESULT result = Device().CreateInputLayout(
        input_elements.data(), input_elements.size(),
        vertex_byte_code_->GetBufferPointer(),
        vertex_byte_code_->GetBufferSize(), &input_layout_);
    detail::CheckResult(result, "Failed to create input layout");
}

void TriangleComponent::InitializeRasterizerState() {
    constexpr D3D11_RASTERIZER_DESC rasterizer_desc{
        .FillMode = D3D11_FILL_SOLID,
        .CullMode = D3D11_CULL_FRONT,
    };

    const HRESULT result = Device().CreateRasterizerState(&rasterizer_desc, &rasterizer_state_);
    detail::CheckResult(result, "Failed to create rasterizer state");
}

void TriangleComponent::InitializeVertexBuffer(std::span<const Vertex> vertices) {
    if (vertices.empty()) {
        vertex_buffer_ = nullptr;
        return;
    }

    const D3D11_BUFFER_DESC buffer_desc{
        .ByteWidth = static_cast<std::uint32_t>(vertices.size_bytes()),
        .Usage = D3D11_USAGE_DEFAULT,
        .BindFlags = D3D11_BIND_VERTEX_BUFFER,
        .CPUAccessFlags = 0,
        .MiscFlags = 0,
        .StructureByteStride = 0,
    };
    const D3D11_SUBRESOURCE_DATA initial_data{
        .pSysMem = vertices.data(),
        .SysMemPitch = 0,
        .SysMemSlicePitch = 0,
    };

    const HRESULT result = Device().CreateBuffer(&buffer_desc, &initial_data, &vertex_buffer_);
    detail::CheckResult(result, "Failed to create vertex buffer");
}

void TriangleComponent::InitializeIndexBuffer(std::span<const Index> indices) {
    if (indices.empty()) {
        index_buffer_ = nullptr;
        return;
    }

    const D3D11_BUFFER_DESC buffer_desc{
        .ByteWidth = static_cast<std::uint32_t>(indices.size_bytes()),
        .Usage = D3D11_USAGE_DEFAULT,
        .BindFlags = D3D11_BIND_INDEX_BUFFER,
        .CPUAccessFlags = 0,
        .MiscFlags = 0,
        .StructureByteStride = 0,
    };
    const D3D11_SUBRESOURCE_DATA initial_data{
        .pSysMem = indices.data(),
        .SysMemPitch = 0,
        .SysMemSlicePitch = 0,
    };

    const HRESULT result = Device().CreateBuffer(&buffer_desc, &initial_data, &index_buffer_);
    detail::CheckResult(result, "Failed to create index buffer");
}

void TriangleComponent::UpdateConstantBuffer(const ConstantBuffer &data) {
    D3D11_MAPPED_SUBRESOURCE mapped_subresource{};
    const HRESULT result =
        DeviceContext().Map(
            constant_buffer_.Get(), 0,
            D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource);
    detail::CheckResult(result, "Failed to map constant buffer data");

    std::memcpy(mapped_subresource.pData, &data, sizeof(data));
    DeviceContext().Unmap(constant_buffer_.Get(), 0);
}

}  // namespace computer_graphics
