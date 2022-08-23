// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_PLANE_HPP
#define SCENER_MATH_BASIC_PLANE_HPP

#include <type_traits>

#include "scener/math/basic_vector.hpp"

namespace scener::math 
{
    // -----------------------------------------------------------------------------------------------------------------
    // TEMPLATES

    /// Defines a plane.
    template <typename T, typename = typename std::enable_if_t<std::is_arithmetic_v<T>>>
    struct basic_plane
    {
    public:
        /// Initializes a new instance of the Plane structure.
        constexpr basic_plane() noexcept
            : normal { }
            , d      { T(0) }
        {
        }

        /// Initializes a new instance of the Plane structure.
        constexpr basic_plane(T a, T b, T c, T distance) noexcept
            : normal { a, b, c }
            , d      { distance }
        {
        }

        /// Initializes a new instance of the Plane structure.
        constexpr basic_plane(const basic_vector3<T>& plane_normal, T distance) noexcept
            : normal { plane_normal }
            , d      { distance }
        {
        }

        /// Initializes a new instance of the Plane structure.
        constexpr basic_plane(const basic_vector4<T>& value) noexcept
            : normal { value.x, value.y, value.z }
            , d      { value.w }
        {
        }

    public:
        /// Gets or Sets The normal vector of the Plane.
        basic_vector3<T> normal;

        /// Gets the distance of the Plane along its normal from the origin.
        T d;
    };

    // -----------------------------------------------------------------------------------------------------------------
    // TYPEDEF'S & ALIASES

    using plane_t = basic_plane<float>;

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS

    template <typename T>
    constexpr bool operator==(const basic_plane<T>& lhs, const basic_plane<T>& rhs) noexcept
    {
        return (lhs.normal == rhs.normal && equal(lhs.d, rhs.d));
    }

    template <typename T>
    constexpr bool operator!=(const basic_plane<T>& lhs, const basic_plane<T>& rhs) noexcept
    {
        return !(lhs == rhs);
    }
}

#endif // SCENER_MATH_BASIC_PLANE_HPP
