#pragma once

#ifndef DETAIL_CHECK_RESULT_INL_INCLUDED
#define DETAIL_CHECK_RESULT_INL_INCLUDED

#include <comdef.h>

#include <stdexcept>

#include "string_api_set.hpp"

namespace computer_graphics::detail {

template <StringFactory F>
void CheckResult(const HRESULT result, F &&factory) {
    if (FAILED(result)) {
        std::string message = factory();

        _com_error error{result};
        if (!message.empty()) {
            message.append("\ncause: ");
        }
        message.append(TCharToMultiByte(CP_UTF8, 0, error.ErrorMessage()));

        throw std::runtime_error{message};
    }
}

}  // namespace computer_graphics::detail

#endif  // DETAIL_CHECK_RESULT_INL_INCLUDED
