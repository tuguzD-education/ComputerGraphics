#include <computer_graphics/input.hpp>
#include <iostream>

#include "game.hpp"
#include "square_component.hpp"

int main() {
    computer_graphics::Window window{"Application", 800, 800};
    computer_graphics::Input input{window};
    Game game{window, input};

    auto exit_on_escape_key = [&](const auto key) {
        std::cout << "Key: " << static_cast<std::uint16_t>(key) << std::endl;
        if (key == computer_graphics::InputKey::Escape) game.Exit();
    };
    input.OnInputKeyDown().AddLambda(exit_on_escape_key);

    game.AddComponent<SquareComponent>();

    game.Run();
    return 0;
}