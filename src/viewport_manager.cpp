#include "computer_graphics/viewport_manager.hpp"

#include "computer_graphics/camera.hpp"
#include "computer_graphics/game.hpp"

namespace computer_graphics {

ViewportManager::ViewportManager(class Game &game, const Initializer &initializer) : Component(game, initializer) {
    if (initializer.name == "component") {
        Name() = "viewport_manager";
    }
}

const Viewport &ViewportManager::TargetViewport() const {
    return target_viewport_;
}

std::span<const Viewport> ViewportManager::Viewports() const {
    if (split_viewports_.empty()) {
        return {&target_viewport_, 1};
    }
    return split_viewports_;
}

void ViewportManager::Update(float delta_time) {}

void ViewportManager::OnTargetResize() {
    const auto target_width = static_cast<float>(Game().TargetWidth());
    const auto target_height = static_cast<float>(Game().TargetHeight());

    target_viewport_.width = target_width;
    target_viewport_.height = target_height;

    target_viewport_.camera = Game().MainCamera();
    if (target_viewport_.camera != nullptr) {
        target_viewport_.camera->Width(target_width);
        target_viewport_.camera->Height(target_height);
    }

    split_viewports_.clear();
    SplitViewports(split_viewports_);
}

void ViewportManager::SplitViewports(std::vector<Viewport> &into) {}

}  // namespace computer_graphics
