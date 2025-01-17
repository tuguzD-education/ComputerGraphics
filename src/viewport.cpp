#include "computer_graphics/viewport.hpp"

namespace computer_graphics {

Viewport::Viewport(Camera *camera) noexcept : camera{camera} {}

Viewport::Viewport(
    const float x, const float y, const float width, const float height,
    const float min_depth, const float max_depth, Camera *camera) noexcept
: math::Viewport(x, y, width, height, min_depth, max_depth), camera{camera} {}

Viewport::Viewport(const RECT &rect, Camera *camera) noexcept : math::Viewport(rect), camera{camera} {}

}  // namespace computer_graphics
