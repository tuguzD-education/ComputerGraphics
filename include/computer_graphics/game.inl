#pragma once

#ifndef GAME_INL_INCLUDED
#define GAME_INL_INCLUDED

namespace computer_graphics {

template <std::derived_from<Component> T, typename... Args>
T &Game::AddComponent(Args &&...args) {
    auto &component = components_.emplace_back(std::make_unique<T>(*this, std::forward<Args>(args)...));
    return dynamic_cast<T &>(*component);
}

}  // namespace computer_graphics

#endif  // GAME_INL_INCLUDED
