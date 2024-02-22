#include <computer_graphics/window.hpp>
#include <computer_graphics/game.hpp>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

int main() {
  computer_graphics::Window window{
      TEXT("Application"), 800, 800
  };
  computer_graphics::Game game{window};

  game.Run();
  return 0;
}
