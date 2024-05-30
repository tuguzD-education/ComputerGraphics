#include "game.hpp"

int main() {
    computer_graphics::Window window{"Solar system", 800, 800};
    computer_graphics::Input input{window};
    Game game{window, input};

    game.Run();
    return 0;
}
