// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_COLOR_HPP
#define SCENER_MATH_BASIC_COLOR_HPP

#include "scener/math/basic_vector.hpp"

namespace scener::math
{
    // -----------------------------------------------------------------------------------------------------------------
    // TEMPLATES

    /// Describes a color in terms of red, green, blue and alpha components.
    template <typename T, typename = typename std::enable_if_t<std::is_arithmetic_v<T>>>
    struct basic_color
    {
    public:
        constexpr static const basic_color black() noexcept
        {
            return { 0x00, 0x00, 0x00, 0xFF };
        }

        constexpr static const basic_color white() noexcept
        {
            return { 0xFF, 0xFF, 0xFF, 0xFF };
        }

    public:
        /// Initializes a new instance of the basic_color structure.
        constexpr basic_color() noexcept
            : basic_color { T(0), T(0), T(0), T(0) }
        {
        }

        /// Initializes a new instance of the Color class.
        /// \param vector A three-component color.
        constexpr basic_color(const basic_vector3<T>& vector) noexcept
            : basic_color { vector.x, vector.y, vector.z, T(1) }
        {
        }

        /// Initializes a new instance of the Color class.
        /// \param vector A four-component color.
        constexpr basic_color(const basic_vector4<T>& vector) noexcept
            : basic_color { vector.x, vector.y, vector.z, vector.w  }
        {
        }

        /// Initializes a new instance of the Color class with the given red, green and blue components.
        /// \param rr The red component value of the color.
        /// \param gg The green component value of the color.
        /// \param bb The blue component value of the color.
        constexpr basic_color(T rr, T gg, T bb) noexcept
            : basic_color { rr, gg, bb, T(1) }
        {
        }

        /// Initializes a new instance of the Color class with the given red, green, blue and alpha components.
        /// \param rr The red component value of the color.
        /// \param gg The green component value of the color.
        /// \param bb The blue component value of the color.
        /// \param aa The alpha component value of the color.
        constexpr basic_color(T rr, T gg, T bb, T aa) noexcept
            : r { rr }, g { gg }, b { bb }, a { aa }
        {
        }

    public:
        constexpr T& operator[](const std::size_t& index) noexcept
        {
            return components[index];
        }

        constexpr const T& operator[](const std::size_t& index) const noexcept
        {
            return components[index];
        }

    public:
        union
        {
            std::array<T, 4> components;
            struct
            {
                T r;
                T g;
                T b;
                T a;
            };
        };
    };

    // -----------------------------------------------------------------------------------------------------------------
    // TYPEDEF'S & ALIASES

    using color = basic_color<float>;

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS

    template <typename T>
    constexpr bool operator==(const basic_color<T>& lhs, const basic_color<T>& rhs) noexcept
    {
        return (math::equal(lhs.r, rhs.r)
             && math::equal(lhs.g, rhs.g)
             && math::equal(lhs.b, rhs.b)
             && math::equal(lhs.a, rhs.a));
    }

    template <typename T>
    constexpr bool operator!=(const basic_color<T>& lhs, const basic_color<T>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <typename T>
    constexpr basic_color<T>& operator*=(basic_color<T>& lhs, const basic_color<T>& rhs) noexcept
    {
        lhs.r *= rhs.r;
        lhs.g *= rhs.g;
        lhs.b *= rhs.b;
        lhs.a *= rhs.a;

        return lhs;
    }

    template <typename T>
    constexpr basic_color<T>& operator-=(basic_color<T>& lhs, const basic_color<T>& rhs) noexcept
    {
        lhs.r -= rhs.r;
        lhs.g -= rhs.g;
        lhs.b -= rhs.b;
        lhs.a -= rhs.a;

        return lhs;
    }

    template <typename T>
    constexpr basic_color<T>& operator+=(basic_color<T>& lhs, const basic_color<T>& rhs) noexcept
    {
        lhs.r += rhs.r;
        lhs.g += rhs.g;
        lhs.b += rhs.b;
        lhs.a += rhs.a;

        return lhs;
    }

    template <typename T>
    constexpr basic_color<T> operator*(const basic_color<T>& lhs, const basic_color<T>& rhs) noexcept
    {
        auto result = lhs;

        result *= rhs;

        return result;
    }

    template <typename T>
    constexpr basic_color<T> operator-(const basic_color<T>& lhs, const basic_color<T>& rhs) noexcept
    {
        auto result = lhs;

        result -= rhs;

        return result;
    }

    template <typename T>
    constexpr basic_color<T> operator+(const basic_color<T>& lhs, const basic_color<T>& rhs) noexcept
    {
        auto result = lhs;

        result += rhs;

        return result;
    }

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS (WITH SCALARS)

    template <typename T>
    constexpr basic_color<T>& operator*=(basic_color<T>& lhs, const T& rhs) noexcept
    {
        lhs.r *= rhs;
        lhs.g *= rhs;
        lhs.b *= rhs;
        lhs.a *= rhs;

        return lhs;
    }

    template <typename T>
    constexpr basic_color<T> operator*(const basic_color<T>& lhs, const T& value) noexcept
    {
        auto result = lhs;

        result *= value;

        return result;
    }
}

#endif  // SCENER_MATH_BASIC_COLOR_HPP

