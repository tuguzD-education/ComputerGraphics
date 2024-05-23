#pragma once

#ifndef STATIC_DELEGATE_INL_INCLUDED
#define STATIC_DELEGATE_INL_INCLUDED

namespace computer_graphics::delegate {

template <typename R, typename... Args, typename... Payload>
StaticDelegate<R(Args...), Payload...>::StaticDelegate(Function function, Payload &&...payload)
    : function_{function}, payload_{std::forward<Payload>(payload)...} {}

template <typename R, typename... Args, typename... Payload>
R StaticDelegate<R(Args...), Payload...>::Execute(Args &&...args) {
    return Execute_Internal(std::forward<Args>(args)..., std::index_sequence_for<Payload...>());
}

template <typename R, typename... Args, typename... Payload>
template <std::size_t... Is>
R StaticDelegate<R(Args...), Payload...>::Execute_Internal(Args &&...args, std::index_sequence<Is...>) {
    return function_(std::forward<Args>(args)..., std::get<Is>(payload_)...);
}

}  // namespace computer_graphics::delegate

#endif  // STATIC_DELEGATE_INL_INCLUDED
