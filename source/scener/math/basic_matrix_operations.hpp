// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_MATRIX_OPERATIONS_HPP
#define SCENER_MATH_BASIC_MATRIX_OPERATIONS_HPP

#include "scener/math/basic_matrix.hpp"
#include "scener/math/basic_angle.hpp"
#include "scener/math/basic_quaternion_operations.hpp"
#include "scener/math/basic_vector_operations.hpp"
#include "scener/math/basic_plane_operations.hpp"

namespace scener::math::matrix 
{
    /// Returns a value indicating wheter the given matrix is an identity matrix .
    /// \param matrix the matrix to check for identity equality.
    /// \returns true if it's an identity matrix ; false otherwise.
    template <typename T = float, std::size_t Dimension>
    constexpr bool is_identity(const basic_matrix<T, Dimension>& matrix) noexcept
    {
        return (matrix == basic_matrix<T, Dimension>::identity());
    }

    template <typename T = float>
    constexpr basic_vector3<T> translation(const basic_matrix4<T>& matrix) noexcept
    {
        return static_cast<vector3>(matrix[3]);
    }

    template <typename T = float>
    void translation(basic_matrix4<T>& matrix, const basic_vector3<T>& translation) noexcept
    {
        matrix[3] = static_cast<vector4>(translation);
    }

    /// Returns the tranpose of the given matrix.
    /// \param matrix the source matrix.
    /// \returns the transposed matrix.
    template <typename T, std::size_t Dimension>
    constexpr basic_matrix<T, Dimension> transpose(const basic_matrix<T, Dimension>& matrix) noexcept
    {
        basic_matrix<T, Dimension> result;

        for (std::size_t r = 0; r < Dimension; ++r)
        {
            for (std::size_t c = 0; c < Dimension; ++c)
            {
                result[r][c] = matrix[c][r];
            }
        }

        return result;
    }

    /// Returns the tranpose of the given matrix3.
    /// \param source the source matrix.
    /// \returns the transposed matrix.
    template <typename T = float>
    constexpr basic_matrix3<T> transpose(const basic_matrix3<T>& source) noexcept
    {
        return { source.m11, source.m21, source.m31
               , source.m12, source.m22, source.m32
               , source.m13, source.m23, source.m33 };
    }

    /// Returns the tranpose of the given matrix4.
    /// \param source the source matrix.
    /// \returns the transposed matrix.
    template <typename T = float>
    constexpr basic_matrix4<T> transpose(const basic_matrix4<T>& source) noexcept
    {
        return { source.m11, source.m21, source.m31, source.m41
               , source.m12, source.m22, source.m32, source.m42
               , source.m13, source.m23, source.m33, source.m43
               , source.m14, source.m24, source.m34, source.m44 };
    }

    /// Retrieves the determinant of the given 3x3 matrix.
    /// \param matrix a matrix.
    /// \return the determinant of the given Matrix.
    template <typename T = float>
    constexpr T determinant(const basic_matrix3<T>& matrix) noexcept
    {
        // Reference: http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q23
        return matrix.m11 * (matrix.m22 * matrix.m33 - matrix.m32 * matrix.m23)
             - matrix.m12 * (matrix.m21 * matrix.m33 - matrix.m31 * matrix.m23)
             + matrix.m13 * (matrix.m21 * matrix.m32 - matrix.m31 * matrix.m22);
    }

    /// Retrieves the determinant of the given 4x4 matrix.
    /// \param matrix a matrix.
    /// \return the determinant of the given Matrix.
    template <typename T = float>
    constexpr T determinant(const basic_matrix4<T>& matrix) noexcept
    {
        // Reference: http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q24
        T a = matrix.m33 * matrix.m44 - matrix.m43 * matrix.m34;
        T b = matrix.m32 * matrix.m44 - matrix.m42 * matrix.m34;
        T c = matrix.m32 * matrix.m43 - matrix.m42 * matrix.m33;
        T d = matrix.m31 * matrix.m44 - matrix.m41 * matrix.m34;
        T e = matrix.m31 * matrix.m43 - matrix.m41 * matrix.m33;
        T f = matrix.m31 * matrix.m42 - matrix.m41 * matrix.m32;

        return matrix.m11 * (matrix.m22 * a - matrix.m23 * b + matrix.m24 * c)
             - matrix.m12 * (matrix.m21 * a - matrix.m23 * d + matrix.m24 * e)
             + matrix.m13 * (matrix.m21 * b - matrix.m22 * d + matrix.m24 * f)
             - matrix.m14 * (matrix.m21 * c - matrix.m22 * e + matrix.m23 * f);
    }

    /// Gets a value that indicates whether this Matrix is invertible.
    /// \param matrix a matrix.
    /// \returns a value that indicates whether this Matrix is invertible.
    template <typename T, std::size_t Dimension>
    constexpr bool has_inverse(const basic_matrix<T, Dimension>& matrix) noexcept
    {
        return (std::abs(determinant(matrix)) > epsilon<T>);
    }

