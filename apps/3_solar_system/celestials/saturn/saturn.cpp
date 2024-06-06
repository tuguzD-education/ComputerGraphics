#include "saturn.hpp"

#include <computer_graphics/game.hpp>

namespace detail {

computer_graphics::GeometricPrimitiveComponent& CreateSaturnMesh(
    computer_graphics::Game& game, const computer_graphics::SceneComponent* parent) {
    computer_graphics::GeometricPrimitiveComponent::Initializer initializer{
        .primitive_arguments =
            computer_graphics::DodecahedronGeometricPrimitiveArguments{
                .size = 0.25f,
            },
        .color = computer_graphics::math::colors::linear::LightGoldenrodYellow.v,
    };
    initializer.parent = parent;
    return game.AddComponent<computer_graphics::GeometricPrimitiveComponent>(initializer);
}

}  // namespace detail

Saturn::Saturn(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer), mesh_{detail::CreateSaturnMesh(Game(), this)} {}

const computer_graphics::GeometricPrimitiveComponent& Saturn::Mesh() const {
    return mesh_;
}

computer_graphics::GeometricPrimitiveComponent& Saturn::Mesh() {
    return mesh_;
}

bool Saturn::Intersects(const computer_graphics::Collision& other) const {
    return CollisionPrimitive().Intersects(other);
}

bool Saturn::Intersects(const computer_graphics::math::Ray& ray, float& dist) const {
    return CollisionPrimitive().Intersects(ray, dist);
}

computer_graphics::SphereCollision Saturn::CollisionPrimitive() const {
    auto [position, rotation, scale] = mesh_.get().WorldTransform();

    const computer_graphics::math::Sphere sphere{position, 0.235f};
    return computer_graphics::SphereCollision{sphere};
}
