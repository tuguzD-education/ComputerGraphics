#pragma once

#ifndef DELEGATE_HANDLE_INL_INCLUDED
#define DELEGATE_HANDLE_INL_INCLUDED

namespace computer_graphics::delegate {

constexpr DelegateHandle::DelegateHandle(std::nullptr_t) noexcept : id_{kInvalidID} {}

constexpr DelegateHandle::~DelegateHandle() noexcept = default;

constexpr DelegateHandle::DelegateHandle(const DelegateHandle &other) noexcept = default;

constexpr DelegateHandle &DelegateHandle::operator=(const DelegateHandle &other) noexcept = default;

constexpr DelegateHandle::DelegateHandle(DelegateHandle &&other) noexcept : id_{other.id_} {
    other.Reset();
}

constexpr DelegateHandle &DelegateHandle::operator=(DelegateHandle &&other) noexcept {
    id_ = other.id_;
    other.Reset();
    return *this;
}

constexpr auto DelegateHandle::operator<=>(const DelegateHandle &other)
const noexcept = default;

constexpr DelegateHandle::operator bool() const noexcept {
    return IsValid();
}

constexpr bool DelegateHandle::IsValid() const noexcept {
    return id_ != kInvalidID;
}

constexpr void DelegateHandle::Reset() noexcept {
    id_ = kInvalidID;
}

}  // namespace computer_graphics::delegate

#endif  // DELEGATE_HANDLE_INL_INCLUDED
