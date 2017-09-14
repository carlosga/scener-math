// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_QUATERNION_HPP
#define SCENER_MATH_BASIC_QUATERNION_HPP

#include "scener/math/basic_vector.hpp"

namespace scener::math
{
    // -----------------------------------------------------------------------------------------------------------------
    // TEMPLATES

    /// Class that represents a rotation in three dimensions.
    template <typename T, typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
    struct basic_quaternion
    {
        using reference              = typename std::add_lvalue_reference_t<T>;
        using const_reference        = typename std::add_lvalue_reference_t<typename std::add_const_t<T>>;
        using value_type             = typename std::remove_reference_t<typename std::remove_cv_t<T>>;
        using pointer                = typename std::add_pointer_t<T>;
        using const_pointer          = typename std::add_pointer_t<typename std::add_const_t<T>>;
        using iterator               = typename std::array<T, 4>::iterator;
        using const_iterator         = typename std::array<T, 4>::const_iterator;
        using reverse_iterator       = typename std::array<T, 4>::reverse_iterator;
        using const_reverse_iterator = typename std::array<T, 4>::const_reverse_iterator;
        using size_type              = std::size_t;

    public:
        /// Gets the identity quaternion.
        constexpr static basic_quaternion<T> identity() noexcept { return { 0, 0, 0, 1 }; }

    public:
        /// Initializes a new instance of the Quaternion class.
        constexpr basic_quaternion() noexcept
            : basic_quaternion { 0, 0, 0, 0 }
        {
        }

        /// Initializes a new instance of the Quaternion class.
        /// \param vector a vector containing the values to initialize x, y, and z components with.
        /// \param w value for the w-component of the vector.
        constexpr basic_quaternion(const basic_vector<T, 3>& vector, T w) noexcept
            : basic_quaternion { vector.x, vector.y, vector.z, w }
        {
        }

        /// Initializes a new instance of the Quaternion class.
        /// \param vector a vector containing the values to initialize x, y, z and w components with.
        constexpr explicit basic_quaternion(const basic_vector<T, 4>& vector) noexcept
            : basic_quaternion { vector.x, vector.y, vector.z, vector.w }
        {
        }

        /// Initializes a new instance of the Quaternion class.
        /// \param x The X value of the new Quaternion structure.
        /// \param y The Y value of the new Quaternion structure.
        /// \param z The Z value of the new Quaternion structure.
        /// \param w The W value of the new Quaternion structure.
        constexpr basic_quaternion(T x, T y, T z, T w) noexcept
            : x { x }, y { y }, z { z }, w { w }
        {
        }

    public:
        /// Returns a pointer to the underlying array serving as element storage.
        /// \returns a pointer to the underlying array serving as element storage.
        constexpr pointer data() noexcept
        {
            return items.data();
        }

        /// Returns a const pointer to the underlying array serving as element storage.
        /// \returns a const pointer to the underlying array serving as element storage.
        constexpr const_pointer data() const noexcept
        {
            return items.data();
        }

    public:
        constexpr reference operator[](size_type index) noexcept
        {
            return items[index];
        }

        constexpr const_reference operator[](size_type index) const noexcept
        {
            return items[index];
        }

    public:
        union
        {
            std::array<T, 4> items;
            struct
            {
                T x;
                T y;
                T z;
                T w;
            };
        };
    };

    // -----------------------------------------------------------------------------------------------------------------
    // TYPEDEF'S & ALIASES

    using quaternion = basic_quaternion<float>;

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS

    template <typename T>
    constexpr bool operator==(const basic_quaternion<T>& lhs, const basic_quaternion<T>& rhs) noexcept
    {
        return (equal(lhs.x, rhs.x)
             && equal(lhs.y, rhs.y)
             && equal(lhs.z, rhs.z)
             && equal(lhs.w, rhs.w));
    }

