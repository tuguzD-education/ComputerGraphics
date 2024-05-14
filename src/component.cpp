#include "computer_graphics/component.hpp"

namespace computer_graphics {

Component::Component(Game &game) : game_{game} {}

Component::~Component() = default;

InputDevice *Component::InputDevice() {
    return &game_.get().input_device_;
}

const InputDevice *Component::InputDevice() const {
    return &game_.get().input_device_;
}

Window *Component::Window() {
    return &game_.get().window_;
}

const Window *Component::Window() const {
    return &game_.get().window_;
}

ID3D11DeviceContext *Component::DeviceContext() {
    return game_.get().device_context_.Get();
}

const ID3D11DeviceContext *Component::DeviceContext() const {
    return game_.get().device_context_.Get();
}

ID3D11Device *Component::Device() {
    return game_.get().device_.Get();
}

const ID3D11Device *Component::Device() const {
    return game_.get().device_.Get();
}

const math::Color &Component::ClearColor() const {
    return game_.get().ClearColor();
}

math::Color & Component::ClearColor() {
    return game_.get().ClearColor();
}

const Timer &Component::Timer() const {
    return game_.get().timer_;
}

}  // namespace computer_graphics