#include "mercury.hpp"

#include <computer_graphics/game.hpp>

namespace detail {

computer_graphics::GeometricPrimitiveComponent& CreateMercuryMesh(
    computer_graphics::Game& game, const computer_graphics::SceneComponent* parent) {
    computer_graphics::GeometricPrimitiveComponent::Initializer initializer{
        .primitive_arguments =
            computer_graphics::CylinderGeometricPrimitiveArguments{
                .height = 0.25f,
                .diameter = 0.25f,
            },
        .color = computer_graphics::math::colors::linear::LightSlateGray.v,
    };
    initializer.parent = parent;
    return game.AddComponent<computer_graphics::GeometricPrimitiveComponent>(initializer);
}

}  // namespace detail

Mercury::Mercury(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer), mesh_{detail::CreateMercuryMesh(Game(), this)} {}

const computer_graphics::GeometricPrimitiveComponent& Mercury::Mesh() const {
    return mesh_;
}

computer_graphics::GeometricPrimitiveComponent& Mercury::Mesh() {
    return mesh_;
}

bool Mercury::Intersects(const computer_graphics::Collision& other) const {
    return CollisionPrimitive().Intersects(other);
}

bool Mercury::Intersects(const computer_graphics::math::Ray& ray, float& dist) const {
    return CollisionPrimitive().Intersects(ray, dist);
}

computer_graphics::SphereCollision Mercury::CollisionPrimitive() const {
    auto [position, rotation, scale] = mesh_.get().WorldTransform();

    const computer_graphics::math::Sphere sphere{position, 0.17f};
    return computer_graphics::SphereCollision{sphere};
}
