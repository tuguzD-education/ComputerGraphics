#pragma once

#ifndef LIGHT_HPP_INCLUDED
#define LIGHT_HPP_INCLUDED

#include "scene_component.hpp"

namespace computer_graphics {

struct alignas(16) AmbientLight {
    math::Color color{math::colors::linear::White};
};

class AmbientLightComponent final : public Component {
  public:
    using PrimitiveType = AmbientLight;

    struct Initializer : Component::Initializer {
        PrimitiveType light;
    };

    explicit AmbientLightComponent(class Game& game, const Initializer& initializer = {});

    [[nodiscard]] const PrimitiveType& Primitive() const noexcept;
    [[nodiscard]] PrimitiveType& Primitive() noexcept;

  private:
    PrimitiveType light_;
};

struct alignas(16) DirectionalLight {
    alignas(16) math::Vector3 direction;
    alignas(16) math::Color color;
};

class DirectionalLightComponent final : public Component {
  public:
    using PrimitiveType = DirectionalLight;

    struct Initializer : Component::Initializer {
        PrimitiveType light;
    };

    explicit DirectionalLightComponent(class Game& game, const Initializer& initializer = {});

    [[nodiscard]] const PrimitiveType& Primitive() const noexcept;
    [[nodiscard]] PrimitiveType& Primitive() noexcept;

  private:
    PrimitiveType light_;
};

struct alignas(16) Attenuation {
    math::Color const_factor{math::colors::linear::White};
    math::Color linear_factor;
    math::Color quad_factor;
};

struct alignas(16) PointLight {
    alignas(16) math::Vector3 position;
    alignas(16) math::Color color;
    alignas(16) Attenuation attenuation;
};

class PointLightComponent final : public SceneComponent {
  public:
    using PrimitiveType = PointLight;

    struct Initializer : SceneComponent::Initializer {
        math::Color color;
        Attenuation attenuation;

        Initializer& Color(math::Color color);
        Initializer& Attenuation(const Attenuation& attenuation);
    };

    explicit PointLightComponent(class Game& game, const Initializer& initializer = {});

    [[nodiscard]] PrimitiveType Primitive() const;

    [[nodiscard]] math::Color Color() const;
    [[nodiscard]] math::Color& Color();

    [[nodiscard]] const Attenuation& Attenuation() const;
    [[nodiscard]] class Attenuation& Attenuation();

  private:
    math::Color color_;
    class Attenuation attenuation_;
};

}  // namespace computer_graphics

#endif  // LIGHT_HPP_INCLUDED