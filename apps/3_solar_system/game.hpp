#pragma once

#ifndef SOLAR_GAME_HPP_INCLUDED
#define SOLAR_GAME_HPP_INCLUDED

#include <computer_graphics/game.hpp>

#include "celestials/earth/earth.hpp"
#include "celestials/earth/moon.hpp"
#include "celestials/jupyter.hpp"
#include "celestials/mars/deimos.hpp"
#include "celestials/mars/mars.hpp"
#include "celestials/mars/phobos.hpp"
#include "celestials/mercury.hpp"
#include "celestials/neptune.hpp"
#include "celestials/saturn/saturn.hpp"
#include "celestials/saturn/saturn_ring.hpp"
#include "celestials/sun.hpp"
#include "celestials/uranus/uranus.hpp"
#include "celestials/uranus/uranus_ring.hpp"
#include "celestials/venus.hpp"
#include "skybox.hpp"

class Game final : public computer_graphics::Game {
  public:
    explicit Game(computer_graphics::Window &window, computer_graphics::Input &input);
    ~Game() override;

  protected:
    void Update(float delta_time) override;

  private:
    void OnInputKeyDown(computer_graphics::InputKey input_key);

    computer_graphics::Camera &camera_;
    Skybox &skybox_;

    Sun &sun_;

    Mercury &mercury_;
    Venus &venus_;

    Earth &earth_;
    Moon &moon_;

    Mars &mars_;
    Phobos &phobos_;
    Deimos &deimos_;

    Jupyter &jupyter_;

    Saturn &saturn_;
    SaturnRing &saturn_ring_;

    Uranus &uranus_;
    UranusRing &uranus_ring_;

    Neptune &neptune_;
};

#endif  // SOLAR_GAME_HPP_INCLUDED
