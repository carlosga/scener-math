// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "basic_vector2_test.hpp"

#include "equality_helper.hpp"

using namespace scener::math;

TEST_F(basic_vector2_test, individual_coordinates_constructor)
{
    auto x      = 20.0f;
    auto y      = 30.0f;
    auto vector = vector2 { x, y };

    // vector2 is equal to (20.0, 30.0)
    EXPECT_EQ(x, vector.x);
    EXPECT_EQ(y, vector.y);
}

TEST_F(basic_vector2_test, lerp)
{
    auto a      = vector2 { 5.0f, 10.0f };
    auto b      = vector2 { 0.0f, -20.0f };
    auto result = vector::lerp(a, b, 0.4f);

    EXPECT_EQ( 3.0f , result.x);
    EXPECT_EQ(-2.0f , result.y);
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, distance)
{
    auto a        = vector2 { 1.0f, 2.0f };
    auto b        = vector2 { 3.0f, 4.0f };
    auto expected = std::sqrt(8.0f);
    auto actual   = vector::distance(a, b);

    EXPECT_EQ(expected, actual);
}

// A test for Distance (Vector2f, Vector2f)
// Distance from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, distance2)
{
    auto a      = vector2 { 1.051f, 2.05f };
    auto b      = vector2 { 1.051f, 2.05f };
    auto actual = vector::distance(a, b);

    EXPECT_EQ(0.0f, actual);
}

// A test for DistanceSquared (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, distance_squared)
{
    auto a        = vector2 { 1.0f, 2.0f };
    auto b        = vector2 { 3.0f, 4.0f };
    auto expected = 8.0f;
    auto actual   = vector::distance_squared(a, b);

    EXPECT_EQ(expected, actual);
}

// A test for Dot (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, dot)
{
    auto a        = vector2 { 1.0f, 2.0f };
    auto b        = vector2 { 3.0f, 4.0f };
    auto expected = 11.0f;
    auto actual   = vector::dot(a, b);

    EXPECT_EQ(expected, actual);
}

// A test for Dot (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, dot_with_perpendicular_vector)
{
    auto a        = vector2 { 1.55f, 1.55f };
    auto b        = vector2 { -1.55f, 1.55f };
    auto expected = 0.0f;
    auto actual   = vector::dot(a, b);

    EXPECT_EQ(expected, actual);
}

// A test for Dot (Vector2f, Vector2f)
// Dot test with special float values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, dot_with_special_float_values)
{
    auto a = vector2 { min_value<>, min_value<> };
    auto b = vector2 { max_value<>, max_value<> };

    auto actual = vector::dot(a, b);

    EXPECT_TRUE(is_negative_infinity(actual));
}

// A test for Length ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, length)
{
    auto a        = vector2 { 2.0f, 4.0f };
    auto target   = a;
    auto expected = std::sqrt(20.0f);
    auto actual   = vector::length(target);

    EXPECT_EQ(expected, actual);
}

// A test for Length ()
// Length test where length is zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, zero_length)
{
    auto target   = vector2 { 0.0f, 0.0f };
    auto expected = 0.0f;
    auto actual   = vector::length(target);

    EXPECT_EQ(expected, actual);
}

// A test for LengthSquared ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, length_squared)
{
    auto a        = vector2 { 2.0f, 4.0f };
    auto target   = a;
    auto expected = 20.0f;
    auto actual   = vector::length_squared(target);

    EXPECT_EQ(expected, actual);
}

// A test for LengthSquared ()
// LengthSquared test where the result is zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, zero_length_squared)
{
    auto a        = vector2 { 0.0f, 0.0f };
    auto expected = 0.0f;
    auto actual   = vector::length_squared(a);

    EXPECT_EQ(expected, actual);
}

// A test for Min (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, min)
{
    auto a        = vector2 { -1.0f, 4.0f };
    auto b        = vector2 { 2.0f, 1.0f };
    auto expected = vector2 { -1.0f, 1.0f };
    auto actual   = vector::min(a, b);

    EXPECT_EQ(expected, actual);
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, min_max_code_coverage)
{
    auto min = vector2 { 0.0f, 0.0f };
    auto max = vector2 { 1.0f, 1.0f };

    // Min.
    auto actual = vector::min(min, max);
    EXPECT_EQ(actual, min);

    actual = vector::min(max, min);
    EXPECT_EQ(actual, min);

    // Max.
    actual = vector::max(min, max);
    EXPECT_EQ(actual, max);

    actual = vector::max(max, min);
    EXPECT_EQ(actual, max);
}

