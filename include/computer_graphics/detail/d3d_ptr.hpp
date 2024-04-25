#pragma once

#ifndef DETAIL_D3D_PTR_HPP_INCLUDED
#define DETAIL_D3D_PTR_HPP_INCLUDED

#include <wrl/client.h>

namespace computer_graphics::detail {

template <typename T>
using D3DPtr = Microsoft::WRL::ComPtr<T>;

}

#endif  // DETAIL_D3D_PTR_HPP_INCLUDED
