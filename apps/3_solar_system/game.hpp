#pragma once

#ifndef SOLAR_GAME_HPP_INCLUDED
#define SOLAR_GAME_HPP_INCLUDED

#include <computer_graphics/game.hpp>

#include "celestials/deimos.hpp"
#include "celestials/earth.hpp"
#include "celestials/jupyter.hpp"
#include "celestials/mars.hpp"
#include "celestials/mercury.hpp"
#include "celestials/moon.hpp"
#include "celestials/neptune.hpp"
#include "celestials/phobos.hpp"
#include "celestials/saturn.hpp"
#include "celestials/sun.hpp"
#include "celestials/uranus.hpp"
#include "celestials/venus.hpp"

class Game final : public computer_graphics::Game {
public:
    explicit Game(computer_graphics::Window &window, computer_graphics::Input &input);
    ~Game() override;

protected:
    void Update(float delta_time) override;

private:
    void OnInputKeyDown(computer_graphics::InputKey input_key);

    computer_graphics::Camera &camera_;

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
    Uranus &uranus_;
    Neptune &neptune_;
};

#endif  // SOLAR_GAME_HPP_INCLUDED
