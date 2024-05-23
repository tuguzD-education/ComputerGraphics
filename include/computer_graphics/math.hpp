#pragma once

#ifndef MATH_HPP_INCLUDED
#define MATH_HPP_INCLUDED

#include <DirectXCollision.h>
#include <DirectXColors.h>
#include <SimpleMath.h>

namespace computer_graphics::math {

using Vector2 = DirectX::SimpleMath::Vector2;
using Vector3 = DirectX::SimpleMath::Vector3;
using Vector4 = DirectX::SimpleMath::Vector4;

void Normalize(const Vector3 &vector, Vector3 &result);
Vector3 Normalize(const Vector3 &vector);

using Color = DirectX::SimpleMath::Color;

namespace colors {

namespace srgb = DirectX::Colors;
namespace linear = DirectX::ColorsLinear;

}  // namespace colors

using Matrix4x4 = DirectX::SimpleMath::Matrix;
using Quaternion = DirectX::SimpleMath::Quaternion;

void RotateAround(
    const Vector3 &position, const Vector3 &rotation_point, const Quaternion &rotate_by, Vector3 &result);
Vector3 RotateAround(
    const Vector3 &position, const Vector3 &rotation_point, const Quaternion &rotate_by);

using Viewport = DirectX::SimpleMath::Viewport;
using Plane = DirectX::SimpleMath::Plane;
using Ray = DirectX::SimpleMath::Ray;
using Rectangle = DirectX::SimpleMath::Rectangle;

struct Point {
    std::int32_t x;
    std::int32_t y;
};

using Box = DirectX::BoundingOrientedBox;
using Frustum = DirectX::BoundingFrustum;

}  // namespace computer_graphics::math

#endif  // MATH_HPP_INCLUDED
