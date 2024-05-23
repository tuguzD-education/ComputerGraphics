#include "computer_graphics/delegate/delegate_kind.hpp"

namespace computer_graphics::delegate {

DelegateKindBase::DelegateKindBase() = default;

DelegateKindBase::~DelegateKindBase() noexcept = default;

const void *DelegateKindBase::Owner() const {
    return nullptr;
}

}  // namespace computer_graphics::delegate
