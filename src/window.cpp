#include "computer_graphics/window.hpp"

#include <stdexcept>
#include <vector>

#include "computer_graphics/detail/string_api_set.hpp"
#include "computer_graphics/input.hpp"

namespace computer_graphics {

Window::Window(
    const std::string_view name, const std::int32_t width, const std::int32_t height,
    const std::int32_t min_width, const std::int32_t min_height, HINSTANCE instance_handle)
: is_destroyed_{}, min_width_{min_width}, min_height_{min_height}, input_{} {
    instance_handle = (instance_handle != nullptr) ? instance_handle : GetModuleHandle(nullptr);

    const std::basic_string<TCHAR> t_name = detail::MultiByteToTChar(CP_UTF8, 0, name);
    const LPCTSTR c_name = t_name.c_str();

    const auto icon = LoadIcon(nullptr, IDI_WINLOGO);
    WNDCLASSEX wc{
        .cbSize = sizeof(decltype(wc)),
        .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
        .lpfnWndProc = WndProc,
        .cbClsExtra = 0,
        .cbWndExtra = 0,
        .hInstance = instance_handle,
        .hIcon = icon,
        .hCursor = LoadCursor(nullptr, IDC_ARROW),
        .hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)),
        .lpszMenuName = nullptr,
        .lpszClassName = c_name,
        .hIconSm = icon,
    };
    RegisterClassEx(&wc);

    RECT rect = {
        .right = width,
        .bottom = height,
    };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

    handle_ = CreateWindowEx(
        WS_EX_APPWINDOW, c_name, c_name, WS_OVERLAPPEDWINDOW,
        (GetSystemMetrics(SM_CXSCREEN) - width) / 2, (GetSystemMetrics(SM_CYSCREEN) - height) / 2,
        rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, instance_handle, this);

    ShowWindow(handle_, SW_SHOW);
    SetForegroundWindow(handle_);
    SetFocus(handle_);
    ShowCursor(true);
}

bool Window::ErrorBox(const LPCTSTR text, const LPCTSTR caption, const UINT type) const {
    return MessageBox(handle_, text, caption, type);
}

Window::~Window() {
    Destroy();
}

HWND Window::RawHandle() const {
    return handle_;
}

HINSTANCE Window::RawInstanceHandle() const {
    return reinterpret_cast<HINSTANCE>(GetWindowLongPtr(handle_, GWLP_HINSTANCE));
}

math::Rectangle Window::Dimensions() const {
    RECT rect{};
    GetWindowRect(handle_, &rect);
    return math::Rectangle{rect};
}

math::Rectangle Window::ClientDimensions() const {
    RECT rect{};
    ::GetClientRect(handle_, &rect);
    return math::Rectangle{rect};
}

std::int32_t Window::MinWidth() const {
    return min_width_;
}

std::int32_t &Window::MinWidth() {
    return min_width_;
}

std::int32_t Window::MinHeight() const {
    return min_height_;
}

std::int32_t &Window::MinHeight() {
    return min_height_;
}

bool Window::IsDestroyed() const {
    return is_destroyed_;
}

bool Window::IsFocused() const {
    return handle_ == GetFocus();
}

std::string Window::Title() const {
    const auto size = GetWindowTextLength(handle_);
    std::basic_string title(size, TEXT('\0'));
    GetWindowText(handle_, title.data(), size + 1);
    return detail::TCharToMultiByte(CP_UTF8, 0, title);
}

// ReSharper disable once CppMemberFunctionMayBeConst
bool Window::Title(const std::string_view title) {
    const std::basic_string<TCHAR> t_title = detail::MultiByteToTChar(CP_UTF8, 0, title);
    const LPCTSTR c_title = t_title.c_str();
    return SetWindowText(handle_, c_title);
}

const OnWindowResize &Window::OnResize() const {
    return on_resize_;
}

OnWindowResize &Window::OnResize() {
    return on_resize_;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void Window::ProcessQueueMessages() {
    MSG msg;
    while (PeekMessage(&msg, handle_, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// ReSharper disable once CppMemberFunctionMayBeConst
void Window::Destroy() {
    if (IsDestroyed()) {
        return;
    }
    DestroyWindow(handle_);
}

// ReSharper disable once CppParameterMayBeConst
LRESULT CALLBACK Window::WndProc(HWND h_wnd, const UINT u_message, const WPARAM w_param, const LPARAM l_param) {
    Window *window;
    if (u_message == WM_NCCREATE) {
        const auto create_struct = reinterpret_cast<LPCREATESTRUCT>(l_param);
        window = static_cast<Window *>(create_struct->lpCreateParams);
        SetWindowLongPtr(h_wnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
    } else {
        window = reinterpret_cast<Window *>(GetWindowLongPtr(h_wnd, GWLP_USERDATA));
    }
    if (!window)
        return DefWindowProc(h_wnd, u_message, w_param, l_param);

    switch (u_message) {
        case WM_INPUT: {
            Input *input = window->input_;
            if (input == nullptr) break;
            if (!window->IsFocused()) break;

            static std::vector<BYTE> raw_input_bytes;

            UINT size;
            const auto h_raw_input = reinterpret_cast<HRAWINPUT>(l_param);
            UINT result = GetRawInputData(
                h_raw_input, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER));
            if (result) {
                throw std::runtime_error{"Failed to obtain raw input"};
            }

            raw_input_bytes.reserve(size);
            result = GetRawInputData(
                h_raw_input, RID_INPUT, raw_input_bytes.data(), &size, sizeof(RAWINPUTHEADER));
            if (result != size) {
                throw std::runtime_error{"Failed to obtain raw input: GetRawInputData does not return correct size"};
            }

            // ReSharper disable once CppTooWideScopeInitStatement
            const auto raw_input = reinterpret_cast<RAWINPUT *>(raw_input_bytes.data());
            switch (raw_input->header.dwType) {
                case RIM_TYPEKEYBOARD: {
                    input->OnRawKeyboard(raw_input->data.keyboard);
                    break;
                }
                case RIM_TYPEMOUSE: {
                    input->OnRawMouse(raw_input->data.mouse);
                    break;
                }
                default: {
                    break;
                }
            }

            raw_input_bytes.clear();
            break;
        }
        case WM_GETMINMAXINFO: {
            const auto min_max_info = reinterpret_cast<LPMINMAXINFO>(l_param);
            min_max_info->ptMinTrackSize = {
                .x = window->min_width_,
                .y = window->min_height_,
            };
            break;
        }
        case WM_SIZE: {
            const std::int32_t width = LOWORD(l_param);
            const std::int32_t height = HIWORD(l_param);
            window->on_resize_.Broadcast(WindowResizeData{width, height});
            break;
        }
        case WM_CLOSE: {
            window->Destroy();
            break;
        }
        case WM_DESTROY: {
            window->is_destroyed_ = true;
            break;
        }
        default: {
            return DefWindowProc(h_wnd, u_message, w_param, l_param);
        }
    }
    return 0;
}

}  // namespace computer_graphics
