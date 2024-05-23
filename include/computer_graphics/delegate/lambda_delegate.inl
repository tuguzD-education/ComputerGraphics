#pragma once

#ifndef LAMBDA_DELEGATE_INL_INCLUDED
#define LAMBDA_DELEGATE_INL_INCLUDED

namespace computer_graphics::delegate {

template <typename Lambda, typename R, typename... Args, typename... Payload>
LambdaDelegate<Lambda, R(Args...), Payload...>::LambdaDelegate(Lambda &&lambda, Payload &&...payload)
    : lambda_{std::forward<Lambda>(lambda)}, payload_{std::forward<Payload>(payload)...} {}

template <typename Lambda, typename R, typename... Args, typename... Payload>
R LambdaDelegate<Lambda, R(Args...), Payload...>::Execute(Args &&...args) {
    return Execute_Internal(std::forward<Args>(args)..., std::index_sequence_for<Payload...>());
}

template <typename Lambda, typename R, typename... Args, typename... Payload>
template <std::size_t... Is>
R LambdaDelegate<Lambda, R(Args...), Payload...>::Execute_Internal(Args &&...args, std::index_sequence<Is...>) {
    return lambda_(std::forward<Args>(args)..., std::get<Is>(payload_)...);
}

}  // namespace computer_graphics::delegate

#endif  // LAMBDA_DELEGATE_INL_INCLUDED
