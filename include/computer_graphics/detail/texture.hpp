#pragma once

#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <d3d11.h>

#include <filesystem>

#include "d3d_ptr.hpp"

namespace computer_graphics::detail {

[[nodiscard]] D3DPtr<ID3D11ShaderResourceView> TextureFromFile(
    ID3D11Device &device, ID3D11DeviceContext &device_context, const std::filesystem::path &path);

}  // namespace borov_engine::detail

#endif  // TEXTURE_HPP_INCLUDED
