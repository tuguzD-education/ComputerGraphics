#pragma once

#ifndef MEMBER_FUNCTION_HPP_INCLUDED
#define MEMBER_FUNCTION_HPP_INCLUDED

namespace computer_graphics::delegate::detail {

template <bool IsConst, typename Object, typename RetVal, typename... Args>
struct MemberFunction;

template <typename Object, typename RetVal, typename... Args>
struct MemberFunction<true, Object, RetVal, Args...> {
    using Type = RetVal (Object::*)(Args...) const;
};

template <typename Object, typename RetVal, typename... Args>
struct MemberFunction<false, Object, RetVal, Args...> {
    using Type = RetVal (Object::*)(Args...);
};

}  // namespace computer_graphics::delegate::detail

#endif  // MEMBER_FUNCTION_HPP_INCLUDED
