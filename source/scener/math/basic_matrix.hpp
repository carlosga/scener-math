// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_MATRIX_HPP
#define SCENER_MATH_BASIC_MATRIX_HPP

#include <gsl/assert>

#include "scener/math/basic_vector.hpp"

namespace scener::math
{
    // -----------------------------------------------------------------------------------------------------------------
    // TRAITS

    template <typename T, std::size_t Dimension>
    struct basic_matrix_traits
    {
        using reference              = typename std::add_lvalue_reference_t<T>;
        using const_reference        = typename std::add_lvalue_reference_t<typename std::add_const_t<T>>;
        using value_type             = typename std::remove_reference_t<typename std::remove_cv_t<T>>;
        using pointer                = typename std::add_pointer_t<T>;
        using const_pointer          = typename std::add_pointer_t<typename std::add_const_t<T>>;
        using iterator               = typename std::array<T, Dimension>::iterator;
        using const_iterator         = typename std::array<T, Dimension>::const_iterator;
        using reverse_iterator       = typename std::array<T, Dimension>::reverse_iterator;
        using const_reverse_iterator = typename std::array<T, Dimension>::const_reverse_iterator;
        using size_type              = std::size_t;
    };

    // -----------------------------------------------------------------------------------------------------------------
    // TEMPLATES

    /// Represents a squared matrix.
    template <typename T, std::size_t Dimension, typename = typename std::enable_if_t<std::is_arithmetic_v<T>>>
    struct basic_matrix
    {
        using traits_type            = basic_matrix_traits<T, Dimension>;
        using reference              = typename traits_type::reference;
        using const_reference        = typename traits_type::const_reference;
        using value_type             = typename traits_type::value_type;
        using pointer                = typename traits_type::pointer;
        using const_pointer          = typename traits_type::const_pointer;
        using iterator               = typename traits_type::iterator;
        using const_iterator         = typename traits_type::const_iterator;
        using reverse_iterator       = typename traits_type::reverse_iterator;
        using const_reverse_iterator = typename traits_type::const_reverse_iterator;
        using size_type              = typename traits_type::size_type;

    public:
        /// Returns an instance of the identity matrix.
        /// \returns an instance of the identity matrix.
        constexpr static basic_matrix<T, Dimension> identity() noexcept
        {
            basic_matrix<T, Dimension> identity;

            for (std::size_t i = 0; i < Dimension; ++i)
            {
                identity[i][i] = T(1);
            }

            return identity;
        }

    public:
        /// Initializes a new instance of the basic_matrix struct.
        constexpr basic_matrix() noexcept
        {
        }

    public:
        /// Returns a pointer to the matrix data.
        constexpr pointer data() noexcept
        {
            return &items[0][0];
        }

        /// Returns a const pointer to the matrix data.
        constexpr const_pointer data() const noexcept
        {
            return &items[0][0];
        }

        /// Returns an iterator to the first element of the vector.
        /// \returns an iterator to the first element of the vector.
        constexpr iterator begin() noexcept
        {
            return raw.begin();
        }

        /// Returns a const iterator to the first element of the vector.
        /// \returns a const iterator to the first element of the vector.
        constexpr const_iterator begin() const noexcept
        {
            return raw.begin();
        }

        /// Returns an iterator to the element following the last element of the vector.
        /// \returns an iterator to the element following the last element of the vector.
        constexpr iterator end() noexcept
        {
            return raw.end();
        }

        /// Returns a const iterator to the element following the last element of the vector.
        /// \returns a const iterator to the element following the last element of the vector.
        constexpr const_iterator end() const noexcept
        {
            return raw.end();
        }

        /// Returns a reverse iterator to the first element of the reversed vector.
        /// \returns a reverse iterator to the first element of the reversed vector.
        constexpr reverse_iterator rbegin() noexcept
        {
            return raw.rbegin();
        }

        /// Returns a const reverse iterator to the first element of the reversed vector.
        /// \returns a const reverse iterator to the first element of the reversed vector.
        constexpr const_reverse_iterator rbegin() const noexcept
        {
            return raw.rbegin();
        }

        /// Returns a reverse iterator to the element following the last element of the reversed vector.
        /// \returns a reverse iterator to the element following the last element of the reversed vector.
        constexpr reverse_iterator rend() noexcept
        {
            return raw.rend();
        }

