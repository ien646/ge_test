#pragma once

#include <type_traits>

// isRangeComparable: Check if a given type has both less than (<)
// and greater or equal than (>=) operators for use on ranges 
// defined as '[first-inclusive, last-exclusive)'

template<typename, typename = void>
struct isRangeComparable : std::false_type { };

template<typename T>
struct isRangeComparable<
    T, 
    std::void_t<
        decltype(std::declval<T>().operator>=()),
        decltype(std::declval<T>().operator<())
    >
> : std::true_type { };