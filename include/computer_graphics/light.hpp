#pragma once

#ifndef LIGHT_HPP_INCLUDED
#define LIGHT_HPP_INCLUDED

#include "scene_component.hpp"

namespace computer_graphics {

struct alignas(16) Light {
    math::Color ambient{math::colors::linear::White};
    math::Color diffuse;
    math::Color specular;
};

class LightComponent : public SceneComponent {
  public:
    struct Initializer : SceneComponent::Initializer {
        Light light;
        bool is_light_enabled = false;
    };

    explicit LightComponent(class Game& game, const Initializer& initializer = {});

    [[nodiscard]] math::Color Ambient() const;
    [[nodiscard]] math::Color& Ambient();

    [[nodiscard]] math::Color Diffuse() const;
    [[nodiscard]] math::Color& Diffuse();

    [[nodiscard]] math::Color Specular() const;
    [[nodiscard]] math::Color& Specular();

    [[nodiscard]] Light Light() const;

    [[nodiscard]] bool IsLightEnabled() const;
    [[nodiscard]] bool& IsLightEnabled();

    [[nodiscard]] virtual math::Matrix4x4 ViewMatrix(const Camera* camera) const = 0;
    [[nodiscard]] virtual math::Matrix4x4 ProjectionMatrix(const Camera* camera) const = 0;

  private:
    class Light light_;
    bool is_enabled_;
};

struct alignas(16) DirectionalLight : Light {
    alignas(16) math::Vector3 direction;
};

class DirectionalLightComponent final : public LightComponent {
  public:
    struct Initializer : LightComponent::Initializer {
        [[nodiscard]] math::Vector3 Direction() const;
        void Direction(const math::Vector3& direction);
    };

    explicit DirectionalLightComponent(class Game& game, const Initializer& initializer = {});

    [[nodiscard]] math::Vector3 Direction() const;
    void Direction(const math::Vector3& direction);

    [[nodiscard]] DirectionalLight DirectionalLight() const;

    [[nodiscard]] math::Matrix4x4 ViewMatrix(const Camera* camera) const override;
    [[nodiscard]] math::Matrix4x4 ProjectionMatrix(const Camera* camera) const override;
};

struct alignas(16) Attenuation {
    math::Color const_factor{math::colors::linear::White};
    math::Color linear_factor;
    math::Color quad_factor;
};

struct alignas(16) PointLight : Light {
    alignas(16) math::Vector3 position;
    alignas(16) Attenuation attenuation;
};

class PointLightComponent final : public LightComponent {
  public:
    struct Initializer : LightComponent::Initializer {
        Attenuation attenuation;
    };

    explicit PointLightComponent(class Game& game, const Initializer& initializer = {});

    [[nodiscard]] const Attenuation& Attenuation() const;
    [[nodiscard]] class Attenuation& Attenuation();

    [[nodiscard]] PointLight PointLight() const;

    [[nodiscard]] math::Matrix4x4 ViewMatrix(const Camera* camera) const override;
    [[nodiscard]] math::Matrix4x4 ProjectionMatrix(const Camera* camera) const override;

  private:
    class Attenuation attenuation_;
};

}  // namespace computer_graphics

#endif  // LIGHT_HPP_INCLUDED
