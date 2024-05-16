#include "computer_graphics/input_device.hpp"

#include <hidusage.h>

#include <array>
#include <stdexcept>

#include "computer_graphics/detail/err_handling_api.hpp"
#include "computer_graphics/game.hpp"

namespace computer_graphics {

InputDevice::InputDevice(Window &window) : window_{window}, mouse_move_data_{} {
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

    assert(window.input_device_ == nullptr && "Input device already exists");
    window.input_device_ = this;
}

InputDevice::~InputDevice() {
    window_.input_device_ = nullptr;
}

bool InputDevice::IsKeyDown(const InputKey key) const {
    return keys_.contains(key);
}

const MouseMoveData &InputDevice::MouseMoveData() const {
    return mouse_move_data_;
}

MouseMoveData &InputDevice::MouseMoveData() {
    return mouse_move_data_;
}

const OnMouseMove &InputDevice::OnMouseMove() const {
    return on_mouse_move_;
}

OnMouseMove &InputDevice::OnMouseMove() {
    return on_mouse_move_;
}

const OnInputKeyUp &InputDevice::OnInputKeyUp() const {
    return on_input_key_up_;
}

OnInputKeyUp &InputDevice::OnInputKeyUp() {
    return on_input_key_up_;
}

const OnInputKeyDown &InputDevice::OnInputKeyDown() const {
    return on_input_key_up_;
}

OnInputKeyDown &InputDevice::OnInputKeyDown() {
    return on_input_key_up_;
}

void InputDevice::OnRawKeyboard(const RAWKEYBOARD &data) {
    const bool is_key_up = data.Flags & RI_KEY_BREAK;

    auto key = static_cast<InputKey>(data.VKey);
    if (data.MakeCode == 42) {
        key = InputKey::LeftShift;
    } else if (data.MakeCode == 54) {
        key = InputKey::RightShift;
    }

    if (is_key_up) {
        if (IsKeyDown(key)) RemovePressedKey(key);
    } else {
        if (!IsKeyDown(key)) AddPressedKey(key);
    }
}

void InputDevice::OnRawMouse(const RAWMOUSE &data) {
    if (data.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN) {
        AddPressedKey(InputKey::LeftButton);
    }
    if (data.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP) {
        RemovePressedKey(InputKey::LeftButton);
    }
    if (data.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN) {
        AddPressedKey(InputKey::RightButton);
    }
    if (data.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP) {
        RemovePressedKey(InputKey::RightButton);
    }
    if (data.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN) {
        AddPressedKey(InputKey::MiddleButton);
    }
    if (data.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP) {
        RemovePressedKey(InputKey::MiddleButton);
    }

    POINT point;
    ::GetCursorPos(&point);
    ::ScreenToClient(window_.RawHandle(), &point);

    mouse_move_data_ = {
        .position = {static_cast<float>(point.x), static_cast<float>(point.y)},
        .offset = {static_cast<float>(data.lLastX), static_cast<float>(data.lLastY)},
        .wheel_delta = data.usButtonData,
    };
    on_mouse_move_.Broadcast(mouse_move_data_);
}

void InputDevice::AddPressedKey(const InputKey key) {
    keys_.insert(key);
    on_input_key_down_.Broadcast(key);
}

void InputDevice::RemovePressedKey(const InputKey key) {
    keys_.erase(key);
    on_input_key_up_.Broadcast(key);
}

}  // namespace computer_graphics
