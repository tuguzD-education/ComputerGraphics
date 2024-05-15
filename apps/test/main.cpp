#include <computer_graphics/input_device.hpp>
#include <iostream>

#include "square_component.hpp"
#include "test_game.hpp"

int main() {
    computer_graphics::Window window{"Application", 800, 800};
    computer_graphics::InputDevice input_device{window};
    TestGame game{window, input_device};

    auto exit_on_escape_key = [&](const auto key) {
        std::cout << "Key: " << static_cast<std::uint16_t>(key) << std::endl;
        if (key == computer_graphics::InputKey::Escape) game.Exit();
    };
    input_device.OnInputKeyDown().AddLambda(exit_on_escape_key);

    game.AddComponent<SquareComponent>();

    game.Run();
    return 0;
}
