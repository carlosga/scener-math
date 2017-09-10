// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "basic_vector3_test.hpp"

#include "equality_helper.hpp"

using namespace scener::math;

TEST_F(basic_vector3_test, default_constructor)
{
    vector3 vector;

    // vec3 is equal to (0.0, 0.0, 0.0)
    EXPECT_EQ(0.0f, vector.x);
    EXPECT_EQ(0.0f, vector.y);
    EXPECT_EQ(0.0f, vector.z);
}

TEST_F(basic_vector3_test, individual_coordinates_constructor)
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;

    vector3 vector { x, y, z };

    // vec3 is equal to (20.0, 30.0, 40.0)
    EXPECT_EQ(x, vector.x);
    EXPECT_EQ(y, vector.y);
    EXPECT_EQ(z, vector.z);
}

TEST_F(basic_vector3_test, indexer)
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;

    vector3 vector { x, y, z };

    // vec3 is equal to (20.0, 30.0, 40.0)
    EXPECT_EQ(x, vector[0]);
    EXPECT_EQ(y, vector[1]);
    EXPECT_EQ(z, vector[2]);
}

TEST_F(basic_vector3_test, x_coordinate)
{
    const float x = 20.0f;
    const float y = 30.0f;
    const float z = 40.0f;

    vector3 vector { x, y, z };

    // vec3 is equal to (20.0, 30.0, 40.0)
    EXPECT_EQ(x, vector.x);
}

TEST_F(basic_vector3_test, y_coordinate)
{
    const float x = 20.0f;
    const float y = 30.0f;
    const float z = 40.0f;

    vector3 vector = { x, y, z };

    // vec3 is equal to (20.0, 30.0, 40.0)
    EXPECT_EQ(y, vector.y);
}

TEST_F(basic_vector3_test, z_coordinate)
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;

    vector3 vector { x, y, z };

    // vec3 is equal to (20.0, 30.0, 40.0)
    EXPECT_EQ(z, vector.z);
}

TEST_F(basic_vector3_test, length)
{
    vector3 vector { 20.0f, 30.0f, 40.0f };

    // length is approximately equal to 53.8516
    EXPECT_EQ(53.8516464f, vector::length(vector));
}

TEST_F(basic_vector3_test, length_squared)
{
    vector3 vector { 20.0f, 30.0f, 40.0f };

    // length is approximately equal to 2900
    EXPECT_EQ(2900.0f, vector::length_squared(vector));
}

TEST_F(basic_vector3_test, cross)
{
    auto crossProduct = vector::cross({ 20.0f, 30.0f, 40.0f }, { 45.0f, 70.0f, 80.0f });

    // crossProduct is equal to (-400, 200, 50)
    EXPECT_EQ(-400.0f, crossProduct.x);
    EXPECT_EQ(200.0f , crossProduct.y);
    EXPECT_EQ(50.0f  , crossProduct.z);
}

TEST_F(basic_vector3_test, dot_product)
{
    auto dotProduct = vector::dot(vector3 { 20.0f, 30.0f, 40.0f }, vector3 { 45.0f, 70.0f, 80.0f });

    EXPECT_EQ(6200.0f, dotProduct);
}

TEST_F(basic_vector3_test, angle_between)
{
    auto angle = vector::angle_between(vector3 { 20.0f, 30.0f, 40.0f }, vector3 { 45.0f, 70.0f, 80.0f });

    // angleBetween is approximately equal to 4.15128803
    EXPECT_EQ(0.0724536479f, angle.value);
}

TEST_F(basic_vector3_test, addition)
{
    auto vector1 = vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = vector3 { 45.0f, 70.0f, 80.0f };
    auto result  = vector1 + vector2;

    // vectorResult is equal to (65, 100, 120)
    EXPECT_EQ(65.0f , result.x);
    EXPECT_EQ(100.0f, result.y);
    EXPECT_EQ(120.0f, result.z);
}

TEST_F(basic_vector3_test, subtraction)
{
    auto vector1 = vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = vector3 { 45.0f, 70.0f, 80.0f };
    auto result  = vector1 - vector2;

    // vector Result is equal to (-25, -40, -40)
    EXPECT_EQ(-25.0f, result.x);
    EXPECT_EQ(-40.0f, result.y);
    EXPECT_EQ(-40.0f, result.z);
}

