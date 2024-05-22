#ifndef MATH_HPP_INCLUDED
#define MATH_HPP_INCLUDED

#include <DirectXCollision.h>
#include <DirectXColors.h>
#include <SimpleMath.h>

namespace computer_graphics::math {

using Vector2 = DirectX::SimpleMath::Vector2;
using Vector3 = DirectX::SimpleMath::Vector3;
using Vector4 = DirectX::SimpleMath::Vector4;

using Color = DirectX::SimpleMath::Color;

namespace colors {

namespace srgb = DirectX::Colors;
namespace linear = DirectX::ColorsLinear;

}  // namespace colors

using Matrix4x4 = DirectX::SimpleMath::Matrix;
using Quaternion = DirectX::SimpleMath::Quaternion;

using Viewport = DirectX::SimpleMath::Viewport;
using Plane = DirectX::SimpleMath::Plane;
using Ray = DirectX::SimpleMath::Ray;
using Rectangle = DirectX::SimpleMath::Rectangle;

using Box = DirectX::BoundingBox;

}  // namespace computer_graphics::math

#endif  // MATH_HPP_INCLUDED
