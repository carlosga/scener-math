// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "basic_plane_test.hpp"

#include "equality_helper.hpp"

using namespace scener::math;

TEST_F(basic_plane_test, transform_plane_by_quaternion)
{
    plane_t    pin { 1.0f, 0.0f, 0.0f, 0.0f };
    quaternion q    = quat::create_from_axis_angle(vector3::unit_z(), radians { pi_over_2<> });
    plane_t    pout = plane::transform(pin, q);

    EXPECT_EQ(0.0f       , pout.normal.x);
    EXPECT_EQ(0.99999994f, pout.normal.y);
    EXPECT_EQ(0.0f       , pout.normal.z);
    EXPECT_EQ(0.0f       , pout.d);
}

// A test to make sure these types are blittable directly into GPU buffer memory layouts
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_plane_test, size_of)
{
    EXPECT_EQ(16u, sizeof(basic_plane<float>));
    EXPECT_EQ(32u, sizeof(basic_plane<double>));
    EXPECT_EQ(16u, sizeof(plane_t));
}

// A test for operator != (Plane, Plane)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_plane_test, inequality)
{
    plane_t a { 1.0f, 2.0f, 3.0f, 4.0f };
    plane_t b { 1.0f, 2.0f, 3.0f, 4.0f };

    // case 1: compare between same values
    bool expected = false;
    bool actual   = a != b;

    EXPECT_EQ(expected, actual);

    // case 2: compare between different values
    b.normal = { 10.0f, b.normal.y, b.normal.z };

    expected = true;
    actual   = a != b;

    EXPECT_EQ(expected, actual);
}

// A test for operator == (Plane, Plane)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_plane_test, equality)
{
    plane_t a { 1.0f, 2.0f, 3.0f, 4.0f };
    plane_t b { 1.0f, 2.0f, 3.0f, 4.0f };

    // case 1: compare between same values
    bool expected = true;
    bool actual   = a == b;

    EXPECT_EQ(expected, actual);

    // case 2: compare between different values
    b.normal = { 10.0f, b.normal.y, b.normal.z };

    expected = false;
    actual   = a == b;

    EXPECT_EQ(expected, actual);
}

// A test for Plane (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_plane_test, constructor)
{
    auto  a = 1.0f;
    auto  b = 2.0f;
    auto  c = 3.0f;
    auto  d = 4.0f;

    plane_t target { a, b, c, d };

    EXPECT_EQ(a, target.normal.x);
    EXPECT_EQ(b, target.normal.y);
    EXPECT_EQ(c, target.normal.z);
    EXPECT_EQ(d, target.d);
}

// A test for Plane.CreateFromVertices
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_plane_test, create_from_vertices)
{
    vector3 point1 { 0.0f, 1.0f, 1.0f };
    vector3 point2 { 0.0f, 0.0f, 1.0f };
    vector3 point3 { 1.0f, 0.0f, 1.0f };

    plane_t target   = plane::create_from_vertices(point1, point2, point3);
    plane_t expected = { { 0.0f, 0.0f, 1.0f }, -1.0f };

    EXPECT_EQ(target, expected);
}

// A test for Plane.CreateFromVertices
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_plane_test, create_from_vertices2)
{
    vector3 point1 { 0.0f, 0.0f, 1.0f };
    vector3 point2 { 1.0f, 0.0f, 0.0f };
    vector3 point3 { 1.0f, 1.0f, 0.0f };

    plane_t target   = plane::create_from_vertices(point1, point2, point3);
    auto    invRoot2 = (1.0f / std::sqrt(2.0f));

    plane_t expected { { invRoot2, 0, invRoot2 }, -invRoot2 };

    EXPECT_TRUE(equality_helper::equal(target, expected));
}

// A test for Plane (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_plane_test, constructor_from_vector3_and_scalar)
{
    vector3 normal { 1.0f, 2.0f, 3.0f };
    float   d      { 4.0f };
    plane_t target { normal, d };

    EXPECT_EQ(normal, target.normal);
    EXPECT_EQ(d, target.d);
}

