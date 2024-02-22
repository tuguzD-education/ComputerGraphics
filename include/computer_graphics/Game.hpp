#pragma once

#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <d3d11.h>
#include <wrl/client.h>

#include "timer.hpp"
#include "window.hpp"

namespace computer_graphics {

class Game {
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

  public:
    explicit Game(Window &window);

    void Run();

    [[nodiscard]] const Timer &GetTimer() const;

  private:
    void InitializeDevice();
    void InitializeSwapChain(const Window &window);
    void InitializeRenderTargetView();

    ComPtr<ID3D11RenderTargetView> render_target_view_;
    ComPtr<IDXGISwapChain> swap_chain_;
    ComPtr<ID3D11DeviceContext> device_context_;
    ComPtr<ID3D11Device> device_;

    Timer timer_;
    Window &window_;
};

}

#endif //GAME_HPP_INCLUDED
