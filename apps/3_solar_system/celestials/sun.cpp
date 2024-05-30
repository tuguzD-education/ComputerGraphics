#include "sun.hpp"

#include <computer_graphics/game.hpp>

namespace detail {

computer_graphics::BoxComponent& CreateSunMesh(
    computer_graphics::Game& game, const computer_graphics::SceneComponent* parent) {
    computer_graphics::BoxComponent::Initializer initializer{
        .length = 1.5f,
        .height = 1.5f,
        .width = 1.5f,
        .color = computer_graphics::math::colors::linear::Yellow.v,
    };
    initializer.Parent(parent);
    return game.AddComponent<computer_graphics::BoxComponent>(initializer);
}

}  // namespace detail

Sun::Sun(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer), mesh_{detail::CreateSunMesh(Game(), this)} {}

const computer_graphics::BoxComponent& Sun::Mesh() const {
    return mesh_;
}

computer_graphics::BoxComponent& Sun::Mesh() {
    return mesh_;
}

bool Sun::Intersects(const computer_graphics::Collision& other) const {
    return CollisionPrimitive().Intersects(other);
}

bool Sun::Intersects(const computer_graphics::math::Ray& ray, float& dist) const {
    return CollisionPrimitive().Intersects(ray, dist);
}

computer_graphics::BoxCollision Sun::CollisionPrimitive() const {
    auto [position, rotation, scale] = mesh_.get().WorldTransform();
    rotation.Normalize();

    const computer_graphics::math::Box box{
        position,
        computer_graphics::math::Vector3::One * 0.75f * scale,
        rotation,
    };
    return computer_graphics::BoxCollision{box};
}
