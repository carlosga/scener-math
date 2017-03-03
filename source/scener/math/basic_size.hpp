// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_SIZE_HPP
#define SCENER_MATH_BASIC_SIZE_HPP

#include <type_traits>

namespace scener::math 
{
    // -----------------------------------------------------------------------------------------------------------------
    // TEMPLATES

    template <typename T, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
    class basic_size
    {
    public:
        constexpr basic_size() noexcept
            : basic_size { 0, 0 }
        {
        }

        constexpr basic_size(T width, T height) noexcept
            : _width { width }, _height { height }
        {
        }

    public:
        constexpr bool empty() const noexcept
        {
            return (_width == T(0) && _height == T(0));
        }

        constexpr T width() const noexcept
        {
            return _width;
        }

        constexpr T height() const noexcept
        {
            return _height;
        }

    public:
        template <typename K>
        constexpr operator basic_size<K>() const noexcept
        {
            return { K(_width), K(_height) };
        }

    private:
        T _width;
        T _height;
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
        return (lhs._width == rhs._width && lhs._height == rhs._height);
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
        lhs._width -= rhs._height;
        lhs._width -= rhs._height;

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
        lhs._width  += rhs._width;
        lhs._height += rhs._height;

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