    /// Inverts the given matrix.
    /// \param m the matrix to invert.
    template <typename T = float>
    constexpr basic_matrix4<T> invert(const basic_matrix4<T>& m) noexcept
    {
        basic_matrix4<T> inv;

        // Adapted from : ftp://download.intel.com/design/PentiumIII/sml/24504301.pdf
        std::array<T, 12> tmp; /* temp array for pairs */
        auto src = transpose(m);

        // calculate pairs for first 8 elements (cofactors)
        tmp[ 0] = src.m33 * src.m44;
        tmp[ 1] = src.m34 * src.m43;
        tmp[ 2] = src.m32 * src.m44;
        tmp[ 3] = src.m34 * src.m42;
        tmp[ 4] = src.m32 * src.m43;
        tmp[ 5] = src.m33 * src.m42;
        tmp[ 6] = src.m31 * src.m44;
        tmp[ 7] = src.m34 * src.m41;
        tmp[ 8] = src.m31 * src.m43;
        tmp[ 9] = src.m33 * src.m41;
        tmp[10] = src.m31 * src.m42;
        tmp[11] = src.m32 * src.m41;

        // calculate first 8 elements (cofactors)
        inv.m11  = tmp[0] * src.m22 + tmp[3] * src.m23 + tmp[ 4] * src.m24;
        inv.m11 -= tmp[1] * src.m22 + tmp[2] * src.m23 + tmp[ 5] * src.m24;

        inv.m12  = tmp[1] * src.m21 + tmp[6] * src.m23 + tmp[ 9] * src.m24;
        inv.m12 -= tmp[0] * src.m21 + tmp[7] * src.m23 + tmp[ 8] * src.m24;
        inv.m13  = tmp[2] * src.m21 + tmp[7] * src.m22 + tmp[10] * src.m24;
        inv.m13 -= tmp[3] * src.m21 + tmp[6] * src.m22 + tmp[11] * src.m24;
        inv.m14  = tmp[5] * src.m21 + tmp[8] * src.m22 + tmp[11] * src.m23;
        inv.m14 -= tmp[4] * src.m21 + tmp[9] * src.m22 + tmp[10] * src.m23;
        inv.m21  = tmp[1] * src.m12 + tmp[2] * src.m13 + tmp[ 5] * src.m14;
        inv.m21 -= tmp[0] * src.m12 + tmp[3] * src.m13 + tmp[ 4] * src.m14;
        inv.m22  = tmp[0] * src.m11 + tmp[7] * src.m13 + tmp[ 8] * src.m14;
        inv.m22 -= tmp[1] * src.m11 + tmp[6] * src.m13 + tmp[ 9] * src.m14;
        inv.m23  = tmp[3] * src.m11 + tmp[6] * src.m12 + tmp[11] * src.m14;
        inv.m23 -= tmp[2] * src.m11 + tmp[7] * src.m12 + tmp[10] * src.m14;
        inv.m24  = tmp[4] * src.m11 + tmp[9] * src.m12 + tmp[10] * src.m13;
        inv.m24 -= tmp[5] * src.m11 + tmp[8] * src.m12 + tmp[11] * src.m13;

        // calculate pairs for second 8 elements (cofactors)
        tmp[ 0] = src.m13 * src.m24;
        tmp[ 1] = src.m14 * src.m23;
        tmp[ 2] = src.m12 * src.m24;
        tmp[ 3] = src.m14 * src.m22;
        tmp[ 4] = src.m12 * src.m23;
        tmp[ 5] = src.m13 * src.m22;
        tmp[ 6] = src.m11 * src.m24;
        tmp[ 7] = src.m14 * src.m21;
        tmp[ 8] = src.m11 * src.m23;
        tmp[ 9] = src.m13 * src.m21;
        tmp[10] = src.m11 * src.m22;
        tmp[11] = src.m12 * src.m21;

        // calculate second 8 elements (cofactors)
        inv.m31  = tmp[ 0] * src.m42 + tmp[ 3] * src.m43 + tmp[ 4] * src.m44;
        inv.m31 -= tmp[ 1] * src.m42 + tmp[ 2] * src.m43 + tmp[ 5] * src.m44;
        inv.m32  = tmp[ 1] * src.m41 + tmp[ 6] * src.m43 + tmp[ 9] * src.m44;
        inv.m32 -= tmp[ 0] * src.m41 + tmp[ 7] * src.m43 + tmp[ 8] * src.m44;
        inv.m33  = tmp[ 2] * src.m41 + tmp[ 7] * src.m42 + tmp[10] * src.m44;
        inv.m33 -= tmp[ 3] * src.m41 + tmp[ 6] * src.m42 + tmp[11] * src.m44;
        inv.m34  = tmp[ 5] * src.m41 + tmp[ 8] * src.m42 + tmp[11] * src.m43;
        inv.m34 -= tmp[ 4] * src.m41 + tmp[ 9] * src.m42 + tmp[10] * src.m43;
        inv.m41  = tmp[ 2] * src.m33 + tmp[ 5] * src.m34 + tmp[ 1] * src.m32;
        inv.m41 -= tmp[ 4] * src.m34 + tmp[ 0] * src.m32 + tmp[ 3] * src.m33;
        inv.m42  = tmp[ 8] * src.m34 + tmp[ 0] * src.m31 + tmp[ 7] * src.m33;
        inv.m42 -= tmp[ 6] * src.m33 + tmp[ 9] * src.m34 + tmp[ 1] * src.m31;
        inv.m43  = tmp[ 6] * src.m32 + tmp[11] * src.m34 + tmp[ 3] * src.m31;
        inv.m43 -= tmp[10] * src.m34 + tmp[ 2] * src.m31 + tmp[ 7] * src.m32;
        inv.m44  = tmp[10] * src.m33 + tmp[ 4] * src.m31 + tmp[ 9] * src.m32;
        inv.m44 -= tmp[ 8] * src.m32 + tmp[11] * src.m33 + tmp[ 5] * src.m31;

        // calculate determinant
        auto det = src.m11 * inv.m11 + src.m12 * inv.m12 + src.m13 * inv.m13 + src.m14 * inv.m14;

        // calculate matrix inverse
        inv *= (1 / det);

        return inv;
    }