TEST_F(basic_vector3_test, multiplication)
{
    auto vector1 = vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = vector3 { 45.0f, 70.0f, 80.0f };
    auto result  = vector1 * vector2;

    // vector Result is equal to (800, 2100, 3200)
    EXPECT_EQ(900.0f , result.x);
    EXPECT_EQ(2100.0f, result.y);
    EXPECT_EQ(3200.0f, result.z);
}

TEST_F(basic_vector3_test, addition_assignment)
{
    auto vector1 = vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = vector3 { 45.0f, 70.0f, 80.0f };

    vector2 += vector1;

    // vector Result is equal to (65, 100, 120)
    EXPECT_EQ(65.0f , vector2.x);
    EXPECT_EQ(100.0f, vector2.y);
    EXPECT_EQ(120.0f, vector2.z);
}

TEST_F(basic_vector3_test, subtraction_assignment)
{
    auto vector1 = vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = vector3 { 45.0f, 70.0f, 80.0f };

    vector2 -= vector1;

    // vector Result is equal to (25, 40, 40)
    EXPECT_EQ(25.0f, vector2.x);
    EXPECT_EQ(40.0f, vector2.y);
    EXPECT_EQ(40.0f, vector2.z);
}

TEST_F(basic_vector3_test, multiplication_assignment)
{
    auto vector1 = vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = vector3 { 45.0f, 70.0f, 80.0f };

    vector2 *= vector1;

    // vector Result is equal to (800, 2100, 3200)
    EXPECT_EQ(900.0f , vector2.x);
    EXPECT_EQ(2100.0f, vector2.y);
    EXPECT_EQ(3200.0f, vector2.z);
}

TEST_F(basic_vector3_test, scalar_multplication_assignment)
{
    auto vector = vector3 { 20.0f, 30.0f, 40.0f };

    vector *= 75.0f;

    // vector Result is equal to (1500, 2250, 3000)
    EXPECT_EQ(1500.0f, vector.x);
    EXPECT_EQ(2250.0f, vector.y);
    EXPECT_EQ(3000.0f, vector.z);
}

TEST_F(basic_vector3_test, matrix_multiplication)
{
    auto vector = vector3 { 20.0f, 30.0f, 40.0f };
    auto matrix = matrix4 { 10.0f, 10.0f, 10.0f, 0.0f
                          , 20.0f, 20.0f, 20.0f, 0.0f
                          , 30.0f, 30.0f, 30.0f, 0.0f
                          , 5.0f , 10.0f, 15.0f, 1.0f };

    auto vectorResult = (vector * matrix);

    // vector Result is equal to (2005, 2010, 2015)
    EXPECT_EQ(2005.0f, vectorResult.x);
    EXPECT_EQ(2010.0f, vectorResult.y);
    EXPECT_EQ(2015.0f, vectorResult.z);
}

TEST_F(basic_vector3_test, transform)
{
    auto vector = vector3 { 20.0f, 30.0f, 40.0f };
    auto matrix = matrix4 { 10.0f, 10.0f, 10.0f, 0.0f
                          , 20.0f, 20.0f, 20.0f, 0.0f
                          , 30.0f, 30.0f, 30.0f, 0.0f
                          , 5.0f , 10.0f, 15.0f, 1.0f };

    auto result = vector::transform(vector, matrix);

    // vector Result is equal to (2005, 2010, 2015)
    EXPECT_EQ(2005.0f, result.x);
    EXPECT_EQ(2010.0f, result.y);
    EXPECT_EQ(2015.0f, result.z);
}

TEST_F(basic_vector3_test, transform_normal)
{
    auto vector = vector3 { 20.0f, 30.0f, 40.0f };
    auto matrix = matrix4 { 10.0f, 10.0f, 10.0f, 0.0f
                          , 20.0f, 20.0f, 20.0f, 0.0f
                          , 30.0f, 30.0f, 30.0f, 0.0f
                          , 5.0f , 10.0f, 15.0f, 1.0f };

    auto result = vector::transform_normal(vector, matrix);

    // vector Result is equal to (2000, 2000, 2000)
    EXPECT_EQ(2000.0f, result.x);
    EXPECT_EQ(2000.0f, result.y);
    EXPECT_EQ(2000.0f, result.z);
}

