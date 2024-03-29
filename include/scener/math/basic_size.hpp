// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_SIZE_HPP
#define SCENER_MATH_BASIC_SIZE_HPP

#include <type_traits>

namespace scener::math 
{
    // -----------------------------------------------------------------------------------------------------------------
    // TEMPLATES

    template <typename T, typename = typename std::enable_if_t<std::is_arithmetic_v<T>>>
    class basic_size
    {
    public:
        constexpr basic_size() noexcept
            : basic_size { 0, 0 }
        {
        }

        constexpr basic_size(T w, T h) noexcept
            : width { w }, height { h }
        {
        }

    public:
        constexpr bool empty() const noexcept
        {
            return (width == T(0) && height == T(0));
        }

    public:
        template <typename K>
        constexpr operator basic_size<K>() const noexcept
        {
            return { K(width), K(height) };
        }

    public:
        T width;
        T height;
    };

    // -----------------------------------------------------------------------------------------------------------------
    // TYPEDEF'S & ALIASES

    using size = basic_size<std::int32_t>;

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS

    /// Equality operator for comparing basic_size instances.
    template <typename T>
    constexpr bool operator==(const basic_size<T>& lhs, const basic_size<T>& rhs) noexcept
    {
        return (lhs.width == rhs.width && lhs.height == rhs.height);
    }

    /// Inequality operator for comparing basic_size instances.
    template <typename T>
    constexpr bool operator!=(const basic_size<T>& lhs, const basic_size<T>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    /// Subtracts the width and height of one basic_size structure to the width and height of another basic_size structure.
    template <typename T>
    constexpr basic_size<T>& operator-=(basic_size<T>& lhs, const basic_size<T>& rhs) noexcept
    {
        lhs.width -= rhs.height;
        lhs.width -= rhs.height;

        return lhs;
    }

    /// Subtracts the width and height of one basic_size structure to the width and height of another basic_size structure.
    template <typename T>
    constexpr basic_size<T> operator-(const basic_size<T>& lhs, const basic_size<T>& rhs) noexcept
    {
        auto result = lhs;

        result -= rhs;

        return result;
    }

    /// Adds the width and height of one basic_size structure to the width and height of another basic_size structure.
    template <typename T>
    constexpr basic_size<T>& operator+=(basic_size<T>& lhs, const basic_size<T>& rhs) noexcept
    {
        lhs.width  += rhs.width;
        lhs.height += rhs.height;

        return lhs;
    }

    /// Adds the width and height of one basic_size structure to the width and height of another basic_size structure.
    template <typename T>
    constexpr basic_size<T> operator+(const basic_size<T>& lhs, const basic_size<T>& rhs) noexcept
    {
        auto result = lhs;

        result += rhs;

        return result;
    }
}

#endif  // SCENER_MATH_BASIC_SIZE_HPP