    /// Extracts the scalar, translation, and rotation components from a 3D scale/rotate/translate (SRT) Matrix.
    /// \param matrix The source matrix.
    /// \param[out] scale The scalar component of the transform matrix, expressed as a Vector3.
    /// \param[out] rotation The rotation component of the transform matrix, expressed as a Quaternion.
    /// \param[out] translation The translation component of the transform matrix, expressed as a Vector3.
    /// \returns true if the Matrix can be decomposed; false otherwise.
    template <typename T = float>
    constexpr bool decompose(const basic_matrix4<T>& matrix
                           , basic_vector3<T>&       scale
                           , basic_quaternion<T>&    rotation
                           , basic_vector3<T>&       translation) noexcept
    {
        // Adapted from: http://callumhay.blogspot.fr/2010/10/decomposing-affine-transforms.html

        // Copy the matrix first - we'll use this to break down each component
        auto mcopy = matrix;

        // Start by extracting the translation (and/or any projection) from the given matrix
        translation = matrix::translation(mcopy);

        matrix::translation(mcopy, vector3::zero());

        // Extract the rotation component - this is done using polar decompostion, where
        // we successively average the matrix with its inverse transpose until there is
        // no/a very small difference between successive averages
        T            norm  = 0;
        std::int32_t count = 0;

        auto mrotation = mcopy;

        do {
            auto nextRotation     = basic_matrix4<T>::identity();
            auto currInvTranspose = invert(transpose(mrotation));

            // find the next rotation matrix
            nextRotation = (mrotation + currInvTranspose) * 0.5f;

            norm = 0;

            for (std::uint32_t i = 0; i < 3; ++i)
            {
                T n = std::abs(mrotation[i].x - nextRotation[i].x)
                    + std::abs(mrotation[i].y - nextRotation[i].y)
                    + std::abs(mrotation[i].z - nextRotation[i].z);

                norm = std::max(norm, n);
            }

            mrotation = nextRotation;
        } while (++count < 100 && norm > epsilon<T>);

        // Extract the scale
        auto v1 = basic_vector3<T> { mcopy.m11, mcopy.m12, mcopy.m13 };
        auto v2 = basic_vector3<T> { mcopy.m21, mcopy.m22, mcopy.m23 };
        auto v3 = basic_vector3<T> { mcopy.m31, mcopy.m32, mcopy.m33 };

        scale = { vector::length(v1), vector::length(v2), vector::length(v3) };

        // Calculate the normalized rotation matrix and take its determinant to determine whether
        // it had a negative scale or not...
        auto row1 = vector::normalize(v1);
        auto row2 = vector::normalize(v2);
        auto row3 = vector::normalize(v3);

        basic_matrix4<T> nrotation { row1.x, row1.y, row1.z
                                   , row2.x, row2.y, row2.z
                                   , row3.x, row3.y, row3.z };

        rotation = quat::create_from_rotation_matrix(nrotation);

        // Special consideration: if there's a single negative scale
        // (all other combinations of negative scales will
        // be part of the rotation matrix), the determinant of the
        // normalized rotation matrix will be < 0.
        // If this is the case we apply an arbitrary negative to one
        // of the component of the scale.
        auto det = determinant(nrotation);

        if (det < T(0))
        {
            scale.x *= -1;
        }

        return (std::abs(det) > T(epsilon<T>));
    }

    /// Negates the given Matrix structure.
    /// \param matrix the matrix to negate.
    template <typename T, std::size_t Dimension>
    constexpr basic_matrix<T, Dimension> negate(const basic_matrix<T, Dimension>& matrix) noexcept
    {
        return -matrix;
    }

    /// Performs a linear interpolation between two matrices.
    /// \param value1 first matrix.
    /// \param value2 second matrix.
    /// \param amount value between 0 and 1 indicating the weight of value2.
    /// \returns the linear interpolation of the two matrices.
    template <typename T = float, typename S, std::size_t Dimension, typename = typename std::enable_if_t<std::is_arithmetic_v<S>>>
    constexpr basic_matrix<T, Dimension> lerp(const basic_matrix<T, Dimension>& value1
                                            , const basic_matrix<T, Dimension>& value2
                                            , S                                 amount) noexcept
    {
        basic_matrix<T, Dimension> result;

        std::transform(value1.begin(), value1.end(), value2.begin(), result.begin()
                     , [&amount](T a, T b) -> T { return math::lerp(a, b, amount); });

        return result;
    }

    // ---------------------------------------------------------------------------------------------------------------------
    // MATRIX 4x4 FUNCTIONS

