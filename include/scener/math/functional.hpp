// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_FUNCTIONAL_HPP
#define SCENER_MATH_FUNCTIONAL_HPP

#include <cmath>

#include "scener/math/basic_math.hpp"

namespace scener::math::functional
{
    template <class T = void> struct sqrt  { };
    template <class T = void> struct abs   { };
    template <class T = void> struct min   { };
    template <class T = void> struct max   { };
    template <class T = void> struct clamp { };

    template<>
    struct sqrt<void>
    {
        template <class T>
        inline constexpr auto operator() (T&& value) const
            -> decltype(std::sqrt(std::forward<T>(value)))
        {
            return std::sqrt(std::forward<T>(value));
        }
    };

    template<>
    struct abs<void>
    {
        template <class T>
        inline constexpr auto operator() (T&& value) const
            -> decltype(std::abs(std::forward<T>(value)))
        {
            return std::abs(std::forward<T>(value));
        }
    };

    template<>
    struct min<void>
    {
        template <class T, class U>
        inline constexpr auto operator() (T&& lhs, U&& rhs) const
            -> decltype(std::min(std::forward<T>(lhs), std::forward<U>(rhs)))
        {
            return std::min(std::forward<T>(lhs), std::forward<U>(rhs));
        }
    };

    template<>
    struct max<void>
    {
        template <class T, class U>
        inline constexpr auto operator() (T&& lhs, U&& rhs) const
            -> decltype(std::max(std::forward<T>(lhs), std::forward<U>(rhs)))
        {
            return std::max(std::forward<T>(lhs), std::forward<U>(rhs));
        }
    };

    template<>
    struct clamp<void>
    {
        template <class T, class U, class V>
        inline constexpr auto operator() (T&& value, U&& min, V&& max) const
            -> decltype(math::clamp(std::forward<T>(value), std::forward<U>(min), std::forward<V>(max)))
        {
            return math::clamp(std::forward<T>(value), std::forward<U>(min), std::forward<V>(max));
        }
    };
}

#endif // SCENER_MATH_FUNCTIONAL_HPP
