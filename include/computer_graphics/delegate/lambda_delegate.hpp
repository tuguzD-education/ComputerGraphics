#pragma once

#ifndef LAMBDA_DELEGATE_HPP_INCLUDED
#define LAMBDA_DELEGATE_HPP_INCLUDED

#include <tuple>

#include "delegate_kind.hpp"

namespace computer_graphics::delegate {

template <typename Lambda, typename FunctionType, typename... Payload>
class LambdaDelegate;

template <typename Lambda, typename R, typename... Args, typename... Payload>
class LambdaDelegate<Lambda, R(Args...), Payload...> : public DelegateKind<R, Args...> {
  public:
    using Function = Lambda;

    explicit LambdaDelegate(Lambda &&lambda, Payload &&...payload);

    R Execute(Args &&...args) override;

  private:
    template <std::size_t... Is>
    R Execute_Internal(Args &&...args, std::index_sequence<Is...>);

    Lambda lambda_;
    std::tuple<Payload...> payload_;
};

}  // namespace computer_graphics::delegate

#include "lambda_delegate.inl"

#endif  // LAMBDA_DELEGATE_HPP_INCLUDED
