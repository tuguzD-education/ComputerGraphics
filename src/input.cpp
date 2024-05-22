#include "computer_graphics/input.hpp"

#include <hidusage.h>

#include <array>
#include <stdexcept>

#include "computer_graphics/detail/err_handling_api.hpp"
#include "computer_graphics/game.hpp"

namespace computer_graphics {

Input::Input(Window &window) : window_{window} {
    std::array raw_input_devices{
        RAWINPUTDEVICE{
            .usUsagePage = HID_USAGE_PAGE_GENERIC,
            .usUsage = HID_USAGE_GENERIC_MOUSE,
            .dwFlags = 0,  // adds HID mouse and also ignores legacy mouse messages
            .hwndTarget = window.RawHandle(),
        },
        RAWINPUTDEVICE{
            .usUsagePage = HID_USAGE_PAGE_GENERIC,
            .usUsage = HID_USAGE_GENERIC_KEYBOARD,
            .dwFlags = 0,  // adds HID keyboard and also ignores legacy keyboard messages
            .hwndTarget = window.RawHandle(),
        },
    };

    if (!RegisterRawInputDevices(
        raw_input_devices.data(), raw_input_devices.size(),
        sizeof(decltype(raw_input_devices)::value_type)
    )) {
        const std::string message = detail::LastError();
        throw std::runtime_error{message};
    }

    assert(window.input_ == nullptr && "Input device already exists");
    window.input_ = this;
}

Input::~Input() {
    window_.input_ = nullptr;
}

bool Input::IsKeyDown(const InputKey key) const {
    return keys_.contains(key);
}

const OnMouseMove &Input::OnMouseMove() const {
    return on_mouse_move_;
}

OnMouseMove &Input::OnMouseMove() {
    return on_mouse_move_;
}

const OnInputKeyUp &Input::OnInputKeyUp() const {
    return on_input_key_up_;
}

OnInputKeyUp &Input::OnInputKeyUp() {
    return on_input_key_up_;
}

const OnInputKeyDown &Input::OnInputKeyDown() const {
    return on_input_key_down_;
}

OnInputKeyDown &Input::OnInputKeyDown() {
    return on_input_key_down_;
}

void Input::OnRawKeyboard(const RAWKEYBOARD &data) {
    const bool is_key_up = data.Flags & RI_KEY_BREAK;

    auto key = static_cast<InputKey>(data.VKey);
    for (const auto &[input_key, code] : raw_keyboard_) {
        if (data.MakeCode == code) key = input_key;
    }

    if (is_key_up) {
        if (IsKeyDown(key)) RemovePressedKey(key);
    } else {
        if (!IsKeyDown(key)) AddPressedKey(key);
    }
}

void Input::OnRawMouse(const RAWMOUSE &data) {
    for (const auto &[input_key, flag_down, flag_up] : raw_mouse_) {
        if (data.usButtonFlags & flag_down) AddPressedKey(input_key);
        if (data.usButtonFlags & flag_up) RemovePressedKey(input_key);
    }

    POINT point;
    ::GetCursorPos(&point);
    ::ScreenToClient(window_.RawHandle(), &point);

    const MouseMoveData mouse_move_data{
        .position = {static_cast<float>(point.x), static_cast<float>(point.y)},
        .offset = {static_cast<float>(data.lLastX), static_cast<float>(data.lLastY)},
        .wheel_delta = static_cast<std::int16_t>(data.usButtonData) / WHEEL_DELTA,
    };
    on_mouse_move_.Broadcast(mouse_move_data);
}

void Input::AddPressedKey(const InputKey key) {
    keys_.insert(key);
    on_input_key_down_.Broadcast(key);
}

void Input::RemovePressedKey(const InputKey key) {
    keys_.erase(key);
    on_input_key_up_.Broadcast(key);
}

}  // namespace computer_graphics
