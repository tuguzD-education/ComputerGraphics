#include "jupyter.hpp"

#include <computer_graphics/game.hpp>

namespace detail {

computer_graphics::GeometricPrimitiveComponent& CreateJupyterMesh(
    computer_graphics::Game& game, const computer_graphics::SceneComponent* parent) {
    computer_graphics::GeometricPrimitiveComponent::Initializer initializer{
        .primitive_arguments =
            computer_graphics::SphereGeometricPrimitiveArguments{
                .diameter = 1.0f,
            },
        .color = computer_graphics::math::colors::linear::DarkOrange.v,
    };
    initializer.parent = parent;
    return game.AddComponent<computer_graphics::GeometricPrimitiveComponent>(initializer);
}

}  // namespace detail

Jupyter::Jupyter(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer), mesh_{detail::CreateJupyterMesh(Game(), this)} {}

const computer_graphics::GeometricPrimitiveComponent& Jupyter::Mesh() const {
    return mesh_;
}

computer_graphics::GeometricPrimitiveComponent& Jupyter::Mesh() {
    return mesh_;
}

bool Jupyter::Intersects(const computer_graphics::Collision& other) const {
    return CollisionPrimitive().Intersects(other);
}

bool Jupyter::Intersects(const computer_graphics::math::Ray& ray, float& dist) const {
    return CollisionPrimitive().Intersects(ray, dist);
}

computer_graphics::SphereCollision Jupyter::CollisionPrimitive() const {
    auto [position, rotation, scale] = mesh_.get().WorldTransform();

    const computer_graphics::math::Sphere sphere{position, 0.475f};
    return computer_graphics::SphereCollision{sphere};
}