        /// Returns a const reverse iterator to the element following the last element of the reversed vector.
        /// \returns a const reverse iterator to the element following the last element of the reversed vector.
        constexpr const_reverse_iterator rend() const noexcept
        {
            return raw.rend();
        }

        /// Returns a reference to the first element in the vector.
        /// \returns a reference to the first element in the vector.
        constexpr reference front() noexcept
        {
            return raw.front();
        }

        /// Returns a const reference to the first element in the vector.
        /// \returns a const reference to the first element in the vector.
        constexpr const_reference front() const noexcept
        {
            return raw.front();
        }

        /// Returns reference to the last element in the vector.
        /// \returns reference to the last element in the vector.
        constexpr reference back() noexcept
        {
            return raw.back();
        }

        /// Returns const reference to the last element in the vector.
        /// \returns const reference to the last element in the vector.
        constexpr const_reference back() const noexcept
        {
            return raw.back();
        }

    public:
        /// Provides a reference to the row vector at the specified index in a matrix.
        /// \param index the index of the position of the row vector to be referenced.
        constexpr basic_vector<T, Dimension>& operator[](size_type index) noexcept
        {
            Expects(index < Dimension);
            return rows[index];
        }

        /// Provides a const reference to the row vector at the specified index in a matrix.
        /// \param index the index of the position of the row vector to be referenced.
        constexpr const basic_vector<T, Dimension>& operator[](size_type index) const noexcept
        {
            Expects(index < Dimension);
            return rows[index];
        }

    public:
        union
        {
            std::array<std::array<T, Dimension>, Dimension> items;
            struct
            {
                basic_vector<T, Dimension> rows[Dimension];
            };
            std::array<T, Dimension * Dimension> raw;
        };
    };

    // -----------------------------------------------------------------------------------------------------------------
    // MATRIX 4x4 SPECIALIZATION

    /// Represents a 4 x 4 matrix.
    template <typename T>
    struct basic_matrix<T, 4>
    {
        using traits_type            = basic_matrix_traits<T, 4>;
        using reference              = typename traits_type::reference;
        using const_reference        = typename traits_type::const_reference;
        using value_type             = typename traits_type::value_type;
        using pointer                = typename traits_type::pointer;
        using const_pointer          = typename traits_type::const_pointer;
        using iterator               = typename traits_type::iterator;
        using const_iterator         = typename traits_type::const_iterator;
        using reverse_iterator       = typename traits_type::reverse_iterator;
        using const_reverse_iterator = typename traits_type::const_reverse_iterator;
        using size_type              = typename traits_type::size_type;

    public:
        /// Returns an instance of the identity matrix.
        /// \returns an instance of the identity matrix.
        constexpr static basic_matrix<T, 4> identity() noexcept
        {
            return { 1, 0, 0, 0
                   , 0, 1, 0, 0
                   , 0, 0, 1, 0
                   , 0, 0, 0, 1 };
        }

    public:
        /// Initializes a new instance of the basic_matrix struct.
        constexpr basic_matrix() noexcept
            : basic_matrix { 0, 0, 0, 0
                           , 0, 0, 0, 0
                           , 0, 0, 0, 0
                           , 0, 0, 0, 0 }
        {
        }

        /// Initializes a new instance of the basic_matrix struct with the given initial values.
        /// \param m11_ value of the (1,1) field of the new matrix.
        /// \param m12_ value of the (1,2) field of the new matrix.
        /// \param m13_ value of the (1,3) field of the new matrix.
        /// \param m21_ value of the (2,1) field of the new matrix.
        /// \param m22_ value of the (2,2) field of the new matrix.
        /// \param m23_ value of the (2,3) field of the new matrix.
        /// \param m31_ value of the (3,1) field of the new matrix.
        /// \param m32_ value of the (3,2) field of the new matrix.
        /// \param m33_ value of the (3,3) field of the new matrix.
        constexpr basic_matrix(T m11_, T m12_, T m13_
                             , T m21_, T m22_, T m23_
                             , T m31_, T m32_, T m33_) noexcept
            : m11 { m11_ }, m12 { m12_ }, m13 { m13_ }, m14 { 0 }
            , m21 { m21_ }, m22 { m22_ }, m23 { m23_ }, m24 { 0 }
            , m31 { m31_ }, m32 { m32_ }, m33 { m33_ }, m34 { 0 }
            , m41 {   0  }, m42 {   0  }, m43 {  0   }, m44 { 1 }
        {
        }

