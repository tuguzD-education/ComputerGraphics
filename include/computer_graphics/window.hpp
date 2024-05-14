#pragma once

#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include <windows.h>

#include <string_view>

namespace computer_graphics {

class Window {
  public:
    struct Dimensions {
        LONG width;
        LONG height;
    };

    explicit Window(
        std::string_view name, LONG width,
        LONG height, HINSTANCE instance_handle = nullptr
    );

    bool ErrorBox(LPCTSTR text, LPCTSTR caption, UINT type = MB_OK);

    [[nodiscard]] HWND GetRawHandle() const;
    [[nodiscard]] HINSTANCE GetRawInstanceHandle() const;

    [[nodiscard]] RECT GetRect() const;
    [[nodiscard]] Dimensions GetDimensions() const;

    [[nodiscard]] RECT GetClientRect() const;
    [[nodiscard]] Dimensions GetClientDimensions() const;

    [[nodiscard]] bool IsDestroyed() const;

    bool SetTitle(std::string_view title);
    void ProcessQueueMessages();
    void Destroy();

  private:
    friend class InputDevice;

    static LRESULT CALLBACK WndProc(
        HWND h_wnd, UINT u_message, WPARAM w_param, LPARAM l_param
    );

    HWND handle_;
    InputDevice *input_device_;
    bool is_destroyed_;
};

}  // namespace computer_graphics

#endif  // WINDOW_HPP_INCLUDED
