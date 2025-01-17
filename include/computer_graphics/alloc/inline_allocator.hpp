#pragma once

#ifndef INLINE_ALLOCATOR_HPP_INCLUDED
#define INLINE_ALLOCATOR_HPP_INCLUDED

#include <cstddef>

namespace computer_graphics::alloc {

template <std::size_t MaxStackSize>
class InlineAllocator {
  public:
    constexpr InlineAllocator() noexcept;
    ~InlineAllocator() noexcept;

    InlineAllocator(const InlineAllocator &other);
    InlineAllocator &operator=(const InlineAllocator &other);

    InlineAllocator(InlineAllocator &&other) noexcept;
    InlineAllocator &operator=(InlineAllocator &&other) noexcept;

    [[nodiscard]] void *Allocate(std::size_t size);

    void Free();

    [[nodiscard]] constexpr void *Allocation() const;

    [[nodiscard]] constexpr std::size_t Size() const;

    [[nodiscard]] constexpr bool HasAllocation() const;

    [[nodiscard]] constexpr bool HasHeapAllocation() const;

  private:
    // If the allocation is smaller than the threshold, `buffer_` is used
    // Otherwise `alloc_` is used together with a separate dynamic allocation
    union {
        std::byte buffer_[MaxStackSize];
        void *alloc_;
    };
    std::size_t size_;
};

}  // namespace computer_graphics::alloc

#include "inline_allocator.inl"

#endif  // INLINE_ALLOCATOR_HPP_INCLUDED
