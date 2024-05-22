#include <computer_graphics/game.hpp>
#include <computer_graphics/input.hpp>
#include <computer_graphics/window.hpp>

#include "game.hpp"

int main() {
    computer_graphics::Window window{"PONG", 800, 800};
    computer_graphics::Input input{window};
    Game game{window, input};

    auto exit_on_escape_key = [&](const auto key) {
        if (key == computer_graphics::InputKey::Escape) game.Exit();
    };
    input.OnInputKeyDown().AddLambda(exit_on_escape_key);

    game.Run();
    return 0;
}