// A test for Max (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, max)
{
    auto a        = vector2 { -1.0f, 4.0f };
    auto b        = vector2 { 2.0f, 1.0f };
    auto expected = vector2 { 2.0f, 4.0f };
    auto actual   = vector::max(a, b);

    EXPECT_EQ(expected, actual);
}

// A test for clamp (Vector2f, Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, clamp)
{
    auto a   = vector2 { 0.5f, 0.3f };
    auto min = vector2 { 0.0f, 0.1f };
    auto max = vector2 { 1.0f, 1.1f };

    // Normal case.
    // Case N1: specified value is in the range.
    auto expected = vector2 { 0.5f, 0.3f };
    auto actual   = vector::clamp(a, min, max);

    EXPECT_EQ(expected, actual);

    // Normal case.
    // Case N2: specified value is bigger than max value.
    a        = vector2 { 2.0f, 3.0f };
    expected = max;
    actual   = vector::clamp(a, min, max);

    EXPECT_EQ(expected, actual);

    // Case N3: specified value is smaller than max value.
    a        = vector2 { -1.0f, -2.0f };
    expected = min;
    actual   = vector::clamp(a, min, max);

    EXPECT_EQ(expected, actual);

    // Case N4: combination case.
    a        = vector2 { -2.0f, 4.0f };
    expected = vector2 { min.x, max.y };
    actual   = vector::clamp(a, min, max);

    EXPECT_EQ(expected, actual);

    // User specified min value is bigger than max value.
    max = vector2 { 0.0f, 0.1f };
    min = vector2 { 1.0f, 1.1f };

    // Case W1: specified value is in the range.
    a        = vector2 { 0.5f, 0.3f };
    expected = min;
    actual   = vector::clamp(a, min, max);

    EXPECT_EQ(expected, actual);

    // Normal case.
    // Case W2: specified value is bigger than max and min value.
    a        = vector2 { 2.0f, 3.0f };
    expected = min;
    actual   = vector::clamp(a, min, max);

    EXPECT_EQ(expected, actual);

    // Case W3: specified value is smaller than min and max value.
    a        = vector2 { -1.0f, -2.0f };
    expected = min;
    actual   = vector::clamp(a, min, max);

    EXPECT_EQ(expected, actual);
}

// A test for Lerp (Vector2f, Vector2f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, lerp2)
{
    auto a        = vector2 { 1.0f, 2.0f };
    auto b        = vector2 { 3.0f, 4.0f };
    auto t        = 0.5f;
    auto expected = vector2 { 2.0f, 3.0f };
    auto actual   = vector::lerp(a, b, t);

    EXPECT_EQ(expected, actual);
}

// A test for Lerp (Vector2f, Vector2f, float)
// Lerp test with factor zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, lerp_with_factor_zero)
{
    auto a        = vector2 { 0.0f, 0.0f };
    auto b        = vector2 { 3.18f, 4.25f };
    auto t        = 0.0f;
    auto expected = vector2::zero();
    auto actual   = vector::lerp(a, b, t);

    EXPECT_EQ(expected, actual);
}

// A test for Lerp (Vector2f, Vector2f, float)
// Lerp test with factor one
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, lerp_with_factor_one)
{
    auto a        = vector2 { 0.0f, 0.0f };
    auto b        = vector2 { 3.18f, 4.25f };
    auto t        = 1.0f;
    auto expected = vector2 { 3.18f, 4.25f };
    auto actual   = vector::lerp(a, b, t);

    EXPECT_EQ(expected, actual);
}

// A test for Lerp (Vector2f, Vector2f, float)
// Lerp test with factor > 1
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, lerp_with_factor_greater_than_one)
{
    auto a        = vector2 { 0.0f, 0.0f };
    auto b        = vector2 { 3.18f, 4.25f };
    auto t        = 2.0f;
    auto expected = b * 2.0f;
    auto actual   = vector::lerp(a, b, t);

    EXPECT_EQ(expected, actual);
}

// A test for Lerp (Vector2f, Vector2f, float)
// Lerp test with factor < 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, lerp_with_factor_less_than_zero)
{
    auto a        = vector2 { 0.0f, 0.0f };
    auto b        = vector2 { 3.18f, 4.25f };
    auto t        = -2.0f;
    auto expected = -(b * 2.0f);
    auto actual   = vector::lerp(a, b, t);

    EXPECT_EQ(expected, actual);
}

