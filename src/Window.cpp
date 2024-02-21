#include <computer_graphics/window.hpp>

#include <winuser.h>
#include <iostream>

namespace computer_graphics {

namespace detail {

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {
  switch (uMessage) {
    case WM_KEYDOWN: {
      // If a key is pressed send it to the input object, so it can record that state.
      std::cout << "Key: " << static_cast<unsigned int>(wParam) << std::endl;

      if (static_cast<unsigned int>(wParam) == 27) {
        PostQuitMessage(0);
        std::cout << "Hello World!\n";
      }
      break;
    }
    case WM_CLOSE: {
      DestroyWindow(hWnd);
      break;
    }
    case WM_DESTROY: {
      PostQuitMessage(0);
      break;
    }
    default: {
      return DefWindowProc(hWnd, uMessage, wParam, lParam);
    }
  }
  return 0;
}

}

Window::Window(LPCTSTR name, LONG width, LONG height, HINSTANCE instanceHandle) {
  instanceHandle = (instanceHandle != nullptr) ? instanceHandle : GetModuleHandle(nullptr);

  auto icon = LoadIcon(nullptr, IDI_WINLOGO);
  WNDCLASSEX wc{
      .cbSize = sizeof(WNDCLASSEX),
      .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
      .lpfnWndProc = detail::WndProc,
      .cbClsExtra = 0, .cbWndExtra = 0,
      .hInstance = instanceHandle,
      .hIcon = icon,
      .hCursor = LoadCursor(nullptr, IDC_ARROW),
      .hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)),
      .lpszMenuName = nullptr,
      .lpszClassName = name,
      .hIconSm = icon,
  };
  RegisterClassEx(&wc);

  RECT rect = {
      .left = 0,
      .top = 0,
      .right = static_cast<LONG>(width),
      .bottom = static_cast<LONG>(height),
  };
  AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

  handle = CreateWindowEx(
      WS_EX_APPWINDOW,name,name,
      WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME,
      (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
      (GetSystemMetrics(SM_CYSCREEN) - height) / 2,
      rect.right - rect.left,rect.bottom - rect.top,
      nullptr, nullptr,
      instanceHandle, nullptr
  );
  ShowWindow(handle, SW_SHOW);
  SetForegroundWindow(handle);
  SetFocus(handle);
  ShowCursor(true);
}

bool Window::ErrorBox(LPCTSTR lpText, LPCTSTR lpCaption, UINT uType) {
  return MessageBox(handle, lpText, lpCaption, uType);
}

HWND Window::GetRawHandle() const {
  return handle;
}

HINSTANCE Window::GetRawInstanceHandle() const {
  return (HINSTANCE) GetWindowLongPtr(handle, GWLP_HINSTANCE);
}

RECT Window::GetRect() const {
  RECT rect{};
  GetWindowRect(handle, &rect);
  return rect;
}

Dimensions Window::GetDimensions() const {
  RECT rect = GetRect();
  return Dimensions{
      .width = rect.right - rect.left,
      .height = rect.bottom - rect.top,
  };
}

RECT Window::GetClientRect() const {
  RECT rect{};
  ::GetClientRect(handle, &rect);
  return rect;
}

Dimensions Window::GetClientDimensions() const {
  RECT rect = GetClientRect();
  return Dimensions{
      .width = rect.right - rect.left,
      .height = rect.bottom - rect.top,
  };
}

bool Window::SetTitle(LPCTSTR title) {
  return SetWindowText(handle, title);
}

}
