#pragma once

#ifndef GAME_INL_INCLUDED
#define GAME_INL_INCLUDED

namespace computer_graphics {

template <std::derived_from<class CameraManager> T, typename... Args>
T &Game::CameraManager(Args &&...args) {
    camera_manager_ = std::make_unique<T>(*this, std::forward<Args>(args)...);
    if (viewport_manager_ != nullptr) {
        viewport_manager_->OnTargetResize();
    }
    return dynamic_cast<T &>(*camera_manager_);
}

template <std::derived_from<class ViewportManager> T, typename... Args>
T &Game::ViewportManager(Args &&...args) {
    viewport_manager_ = std::make_unique<T>(*this, std::forward<Args>(args)...);
    viewport_manager_->OnTargetResize();
    return dynamic_cast<T &>(*viewport_manager_);
}

template <std::derived_from<class DebugDraw> T, typename... Args>
T &Game::DebugDraw(Args &&...args) {
    debug_draw_ = std::make_unique<T>(*this, std::forward<Args>(args)...);
    return dynamic_cast<T &>(*debug_draw_);
}

template <std::derived_from<Component> T, typename... Args>
T &Game::AddComponent(Args &&...args) {
    auto &component = components_.emplace_back(
        std::make_unique<T>(*this, std::forward<Args>(args)...));
    return dynamic_cast<T &>(*component);
}

inline ConstComponentRange auto Game::Components() const {
    auto unique_ptr_to_ref = [](const std::unique_ptr<Component> &component) {
        return std::cref(*component);
    };
    return components_ | std::ranges::views::transform(unique_ptr_to_ref);
}

inline ComponentRange auto Game::Components() {
    auto unique_ptr_to_ref = [](const std::unique_ptr<Component> &component) {
        return std::ref(*component);
    };
    return components_ | std::ranges::views::transform(unique_ptr_to_ref);
}

}  // namespace computer_graphics

#endif  // GAME_INL_INCLUDED