// A test for Lerp (Vector2f, Vector2f, float)
// Lerp test with special float value
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, lerp_with_special_float_value)
{
    auto a      = vector2 { 45.67f, 90.0f };
    auto b      = vector2 { positive_infinity<>, negative_infinity<> };
    auto t      = 0.408f;
    auto actual = vector::lerp(a, b, t);

    EXPECT_TRUE(is_positive_infinity(actual.x));
    EXPECT_TRUE(is_negative_infinity(actual.y));
}

// A test for Lerp (Vector2f, Vector2f, float)
// Lerp test from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, lerp_from_same_point)
{
    auto a        = vector2 { 1.0f, 2.0f };
    auto b        = vector2 { 1.0f, 2.0f };
    auto t        = 0.5f;
    auto expected = vector2 { 1.0f, 2.0f };
    auto actual   = vector::lerp(a, b, t);

    EXPECT_EQ(expected, actual);
}

// A test for Transform(Vector2f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, transform)
{
    auto v = vector2 { 1.0f, 2.0f };
    auto m = matrix::create_rotation_x(static_cast<radians>(degrees(30.0f)))
           * matrix::create_rotation_y(static_cast<radians>(degrees(30.0f)))
           * matrix::create_rotation_z(static_cast<radians>(degrees(30.0f)));

    m.m41 = 10.0f;
    m.m42 = 20.0f;
    m.m43 = 30.0f;

    auto expected = vector2 { 10.316987f, 22.183012f };
    auto actual   = vector::transform(v, m);

    EXPECT_EQ(expected, actual);
}

// A test for TransformNormal (Vector2f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, transform_normal)
{
    auto v = vector2 { 1.0f, 2.0f };
    auto m = matrix::create_rotation_x(static_cast<radians>(degrees(30.0f)))
           * matrix::create_rotation_y(static_cast<radians>(degrees(30.0f)))
           * matrix::create_rotation_z(static_cast<radians>(degrees(30.0f)));

    m.m41 = 10.0f;
    m.m42 = 20.0f;
    m.m43 = 30.0f;

    auto expected = vector2 { 0.3169873f, 2.18301272f };
    auto actual   = vector::transform_normal(v, m);

    EXPECT_EQ(expected, actual);
}

// A test for Normalize (Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, normalize)
{
    auto a        = vector2 { 2.0f, 3.0f };
    auto expected = vector2 { 0.554700196225229122018341733457f, 0.8320502943378436830275126001855f };
    auto actual   = vector::normalize(a);

    EXPECT_EQ(expected, actual);
}

// A test for Normalize (Vector2f)
// Normalize zero length vector
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, normalize_zero_length_vector)
{
    vector2 a; // no parameter, default to 0.0f
    vector2 actual = vector::normalize(a);

    EXPECT_TRUE(is_nan(actual.x) && is_nan(actual.y));
}

// A test for Normalize (Vector2f)
// Normalize infinite length vector
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, normalize_infinite_length_vector)
{
    auto a        = vector2 { max_value<>, max_value<> };
    auto actual   = vector::normalize(a);
    auto expected = vector2 { 0, 0 };

    EXPECT_EQ(expected, actual);
}

// A test for operator - (Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, unary_negation)
{
    auto a        = vector2 {  1.0f,  2.0f };
    auto expected = vector2 { -1.0f, -2.0f };
    auto actual   = -a;

    EXPECT_EQ(expected, actual);
}

// A test for operator - (Vector2f)
// negate test with special float value
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, unary_negation_with_infinity_values)
{
    auto a      = vector2 { positive_infinity<>, negative_infinity<> };
    auto actual = -a;

    EXPECT_TRUE(is_negative_infinity(actual.x));
    EXPECT_TRUE(is_positive_infinity(actual.y));
}

// A test for operator - (Vector2f)
// negate test with special float value
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, unary_negation_with_nan_value)
{
    auto a      = vector2 { nan<>, 0.0f };
    auto actual = -a;

    EXPECT_TRUE(is_nan(actual.x));
    EXPECT_EQ(0.0f, actual.y);
}

// A test for operator - (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, subtraction)
{
    auto a        = vector2 {  1.0f, 3.0f };
    auto b        = vector2 {  2.0f, 1.5f };
    auto expected = vector2 { -1.0f, 1.5f };
    auto actual   = a - b;

    EXPECT_EQ(expected, actual);
}

