#pragma once

#include <type_traits>

template <typename T, typename = std::void_t<>>
struct is_comparable : std::false_type {};

template <typename T>
struct is_comparable<T,
    std::void_t<
        decltype(std::declval<T>() < std::declval<T>()),
        decltype(std::declval<T>() > std::declval<T>()),
        decltype(std::declval<T>() <= std::declval<T>()),
        decltype(std::declval<T>() >= std::declval<T>())
    >
> : std::true_type {};
