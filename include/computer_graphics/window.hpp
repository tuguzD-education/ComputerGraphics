#pragma once

#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include <windows.h>

#include <string>

#include "math.hpp"

namespace computer_graphics {

class Window {
  public:
    explicit Window(std::string_view name, LONG width, LONG height, HINSTANCE instance_handle = nullptr);
    ~Window();

    bool ErrorBox(LPCTSTR text, LPCTSTR caption, UINT type = MB_OK) const;

    [[nodiscard]] HWND RawHandle() const;
    [[nodiscard]] HINSTANCE RawInstanceHandle() const;

    [[nodiscard]] math::Rectangle Dimensions() const;
    [[nodiscard]] math::Rectangle ClientDimensions() const;

    [[nodiscard]] bool IsDestroyed() const;
    [[nodiscard]] bool IsFocused() const;

    [[nodiscard]] std::string Title() const;
    bool Title(std::string_view title);

    void ProcessQueueMessages() const;
    void Destroy() const;

  private:
    friend class InputDevice;

    static LRESULT CALLBACK WndProc(HWND h_wnd, UINT u_message, WPARAM w_param, LPARAM l_param);

    HWND handle_;
    InputDevice *input_device_;
    bool is_destroyed_;
};

}  // namespace computer_graphics

#endif  // WINDOW_HPP_INCLUDED
