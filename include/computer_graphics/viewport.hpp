#pragma once

#ifndef VIEWPORT_HPP_INCLUDED
#define VIEWPORT_HPP_INCLUDED

#include "math.hpp"

namespace computer_graphics {

class Camera;

class Viewport : public math::Viewport {
  public:
    Camera *camera;

    explicit Viewport(Camera *camera = nullptr) noexcept;

    Viewport(float x, float y, float width, float height,
        float min_depth = 0.0f, float max_depth = 1.0f,
        Camera *camera = nullptr) noexcept;

    explicit Viewport(const RECT &rect, Camera *camera = nullptr) noexcept;
};

}  // namespace computer_graphics

#endif  // VIEWPORT_HPP_INCLUDED