TEST_F(basic_vector3_test, lerp)
{
    auto vector1 = vector3 { 5.0f, 10.0f, 50.0f };
    auto vector2 = vector3 { 0.0f, -20.0f, 100.0f };
    auto result  = vector::lerp(vector1, vector2, 0.4f);

    EXPECT_EQ(3.0f , result.x);
    EXPECT_EQ(-2.0f, result.y);
    EXPECT_EQ(70.0f, result.z);
}

// A test for Cross (vec3f, vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, cross1)
{
    auto a        = vector3 { 1.0f, 0.0f, 0.0f };
    auto b        = vector3 { 0.0f, 1.0f, 0.0f };
    auto expected = vector3 { 0.0f, 0.0f, 1.0f };
    auto actual   = vector::cross(a, b);

    EXPECT_EQ(expected, actual);
}

// A test for Cross (vec3f, vec3f)
// Cross test of the same vector
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, cross_with_same_vector)
{
    auto a        = vector3 { 0.0f, 1.0f, 0.0f };
    auto b        = vector3 { 0.0f, 1.0f, 0.0f };
    auto expected = vector3 { 0.0f, 0.0f, 0.0f };
    auto actual   = vector::cross(a, b);

    EXPECT_EQ(expected, actual);
}

// A test for Distance (vec3f, vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, distance)
{
    auto a = vector3 { 1.0f, 2.0f, 3.0f };
    auto b = vector3 { 4.0f, 5.0f, 6.0f };

    auto expected = std::sqrt(27.0f);
    auto actual   = vector::distance(a, b);

    EXPECT_EQ(expected, actual);
}

// A test for Distance (vec3f, vec3f)
// Distance from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, distance_from_the_same_point)
{
    auto a = vector3 { 1.051f, 2.05f, 3.478f };
    auto b = vector3 { { 1.051f, 0.0f }, 1.0f };

    b.y = 2.05f;
    b.z = 3.478f;

    auto actual = vector::distance(a, b);

    EXPECT_EQ(0.0f, actual);
}

