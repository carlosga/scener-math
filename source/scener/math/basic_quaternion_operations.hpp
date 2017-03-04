// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_QUATERNION_OPERATIONS_HPP
#define SCENER_MATH_BASIC_QUATERNION_OPERATIONS_HPP

#include "scener/math/basic_quaternion.hpp"
#include "scener/math/basic_angle.hpp"
#include "scener/math/basic_matrix.hpp"
#include "scener/math/basic_vector_operations.hpp"

namespace scener::math::quat 
{
    /// Returns a value indicating wheter the given quaternion is an identity quaternion.
    /// \param q the quaternion to check for identity equality.
    /// \returns true if it's an identity quaternion; false otherwise.
    template <typename T = float>
    constexpr bool is_identity(const basic_quaternion<T>& q) noexcept
    {
        return (q == basic_quaternion<T>::identity());
    }

    /// Gets the square of the length of the given quaternion.
    /// \param q the quaternion of which to return the square of the length.
    /// \returns the square of the length of the given quaternion.
    template <typename T = float>
    constexpr T length_squared(const basic_quaternion<T>& q) noexcept
    {
        return (q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w);
    }

    /// Gets the length of the given Quaternion.
    /// \param q the quaternion of which to return the length.
    /// \returns the length of the given Quaternion.
    template <typename T = float>
    constexpr T length(const basic_quaternion<T>& q) noexcept
    {
        return std::sqrt(length_squared(q));
    }

    /// Returns the conjugate of a specified quaternion.
    /// \param quaternion the Quaternion of which to return the conjugate.
    /// \returns the quaternion conjugate.
    template <typename T = float>
    constexpr basic_quaternion<T> conjugate(const basic_quaternion<T>& quaternion) noexcept
    {
        // The conjugate of a quaternion is defined by
        // q* = (w + xi + yj + zk) = w -xi -yj -zk
        return { -quaternion.x, -quaternion.y, -quaternion.z, quaternion.w };
    }

    /// Creates a quaternion from a vector and an angle to rotate about the vector.
    /// \param axisOfRotation Vector3 that represents the axis of rotation.
    /// \param angle Angle to rotate around the specified axis, in radians.
    /// \returns the created Quaternion.
    template <typename T = float>
    constexpr basic_quaternion<T> create_from_axis_angle(const basic_vector3<T>& axisOfRotation
                                                       , const basic_radians<T>& angle) noexcept
    {
        // The quaternion in terms of axis-angle is:
        // q = cos(a/2) + i ( x * sin(a/2)) + j (y * sin(a/2)) + k ( z * sin(a/2))

        auto theta = angle * T(0.5);
        auto rads  = theta.value;
        auto rSin  = std::sin(rads);

        return { axisOfRotation.x * rSin
               , axisOfRotation.y * rSin
               , axisOfRotation.z * rSin
               , std::cos(rads) };
    }

    /// Creates a Quaternion from a rotation Matrix.
    /// \param matrix the rotation matrix.
    template <typename T = float>
    constexpr basic_quaternion<T> create_from_rotation_matrix(const basic_matrix4<T>& matrix) noexcept
    {
        // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

        auto result = basic_quaternion<T> { };
        T    tr     = matrix.m11 + matrix.m22 + matrix.m33;

        if (tr > T(0))
        {
            T s      = std::sqrt(tr + T(1));
            result.w = s * T(0.5);
            s        = T(0.5) / s;
            result.x = (matrix.m23 - matrix.m32) * s;
            result.y = (matrix.m31 - matrix.m13) * s;
            result.z = (matrix.m12 - matrix.m21) * s;
        }
        else
        {
            if ((matrix.m11 >= matrix.m22) && (matrix.m11 >= matrix.m33))
            {
                T s      = std::sqrt(1 + matrix.m11 - matrix.m22 - matrix.m33);
                T s2     = T(0.5) / s;
                result.w = (matrix.m23 - matrix.m32) * s2;
                result.x = T(0.5) * s;
                result.y = (matrix.m12 + matrix.m21) * s2;
                result.z = (matrix.m13 + matrix.m31) * s2;
            }
            else if (matrix.m22 > matrix.m33)
            {
                T s      = std::sqrt(1 + matrix.m22 - matrix.m11 - matrix.m33);
                T s2     = T(0.5) / s;
                result.w = (matrix.m31 - matrix.m13) * s2;
                result.x = (matrix.m21 + matrix.m12) * s2;
                result.y = T(0.5) * s;
                result.z = (matrix.m32 + matrix.m23) * s2;
            }
            else
            {
                T s      = std::sqrt(1 + matrix.m33 - matrix.m11 - matrix.m22);
                T s2     = T(0.5) / s;
                result.w = (matrix.m12 - matrix.m21) * s2;
                result.x = (matrix.m31 + matrix.m13) * s2;
                result.y = (matrix.m32 + matrix.m23) * s2;
                result.z = T(0.5) * s;
            }
        }

        return result;
    }

