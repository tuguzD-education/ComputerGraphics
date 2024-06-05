#pragma once

#ifndef FIELD_HPP_INCLUDED
#define FIELD_HPP_INCLUDED

#include <d3dcompiler.h>

#include <computer_graphics/box_component.hpp>

#include "computer_graphics/detail/check_result.hpp"
#include "computer_graphics/detail/shader.hpp"

class Background final : public computer_graphics::BoxComponent {
  public:
    explicit Background(computer_graphics::Game& game);
};

inline Background::Background(computer_graphics::Game& game)
    : BoxComponent(game, Initializer{}) {
    vertex_shader_byte_code_ = computer_graphics::detail::ShaderFromFile(
        "resources/shaders/chess.hlsl", nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, "VSMain", "vs_5_0",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0);

    HRESULT result = Device().CreateVertexShader(
        vertex_shader_byte_code_->GetBufferPointer(),
        vertex_shader_byte_code_->GetBufferSize(),
        nullptr, &vertex_shader_);
    computer_graphics::detail::CheckResult(result, "Failed to create vertex shader from byte code");

    pixel_shader_byte_code_ = computer_graphics::detail::ShaderFromFile(
        "resources/shaders/chess.hlsl", nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, "PSMain", "ps_5_0",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0);

    result = Device().CreatePixelShader(
        pixel_shader_byte_code_->GetBufferPointer(),
        pixel_shader_byte_code_->GetBufferSize(),
        nullptr, &pixel_shader_);
    computer_graphics::detail::CheckResult(result, "Failed to create index shader from byte code");
}

#endif  // FIELD_HPP_INCLUDED
