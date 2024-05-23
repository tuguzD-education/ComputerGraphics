#pragma once

#ifndef DELEGATE_HANDLE_HPP_INCLUDED
#define DELEGATE_HANDLE_HPP_INCLUDED

#include <compare>

namespace computer_graphics::delegate {

class DelegateHandle {
  public:
    using ID = std::size_t;

    explicit DelegateHandle() noexcept;
    constexpr explicit DelegateHandle(std::nullptr_t) noexcept;

    constexpr ~DelegateHandle() noexcept;

    constexpr DelegateHandle(const DelegateHandle &other) noexcept;
    constexpr DelegateHandle &operator=(const DelegateHandle &other) noexcept;

    constexpr DelegateHandle(DelegateHandle &&other) noexcept;
    constexpr DelegateHandle &operator=(DelegateHandle &&other) noexcept;

    constexpr auto operator<=>(const DelegateHandle &other) const noexcept;
    explicit constexpr operator bool() const noexcept;

    [[nodiscard]] constexpr bool IsValid() const noexcept;

    constexpr void Reset() noexcept;

  private:
    static const ID kInvalidID;
    static ID GenerateNewID() noexcept;

    ID id_;
};

}  // namespace computer_graphics::delegate

#include "delegate_handle.inl"

#endif  // DELEGATE_HANDLE_HPP_INCLUDED
