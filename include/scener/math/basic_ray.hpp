// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_RAY_HPP
#define SCENER_MATH_BASIC_RAY_HPP

#include "scener/math/basic_vector.hpp"

namespace scener::math 
{
    // -----------------------------------------------------------------------------------------------------------------
    // TEMPLATES

    /// Defines a ray.
    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    struct basic_ray
    {
    public:
        /// Initializes a new instance of the basic_ray structure with the given position an direction.
        /// \param rposition the ray starting.
        /// \param rdirection unit vector describing he ray direction.
        constexpr basic_ray(const basic_vector3<T>& rposition, const basic_vector3<T>& rdirection) noexcept
            : direction { rdirection }
            , position  { rposition }
        {
        }

    public:
        /// Unit vector specifying the direction the basic_ray is pointing.
        basic_vector3<T> direction;

        /// Specifies the starting point of the basic_ray.
        basic_vector3<T> position;
    };

    // -----------------------------------------------------------------------------------------------------------------
    // TYPEDEF'S & ALIASES

    using ray = basic_ray<float>;

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS

    template <typename T>
    constexpr bool operator ==(const basic_ray<T>& lhs, const basic_ray<T>& rhs) noexcept
    {
        return (lhs.direction == rhs.direction && lhs.position == rhs.position);
    }

    template <typename T>
    constexpr bool operator !=(const basic_ray<T>& lhs, const basic_ray<T>& rhs) noexcept
    {
        return !(lhs == rhs);
    }
}

#endif // SCENER_MATH_BASIC_RAY_HPP
