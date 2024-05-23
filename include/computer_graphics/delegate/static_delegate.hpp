#pragma once

#ifndef STATIC_DELEGATE_HPP_INCLUDED
#define STATIC_DELEGATE_HPP_INCLUDED

#include <tuple>

#include "delegate_kind.hpp"

namespace computer_graphics::delegate {

template <typename FunctionType, typename... Payload>
class StaticDelegate;

template <typename R, typename... Args, typename... Payload>
class StaticDelegate<R(Args...), Payload...> : public DelegateKind<R, Args...> {
  public:
    using Function = R (*)(Args..., Payload...);

    explicit StaticDelegate(Function function, Payload &&...payload);

    R Execute(Args &&...args) override;

  private:
    template <std::size_t... Is>
    R Execute_Internal(Args &&...args, std::index_sequence<Is...>);

    Function function_;
    std::tuple<Payload...> payload_;
};

}  // namespace computer_graphics::delegate

#include "static_delegate.inl"

#endif  // STATIC_DELEGATE_HPP_INCLUDED
