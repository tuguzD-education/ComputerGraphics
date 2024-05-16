#include "computer_graphics/triangle_component.hpp"

#include <d3dcompiler.h>

#include <array>
#include <format>

#include "computer_graphics/detail/check_result.hpp"
#include "computer_graphics/detail/string_api_set.hpp"
#include "computer_graphics/game.hpp"

namespace computer_graphics {

namespace detail {

D3DPtr<ID3DBlob> CompileFromFile(
    const char *path, const D3D_SHADER_MACRO *defines, ID3DInclude *include,
    const char *entrypoint, const char *target, const UINT flags_1, const UINT flags_2) {

    D3DPtr<ID3DBlob> shader;
    D3DPtr<ID3DBlob> error_messages;

    const std::wstring w_path = MultiByteToWideChar(CP_UTF8, 0, path);
    const HRESULT result = D3DCompileFromFile(
        w_path.c_str(), defines, include, entrypoint, target,
        flags_1, flags_2, &shader, &error_messages);
    detail::CheckResult(result, [&] {
        const char *message =
            error_messages ? static_cast<const char *>(error_messages->GetBufferPointer()) : "file is missing";
        return std::format("Failed to compile vertex shader file '{}':\n{}", path, message);
    });

    return shader;
}

}  // namespace detail

TriangleComponent::TriangleComponent(
    Game &game, const std::span<Vertex> vertices,
    const std::span<Index> indices, const math::Vector3 position)
    : Component{game}, position_{position} {

    InitializeVertexShader();
    InitializePixelShader();
    InitializeInputLayout();
    InitializeRasterizerState();
    InitializeVertexBuffer(vertices);
    InitializeIndexBuffer(indices);
    InitializeConstantBuffer(position);
}

const math::Vector3 &TriangleComponent::Position() const {
    return position_;
}

math::Vector3 &TriangleComponent::Position() {
    return position_;
}

void TriangleComponent::Update(float delta_time) {}

void TriangleComponent::Draw() {
    ID3D11DeviceContext *device_context = DeviceContext();

    const std::array vertex_buffers = {vertex_buffer_.Get()};
    constexpr std::array<UINT, vertex_buffers.size()> strides{sizeof(Vertex)};
    constexpr std::array<UINT, vertex_buffers.size()> offsets{0};

    device_context->RSSetState(rasterizer_state_.Get());
    device_context->IASetInputLayout(input_layout_.Get());
    device_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    device_context->IASetIndexBuffer(index_buffer_.Get(), DXGI_FORMAT_R32_UINT, 0);
    device_context->IASetVertexBuffers(
        0, vertex_buffers.size(), vertex_buffers.data(),
        strides.data(), offsets.data());
    device_context->VSSetShader(vertex_shader_.Get(), nullptr, 0);
    device_context->PSSetShader(pixel_shader_.Get(), nullptr, 0);

    D3D11_MAPPED_SUBRESOURCE subresource{};
    device_context->Map(
        constant_buffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource);
    std::memcpy(subresource.pData, &position_, sizeof(position_));
    device_context->Unmap(constant_buffer_.Get(), 0);

    device_context->VSSetConstantBuffers(0, 1, constant_buffer_.GetAddressOf());

    D3D11_BUFFER_DESC index_buffer_desc;
    index_buffer_->GetDesc(&index_buffer_desc);
    const UINT index_count = index_buffer_desc.ByteWidth / sizeof(Index);
    device_context->DrawIndexed(index_count, 0, 0);
}

void TriangleComponent::InitializeVertexShader() {
    vertex_byte_code_ =
        detail::CompileFromFile(
            "resources/shaders/shader.hlsl", nullptr /*macros*/, nullptr /*include*/,
            "VSMain", "vs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0);

    const HRESULT result = Device()->CreateVertexShader(
        vertex_byte_code_->GetBufferPointer(), vertex_byte_code_->GetBufferSize(),
        nullptr, &vertex_shader_);
    detail::CheckResult(result, "Failed to create vertex shader from byte code");
}

void TriangleComponent::InitializePixelShader() {
    std::array shader_macros{
        D3D_SHADER_MACRO{.Name = "TEST", .Definition = "1"},
        D3D_SHADER_MACRO{.Name = "TCOLOR", .Definition = "float4(0.0f, 1.0f, 0.0f, 1.0f)"},
        D3D_SHADER_MACRO{.Name = nullptr, .Definition = nullptr},
    };

    pixel_byte_code_ =
        detail::CompileFromFile(
            "resources/shaders/shader.hlsl", shader_macros.data() /*macros*/, nullptr /*include*/,
            "PSMain", "ps_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0);

    const HRESULT result = Device()->CreatePixelShader(
        pixel_byte_code_->GetBufferPointer(), pixel_byte_code_->GetBufferSize(),
        nullptr, &pixel_shader_);
    detail::CheckResult(result, "Failed to create index shader from byte code");
}

void TriangleComponent::InitializeInputLayout() {
    constexpr std::array input_elements{
        D3D11_INPUT_ELEMENT_DESC{
            .SemanticName = "POSITION",
            .SemanticIndex = 0,
            .Format = DXGI_FORMAT_R32G32B32_FLOAT,
            .InputSlot = 0,
            .AlignedByteOffset = 0,
            .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,
            .InstanceDataStepRate = 0,
        },
        D3D11_INPUT_ELEMENT_DESC{
            .SemanticName = "COLOR",
            .SemanticIndex = 0,
            .Format = DXGI_FORMAT_R32G32B32A32_FLOAT,
            .InputSlot = 0,
            .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,
            .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,
            .InstanceDataStepRate = 0,
        },
    };

    const HRESULT result = Device()->CreateInputLayout(
        input_elements.data(), input_elements.size(),
        vertex_byte_code_->GetBufferPointer(),
        vertex_byte_code_->GetBufferSize(), &input_layout_);
    detail::CheckResult(result, "Failed to create input layout");
}

void TriangleComponent::InitializeRasterizerState() {
    constexpr D3D11_RASTERIZER_DESC rasterizer_desc{
        .FillMode = D3D11_FILL_SOLID,
        .CullMode = D3D11_CULL_NONE,
    };

    const HRESULT result = Device()->CreateRasterizerState(&rasterizer_desc, &rasterizer_state_);
    detail::CheckResult(result, "Failed to create rasterizer state");
}

void TriangleComponent::InitializeVertexBuffer(std::span<Vertex> vertices) {
    const D3D11_BUFFER_DESC buffer_desc{
        .ByteWidth = static_cast<UINT>(vertices.size_bytes()),
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

    const HRESULT result = Device()->CreateBuffer(&buffer_desc, &initial_data, &vertex_buffer_);
    detail::CheckResult(result, "Failed to create vertex buffer");
}

void TriangleComponent::InitializeIndexBuffer(std::span<Index> indices) {
    const D3D11_BUFFER_DESC buffer_desc{
        .ByteWidth = static_cast<UINT>(indices.size_bytes()),
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

    const HRESULT result = Device()->CreateBuffer(&buffer_desc, &initial_data, &index_buffer_);
    detail::CheckResult(result, "Failed to create index buffer");
}

void TriangleComponent::InitializeConstantBuffer(math::Vector3 position) {
    constexpr D3D11_BUFFER_DESC buffer_desc{
        .ByteWidth = ((sizeof(position) - 1) | 15) + 1,
        .Usage = D3D11_USAGE_DYNAMIC,
        .BindFlags = D3D11_BIND_CONSTANT_BUFFER,
        .CPUAccessFlags = D3D11_CPU_ACCESS_WRITE,
        .MiscFlags = 0,
        .StructureByteStride = 0,
    };
    const D3D11_SUBRESOURCE_DATA initial_data{
        .pSysMem = &position,
        .SysMemPitch = 0,
        .SysMemSlicePitch = 0,
    };

    const HRESULT result = Device()->CreateBuffer(&buffer_desc, &initial_data, &constant_buffer_);
    detail::CheckResult(result, "Failed to create constant buffer");
}

}  // namespace computer_graphics