    /// Creates a new Matrix that rotates around an arbitrary axis.
    /// \param axis Threee dimensional vector that specifies the axis around which to rotate.
    /// \param angle Value that specifies the angle of rotation, in radians.
    template <typename T = float>
    constexpr basic_matrix4<T> create_from_axis_angle(const basic_vector3<T>& axis, const basic_radians<T>& angle) noexcept
    {
        // http://mathworld.wolfram.com/RodriguesRotationFormula.html
        auto naxis = vector::normalize(axis);
        T    cos   = std::cos(angle.value);
        T    sin   = std::sin(angle.value);
        T    cos_1 = 1 - cos;
        T    x     = naxis.x;
        T    y     = naxis.y;
        T    z     = naxis.z;
        T    xx    = x * x;
        T    yy    = y * y;
        T    zz    = z * z;
        T    xy    = x * y;
        T    yz    = y * z;
        T    xz    = x * z;

        return {     cos + xx * cos_1,  z * sin + xy * cos_1, -y * sin + xz * cos_1
               , xy * cos_1 - z * sin,      cos + yy * cos_1,  x * sin + yz * cos_1
               , y * sin + xz * cos_1, -x * sin + yz * cos_1,      cos + zz * cos_1 };
    }

    /// Creates a rotation Matrix from a Quaternion.
    /// \param quaternion Quaternion to create the Matrix from.
    template <typename T = float>
    constexpr basic_matrix4<T> create_from_quaternion(const basic_quaternion<T>& quaternion) noexcept
    {
        // Reference: http://en.wikipedia.org/wiki/Rotation_matrix
        //            http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
        // [1 - 2yy - 2zz][2xy - 2zw    ][2xz + 2yw    ]
        // [2xy + 2zw    ][1 - 2xx - 2zz][2yz - 2xw    ]
        // [2xz - 2yw    ][2yz + 2xw    ][1 - 2xx - 2yy]

        T xx = quaternion.x * quaternion.x;
        T yy = quaternion.y * quaternion.y;
        T zz = quaternion.z * quaternion.z;
        T xy = quaternion.x * quaternion.y;
        T zw = quaternion.z * quaternion.w;
        T xz = quaternion.x * quaternion.z;
        T yw = quaternion.y * quaternion.w;
        T yz = quaternion.y * quaternion.z;
        T xw = quaternion.x * quaternion.w;

        return { 1 - 2 * (yy + zz),     2 * (xy + zw),     2 * (xz - yw)
               ,     2 * (xy - zw), 1 - 2 * (xx + zz),     2 * (yz + xw)
               ,     2 * (xz + yw),     2 * (yz - xw), 1 - 2 * (xx + yy) };
    }

    /// Creates a new matrix with a specified yaw, pitch, and roll.
    /// The order of transformations is yaw first, then pitch, then roll.
    /// \param yaw Yaw around the y-axis.
    /// \param pitch Pitch around the z-axis.
    /// \param roll Roll around the x-axis.
    template <typename T = float>
    constexpr basic_matrix4<T> create_from_yaw_pitch_roll(const basic_radians<T>& yaw
                                                        , const basic_radians<T>& pitch
                                                        , const basic_radians<T>& roll) noexcept
    {
        return create_from_axis_angle(basic_vector3<T>::unit_z(), roll)
             * create_from_axis_angle(basic_vector3<T>::unit_x(), pitch)
             * create_from_axis_angle(basic_vector3<T>::unit_y(), yaw);
    }

    /// Creates a perspective projection matrix.
    /// \param left The coordinate for the left-vertical clipping plane.
    /// \param right The coordinate for the right-vertical clipping plane.
    /// \param bottom The coordinate for the bottom-horizontal clipping plane.
    /// \param top The coordinate for the top-horizontal clipping plane.
    /// \param zNear The distances to the near-depth clipping plane. Must be positive.
    /// \param zFar The distances to the far-depth clipping plane. Must be positive.
    template <typename T = float>
    constexpr basic_matrix4<T> create_frustum(T left, T right, T bottom, T top, T zNear, T zFar) noexcept
    {
        Expects (zNear < 0 || zFar < 0);

        T rsl = right - left;
        T rpl = right + left;
        T tsb = top   - bottom;
        T tpb = top   + bottom;
        T fsb = zFar  - zNear;
        T fpn = zFar  - zNear;

        return { (2 * zNear) / rsl, 0                ,  (rpl / rsl), 0
               , 0                , (2 * zNear) / tsb,  (tpb / tsb), 0
               , 0                , 0                , -(fpn / fsb), -(2 * zFar * zNear / fsb)
               , 0                , 0                , -1          , 0 };
    }