        /// Initializes a new instance of the basic_matrix struct with the given initial values.
        /// \param m11_ value of the (1,1) field of the new matrix.
        /// \param m12_ value of the (1,2) field of the new matrix.
        /// \param m13_ value of the (1,3) field of the new matrix.
        /// \param m14_ value of the (1,4) field of the new matrix.
        /// \param m21_ value of the (2,1) field of the new matrix.
        /// \param m22_ value of the (2,2) field of the new matrix.
        /// \param m23_ value of the (2,3) field of the new matrix.
        /// \param m24_ value of the (2,4) field of the new matrix.
        /// \param m31_ value of the (3,1) field of the new matrix.
        /// \param m32_ value of the (3,2) field of the new matrix.
        /// \param m33_ value of the (3,3) field of the new matrix.
        /// \param m34_ value of the (3,4) field of the new matrix.
        /// \param m41_ value of the (4,1) field of the new matrix.
        /// \param m42_ value of the (4,2) field of the new matrix.
        /// \param m43_ value of the (4,3) field of the new matrix.
        /// \param m44_ value of the (4,4) field of the new matrix.
        constexpr basic_matrix(T m11_, T m12_, T m13_, T m14_
                             , T m21_, T m22_, T m23_, T m24_
                             , T m31_, T m32_, T m33_, T m34_
                             , T m41_, T m42_, T m43_, T m44_) noexcept
            : m11 { m11_ }, m12 { m12_ }, m13 { m13_ }, m14 { m14_ }
            , m21 { m21_ }, m22 { m22_ }, m23 { m23_ }, m24 { m24_ }
            , m31 { m31_ }, m32 { m32_ }, m33 { m33_ }, m34 { m34_ }
            , m41 { m41_ }, m42 { m42_ }, m43 { m43_ }, m44 { m44_ }
        {
        }

    public:
        /// Returns a pointer to the matrix data.
        constexpr pointer data() noexcept
        {
            return &items[0][0];
        }

        /// Returns a const pointer to the matrix data.
        constexpr const_pointer data() const noexcept
        {
            return &items[0][0];
        }

        /// Returns an iterator to the first element of the vector.
        /// \returns an iterator to the first element of the vector.
        constexpr iterator begin() noexcept
        {
            return raw.begin();
        }

        /// Returns a const iterator to the first element of the vector.
        /// \returns a const iterator to the first element of the vector.
        constexpr const_iterator begin() const noexcept
        {
            return raw.begin();
        }

        /// Returns an iterator to the element following the last element of the vector.
        /// \returns an iterator to the element following the last element of the vector.
        constexpr iterator end() noexcept
        {
            return raw.end();
        }

        /// Returns a const iterator to the element following the last element of the vector.
        /// \returns a const iterator to the element following the last element of the vector.
        constexpr const_iterator end() const noexcept
        {
            return raw.end();
        }

        /// Returns a reverse iterator to the first element of the reversed vector.
        /// \returns a reverse iterator to the first element of the reversed vector.
        constexpr reverse_iterator rbegin() noexcept
        {
            return raw.rbegin();
        }

        /// Returns a const reverse iterator to the first element of the reversed vector.
        /// \returns a const reverse iterator to the first element of the reversed vector.
        constexpr const_reverse_iterator rbegin() const noexcept
        {
            return raw.rbegin();
        }

        /// Returns a reverse iterator to the element following the last element of the reversed vector.
        /// \returns a reverse iterator to the element following the last element of the reversed vector.
        constexpr reverse_iterator rend() noexcept
        {
            return raw.rend();
        }

        /// Returns a const reverse iterator to the element following the last element of the reversed vector.
        /// \returns a const reverse iterator to the element following the last element of the reversed vector.
        constexpr const_reverse_iterator rend() const noexcept
        {
            return raw.rend();
        }

        /// Returns a reference to the first element in the vector.
        /// \returns a reference to the first element in the vector.
        constexpr reference front() noexcept
        {
            return raw.front();
        }

