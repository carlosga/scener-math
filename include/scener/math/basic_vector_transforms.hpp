// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_VECTOR_TRANSFORMS_HPP
#define SCENER_MATH_BASIC_VECTOR_TRANSFORMS_HPP

#include "scener/math/basic_matrix_operations.hpp"
#include "scener/math/basic_quaternion.hpp"

namespace scener::math::vector
{
    // -----------------------------------------------------------------------------------------------------------------
    // TRANSFORM: VECTOR by MATRIX 4x4

    /// Transforms a two-dimensional vector by a specified 4x4 matrix.
    /// \param position the vector to transform.
    /// \param matrix the transformation matrix.
    /// \returns the transformed vector.
    template <typename T = float>
    basic_vector2<T> transform(const basic_vector2<T>& position, const basic_matrix4<T>& matrix) noexcept
    {
        return { (position.x * matrix.m11) + (position.y * matrix.m21) + matrix.m41
               , (position.x * matrix.m12) + (position.y * matrix.m22) + matrix.m42 };
    }

    /// Transforms a 3D vector by the given matrix.
    /// \param position the 3D Vector to be transformed.
    /// \param matrix the transformation matrix.
    /// \returns the transformed vector.
    template <typename T = float>
    constexpr basic_vector3<T> transform(const basic_vector3<T>& position, const basic_matrix4<T>& matrix) noexcept
    {
        return (position * matrix);
    }

    /// Transforms a four-dimensional vector by a specified 4x4 matrix.
    /// \param position the vector to transform.
    /// \param matrix the transformation matrix.
    /// \returns the transformed vector.
    template <typename T = float>
    constexpr basic_vector4<T> transform(const basic_vector4<T>& position, const basic_matrix4<T>& matrix) noexcept
    {
        return (position * matrix);
    }

    // -----------------------------------------------------------------------------------------------------------------
    // TRANSFORM: VECTOR by QUATERNION

    /// Transforms a vector by the specified quaternion rotation value.
    /// \param vector The vector to rotate.
    /// \param rotation The rotation to apply.
    /// \return The transformed vector.
    template <typename T = float>
    constexpr basic_vector2<T> transform(const basic_vector2<T>& vector, const basic_quaternion<T>& rotation) noexcept
    {
        return (transform(vector, matrix::create_from_quaternion(rotation)));
    }

    /// Transforms a vector by the specified quaternion rotation value.
    /// \param vector The vector to rotate.
    /// \param rotation The rotation to apply.
    /// \return The transformed vector.
    template <typename T = float>
    constexpr basic_vector3<T> transform(const basic_vector3<T>& vector, const basic_quaternion<T>& rotation) noexcept
    {
        return (vector * matrix::create_from_quaternion(rotation));
    }

    /// Transforms a four-dimensional vector by a specified quaternion.
    /// \param value The vector to transform.
    /// \param rotation The transformation quaternion.
    /// \returns The transformed vector
    template <typename T = float>
    constexpr basic_vector4<T> transform(const basic_vector4<T>& value, const basic_quaternion<T>& rotation) noexcept
    {
        return (value * matrix::create_from_quaternion(rotation));
    }

    // -----------------------------------------------------------------------------------------------------------------
    // TRANSFORM NORMAL: VECTOR by MATRIX

    /// This method transforms the vector normal (x, y, 0) of the source vector,
    /// or the array of vector structures, by the sourceMatrix matrix.
    /// If you transform a normal by a non-affine matrix, the matrix you pass to this
    /// function should be the transpose of the inverse of the matrix you would use to
    /// transform a coordinate.
    template <typename T = float, std::size_t Dimension>
    constexpr basic_vector2<T> transform_normal(const basic_vector2<T>&           normal
                                              , const basic_matrix<T, Dimension>& matrix) noexcept
    {
        static_assert(Dimension == 2 || Dimension == 3 || Dimension == 4, "Invalid matrix dimensions");

        return { (normal.x * matrix.m11) + (normal.y * matrix.m21)
               , (normal.x * matrix.m12) + (normal.y * matrix.m22) };
    }

    /// This method transforms the vector normal (x, y, z, 0) of the source vector,
    /// or the array of vector structures, by the sourceMatrix matrix.
    /// If you transform a normal by a non-affine matrix, the matrix you pass to this
    /// function should be the transpose of the inverse of the matrix you would use to
    /// transform a coordinate.
    template <typename T = float, std::size_t Dimension>
    constexpr basic_vector3<T> transform_normal(const basic_vector3<T>&           normal
                                              , const basic_matrix<T, Dimension>& matrix) noexcept
    {
        static_assert(Dimension == 3 || Dimension == 4, "Invalid matrix dimensions");

        return { (normal.x * matrix.m11) + (normal.y * matrix.m21) + (normal.z * matrix.m31)
               , (normal.x * matrix.m12) + (normal.y * matrix.m22) + (normal.z * matrix.m32)
               , (normal.x * matrix.m13) + (normal.y * matrix.m23) + (normal.z * matrix.m33) };
    }
}

#endif // SCENER_MATH_BASIC_VECTOR_TRANSFORMS_HPP
