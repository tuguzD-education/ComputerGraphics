#include "computer_graphics/component.hpp"

#include "computer_graphics/game.hpp"

namespace computer_graphics {

Component::Component(Game &game) : game_{game} {}

ID3D11DeviceContext *Component::GetDeviceContext() {
    return game_.get().device_context_.Get();
}

ID3D11Device *Component::GetDevice() {
    return game_.get().device_.Get();
}

}  // namespace computer_graphics
