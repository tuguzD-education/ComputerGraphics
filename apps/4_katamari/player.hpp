#pragma once

#ifndef KATAMARI_PLAYER_HPP_INCLUDED
#define KATAMARI_PLAYER_HPP_INCLUDED

#include <computer_graphics/collision.hpp>
#include <computer_graphics/input.hpp>
#include <computer_graphics/mesh_component.hpp>

#include "player_child.hpp"

class Player final : public computer_graphics::MeshComponent<PlayerChild>, public computer_graphics::Collision {
  public:
    struct ControlKeys {
        using enum computer_graphics::InputKey;

        computer_graphics::InputKey left = A;
        computer_graphics::InputKey right = D;
        computer_graphics::InputKey forward = W;
        computer_graphics::InputKey backward = S;
    };

    explicit Player(computer_graphics::Game& game, ControlKeys control_keys = {});

    [[nodiscard]] ControlKeys Controls() const;
    [[nodiscard]] ControlKeys& Controls();

    [[nodiscard]] bool Intersects(const Collision& other) const override;
    [[nodiscard]] bool Intersects(
        const computer_graphics::math::Ray& ray, float& dist) const override;

  private:
    [[nodiscard]] computer_graphics::SphereCollision CollisionPrimitive() const;

    ControlKeys control_keys_;
};

#endif  // KATAMARI_PLAYER_HPP_INCLUDED
