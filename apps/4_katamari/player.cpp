#include "player.hpp"

Player::Player(computer_graphics::Game& game, const ControlKeys control_keys)
    : MeshComponent(game, [] {
        Initializer initializer{.mesh_path = "resources/meshes/katamari/katamari.fbx"};
        initializer.transform = computer_graphics::Transform{
            .position = computer_graphics::math::Vector3::Up / 2.0f,
            .scale = computer_graphics::math::Vector3::One / 200.0f,
        };
        return initializer;
    }()), control_keys_{control_keys} {}

auto Player::Controls() const -> ControlKeys {
    return control_keys_;
}

auto Player::Controls() -> ControlKeys& {
    return control_keys_;
}

bool Player::Intersects(const Collision& other) const {
    return CollisionPrimitive().Intersects(other);
}

bool Player::Intersects(const computer_graphics::math::Ray& ray, float& dist) const {
    return CollisionPrimitive().Intersects(ray, dist);
}

computer_graphics::SphereCollision Player::CollisionPrimitive() const {
    const computer_graphics::math::Sphere sphere{WorldTransform().position, 0.5f};
    return computer_graphics::SphereCollision{sphere};
}
