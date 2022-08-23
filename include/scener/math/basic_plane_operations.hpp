// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_PLANE_OPERATIONS_HPP
#define SCENER_MATH_BASIC_PLANE_OPERATIONS_HPP

#include "scener/math/basic_plane.hpp"
#include "scener/math/basic_matrix.hpp"
#include "scener/math/basic_vector_operations.hpp"

namespace scener::math::plane 
{
    /// Creates a Plane object that contains three specified points.
    /// \param point1 the first point defining the plane.
    /// \param point2 the second point defining the plane.
    /// \param point3 the third point defining the plane.
    /// \returns the plane containing the three points.
    template <typename T = float>
    constexpr basic_plane<T> create_from_vertices(const basic_vector3<T>& point1
                                                , const basic_vector3<T>& point2
                                                , const basic_vector3<T>& point3) noexcept
    {
        // http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplanefrompoints(v=vs.85).aspx
        // http://en.wikipedia.org/wiki/Plane_%28geometry%29#Describing_a_plane_through_three_points

        // A plane can be described by a "point and a normal vector".
        // A suitable normal vector is given by the cross product
        // n = (p2 - p1) x (p3 - p1)
        // and the point r can be taken to be any of the given points p1, p2 or p3.
        //
        // The Hesse normal form for the equation of a plane relies on the parameter D. This form is:
        // n · r - D = 0
        // where n is a unit normal vector to the plane,
        // r a position vector of a point of the plane and D0 the distance of the plane from the origin.

        auto n = vector::normalize(vector::cross(point2 - point1, point3 - point1));
        auto d = -vector::dot(n, point1);

        return { n, d };
    }

    /// Calculates the dot product of a specified Vector4 and this Plane.
    /// \param plane The plane.
    /// \param value The four-dimensional vector.
    template <typename T = float>
    constexpr T dot(const basic_plane<T>& plane, const basic_vector4<T>& value) noexcept
    {
        return vector::dot({ plane.normal, plane.d }, value);
    }

    /// Returns the dot product of a specified three-dimensional vector and the Normal vector of this plane.
    /// \param p The plane.
    /// \param v The three-dimensional vector.
    /// \returns The dot product.
    template <typename T = float>
    constexpr T dot_normal(const basic_plane<T>& p, const basic_vector3<T>& v) noexcept
    {
        // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplanedotnormal(v=vs.85).aspx
        return vector::dot(p.normal, v);
    }

    /// Returns the dot product of a specified three-dimensional vector and the normal vector of this plane
    /// plus the distance (D) value of the plane.
    /// \param p The plane
    /// \param value The three-dimensional vector.
    /// \returns The dot product
    template <typename T = float>
    constexpr T dot_coordinate(const basic_plane<T>& p, const basic_vector3<T>& value) noexcept
    {
        return dot_normal(p, value) + p.d;
    }

    /// Changes the coefficients of the Normal vector of a Plane to make it of unit length.
    /// \param value the Plane to normalize.
    template <typename T = float>
    constexpr basic_plane<T> normalize(const basic_plane<T>& value) noexcept
    {
        auto reciprocal_length = T(1) / vector::length(value.normal);

        return { value.normal * reciprocal_length, value.d * reciprocal_length };
    }

    //template <typename T>
    //plane_intersection_type intersects(const basic_plane<T>& plane, const bounding_box& box)
    //{
    //    throw std::runtime_error("Not implemented");
    //}

    //template <typename T>
    //plane_intersection_type intersects(const basic_plane<T>& plane, const bounding_frustrum& frustrum)
    //{
    //    throw std::runtime_error("Not implemented");
    //}

    //template <typename T>
    //plane_intersection_type Plane::intersects(const basic_plane<T>& plane, const bounding_sphere& sphere)
    //{
    //    return sphere.intersects(plane);
    //}
}

#endif // SCENER_MATH_BASIC_PLANE_OPERATIONS_HPP
