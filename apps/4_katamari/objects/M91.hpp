#pragma once

#ifndef M91_HPP_INCLUDED
#define M91_HPP_INCLUDED

#include "computer_graphics/collision.hpp"
#include "computer_graphics/mesh_component.hpp"

class M91 final : public computer_graphics::SceneComponent, public computer_graphics::Collision {
  public:
    using MeshType = computer_graphics::MeshComponent<>;

    explicit M91(computer_graphics::Game& game, const Initializer& initializer = {});

    [[nodiscard]] const MeshType& Mesh() const;
    [[nodiscard]] MeshType& Mesh();

    // void Draw(const computer_graphics::Camera* camera) override;

    [[nodiscard]] bool Intersects(const Collision& other) const override;
    [[nodiscard]] bool Intersects(const computer_graphics::math::Ray& ray, float& dist) const override;

  private:
    [[nodiscard]] computer_graphics::BoxCollision CollisionPrimitive() const;

    std::reference_wrapper<MeshType> mesh_;
};

inline M91::M91(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer),
      mesh_{Game().AddComponent<MeshType>([this] {
          MeshType::Initializer mesh_initializer{
              .mesh_path = "resources/meshes/M91/M91.fbx",
          };
          mesh_initializer.transform = {.scale = computer_graphics::math::Vector3::One / 60.0f};
          mesh_initializer.parent = this;
          return mesh_initializer;
      }())} {}

inline auto M91::Mesh() const -> const MeshType& {
    return mesh_;
}

inline auto M91::Mesh() -> MeshType& {
    return mesh_;
}

// inline void M91::Draw(const computer_graphics::Camera* camera) {
//     SceneComponent::Draw(camera);
//
//     Game().DebugDraw().DrawBox(CollisionPrimitive().Primitive());
// }

inline bool M91::Intersects(const Collision& other) const {
    return CollisionPrimitive().Intersects(other);
}

inline bool M91::Intersects(const computer_graphics::math::Ray& ray, float& dist) const {
    return CollisionPrimitive().Intersects(ray, dist);
}

inline computer_graphics::BoxCollision M91::CollisionPrimitive() const {
    computer_graphics::math::Box box{
        computer_graphics::math::Vector3{0.0f, 0.15f, 0.0f},
        computer_graphics::math::Vector3{0.025f, 0.15f, 1.15f},
        computer_graphics::math::Quaternion::Identity,
    };
    box.Transform(box, WorldTransform().ToMatrix());

    return computer_graphics::BoxCollision{box};
}

#endif  // M91_HPP_INCLUDED
