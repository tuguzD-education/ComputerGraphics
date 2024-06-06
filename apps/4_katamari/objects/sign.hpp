#pragma once

#ifndef SIGN_HPP_INCLUDED
#define SIGN_HPP_INCLUDED

#include <computer_graphics/collision.hpp>
#include <computer_graphics/mesh_component.hpp>

class Sign final : public computer_graphics::SceneComponent, public computer_graphics::Collision {
  public:
    using MeshType = computer_graphics::MeshComponent<>;

    explicit Sign(computer_graphics::Game& game, const Initializer& initializer = {});

    [[nodiscard]] const MeshType& Mesh() const;
    [[nodiscard]] MeshType& Mesh();

    // void Draw(const computer_graphics::Camera* camera) override;

    [[nodiscard]] bool Intersects(const Collision& other) const override;
    [[nodiscard]] bool Intersects(const computer_graphics::math::Ray& ray, float& dist) const override;

  private:
    [[nodiscard]] computer_graphics::SphereCollision CollisionPrimitive() const;

    std::reference_wrapper<MeshType> mesh_;
};

inline Sign::Sign(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer),
      mesh_{Game().AddComponent<MeshType>([this] {
          MeshType::Initializer mesh_initializer{
              .mesh_path = "resources/meshes/sign/sign.fbx",
          };
          mesh_initializer.transform = {.scale = computer_graphics::math::Vector3::One / 20.0f};
          mesh_initializer.parent = this;
          return mesh_initializer;
      }())} {}

inline auto Sign::Mesh() const -> const MeshType& {
    return mesh_;
}

inline auto Sign::Mesh() -> MeshType& {
    return mesh_;
}

// inline void Sign::Draw(const computer_graphics::Camera* camera) {
//     SceneComponent::Draw(camera);
//
//     Game().DebugDraw().DrawSphere(CollisionPrimitive().Primitive());
// }

inline bool Sign::Intersects(const Collision& other) const {
    return CollisionPrimitive().Intersects(other);
}

inline bool Sign::Intersects(const computer_graphics::math::Ray& ray, float& dist) const {
    return CollisionPrimitive().Intersects(ray, dist);
}

inline computer_graphics::SphereCollision Sign::CollisionPrimitive() const {
    computer_graphics::math::Sphere sphere{
        computer_graphics::math::Vector3{0.0f, 2.0f, 0.0f},
        0.15f,
    };
    sphere.Transform(sphere, WorldTransform().ToMatrix());

    return computer_graphics::SphereCollision{sphere};
}

#endif  // SIGN_HPP_INCLUDED