    /// Creates a view matrix
    /// \param cameraPosition The position of the camera.
    /// \param cameraTarget The target towards which the camera is pointing.
    /// \param cameraUpVector The direction that is "up" from the camera's point of view.
    template <typename T = float>
    constexpr inline basic_matrix4<T> create_look_at(const basic_vector3<T>& cameraPosition
                                                   , const basic_vector3<T>& cameraTarget
                                                   , const basic_vector3<T>& cameraUpVector) noexcept
    {
        // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/bb281711(v=vs.85).aspx
        // zaxis = normal(cameraPosition - cameraTarget)
        // xaxis = normal(cross(cameraUpVector, zaxis))
        // yaxis = cross(zaxis, xaxis)

        // [ xaxis.x                   ][yaxis.x                    ][zaxis.x                    ][0]
        // [ xaxis.y                   ][yaxis.y                    ][zaxis.y                    ][0]
        // [ xaxis.z                   ][yaxis.z                    ][zaxis.z                    ][0]
        // [-dot(xaxis, cameraPosition)][-dot(yaxis, cameraPosition)][-dot(zaxis, cameraPosition)][1]

        auto zAxis = vector::normalize(cameraPosition - cameraTarget);
        auto xAxis = vector::normalize(vector::cross(cameraUpVector, zAxis));
        auto yAxis = vector::cross(zAxis, xAxis);
        auto dx    = vector::dot(xAxis, cameraPosition);
        auto dy    = vector::dot(yAxis, cameraPosition);
        auto dz    = vector::dot(zAxis, cameraPosition);

        return { xAxis.x, yAxis.x, zAxis.x, 0
               , xAxis.y, yAxis.y, zAxis.y, 0
               , xAxis.z, yAxis.z, zAxis.z, 0
               , -dx    , -dy    , -dz    , 1 };
    }

    /// Creates an orthogonal matrix
    /// \param width Width of the view volume.
    /// \param height Height of the view volume.
    /// \param zNear Minimum z-value of the view volume.
    /// \param zFar Maximun z-value of the view volume.
    template <typename T = float>
    constexpr basic_matrix4<T> create_orthographic(T width, T height, T zNear, T zFar) noexcept
    {
        // Reference: http://msdn.microsoft.com/en-us/library/bb205349(v=vs.85).aspx
        // [2/w][0  ][0         ][0]
        // [0  ][2/h][0         ][0]
        // [0  ][0  ][1/(zn-zf) ][0]
        // [0  ][0  ][zn/(zn-zf)][1]

        T nsf = zNear - zFar;

        return { 2 / width, 0         , 0          , 0
               , 0        , 2 / height, 0          , 0
               , 0        , 0         , 1 / nsf    , 0
               , 0        , 0         , zNear / nsf, 1 };
    }

    /// Builds a customized, orthogonal projection matrix.
    /// \param left Minimum x-value of the view volume.
    /// \param right Maximum x-value of the view volume.
    /// \param bottom Minimum y-value of the view volume.
    /// \param top Maximum y-value of the view volume.
    /// \param zNear Minimum z-value of the view volume.
    /// \param zFar Maximun z-value of the view volume.
    template <typename T = float>
    constexpr basic_matrix4<T> create_orthographic_off_center(T left, T right, T bottom, T top, T zNear, T zFar) noexcept
    {
        // Reference: http://msdn.microsoft.com/en-us/library/bb205348(v=vs.85).aspx
        // [2/(r-l)    ][0          ][0         ][0]
        // [0          ][2/(t-b)    ][0         ][0]
        // [0          ][0          ][1/(zn-zf) ][0]
        // [(l+r)/(l-r)][(t+b)/(b-t)][zn/(zn-zf)][1]

        T lsr = left   - right;
        T lpr = left   + right;
        T rsl = right  - left;
        T bst = bottom - top;
        T tsb = top    - bottom;
        T tpb = top    + bottom;
        T nsf = zNear  - zFar;

        return { 2 / rsl  , 0        , 0          , 0
               , 0        , 2 / tsb  , 0          , 0
               , 0        , 0        , 1 / nsf    , 0
               , lpr / lsr, tpb / bst, zNear / nsf, 1 };
    }

    /// Builds a perspective projection matrix.
    /// \param width Width of the view volume at the near view plane.
    /// \param height Height of the view volume at the near view plane.
    /// \param zNear Distance to the near view plane.
    /// \param zFar Distance to the far view plane.
    template <typename T = float>
    constexpr basic_matrix4<T> create_perspective(T width, T height, T zNear, T zFar) noexcept
    {
        Expects(zNear >= 0 && zFar >= 0 && zNear < zFar);

        // Reference: http://msdn.microsoft.com/en-us/library/bb205355(v=vs.85).aspx
        // [2*zn/w][0     ][0            ][ 0]
        // [0     ][2*zn/h][0            ][ 0]
        // [0     ][0     ][zf/(zn-zf)   ][-1]
        // [0     ][0     ][zn*zf/(zn-zf)][ 0]

        T nsf = zNear - zFar;

        return { 2 * zNear / width, 0                 , 0                 ,  0
               , 0                , 2 * zNear / height, 0                 ,  0
               , 0                , 0                 , zFar / nsf        , -1
               , 0                , 0                 , zNear * zFar / nsf,  0 };
    }

