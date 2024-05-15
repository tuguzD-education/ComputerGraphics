#include <computer_graphics/game.hpp>
#include <computer_graphics/input_device.hpp>
#include <computer_graphics/window.hpp>

#include "game.hpp"

int main() {
    computer_graphics::Window window{"PONG", 800, 800};
    computer_graphics::InputDevice input_device{window};
    Game game{window, input_device};

    auto exit_on_escape_key = [&](const auto key) {
        if (key == computer_graphics::InputKey::Escape) game.Exit();
    };
    input_device.OnInputKeyDown().AddLambda(exit_on_escape_key);

    game.Run();
    return 0;
}
