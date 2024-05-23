#pragma once

#ifndef RAW_DELEGATE_INL_INCLUDED
#define RAW_DELEGATE_INL_INCLUDED

namespace computer_graphics::delegate {

template <bool IsConst, typename T, typename R, typename... Args, typename... Payload>
RawDelegate<IsConst, T, R(Args...), Payload...>::RawDelegate(T *object, Function function, Payload &&...payload)
    : object_{object}, function_{function}, payload_{std::forward<Payload>(payload)...} {}

template <bool IsConst, typename T, typename R, typename... Args, typename... Payload>
R RawDelegate<IsConst, T, R(Args...), Payload...>::Execute(Args &&...args) {
    return Execute_Internal(std::forward<Args>(args)..., std::index_sequence_for<Payload...>());
}

template <bool IsConst, typename T, typename R, typename... Args, typename... Payload>
const void *RawDelegate<IsConst, T, R(Args...), Payload...>::Owner() const {
    return object_;
}

template <bool IsConst, typename T, typename R, typename... Args, typename... Payload>
template <std::size_t... Is>
R RawDelegate<IsConst, T, R(Args...), Payload...>::Execute_Internal(Args &&...args, std::index_sequence<Is...>) {
    return (object_->*function_)(std::forward<Args>(args)..., std::get<Is>(payload_)...);
}

}  // namespace computer_graphics::delegate

#endif  // RAW_DELEGATE_INL_INCLUDED
