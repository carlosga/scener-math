// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "basic_vector4_test.hpp"

#include "equality_helper.hpp"

using namespace scener::math;

TEST_F(basic_vector4_test, vector_matrix_multiplication)
{
    auto point  = vector4 { 10.0f, 5.0f, 1.0f, 4.0f };
    auto matrix = matrix4 { 10.0f, 10.0f, 10.0f, 0.0f
                          , 20.0f, 20.0f, 20.0f, 0.0f
                          , 30.0f, 30.0f, 30.0f, 0.0f
                          , 5.0f , 10.0f, 15.0f, 1.0f };
    auto result = point * matrix;

    // pointResult is equal to (250, 270, 290, 4)
    EXPECT_EQ(250.0f, result.x);
    EXPECT_EQ(270.0f, result.y);
    EXPECT_EQ(290.0f, result.z);
    EXPECT_EQ(  4.0f, result.w);
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, size_of)
{
    EXPECT_TRUE(16 == sizeof(vector4));
    EXPECT_TRUE(16 == sizeof(vector4i));
    EXPECT_TRUE(16 == sizeof(vector4u));
    EXPECT_TRUE(32 == sizeof(vector4d));
}

// A test for DistanceSquared (vector4f, vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, distance_squared)
{
    auto a = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = vector4 { 5.0f, 6.0f, 7.0f, 8.0f };

    auto expected = 64.0f;
    auto actual   = vector::distance_squared(a, b);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Distance (vector4f, vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, distance)
{
    auto a = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = vector4 { 5.0f, 6.0f, 7.0f, 8.0f };

    auto expected = 8.0f;
    auto actual   = vector::distance(a, b);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Distance (vector4f, vector4f)
// Distance from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, distance_from_the_same_point)
{
    auto a = vector4({ 1.051f, 2.05f }, 3.478f, 1.0f);  // With vector2
    auto b = vector4({ 1.051f, 2.05f, 3.478f }, 0.0f);  // With vector3

    b.w = 1.0f;

    auto actual = vector::distance(a, b);

    EXPECT_EQ(0.0f, actual);
}

// A test for Dot (vector4f, vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, dot)
{
    auto a = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = vector4 { 5.0f, 6.0f, 7.0f, 8.0f };

    auto expected = 70.0f;
    auto actual   = vector::dot(a, b);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Dot (vector4f, vector4f)
// Dot test for perpendicular vector
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, dot_for_perpendicular_vector)
{
    auto a = vector3 { 1.55f, 1.55f, 1 };
    auto b = vector3 { 2.5f, 3, 1.5f };
    auto c = vector::cross(a, b);

    auto d = vector4 { a, 0 };
    auto e = vector4 { c, 0 };

    auto actual = vector::dot(d, e);

    EXPECT_TRUE(equality_helper::equal(0.0f, actual));
}

// A test for Length ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, length)
{
    auto a      = vector3 { 1.0f, 2.0f, 3.0f };
    auto w      = 4.0f;
    auto target = vector4 { a, w };

    auto expected = std::sqrt(30.0f);
    auto actual   = vector::length(target);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Length ()
// Length test where length is zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, length_where_length_is_zero)
{
    vector4 target;
    auto    expected = 0.0f;
    auto    actual   = vector::length(target);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for LengthSquared ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, length_squared)
{
    auto a = vector3 { 1.0f, 2.0f, 3.0f };
    auto w = 4.0f;

    auto target = vector4 { a, w };

    auto expected = 30;
    auto actual   = vector::length_squared(target);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Min (vector4f, vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, Min)
{
    auto a = vector4 { -1.0f, 4.0f, -3.0f, 1000.0f };
    auto b = vector4 { 2.0f, 1.0f, -1.0f, 0.0f };

    auto expected = vector4 { -1.0f, 1.0f, -3.0f, 0.0f };
    auto actual   = vector::min(a, b);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Max (vector4f, vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, max)
{
    auto a = vector4 { -1.0f, 4.0f, -3.0f, 1000.0f };
    auto b = vector4 { 2.0f, 1.0f, -1.0f, 0.0f };

    auto expected = vector4(2.0f, 4.0f, -1.0f, 1000.0f);
    auto actual   = vector::max(a, b);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, min_max_code_coverage)
{
    auto    min = vector4::zero();
    auto    max = vector4::one();
    vector4 actual;

    // Min.
    actual = vector::min(min, max);

    EXPECT_EQ(actual, min);

    actual = vector::min(max, min);

    EXPECT_EQ(actual, min);

    // Max.
    actual = vector::max(min, max);

    EXPECT_EQ(actual, max);

    actual = vector::max(max, min);

    EXPECT_EQ(actual, max);
}

// A test for clamp (vector4f, vector4f, vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, clamp)
{
    auto a   = vector4 { 0.5f, 0.3f, 0.33f, 0.44f };
    auto min = vector4 { 0.0f, 0.1f, 0.13f, 0.14f };
    auto max = vector4 { 1.0f, 1.1f, 1.13f, 1.14f };

    // Normal case.
    // Case N1: specfied value is in the range.
    auto expected = vector4 { 0.5f, 0.3f, 0.33f, 0.44f };
    auto actual   = vector::clamp(a, min, max);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Normal case.
    // Case N2: specfied value is bigger than max value.
    a        = vector4 { 2.0f, 3.0f, 4.0f, 5.0f };
    expected = max;
    actual   = vector::clamp(a, min, max);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Case N3: specfied value is smaller than max value.
    a        = vector4 { -2.0f, -3.0f, -4.0f, -5.0f };
    expected = min;
    actual   = vector::clamp(a, min, max);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Case N4: combination case.
    a        = vector4 { -2.0f, 0.5f, 4.0f, -5.0f };
    expected = vector4 { min.x, a.y, max.z, min.w };
    actual   = vector::clamp(a, min, max);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // User specfied min value is bigger than max value.
    max = vector4 { 0.0f, 0.1f, 0.13f, 0.14f };
    min = vector4 { 1.0f, 1.1f, 1.13f, 1.14f };

    // Case W1: specfied value is in the range.
    a        = vector4 { 0.5f, 0.3f, 0.33f, 0.44f };
    expected = min;
    actual   = vector::clamp(a, min, max);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Normal case.
    // Case W2: specfied value is bigger than max and min value.
    a        = vector4 { 2.0f, 3.0f, 4.0f, 5.0f };
    expected = min;
    actual   = vector::clamp(a, min, max);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Case W3: specfied value is smaller than min and max value.
    a        = vector4 { -2.0f, -3.0f, -4.0f, -5.0f };
    expected = min;
    actual   = vector::clamp(a, min, max);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Lerp (vector4f, vector4f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, Lerp)
{
    auto a = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = vector4 { 5.0f, 6.0f, 7.0f, 8.0f };
    auto t = 0.5f;

    auto expected = vector4 { 3.0f, 4.0f, 5.0f, 6.0f };
    auto actual   = vector::lerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Lerp (vector4f, vector4f, float)
// Lerp test with factor zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, lerp_with_factor_zero)
{
    auto a = vector4 { { 1.0f, 2.0f, 3.0f }, 4.0f };
    auto b = vector4 { 4.0f, 5.0f, 6.0f, 7.0f };
    auto t = 0.0f;

    auto expected = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto actual   = vector::lerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Lerp (vector4f, vector4f, float)
// Lerp test with factor one
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, lerp_with_factor_one)
{
    auto a = vector4 { { 1.0f, 2.0f, 3.0f }, 4.0f };
    auto b = vector4 { 4.0f, 5.0f, 6.0f, 7.0f };
    auto t = 1.0f;

    auto expected = vector4 { 4.0f, 5.0f, 6.0f, 7.0f };
    auto actual   = vector::lerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Lerp (vector4f, vector4f, float)
// Lerp test with factor > 1
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, lerp_with_factor_greater_than_one)
{
    auto a = vector4 { { 0.0f, 0.0f, 0.0f }, 0.0f };
    auto b = vector4 { 4.0f, 5.0f, 6.0f, 7.0f };
    auto t = 2.0f;

    auto expected = vector4 { 8.0f, 10.0f, 12.0f, 14.0f };
    auto actual   = vector::lerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Lerp (vector4f, vector4f, float)
// Lerp test with factor < 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, lerp_with_factor_less_than_zero)
{
    auto a = vector4 { { 0.0f, 0.0f, 0.0f }, 0.0f };
    auto b = vector4 { 4.0f, 5.0f, 6.0f, 7.0f };
    auto t = -2.0f;

    auto expected = -(b * 2.0f);
    auto actual   = vector::lerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Lerp (vector4f, vector4f, float)
// Lerp test from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, lerp_from_the_same_point)
{
    vector4 a = vector4 { 4.0f, 5.0f, 6.0f, 7.0f };
    vector4 b = vector4 { 4.0f, 5.0f, 6.0f, 7.0f };
    auto    t = 0.85f;

    auto expected = a;
    auto actual   = vector::lerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (vector3f, matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, transform_vector3)
{
    auto v = vector3 { 1.0f, 2.0f, 3.0f };
    auto a = static_cast<radians>(degrees { 30.0f });
    auto m = matrix::create_rotation_x(a)
           * matrix::create_rotation_y(a)
           * matrix::create_rotation_z(a);

    m.m41 = 10.0f;
    m.m42 = 20.0f;
    m.m43 = 30.0f;

    auto expected = vector4(12.19198728f, 21.53349376f, 32.61602545f, 1.0f);
    auto actual   = vector::transform(static_cast<vector4>(v), m);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (vector4f, matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, transform)
{
    auto v = vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto a = static_cast<radians>(degrees { 30.0f });
    auto m = matrix::create_rotation_x(a)
           * matrix::create_rotation_y(a)
           * matrix::create_rotation_z(a);

    m.m41 = 10.0f;
    m.m42 = 20.0f;
    m.m43 = 30.0f;

    auto expected = vector4(2.19198728f, 1.53349376f, 2.61602545f, 0.0f);
    auto actual   = vector::transform(v, m);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    v.w = 1.0f;

    expected = vector4 { 12.19198728f, 21.53349376f, 32.61602545f, 1.0f };
    actual   = vector::transform(v, m);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (vector4f, matrix4x4)
// Transform vector4 with zero matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, transform_with_zero_matrix)
{
    auto v        = vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto m        = matrix4 { };
    auto expected = vector4 { 0, 0, 0, 0 };
    auto actual   = vector::transform(v, m);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (vector4f, matrix4x4)
// Transform vector4 with identity matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, transform_with_identity_matrix)
{
    auto v        = vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto m        = matrix4::identity();
    auto expected = vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto actual   = vector::transform(v, m);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (vector3f, matrix4x4)
// Transform vector3f test
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, transform_vector3_2)
{
    auto    v = vector3 { 1.0f, 2.0f, 3.0f };
    radians a = degrees { 30.0f };
    auto    m = matrix::create_rotation_x(a)
              * matrix::create_rotation_y(a)
              * matrix::create_rotation_z(a);

    m.m41 = 10.0f;
    m.m42 = 20.0f;
    m.m43 = 30.0f;

    auto expected = vector::transform({ v, 1.0f }, m);
    auto actual   = vector::transform(static_cast<vector4>(v), m);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (vector3f, matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, transform_vector3_with_zero_matrix)
{
    auto v        = vector3 { 1.0f, 2.0f, 3.0f };
    auto m        = matrix4 { };
    auto expected = vector4 { 0, 0, 0, 0 };
    auto actual   = vector::transform({ v, 1.0f }, m);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (vector3f, matrix4x4)
// Transform vector3 with identity matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, transform_vector3_with_identity_matrix)
{
    auto v        = vector3 { 1.0f, 2.0f, 3.0f };
    auto m        = matrix4::identity();
    auto expected = vector4 { 1.0f, 2.0f, 3.0f, 1.0f };
    auto actual   = vector::transform({ v, 1.0f }, m);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (vector3f, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, transform_vector3_quaternion)
{
    auto v = vector3 { 1.0f, 2.0f, 3.0f };
    auto a = static_cast<radians>(degrees { 30.0f });
    auto m = matrix::create_rotation_x(a)
           * matrix::create_rotation_y(a)
           * matrix::create_rotation_z(a);

    auto q        = quat::create_from_rotation_matrix(m);
    auto expected = vector::transform(v, m);
    auto actual   = vector::transform(v, q);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (vector4f, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, transform_quaternion)
{
    auto v = vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto a = static_cast<radians>(degrees { 30.0f });
    auto m = matrix::create_rotation_x(a)
           * matrix::create_rotation_y(a)
           * matrix::create_rotation_z(a);

    auto q        = quat::create_from_rotation_matrix(m);
    auto expected = vector::transform(v, m);
    auto actual   = vector::transform(v, q);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    v.w        = 1.0f;
    expected.w = 1.0f;

    actual = vector::transform(v, q);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (vector4f, Quaternion)
// Transform vector4 with zero quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, transform_with_zero_quaternion)
{
    auto v        = vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto q        = quaternion { };
    auto expected = v;
    auto actual   = vector::transform(v, q);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (vector4f, Quaternion)
// Transform vector4 with identity quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, transform_with_identity_quaternion)
{
    auto v        = vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto q        = quaternion::identity();
    auto expected = vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto actual   = vector::transform(v, q);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (vector3f, Quaternion)
// Transform vector3 with zero quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, transform_vector3_with_zero_quaternion)
{
    auto v        = vector3 { 1.0f, 2.0f, 3.0f };
    auto q        = quaternion { };
    auto expected = vector4 { v, 1.0f };
    auto actual   = vector::transform(static_cast<vector4>(v), q);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (vector3f, Quaternion)
// Transform vector3 with identity quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, transform_vector3_with_identity_quaternion)
{
    auto v        = vector3 { 1.0f, 2.0f, 3.0f };
    auto q        = quaternion::identity();
    auto expected = vector4 { 1.0f, 2.0f, 3.0f, 1.0f };
    auto actual   = vector::transform(static_cast<vector4>(v), q);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Normalize (vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, normalize)
{
    auto a        = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto expected = vector4 { 0.1825741858350553711523232609336f
                            , 0.3651483716701107423046465218672f
                            , 0.5477225575051661134569697828008f
                            , 0.7302967433402214846092930437344f };

    auto actual = vector::normalize(a);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Normalize (vector4f)
// Normalize vector of length one
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, normalize_vector_of_length_zero)
{
    auto a        = vector4 { 1.0f, 0.0f, 0.0f, 0.0f };
    auto expected = vector4 { 1.0f, 0.0f, 0.0f, 0.0f };
    auto actual   = vector::normalize(a);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Normalize (vector4f)
// Normalize vector of length zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, normalize_vector_of_length_zero2)
{
    auto a      = vector4 { 0.0f, 0.0f, 0.0f, 0.0f };
    auto actual = vector::normalize(a);

    EXPECT_TRUE(is_nan(actual.x) && is_nan(actual.y) && is_nan(actual.z) && is_nan(actual.w));
}

// A test for operator - (vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, unary_negation)
{
    auto a        = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto expected = vector4 { -1.0f, -2.0f, -3.0f, -4.0f };
    auto actual   = -a;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator - (vector4f, vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, subtraction)
{
    auto a        = vector4 { 1.0f, 6.0f, 3.0f, 4.0f };
    auto b        = vector4 { 5.0f, 2.0f, 3.0f, 9.0f };
    auto expected = vector4 { -4.0f, 4.0f, 0.0f, -5.0f };
    auto actual   = a - b;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator * (vector4f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, multiply_by_scalar)
{
    auto a      = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto factor = 2.0f;

    auto expected = vector4 { 2.0f, 4.0f, 6.0f, 8.0f };
    auto actual   = a * factor;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator * (float, vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, multiply_scalar_by_vector)
{
    auto a      = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto factor = 2.0f;

    auto expected = vector4 { 2.0f, 4.0f, 6.0f, 8.0f };
    auto actual   = factor * a;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator * (vector4f, vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, multiply)
{
    auto a        = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b        = vector4 { 5.0f, 6.0f, 7.0f, 8.0f };
    auto expected = vector4 { 5.0f, 12.0f, 21.0f, 32.0f };
    auto actual   = a * b;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator / (vector4f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, division)
{
    auto a   = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto div = 2.0f;

    auto expected = vector4 { 0.5f, 1.0f, 1.5f, 2.0f };
    auto actual   = a / div;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator / (vector4f, vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, division1)
{
    auto a = vector4 { 1.0f, 6.0f, 7.0f, 4.0f };
    auto b = vector4 { 5.0f, 2.0f, 3.0f, 8.0f };

    auto expected = vector4 { 1.0f / 5.0f, 6.0f / 2.0f, 7.0f / 3.0f, 4.0f / 8.0f };
    auto actual   = a / b;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator / (vector4f, float)
// Divide by zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, division_by_zero_scalar)
{
    auto a      = vector4 { -2.0f, 3.0f, max_value<>, nan<> };
    auto div    = 0.0f;
    auto actual = a / div;

    EXPECT_TRUE(is_negative_infinity(actual.x));
    EXPECT_TRUE(is_positive_infinity(actual.y));
    EXPECT_TRUE(is_positive_infinity(actual.z));
    EXPECT_TRUE(is_nan(actual.w));
}

// A test for operator / (vector4f, vector4f)
// Divide by zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, division_by_zero)
{
    auto a = vector4 { 0.047f, -3.0f, negative_infinity<>, min_value<>};
    auto b = vector4 { };

    vector4 actual = a / b;

    EXPECT_TRUE(is_positive_infinity(actual.x));
    EXPECT_TRUE(is_negative_infinity(actual.y));
    EXPECT_TRUE(is_negative_infinity(actual.z));
    EXPECT_TRUE(is_negative_infinity(actual.w));
}

// A test for operator + (vector4f, vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, addition)
{
    auto a = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = vector4 { 5.0f, 6.0f, 7.0f, 8.0f };

    auto expected = vector4 { 6.0f, 8.0f, 10.0f, 12.0f };
    auto actual   = a + b;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, add)
{
    auto v1 = vector4 { 2.5f, 2.0f, 3.0f, 3.3f };
    auto v2 = vector4 { 5.5f, 4.5f, 6.5f, 7.5f };

    auto v3 = v1 + v2;
    auto v5 = vector4 { -1.0f, 0.0f, 0.0f, nan<> };
    auto v4 = v1 + v5;

    EXPECT_TRUE( 8.0f == v3.x);
    EXPECT_TRUE( 6.5f == v3.y);
    EXPECT_TRUE( 9.5f == v3.z);
    EXPECT_TRUE(10.8f == v3.w);
    EXPECT_TRUE( 1.5f == v4.x);
    EXPECT_TRUE( 2.0f == v4.y);
    EXPECT_TRUE( 3.0f == v4.z);
    EXPECT_TRUE(is_nan(v4.w));
}

// A test for vector4f (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, constructor)
{
    auto x = 1.0f;
    auto y = 2.0f;
    auto z = 3.0f;
    auto w = 4.0f;

    auto target = vector4 { x, y, z, w };

    EXPECT_TRUE(equality_helper::equal(target.x, x)
             && equality_helper::equal(target.y, y)
             && equality_helper::equal(target.z, z)
             && equality_helper::equal(target.w, w));
}

// A test for vector4f (vector2f, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, constructor_with_vector2)
{
    auto a = vector2 { 1.0f, 2.0f };
    auto z = 3.0f;
    auto w = 4.0f;

    auto target = vector4 { a, z, w };

    EXPECT_TRUE(equality_helper::equal(target.x, a.x)
             && equality_helper::equal(target.y, a.y)
             && equality_helper::equal(target.z, z)
             && equality_helper::equal(target.w, w));
}

// A test for vector4f (vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, constructor_with_vector3)
{
    auto a = vector3 { 1.0f, 2.0f, 3.0f };
    auto w = 4.0f;

    auto target = vector4 { a, w };

    EXPECT_TRUE(equality_helper::equal(target.x, a.x)
             && equality_helper::equal(target.y, a.y)
             && equality_helper::equal(target.z, a.z)
             && equality_helper::equal(target.w, w));
}

// A test for vector4f ()
// Constructor with no parameter
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, default_constructor)
{
    vector4 a;

    EXPECT_EQ(a.x, 0.0f);
    EXPECT_EQ(a.y, 0.0f);
    EXPECT_EQ(a.z, 0.0f);
    EXPECT_EQ(a.w, 0.0f);
}

// A test for vector4f ()
// Constructor with special floating values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, constructor_with_special_floating_values)
{
    auto target = vector4 { nan<>, max_value<>, positive_infinity<>, epsilon<> };

    EXPECT_TRUE(is_nan(target.x));
    EXPECT_TRUE(equality_helper::equal(max_value<>, target.y));
    EXPECT_TRUE(is_positive_infinity(target.z));
    EXPECT_TRUE(equality_helper::equal(epsilon<>, target.w));
}

// A test for negate (vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, negate)
{
    auto a        = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto expected = vector4 { -1.0f, -2.0f, -3.0f, -4.0f };
    auto actual   = vector::negate(a);

    EXPECT_EQ(expected, actual);
}

// A test for operator != (vector4f, vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, inequality)
{
    auto a = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };

    // case 1: compare between same values
    bool expected = false;
    bool actual   = a != b;

    EXPECT_EQ(expected, actual);

    // case 2: compare between different values
    b.x = 10.0f;

    expected = true;
    actual   = a != b;

    EXPECT_EQ(expected, actual);
}

// A test for operator == (vector4f, vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, equality)
{
    auto a = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = vector4 { 1.0f, 2.0f, 3.0f, 4.0f };

    // case 1: compare between same values
    bool expected = true;
    bool actual   = a == b;

    EXPECT_EQ(expected, actual);

    // case 2: compare between different values
    b.x = 10.0f;

    expected = false;
    actual   = a == b;

    EXPECT_EQ(expected, actual);
}

// A test for UnitW
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, unit_w)
{
    vector4 val { 0.0f, 0.0f, 0.0f, 1.0f };

    EXPECT_EQ(val, vector4::unit_w());
}

// A test for UnitX
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, unit_x)
{
    vector4 val { 1.0f, 0.0f, 0.0f, 0.0f };

    EXPECT_EQ(val, vector4::unit_x());
}

// A test for UnitY
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, unit_y)
{
    vector4 val { 0.0f, 1.0f, 0.0f, 0.0f };

    EXPECT_EQ(val, vector4::unit_y());
}

// A test for UnitZ
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, unit_z)
{
    vector4 val { 0.0f, 0.0f, 1.0f, 0.0f };

    EXPECT_EQ(val, vector4::unit_z());
}

// A test for One
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, one)
{
    vector4 val { 1.0f, 1.0f, 1.0f, 1.0f };

    EXPECT_EQ(val, vector4::one());
}

// A test for Zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, zero)
{
    vector4 val { 0.0f, 0.0f, 0.0f, 0.0f };

    EXPECT_EQ(val, vector4::zero());
}

// A test for vector4f (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, constructor_with_scalar_value)
{
    auto    value = 1.0f;
    vector4 target { value };

    vector4 expected { value, value, value, value };

    EXPECT_EQ(expected, target);

    value    = 2.0f;
    target   = vector4 { value };
    expected = vector4 { value, value, value, value };

    EXPECT_EQ(expected, target);
}

// A test for vector4f comparison involving NaN values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, equals_nan)
{
    vector4 a { nan<>, 0    , 0    , 0     };
    vector4 b { 0    , nan<>, 0    , 0     };
    vector4 c { 0    , 0    , nan<>, 0     };
    vector4 d { 0    , 0    , 0    , nan<> };

    EXPECT_FALSE(a == vector4::zero());
    EXPECT_FALSE(b == vector4::zero());
    EXPECT_FALSE(c == vector4::zero());
    EXPECT_FALSE(d == vector4::zero());

    EXPECT_TRUE(a != vector4::zero());
    EXPECT_TRUE(b != vector4::zero());
    EXPECT_TRUE(c != vector4::zero());
    EXPECT_TRUE(d != vector4::zero());
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, abs)
{
    vector4 v1 { -2.5f, 2.0f, 3.0f, 3.3f };
    vector4 v3 = vector::abs(vector4 { positive_infinity<>, 0.0f, negative_infinity<>, nan<> });
    vector4 v  = vector::abs(v1);

    EXPECT_EQ(2.5f, v.x);
    EXPECT_EQ(2.0f, v.y);
    EXPECT_EQ(3.0f, v.z);
    EXPECT_EQ(3.3f, v.w);
    EXPECT_TRUE(positive_infinity<> == v3.x);
    EXPECT_EQ(0.0f, v3.y);
    EXPECT_TRUE(positive_infinity<> == v3.z);
    EXPECT_TRUE(is_nan(v3.w));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, square_root)
{
    vector4 v1 { -2.5f, 2.0f, 3.0f, 3.3f };
    vector4 v2 { 5.5f, 4.5f, 6.5f, 7.5f };

    EXPECT_EQ(2, (std::int32_t)vector::square_root(v2).x);
    EXPECT_EQ(2, (std::int32_t)vector::square_root(v2).y);
    EXPECT_EQ(2, (std::int32_t)vector::square_root(v2).z);
    EXPECT_EQ(2, (std::int32_t)vector::square_root(v2).w);
    EXPECT_TRUE(is_nan(vector::square_root(v1).x));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector4_test, set_fields)
{
    vector4 v3 { 4.0f, 5.0f, 6.0f, 7 };

    v3.x = 1.0f;
    v3.y = 2.0f;
    v3.z = 3.0f;
    v3.w = 4.0f;

    EXPECT_EQ(1.0f, v3.x);
    EXPECT_EQ(2.0f, v3.y);
    EXPECT_EQ(3.0f, v3.z);
    EXPECT_EQ(4.0f, v3.w);

    auto v4 = v3;

    v4.y = 0.5f;
    v4.z = 2.2f;
    v4.w = 3.5f;

    EXPECT_EQ(1.0f, v4.x);
    EXPECT_EQ(0.5f, v4.y);
    EXPECT_EQ(2.2f, v4.z);
    EXPECT_EQ(3.5f, v4.w);
    EXPECT_EQ(2.0f, v3.y);
}