// A test for Plane (Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_plane_test, constructor_from_vector4)
{
    vector4 value  { 1.0f, 2.0f, 3.0f, 4.0f };
    plane_t target { value };

    EXPECT_EQ(value.x, target.normal.x);
    EXPECT_EQ(value.y, target.normal.y);
    EXPECT_EQ(value.z, target.normal.z);
    EXPECT_EQ(value.w, target.d       );
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_plane_test, dot)
{
    plane_t target { 2, 3, 4, 5 };
    vector4 value  { 5, 4, 3, 2 };

    float expected = 10 + 12 + 12 + 10;
    float actual   = plane::dot(target, value);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_plane_test, dot_coordinate)
{
    plane_t target { 2, 3, 4, 5 };
    vector3 value  { 5, 4, 3 };

    float expected = 10 + 12 + 12 + 5;
    float actual   = plane::dot_coordinate(target, value);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_plane_test, dot_normal)
{
    plane_t target { 2, 3, 4, 5 };
    vector3 value  { 5, 4, 3 };

    float expected = 10 + 12 + 12;
    float actual   = plane::dot_normal(target, value);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_plane_test, normalize)
{
    plane_t target { 1, 2, 3, 4 };

    float f        = vector::length_squared(target.normal);
    float invF     = 1.0f / std::sqrt(f);

    plane_t expected { target.normal * invF, target.d * invF };

    auto actual = plane::normalize(target);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // normalize, normalized normal.
    actual = plane::normalize(actual);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// Transform by matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_plane_test, transform_by_matrix)
{
    auto target = plane::normalize(plane_t { 1.0f, 2.0f, 3.0f, 4.0f });
    auto m      = matrix::create_rotation_x(static_cast<radians>(30_deg))
                * matrix::create_rotation_y(static_cast<radians>(30_deg))
                * matrix::create_rotation_z(static_cast<radians>(30_deg));

    m.m41 = 10.0f;
    m.m42 = 20.0f;
    m.m43 = 30.0f;

    plane_t expected;

    auto inv = matrix::invert(m);
    auto itm = matrix::transpose(inv);
    auto x   = target.normal.x;
    auto y   = target.normal.y;
    auto z   = target.normal.z;
    auto w   = target.d;

    expected.normal = { x * itm.m11 + y * itm.m21 + z * itm.m31 + w * itm.m41
                      , x * itm.m12 + y * itm.m22 + z * itm.m32 + w * itm.m42
                      , x * itm.m13 + y * itm.m23 + z * itm.m33 + w * itm.m43 };

    expected.d = (x * itm.m14 + y * itm.m24 + z * itm.m34 + w * itm.m44);

    auto actual = plane::transform(target, m);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// Transform by quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_plane_test, transform_by_quaternion)
{
    auto target = plane::normalize(plane_t { 1, 2, 3, 4 });
    auto m      = matrix::create_rotation_x(static_cast<radians>(30_deg))
                * matrix::create_rotation_y(static_cast<radians>(30_deg))
                * matrix::create_rotation_z(static_cast<radians>(30_deg));
    auto q      = quat::create_from_rotation_matrix(m);

    plane_t expected;

    auto x = target.normal.x;
    auto y = target.normal.y;
    auto z = target.normal.z;
    auto w = target.d;

    expected.normal = { x * m.m11 + y * m.m21 + z * m.m31 + w * m.m41
                      , x * m.m12 + y * m.m22 + z * m.m32 + w * m.m42
                      , x * m.m13 + y * m.m23 + z * m.m33 + w * m.m43 };

    expected.d = (x * m.m14 + y * m.m24 + z * m.m34 + w * m.m44);

    auto actual = plane::transform(target, q);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Plane comparison involving NaN values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_plane_test, equals_nan)
{
    plane_t a = { NaN<>, 0    , 0    , 0     };
    plane_t b = { 0    , NaN<>, 0    , 0     };
    plane_t c = { 0    , 0    , NaN<>, 0     };
    plane_t d = { 0    , 0    , 0    , NaN<> };
    plane_t z = { 0    , 0    , 0    , 0     };

    EXPECT_FALSE(a == z);
    EXPECT_FALSE(c == z);
    EXPECT_FALSE(d == z);
    EXPECT_FALSE(b == z);

    EXPECT_TRUE(a != z);
    EXPECT_TRUE(b != z);
    EXPECT_TRUE(c != z);
    EXPECT_TRUE(d != z);
}
