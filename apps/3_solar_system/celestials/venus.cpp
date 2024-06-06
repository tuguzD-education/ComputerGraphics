#include "venus.hpp"

#include <computer_graphics/game.hpp>
#include <numbers>

namespace detail {

computer_graphics::GeometricPrimitiveComponent& CreateVenusMesh(
    computer_graphics::Game& game, const computer_graphics::SceneComponent* parent) {
    computer_graphics::GeometricPrimitiveComponent::Initializer initializer{
        .primitive_arguments =
            computer_graphics::TorusGeometricPrimitiveArguments{
                .diameter = 0.4f,
                .thickness = 0.2f,
            },
        .color = computer_graphics::math::colors::linear::LightGoldenrodYellow.v,
    };
    initializer.transform = computer_graphics::Transform{
        .rotation = computer_graphics::math::Quaternion::CreateFromAxisAngle(
            computer_graphics::math::Vector3::Right, std::numbers::pi_v<float> / 2.0f),
    };
    initializer.parent = parent;
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
        computer_graphics::math::Vector3::One * 0.275f * scale,
        rotation,
    };
    return computer_graphics::BoxCollision{box};
}

// void Venus::Draw(const computer_graphics::Camera* camera) {
//     SceneComponent::Draw(camera);
//
//     Game().DebugDraw().DrawBox(CollisionPrimitive().Primitive());
// }
