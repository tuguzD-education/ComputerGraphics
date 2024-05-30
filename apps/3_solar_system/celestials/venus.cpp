#include "venus.hpp"

#include <computer_graphics/game.hpp>
#include <numbers>

namespace detail {

computer_graphics::GeometricPrimitiveComponent& CreateVenusMesh(
    computer_graphics::Game& game, const computer_graphics::SceneComponent* parent) {
    computer_graphics::GeometricPrimitiveComponent::Initializer initializer{
        .primitive_arguments =
            computer_graphics::CylinderGeometricPrimitiveArguments{
                .height = 0.25f,
                .diameter = 0.25f,
            },
        .color = computer_graphics::math::colors::linear::LightYellow.v,
    };
    initializer
        .Transform({
            .rotation = computer_graphics::math::Quaternion::CreateFromAxisAngle(
                computer_graphics::math::Vector3::Right, std::numbers::pi_v<float> / 2.0f),
        })
        .Parent(parent);
    return game.AddComponent<computer_graphics::GeometricPrimitiveComponent>(initializer);
}

}  // namespace detail

Venus::Venus(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer), mesh_{detail::CreateVenusMesh(Game(), this)} {}

const computer_graphics::GeometricPrimitiveComponent& Venus::Mesh() const {
    return mesh_;
}

computer_graphics::GeometricPrimitiveComponent& Venus::Mesh() {
    return mesh_;
}

bool Venus::Intersects(const computer_graphics::Collision& other) const {
    return CollisionPrimitive().Intersects(other);
}

bool Venus::Intersects(const computer_graphics::math::Ray& ray, float& dist) const {
    return CollisionPrimitive().Intersects(ray, dist);
}

computer_graphics::BoxCollision Venus::CollisionPrimitive() const {
    auto [position, rotation, scale] = mesh_.get().WorldTransform();
    rotation.Normalize();

    const computer_graphics::math::Box box{
        position,
        computer_graphics::math::Vector3::One * 0.125f * scale,
        rotation,
    };
    return computer_graphics::BoxCollision{box};
}
