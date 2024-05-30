#include "deimos.hpp"

#include <computer_graphics/game.hpp>

namespace detail {

computer_graphics::GeometricPrimitiveComponent& CreateDeimosMesh(
    computer_graphics::Game& game, const computer_graphics::SceneComponent* parent) {
    computer_graphics::GeometricPrimitiveComponent::Initializer initializer{
        .primitive_arguments =
            computer_graphics::BoxGeometricPrimitiveArguments{
                .size = computer_graphics::math::Vector3::One * 0.1f,
            },
        .color = computer_graphics::math::colors::linear::DarkRed.v,
    };
    initializer.Parent(parent);
    return game.AddComponent<computer_graphics::GeometricPrimitiveComponent>(initializer);
}

}  // namespace detail

Deimos::Deimos(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer), mesh_{detail::CreateDeimosMesh(Game(), this)} {}

const computer_graphics::GeometricPrimitiveComponent& Deimos::Mesh() const {
    return mesh_;
}

computer_graphics::GeometricPrimitiveComponent& Deimos::Mesh() {
    return mesh_;
}

bool Deimos::Intersects(const computer_graphics::Collision& other) const {
    return CollisionPrimitive().Intersects(other);
}

bool Deimos::Intersects(const computer_graphics::math::Ray& ray, float& dist) const {
    return CollisionPrimitive().Intersects(ray, dist);
}

computer_graphics::BoxCollision Deimos::CollisionPrimitive() const {
    auto [position, rotation, scale] = mesh_.get().WorldTransform();
    rotation.Normalize();

    const computer_graphics::math::Box box{
        position,
        computer_graphics::math::Vector3::One * 0.05f * scale,
        rotation,
    };
    return computer_graphics::BoxCollision{box};
}
