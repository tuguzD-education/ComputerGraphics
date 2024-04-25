#include "computer_graphics/game.hpp"
#include "computer_graphics/window.hpp"

int main() {
    computer_graphics::Window window{
        "Application",
        800,
        800,
    };
    computer_graphics::Game game{
        window,
    };

    game.Run();
    return 0;
}
