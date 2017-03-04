// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_MATH_HPP
#define SCENER_MATH_BASIC_MATH_HPP

#include <cmath>
#include <limits>
#include <type_traits>

namespace scener::math 
{
    /// Represents the mathematical constant e.
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr T e = T(M_E);

    /// Represents the log base ten of e.
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr T log_10E = T(M_LOG10E);

    /// Represents the log base two of e.
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr T log_2E = T(M_LOG2E);

    /// Represents the value of PI
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr T pi = T(M_PI);

    /// Represents the value of PI divided by 2
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr T pi_over_2 = T(M_PI_2);

    /// Represents the value of PI divided by 4
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr T pi_over_4 = T(M_PI_4);

    /// Represents the value of pi times two.
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr T two_pi = T(M_2_PI);

    /// Represents positive infinity.
    template <typename T = float, typename = std::enable_if_t<std::numeric_limits<T>::has_infinity>>
    constexpr T positive_infinity = std::numeric_limits<T>::infinity();

    /// Represents negative infinity.
    template <typename T = float, typename = std::enable_if_t<std::numeric_limits<T>::has_infinity>>
    constexpr T negative_infinity = -positive_infinity<T>;

    /// Represents not a number (NaN).
    template <typename T = float, typename = std::enable_if_t<std::numeric_limits<T>::has_quiet_NaN>>
    constexpr T nan = std::numeric_limits<float>::quiet_NaN();

    /// Represents the smallest positive value that is greater than zero.
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr T epsilon = std::numeric_limits<T>::epsilon();

    /// Represents the smallest possible value of the underliying template type.
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr T min_value = std::numeric_limits<T>::lowest();

    /// Represents the largest possible value of the underliying template type.
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr T max_value = std::numeric_limits<T>::max();

    /// Equality comparision between two values.
    /// \param value1 the first value.
    /// \param value2 the second value.
    /// \returns true if both values are equal; false otherwise.
    template <typename T, typename S, typename = std::enable_if_t<std::is_arithmetic_v<T> && std::is_arithmetic_v<S>>>
    constexpr bool equal(T value1, S value2) noexcept
    {
        typedef typename std::common_type<T, S>::type common_t;

        // TODO: Take a look at
        //
        // http://floating-point-gui.de/errors/comparison/
        // https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
        //
        // to take care for edge cases

        return (common_t(value1) == common_t(value2));
    }

    /// Returns a value indicating whether the specified number evaluates to positive infinity.
    /// \param f a single-precision floating-point number.
    /// \returns true if f evaluates to negative_infinity; otherwise, false.
    template <typename T = float, typename = std::enable_if_t<std::numeric_limits<T>::has_infinity>>
    constexpr bool is_negative_infinity(T f) noexcept
    {
        return equal(f, negative_infinity<T>);
    }

    /// Returns a value indicating whether the specified number evaluates to negative or positive infinity.
    /// \param f a single-precision floating-point number.
    /// @returns true if f evaluates to negative_infinity; otherwise, false.
    template <typename T = float, typename = std::enable_if_t<std::numeric_limits<T>::has_infinity>>
    constexpr bool is_positive_infinity(T f) noexcept
    {
        return (equal(f, positive_infinity<T>));
    }

    /// Returns a value indicating whether the specified number evaluates to negative or positive infinity.
    /// \param f a single-precision floating-point number.
    /// \returns true if f evaluates to negative_infinity or negative_infinity; otherwise, false.
    template <typename T = float, typename = std::enable_if_t<std::numeric_limits<T>::has_infinity>>
    constexpr bool is_infinity(T f) noexcept
    {
        return is_positive_infinity<T>(f) || is_negative_infinity<T>(f);
    }

    /// Returns a value that indicates whether the specified value is not a number (NaN).
    /// \param f a single-precision floating-point number.
    /// \returns true if f evaluates to not a number (NaN); otherwise, false.
    template <typename T = float, typename = std::enable_if_t<std::numeric_limits<T>::has_quiet_NaN>>
    inline bool is_nan(T f) noexcept
    {
        return std::isnan(f);
    }

    /// Returns the remainder resulting from the division of a specified number by another specified number.
    /// \param x a dividend.
    /// \param y a divisor.
    /// \returns a number equal to x - (y Q), where Q is the quotient of x / y rounded to the nearest integer
    ///          (if x / y falls halfway between two integers, the even integer is returned).
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline T ieee_remainder(T x, T y) noexcept
    {
        // Reference: https://msdn.microsoft.com/es-es/library/system.math.ieeeremainder%28v=vs.110%29.aspx
        // ieee_remainder = dividend - (divisor * Math.round(dividend / divisor))
        return x - (y * std::round(x / y));
    }