    /// Builds a perspective projection matrix based on a field of view and returns by value.
    /// \param fieldOfView Field of view in the y direction.
    /// \param aspectRatio Aspect ratio, defined as view space width divided by height.
    /// \param zNear Distance to the near view plane.
    /// \param zFar Distance to the far view plane.
    template <typename T = float>
    constexpr basic_matrix4<T> create_perspective_field_of_view(const basic_radians<T>& fieldOfView
                                                              , T                       aspectRatio
                                                              , T                       zNear
                                                              , T                       zFar) noexcept
    {
        Expects(fieldOfView.value >= T(0) && fieldOfView.value <= pi<T>);
        Expects(zNear >= T(0));
        Expects(zFar >= T(0));
        Expects(zNear < zFar);

        // Reference: http://msdn.microsoft.com/en-us/library/bb205351(v=vs.85).aspx
        // [xScale][0     ][0            ][ 0]
        // [0     ][yScale][0            ][ 0]
        // [0     ][0     ][zf/(zn-zf)   ][-1]
        // [0     ][0     ][zn*zf/(zn-zf)][ 0]
        //
        // where:
        // yScale = cot(fovY/2)
        // xScale = yScale / aspect ratio

        T yScale = T(1) / std::tan(fieldOfView.value * T(0.5));
        T xScale = yScale / aspectRatio;
        T nsr    = zNear - zFar;

        return { xScale, 0     , 0                 ,  0
               , 0     , yScale, 0                 ,  0
               , 0     , 0     , zFar / nsr        , -1
               , 0     , 0     , zNear * zFar / nsr,  0 };
    }

    /// Builds a customized, right-handed perspective projection matrix.
    /// \param left Minimum x-value of the view volume.
    /// \param right Maximum x-value of the view volume.
    /// \param bottom Minimum y-value of the view volume.
    /// \param top Maximum y-value of the view volume.
    /// \param zNear Minimum z-value of the view volume.
    /// \param zFar Maximun z-value of the view volume.
    template <typename T = float>
    constexpr basic_matrix4<T> create_perspective_off_center(T left, T right, T bottom, T top, T zNear, T zFar) noexcept
    {
        Expects(zNear >= 0.0f);
        Expects(zFar >= 0.0f);
        Expects(zNear < zFar);

        // Reference : https://msdn.microsoft.com/en-us/library/bb205354(v=vs.85).aspx
        // [2*zn/(r-l) ][0          ][0            ][ 0]
        // [0          ][2*zn/(t-b) ][0            ][ 0]
        // [(l+r)/(r-l)][(t+b)/(t-b)][zf/(zn-zf)   ][-1]
        // [0          ][0          ][zn*zf/(zn-zf)][ 0]

        T rsl = right - left;
        T lpr = left  + right;
        T tsb = top   - bottom;
        T tpb = top   + bottom;
        T nsf = zNear - zFar;

        return { 2 * zNear / rsl, 0              , 0                 ,  0
               , 0              , 2 * zNear / tsb, 0                 ,  0
               , lpr / rsl      , tpb / tsb      , zFar / nsf        , -1
               , 0              , 0              , zNear * zFar / nsf,  0 };
    }

    /// Returns a matrix that can be used to rotate a set of vertices around the x-axis.
    /// \param angle Value that specifies the angle of rotation.
    template <typename T = float>
    constexpr basic_matrix4<T> create_rotation_x(const basic_radians<T>& angle) noexcept
    {
        // Reference: http://en.wikipedia.org/wiki/Rotation_matrix
        T cos = std::cos(angle.value);
        T sin = std::sin(angle.value);

        return { 1,    0,    0
               , 0,  cos,  sin
               , 0, -sin,  cos };
    }

    /// Creates a matrix for rotating points around the X-axis, from a center point.
    /// \param angle The amount by which to rotate around the X-axis.
    /// \param center The center point.
    /// \returns The rotation matrix.
    template <typename T = float>
    constexpr basic_matrix4<T> create_rotation_x(const basic_radians<T>& angle, const basic_vector3<T>& center) noexcept
    {
        // Reference: http://www.euclideanspace.com/maths/geometry/affine/aroundPoint/matrix3d/index.htm
        // [r00][r01][r02][x - r00*x - r01*y - r02*z]
        // [r10][r11][r12][y - r10*x - r11*y - r12*z]
        // [r20][r21][r22][z - r20*x - r21*y - r22*z]
        // [0  ][0  ][0  ][1                        ]

        T cos = std::cos(angle.value);
        T sin = std::sin(angle.value);
        T y   = center.y;
        T z   = center.z;

        return { 1,  0                   , 0                    , 0
               , 0,  cos                 , sin                  , 0
               , 0, -sin                 , cos                  , 0
               , 0, y - cos * y + sin * z, z - sin * y - cos * z, 1 };
    }

    /// Returns a matrix that can be used to rotate a set of vertices around the y-axis.
    /// \param angle value that specifies the angle of rotation, in radians.
    template <typename T = float>
    constexpr basic_matrix4<T> create_rotation_y(const basic_radians<T>& angle) noexcept
    {
        // Reference: http://en.wikipedia.org/wiki/Rotation_matrix
        T cos = std::cos(angle.value);
        T sin = std::sin(angle.value);

        return {  cos, 0, -sin
               ,    0, 1,    0
               ,  sin, 0,  cos };
    }

    /// Creates a matrix for rotating points around the Y-axis, from a center point.
    /// \param angle the amount, by which to rotate around the Y-axis, in radians.
    /// \param center the center point.
    /// \returns the rotation matrix.
    template <typename T = float>
    constexpr basic_matrix4<T> create_rotation_y(const basic_radians<T>& angle, const basic_vector3<T>& center) noexcept
    {
        // Reference: http://www.euclideanspace.com/maths/geometry/affine/aroundPoint/matrix3d/index.htm
        // [r00][r01][r02][x - r00*x - r01*y - r02*z]
        // [r10][r11][r12][y - r10*x - r11*y - r12*z]
        // [r20][r21][r22][z - r20*x - r21*y - r22*z]
        // [0  ][0  ][0  ][1                        ]

        T cos = std::cos(angle.value);
        T sin = std::sin(angle.value);
        T x   = center.x;
        T z   = center.z;

        return { cos                  , 0, -sin                 , 0
               , 0                    , 1,  0                   , 0
               , sin                  , 0,  cos                 , 0
               , x - cos * x - sin * z, 0, z + sin * x - cos * z, 1 };
    }

