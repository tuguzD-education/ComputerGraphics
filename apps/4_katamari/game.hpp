#pragma once

#ifndef KATAMARI_GAME_HPP_INCLUDED
#define KATAMARI_GAME_HPP_INCLUDED

#include <computer_graphics/game.hpp>

#include "field.hpp"
#include "objects/gear.hpp"
#include "objects/sign.hpp"
#include "player.hpp"

class Game final : public computer_graphics::Game {
  public:
    explicit Game(computer_graphics::Window &window, computer_graphics::Input &input);

    void Update(float delta_time) override;

  private:
    std::reference_wrapper<computer_graphics::Camera> camera_;
    std::reference_wrapper<Field> field_;
    std::reference_wrapper<Player> player_;

    std::reference_wrapper<Sign> sign_;
    std::reference_wrapper<Gear> gear_;
};

#endif  // KATAMARI_GAME_HPP_INCLUDED
