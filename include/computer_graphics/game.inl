#pragma once

#ifndef GAME_INL_INCLUDED
#define GAME_INL_INCLUDED

namespace computer_graphics {

template <typename T, typename... Args>
void Game::AddComponent(Args &&...args) {
    auto component = std::make_unique<T>(*this, std::forward<Args>(args)...);
    components_.push_back(std::move(component));
}

}  // namespace computer_graphics

#endif  // GAME_INL_INCLUDED
