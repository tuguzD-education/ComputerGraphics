#include "computer_graphics/detail/check_result.hpp"

namespace computer_graphics::detail {

void CheckResult(const HRESULT result, const char *message) {
    CheckResult(result, [=] { return message; });
}

void CheckResult(const HRESULT result, const std::string &message) {
    CheckResult(result, [&] { return message; });
}

}  // namespace computer_graphics::detail
