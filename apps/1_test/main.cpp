#include "game.hpp"
#include "square_component.hpp"

int main() {
    computer_graphics::Window window{"Application", 800, 800};
    computer_graphics::Input input{window};

    Game game{window, input};
    game.AddComponent<SquareComponent>([] {
        SquareComponent::Initializer initializer{};
        initializer.name = "plane";
        return initializer;
    }());

    game.Run();
    return 0;
}
