#include "earth.hpp"

#include <computer_graphics/game.hpp>

namespace detail {

computer_graphics::BoxComponent& CreateEarthMesh(
    computer_graphics::Game& game, const computer_graphics::SceneComponent* parent) {
    computer_graphics::BoxComponent::Initializer initializer{
        .length = 0.5f,
        .height = 0.5f,
        .width = 0.5f,
        .color = computer_graphics::math::colors::linear::SpringGreen.v,
    };
    initializer.parent = parent;
    return game.AddComponent<computer_graphics::BoxComponent>(initializer);
}

}  // namespace detail

Earth::Earth(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer), mesh_{detail::CreateEarthMesh(Game(), this)} {}

const computer_graphics::BoxComponent& Earth::Mesh() const {
    return mesh_;
}

computer_graphics::BoxComponent& Earth::Mesh() {
    return mesh_;
}

bool Earth::Intersects(const computer_graphics::Collision& other) const {
    return CollisionPrimitive().Intersects(other);
}

bool Earth::Intersects(const computer_graphics::math::Ray& ray, float& dist) const {
    return CollisionPrimitive().Intersects(ray, dist);
}

computer_graphics::BoxCollision Earth::CollisionPrimitive() const {
    auto [position, rotation, scale] = mesh_.get().WorldTransform();
    rotation.Normalize();

    const computer_graphics::math::Box box{
        position,
        computer_graphics::math::Vector3::One * 0.25f * scale,
        rotation,
    };
    return computer_graphics::BoxCollision{box};
}
