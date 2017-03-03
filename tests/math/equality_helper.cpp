// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ----------------------------------------------------------------------------------------------------
// Ported from Microsoft corefx System.Numerics.Vector MathHelper class.
// ----------------------------------------------------------------------------------------------------

#include "equality_helper.hpp"

using namespace scener::math;

// Comparison helpers with small tolerance to allow for floating point rounding during computations.
bool equality_helper::equal(const float& a, const float& b)
{
    return (std::fabs(a - b) < 1e-5);
}

bool equality_helper::equal(const vector2& a, const vector2& b)
{
    return equal(a.x, b.x) && equal(a.y, b.y);
}

bool equality_helper::equal(const vector3& a, const vector3& b)
{
    return equal(a.x, b.x) && equal(a.y, b.y) && equal(a.z, b.z);
}

bool equality_helper::equal(const vector4& a, const vector4& b)
{
    return equal(a.x, b.x) && equal(a.y, b.y) && equal(a.z, b.z) && equal(a.w, b.w);
}

bool equality_helper::equal(const matrix4& a, const matrix4& b)
{
    return
        equal(a.m11, b.m11) && equal(a.m12, b.m12) && equal(a.m13, b.m13) && equal(a.m14, b.m14)
     && equal(a.m21, b.m21) && equal(a.m22, b.m22) && equal(a.m23, b.m23) && equal(a.m24, b.m24)
     && equal(a.m31, b.m31) && equal(a.m32, b.m32) && equal(a.m33, b.m33) && equal(a.m34, b.m34)
     && equal(a.m41, b.m41) && equal(a.m42, b.m42) && equal(a.m43, b.m43) && equal(a.m44, b.m44);
}

bool equality_helper::equal(const plane_t& a, const plane_t& b)
{
    return equal(a.normal, b.normal) && equal(a.d, b.d);
}

bool equality_helper::equal(const quaternion& a, const quaternion& b)
{
    return equal(a.x, b.x) && equal(a.y, b.y) && equal(a.z, b.z) && equal(a.w, b.w);
}

bool  equality_helper::equal_rotation(const quaternion& a, const quaternion& b)
{
    return equal(a, b) || equal(a, -b);
}
