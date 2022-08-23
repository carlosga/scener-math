// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_VECTOR_OPERATIONS_HPP
#define SCENER_MATH_BASIC_VECTOR_OPERATIONS_HPP

#include <numeric>

#include "scener/math/algorithm.hpp"
#include "scener/math/basic_vector.hpp"
#include "scener/math/basic_angle.hpp"
#include "scener/math/functional.hpp"

namespace scener::math::vector
{
    /// Returns a vector whose elements are the absolute values of each of the specified vector's elements.
    /// \param value a vector.
    /// \returns the absolute value vector.
    template <typename T = float, std::size_t Dimension>
    constexpr basic_vector<T, Dimension> abs(const basic_vector<T, Dimension>& value) noexcept
    {
        basic_vector<T, Dimension> vector;

        std::transform(value.begin(), value.end(), vector.begin(), functional::abs<>());

        return vector;
    }

    /// Returns the cartesian coordinate for one axis of a point that is defined by a given triangle and
    /// two normalized barycentric (areal) coordinates.
    /// \param value1 the coordinate on one axis of vertex 1 of the defining triangle.
    /// \param value2 the coordinate on the same axis of vertex 2 of the defining triangle.
    /// \param value3 the coordinate on the same axis of vertex 3 of the defining triangle.
    /// \param amount1 the normalized barycentric (areal) coordinate b2, equal to the weighting factor for vertex 2,
    ///                the coordinate of which is specified in value2.
    /// \param amount2 the normalized barycentric (areal) coordinate b3, equal to the weighting factor for vertex 3,
    ///                the coordinate of which is specified in value3.
    /// \returns the cartesian coordinate.
    template <typename T = float, std::size_t Dimension, typename S, typename = typename std::enable_if_t<std::is_arithmetic_v<S>>>
    constexpr basic_vector<T, Dimension> barycentric(const basic_vector<T, Dimension>& value1
                                                   , const basic_vector<T, Dimension>& value2
                                                   , const basic_vector<T, Dimension>& value3
                                                   , S                                 amount1
                                                   , S                                 amount2) noexcept
    {
        basic_vector<T, Dimension> vector;

        algorithm::transform(value1.begin(), value1.end(), value2.begin(), value3.begin(), vector.begin()
            , [amount1, amount2](T a, T b, T c) -> T { return math::barycentric(a, b, c, amount1, amount2); });

        return vector;
    }

    /// Performs a Catmull-Rom interpolation using the specified positions.
    /// \param value1 the first position in the interpolation.
    /// \param value2 the second position in the interpolation.
    /// \param value3 the third position in the interpolation.
    /// \param value4 the fourth position in the interpolation.
    /// \param amount weighting factor.
    /// \returns the interpolation result.
    template <typename T = float, typename S, std::size_t Dimension, typename = typename std::enable_if_t<std::is_arithmetic_v<S>>>
    constexpr basic_vector<T, Dimension> catmull_rom(const basic_vector<T, Dimension>& value1
                                                   , const basic_vector<T, Dimension>& value2
                                                   , const basic_vector<T, Dimension>& value3
                                                   , const basic_vector<T, Dimension>& value4
                                                   , S                                 amount) noexcept
    {
        basic_vector<T, Dimension> vector;

        algorithm::transform(value1.begin(), value1.end(), value2.begin(), value3.begin(), value4.begin(), vector.begin()
            , [amount](T a, T b, T c, T d) -> T { return math::catmull_rom(a, b, c, d, amount); });

        return vector;
    }

    /// Restricts a value to be within a specified range.
    /// \param value1 the value to clamp.
    /// \param min the minimum value.
    /// \param max the maximum value.
    /// \returns the clamped value.
    template <typename T = float, std::size_t Dimension>
    constexpr basic_vector<T, Dimension> clamp(const basic_vector<T, Dimension>& value1
                                             , const basic_vector<T, Dimension>& min
                                             , const basic_vector<T, Dimension>& max) noexcept
    {
        basic_vector<T, Dimension> vector;

        algorithm::transform(value1.begin(), value1.end(), min.begin(), max.begin(), vector.begin(), functional::clamp<>());

        return vector;
    }

    /// Calculates the dot product of two vector structures.
    /// \param left the first Vector3 to evaluate.
    /// \param right the second Vector3 to evaluate.
    /// \returns the dot product of the given vectors.
    template <typename T = float, std::size_t Dimension>
    constexpr T dot(const basic_vector<T, Dimension>& left, const basic_vector<T, Dimension>& right) noexcept
    {
        // The definition of the scalar (dot) product is:
        // a · b = |a||b|cosθ
        //
        // The scalar product can also be written in terms of Cartesian components as:
        // a · b = x1x2 + y1y2 + z1z2

        auto vector = left * right;

        return std::accumulate(vector.begin(), vector.end(), T(0));
    }

