#include "neptune.hpp"

#include <computer_graphics/game.hpp>

namespace detail {

computer_graphics::GeometricPrimitiveComponent& CreateNeptuneMesh(
    computer_graphics::Game& game, const computer_graphics::SceneComponent* parent) {
    computer_graphics::GeometricPrimitiveComponent::Initializer initializer{
        .primitive_arguments =
            computer_graphics::DodecahedronGeometricPrimitiveArguments{
                .size = 0.75f,
            },
        .color = computer_graphics::math::colors::linear::BlueViolet.v,
    };
    initializer.Parent(parent);
    return game.AddComponent<computer_graphics::GeometricPrimitiveComponent>(initializer);
}

}  // namespace detail

Neptune::Neptune(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer), mesh_{detail::CreateNeptuneMesh(Game(), this)} {}

const computer_graphics::GeometricPrimitiveComponent& Neptune::Mesh() const {
    return mesh_;
}

computer_graphics::GeometricPrimitiveComponent& Neptune::Mesh() {
    return mesh_;
}

bool Neptune::Intersects(const computer_graphics::Collision& other) const {
    return CollisionPrimitive().Intersects(other);
}

bool Neptune::Intersects(const computer_graphics::math::Ray& ray, float& dist) const {
    return CollisionPrimitive().Intersects(ray, dist);
}

computer_graphics::SphereCollision Neptune::CollisionPrimitive() const {
    auto [position, rotation, scale] = mesh_.get().WorldTransform();

    const computer_graphics::math::Sphere sphere{position, 0.375f};
    return computer_graphics::SphereCollision{sphere};
}
