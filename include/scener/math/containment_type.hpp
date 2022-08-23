// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_CONTAINMENTTYPE_HPP
#define SCENER_MATH_CONTAINMENTTYPE_HPP

#include <cstdint>

namespace scener::math
{
    /// Indicates the extent to which bounding volumes intersect or contain one another.
    enum class containment_type : std::uint32_t
    {
        contains   = 0 ///< Indicates that one bounding volume completely contains the other.
      , disjoint   = 1 ///< Indicates there is no overlap between the bounding volumes.
      , intersects = 2 ///< Indicates that the bounding volumes partially overlap.
  };
}

#endif // SCENER_MATH_CONTAINMENTTYPE_HPP
