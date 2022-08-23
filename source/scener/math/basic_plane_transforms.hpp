// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_PLANE_TRANSFORMS_HPP
#define SCENER_MATH_BASIC_PLANE_TRANSFORMS_HPP

#include "scener/math/basic_plane.hpp"
#include "scener/math/basic_matrix_operations.hpp"
#include "scener/math/basic_quaternion_operations.hpp"

namespace scener::math::plane 
{
    /// Transforms a normalized Plane by a Matrix.
    /// \param plane the normalized Plane to transform. This Plane must already be normalized.
    /// \param matrix the transform Matrix to apply to the Plane.
    /// \returns a new Plane that results from applying the transform.
    template <typename T>
    constexpr basic_plane<T> transform(const basic_plane<T>& plane, const basic_matrix4<T>& matrix) noexcept
    {
        return { basic_vector4<T> { plane.normal, plane.d } * matrix::transpose(matrix::invert(matrix)) };
    }

    /// Transforms a normalized Plane by a Quaternion rotation.
    /// \param plane the normalized Plane to transform. This Plane must already be normalized.
    /// \param rotation the Quaternion rotation to apply to the Plane.
    /// \returns a new Plane that results from applying the rotation.
    template <typename T>
    constexpr basic_plane<T> transform(const basic_plane<T>& plane, const basic_quaternion<T>& rotation) noexcept
    {
        // Reference: http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/transforms/
        //
        //      Pout = q * Pin * conj(q)
        //

        auto pout = (rotation * basic_quaternion<T>(plane.normal, plane.d) * quat::conjugate(rotation));

        return { pout.x, pout.y, pout.z, pout.w };
    }
}

#endif // SCENER_MATH_BASIC_PLANE_TRANSFORMS_HPP