    /// Calculates a hermite spline interpolation.
    /// \param value1 source position 1.
    /// \param tangent1 source tangent 1.
    /// \param value2 source position 2.
    /// \param tangent2 source tangent 2.
    /// \param amount weighting factor.
    /// \returns the interpolation result.
    template <typename T = float, typename S, std::size_t Dimension, typename = typename std::enable_if_t<std::is_arithmetic_v<S>>>
    constexpr basic_vector<T, Dimension> hermite(const basic_vector<T, Dimension>& value1
                                               , const basic_vector<T, Dimension>& tangent1
                                               , const basic_vector<T, Dimension>& value2
                                               , const basic_vector<T, Dimension>& tangent2
                                               , S                                 amount) noexcept
    {
        basic_vector<T, Dimension> vector;

        algorithm::transform(value1.begin(), value1.end(), tangent1.begin(), value2.begin(), tangent2.begin(), vector.begin()
            , [amount](T a, T b, T c, T d) -> T { return math::hermite(a, b, c, d, amount); });

        return vector;
    }

    /// Performs a linear interpolation between two vectors.
    /// \param value1 first vector.
    /// \param value2 second vector.
    /// \param amount value between 0 and 1 indicating the weight of value2.
    /// \returns the linear interpolation of the two vectors.
    template <typename T = float, typename S, std::size_t Dimension, typename = typename std::enable_if_t<std::is_arithmetic_v<S>>>
    constexpr basic_vector<T, Dimension> lerp(const basic_vector<T, Dimension>& value1
                                            , const basic_vector<T, Dimension>& value2
                                            , S                                 amount) noexcept
    {
        basic_vector<T, Dimension> vector;

        std::transform(value1.begin(), value1.end(), value2.begin(), vector.begin()
            , [amount](T a, T b) -> T { return math::lerp(a, b, amount); });

        return vector;
    }

    /// Returns a vector that contains the lowest value from each matching pair of components.
    /// \param value1 the first vector.
    /// \param value2 the second vector.
    /// \returns returns a vector that contains the lowest value from each matching pair of components.
    template <typename T = float, std::size_t Dimension>
    constexpr basic_vector<T, Dimension> min(const basic_vector<T, Dimension>& value1
                                           , const basic_vector<T, Dimension>& value2) noexcept
    {
        basic_vector<T, Dimension> vector;

        std::transform(value1.begin(), value1.end(), value2.begin(), vector.begin(), functional::min<>());

        return vector;
    }

    /// Returns a vector that contains the highest value from each matching pair of components.
    /// \param value1 the first vector
    /// \param value2 the second vector
    /// \returns returns a vector that contains the highest value from each matching pair of components.
    template <typename T = float, std::size_t Dimension>
    constexpr basic_vector<T, Dimension> max(const basic_vector<T, Dimension>& value1
                                           , const basic_vector<T, Dimension>& value2) noexcept
    {
        basic_vector<T, Dimension> vector;

        std::transform(value1.begin(), value1.end(), value2.begin(), vector.begin(), functional::max<>());

        return vector;
    }

    /// Negates a vector. The vector has the same magnitude as before, but its direction is now opposite.
    /// \param vector the vector to be negated.
    /// \returns the negated vector.
    template <typename T = float, std::size_t Dimension>
    constexpr basic_vector<T, Dimension> negate(const basic_vector<T, Dimension>& vector) noexcept
    {
        return -vector;
    }

    /// Returns the reflection of a vector off a surface that has the specified normal.
    /// \param vector source vector.
    /// \param normal normal of the surface.
    /// \returns the reflected vector.
    template <typename T = float, std::size_t Dimension>
    constexpr basic_vector<T, Dimension> reflect(const basic_vector<T, Dimension>& vector
                                               , const basic_vector<T, Dimension>& normal) noexcept
    {
        // Reference : http://mathworld.wolfram.com/Reflection.html
        // The position of the point reflected in the given plane is given by
        // r = v-2·Dn

        return vector - 2 * dot(vector, normal) * normal;
    }

    /// Performs a cubic interpolation between two vectors.
    /// \param value1 first vector
    /// \param value2 second vector
    /// \param amount weighting value.
    /// \returns the linear interpolation of the two vectors.
    template <typename T = float, typename S, std::size_t Dimension, typename = typename std::enable_if_t<std::is_arithmetic_v<S>>>
    constexpr basic_vector<T, Dimension> smooth_step(const basic_vector<T, Dimension>& value1
                                                   , const basic_vector<T, Dimension>& value2
                                                   , S                                 amount) noexcept
    {
        basic_vector<T, Dimension> vector;

        std::transform(value1.begin(), value1.end(), value2.begin(), vector.begin()
            , [amount](T a, T b) -> T { return math::smooth_step(a, b, amount); });

        return vector;
    }