// A test for DistanceSquared (vec3f, vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, distance_squared)
{
    auto a = vector3 { 1.0f, 2.0f, 3.0f };
    auto b = vector3 { 4.0f, 5.0f, 6.0f };

    auto expected = 27.0f;
    auto actual   = vector::distance_squared(a, b);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Dot (vec3f, vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, dot)
{
    auto a = vector3 { 1.0f, 2.0f, 3.0f };
    auto b = vector3 { 4.0f, 5.0f, 6.0f };

    auto expected = 32.0f;
    auto actual   = vector::dot(a, b);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Dot (vec3f, vec3f)
// Dot test for perpendicular vector
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, dot_for_perpendicular_vector)
{
    auto a = vector3 { 1.55f, 1.55f, 1 };
    auto b = vector3 { 2.5f, 3, 1.5f };
    auto c = vector::cross(a, b);

    auto expected = 0.0f;
    auto actual1  = vector::dot(a, c);
    auto actual2  = vector::dot(b, c);

    EXPECT_TRUE(equality_helper::equal(expected, actual1));
    EXPECT_TRUE(equality_helper::equal(expected, actual2));
}

// A test for Length ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, length2)
{
    auto a        = vector2 { 1.0f, 2.0f };
    auto z        = 3.0f;
    auto target   = vector3 { a, z };
    auto expected = std::sqrt(14.0f);
    auto actual   = vector::length(target);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Length ()
// Length test where length is zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, length_zero)
{
    vector3 target;
    auto expected = 0.0f;
    auto actual   = vector::length(target);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for LengthSquared ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, length_squared2)
{
    auto a        = vector2 { 1.0f, 2.0f };
    auto z        = 3.0f;
    auto target   = vector3 { a, z };
    auto expected = 14.0f;
    auto actual   = vector::length_squared(target);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Min (vec3f, vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, min)
{
    auto a        = vector3 { -1.0f, 4.0f, -3.0f };
    auto b        = vector3 { 2.0f , 1.0f, -1.0f };
    auto expected = vector3 { -1.0f, 1.0f, -3.0f };
    auto actual   = vector::min(a, b);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Max (vec3f, vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, max)
{
    auto a        = vector3 { -1.0f, 4.0f, -3.0f };
    auto b        = vector3 { 2.0f , 1.0f, -1.0f };
    auto expected = vector3 { 2.0f , 4.0f, -1.0f };
    auto actual   = vector::max(a, b);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, min_max_code_coverage)
{
    auto min = vector3::zero();
    auto max = vector3::one();

    vector3 actual;

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

// A test for Lerp (vec3f, vec3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, lerp1)
{
    auto a = vector3 { 1.0f, 2.0f, 3.0f };
    auto b = vector3 { 4.0f, 5.0f, 6.0f };
    auto t = 0.5f;

    auto expected = vector3 { 2.5f, 3.5f, 4.5f };
    auto actual   = vector::lerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Lerp (vec3f, vec3f, float)
// Lerp test with factor zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, lerp_with_factor_zero)
{
    auto a = vector3 { 1.0f, 2.0f, 3.0f };
    auto b = vector3 { 4.0f, 5.0f, 6.0f };
    auto t = 0.0f;

    auto expected = vector3 { 1.0f, 2.0f, 3.0f };
    auto actual   = vector::lerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Lerp (vec3f, vec3f, float)
// Lerp test with factor one
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, lerp_with_factor_one)
{
    auto a = vector3 { 1.0f, 2.0f, 3.0f };
    auto b = vector3 { 4.0f, 5.0f, 6.0f };
    auto t = 1.0f;

    auto expected = vector3 { 4.0f, 5.0f, 6.0f };
    auto actual   = vector::lerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Lerp (vec3f, vec3f, float)
// Lerp test with factor > 1
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, lerp_with_factor_greater_than_one)
{
    auto a = vector3 { 0.0f, 0.0f, 0.0f };
    auto b = vector3 { 4.0f, 5.0f, 6.0f };
    auto t = 2.0f;

    auto expected = vector3 { 8.0f, 10.0f, 12.0f };
    auto actual   = vector::lerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Lerp (vec3f, vec3f, float)
// Lerp test with factor < 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, lerp_with_factor_less_than_zero)
{
    auto a = vector3 { 0.0f, 0.0f, 0.0f };
    auto b = vector3 { 4.0f, 5.0f, 6.0f };
    auto t = -2.0f;

    auto expected = vector3 { -8.0f, -10.0f, -12.0f };
    auto actual   = vector::lerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Lerp (vec3f, vec3f, float)
// Lerp test from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, lerp_from_the_same_point)
{
    auto a = vector3 { 1.68f, 2.34f, 5.43f };
    auto b = a;
    auto t = 0.18f;

    auto expected = vector3 { 1.68f, 2.34f, 5.43f };
    auto actual   = vector::lerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Reflect (vec3f, vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, reflect)
{
    auto a = vector::normalize(vector3 { 1.0f, 1.0f, 1.0f });

    // Reflect on XZ plane.
    auto n        = vector3 { 0.0f, 1.0f, 0.0f };
    auto expected = vector3 { a.x, -a.y, a.z };
    auto actual   = vector::reflect(a, n);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Reflect on XY plane.
    n        = vector3 { 0.0f, 0.0f, 1.0f };
    expected = vector3(a.x, a.y, -a.z);
    actual   = vector::reflect(a, n);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Reflect on YZ plane.
    n        = vector3 { 1.0f, 0.0f, 0.0f };
    expected = vector3 { -a.x, a.y, a.z };
    actual   = vector::reflect(a, n);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Reflect (vec3f, vec3f)
// Reflection when normal and source are the same
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, reflect_when_normal_and_source_are_the_same)
{
    auto n        = vector::normalize(vector3 { 0.45f, 1.28f, 0.86f });
    auto a        = n;
    auto expected = -n;
    auto actual   = vector::reflect(a, n);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Reflect (vec3f, vec3f)
// Reflection when normal and source are negation
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, reflect_when_normal_and_source_are_negation)
{
    auto n        = vector::normalize(vector3 { 0.45f, 1.28f, 0.86f });
    auto a        = -n;
    auto expected = n;
    auto actual   = vector::reflect(a, n);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Reflect (vec3f, vec3f)
// Reflection when normal and source are perpendicular (a dot n = 0)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, reflect_when_normal_and_source_are_perpendicular)
{
    auto n    = vector3 { 0.45f, 1.28f, 0.86f };
    auto temp = vector3 { 1.28f, 0.45f, 0.01f };

    // find a perpendicular vector of n
    auto a = vector::cross(temp, n);

    auto expected = a;
    auto actual   = vector::reflect(a, n);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform(vec3f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, transform1)
{
    auto    v = vector3 { 1.0f, 2.0f, 3.0f };
    radians a = degrees { 30.0f };
    auto    m = matrix::create_rotation_x(a)
              * matrix::create_rotation_y(a)
              * matrix::create_rotation_z(a);

    m.m41 = 10.0f;
    m.m42 = 20.0f;
    m.m43 = 30.0f;

    auto expected = vector3 { 12.191987f, 21.533493f, 32.616024f };
    auto actual   = vector::transform(v, m);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for clamp (vec3f, vec3f, vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, clamp)
{
    auto a   = vector3 { 0.5f, 0.3f, 0.33f };
    auto min = vector3 { 0.0f, 0.1f, 0.13f };
    auto max = vector3 { 1.0f, 1.1f, 1.13f };

    // Normal case.
    // Case N1: specfied value is in the range.
    auto expected = vector3 { 0.5f, 0.3f, 0.33f };
    auto actual   = vector::clamp(a, min, max);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Normal case.
    // Case N2: specfied value is bigger than max value.
    a        = vector3 { 2.0f, 3.0f, 4.0f };
    expected = max;
    actual   = vector::clamp(a, min, max);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Case N3: specfied value is smaller than max value.
    a        = vector3 { -2.0f, -3.0f, -4.0f };
    expected = min;
    actual   = vector::clamp(a, min, max);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Case N4: combination case.
    a        = vector3 {   -2.0f,  0.5f,    4.0f };
    expected = vector3 { min.x, a.y, max.z };
    actual   = vector::clamp(a, min, max);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // User specfied min value is bigger than max value.
    max = vector3 { 0.0f, 0.1f, 0.13f };
    min = vector3 { 1.0f, 1.1f, 1.13f };

    // Case W1: specfied value is in the range.
    a        = vector3 { 0.5f, 0.3f, 0.33f };
    expected = min;
    actual   = vector::clamp(a, min, max);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Normal case.
    // Case W2: specfied value is bigger than max and min value.
    a        = vector3 { 2.0f, 3.0f, 4.0f };
    expected = min;
    actual   = vector::clamp(a, min, max);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Case W3: specfied value is smaller than min and max value.
    a        = vector3 { -2.0f, -3.0f, -4.0f };
    expected = min;
    actual   = vector::clamp(a, min, max);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for TransformNormal (vec3f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, transform_normal1)
{
    auto v = vector3 { 1.0f, 2.0f, 3.0f };
    auto a = radians(30_deg);
    auto m = matrix::create_rotation_x(a)
           * matrix::create_rotation_y(a)
           * matrix::create_rotation_z(a);

    m.m41 = 10.0f;
    m.m42 = 20.0f;
    m.m43 = 30.0f;

    auto expected = vector3 { 2.19198728f, 1.53349364f, 2.61602545f };
    auto actual   = vector::transform_normal(v, m);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (vec3f, quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, transform_by_quaternion)
{
    auto v = vector3 { 1.0f, 2.0f, 3.0f };
    auto a = radians(30_deg);
    auto m = matrix::create_rotation_x(a)
           * matrix::create_rotation_y(a)
           * matrix::create_rotation_z(a);
    auto q = quat::create_from_rotation_matrix(m);

    auto expected = vector::transform(v, m);
    auto actual   = vector::transform(v, q);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (vec3f, quaternion)
// Transform vec3 with zero quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, transform_by_zero_quaternion)
{
    auto v        = vector3 { 1.0f, 2.0f, 3.0f };
    auto q        = quaternion {};
    auto expected = v;
    auto actual   = vector::transform(v, q);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transform (vec3f, quaternion)
// Transform vec3 with identity quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, transform_by_identity_quaternion)
{
    auto v        = vector3 { 1.0f, 2.0f, 3.0f };
    auto q        = quaternion::identity();
    auto expected = v;

    auto actual = vector::transform(v, q);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

TEST_F(basic_vector3_test, normalize)
{
    auto actual = vector::normalize(vector3 { 20.0f, 30.0f, 40.0f });

    // vector Result is equal to (0.37139, 0.55709, 0.74278)
    EXPECT_TRUE(0.3713907f   == actual.x);
    EXPECT_TRUE(0.557086051f == actual.y);
    EXPECT_TRUE(0.742781401f == actual.z);
}

// A test for Normalize (vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, normalize1)
{
    auto a        = vector3 { 1.0f, 2.0f, 3.0f };
    auto expected = vector3 { 0.26726124191242438468455348087975f
                         , 0.53452248382484876936910696175951f
                         , 0.80178372573727315405366044263926f };

    auto actual = vector::normalize(a);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Normalize (vec3f)
// Normalize vector of length one
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, normalize_vector_of_length_one)
{
    auto a = vector3 { 1.0f, 0.0f, 0.0f };

    auto expected = vector3 { 1.0f, 0.0f, 0.0f };
    auto actual   = vector::normalize(a);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Normalize (vec3f)
// Normalize vector of length zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, normalize_vector_of_length_zero)
{
    auto a      = vector3 { 0.0f, 0.0f, 0.0f };
    auto actual = vector::normalize(a);

    EXPECT_TRUE(is_nan(actual.x));
    EXPECT_TRUE(is_nan(actual.y));
    EXPECT_TRUE(is_nan(actual.z));
}

// A test for operator - (vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, unary_negation)
{
    auto a        = vector3 {  1.0f,  2.0f,  3.0f };
    auto expected = vector3 { -1.0f, -2.0f, -3.0f };
    auto actual   = -a;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, unary_Negation_with_special_values)
{
    auto a = -vector3 { NaN<>, positive_infinity<>, negative_infinity<> };
    auto b = -vector3 { 0.0f, 0.0f, 0.0f };

    EXPECT_TRUE(is_nan(a.x));
    EXPECT_TRUE(is_negative_infinity(a.y));
    EXPECT_TRUE(is_positive_infinity(a.z));
    EXPECT_EQ(0.0f, b.x);
    EXPECT_EQ(0.0f, b.y);
    EXPECT_EQ(0.0f, b.z);
}

// A test for operator - (vec3f, vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, subtraction1)
{
    auto a        = vector3 { 4.0f, 2.0f, 3.0f };
    auto b        = vector3 { 1.0f, 5.0f, 7.0f };
    auto expected = vector3 { 3.0f, -3.0f, -4.0f };
    auto actual   = a - b;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

TEST_F(basic_vector3_test, scalar_multiplication)
{
    auto vector = vector3 { 20.0f, 30.0f, 40.0f };
    auto result = vector * 75.0f;

    // vector Result is equal to (1500, 2250, 3000)
    EXPECT_TRUE(1500.0f == result.x);
    EXPECT_TRUE(2250.0f == result.y);
    EXPECT_TRUE(3000.0f == result.z);
}

// A test for operator * (vec3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, scalar_multiplication1)
{
    auto a        = vector3 { 1.0f, 2.0f, 3.0f };
    auto factor   = 2.0f;
    auto expected = vector3 { 2.0f, 4.0f, 6.0f };
    auto actual   = a * factor;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator * (vec3f, vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, vector_multiplication)
{
    auto a        = vector3 { 1.0f,  2.0f,  3.0f };
    auto b        = vector3 { 4.0f,  5.0f,  6.0f };
    auto expected = vector3 { 4.0f, 10.0f, 18.0f };
    auto actual   = a * b;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator / (vec3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, scalar_division)
{
    auto a        = vector3 { 1.0f, 2.0f, 3.0f };
    auto div      = 2.0f;
    auto expected = vector3 { 0.5f, 1.0f, 1.5f };
    auto actual   = a / div;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator / (vec3f, vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, vector_division)
{
    auto a        = vector3 { 4.0f, 2.0f, 3.0f };
    auto b        = vector3 { 1.0f, 5.0f, 6.0f };
    auto expected = vector3 { 4.0f, 0.4f, 0.5f };
    auto actual   = a / b;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator / (vec3f, float)
// Divide by zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, scalar_division_by_zero)
{
    auto a      = vector3 { -2.0f, 3.0f, max_value<>};
    auto div    = 0.0f;
    auto actual = a / div;

    EXPECT_TRUE(is_negative_infinity(actual.x));
    EXPECT_TRUE(is_positive_infinity(actual.y));
    EXPECT_TRUE(is_positive_infinity(actual.z));
}

// A test for operator / (vec3f, vec3f)
// Divide by zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, vector_division_by_zero)
{
    auto a      = vector3 { 0.047f, -3.0f, negative_infinity<>};
    auto b      = vector3 { };
    auto actual = a / b;

    EXPECT_TRUE(is_positive_infinity(actual.x));
    EXPECT_TRUE(is_negative_infinity(actual.y));
    EXPECT_TRUE(is_negative_infinity(actual.z));
}

// A test for operator + (vec3f, vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, addition1)
{
    auto a = vector3 { 1.0f, 2.0f, 3.0f };
    auto b = vector3 { 4.0f, 5.0f, 6.0f };

    auto expected = vector3 { 5.0f, 7.0f, 9.0f };
    auto actual   = a + b;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for vec3f (float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, constructor)
{
    auto x      = 1.0f;
    auto y      = 2.0f;
    auto z      = 3.0f;
    auto target = vector3 { x, y, z };

    EXPECT_TRUE(equality_helper::equal(target.x, x));
    EXPECT_TRUE(equality_helper::equal(target.y, y));
    EXPECT_TRUE(equality_helper::equal(target.z, z));
}

// A test for vec3f (Vector2f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, constructor1)
{
    auto a      = vector2 { 1.0f, 2.0f };
    auto z      = 3.0f;
    auto target = vector3 { a, z };

    EXPECT_TRUE(equality_helper::equal(target.x, a.x));
    EXPECT_TRUE(equality_helper::equal(target.y, a.y));
    EXPECT_TRUE(equality_helper::equal(target.z, z));
}

// A test for vec3f ()
// Constructor with no parameter
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, constructor2)
{
    auto a = vector3 { };

    EXPECT_EQ(a.x, 0.0f);
    EXPECT_EQ(a.y, 0.0f);
    EXPECT_EQ(a.z, 0.0f);
}

// A test for Vector2f (float, float)
// Constructor with special floating values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, constructor_with_special_float_values)
{
    auto target = vector3 { NaN<>, max_value<> , positive_infinity<> };

    EXPECT_TRUE(is_nan(target.x));
    EXPECT_EQ(max_value<>, target.y);
    EXPECT_TRUE(is_positive_infinity(target.z));
}

TEST_F(basic_vector3_test, negate)
{
    auto actual = vector::negate(vector3 { 20.0f, 30.0f, 40.0f });

    // vector Result is equal to (-20, -30, -40)
    EXPECT_TRUE(-20.0f == actual.x);
    EXPECT_TRUE(-30.0f == actual.y);
    EXPECT_TRUE(-40.0f == actual.z);
}

// A test for negate (vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, negate1)
{
    auto a        = vector3 { 1.0f, 2.0f, 3.0f };
    auto expected = vector3 { -1.0f, -2.0f, -3.0f };
    auto actual   = vector::negate(a);

    EXPECT_EQ(expected, actual);
}

// A test for operator != (vec3f, vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, inequality)
{
    auto a = vector3 { 1.0f, 2.0f, 3.0f };
    auto b = vector3 { 1.0f, 2.0f, 3.0f };

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

// A test for operator == (vec3f, vec3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, equality)
{
    auto a = vector3 { 1.0f, 2.0f, 3.0f };
    auto b = vector3 { 1.0f, 2.0f, 3.0f };

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

// A test for One
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, one)
{
    auto val = vector3 { 1.0f, 1.0f, 1.0f };

    EXPECT_EQ(val, vector3::one());
}

// A test for UnitX
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, unit_x)
{
    auto val = vector3 { 1.0f, 0.0f, 0.0f };

    EXPECT_EQ(val, vector3::unit_x());
}

// A test for UnitY
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, unit_y)
{
    auto val = vector3 { 0.0f, 1.0f, 0.0f };

    EXPECT_EQ(val, vector3::unit_y());
}

// A test for UnitZ
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, unit_z)
{
    auto val = vector3 { 0.0f, 0.0f, 1.0f };

    EXPECT_EQ(val, vector3::unit_z());
}

// A test for Zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, zero)
{
    auto val = vector3 { 0.0f, 0.0f, 0.0f };

    EXPECT_EQ(val, vector3::zero());
}

// A test for vec3f (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, constructor4)
{
    auto value    = 1.0f;
    auto target   = vector3 { value };
    auto expected = vector3 { value, value, value };

    EXPECT_EQ(expected, target);

    value    = 2.0f;
    target   = vector3 { value };
    expected = vector3 { value, value, value };

    EXPECT_EQ(expected, target);
}

// A test for vec3f comparison involving NaN values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, equals_nan)
{
    auto a = vector3 { NaN<>, 0    , 0     };
    auto b = vector3 { 0    , NaN<>, 0     };
    auto c = vector3 { 0    , 0    , NaN<> };

    EXPECT_FALSE(a == vector3::zero());
    EXPECT_FALSE(b == vector3::zero());
    EXPECT_FALSE(c == vector3::zero());

    EXPECT_TRUE(a != vector3::zero());
    EXPECT_TRUE(b != vector3::zero());
    EXPECT_TRUE(c != vector3::zero());
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, abs)
{
    auto v1 = vector3 { -2.5f, 2.0f, 0.5f };
    auto v3 = vector::abs(vector3 { 0.0f, negative_infinity<>, NaN<> });
    auto v  = vector::abs(v1);

    EXPECT_EQ(2.5f, v.x);
    EXPECT_EQ(2.0f, v.y);
    EXPECT_EQ(0.5f, v.z);
    EXPECT_EQ(0.0f, v3.x);
    EXPECT_EQ(positive_infinity<>, v3.y);
    EXPECT_TRUE(is_nan(v3.z));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, sqrt)
{
    auto a = vector3 { -2.5f, 2.0f, 0.5f };
    auto b = vector3 { 5.5f, 4.5f, 16.5f };

    EXPECT_EQ(2, static_cast<std::int32_t>(vector::square_root(b).x));
    EXPECT_EQ(2, static_cast<std::int32_t>(vector::square_root(b).y));
    EXPECT_EQ(4, static_cast<std::int32_t>(vector::square_root(b).z));
    EXPECT_TRUE(is_nan(vector::square_root(a).x));
}

// A test to make sure these types are blittable directly into GPU buffer memory layouts
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, size_of)
{
    EXPECT_TRUE(12 == sizeof(vector3));
    EXPECT_TRUE(12 == sizeof(vector3i));
    EXPECT_TRUE(12 == sizeof(vector3u));
    EXPECT_TRUE(24 == sizeof(vector3d));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_vector3_test, set_fields)
{
    auto v3 = vector3 { 4.0f, 5.0f, 6.0f };

    v3.x = 1.0f;
    v3.y = 2.0f;
    v3.z = 3.0f;

    EXPECT_EQ(1.0f, v3.x);
    EXPECT_EQ(2.0f, v3.y);
    EXPECT_EQ(3.0f, v3.z);

    auto v4 = v3;

    v4.y = 0.5f;
    v4.z = 2.2f;

    EXPECT_EQ(1.0f, v4.x);
    EXPECT_EQ(0.5f, v4.y);
    EXPECT_EQ(2.2f, v4.z);
    EXPECT_EQ(2.0f, v3.y);

    auto before = vector3 { 1.0f, 2.0f, 3.0f };
    auto after  = before;

    after.x = 500.0f;

    EXPECT_NE(before, after);
}
