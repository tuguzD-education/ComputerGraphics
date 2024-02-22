#include <computer_graphics/window.hpp>
#include <computer_graphics/game.hpp>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

int main() {
  constexpr LONG width = 800, height = 800;
  computer_graphics::Window window{
      TEXT("Application"), width, height,
      GetModuleHandle(nullptr),
  };

  computer_graphics::Game game{window};
  game.Run();

  return 0;
}
