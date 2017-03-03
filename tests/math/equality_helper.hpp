// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ----------------------------------------------------------------------------------------------------
// Ported from Microsoft corefx System.Numerics.Vectors MathHelper class.
// ----------------------------------------------------------------------------------------------------

#ifndef TESTS_EQUALITYHELPER_HPP
#define	TESTS_EQUALITYHELPER_HPP

#include <scener/math/math.hpp>

class equality_helper
{
public:
    // Comparison helpers with small tolerance to allow for floating point rounding during computations.
    static bool equal(const float& a, const float& b);

    static bool equal(const scener::math::vector2& a, const scener::math::vector2& b);

    static bool equal(const scener::math::vector3& a, const scener::math::vector3& b);

    static bool equal(const scener::math::vector4& a, const scener::math::vector4& b);

    static bool equal(const scener::math::matrix4& a, const scener::math::matrix4& b);

    static bool equal(const scener::math::plane_t& a, const scener::math::plane_t& b);

    static bool equal(const scener::math::quaternion& a, const scener::math::quaternion& b);

    static bool equal_rotation(const scener::math::quaternion& a, const scener::math::quaternion& b);
};

#endif // TESTS_EQUALITYHELPER_HPP
