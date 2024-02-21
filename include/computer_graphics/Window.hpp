#pragma once

#include <wtypes.h>

namespace computer_graphics {

struct Dimensions {
  LONG width;
  LONG height;
};

class Window {
  public:
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
