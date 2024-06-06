#pragma once

#ifndef PORTAL_HPP_INCLUDED
#define PORTAL_HPP_INCLUDED

#include "computer_graphics/collision.hpp"
#include "computer_graphics/mesh_component.hpp"

class Portal final : public computer_graphics::SceneComponent, public computer_graphics::Collision {
  public:
    using MeshType = computer_graphics::MeshComponent<>;

    explicit Portal(computer_graphics::Game& game, const Initializer& initializer = {});

    [[nodiscard]] const MeshType& Mesh() const;
    [[nodiscard]] MeshType& Mesh();

    // void Draw(const computer_graphics::Camera* camera) override;

    [[nodiscard]] bool Intersects(const Collision& other) const override;
    [[nodiscard]] bool Intersects(const computer_graphics::math::Ray& ray, float& dist) const override;

  private:
    [[nodiscard]] computer_graphics::BoxCollision CollisionPrimitive() const;

    std::reference_wrapper<MeshType> mesh_;
};

inline Portal::Portal(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer),
      mesh_{Game().AddComponent<MeshType>([this] {
          MeshType::Initializer mesh_initializer{
              .mesh_path = "resources/meshes/portal/StonePortal1.fbx",
          };
          mesh_initializer.transform = {
              .position = computer_graphics::math::Vector3::Up * 0.95f,
              .scale = computer_graphics::math::Vector3::One / 4000.0f,
          };
          mesh_initializer.parent = this;
          return mesh_initializer;
      }())} {}

inline auto Portal::Mesh() const -> const MeshType& {
    return mesh_;
}

inline auto Portal::Mesh() -> MeshType& {
    return mesh_;
}

// inline void Portal::Draw(const computer_graphics::Camera* camera) {
//     SceneComponent::Draw(camera);
//
//     Game().DebugDraw().DrawBox(CollisionPrimitive().Primitive());
// }

inline bool Portal::Intersects(const Collision& other) const {
    return CollisionPrimitive().Intersects(other);
}

inline bool Portal::Intersects(const computer_graphics::math::Ray& ray, float& dist) const {
    return CollisionPrimitive().Intersects(ray, dist);
}

inline computer_graphics::BoxCollision Portal::CollisionPrimitive() const {
    computer_graphics::math::Box box{
        computer_graphics::math::Vector3{0.0f, 0.95f, 0.0f},
        computer_graphics::math::Vector3{0.9f, 0.95f, 0.2f},
        computer_graphics::math::Quaternion::Identity,
    };
    box.Transform(box, WorldTransform().ToMatrix());

    return computer_graphics::BoxCollision{box};
}

#endif  // PORTAL_HPP_INCLUDED
