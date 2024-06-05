#include "mars.hpp"

#include <computer_graphics/game.hpp>

namespace detail {

computer_graphics::GeometricPrimitiveComponent& CreateMarsMesh(
    computer_graphics::Game& game, const computer_graphics::SceneComponent* parent) {
    computer_graphics::GeometricPrimitiveComponent::Initializer initializer{
        .primitive_arguments =
            computer_graphics::IcosahedronGeometricPrimitiveArguments{
                .size = 0.25f,
            },
        .color = computer_graphics::math::colors::linear::IndianRed.v,
    };
    initializer.parent = parent;
    return game.AddComponent<computer_graphics::GeometricPrimitiveComponent>(initializer);
}

}  // namespace detail

Mars::Mars(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer), mesh_{detail::CreateMarsMesh(Game(), this)} {}

const computer_graphics::GeometricPrimitiveComponent& Mars::Mesh() const {
    return mesh_;
}

computer_graphics::GeometricPrimitiveComponent& Mars::Mesh() {
    return mesh_;
}

bool Mars::Intersects(const computer_graphics::Collision& other) const {
    return CollisionPrimitive().Intersects(other);
}

bool Mars::Intersects(const computer_graphics::math::Ray& ray, float& dist) const {
    return CollisionPrimitive().Intersects(ray, dist);
}

computer_graphics::SphereCollision Mars::CollisionPrimitive() const {
    auto [position, rotation, scale] = mesh_.get().WorldTransform();

    const computer_graphics::math::Sphere sphere{position, 0.25f};
    return computer_graphics::SphereCollision{sphere};
}
