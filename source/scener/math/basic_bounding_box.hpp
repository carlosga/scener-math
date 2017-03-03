// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_BOUNDING_BOX_HPP
#define SCENER_MATH_BASIC_BOUNDING_BOX_HPP

#include "scener/math/basic_vector.hpp"
#include "scener/math/containment_type.hpp"
#include "scener/math/plane_intersection_type.hpp"

namespace scener::math 
{
    // -----------------------------------------------------------------------------------------------------------------
    // TEMPLATES

    /// Defines an axis-aligned box-shaped 3D volume.
    template <typename T, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
    struct basic_bounding_box
    {
    public:
        /// Specifies the total number of corners (8) in the basic_bounding_box.
        constexpr static std::uint32_t corner_count = 8;

    public:
        /// Initializes a new instance of the basic_bounding_box structure.
        /// \param min_point the minimum point the basic_bounding_box includes.
        /// \param max_point the maximum point the basic_bounding_box includes.
        constexpr basic_bounding_box(const basic_vector3<T>& min_point, const basic_vector3<T>& max_point) noexcept
            : min { min_point }, max { max_point }
        {
        }

    public:
        basic_vector3<T> min;
        basic_vector3<T> max;
    };

    // -----------------------------------------------------------------------------------------------------------------
    // TYPEDEF'S & ALIASES

    using bounding_box = basic_bounding_box<float>;

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS

    template <typename T>
    constexpr bool operator==(const basic_bounding_box<T>& lhs, const basic_bounding_box<T>& rhs) noexcept
    {
        return (lhs.min == rhs.min && lhs.max == rhs.max);
    }

    template <typename T>
    constexpr bool operator!=(const basic_bounding_box<T>& lhs, const basic_bounding_box<T>& rhs) noexcept
    {
        return !(lhs == rhs);
    }
}

#endif // SCENER_MATH_basic_bounding_box_HPP