// A test for operator * (Vector2f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, multiply)
{
    auto a        = vector2 { 2.0f, 3.0f };
    auto factor   = 2.0f;
    auto expected = vector2 { 4.0f, 6.0f };
    auto actual   = a * factor;

    EXPECT_EQ(expected, actual);
}

// A test for operator * (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, multiply1)
{
    auto a        = vector2 { 2.0f, 3.0f };
    auto b        = vector2 { 4.0f, 5.0f };
    auto expected = vector2 { 8.0f, 15.0f };
    auto actual   = a * b;

    EXPECT_EQ(expected, actual);
}

// A test for operator / (Vector2f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, division)
{
    auto a        = vector2 { 2.0f, 3.0f };
    auto div      = 2.0f;
    auto expected = vector2 { 1.0f, 1.5f };
    auto actual   = a / div;

    EXPECT_EQ(expected, actual);
}

// A test for operator / (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, division1)
{
    auto a        = vector2 { 2.0f, 3.0f };
    auto b        = vector2 { 4.0f, 5.0f };
    auto expected = vector2 { 2.0f / 4.0f, 3.0f / 5.0f };
    auto actual   = a / b;

    EXPECT_EQ(expected, actual);
}

// A test for operator / (Vector2f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, division2)
{
    auto a      = vector2 { -2.0f, 3.0f };
    auto div    = 0.0f;
    auto actual = a / div;

    EXPECT_TRUE(is_negative_infinity(actual.x));
    EXPECT_TRUE(is_positive_infinity(actual.y));
}

// A test for operator / (Vector2f, Vector2f)
// Divide by zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, division_by_zero)
{
    auto a      = vector2 { 0.047f, -3.0f };
    auto b      = vector2 { };
    auto actual = a / b;

    EXPECT_TRUE(is_positive_infinity(actual.x));
    EXPECT_TRUE(is_negative_infinity(actual.y));
}

// A test for operator + (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, addition)
{
    auto a        = vector2 { 1.0f, 2.0f };
    auto b        = vector2 { 3.0f, 4.0f };
    auto expected = vector2 { 4.0f, 6.0f };
    auto actual   = a + b;

    EXPECT_EQ(expected, actual);
}

// A test for Vector2f (float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, constructor)
{
    auto x      = 1.0f;
    auto y      = 2.0f;
    auto target = vector2 { x, y };

    EXPECT_TRUE(x == target.x);
    EXPECT_TRUE(y == target.y);
}

// A test for Vector2f ()
// Constructor with no parameter
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, default_constructor)
{
    auto target = vector2 { };

    EXPECT_EQ(0.0f, target.x);
    EXPECT_EQ(0.0f, target.y);
}

// A test for Vector2f (float, float)
// Constructor with special floating values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, constructor_with_special_values)
{
    auto target = vector2 { nan<>, max_value<> };

    EXPECT_TRUE(is_nan(target.x));
    EXPECT_EQ(max_value<>, target.y);
}

// A test for Vector2f (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, constructor4)
{
    auto value    = 1.0f;
    auto target   = vector2 { value };
    auto expected = vector2 { value, value };

    EXPECT_EQ(expected, target);

    value    = 2.0f;
    target   = vector2 { value };
    expected = vector2 { value, value };

    EXPECT_EQ(expected, target);
}

// A test for negate (Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, negate)
{
    auto a        = vector2 {  1.0f,  2.0f };
    auto expected = vector2 { -1.0f, -2.0f };
    auto actual   = vector::negate(a);

    EXPECT_EQ(expected, actual);
}

// A test for operator != (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, inequality)
{
    auto a = vector2 { 1.0f, 2.0f };
    auto b = vector2 { 1.0f, 2.0f };

    // case 1: compare between same values
    bool expected = false;
    bool actual   = a != b;

    EXPECT_EQ(expected, actual);

    // case 2: compare between different values
    b        = vector2 { 10.0f, 2.0f };
    expected = true;
    actual   = a != b;

    EXPECT_EQ(expected, actual);
}

// A test for operator == (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, equality)
{
    auto a = vector2 { 1.0f, 2.0f };
    auto b = vector2 { 1.0f, 2.0f };

    // case 1: compare between same values
    bool expected = true;
    bool actual   = a == b;

    EXPECT_EQ(expected, actual);

    // case 2: compare between different values
    b        = vector2 { 10.0f, 2.0f };
    expected = false;
    actual   = a == b;

    EXPECT_EQ(expected, actual);
}

// A test for UnitX
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, unit_x)
{
    auto actual = vector2 { 1.0f, 0.0f };

    EXPECT_EQ(vector2::unit_x(), actual);
}