    /// Returns the Cartesian coordinate for one axis of a point that is defined by a given triangle and
    /// two normalized barycentric (areal) coordinates.
    /// \param value1 the coordinate on one axis of vertex 1 of the defining triangle.
    /// \param value2 the coordinate on the same axis of vertex 2 of the defining triangle.
    /// \param value3 the coordinate on the same axis of vertex 3 of the defining triangle.
    /// \param amount1 the normalized barycentric (areal) coordinate b2, equal to the weighting factor for vertex 2,
    ///                the coordinate of which is specified in value2.
    /// \param amount2 the normalized barycentric (areal) coordinate b3, equal to the weighting factor for vertex 3,
    ///                the coordinate of which is specified in value3.
    /// \returns the Cartesian coordinate.
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr T barycentric(T value1, T value2, T value3, T amount1, T amount2) noexcept
    {
        // Reference: http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.Math.barycentric(v=xnagamestudio.40).aspx
        //  Pa = ((1 - b2 - b3) * V1a) + (b2 * V2a) + (b3 * V3a);
        //
        // NOTE: DirectX docs have a different formula. http://msdn.microsoft.com/en-us/library/windows/desktop/bb324330(v=vs.85).aspx
        //  v1 + f(v2 - v1) + g(v3 - v1)

        return ((1 - amount1 - amount2) * value1) + (amount1 * value2) + (amount2 * value3);
    }

    /// Performs a Catmull-Rom interpolation using the specified positions.
    /// \param value1 the first position in the interpolation.
    /// \param value2 the second position in the interpolation.
    /// \param value3 the third position in the interpolation.
    /// \param value4 the fourth position in the interpolation.
    /// \param amount weighting factor.
    /// \returns the interpolation result.
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr T catmull_rom(T value1, T value2, T value3, T value4, T amount) noexcept
    {
        // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/bb324331(v=vs.85).aspx
        // Q(s) = [(-s3 + 2s2 - s)p1 + (3s3 - 5s2 + 2)p2 + (-3s3 + 4s2 + s)p3 + (s3 - s2)p4] / 2;

        const T s3 = amount * amount * amount;
        const T s2 = amount * amount;
        const T s  = amount;

        return ((-s3      + 2      * s2 - s) * value1
              + (  3      * s3 - 5 * s2 + 2) * value2
              + ( -3      * s3 + 4 * s2 + s) * value3
              + (s3 - s2) * value4) / 2;
    }

    /// Restricts a value to be within a specified range.
    /// \param value the value to clamp.
    /// \param min_ the min value.
    /// \param max_ the max value.
    /// \returns the clamped value.
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr T clamp(T value, T min_, T max_) noexcept
    {
        const T maxValue = ((max_ < min_) ? min_ : max_);

        if (value < min_)
        {
            return min_;
        }
        else if (value > maxValue)
        {
            return maxValue;
        }

        return value;
    }

    /// Calculates a hermite spline interpolation.
    /// \param value1 source position 1.
    /// \param tangent1 source tangent 1.
    /// \param value2 source position 2.
    /// \param tangent2 source tangent 2.
    /// \param amount weighting factor.
    /// \returns the interpolation result.
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr T hermite(T value1, T tangent1, T value2, T tangent2, T amount) noexcept
    {
        // Reference: http://cubic.org/docs/hermite.htm
        // h1(s) =  2s^3 - 3s^2 + 1
        // h2(s) = -2s^3 + 3s^2
        // h3(s) =   s^3 - 2s^2 + s
        // h4(s) =   s^3 -  s^2
        //
        // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/bb324340(v=vs.85).aspx
        // Q(s) = (2s3 - 3s2 + 1)v1 + (-2s3 + 3s2)v2 + (s3 - 2s2 + s)t1 + (s3 - s2)t2.

        const T s3 = amount * amount * amount;
        const T s2 = amount * amount;

        return ( 2 * s3 - 3 * s2 + 1)      * value1
             + (-2 * s3 + 3 * s2)          * value2
             + (s3      - 2 * s2 + amount) * tangent1
             + (s3      - s2)              * tangent2;
    }

    /// Performs a linear interpolation between two values.
    /// \param value1 first values.
    /// \param value2 second values.
    /// \param amount value between 0 and 1 indicating the weight of value2.
    /// \returns the linear interpolation of the two values.
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr T lerp(T value1, T value2, T amount) noexcept
    {
        // Reference: http://msdn.microsoft.com/en-us/library/bb197812.aspx
        return (value1 + (value2 - value1) * amount);
    }

    /// Interpolates between two values using a cubic equation.
    /// \param value1 first value
    /// \param value2 second value
    /// \param amount weighting value.
    /// \returns the interpolation result.
    template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr T smooth_step(T value1, T value2, T amount) noexcept
    {
        // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorlerp(v=vs.85).aspx
        T t = clamp(amount, T(0), T(1));

        return lerp(value1, value2, t * t * (3 - 2 * t));
    }
}

#endif // SCENER_MATH_BASIC_MATH_HPP
