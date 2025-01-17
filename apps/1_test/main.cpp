#include "game.hpp"
#include "square_component.hpp"
#include "square_component_alt.hpp"

int main() {
    computer_graphics::Window window{"Application", 800, 800};
    computer_graphics::Input input{window};

    Game game{window, input};
    game.AddComponent<SquareComponent>();
    game.AddComponent<SquareComponentAlt>();

    game.Run();
    return 0;
}
