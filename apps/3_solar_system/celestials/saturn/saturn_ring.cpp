#include "saturn_ring.hpp"

#include <computer_graphics/game.hpp>

namespace detail {

computer_graphics::GeometricPrimitiveComponent& CreateSaturnRingMesh(
    computer_graphics::Game& game, const computer_graphics::SceneComponent* parent) {
    computer_graphics::GeometricPrimitiveComponent::Initializer initializer{
        .primitive_arguments =
            computer_graphics::TorusGeometricPrimitiveArguments{
                .diameter = 0.7f,
                .thickness = 0.075f,
            },
        .color = computer_graphics::math::colors::linear::SandyBrown.v,
    };
    initializer.Parent(parent);
    return game.AddComponent<computer_graphics::GeometricPrimitiveComponent>(initializer);
}

}  // namespace detail

SaturnRing::SaturnRing(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer), mesh_{detail::CreateSaturnRingMesh(Game(), this)} {}

const computer_graphics::GeometricPrimitiveComponent& SaturnRing::Mesh() const {
    return mesh_;
}

computer_graphics::GeometricPrimitiveComponent& SaturnRing::Mesh() {
    return mesh_;
}
