#include "uranus.hpp"

#include <computer_graphics/game.hpp>

namespace detail {

computer_graphics::GeometricPrimitiveComponent& CreateUranusMesh(
    computer_graphics::Game& game, const computer_graphics::SceneComponent* parent) {
    computer_graphics::GeometricPrimitiveComponent::Initializer initializer{
        .primitive_arguments =
            computer_graphics::SphereGeometricPrimitiveArguments{
                .diameter = 0.35f,
                .tessellation = 16,
            },
        .color = computer_graphics::math::colors::linear::LightSkyBlue.v,
    };
    initializer.parent = parent;
    return game.AddComponent<computer_graphics::GeometricPrimitiveComponent>(initializer);
}

}  // namespace detail

Uranus::Uranus(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer), mesh_{detail::CreateUranusMesh(Game(), this)} {}

const computer_graphics::GeometricPrimitiveComponent& Uranus::Mesh() const {
    return mesh_;
}

computer_graphics::GeometricPrimitiveComponent& Uranus::Mesh() {
    return mesh_;
}

bool Uranus::Intersects(const computer_graphics::Collision& other) const {
    return CollisionPrimitive().Intersects(other);
}

bool Uranus::Intersects(const computer_graphics::math::Ray& ray, float& dist) const {
    return CollisionPrimitive().Intersects(ray, dist);
}

computer_graphics::SphereCollision Uranus::CollisionPrimitive() const {
    auto [position, rotation, scale] = mesh_.get().WorldTransform();

    const computer_graphics::math::Sphere sphere{position, 0.185f};
    return computer_graphics::SphereCollision{sphere};
}

// void Uranus::Draw(const computer_graphics::Camera* camera) {
//     SceneComponent::Draw(camera);
//
//     Game().DebugDraw().DrawSphere(CollisionPrimitive().Primitive());
// }
