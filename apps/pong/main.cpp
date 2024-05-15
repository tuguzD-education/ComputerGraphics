#include <computer_graphics/game.hpp>
#include <computer_graphics/input_device.hpp>
#include <computer_graphics/window.hpp>

#include "ball.hpp"
#include "host.hpp"
#include "player.hpp"

int main() {
    computer_graphics::Window window{"Pong", 800, 800};
    computer_graphics::InputDevice input_device{window};
    computer_graphics::Game game{window, input_device};

    auto exit_on_escape_key = [&](const auto key) {
        if (key == computer_graphics::InputKey::Escape) game.Exit();
    };
    input_device.OnInputKeyDown().AddLambda(exit_on_escape_key);

    game.AddComponent<Ball>();
    game.AddComponent<Player>(
        Direction::Left,
        Player::ControlKeys{
            .up = computer_graphics::InputKey::W,
            .down = computer_graphics::InputKey::S,
        }
    );
    game.AddComponent<Player>(
        Direction::Right,
        Player::ControlKeys{
            .up = computer_graphics::InputKey::Up,
            .down = computer_graphics::InputKey::Down,
        }
    );
    game.AddComponent<Host>();

    game.Run();
    return 0;
}
