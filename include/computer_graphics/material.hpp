#pragma once

#ifndef MATERIAL_HPP_INCLUDED
#define MATERIAL_HPP_INCLUDED

#include "math.hpp"

namespace computer_graphics {

struct alignas(16) Material {
    math::Color ambient{math::colors::linear::White};
    math::Color diffuse{math::colors::linear::White};
    math::Color specular{math::colors::linear::White};
    math::Color emissive;
    float exponent = 16.0f;
};

}  // namespace computer_graphics

#endif  // MATERIAL_HPP_INCLUDED
