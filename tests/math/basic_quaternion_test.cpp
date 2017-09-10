// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "basic_quaternion_test.hpp"

#include "equality_helper.hpp"

using namespace scener::math;

TEST_F(basic_quaternion_test, coordinates)
{
    auto q = quaternion { 1.0f, 2.0f, 3.0f, 4.0f };

    EXPECT_EQ(1.0f, q.x);
    EXPECT_EQ(2.0f, q.y);
    EXPECT_EQ(3.0f, q.z);
    EXPECT_EQ(4.0f, q.w);
}

TEST_F(basic_quaternion_test, conjugate)
{
    auto actual = quat::conjugate({ 5.0f, 6.0f, 7.0f, 8.0f });

    EXPECT_EQ(-5.0f, actual.x);
    EXPECT_EQ(-6.0f, actual.y);
    EXPECT_EQ(-7.0f, actual.z);
    EXPECT_EQ( 8.0f, actual.w);
}

TEST_F(basic_quaternion_test, multiplication)
{
    auto q1 = quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto q2 = quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
    auto qr = q1 * q2;

    // quaternion Result is equal to (24, 48, 48, -6)
    EXPECT_EQ(24.0f, qr.x);
    EXPECT_EQ(48.0f, qr.y);
    EXPECT_EQ(48.0f, qr.z);
    EXPECT_EQ(-6.0f, qr.w);
}

TEST_F(basic_quaternion_test, calculate_quaternion_from_axis_angle)
{
    auto result = quat::create_from_axis_angle({ 1.0f, 0.0f, 0.0f }, radians { pi_over_2<> });

    // quaternion Result is equal to (0.707106769, 0, 0, 0.707106769)
    EXPECT_EQ(0.707106769f, result.x);
    EXPECT_EQ(        0.0f, result.y);
    EXPECT_EQ(        0.0f, result.z);
    EXPECT_EQ(0.707106769f, result.w);
}

