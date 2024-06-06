#pragma once

#ifndef GEAR_HPP_INCLUDED
#define GEAR_HPP_INCLUDED

#include <numbers>

#include "computer_graphics/collision.hpp"
#include "computer_graphics/mesh_component.hpp"

class Gear final : public computer_graphics::SceneComponent, public computer_graphics::Collision {
  public:
    using MeshType = computer_graphics::MeshComponent<>;

    explicit Gear(computer_graphics::Game& game, const Initializer& initializer = {});

    [[nodiscard]] const MeshType& Mesh() const;
    [[nodiscard]] MeshType& Mesh();

    // void Draw(const computer_graphics::Camera* camera) override;

    [[nodiscard]] bool Intersects(const Collision& other) const override;
    [[nodiscard]] bool Intersects(const computer_graphics::math::Ray& ray, float& dist) const override;

  private:
    [[nodiscard]] computer_graphics::BoxCollision CollisionPrimitive() const;

    std::reference_wrapper<MeshType> mesh_;
};

inline Gear::Gear(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer),
      mesh_{Game().AddComponent<MeshType>([this] {
          MeshType::Initializer mesh_initializer{
              .mesh_path = "resources/meshes/gear/Gear2.fbx",
          };
          mesh_initializer.transform = {
              .position = computer_graphics::math::Vector3::Up * 0.3f,
              .rotation = computer_graphics::math::Quaternion::CreateFromYawPitchRoll(
                  0.0f, std::numbers::pi_v<float> / 2.0f, 0.0f),
              .scale = computer_graphics::math::Vector3::One / 30.0f,
          };
          mesh_initializer.parent = this;
          return mesh_initializer;
      }())} {}

inline auto Gear::Mesh() const -> const MeshType& {
    return mesh_;
}

inline auto Gear::Mesh() -> MeshType& {
    return mesh_;
}

// inline void Gear::Draw(const computer_graphics::Camera* camera) {
//     SceneComponent::Draw(camera);
//
//     Game().DebugDraw().DrawBox(CollisionPrimitive().Primitive());
// }

inline bool Gear::Intersects(const Collision& other) const {
    return CollisionPrimitive().Intersects(other);
}

inline bool Gear::Intersects(const computer_graphics::math::Ray& ray, float& dist) const {
    return CollisionPrimitive().Intersects(ray, dist);
}

inline computer_graphics::BoxCollision Gear::CollisionPrimitive() const {
    computer_graphics::math::Box box{
        computer_graphics::math::Vector3{0.0f, 0.3f, 0.05f},
        computer_graphics::math::Vector3{0.3f, 0.3f, 0.05f},
        computer_graphics::math::Quaternion::Identity,
    };
    box.Transform(box, WorldTransform().ToMatrix());

    return computer_graphics::BoxCollision{box};
}

#endif  // GEAR_HPP_INCLUDED
