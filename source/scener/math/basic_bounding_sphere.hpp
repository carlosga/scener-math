// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_BOUNDING_SPHERE_HPP
#define SCENER_MATH_BASIC_BOUNDING_SPHERE_HPP

#include "scener/math/basic_vector.hpp"

namespace scener::math 
{
    // -----------------------------------------------------------------------------------------------------------------
    // TEMPLATES

    /// Defines a sphere.
    template <typename T, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
    struct basic_bounding_sphere
    {
    public:
        /// Initializes a new instance of the basic_bounding_sphere class with the given center an radius.
        /// \param scenter center point of the sphere.
        /// \param sradius radius of the sphere.
        constexpr basic_bounding_sphere(const basic_vector3<T>& scenter, float sradius) noexcept
            : center { scenter }
            , radius { sradius }
        {
        }

    public:
        basic_vector3<T> center;
        float            radius;
    };

    // -----------------------------------------------------------------------------------------------------------------
    // TYPEDEF'S & ALIASES

    using bounding_sphere = basic_bounding_sphere<float>;

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS

    /// Equality operator for comparing basic_bounding_sphere instances.
    template <typename T>
    constexpr bool operator==(const basic_bounding_sphere<T>& lhs, const basic_bounding_sphere<T>& rhs) noexcept
    {
        return (lhs.center == rhs.center && math::equal(lhs.radius, rhs._radius));
    }

    /// Inequality operator for comparing basic_bounding_sphere instances.
    template <typename T>
    constexpr bool operator!=(const basic_bounding_sphere<T>& lhs, const basic_bounding_sphere<T>& rhs) noexcept
    {
        return !(lhs == rhs);
    }
}

#endif // SCENER_MATH_BASIC_BOUNDING_SPHERE_HPP
