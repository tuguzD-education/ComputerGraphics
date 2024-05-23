#pragma once

#ifndef CONCEPTS_HPP_INCLUDED
#define CONCEPTS_HPP_INCLUDED

#include <ranges>

namespace computer_graphics {

template <typename Range, typename T>
concept TypedRange = std::ranges::range<Range> && std::same_as<std::ranges::range_value_t<Range>, T>;

template <typename Range, typename T>
concept RefWrapperRange = TypedRange<Range, std::reference_wrapper<T>>;

}  // namespace computer_graphics

#endif  // CONCEPTS_HPP_INCLUDED