    template <typename T>
    constexpr bool operator!=(const basic_quaternion<T>& lhs, const basic_quaternion<T>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <typename T>
    constexpr basic_quaternion<T>& operator*=(basic_quaternion<T>& q0, const basic_quaternion<T>& q1) noexcept
    {
        // Multiplication of quaternions is defined by
        // q0q1 = (w0 + x0i + y0j + z0k)(w1 + x1i + y1j + z1k) = (w0w1 - x0x1 - y0y1 - z0z1)
        //                                                     + (w0x1 + x0w1 + y0z1 - z0y1)i
        //                                                     + (w0y1 - x0z1 + y0w1 + z0x1)j
        //                                                     + (w0z1 + x0y1 - y0x1 + z0w1)k

        auto w = (q0.w * q1.w - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z);
        auto x = (q0.w * q1.x + q0.x * q1.w + q0.y * q1.z - q0.z * q1.y);
        auto y = (q0.w * q1.y - q0.x * q1.z + q0.y * q1.w + q0.z * q1.x);
        auto z = (q0.w * q1.z + q0.x * q1.y - q0.y * q1.x + q0.z * q1.w);

        q0.w = w;
        q0.x = x;
        q0.y = y;
        q0.z = z;

        return q0;
    }

    template <typename T>
    constexpr basic_quaternion<T> operator*(const basic_quaternion<T>& lhs, const basic_quaternion<T>& rhs) noexcept
    {
        auto result = lhs;

        result *= rhs;

        return result;
    }

    template <typename T>
    constexpr basic_quaternion<T>& operator/=(basic_quaternion<T>& q, const basic_quaternion<T>& r) noexcept
    {
        // http://es.mathworks.com/help/aeroblks/quaterniondivision.html
        auto lengthSquared = (r.x * r.x) + (r.y * r.y) + (r.z * r.z) + (r.w * r.w);

        auto qw = (r.x * q.w - r.y * q.z + r.z * q.y - r.w * q.x) / lengthSquared;
        auto qx = (r.x * q.x + r.y * q.y + r.z * q.z + r.w * q.w) / lengthSquared;
        auto qy = (r.x * q.y - r.y * q.x - r.z * q.w + r.w * q.z) / lengthSquared;
        auto qz = (r.x * q.z + r.y * q.w - r.z * q.x - r.w * q.y) / lengthSquared;

        q.x = -qw;
        q.y = -qz;
        q.z = -qy;
        q.w =  qx;

        return q;
    }

    template <typename T>
    constexpr basic_quaternion<T> operator/(const basic_quaternion<T>& lhs, const basic_quaternion<T>& rhs) noexcept
    {
        auto result = lhs;

        result /= rhs;

        return result;
    }

    template <typename T>
    constexpr basic_quaternion<T>& operator-=(basic_quaternion<T>& lhs, const basic_quaternion<T>& rhs) noexcept
    {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        lhs.z -= rhs.z;
        lhs.w -= rhs.w;

        return lhs;
    }

    template <typename T>
    constexpr basic_quaternion<T> operator-(const basic_quaternion<T>& lhs, const basic_quaternion<T>& rhs) noexcept
    {
        auto result = lhs;

        result -= rhs;

        return result;
    }

    template <typename T>
    constexpr basic_quaternion<T>& operator+=(basic_quaternion<T>& lhs, const basic_quaternion<T>& rhs) noexcept
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        lhs.z += rhs.z;
        lhs.w += rhs.w;

        return lhs;
    }

    template <typename T>
    constexpr basic_quaternion<T> operator+(const basic_quaternion<T>& lhs, const basic_quaternion<T>& rhs) noexcept
    {
        auto result = lhs;

        result += rhs;

        return result;
    }

    template <typename T>
    constexpr basic_quaternion<T> operator-(const basic_quaternion<T>& q) noexcept
    {
        return { -q.x, -q.y, -q.z, -q.w };
    }

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS (WITH SCALARS)

    template <typename T, typename S, typename = typename std::enable_if_t<std::is_arithmetic_v<S>>>
    constexpr basic_quaternion<T>& operator*=(basic_quaternion<T>& lhs, const S& rhs) noexcept
    {
        lhs.x *= rhs;
        lhs.y *= rhs;
        lhs.z *= rhs;
        lhs.w *= rhs;

        return lhs;
    }

    template <typename T, typename S, typename = typename std::enable_if_t<std::is_arithmetic_v<S>>>
    constexpr basic_quaternion<T> operator*(const basic_quaternion<T>& lhs, const S& rhs) noexcept
    {
        auto result = lhs;

        result *= rhs;

        return result;
    }

    template <typename T, typename S, typename = typename std::enable_if_t<std::is_arithmetic_v<S>>>
    constexpr basic_quaternion<T>& operator/=(basic_quaternion<T>& lhs, const S& rhs) noexcept
    {
        lhs.x /= rhs;
        lhs.y /= rhs;
        lhs.z /= rhs;
        lhs.w /= rhs;

        return lhs;
    }

    template <typename T, typename S, typename = typename std::enable_if_t<std::is_arithmetic_v<S>>>
    constexpr basic_quaternion<T> operator/(const basic_quaternion<T>& lhs, const S& rhs) noexcept
    {
        auto result = lhs;

        result /= rhs;

        return result;
    }
}

#endif // SCENER_MATH_BASIC_QUATERNION_HPP