// A test for Dot (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, dot)
{
    auto a = quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = quaternion { 5.0f, 6.0f, 7.0f, 8.0f };

    auto expected = 70.0f;
    auto actual   = quat::dot(a, b);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Length ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, length)
{
    auto v        = vector3 { 1.0f, 2.0f, 3.0f };
    auto w        = 4.0f;
    auto target   = quaternion { v, w };
    auto expected = 5.477226f;
    auto actual   = quat::length(target);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for LengthSquared ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, length_squared)
{
    auto v        = vector3 { 1.0f, 2.0f, 3.0f };
    auto w        = 4.0f;
    auto target   = quaternion { v, w };
    auto expected = 30.0f;
    auto actual   = quat::length_squared(target);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Lerp (Quaternion, Quaternion, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, lerp)
{
    auto    axis     = vector::normalize(vector3 { 1.0f, 2.0f, 3.0f });
    radians angle1   = degrees(10.0f);
    auto    a        = quat::create_from_axis_angle(axis, angle1);
    radians angle2   = degrees(30.0f);
    auto    b        = quat::create_from_axis_angle(axis, angle2);
    auto    t        = 0.5f;
    radians angle3   = degrees(20.0f);
    auto    expected = quat::create_from_axis_angle(axis, angle3);
    auto    actual   = quat::lerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Case a and b are same.
    expected = a;
    actual   = quat::lerp(a, a, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Lerp (Quaternion, Quaternion, float)
// Lerp test when t = 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, lerp_with_interpolate_zero)
{
    auto    axis     = vector::normalize(vector3 { 1.0f, 2.0f, 3.0f });
    radians angle1   = degrees(10.0f);
    auto    a        = quat::create_from_axis_angle(axis, angle1);
    radians angle2   = degrees(30.0f);
    auto    b        = quat::create_from_axis_angle(axis, angle2);
    auto    t        = 0.0f;
    auto    expected = quaternion { a.x, a.y, a.z, a.w };
    auto    actual   = quat::lerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Lerp (Quaternion, Quaternion, float)
// Lerp test when t = 1
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, lerp_with_interpolate_one)
{
    auto    axis     = vector::normalize(vector3 { 1.0f, 2.0f, 3.0f });
    radians angle1   = degrees(10.0f);
    auto    a        = quat::create_from_axis_angle(axis, angle1);
    radians angle2   = degrees(30.0f);
    auto    b        = quat::create_from_axis_angle(axis, angle2);
    auto    t        = 1.0f;
    auto    expected = quaternion { b.x, b.y, b.z, b.w };
    auto    actual   = quat::lerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Lerp (Quaternion, Quaternion, float)
// Lerp test when the two quaternions are more than 90 degree (dot product <0)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, lerp_with_quaternions_with_more_than_90_degrees)
{
    auto    axis   = vector::normalize(vector3 { 1.0f, 2.0f, 3.0f });
    radians angle  = degrees(10.0f);
    auto    a      = quat::create_from_axis_angle(axis, angle);
    auto    b      = quat::negate(a);
    auto    t      = 1.0f;
    auto    actual = quat::lerp(a, b, t);

    // Note that in quaternion world, Q == -Q. In the case of quaternions dot product is zero,
    // one of the quaternion will be flipped to compute the shortest distance. When t = 1, we
    // expect the result to be the same as quaternion b but flipped.
    EXPECT_TRUE(equality_helper::equal(a, actual));
}

// A test for Conjugate(Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, conjugate2)
{
    auto a        = quaternion {  1,  2,  3, 4 };
    auto expected = quaternion { -1, -2, -3, 4 };
    auto actual   = quat::conjugate(a);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Normalize (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, normalize)
{
    auto a        = quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto expected = quaternion { 0.182574168f, 0.365148336f, 0.5477225f, 0.7302967f };
    auto actual   = quat::normalize(a);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Normalize (Quaternion)
// Normalize zero length quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, normalize_zero_length_quaternion)
{
    auto a      = quaternion { 0.0f, 0.0f, -0.0f, 0.0f };
    auto actual = quat::normalize(a);

    EXPECT_TRUE(is_nan(actual.x));
    EXPECT_TRUE(is_nan(actual.y));
    EXPECT_TRUE(is_nan(actual.z));
    EXPECT_TRUE(is_nan(actual.w));
}

// A test for Concatenate(Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, concatenate)
{
//    auto b        = quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
//    auto a        = quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
//    auto expected = quaternion { 24.0f, 48.0f, 48.0f, -6.0f };
//    auto actual   = quat::Concatenate(a, b);
//
//    EXPECT_TRUE(expected == actual);
}

// A test for operator - (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, subtraction)
{
    auto a        = quaternion { 1.0f, 6.0f, 7.0f, 4.0f };
    auto b        = quaternion { 5.0f, 2.0f, 3.0f, 8.0f };
    auto expected = quaternion { -4.0f, 4.0f, 4.0f, -4.0f };
    auto actual   = a - b;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator * (Quaternion, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, multiply_by_scalar)
{
    auto a        = quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto factor   = 0.5f;
    auto expected = quaternion { 0.5f, 1.0f, 1.5f, 2.0f };
    auto actual   = a * factor;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator * (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, multiply)
{
    auto a        = quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b        = quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
    auto expected = quaternion { 24.0f, 48.0f, 48.0f, -6.0f };
    auto actual   = a * b;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator / (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, division)
{
    auto a        = quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b        = quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
    auto expected = quaternion { -0.045977015f, -0.09195402f, -7.450581E-9f, 0.402298868f };
    auto actual   = a / b;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator + (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, addition)
{
    auto a        = quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b        = quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
    auto expected = quaternion { 6.0f, 8.0f, 10.0f, 12.0f };
    auto actual   = a + b;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Quaternion (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, constructor)
{
    auto x = 1.0f;
    auto y = 2.0f;
    auto z = 3.0f;
    auto w = 4.0f;

    auto target = quaternion { x, y, z, w };

    EXPECT_EQ(x, target.x);
    EXPECT_EQ(y, target.y);
    EXPECT_EQ(z, target.z);
    EXPECT_EQ(w, target.w);
}

// A test for Quaternion (vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, constructor_with_vector3)
{
    auto v      = vector3 { 1.0f, 2.0f, 3.0f };
    auto w      = 4.0f;
    auto target = quaternion { v, w };

    EXPECT_EQ(v.x, target.x);
    EXPECT_EQ(v.y, target.y);
    EXPECT_EQ(v.z, target.z);
    EXPECT_EQ(  w, target.w);
}

// A test for CreateFromAxisAngle (vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, create_from_axis_angle)
{
    auto    axis     = vector::normalize(vector3 { 1.0f, 2.0f, 3.0f });
    radians angle    = degrees(30.0f);
    auto    expected = quaternion(0.0691723f, 0.1383446f, 0.207516879f, 0.9659258f);
    auto    actual   = quat::create_from_axis_angle(axis, angle);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for CreateFromAxisAngle (vector3f, float)
// CreateFromAxisAngle of zero vector
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, create_from_axis_angle_of_zero_vector)
{
    auto    axis   = vector3 { };
    radians angle  = degrees(-30.0f);
    auto    cos    = std::cos(angle.value / 2.0f);
    auto    actual = quat::create_from_axis_angle(axis, angle);

    EXPECT_EQ(0.0f, actual.x);
    EXPECT_EQ(0.0f, actual.y);
    EXPECT_EQ(0.0f, actual.z);
    EXPECT_TRUE(equality_helper::equal(cos, actual.w));
}

// A test for CreateFromAxisAngle (vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, create_from_Axis_angle_of_angle_30_and_750)
{
    auto    axis    = vector3 { 1.0f, 0.0f, 0.0f };
    radians angle1  = degrees(30.0f);
    radians angle2  = degrees(750.0f);
    auto    actual1 = quat::create_from_axis_angle(axis, angle1);
    auto    actual2 = quat::create_from_axis_angle(axis, angle2);

    EXPECT_TRUE(equality_helper::equal(actual1, actual2));
}

// A test for CreateFromAxisAngle (vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, create_from_axis_angle_of_angle_30_and_390)
{
    auto    axis    = vector3 { 1.0f, 0.0f, 0.0f };
    radians angle1  = degrees(30.0f);
    radians angle2  = degrees(390.0f);
    auto    actual1 = quat::create_from_axis_angle(axis, angle1);
    auto    actual2 = quat::create_from_axis_angle(axis, angle2);

    actual1.x = -actual1.x;
    actual1.w = -actual1.w;

    EXPECT_TRUE(equality_helper::equal(actual1, actual2));
}

// A test for CreateFromAxisAngle (vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, create_from_yaw_pitch_roll)
{
    radians yawAngle   = degrees(30.0f);
    radians pitchAngle = degrees(40.0f);
    radians rollAngle  = degrees(50.0f);

    auto yaw      = quat::create_from_axis_angle(vector3::unit_y(), yawAngle);
    auto pitch    = quat::create_from_axis_angle(vector3::unit_x(), pitchAngle);
    auto roll     = quat::create_from_axis_angle(vector3::unit_z(), rollAngle);
    auto expected = yaw * pitch * roll;
    auto actual   = quat::create_from_yaw_pitch_roll(yawAngle, pitchAngle, rollAngle);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// Covers more numeric rigions
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, create_from_yaw_pitch_roll2)
{
    const auto step = 35.0f;

    for (degrees yawAngle = -720.0f; yawAngle <= 720.0f; yawAngle += step)
    {
        for (degrees pitchAngle = -720.0f; pitchAngle <= 720.0f; pitchAngle += step)
        {
            for (degrees rollAngle = -720.0f; rollAngle <= 720.0f; rollAngle += step)
            {
                radians yawRad   = yawAngle;
                radians pitchRad = pitchAngle;
                radians rollRad  = rollAngle;

                auto yaw   = quat::create_from_axis_angle(vector3::unit_y(), yawRad);
                auto pitch = quat::create_from_axis_angle(vector3::unit_x(), pitchRad);
                auto roll  = quat::create_from_axis_angle(vector3::unit_z(), rollRad);

                auto expected = yaw * pitch * roll;
                auto actual   = quat::create_from_yaw_pitch_roll(yawRad, pitchRad, rollRad);

                EXPECT_TRUE(equality_helper::equal(expected, actual));
            }
        }
    }
}

// A test for Slerp (Quaternion, Quaternion, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, slerp)
{
    auto    axis   = vector::normalize(vector3 { 1.0f, 2.0f, 3.0f });
    radians angle1 = degrees(10.0f);
    auto    a      = quat::create_from_axis_angle(axis, angle1);
    radians angle2 = degrees(30.0f);
    auto    b      = quat::create_from_axis_angle(axis, angle2);
    auto    t      = 0.5f;

    radians angle3   = degrees(20.0f);
    auto    expected = quat::create_from_axis_angle(axis, angle3);
    auto    actual   = quat::slerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Case a and b are same.
    expected = a;
    actual   = quat::slerp(a, a, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Slerp (Quaternion, Quaternion, float)
// Slerp test where t = 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, slerp_with_interpolate_zero)
{
    auto    axis   = vector::normalize(vector3 { 1.0f, 2.0f, 3.0f });
    radians angle1 = degrees(10.0f);
    auto    a      = quat::create_from_axis_angle(axis, angle1);
    radians angle2 = degrees(30.0f);
    auto    b      = quat::create_from_axis_angle(axis, angle2);
    auto    t      = 0.0f;

    auto expected = quaternion { a.x, a.y, a.z, a.w };
    auto actual   = quat::slerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Slerp (Quaternion, Quaternion, float)
// Slerp test where t = 1
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, slerp_with_interpolate_one)
{
    auto    axis   = vector::normalize(vector3 { 1.0f, 2.0f, 3.0f });
    radians angle1 = degrees(10.0f);
    auto    a      = quat::create_from_axis_angle(axis, angle1);
    radians angle2 = degrees(30.0f);
    auto    b      = quat::create_from_axis_angle(axis, angle2);
    auto    t      = 1.0f;

    auto expected = quaternion { b.x, b.y, b.z, b.w };
    auto actual   = quat::slerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Slerp (Quaternion, Quaternion, float)
// Slerp test where dot product is < 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, slerp_with_dot_product_less_than_zero)
{
    auto    axis   = vector::normalize(vector3 { 1.0f, 2.0f, 3.0f });
    radians angle1 = degrees(10.0f);
    auto    a      = quat::create_from_axis_angle(axis, angle1);
    auto    b      = -a;
    auto    t      = 1.0f;

    auto expected = a;
    auto actual   = quat::slerp(a, b, t);

    // Note that in quaternion world, Q == -Q. In the case of quaternions dot product is zero,
    // one of the quaternion will be flipped to compute the shortest distance. When t = 1, we
    // expect the result to be the same as quaternion b but flipped.
    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Slerp (Quaternion, Quaternion, float)
// Slerp test where the quaternion is flipped
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, slerp_with_flipped_quaternion)
{
    auto    axis   = vector::normalize(vector3 { 1.0f, 2.0f, 3.0f });
    radians angle1 = degrees(10.0f);
    auto    a      = quat::create_from_axis_angle(axis, angle1);
    radians angle2 = degrees(30.0f);
    auto    b      = -quat::create_from_axis_angle(axis, angle2);
    auto    t      = 0.0f;

    auto expected = quaternion { a.x, a.y, a.z, a.w };
    auto actual   = quat::slerp(a, b, t);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator - (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, unary_negation)
{
    auto a        = quaternion {  1.0f,  2.0f,  3.0f,  4.0f };
    auto expected = quaternion { -1.0f, -2.0f, -3.0f, -4.0f };
    auto actual   = -a;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Inverse (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, inverse)
{
    auto a        = quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
    auto expected = quaternion { -0.0287356321f, -0.03448276f, -0.0402298868f, 0.04597701f };
    auto actual   = quat::inverse(a);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Inverse (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, invert_zero_length_quaternion)
{
    auto a      = quaternion { };
    auto actual = quat::inverse(a);

    EXPECT_TRUE(is_nan(actual.x));
    EXPECT_TRUE(is_nan(actual.y));
    EXPECT_TRUE(is_nan(actual.z));
    EXPECT_TRUE(is_nan(actual.w));
}

// A test for negate (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, negate)
{
    auto a        = quaternion {  1.0f,  2.0f,  3.0f,  4.0f };
    auto expected = quaternion { -1.0f, -2.0f, -3.0f, -4.0f };
    auto actual   = quat::negate(a);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator != (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, inequality)
{
    auto a = quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = quaternion { 1.0f, 2.0f, 3.0f, 4.0f };

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

// A test for operator == (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, equality)
{
    auto a = quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = quaternion { 1.0f, 2.0f, 3.0f, 4.0f };

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

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, create_from_rotation_matrix)
{
    auto matrix   = matrix4::identity();
    auto expected = quaternion { 0.0f, 0.0f, 0.0f, 1.0f };
    auto actual   = quat::create_from_rotation_matrix(matrix);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // make sure convert back to matrix is same as we passed matrix.
    auto m2 = matrix::create_from_quaternion(actual);

    EXPECT_TRUE(equality_helper::equal(matrix, m2));
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, convert_x_axis_rotation_matrix)
{
    const auto step = 10.0f;

    for (degrees angle = 0.0f; angle < 720.0f; angle += step)
    {
        radians rads     = angle;
        auto    matrix   = matrix::create_rotation_x(rads);
        auto    expected = quat::create_from_axis_angle(vector3::unit_x(), rads);
        auto    actual   = quat::create_from_rotation_matrix(matrix);

        EXPECT_TRUE(equality_helper::equal_rotation(expected, actual));

        // make sure convert back to matrix is same as we passed matrix.
        auto m2 = matrix::create_from_quaternion(actual);

        EXPECT_TRUE(equality_helper::equal(matrix, m2));
    }
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, convert_y_axis_rotation_matrix)
{
    const auto step = 10.0f;

    for (degrees angle = 0.0f; angle < 720.0f; angle += step)
    {
        radians rads     = angle;
        auto    matrix   = matrix::create_rotation_y(rads);
        auto    expected = quat::create_from_axis_angle(vector3::unit_y(), rads);
        auto    actual   = quat::create_from_rotation_matrix(matrix);

        EXPECT_TRUE(equality_helper::equal_rotation(expected, actual));

        // make sure convert back to matrix is same as we passed matrix.
        auto m2 = matrix::create_from_quaternion(actual);

        EXPECT_TRUE(equality_helper::equal(matrix, m2));
    }
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, convert_z_axis_rotation_matrix)
{
    const auto step = 10.0f;

    for (degrees angle = 0.0f; angle < 720.0f; angle += step)
    {
        radians rads     = angle;
        auto    matrix   = matrix::create_rotation_z(rads);
        auto    expected = quat::create_from_axis_angle(vector3::unit_z(), rads);
        auto    actual   = quat::create_from_rotation_matrix(matrix);

        EXPECT_TRUE(equality_helper::equal_rotation(expected, actual));

        // make sure convert back to matrix is same as we passed matrix.
        auto m2 = matrix::create_from_quaternion(actual);

        EXPECT_TRUE(equality_helper::equal(matrix, m2));
    }
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, convert_xyz_axis_rotation_matrix)
{
    const auto step = 10.0f;

    for (degrees angle = 0.0f; angle < 720.0f; angle += step)
    {
        radians rads   = angle;
        auto    matrix = matrix::create_rotation_x(rads)
                       * matrix::create_rotation_y(rads)
                       * matrix::create_rotation_z(rads);

        auto expected = quat::create_from_axis_angle(vector3::unit_z(), rads)
                      * quat::create_from_axis_angle(vector3::unit_y(), rads)
                      * quat::create_from_axis_angle(vector3::unit_x(), rads);

        auto actual = quat::create_from_rotation_matrix(matrix);

        EXPECT_TRUE(equality_helper::equal_rotation(expected, actual));

        // make sure convert back to matrix is same as we passed matrix.
        auto m2 = matrix::create_from_quaternion(actual);

        EXPECT_TRUE(equality_helper::equal(matrix, m2));
    }
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, from_rotation_matrix_with_scaled_matrix_on_x_axis)
{
    radians angle  = degrees(180.0f);
    auto    matrix = matrix::create_rotation_y(angle)
                   * matrix::create_rotation_z(angle);

    auto expected = quat::create_from_axis_angle(vector3::unit_z(), angle)
                  * quat::create_from_axis_angle(vector3::unit_y(), angle);
    auto actual   = quat::create_from_rotation_matrix(matrix);

    EXPECT_TRUE(equality_helper::equal_rotation(expected, actual));

    // make sure convert back to matrix is same as we passed matrix.
    auto m2 = matrix::create_from_quaternion(actual);

    EXPECT_TRUE(equality_helper::equal(matrix, m2));
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, from_rotation_matrix_with_scaled_matrix_on_y_axis)
{
    radians angle  = degrees(180.0f);
    auto    matrix = matrix::create_rotation_x(angle)
                   * matrix::create_rotation_z(angle);

    auto expected = quat::create_from_axis_angle(vector3::unit_z(), angle)
                  * quat::create_from_axis_angle(vector3::unit_x(), angle);
    auto actual   = quat::create_from_rotation_matrix(matrix);

    EXPECT_TRUE(equality_helper::equal_rotation(expected, actual));

    // make sure convert back to matrix is same as we passed matrix.
    auto m2 = matrix::create_from_quaternion(actual);

    EXPECT_TRUE(equality_helper::equal(matrix, m2));
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, from_rotation_matrix_with_scaled_matrix_on_z_axis)
{
    radians angle  = degrees(180.0f);
    auto    matrix = matrix::create_rotation_x(angle)
                   * matrix::create_rotation_y(angle);

    auto expected = quat::create_from_axis_angle(vector3::unit_y(), angle)
                  * quat::create_from_axis_angle(vector3::unit_x(), angle);
    auto actual   = quat::create_from_rotation_matrix(matrix);

    EXPECT_TRUE(equality_helper::equal_rotation(expected, actual));

    // make sure convert back to matrix is same as we passed matrix.
    auto m2 = matrix::create_from_quaternion(actual);

    EXPECT_TRUE(equality_helper::equal(matrix, m2));
}

// A test for Identity
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, identity)
{
    auto actual = quaternion { 0.0f, 0.0f, 0.0f, 1.0f };

    EXPECT_TRUE(equality_helper::equal(quaternion::identity(), actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, is_identity)
{
    EXPECT_TRUE (quat::is_identity(quaternion::identity()));
    EXPECT_TRUE (quat::is_identity(quaternion(0, 0, 0, 1)));
    EXPECT_FALSE(quat::is_identity(quaternion(1, 0, 0, 1)));
    EXPECT_FALSE(quat::is_identity(quaternion(0, 1, 0, 1)));
    EXPECT_FALSE(quat::is_identity(quaternion(0, 0, 1, 1)));
    EXPECT_FALSE(quat::is_identity(quaternion(0, 0, 0, 0)));
}

// A test for Quaternion comparison involving NaN values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_quaternion_test, equals_nan)
{
    auto a = quaternion { NaN<>, 0    , 0    , 0     };
    auto b = quaternion { 0    , NaN<>, 0    , 0     };
    auto c = quaternion { 0    , 0    , NaN<>, 0     };
    auto d = quaternion { 0    , 0    , 0    , NaN<> };
    auto z = quaternion { 0    , 0    , 0    , 0     };

    EXPECT_FALSE(a == z);
    EXPECT_FALSE(b == z);
    EXPECT_FALSE(c == z);
    EXPECT_FALSE(d == z);

    EXPECT_TRUE(a != z);
    EXPECT_TRUE(b != z);
    EXPECT_TRUE(c != z);
    EXPECT_TRUE(d != z);

    EXPECT_FALSE(quat::is_identity(a));
    EXPECT_FALSE(quat::is_identity(b));
    EXPECT_FALSE(quat::is_identity(c));
    EXPECT_FALSE(quat::is_identity(d));
}

TEST_F(basic_quaternion_test, size_of)
{
    EXPECT_EQ(16u, sizeof(basic_quaternion<float>));
    EXPECT_EQ(32u, sizeof(basic_quaternion<double>));
}