        /// Returns a const reference to the first element in the vector.
        /// \returns a const reference to the first element in the vector.
        constexpr const_reference front() const noexcept
        {
            return raw.front();
        }

        /// Returns reference to the last element in the vector.
        /// \returns reference to the last element in the vector.
        constexpr reference back() noexcept
        {
            return raw.back();
        }

        /// Returns const reference to the last element in the vector.
        /// \returns const reference to the last element in the vector.
        constexpr const_reference back() const noexcept
        {
            return raw.back();
        }

    public:
        /// Provides a reference to the row vector at the specified index in a matrix.
        /// \param index the index of the position of the row vector to be referenced.
        constexpr basic_vector<T, 4>& operator[](size_type index) noexcept
        {
            Expects(index < 4);
            return rows[index];
        }

        /// Provides a const reference to the row vector at the specified index in a matrix.
        /// \param index the index of the position of the row vector to be referenced.
        constexpr const basic_vector<T, 4>& operator[](size_type index) const noexcept
        {
            Expects(index < 4);
            return rows[index];
        }

        template <typename K, size_type Dimension2>
        constexpr operator basic_matrix<K, Dimension2>() const noexcept
        {
            static_assert(Dimension2 <= 4, "Invalid dimensions on matrix conversion");

            // Algorithm: http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q24
            basic_matrix<K, Dimension2> result;

            for (std::uint32_t row = 0; row < Dimension2; ++row)
            {
                for (std::uint32_t col = 0; col < Dimension2; ++col)
                {
                    result[row][col] = K(items[row][col]);
                }
            }

            return result;
        }

    public:
        union
        {
            std::array<std::array<T, 4>, 4> items;
            struct
            {
                T m11;
                T m12;
                T m13;
                T m14;
                T m21;
                T m22;
                T m23;
                T m24;
                T m31;
                T m32;
                T m33;
                T m34;
                T m41;
                T m42;
                T m43;
                T m44;
            };
            struct
            {
                basic_vector<T, 4> rows[4];
            };
            std::array<T, 16> raw;
        };
    };

    // -----------------------------------------------------------------------------------------------------------------
    // TYPEDEF'S & ALIASES

    template <typename T>
    using basic_matrix2 = basic_matrix<T, 2>;

    template <typename T>
    using basic_matrix3 = basic_matrix<T, 3>;

    template <typename T>
    using basic_matrix4 = basic_matrix<T, 4>;

    using matrix2 = basic_matrix2<float>;
    using matrix3 = basic_matrix3<float>;
    using matrix4 = basic_matrix4<float>;

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS

