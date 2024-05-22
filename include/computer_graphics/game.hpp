#pragma once

#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <d3d11.h>

#include <memory>
#include <span>
#include <vector>

#include "detail/d3d_ptr.hpp"
#include "timer.hpp"
#include "window.hpp"

namespace computer_graphics {

class Game {
  private:
    friend class Component;

  public:
    explicit Game(Window &window, Input &input);
    virtual ~Game();

    [[nodiscard]] const Timer::Duration &TimePerUpdate() const;
    void TimePerUpdate(Timer::Duration time_per_update);

    [[nodiscard]] const math::Color &ClearColor() const;
    [[nodiscard]] math::Color &ClearColor();

    [[nodiscard]] const Window *Window() const;
    [[nodiscard]] class Window *Window();

    [[nodiscard]] const Timer& Timer() const;
    [[nodiscard]] class Timer& Timer();

    [[nodiscard]] bool IsRunning() const;

    template <std::derived_from<Component> T, typename... Args>
    T &AddComponent(Args &&...args);

    [[nodiscard]] std::span<const std::unique_ptr<Component>> Components() const;

    void Run();
    void Exit();

  protected:
    virtual void Update(float delta_time);
    virtual void Draw();

  private:
    void InitializeDevice();
    void InitializeSwapChain(const class Window &window);
    void InitializeRenderTargetView();

    void DrawInternal();

    [[nodiscard]] std::span<std::unique_ptr<Component>> Components();

    class Timer timer_;
    Timer::Duration time_per_update_;

    Input &input_;

    class Window &window_;
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
