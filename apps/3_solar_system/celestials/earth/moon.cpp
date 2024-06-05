#include "moon.hpp"

#include <computer_graphics/game.hpp>

namespace detail {

computer_graphics::GeometricPrimitiveComponent& CreateMoonMesh(
    computer_graphics::Game& game, const computer_graphics::SceneComponent* parent) {
    computer_graphics::GeometricPrimitiveComponent::Initializer initializer{
        .primitive_arguments =
            computer_graphics::OctahedronGeometricPrimitiveArguments{
                .size = 0.1f,
            },
        .color = computer_graphics::math::colors::linear::LightGray.v,
    };
    initializer.parent = parent;
    return game.AddComponent<computer_graphics::GeometricPrimitiveComponent>(initializer);
}

}  // namespace detail

Moon::Moon(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer), mesh_{detail::CreateMoonMesh(Game(), this)} {}

const computer_graphics::GeometricPrimitiveComponent& Moon::Mesh() const {
    return mesh_;
}

computer_graphics::GeometricPrimitiveComponent& Moon::Mesh() {
    return mesh_;
}

bool Moon::Intersects(const computer_graphics::Collision& other) const {
    return CollisionPrimitive().Intersects(other);
}

bool Moon::Intersects(const computer_graphics::math::Ray& ray, float& dist) const {
    return CollisionPrimitive().Intersects(ray, dist);
}

computer_graphics::SphereCollision Moon::CollisionPrimitive() const {
    auto [position, rotation, scale] = mesh_.get().WorldTransform();

    const computer_graphics::math::Sphere sphere{position, 0.05f};
    return computer_graphics::SphereCollision{sphere};
}