    /// Returns a vector whose elements are the square root of each of a specified vector's elements.
    /// \param value a vector.
    /// \returns The square root vector.
    template <typename T = float, std::size_t Dimension>
    constexpr basic_vector<T, Dimension> square_root(const basic_vector<T, Dimension>& value) noexcept
    {
        basic_vector<T, Dimension> vector;

        std::transform(value.begin(), value.end(), vector.begin(), functional::sqrt<>());

        return vector;
    }

    /// Gets the square of the length of the given vector.
    /// \param vector a vector.
    /// \returns the square of the length of the given vector.
    template <typename T = float, std::size_t Dimension>
    constexpr T length_squared(const basic_vector<T, Dimension>& vector) noexcept
    {
        return std::inner_product(vector.begin(), vector.end(), vector.begin(), T(0));
    }

    /// Gets the length of the given vector.
    /// \param vector a vector.
    /// \returns the length of the given vector.
    template <typename T = float, std::size_t Dimension>
    constexpr T length(const basic_vector<T, Dimension>& vector) noexcept
    {
        // The modulus or magnitude of a vector is simply its length.
        // This can easily be found using Pythagorean Theorem with the vector components.
        //
        // The modulus is written like:
        // a = |a|
        //
        // Given:
        // a = xi + yj + zk
        //
        // Then:
        //
        // |a| = sqrt(x^2 + y^2 + z^2)

        return std::sqrt(length_squared(vector));
    }

    /// Retrieves the angle required to rotate the first specified vector structure into the second specified vector structure.
    /// \param left the first vector to evaluate.
    /// \param right the second vector to evaluate.
    /// \returns the angle, in radians, needed to rotate the left vector into the right vector.
    template <typename T = float, std::size_t Dimension>
    constexpr basic_radians<T> angle_between(const basic_vector<T, Dimension>& left
                                           , const basic_vector<T, Dimension>& right) noexcept
    {
        return { std::acos(dot(left, right) / std::sqrt(length_squared(left) * length_squared(right))) };
    }

    /// Calculates the distance between two vectors.
    /// \param value1 the first vector.
    /// \param value2 the second vector.
    /// \returns the distance between the source vectors.
    template <typename T = float, std::size_t Dimension>
    constexpr T distance(const basic_vector<T, Dimension>& value1, const basic_vector<T, Dimension>& value2) noexcept
    {
        return length(value2 - value1);
    }

    /// Calculates the distance between two vectors squared.
    /// \param value1 the first vector.
    /// \param value2 the second vector.
    /// \returns the distance between the source vectors squared.
    template <typename T = float, std::size_t Dimension>
    constexpr T distance_squared(const basic_vector<T, Dimension>& value1, const basic_vector<T, Dimension>& value2) noexcept
    {
        return length_squared(value2 - value1);
    }

    /// Normalizes the specified vector. A normalized vector maintains its direction but its magnitude becomes 1.
    /// The resulting vector is often called a unit vector. A vector is normalized by dividing the vector by its magnitude.
    /// \param vector the vector to be normalized.
    /// \returns the normalized vector.
    template <typename T = float, std::size_t Dimension>
    constexpr basic_vector<T, Dimension> normalize(const basic_vector<T, Dimension>& vector) noexcept
    {
        // To find the unit vector of another vector, we use the modulus operator
        // and scalar multiplication like so:
        // b = a / |a|
        //
        // Where |a| is the modulus of a
        return (vector / length(vector));
    }

    // -----------------------------------------------------------------------------------------------------------------
    // VECTOR 3 SPECIALIZATION

    /// Calculates the cross product of two vector3 structures.
    /// \param lhs the first Vector3 to evaluate.
    /// \param rhs the second Vector3 to evaluate.
    /// \returns the cross product of this vector3 and vectorb.
    template <typename T = float>
    constexpr basic_vector3<T> cross(const basic_vector3<T>& lhs, const basic_vector3<T>& rhs) noexcept
    {
        // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector3cross(v=vs.85).aspx
        return { (lhs.y * rhs.z) - (lhs.z * rhs.y)
               , (lhs.z * rhs.x) - (lhs.x * rhs.z)
               , (lhs.x * rhs.y) - (lhs.y * rhs.x) };
    }
}

#endif // SCENER_MATH_VECTOR_OPERATIONS_HPP