    template <typename T, std::size_t Dimension>
    constexpr bool operator==(const basic_matrix<T, Dimension>& lhs, const basic_matrix<T, Dimension>& rhs) noexcept
    {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), [](T a, T b) { return equal(a, b); });
    }

    template <typename T, std::size_t Dimension>
    constexpr bool operator!=(const basic_matrix<T, Dimension>& lhs, const basic_matrix<T, Dimension>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <typename T, std::size_t Dimension>
    constexpr basic_matrix<T, Dimension>& operator*=(basic_matrix<T, Dimension>&       lhs
                                                   , const basic_matrix<T, Dimension>& rhs) noexcept
    {
        auto matrix = lhs;

        for (std::size_t r = 0; r < Dimension; ++r)
        {
            for (std::size_t c = 0; c < Dimension; ++c)
            {
                lhs[r][c] = T(0);

                for (std::size_t m = 0; m < Dimension; ++m)
                {
                    lhs[r][c] += (matrix[r][m] * rhs[m][c]);
                }
            }
        }

        return lhs;
    }

    template <typename T, std::size_t Dimension>
    constexpr basic_matrix<T, Dimension> operator*(const basic_matrix<T, Dimension>& lhs
                                                 , const basic_matrix<T, Dimension>& rhs) noexcept
    {
        auto result = lhs;

        result *= rhs;

        return result;
    }

    template <typename T, std::size_t Dimension>
    constexpr basic_matrix<T, Dimension>& operator+=(basic_matrix<T, Dimension>&       lhs
                                                   , const basic_matrix<T, Dimension>& rhs) noexcept
    {
        std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::plus<T>());

        return lhs;
    }

    template <typename T, std::size_t Dimension>
    constexpr basic_matrix<T, Dimension> operator+(const basic_matrix<T, Dimension>& lhs
                                                 , const basic_matrix<T, Dimension>& rhs) noexcept
    {
        auto result = lhs;

        result += rhs;

        return result;
    }

    template <typename T, std::size_t Dimension>
    constexpr basic_matrix<T, Dimension>& operator-=(basic_matrix<T, Dimension>&       lhs
                                                   , const basic_matrix<T, Dimension>& rhs) noexcept
    {
        std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::minus<T>());

        return lhs;
    }

    template <typename T, std::size_t Dimension>
    constexpr basic_matrix<T, Dimension> operator-(const basic_matrix<T, Dimension>& lhs
                                                 , const basic_matrix<T, Dimension>& rhs) noexcept
    {
        auto result = lhs;

        result -= rhs;

        return result;
    }

    template <typename T, std::size_t Dimension>
    constexpr basic_matrix<T, Dimension> operator-(const basic_matrix<T, Dimension>& matrix) noexcept
    {
        basic_matrix<T, Dimension> result;

        std::transform(matrix.begin(), matrix.end(), result.begin(), std::negate<T>());

        return result;
    }

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS (WITH SCALARS)

    template <typename T, std::size_t Dimension>
    constexpr basic_matrix<T, Dimension>& operator*=(basic_matrix<T, Dimension>& lhs, const T& rhs) noexcept
    {
        std::transform(lhs.begin(), lhs.end(), lhs.begin(), std::bind(std::multiplies<T>(), std::placeholders::_1, rhs));

        return lhs;
    }

    template <typename T, std::size_t Dimension>
    constexpr basic_matrix<T, Dimension> operator*(const basic_matrix<T, Dimension>& lhs, const T& value) noexcept
    {
        auto result = lhs;

        result *= value;

        return result;
    }

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS (MATRIX 4x4)

    template <typename T>
    constexpr bool operator==(const basic_matrix4<T>& lhs, const basic_matrix4<T>& rhs) noexcept
    {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), [](T a, T b) { return equal(a, b); });
    }

    template <typename T>
    constexpr basic_matrix4<T>& operator*=(basic_matrix4<T>& lhs, const basic_matrix4<T>& rhs) noexcept
    {
        auto lhsc = lhs;

        lhs.m11 = ((lhsc.m11 * rhs.m11) + (lhsc.m12 * rhs.m21) + (lhsc.m13 * rhs.m31) + (lhsc.m14 * rhs.m41));
        lhs.m12 = ((lhsc.m11 * rhs.m12) + (lhsc.m12 * rhs.m22) + (lhsc.m13 * rhs.m32) + (lhsc.m14 * rhs.m42));
        lhs.m13 = ((lhsc.m11 * rhs.m13) + (lhsc.m12 * rhs.m23) + (lhsc.m13 * rhs.m33) + (lhsc.m14 * rhs.m43));
        lhs.m14 = ((lhsc.m11 * rhs.m14) + (lhsc.m12 * rhs.m24) + (lhsc.m13 * rhs.m34) + (lhsc.m14 * rhs.m44));

        lhs.m21 = ((lhsc.m21 * rhs.m11) + (lhsc.m22 * rhs.m21) + (lhsc.m23 * rhs.m31) + (lhsc.m24 * rhs.m41));
        lhs.m22 = ((lhsc.m21 * rhs.m12) + (lhsc.m22 * rhs.m22) + (lhsc.m23 * rhs.m32) + (lhsc.m24 * rhs.m42));
        lhs.m23 = ((lhsc.m21 * rhs.m13) + (lhsc.m22 * rhs.m23) + (lhsc.m23 * rhs.m33) + (lhsc.m24 * rhs.m43));
        lhs.m24 = ((lhsc.m21 * rhs.m14) + (lhsc.m22 * rhs.m24) + (lhsc.m23 * rhs.m34) + (lhsc.m24 * rhs.m44));

        lhs.m31 = ((lhsc.m31 * rhs.m11) + (lhsc.m32 * rhs.m21) + (lhsc.m33 * rhs.m31) + (lhsc.m34 * rhs.m41));
        lhs.m32 = ((lhsc.m31 * rhs.m12) + (lhsc.m32 * rhs.m22) + (lhsc.m33 * rhs.m32) + (lhsc.m34 * rhs.m42));
        lhs.m33 = ((lhsc.m31 * rhs.m13) + (lhsc.m32 * rhs.m23) + (lhsc.m33 * rhs.m33) + (lhsc.m34 * rhs.m43));
        lhs.m34 = ((lhsc.m31 * rhs.m14) + (lhsc.m32 * rhs.m24) + (lhsc.m33 * rhs.m34) + (lhsc.m34 * rhs.m44));

        lhs.m41 = ((lhsc.m41 * rhs.m11) + (lhsc.m42 * rhs.m21) + (lhsc.m43 * rhs.m31) + (lhsc.m44 * rhs.m41));
        lhs.m42 = ((lhsc.m41 * rhs.m12) + (lhsc.m42 * rhs.m22) + (lhsc.m43 * rhs.m32) + (lhsc.m44 * rhs.m42));
        lhs.m43 = ((lhsc.m41 * rhs.m13) + (lhsc.m42 * rhs.m23) + (lhsc.m43 * rhs.m33) + (lhsc.m44 * rhs.m43));
        lhs.m44 = ((lhsc.m41 * rhs.m14) + (lhsc.m42 * rhs.m24) + (lhsc.m43 * rhs.m34) + (lhsc.m44 * rhs.m44));

        return lhs;
    }

    template <typename T>
    constexpr basic_matrix4<T> operator*=(basic_matrix4<T>& lhs, const T& rhs) noexcept
    {
        std::transform(lhs.begin(), lhs.end(), lhs.begin(), std::bind(std::multiplies<T>(), std::placeholders::_1, rhs));

        return lhs;
    }

    template <typename T>
    constexpr basic_matrix4<T>& operator+=(basic_matrix4<T>& lhs, const basic_matrix4<T>& rhs) noexcept
    {
        std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::plus<T>());

        return lhs;
    }

    template <typename T>
    constexpr basic_matrix4<T>& operator-=(basic_matrix4<T>& lhs, const basic_matrix4<T>& rhs) noexcept
    {
        std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::minus<T>());

        return lhs;
    }

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS (VECTOR | MATRIX 4x4)

    template <typename T = float>
    constexpr basic_vector3<T> operator*(const basic_vector3<T>& vector, const basic_matrix4<T>& matrix) noexcept
    {
        // http://softimage.wiki.softimage.com/xsidocs/iceref_Multiply_Vector_by_Matrix.htm

        T vx = (vector.x * matrix.m11)
             + (vector.y * matrix.m21)
             + (vector.z * matrix.m31)
             +             matrix.m41;

        T vy = (vector.x * matrix.m12)
             + (vector.y * matrix.m22)
             + (vector.z * matrix.m32)
             +             matrix.m42;

        T vz = (vector.x * matrix.m13)
             + (vector.y * matrix.m23)
             + (vector.z * matrix.m33)
             +             matrix.m43;

        T vw = (vector.x * matrix.m14)
             + (vector.y * matrix.m24)
             + (vector.z * matrix.m34)
             +             matrix.m44;

        return { vx / vw, vy / vw, vz / vw };
    }

    template <typename T = float>
    constexpr basic_vector4<T> operator*(const basic_vector4<T>& vector, const basic_matrix4<T>& matrix) noexcept
    {
        T vx = (vector.x * matrix.m11)
             + (vector.y * matrix.m21)
             + (vector.z * matrix.m31)
             + (vector.w * matrix.m41);

        T vy = (vector.x * matrix.m12)
             + (vector.y * matrix.m22)
             + (vector.z * matrix.m32)
             + (vector.w * matrix.m42);

        T vz = (vector.x * matrix.m13)
             + (vector.y * matrix.m23)
             + (vector.z * matrix.m33)
             + (vector.w * matrix.m43);

        T vw = (vector.x * matrix.m14)
             + (vector.y * matrix.m24)
             + (vector.z * matrix.m34)
             + (vector.w * matrix.m44);

        return { vx, vy, vz, vw };
    }
}

#endif // SCENER_MATH_BASIC_MATRIX_HPP
