#include "computer_graphics/game.hpp"
#include "computer_graphics/window.hpp"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

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