    /// Returns a matrix that can be used to rotate a set of vertices around the z-axis.
    /// \param angle value that specifies the angle of rotation, in radians
    template <typename T = float>
    constexpr basic_matrix4<T> create_rotation_z(const basic_radians<T>& angle) noexcept
    {
        // Reference: http://en.wikipedia.org/wiki/Rotation_matrix
        T cos = std::cos(angle.value);
        T sin = std::sin(angle.value);

        return {  cos,  sin, 0
               , -sin,  cos, 0
               ,  0  ,  0  , 1 };
    }

    /// Creates a matrix for rotating points around the Z-axis, from a center point.
    /// \param angle the amount by which to rotate around the Z-axis, in radians.
    /// \param center the center point.
    /// \returns the rotation matrix.
    template <typename T = float>
    constexpr basic_matrix4<T> create_rotation_z(const basic_radians<T>& angle, const basic_vector3<T>& center) noexcept
    {
        // Reference: http://www.euclideanspace.com/maths/geometry/affine/aroundPoint/matrix3d/index.htm
        // [r00][r01][r02][x - r00*x - r01*y - r02*z]
        // [r10][r11][r12][y - r10*x - r11*y - r12*z]
        // [r20][r21][r22][z - r20*x - r21*y - r22*z]
        // [0  ][0  ][0  ][1                        ]

        T cos = std::cos(angle.value);
        T sin = std::sin(angle.value);
        T x   = center.x;
        T y   = center.y;

        return {  cos                 , sin                  , 0, 0
               , -sin                 , cos                  , 0, 0
               ,  0                   , 0                    , 1, 0
               , x - cos * x + sin * y, y - sin * x - cos * y, 0, 1 };
    }

    /// Creates a scaling matrix from the specified X, Y, and Z components.
    /// \param xScale The value to scale by on the X axis.
    /// \param yScale The value to scale by on the Y axis.
    /// \param zScale The value to scale by on the Z axis.
    template <typename T = float>
    constexpr basic_matrix4<T> create_scale(T xScale, T yScale, T zScale) noexcept
    {
        return { xScale,      0,      0
               ,      0, yScale,      0
               ,      0,      0, zScale };
    }

    /// Creates a scaling matrix that is offset by a given center point.
    /// \param xScale The value to scale by on the X axis.
    /// \param yScale The value to scale by on the Y axis.
    /// \param zScale The value to scale by on the Z axis.
    /// \param center The center point.
    template <typename T = float>
    constexpr basic_matrix4<T> create_scale(T xScale, T yScale, T zScale, const basic_vector3<T>& center) noexcept
    {
        // Reference: http://www.euclideanspace.com/maths/geometry/affine/aroundPoint/matrix3d/index.htm
        // [s00][s01][s02][x - s00*x - s01*y - s02*z]
        // [s10][s11][s12][y - s10*x - s11*y - s12*z]
        // [s20][s21][s22][z - s20*x - s21*y - s22*z]
        // [0  ][0  ][0  ][1                        ]

        T x = center.x;
        T y = center.y;
        T z = center.z;

        return { xScale        , 0             , 0             , 0
               , 0             , yScale        , 0             , 0
               , 0             , 0             , zScale        , 0
               , x - xScale * x, y - yScale * y, z - zScale * z, 1 };
    }

    /// Creates a uniform scaling matrix that scales equally on each axis.
    /// \param scale Amount to scale by.
    template <typename T = float>
    constexpr basic_matrix4<T> create_scale(T scale) noexcept
    {
        return create_scale(scale, scale, scale);
    }

    /// Creates a uniform scaling matrix that scales equally on each axis with a center point.
    /// \param scale Amount to scale by.
    /// \param center The center point
    template <typename T = float>
    constexpr basic_matrix4<T> create_scale(T scale, const basic_vector3<T>& center) noexcept
    {
        return create_scale(scale, scale, scale, center);
    }

    /// Creates a scaling matrix from the specified vector scale.
    /// \param scales Amounts to scale by on the x, y, and z axes.
    template <typename T = float>
    constexpr basic_matrix4<T> create_scale(const basic_vector3<T>& scales) noexcept
    {
        return create_scale(scales.x, scales.y, scales.z);
    }

    /// Creates a scaling matrix with a center point.
    /// \param scales The vector that contains the amount to scale on each axis.
    /// \param center The center point
    template <typename T = float>
    constexpr basic_matrix4<T> create_scale(const basic_vector3<T>& scales, const basic_vector3<T>& center) noexcept
    {
        return create_scale(scales.x, scales.y, scales.z, center);
    }

