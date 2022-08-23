// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_BOUNDING_BOX_HPP
#define SCENER_MATH_BASIC_BOUNDING_BOX_HPP

#include "scener/math/basic_bounding_box.hpp"

#include "scener/math/basic_ray.hpp"

namespace scener::math
{
    // -----------------------------------------------------------------------------------------------------------------
    // OPERATIONS

    //Public Method Static    CreateFromPoints    Creates the smallest basic_bounding_box that will contain a group of points.
    //Public Method Static    CreateFromSphere    Overloaded. Creates the smallest basic_bounding_box that will contain the specified BoundingSphere.
    //Public Method Static    CreateMerged    Overloaded. Creates the smallest basic_bounding_box that contains the two specified basic_bounding_box instances.

    //containment_type contains(const basic_bounding_box& box) const noexcept
    //{
    //}

    //containment_type contains(const BoundingFrustrum& frustrum) const noexcept
    //{
    //}

    //containment_type contains(const BoundingSphere& sphere) const noexcept
    //{
    //}

    //containment_type contains(const vector3& point) const noexcept
    //{
    //}

    //std::vector<vector3> get_corners() const noexcept
    //{
    //}

    //bool intersects(const basic_bounding_box& box) const noexcept
    //{
    //}

    //bool intersects(const BoundingFrustrum& frustrum) const noexcept
    //{
    //}

    //bool intersects(const BoundingSphere& sphere) const noexcept
    //{
    //}

    //plane_intersection_type intersects(const plane_t& plane) const noexcept
    //{
    //}
}

#endif  // SCENER_MATH_BASIC_BOUNDING_BOX_HPP
