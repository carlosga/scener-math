// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_PLANEINTERSECTIONTYPE_HPP
#define SCENER_MATH_PLANEINTERSECTIONTYPE_HPP

#include <cstdint>

namespace scener::math
{
    /// Describes the intersection between a plane and a bounding volume.
    enum class plane_intersection_type : std::uint32_t
    {
        back         = 0  ///< There is no intersection, and the bounding volume is in the negative half-space of the Plane.
      , front        = 1  ///< There is no intersection, and the bounding volume is in the positive half-space of the Plane.
      , intersecting = 2  ///< The Plane is intersected.
    };
}

#endif // SCENER_MATH_PLANEINTERSECTIONTYPE_HPP
