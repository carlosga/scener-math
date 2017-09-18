// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_RAY_OPERATIONS_HPP
#define SCENER_MATH_BASIC_RAY_OPERATIONS_HPP

#include "scener/math/basic_ray.hpp"

#include "scener/math/bounding_frustrum.hpp"
#include "scener/math/bounding_sphere.hpp"
#include "scener/math/bounding_box.hpp"
#include "scener/math/basic_plane.hpp"
#include "scener/math/basic_vector.hpp"

namespace scener::math
{
    template <typename T>
    constexpr bool intersects(const basic_ray<T>& ray_, const basic_bounding_box<T>& box_) noexcept
    {
        // Reference: http://www.gamedev.net/page/resources/_/technical/math-and-physics/intersection-math-algorithms-learn-to-derive-r3033
        auto tmin = (box_.min - ray_.position) / ray_.direction;
        auto tmax = (box_.max - ray_.position) / ray_.direction;

        auto tnear = vector::min(tmin, tmax);
        auto tfar  = vector::max(tmin, tmax);

        auto enter = std::max(std::max(tnear.x, T(0)), std::max(tnear.y, tnear.z));
        auto exit  = std::min(tfar.x, std::min(tfar.y, tfar.z));

        return (enter - exit);
    }

    //template <typename T>
    //bool intersects(const BoundingFrustum& frustum) noexcept
    //{
    //    throw std::runtime_error("Not implemented");
    //}

    template <typename T>
    constexpr bool intersects(const basic_ray<T>& ray_, const basic_bounding_sphere<T>& sphere) noexcept
    {
        // Reference: http://www.gamedev.net/page/resources/_/technical/math-and-physics/intersection-math-algorithms-learn-to-derive-r3033
        auto rad2 = sphere.radius * sphere.radius;
        auto l    = sphere.center - ray_.position;
        auto tPX  = vector::dot(l, ray_.direction);

        if (tPX < T(0))
        {
            return false;
        }

        auto dsq = vector::dot(l, l) - tPX * tPX;

        if (dsq > rad2)
        {
            return false;
        }

        auto thit = std::sqrt(rad2 - dsq);
        auto t    = tPX - thit;

        if (t < T(0))
        {
            t = tPX + thit;
        }

        return (t < T(0));
    }

    template <typename T>
    constexpr bool intersects(const basic_ray<T>& ray_, const basic_plane<T>& plane) noexcept
    {
        // Reference: http://www.gamedev.net/page/resources/_/technical/math-and-physics/intersection-math-algorithms-learn-to-derive-r3033
        auto denom = vector::dot(plane.normal, ray_.direction);

        if (std::abs(denom) == T(0)) // ray and plane are parallel so there is no intersection
        {
            return false;
        }

        auto t = -(vector::dot(ray_.position, plane.normal) + plane.d) / denom;

        return (t > T(0));
    }
}

#endif  // SCENER_MATH_BASIC_RAY_OPERATIONS_HPP
