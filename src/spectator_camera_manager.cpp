#include "computer_graphics/spectator_camera_manager.hpp"

#include "computer_graphics/camera.hpp"
#include "computer_graphics/game.hpp"

namespace computer_graphics {

auto SpectatorCameraManager::Initializer::Camera(class Camera* camera) -> Initializer& {
    this->camera = camera;
    return *this;
}

auto SpectatorCameraManager::Initializer::MovementInput(const class MovementInput movement_input) -> Initializer& {
    this->movement_input = movement_input;
    return *this;
}

auto SpectatorCameraManager::Initializer::Speed(const float speed) -> Initializer& {
    if (speed >= 0.0f) {
        this->speed = speed;
    }
    return *this;
}

auto SpectatorCameraManager::Initializer::Sensitivity(const float sensitivity) -> Initializer& {
    if (sensitivity >= 0.0f) {
        this->sensitivity = sensitivity;
    }
    return *this;
}

auto SpectatorCameraManager::Initializer::ZoomSpeed(const float zoom_speed) -> Initializer& {
    if (zoom_speed >= 0.0f) {
        this->zoom_speed = zoom_speed;
    }
    return *this;
}

SpectatorCameraManager::SpectatorCameraManager(class Game& game, const Initializer& initializer)
    : CameraManager(game),
      camera_{
          initializer.camera ? *initializer.camera
              : game.AddComponent<Camera>(Camera::Initializer{
                  .projection_type = PerspectiveCameraProjectionType{}
              }),
      },
      movement_input_{initializer.movement_input},
      speed_{initializer.speed},
      sensitivity_{initializer.sensitivity},
      zoom_speed_{initializer.zoom_speed},
      wheel_delta_{} {
    if (const auto input = Game().Input(); input != nullptr) {
        input->OnMouseMove().AddRaw(this, &SpectatorCameraManager::OnMouseMove);
    }
}

SpectatorCameraManager::~SpectatorCameraManager() {
    if (const auto input = Game().Input(); input != nullptr) {
        input->OnMouseMove().RemoveByOwner(this);
    }
}

auto SpectatorCameraManager::MovementInput() const -> class MovementInput {
    return movement_input_;
}

auto SpectatorCameraManager::MovementInput() -> class MovementInput& {
    return movement_input_;
}

float SpectatorCameraManager::Speed() const {
    return speed_;
}

bool SpectatorCameraManager::Speed(const float speed) {
    if (speed < 0.0f) {
        return false;
    }
    speed_ = speed;
    return true;
}

float SpectatorCameraManager::Sensitivity() const {
    return sensitivity_;
}

bool SpectatorCameraManager::Sensitivity(const float sensitivity) {
    if (sensitivity < 0.0f) {
        return false;
    }
    sensitivity_ = sensitivity;
    return true;
}

float SpectatorCameraManager::ZoomSpeed() const {
    return zoom_speed_;
}

bool SpectatorCameraManager::ZoomSpeed(const float zoom_speed) {
    if (zoom_speed < 0.0f) {
        return false;
    }
    zoom_speed_ = zoom_speed;
    return true;
}

const Camera* SpectatorCameraManager::MainCamera() const {
    return &camera_.get();
}

Camera* SpectatorCameraManager::MainCamera() {
    return &camera_.get();
}

void SpectatorCameraManager::Update(const float delta_time) {
    CameraManager::Update(delta_time);

    const Input* input = Game().Input();
    if (input == nullptr) {
        return;
    }

    Transform& transform = camera_.get().Transform();
    {
        auto axis_value = [input](const MovementInput::Axis axis) {
            return static_cast<float>(input->IsKeyDown(axis.positive) - input->IsKeyDown(axis.negative));
        };
        const float x = axis_value(movement_input_.x);
        const float y = axis_value(movement_input_.y);
        const float z = axis_value(movement_input_.z);

        const math::Vector3 direction = transform.Right() * x + math::Vector3::Up * y + transform.Forward() * z;
        transform.position += direction * speed_ * delta_time;
    }

    {
        auto [pitch, yaw, roll] = transform.rotation.ToEuler();
        yaw -= mouse_offset_.x * sensitivity_ * delta_time;
        pitch -= mouse_offset_.y * sensitivity_ * delta_time;

        constexpr float max_pitch = std::numbers::pi_v<float> / 2.0f - 0.001f;
        constexpr float min_pitch = -max_pitch;
        pitch = std::clamp(pitch, min_pitch, max_pitch);

        transform.rotation = math::Quaternion::CreateFromYawPitchRoll(yaw, pitch, 0.0f);
        mouse_offset_ = math::Vector2::Zero;
    }

    if (CameraProjectionType& projection_type = camera_.get().ProjectionType();
        std::holds_alternative<PerspectiveCameraProjectionType>(projection_type)) {
        auto& [horizontal_fov] = std::get<PerspectiveCameraProjectionType>(projection_type);

        horizontal_fov -= static_cast<float>(wheel_delta_) * zoom_speed_ * delta_time;
        wheel_delta_ = 0;
    }
}

void SpectatorCameraManager::OnMouseMove(const MouseMoveData& data) {
    mouse_offset_ += data.offset;
    wheel_delta_ += data.wheel_delta;
}

}  // namespace computer_graphics