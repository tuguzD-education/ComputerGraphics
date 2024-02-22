#pragma once

#ifndef DETAIL_CHECK_RESULT_INL_INCLUDED
#define DETAIL_CHECK_RESULT_INL_INCLUDED

#include <stdexcept>

namespace computer_graphics::detail {

template<StringFactory F>
void CheckResult(const HRESULT result, F factory) {
  if (FAILED(result)) {
    std::string message = factory();
    throw std::runtime_error{message};
  }
}

}

#endif //DETAIL_CHECK_RESULT_INL_INCLUDED