    /// Creates a new quaternion with a specified yaw, pitch, and roll.
    /// \param yaw Yaw around the y-axis, in radians.
    /// \param pitch Pitch around the x-axis, in radians.
    /// \param roll Roll around the z-axis, in radians.
    /// \returns a new Quaternion expressing the specified yaw, pitch, and roll angles.
    template <typename T = float>
    constexpr basic_quaternion<T> create_from_yaw_pitch_roll(const basic_radians<T>& yaw
                                                           , const basic_radians<T>& pitch
                                                           , const basic_radians<T>& roll) noexcept
    {
        // http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q60
        // VECTOR3 vx = { 1, 0, 0 }, vy = { 0, 1, 0 }, vz = { 0, 0, 1 };
        // QUATERNION qx, qy, qz, qt;
        // quaternion_from_axisangle( qx, &vx, rx );
        // quaternion_from_axisangle( qy, &vy, ry );
        // quaternion_from_axisangle( qz, &vz, rz );
        // quaternion_multiply( &qt, &qx, &qy );
        // quaternion_multiply( &q,  &qt, &qz );

        auto qy = create_from_axis_angle(basic_vector3<T>::unit_y(), yaw);
        auto qx = create_from_axis_angle(basic_vector3<T>::unit_x(), pitch);
        auto qz = create_from_axis_angle(basic_vector3<T>::unit_z(), roll);

        return (qy * qx) * qz; // yaw * pitch * roll
    }

    /// Calculates the dot product oof two quaternions.
    /// \param left the first quaternion.
    /// \param right the second quaternion.
    /// \returns Dot product of the quaternions.
    template <typename T = float>
    constexpr T dot(const basic_quaternion<T>& left, const basic_quaternion<T>& right) noexcept
    {
        return (left.x * right.x) + (left.y * right.y) + (left.z * right.z) + (left.w * right.w);
    }

    /// Calculates the inverse of the specified quaternion.
    /// \param q the quaternion of which to return the inverse.
    /// \returns the inverse of the quaternion.
    template <typename T = float>
    constexpr basic_quaternion<T> inverse(const basic_quaternion<T>& q) noexcept
    {
        // The multiplicative inverse of a quaternion q is constructed as
        // q^-1 = q* / N(q)
        //
        // Where:
        //  q* is the quaternion Conjugate
        //  N(q) is the quaternion norm
        return conjugate(q) / length_squared(q);
    }

    /// Flips the sign of each component of the quaternion.
    /// \param q source quaterion.
    /// \returns the negated quaternion.
    template <typename T = float>
    constexpr basic_quaternion<T> negate(const basic_quaternion<T>& q) noexcept
    {
        return -q;
    }

    /// Normalizes the specified Quaternion. A normalized Quaternion maintains its direction but its magnitude becomes 1.
    /// The resulting Quaternion is often called a unit vector.
    /// \param q the quaternion to normalize.
    /// \returns A Quaternion is normalized by dividing the Quaternion by its magnitude.
    template <typename T = float>
    constexpr basic_quaternion<T> normalize(const basic_quaternion<T>& q) noexcept
    {
        return q / length(q);
    }

    /// Calculates the linear interpolation between two quaternions.
    /// \param quaternion1 first quaternion
    /// \param quaternion2 second quaternion
    /// \param amount Value indicating how far to interpolate between the quaternions.
    /// \returns the result of the interpolation.
    template <typename T, typename S, typename = typename std::enable_if_t<std::is_arithmetic_v<S>>>
    constexpr basic_quaternion<T> lerp(const basic_quaternion<T>& quaternion1
                                     , const basic_quaternion<T>& quaternion2
                                     , S                          amount) noexcept
    {
        auto amount1 = T(1) - amount;
        auto amount2 = amount;

        if (dot(quaternion1, quaternion2) < 0)
        {
            amount2 = -amount2;
        }

        return normalize(quaternion1 * amount1 + quaternion2 * amount2);
    }

    /// Calculates the spherical interpolation between two quaternions.
    /// \param quaternion1 first quaternion
    /// \param quaternion2 second quaternion
    /// \param amount Value indicating how far to interpolate between the quaternions.
    /// \returns the result of the interpolation.
    template <typename T, typename S, typename = typename std::enable_if_t<std::is_arithmetic_v<S>>>
    constexpr basic_quaternion<T> slerp(const basic_quaternion<T>& quaternion1
                                      , const basic_quaternion<T>& quaternion2
                                      , S                          amount) noexcept
    {
        bool flip     = false;
        auto cosTheta = dot(quaternion1, quaternion2);
        auto w1       = T(0);
        auto w2       = T(0);

        if (cosTheta < T(0))
        {
            // We need to flip a quaternion for shortest path interpolation
            cosTheta = -cosTheta;
            flip     = true;
        }

        auto theta    = std::acos(cosTheta);
        auto sinTheta = std::sin(theta);

        if (sinTheta > T(0.005))
        {
            w1 = std::sin((T(1) - amount) * theta) / sinTheta;
            w2 = std::sin(amount * theta) / sinTheta;
        }
        else
        {
            // They're almost the same quaternion
            w1 = T(1) - amount;
            w2 = amount;
        }

        if (flip)
        {
            w2 = -w2;
        }

        return (quaternion1 * w1 + quaternion2 * w2);
    }
}

#endif // SCENER_MATH_BASIC_QUATERNION_OPERATIONS_HPP
