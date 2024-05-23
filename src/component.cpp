#include "computer_graphics/component.hpp"

#include "computer_graphics/game.hpp"

namespace computer_graphics {

Component::Component(class Game &game, const Initializer &initializer) : game_{game}, name_{initializer.name} {}

Component::~Component() = default;

void Component::Update(float delta_time) {}

void Component::Draw(const Camera *camera) {}

void Component::OnTargetResize() {}

Game &Component::Game() {
    return game_;
}

const Game &Component::Game() const {
    return game_;
}

ID3D11DeviceContext &Component::DeviceContext() {
    return *Game().device_context_.Get();
}

const ID3D11DeviceContext &Component::DeviceContext() const {
    return *Game().device_context_.Get();
}

ID3D11Device &Component::Device() {
    return *Game().device_.Get();
}

const ID3D11Device &Component::Device() const {
    return *Game().device_.Get();
}

std::string &Component::Name() {
    return name_;
}

const std::string &Component::Name() const {
    return name_;
}

}  // namespace computer_graphics
