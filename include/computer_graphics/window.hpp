#pragma once

#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include <windows.h>

#include <string>

#include "delegate/multicast_delegate.hpp"
#include "math.hpp"

namespace computer_graphics {

struct WindowResizeData {
    std::int32_t width;
    std::int32_t height;
};

DECLARE_MULTICAST_DELEGATE(OnWindowResize, WindowResizeData);

class Window {
  public:
    explicit Window(
        std::string_view name, std::int32_t width, std::int32_t height,
        std::int32_t min_width = 400, std::int32_t min_height = 400,
        HINSTANCE instance_handle = nullptr);
    ~Window();

    bool ErrorBox(LPCTSTR text, LPCTSTR caption, UINT type = MB_OK) const;

    [[nodiscard]] HWND RawHandle() const;
    [[nodiscard]] HINSTANCE RawInstanceHandle() const;

    [[nodiscard]] math::Rectangle Dimensions() const;
    [[nodiscard]] math::Rectangle ClientDimensions() const;

    [[nodiscard]] std::int32_t MinWidth() const;
    [[nodiscard]] std::int32_t &MinWidth();

    [[nodiscard]] std::int32_t MinHeight() const;
    [[nodiscard]] std::int32_t &MinHeight();

    [[nodiscard]] math::Point CursorPosition() const;
    bool CursorPosition(math::Point cursor_position);

    [[nodiscard]] bool IsDestroyed() const;
    [[nodiscard]] bool IsFocused() const;

    [[nodiscard]] std::string Title() const;
    bool Title(std::string_view title);

    [[nodiscard]] const OnWindowResize &OnResize() const;
    [[nodiscard]] OnWindowResize &OnResize();

    void ProcessQueueMessages();
    void Destroy();

  private:
    friend class Input;

    static LRESULT CALLBACK WndProc(
        HWND h_wnd, UINT u_message, WPARAM w_param, LPARAM l_param);

    HWND handle_;
    bool is_destroyed_;

    std::int32_t min_width_;
    std::int32_t min_height_;

    Input *input_;
    OnWindowResize on_resize_;
};

}  // namespace computer_graphics

#endif  // WINDOW_HPP_INCLUDED
