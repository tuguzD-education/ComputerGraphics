#include "uranus_ring.hpp"

#include <computer_graphics/game.hpp>

namespace detail {

computer_graphics::GeometricPrimitiveComponent& CreateUranusRingMesh(
    computer_graphics::Game& game, const computer_graphics::SceneComponent* parent) {
    computer_graphics::GeometricPrimitiveComponent::Initializer initializer{
        .primitive_arguments =
            computer_graphics::TorusGeometricPrimitiveArguments{
                .diameter = 0.8f,
                .thickness = 0.02f,
            },
        .color = computer_graphics::math::colors::linear::GhostWhite.v,
    };
    initializer.parent = parent;
    return game.AddComponent<computer_graphics::GeometricPrimitiveComponent>(initializer);
}

}  // namespace detail

UranusRing::UranusRing(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer), mesh_{detail::CreateUranusRingMesh(Game(), this)} {}

const computer_graphics::GeometricPrimitiveComponent& UranusRing::Mesh() const {
    return mesh_;
}

computer_graphics::GeometricPrimitiveComponent& UranusRing::Mesh() {
    return mesh_;
}
