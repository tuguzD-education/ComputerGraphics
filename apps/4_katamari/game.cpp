#include "game.hpp"

#include <computer_graphics/camera.hpp>
#include <computer_graphics/orbit_camera_manager.hpp>

#include "viewport_manager.hpp"

Game::Game(computer_graphics::Window &window, computer_graphics::Input &input)
    : computer_graphics::Game(window, input),
      camera_{
          AddComponent<computer_graphics::Camera>([] {
              computer_graphics::Camera::Initializer initializer{
                  .projection = std::make_unique<computer_graphics::PerspectiveProjection>(),
                  .far_plane = 10.0f,
              };
              initializer.transform = {.position = computer_graphics::math::Vector3::Backward};
              return initializer;
          }()),
      },
      field_{AddComponent<Field>()},
      player_{AddComponent<Player>()},
      sign_{AddComponent<Sign>(Sign::Initializer{.transform = computer_graphics::Transform{
          .position = computer_graphics::math::Vector3::Right * 2.0f +
              computer_graphics::math::Vector3::Forward * 3.0f,
          .scale = computer_graphics::math::Vector3::One * 0.2f,
      }})},
      gear_{AddComponent<Gear>(Sign::Initializer{.transform = computer_graphics::Transform{
          .position = computer_graphics::math::Vector3::Right * -2.0f +
              computer_graphics::math::Vector3::Forward * -3.0f,
          .scale = computer_graphics::math::Vector3::One,
      }})} {
    using computer_graphics::OrbitCameraManager;
    CameraManager<OrbitCameraManager>(OrbitCameraManager::Initializer{
        .target = player_,
        .camera = &camera_.get(),
    });
    ViewportManager<::ViewportManager>();

    namespace math = computer_graphics::math;

    ClearColor() = math::colors::linear::LightGoldenrodYellow;

    DirectionalLight().IsLightEnabled() = true;
    DirectionalLight().Ambient() = math::Color{math::colors::linear::White} * 0.5f;
    DirectionalLight().Diffuse() = math::Color{math::colors::linear::White};
    DirectionalLight().Specular() = math::Color{math::colors::linear::White};
    DirectionalLight().Direction(math::Normalize(math::Vector3::Down + math::Vector3::Forward));

    PointLight().IsLightEnabled() = false;
    PointLight().Ambient() = math::Color{math::colors::linear::Black};
    PointLight().Diffuse() = math::Color{math::colors::linear::White};
    PointLight().Specular() = math::Color{math::colors::linear::White};
    PointLight().Attenuation().linear_factor = math::Color{math::colors::linear::White};
    PointLight().Transform() = computer_graphics::Transform{.position = math::Vector3::Up * 0.2f};
}

void Game::Update(const float delta_time) {
    computer_graphics::Game::Update(delta_time);
    namespace math = computer_graphics::math;

    const computer_graphics::Input *input = Input();
    if (input == nullptr) return;

    const computer_graphics::Transform camera_transform = camera_.get().WorldTransform();

    auto [left_key, right_key, forward_key, backward_key] = player_.get().Controls();
    const auto x = static_cast<float>(input->IsKeyDown(right_key) - input->IsKeyDown(left_key));
    const auto z = static_cast<float>(input->IsKeyDown(forward_key) - input->IsKeyDown(backward_key));

    const math::Vector3 right = camera_transform.Right();
    math::Vector3 forward = camera_transform.Forward();
    forward.y = 0.0f;
    forward.Normalize();
    if (forward.LengthSquared() <= 0.1f) {
        forward = right.Cross(math::Vector3::Up);
    }

    math::Vector3 direction = right * x + forward * z;
    direction.y = 0.0f;
    direction.Normalize();

    computer_graphics::Transform player_transform = player_.get().WorldTransform();
    player_transform.position += direction * delta_time;
    if (direction.LengthSquared() > 0.1f) {
        const auto additional = math::Quaternion::CreateFromAxisAngle(
            -direction.Cross(math::Vector3::Up), std::numbers::pi_v<float> * 0.5f * delta_time);
        player_transform.rotation = math::Quaternion::Concatenate(additional, player_transform.rotation);
    }
    player_.get().WorldTransform(player_transform);

    // ReSharper disable once CppTooWideScopeInitStatement
    auto is_scene_and_collision = [](const computer_graphics::Component &component) {
        return dynamic_cast<const computer_graphics::SceneComponent *>(&component) != nullptr &&
            dynamic_cast<const computer_graphics::Collision *>(&component) != nullptr;
    };
    for (computer_graphics::Component &component : Components() | std::views::filter(is_scene_and_collision)) {
        if (&component == &player_.get() || &component == &field_.get()) {
            continue;
        }
        auto &scene_component = dynamic_cast<computer_graphics::SceneComponent &>(component);
        auto &collision_primitive = dynamic_cast<const computer_graphics::Collision &>(component);

        if (collision_primitive.Intersects(player_)) {
            scene_component.Parent(&player_.get());
        }
    }
}
