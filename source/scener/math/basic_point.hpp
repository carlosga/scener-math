// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_POINT_HPP
#define SCENER_MATH_BASIC_POINT_HPP

#include <type_traits>

namespace scener::math 
{
    // -----------------------------------------------------------------------------------------------------------------
    // TEMPLATES

    template <typename T, typename = typename std::enable_if_t<std::is_arithmetic_v<T>>>
    struct basic_point
    {
    public:
        constexpr basic_point() noexcept
            : basic_point { 0, 0 }
        {
        }

        constexpr explicit basic_point(T value) noexcept
            : basic_point { value, value }
        {
        }

        constexpr basic_point(T xx, T yy) noexcept
            : x { xx }, y { yy }
        {
        }

    public:
        constexpr bool empty() const noexcept
        {
            return (x == 0 && y == 0);
        }

    public:
        T x;
        T y;
    };

    // ---------------------------------------------------------------------------------------------------------------------
    // TYPEDEF'S & ALIASES

    using point = basic_point<std::int32_t>;

    // ---------------------------------------------------------------------------------------------------------------------
    // OPERATORS

    /// Equality operator for comparing basic_point instances.
    template <typename T>
    constexpr bool operator==(const basic_point<T>& lhs, const basic_point<T>& rhs) noexcept
    {
        return (lhs.x == rhs.x && lhs.y == rhs.y);
    }

    /// Inequality operator for comparing basic_point instances.
    template <typename T>
    constexpr bool operator!=(const basic_point<T>& lhs, const basic_point<T>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <typename T>
    constexpr basic_point<T>& operator-=(basic_point<T>& lhs, const basic_point<T>& rhs) noexcept
    {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;

        return lhs;
    }

    template <typename T>
    constexpr basic_point<T> operator-(const basic_point<T>& lhs, const basic_point<T>& rhs) noexcept
    {
        auto result = lhs;

        result -= rhs;

        return result;
    }

    template <typename T>
    constexpr basic_point<T>& operator+=(basic_point<T>& lhs, const basic_point<T>& rhs) noexcept
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;

        return lhs;
    }

    template <typename T>
    constexpr basic_point<T> operator+(const basic_point<T>& lhs, const basic_point<T>& rhs) noexcept
    {
        auto result = lhs;

        result += rhs;

        return result;
    }

    template <typename T>
    constexpr basic_point<T> operator-(const basic_point<T>& point) noexcept
    {
        return { -point.x, -point.y };
    }
}

#endif  // SCENER_MATH_BASIC_POINT_HPP
