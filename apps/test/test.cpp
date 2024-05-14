#include <iostream>

#include "computer_graphics/game.hpp"
#include "computer_graphics/input_device.hpp"
#include "computer_graphics/window.hpp"

int main() {
    computer_graphics::Window window{"Application", 800, 800};
    computer_graphics::InputDevice input_device{window};
    computer_graphics::Game game{window};

    auto exit_on_escape_key = [&](const auto key) {
        std::cout << "Key: " << static_cast<std::uint16_t>(key) << std::endl;
        if (key == computer_graphics::InputKey::Escape) game.Exit();
    };
    input_device.GetOnInputKeyDown().AddLambda(exit_on_escape_key);

    game.Run();
    return 0;
}