    /// Creates a translation Matrix
    /// \param x Value to translate by on the x-axis.
    /// \param y Value to translate by on the y-axis.
    /// \param z Value to translate by on the z-axis.
    template <typename T = float>
    constexpr basic_matrix4<T> create_translation(T x, T y, T z) noexcept
    {
        return { 1, 0, 0, 0
               , 0, 1, 0, 0
               , 0, 0, 1, 0
               , x, y, z, 1 };
    }

    /// Creates a translation Matrix
    /// \param position Amounts to translate by on the x, y, and z-axis.
    template <typename T = float>
    constexpr basic_matrix4<T> create_translation(const basic_vector3<T>& position) noexcept
    {
        return create_translation(position.x, position.y, position.z);
    }

    /// Creates a matrix that reflects the coordinate system about a specified plane.
    /// \param plane the plane.
    /// \returns a new matrix expressing the reflection.
    template <typename T = float>
    constexpr basic_matrix4<T> create_reflection(const basic_plane<T>& plane) noexcept
    {
        // Reference: https://msdn.microsoft.com/en-us/library/bb205356(v=vs.85).aspx
        // P = normalize(Plane);

        // [-2 * P.a * P.a + 1][-2 * P.b * P.a    ][-2 * P.c * P.a    ][0]
        // [-2 * P.a * P.b    ][-2 * P.b * P.b + 1][-2 * P.c * P.b    ][0]
        // [-2 * P.a * P.c    ][-2 * P.b * P.c    ][-2 * P.c * P.c + 1][0]
        // [-2 * P.a * P.d    ][-2 * P.b * P.d    ][-2 * P.c * P.d    ][1]

        auto P = plane::normalize(plane);
        auto a = -P.normal.x;
        auto b = -P.normal.y;
        auto c = -P.normal.z;
        auto d = -P.d;

        return { -2 * a * a + 1, -2 * b * a    , -2 * c * a    , 0
               , -2 * a * b    , -2 * b * b + 1, -2 * c * b    , 0
               , -2 * a * c    , -2 * b * c    , -2 * c * c + 1, 0
               , -2 * a * d    , -2 * b * d    , -2 * c * d    , 1 };
    }

    /// Creates a matrix that flattens geometry into a specified plane as if casting a shadow from a specified light source.
    /// \param lightDirection the direction from which the light that will cast the shadow is coming.
    /// \param plane the plane onto which the new matrix should flatten geometry so as to cast a shadow.
    /// \returns a new matrix that can be used to flatten geometry onto the specified plane from the specified direction.
    template <typename T = float>
    constexpr basic_matrix4<T> create_shadow(const basic_vector3<T>& lightDirection, const basic_plane<T>& plane) noexcept
    {
        // Reference: https://msdn.microsoft.com/en-us/library/bb205364(v=vs.85).aspx
        // P = normalize(Plane);
        // L = Light;
        // d = -dot(P, L)

        // [P.a * L.x + d][P.a * L.y    ][P.a * L.z    ][P.a * L.w    ]
        // [P.b * L.x    ][P.b * L.y + d][P.b * L.z    ][P.b * L.w    ]
        // [P.c * L.x    ][P.c * L.y    ][P.c * L.z + d][P.c * L.w    ]
        // [P.d * L.x    ][P.d * L.y    ][P.d * L.z    ][P.d * L.w + d]
        //
        // If the light's w-component is 0, the ray from the origin to the light represents a directional light.
        // If it is 1, the light is a point light.

        auto P = plane::normalize(plane);
        auto L = basic_vector4<T> { lightDirection, T(0) };
        auto a = -P.normal.x;
        auto b = -P.normal.y;
        auto c = -P.normal.z;
        auto d = -P.d;
        auto D = plane::dot(P, L);

        return { a * L.x + D, a * L.y    , a * L.z    , a * L.w
               , b * L.x    , b * L.y + D, b * L.z    , b * L.w
               , c * L.x    , c * L.y    , c * L.z + D, c * L.w
               , d * L.x    , d * L.y    , d * L.z    , d * L.w + D };
    }

    /// Creates a World Matrix
    /// \param position Position of the object. This value is used in translation operations.
    /// \param forward Forward direction of the object.
    /// \param up Upward direction of the object; usually [0, 1, 0].
    template <typename T = float>
    constexpr inline basic_matrix4<T> create_world(const basic_vector3<T>& position
                                                 , const basic_vector3<T>& forward
                                                 , const basic_vector3<T>& up) noexcept
    {
        auto nf    = vector::normalize(forward);
        auto right = vector::normalize(vector::cross(nf, vector::normalize(up)));
        auto upv   = vector::normalize(vector::cross(right, nf));

        return { right.x   , right.y   , right.z   , 0
               , upv.x     , upv.y     , upv.z     , 0
               , -nf.x     , -nf.y     , -nf.z     , 0
               , position.x, position.y, position.z, 1 };
    }

    /// Transforms a Matrix by applying a quaternion rotation.
    /// \param value the matrix to transform.
    /// \param rotation the quaternion rotation.
    /// \returns the transformed matrix.
    template <typename T, std::size_t Dimension>
    constexpr basic_matrix<T, Dimension> transform(const basic_matrix<T, Dimension>& value
                                                 , const basic_quaternion<T>&        rotation) noexcept
    {
        return value * create_from_quaternion(rotation);
    }
}

#endif // SCENER_MATH_BASIC_MATRIX_OPERATIONS_HPP
