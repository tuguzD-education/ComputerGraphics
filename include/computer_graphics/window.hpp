#pragma once

#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include <windows.h>

namespace computer_graphics {

class Window {
  public:
    struct Dimensions {
      LONG width;
      LONG height;
    };

    explicit Window(LPCTSTR name, LONG width, LONG height, HINSTANCE instanceHandle = nullptr);

    bool ErrorBox(LPCTSTR lpText, LPCTSTR lpCaption, UINT uType = MB_OK);

    [[nodiscard]] HWND GetRawHandle() const;
    [[nodiscard]] HINSTANCE GetRawInstanceHandle() const;

    [[nodiscard]] RECT GetRect() const;
    [[nodiscard]] Dimensions GetDimensions() const;

    [[nodiscard]] RECT GetClientRect() const;
    [[nodiscard]] Dimensions GetClientDimensions() const;

    bool SetTitle(LPCTSTR title);

  private:
    HWND handle;
};

}

#endif //WINDOW_HPP_INCLUDED
