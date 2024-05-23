#include "computer_graphics/delegate/delegate_handle.hpp"

namespace computer_graphics::delegate {

DelegateHandle::DelegateHandle() noexcept : id_{kInvalidID} {}

constexpr DelegateHandle::ID DelegateHandle::kInvalidID = ~0;

DelegateHandle::ID DelegateHandle::GenerateNewID() noexcept {
    static constinit ID next_id = 0;

    const ID id = next_id++;
    if (next_id == kInvalidID) {
        next_id = 0;
    }
    return id;
}

}  // namespace computer_graphics::delegate
