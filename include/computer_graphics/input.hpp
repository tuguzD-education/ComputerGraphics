#pragma once

#ifndef INPUT_HPP_INCLUDED
#define INPUT_HPP_INCLUDED

#include <unordered_set>

#include "delegate/multicast_delegate.hpp"
#include "input_key.hpp"
#include "window.hpp"

namespace computer_graphics {

struct MouseMoveData {
    math::Vector2 position;
    math::Vector2 offset;
    std::int32_t wheel_delta;
};

struct RawMouse {
    InputKey input_key;
    std::uint32_t flag_down;
    std::uint32_t flag_up;
};

struct RawKeyboard {
    InputKey input_key;
    std::atomic_ushort code;
};

DECLARE_MULTICAST_DELEGATE(OnMouseMove, const MouseMoveData &);
DECLARE_MULTICAST_DELEGATE(OnInputKeyUp, InputKey);
DECLARE_MULTICAST_DELEGATE(OnInputKeyDown, InputKey);

class Input {
  public:
    explicit Input(Window &window);
    ~Input();

    [[nodiscard]] bool IsKeyDown(InputKey key) const;

    [[nodiscard]] const OnMouseMove &OnMouseMove() const;
    [[nodiscard]] computer_graphics::OnMouseMove &OnMouseMove();

    [[nodiscard]] const OnInputKeyUp &OnInputKeyUp() const;
    [[nodiscard]] computer_graphics::OnInputKeyUp &OnInputKeyUp();

    [[nodiscard]] const OnInputKeyDown &OnInputKeyDown() const;
    [[nodiscard]] computer_graphics::OnInputKeyDown &OnInputKeyDown();

  private:
    friend class Window;

    void OnRawKeyboard(const RAWKEYBOARD &data);
    void OnRawMouse(const RAWMOUSE &data);

    void AddPressedKey(InputKey key);
    void RemovePressedKey(InputKey key);

    Window &window_;
    computer_graphics::OnMouseMove on_mouse_move_;
    computer_graphics::OnInputKeyDown on_input_key_down_;
    computer_graphics::OnInputKeyUp on_input_key_up_;
    std::unordered_set<InputKey> keys_;
};

}  // namespace computer_graphics

#endif  // INPUT_HPP_INCLUDED
