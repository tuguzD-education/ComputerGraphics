#pragma once

#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <d3d11.h>

#include <memory>
#include <vector>

#include "detail/d3d_ptr.hpp"
#include "timer.hpp"
#include "window.hpp"

namespace computer_graphics {

class Game {
  public:
    explicit Game(Window &window, InputDevice &input_device);
    ~Game();

    [[nodiscard]] const Timer::Duration &TimePerUpdate() const;
    void TimePerUpdate(Timer::Duration time_per_update);

    [[nodiscard]] const math::Color &ClearColor() const;
    [[nodiscard]] math::Color &ClearColor();

    [[nodiscard]] bool IsRunning() const;

    template <typename T, typename... Args>
    void AddComponent(Args &&...args);

    void Run();
    void Exit();

  private:
    friend class Component;

    void InitializeDevice();
    void InitializeSwapChain(const Window &window);
    void InitializeRenderTargetView();

    void Update(float delta_time);
    void Draw();

    Timer timer_;
    Timer::Duration time_per_update_;

    InputDevice &input_device_;

    Window &window_;
    UINT target_width_;
    UINT target_height_;

    math::Color clear_color_;
    bool should_exit_;
    bool is_running_;

    std::vector<std::unique_ptr<Component>> components_;

    detail::D3DPtr<ID3D11RenderTargetView> render_target_view_;
    detail::D3DPtr<IDXGISwapChain> swap_chain_;
    detail::D3DPtr<ID3D11DeviceContext> device_context_;
    detail::D3DPtr<ID3D11Device> device_;
};

}  // namespace computer_graphics

#include "game.inl"

#endif  // GAME_HPP_INCLUDED
