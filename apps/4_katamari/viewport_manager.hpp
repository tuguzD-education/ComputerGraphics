#pragma once

#ifndef KATAMARI_VIEWPORT_MANAGER_HPP_INCLUDED
#define KATAMARI_VIEWPORT_MANAGER_HPP_INCLUDED

#include <computer_graphics/camera.hpp>
#include <computer_graphics/viewport_manager.hpp>

class ViewportManager final : public computer_graphics::ViewportManager {
  public:
    explicit ViewportManager(computer_graphics::Game &game);

  private:
    std::reference_wrapper<computer_graphics::Camera> stationary_camera_;
};

inline ViewportManager::ViewportManager(computer_graphics::Game &game)
    : computer_graphics::ViewportManager(game),
      stationary_camera_{
          Game().AddComponent<computer_graphics::Camera>([] {
              computer_graphics::Camera::Initializer initializer{
                  .projection = std::make_unique<computer_graphics::PerspectiveProjection>(),
                  .far_plane = 12.01f,
              };
              namespace math = computer_graphics::math;

              initializer.transform.position = math::Vector3::Up * 12.0f;
              initializer.transform.rotation =
                  math::Quaternion::CreateFromAxisAngle(
                      math::Vector3::Right, -std::numbers::pi_v<float> / 2.0f);
              return initializer;
          }()),
      } {}

#endif  // KATAMARI_VIEWPORT_MANAGER_HPP_INCLUDED
