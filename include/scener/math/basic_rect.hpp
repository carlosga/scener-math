// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_RECT_HPP
#define SCENER_MATH_BASIC_RECT_HPP

#include <cstdint>
#include <type_traits>

#include "scener/math/basic_point.hpp"
#include "scener/math/basic_size.hpp"

namespace scener::math 
{
    // -----------------------------------------------------------------------------------------------------------------
    // TEMPLATES

    template <typename T, typename = typename std::enable_if_t<std::is_arithmetic_v<T>>>
    class basic_rect final
    {
    public:
        constexpr basic_rect() noexcept
        {
        }

        constexpr basic_rect(T x, T y, T width, T height) noexcept
            : _location { x, y }, _size { width, height }
        {
        }

        constexpr basic_rect(const basic_point<T>& location, const basic_size<T> size) noexcept
            : _location { location }, _size { size }
        {
        }

    public:
        // Gets the y-coordinate that is the sum of the Y and Height property values of this Rectangle structure.
        constexpr T bottom() const noexcept
        {
            return (_location.y + _size.height);
        }

        // Gets or sets the height of this Rectangle structure.
        constexpr T height() const noexcept
        {
            return _size.height;
        }

        // Tests whether all numeric properties of this Rectangle have values of zero.
        constexpr bool empty() const noexcept
        {
            return _location.empty() && _size.empty();
        }

        // Gets the x-coordinate of the lhs edge of this Rectangle structure.
        constexpr T lhs() const noexcept
        {
            return _location.x;
        }

        // Gets or sets the coordinates of the upper-lhs corner of this Rectangle structure.
        constexpr basic_point<T> location() const noexcept
        {
            return _location;
        }

        // Gets the x-coordinate that is the sum of X and Width property values of this Rectangle structure.
        constexpr T rhs() const noexcept
        {
            return (_location.x + _size.width);
        }

        // Gets or sets the size of this Rectangle.
        constexpr basic_size<T> size() const noexcept
        {
            return _size;
        }

        // The y-coordinate of the top edge of this Rectangle structure.
        constexpr T top() const noexcept
        {
            return _location.y;
        }

        // Gets or sets the width of this Rectangle structure.
        constexpr T width() const noexcept
        {
            return _size.width;
        }

        // Gets or sets the x-coordinate of the upper-lhs corner of this Rectangle structure.
        constexpr T x() const noexcept
        {
            return _location.x;
        }

        // Gets or sets the y-coordinate of the upper-lhs corner of this Rectangle structure.
        constexpr T y() const noexcept
        {
            return _location.y;
        }

    public:
        // bool contains(T x, T y);
        // bool contains(basic_point<T> pt);
        // bool contains(basic_rect<T> rect);

        // static basic_rect<T> inflate(basic_rect<T> rect, int x, int y);
        // void inflate(basic_size<T> size);
        // void inflate(T width, T height);

        // static basic_rect<T> intersect(basic_rect<T> a, basic_rect<T> b);
        // void intersect(basic_rect<T> rect);

        // Determines if this rectangle intersects with rect.
        // bool intersects_with(basic_rect<T> rect);

        // Adjusts the location of this rectangle by the specified amount.
        // void offset(basic_point<T> pos);
        // void offset(T x, T y);

        // Gets a Rectangle structure that contains the union of two Rectangle structures.
        // When one of the two rectangles is empty, meaning all of its values are zero,
        // the Union method returns a rectangle with a starting point of (0, 0),
        // and the height and width of the non-empty rectangle.
        // For example, if you have two rectangles: A = (0, 0; 0, 0) and B = (1, 1; 2, 2), then the union of A and B is (0, 0; 2, 2).
        // static basic_rect<T> union(basic_rect<T> a, basic_rect<T> b);

    private:
        basic_point<T> _location;
        basic_size<T>  _size;
    };

    // -----------------------------------------------------------------------------------------------------------------
    // TYPEDEF'S & ALIASES

    using rect = basic_rect<std::int32_t>;

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS

    /// Equality operator for comparing basic_rect instances.
    template <typename T>
    constexpr bool operator==(const basic_rect<T>& lhs, const basic_rect<T>& rhs) noexcept
    {
        return (lhs._location == rhs._location && lhs._size == rhs._size);
    }

    /// Inequality operator for comparing basic_rect instances.
    template <typename T>
    constexpr bool operator!=(const basic_rect<T>& lhs, const basic_rect<T>& rhs) noexcept
    {
        return !(lhs == rhs);
    }
}

#endif // SCENER_MATH_BASIC_RECT_HPP
