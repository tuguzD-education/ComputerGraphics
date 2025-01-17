#pragma once

#ifndef DETAIL_CHECK_RESULT_HPP_INCLUDED
#define DETAIL_CHECK_RESULT_HPP_INCLUDED

#include <windows.h>

#include <string>

namespace computer_graphics::detail {

void CheckResult(HRESULT result, const char *message = nullptr);
void CheckResult(HRESULT result, const std::string &message);

template <typename F>
concept StringFactory = requires(F &&factory) {
    { factory() } -> std::convertible_to<std::string>;
};

template <StringFactory F>
void CheckResult(HRESULT result, F &&factory);

}  // namespace computer_graphics::detail

#include "check_result.inl"

#endif  // DETAIL_CHECK_RESULT_HPP_INCLUDED
