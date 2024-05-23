#pragma once

#ifndef SHADER_HPP_INCLUDED
#define SHADER_HPP_INCLUDED

#include <d3dcommon.h>

#include <filesystem>

#include "d3d_ptr.hpp"

namespace computer_graphics::detail {

[[nodiscard]] D3DPtr<ID3DBlob> ShaderFromFile(
    const std::filesystem::path &path, const D3D_SHADER_MACRO *defines, ID3DInclude *include,
    const char *entrypoint, const char *target, UINT flags_1, UINT flags_2);

}

#endif  // SHADER_HPP_INCLUDED