// A test for UnitY
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, unit_y)
{
    auto actual = vector2 { 0.0f, 1.0f };

    EXPECT_EQ(vector2::unit_y(), actual);
}

// A test for One
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, one)
{
    auto actual = vector2 { 1.0f, 1.0f };

    EXPECT_EQ(vector2::one(), actual);
}

// A test for Zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, zero)
{
    auto actual = vector2 { 0.0f, 0.0f };

    EXPECT_EQ(vector2::zero(), actual);
}

// A test for Vector2f comparison involving NaN values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, equals)
{
    auto a = vector2 { nan<>, 0.0f  };
    auto b = vector2 { 0    , nan<> };

    EXPECT_FALSE(a == vector2::zero());
    EXPECT_FALSE(b == vector2::zero());

    EXPECT_TRUE(a != vector2::zero());
    EXPECT_TRUE(b != vector2::zero());
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, abs)
{
    auto v1 = vector2 { -2.5f, 2.0f };
    auto v3 = vector::abs(vector2 { 0.0f, negative_infinity<> });
    auto v  = vector::abs(v1);

    EXPECT_EQ(2.5f, v.x);
    EXPECT_EQ(2.0f, v.y);
    EXPECT_EQ(0.0f, v3.x);
    EXPECT_EQ(positive_infinity<>, v3.y);
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, sqrt)
{
    auto v1 = vector2 { -2.5f, 2.0f };
    auto v2 = vector2 { 5.5f, 4.5f };

    EXPECT_EQ(2, static_cast<std::int32_t>(vector::square_root(v2).x));
    EXPECT_EQ(2, static_cast<std::int32_t>(vector::square_root(v2).y));
    EXPECT_TRUE(is_nan(vector::square_root(v1).x));
}

// A test for Reflect (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, reflect)
{
    vector2 a = vector::normalize(vector2 { 1.0f, 1.0f });

    // Reflect on XZ plane.
    vector2 n        { 0.0f, 1.0f };
    vector2 expected {  a.x, -a.y };
    vector2 actual   = vector::reflect(a, n);
    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Reflect on XY plane.
    n        = { 0.0f, 0.0f };
    expected = {  a.x,  a.y };
    actual   = vector::reflect(a, n);
    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Reflect on YZ plane.
    n        = { 1.0f, 0.0f };
    expected = { -a.x,  a.y };
    actual   = vector::reflect(a, n);
    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Reflect (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, reflect1)
{
    vector2 n = vector::normalize(vector2 { 0.45f, 1.28f });
    vector2 a = n;

    vector2 expected = -n;
    vector2 actual   = vector::reflect(a, n);
    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Reflect (Vector2f, Vector2f)
// Reflection when normal and source are negation
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, reflection_when_normal_and_source_are_negation)
{
    vector2 n = vector::normalize(vector2 { 0.45f, 1.28f });
    vector2 a = -n;

    vector2 expected = n;
    vector2 actual = vector::reflect(a, n);
    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (Vector2f, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, transform_by_quaternion)
{
    vector2 v { 1.0f, 2.0f };
    matrix4 m = matrix::create_rotation_x(static_cast<radians>(degrees(30.0f)))
              * matrix::create_rotation_y(static_cast<radians>(degrees(30.0f)))
              * matrix::create_rotation_z(static_cast<radians>(degrees(30.0f)));
    quaternion q = quat::create_from_rotation_matrix(m);

    vector2 expected = vector::transform(v, m);
    vector2 actual   = vector::transform(v, q);
    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (Vector2f, Quaternion)
// Transform Vector2f with zero quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, transform_by_zero_quaternion)
{
    vector2     v        = { 1.0f, 2.0f };
    vector2     expected = v;
    quaternion  q;

    vector2 actual = vector::transform(v, q);
    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (Vector2f, Quaternion)
// Transform Vector2f with identity quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector2_test, transform_by_identity_quaternion)
{
    vector2    v        = { 1.0f, 2.0f };
    vector2    expected = v;
    quaternion q        = quaternion::identity();

    vector2 actual = vector::transform(v, q);
    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

TEST_F(basic_vector2_test, size_of)
{
    EXPECT_TRUE( 8 == sizeof(vector2));
    EXPECT_TRUE( 8 == sizeof(vector2i));
    EXPECT_TRUE( 8 == sizeof(vector2u));
    EXPECT_TRUE(16 == sizeof(vector2d));
}
