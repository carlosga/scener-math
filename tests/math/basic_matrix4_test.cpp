// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "basic_matrix4_test.hpp"

#include <cstdint>
#include <vector>

#include "equality_helper.hpp"

using namespace scener::math;

matrix4 basic_matrix4_test::generate_matrix_number_from_1_to_16()
{
    matrix4 a;

    a.m11 = 1.0f;
    a.m12 = 2.0f;
    a.m13 = 3.0f;
    a.m14 = 4.0f;
    a.m21 = 5.0f;
    a.m22 = 6.0f;
    a.m23 = 7.0f;
    a.m24 = 8.0f;
    a.m31 = 9.0f;
    a.m32 = 10.0f;
    a.m33 = 11.0f;
    a.m34 = 12.0f;
    a.m41 = 13.0f;
    a.m42 = 14.0f;
    a.m43 = 15.0f;
    a.m44 = 16.0f;

    return a;
}

matrix4 basic_matrix4_test::generate_test_matrix()
{
    radians a = degrees(30.0f);
    auto m = matrix::create_rotation_x(a)
           * matrix::create_rotation_y(a)
           * matrix::create_rotation_z(a);

    matrix::translation(m, { 111.0f, 222.0f, 333.0f });

    return m;
}

void basic_matrix4_test::create_reflection(const plane_t& plane, const matrix4& expected)
{
    auto actual = matrix::create_reflection(plane);

    EXPECT_TRUE(equality_helper::equal(actual, expected));
}

void basic_matrix4_test::decompose(const radians& yaw
                                 , const radians& pitch
                                 , const radians& roll
                                 , const vector3& expectedTranslation
                                 , const vector3& expectedScales)
{
    auto expectedRotation = quat::create_from_yaw_pitch_roll(yaw, pitch, roll);

    auto m = matrix::create_scale(expectedScales)
           * matrix::create_from_quaternion(expectedRotation)
           * matrix::create_translation(expectedTranslation);

    vector3    scales;
    quaternion rotation;
    vector3    translation;

    bool actualResult = matrix::decompose(m, scales, rotation, translation);

    EXPECT_TRUE(actualResult);

    bool scaleIsZeroOrNegative = expectedScales.x <= 0
                              || expectedScales.y <= 0
                              || expectedScales.z <= 0;

    if (scaleIsZeroOrNegative)
    {
        EXPECT_TRUE(equality_helper::equal(std::abs(expectedScales.x), std::abs(scales.x)));
        EXPECT_TRUE(equality_helper::equal(std::abs(expectedScales.y), std::abs(scales.y)));
        EXPECT_TRUE(equality_helper::equal(std::abs(expectedScales.z), std::abs(scales.z)));
    }
    else
    {
        EXPECT_TRUE(equality_helper::equal(expectedScales, scales));
        EXPECT_TRUE(equality_helper::equal_rotation(expectedRotation, rotation));
    }

    EXPECT_TRUE(equality_helper::equal(expectedTranslation, translation));
}

void basic_matrix4_test::decompose_scale(const float& sx, const float& sy, const float& sz)
{
    auto m              = matrix::create_scale(sx, sy, sz);
    auto expectedScales = vector3 { sx, sy, sz };

    vector3    scales;
    quaternion rotation;
    vector3    translation;

    bool actualResult = matrix::decompose(m, scales, rotation, translation);

    EXPECT_TRUE(actualResult);
    EXPECT_TRUE(equality_helper::equal(expectedScales, scales));
    EXPECT_TRUE(equality_helper::equal_rotation(quaternion::identity(), rotation));
    EXPECT_TRUE(equality_helper::equal(vector3::zero(), translation));
}

TEST_F(basic_matrix4_test, default_constructor)
{
    matrix4 matrix;

    EXPECT_EQ(0.0f, matrix.m11);
    EXPECT_EQ(0.0f, matrix.m12);
    EXPECT_EQ(0.0f, matrix.m13);
    EXPECT_EQ(0.0f, matrix.m14);
    EXPECT_EQ(0.0f, matrix.m21);
    EXPECT_EQ(0.0f, matrix.m22);
    EXPECT_EQ(0.0f, matrix.m23);
    EXPECT_EQ(0.0f, matrix.m24);
    EXPECT_EQ(0.0f, matrix.m31);
    EXPECT_EQ(0.0f, matrix.m32);
    EXPECT_EQ(0.0f, matrix.m33);
    EXPECT_EQ(0.0f, matrix.m34);
    EXPECT_EQ(0.0f, matrix.m41);
    EXPECT_EQ(0.0f, matrix.m42);
    EXPECT_EQ(0.0f, matrix.m43);
    EXPECT_EQ(0.0f, matrix.m44);
}

TEST_F(basic_matrix4_test, matrix_constructor)
{
    matrix4 matrix { 10.0f, 10.0f, 10.0f, 0.0f
                   , 20.0f, 20.0f, 20.0f, 0.0f
                   , 30.0f, 30.0f, 30.0f, 0.0f
                   , 5.0f , 10.0f, 15.0f, 1.0f };

    EXPECT_EQ(10.0f, matrix.m11);
    EXPECT_EQ(10.0f, matrix.m12);
    EXPECT_EQ(10.0f, matrix.m13);
    EXPECT_EQ( 0.0f, matrix.m14);
    EXPECT_EQ(20.0f, matrix.m21);
    EXPECT_EQ(20.0f, matrix.m22);
    EXPECT_EQ(20.0f, matrix.m23);
    EXPECT_EQ( 0.0f, matrix.m24);
    EXPECT_EQ(30.0f, matrix.m31);
    EXPECT_EQ(30.0f, matrix.m32);
    EXPECT_EQ(30.0f, matrix.m33);
    EXPECT_EQ( 0.0f, matrix.m34);
    EXPECT_EQ( 5.0f, matrix.m41);
    EXPECT_EQ(10.0f, matrix.m42);
    EXPECT_EQ(15.0f, matrix.m43);
    EXPECT_EQ( 1.0f, matrix.m44);
}

TEST_F(basic_matrix4_test, matrix_multiplication)
{
    matrix4 matrix1 { 1.0f, 2.0f, 3.0f, 4.0f
                    , 5.0f, 6.0f, 7.0f, 8.0f
                    , 1.0f, 2.0f, 3.0f, 4.0f
                    , 5.0f, 6.0f, 7.0f, 8.0f };
    matrix4 matrix2 { 1.0f, 2.0f, 3.0f, 4.0f
                    , 5.0f, 6.0f, 7.0f, 8.0f
                    , 1.0f, 2.0f, 3.0f, 4.0f
                    , 5.0f, 6.0f, 7.0f, 8.0f };

    auto result = matrix1 * matrix2;

    EXPECT_EQ( 34.0f, result.m11);
    EXPECT_EQ( 44.0f, result.m12);
    EXPECT_EQ( 54.0f, result.m13);
    EXPECT_EQ( 64.0f, result.m14);
    EXPECT_EQ( 82.0f, result.m21);
    EXPECT_EQ(108.0f, result.m22);
    EXPECT_EQ(134.0f, result.m23);
    EXPECT_EQ(160.0f, result.m24);
    EXPECT_EQ( 34.0f, result.m31);
    EXPECT_EQ( 44.0f, result.m32);
    EXPECT_EQ( 54.0f, result.m33);
    EXPECT_EQ( 64.0f, result.m34);
    EXPECT_EQ( 82.0f, result.m41);
    EXPECT_EQ(108.0f, result.m42);
    EXPECT_EQ(134.0f, result.m43);
    EXPECT_EQ(160.0f, result.m44);
}

TEST_F(basic_matrix4_test, transpose)
{
    matrix4 source { 1.0f, 0.0f, 0.0f, 10.0f
                   , 0.0f, 1.0f, 0.0f, 10.0f
                   , 0.0f, 0.0f, 1.0f, 10.0f
                   , 0.0f, 0.0f, 0.0f, 1.0f };

    auto transposed = matrix::transpose(source);

    EXPECT_EQ( 1.0f, transposed.m11);
    EXPECT_EQ( 0.0f, transposed.m12);
    EXPECT_EQ( 0.0f, transposed.m13);
    EXPECT_EQ( 0.0f, transposed.m14);
    EXPECT_EQ( 0.0f, transposed.m21);
    EXPECT_EQ( 1.0f, transposed.m22);
    EXPECT_EQ( 0.0f, transposed.m23);
    EXPECT_EQ( 0.0f, transposed.m24);
    EXPECT_EQ( 0.0f, transposed.m31);
    EXPECT_EQ( 0.0f, transposed.m32);
    EXPECT_EQ( 1.0f, transposed.m33);
    EXPECT_EQ( 0.0f, transposed.m34);
    EXPECT_EQ(10.0f, transposed.m41);
    EXPECT_EQ(10.0f, transposed.m42);
    EXPECT_EQ(10.0f, transposed.m43);
    EXPECT_EQ( 1.0f, transposed.m44);
}

TEST_F(basic_matrix4_test, determinant)
{
    matrix4 matrix = { 2.0f, 3.0f, 4.0f , 0.0f
                     , 1.0f, 2.0f, -3.0f, 0.0f
                     , 1.0f, 1.0f, 5.0f , 0.0f
                     , 0.0f, 0.0f, 0.0f , 1.0f };

    EXPECT_EQ(-2.0f, matrix::determinant(matrix));
}

TEST_F(basic_matrix4_test, inverse)
{
    matrix4 mtx = { 2.0f, 3.0f, 4.0f , 0.0f
                  , 1.0f, 2.0f, -3.0f, 0.0f
                  , 1.0f, 1.0f, 5.0f , 0.0f
                  , 0.0f, 0.0f, 0.0f , 1.0f };

    auto actual = matrix::invert(mtx);

    EXPECT_EQ(-6.5f, actual.m11);
    EXPECT_EQ( 5.5f, actual.m12);
    EXPECT_EQ( 8.5f, actual.m13);
    EXPECT_EQ( 0.0f, actual.m14);
    EXPECT_EQ( 4.0f, actual.m21);
    EXPECT_EQ(-3.0f, actual.m22);
    EXPECT_EQ(-5.0f, actual.m23);
    EXPECT_EQ( 0.0f, actual.m24);
    EXPECT_EQ( 0.5f, actual.m31);
    EXPECT_EQ(-0.5f, actual.m32);
    EXPECT_EQ(-0.5f, actual.m33);
    EXPECT_EQ( 0.0f, actual.m34);
    EXPECT_EQ( 0.0f, actual.m41);
    EXPECT_EQ( 0.0f, actual.m42);
    EXPECT_EQ( 0.0f, actual.m43);
    EXPECT_EQ( 1.0f, actual.m44);

    // Make sure M*M is identity matrix
    auto i = mtx * actual;

    EXPECT_TRUE(equality_helper::equal(matrix4::identity(), i));
}

TEST_F(basic_matrix4_test, create_perspective_field_of_view)
{
    auto fieldOfView = radians { pi_over_4<> };
    auto aspectRatio = 768.0f / 480.0f;
    auto perspective = matrix::create_perspective_field_of_view(fieldOfView, aspectRatio, 0.1f, 100.0f);

    EXPECT_EQ(1.50888336f, perspective.m11);
    EXPECT_EQ(       0.0f, perspective.m12);
    EXPECT_EQ(       0.0f, perspective.m13);
    EXPECT_EQ(       0.0f, perspective.m14);
    EXPECT_EQ(       0.0f, perspective.m21);
    EXPECT_EQ(2.41421342f, perspective.m22);
    EXPECT_EQ(       0.0f, perspective.m23);
    EXPECT_EQ(       0.0f, perspective.m24);
    EXPECT_EQ(       0.0f, perspective.m31);
    EXPECT_EQ(       0.0f, perspective.m32);
    EXPECT_EQ(-1.001001f , perspective.m33);
    EXPECT_EQ(      -1.0f, perspective.m34);
    EXPECT_EQ(       0.0f, perspective.m41);
    EXPECT_EQ(       0.0f, perspective.m42);
    EXPECT_EQ(-0.1001001f, perspective.m43);
    EXPECT_EQ(       0.0f, perspective.m44);
}

TEST_F(basic_matrix4_test, create_look_at)
{
    auto lookAt = matrix::create_look_at({ 0.0f, 1.0f, -5.0f }, vector3::unit_y(), vector3::up());

    EXPECT_EQ(-1.0f, lookAt.m11);
    EXPECT_EQ( 0.0f, lookAt.m12);
    EXPECT_EQ( 0.0f, lookAt.m13);
    EXPECT_EQ( 0.0f, lookAt.m14);
    EXPECT_EQ( 0.0f, lookAt.m21);
    EXPECT_EQ( 1.0f, lookAt.m22);
    EXPECT_EQ( 0.0f, lookAt.m23);
    EXPECT_EQ( 0.0f, lookAt.m24);
    EXPECT_EQ( 0.0f, lookAt.m31);
    EXPECT_EQ( 0.0f, lookAt.m32);
    EXPECT_EQ(-1.0f, lookAt.m33);
    EXPECT_EQ( 0.0f, lookAt.m34);
    EXPECT_EQ( 0.0f, lookAt.m41);
    EXPECT_EQ(-1.0f, lookAt.m42);
    EXPECT_EQ(-5.0f, lookAt.m43);
    EXPECT_EQ( 1.0f, lookAt.m44);
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, identity)
{
    matrix4 val;

    val.m11 = 1.0f;
    val.m22 = 1.0f;
    val.m33 = 1.0f;
    val.m44 = 1.0f;

    EXPECT_TRUE(equality_helper::equal(val, matrix4::identity()));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, determinant1)
{
    auto angle  = degrees(30.0f);
    auto target = matrix::create_rotation_x(static_cast<radians>(angle))
                * matrix::create_rotation_y(static_cast<radians>(angle))
                * matrix::create_rotation_z(static_cast<radians>(angle));

    auto val = 1.0f;
    auto det = matrix::determinant(target);

    EXPECT_EQ(val, det);
}

// Determinant test |A| = 1 / |A'|
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, determinant2)
{
    matrix4 a;

    a.m11 =  5.0f;
    a.m12 =  2.0f;
    a.m13 = 8.25f;
    a.m14 =  1.0f;
    a.m21 = 12.0f;
    a.m22 =  6.8f;
    a.m23 = 2.14f;
    a.m24 =  9.6f;
    a.m31 =  6.5f;
    a.m32 =  1.0f;
    a.m33 = 3.14f;
    a.m34 = 2.22f;
    a.m41 =  0.0f;
    a.m42 = 0.86f;
    a.m43 =  4.0f;
    a.m44 =  1.0f;

    auto  i    = matrix::invert(a);
    float detA = matrix::determinant(a);
    float detI = matrix::determinant(i);
    float t    = 1.0f / detI;

    // only accurate to 3 precision
    EXPECT_TRUE(std::abs(detA - t) < 1e-3);
}

// A test for Invert (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, invert)
{
    radians a   = degrees(30.0f);
    auto    mtx = matrix::create_rotation_x(a)
                * matrix::create_rotation_y(a)
                * matrix::create_rotation_z(a);

    matrix4 expected {  0.74999994f, -0.216506317f,   0.62499994f,        0.0f
                     , 0.433012635f,   0.87499994f, -0.216506317f,        0.0f
                     , -0.49999997f,  0.433012635f,   0.74999994f,        0.0f
                     ,         0.0f,          0.0f,          0.0f, 0.99999994f };

    auto actual = matrix::invert(mtx);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    // Make sure M*M is identity matrix
    auto i = mtx * actual;

    EXPECT_TRUE(equality_helper::equal(matrix4::identity(), i));
}

// A test for Invert (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, invert_identity_matrix)
{
    auto mtx    = matrix4::identity();
    auto actual = matrix::invert(mtx);

    EXPECT_TRUE(equality_helper::equal(actual, matrix4::identity()));
}

// A test for Invert (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, invert_translation_matrix)
{
    auto mtx    = matrix::create_translation(23.0f, 42.0f, 666.0f);
    auto actual = matrix::invert(mtx);
    auto i      = mtx * actual;

    EXPECT_TRUE(equality_helper::equal(i, matrix4::identity()));
}

// A test for Invert (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, invert_rotation_matrix)
{
    auto mtx    = matrix::create_from_yaw_pitch_roll(radians { 3.0f }, radians { 4.0f }, radians { 5.0f });
    auto actual = matrix::invert(mtx);
    auto i      = mtx * actual;

    EXPECT_TRUE(equality_helper::equal(i, matrix4::identity()));
}

// A test for Invert (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, invert_scale_matrix)
{
    auto mtx      = matrix::create_scale(23.0f, 42.0f, -666.0f);
    auto actual   = matrix::invert(mtx);
    auto identity = mtx * actual;

    EXPECT_TRUE(equality_helper::equal(identity, matrix4::identity()));
}

// A test for Invert (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, invert_projection_matrix)
{
    auto fov       = radians { 1.0f };
    auto mtx       = matrix::create_perspective_field_of_view(fov, 1.333f, 0.1f, 666.0f);
    auto actual    = matrix::invert(mtx);
    auto idientity = mtx * actual;

    EXPECT_TRUE(equality_helper::equal(idientity, matrix4::identity()));
}

// A test for Invert (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, invert_affine_matrix)
{
    auto mtx = matrix::create_from_yaw_pitch_roll(radians { 3.0f }, radians { 4.0f } , radians { 5.0f })
             * matrix::create_scale(23.0f, 42.0f, -666.0f)
             * matrix::create_translation(17.0f, 53.0f, 89.0f);

    auto actual = matrix::invert(mtx);
    auto i      = mtx * actual;

    EXPECT_TRUE(equality_helper::equal(i, matrix4::identity()));
}

// Various rotation decompose test.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, decompose)
{
    auto yaw   = degrees { 10.0f };
    auto pitch = degrees { 20.0f };
    auto roll  = degrees { 30.0f };

    basic_matrix4_test::decompose(yaw, pitch, roll, { 10.0f, 20.0f, 30.0f }, { 2.0f, 3.0f, 4.0f });

    const auto step = 35.0f;

    for (degrees yawAngle = -720.0f; yawAngle <= 720.0f; yawAngle += step)
    {
        for (degrees pitchAngle = -720.0f; pitchAngle <= 720.0f; pitchAngle += step)
        {
            for (degrees rollAngle = -720.0f; rollAngle <= 720.0f; rollAngle += step)
            {
                basic_matrix4_test::decompose(yawAngle, pitchAngle, rollAngle, { 10, 20, 30 }, { 2, 3, 4 });
            }
        }
    }
}

// Various scaled matrix decompose test.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, DISABLED_various_scaled_matrix_decomposition)
{
    auto yaw   = degrees(10.0f);
    auto pitch = degrees(20.0f);
    auto roll  = degrees(30.0f);

    basic_matrix4_test::decompose(yaw, pitch, roll, { 10.0f, 20.0f, 30.0f }, { 2.0f, 3.0f, 4.0f });

    radians zero;

    // Various scales.
    basic_matrix4_test::decompose(zero, zero, zero, vector3::zero(), { 1.0f, 2.0f, 3.0f });
    basic_matrix4_test::decompose(zero, zero, zero, vector3::zero(), { 1.0f, 3.0f, 2.0f });
    basic_matrix4_test::decompose(zero, zero, zero, vector3::zero(), { 2.0f, 1.0f, 3.0f });
    basic_matrix4_test::decompose(zero, zero, zero, vector3::zero(), { 2.0f, 3.0f, 1.0f });
    basic_matrix4_test::decompose(zero, zero, zero, vector3::zero(), { 3.0f, 1.0f, 2.0f });
    basic_matrix4_test::decompose(zero, zero, zero, vector3::zero(), { 3.0f, 2.0f, 1.0f });

    basic_matrix4_test::decompose(zero, zero, zero, vector3::zero(), { -2.0f, 1.0f, 1.0f });

    // Small scales.
    basic_matrix4_test::decompose(zero, zero, zero, vector3::zero(), { 1e-4f, 2e-4f, 3e-4f });
    basic_matrix4_test::decompose(zero, zero, zero, vector3::zero(), { 1e-4f, 3e-4f, 2e-4f });
    basic_matrix4_test::decompose(zero, zero, zero, vector3::zero(), { 2e-4f, 1e-4f, 3e-4f });
    basic_matrix4_test::decompose(zero, zero, zero, vector3::zero(), { 2e-4f, 3e-4f, 1e-4f });
    basic_matrix4_test::decompose(zero, zero, zero, vector3::zero(), { 3e-4f, 1e-4f, 2e-4f });
    basic_matrix4_test::decompose(zero, zero, zero, vector3::zero(), { 3e-4f, 2e-4f, 1e-4f });

    // Zero scales.
    basic_matrix4_test::decompose(zero, zero, zero, { 10.0f, 20.0f, 30.0f }, { 0.0f, 0.0f, 0.0f });
    basic_matrix4_test::decompose(zero, zero, zero, { 10.0f, 20.0f, 30.0f }, { 1.0f, 0.0f, 0.0f });
    basic_matrix4_test::decompose(zero, zero, zero, { 10.0f, 20.0f, 30.0f }, { 0.0f, 1.0f, 0.0f });
    basic_matrix4_test::decompose(zero, zero, zero, { 10.0f, 20.0f, 30.0f }, { 0.0f, 0.0f, 1.0f });
    basic_matrix4_test::decompose(zero, zero, zero, { 10.0f, 20.0f, 30.0f }, { 0.0f, 1.0f, 1.0f });
    basic_matrix4_test::decompose(zero, zero, zero, { 10.0f, 20.0f, 30.0f }, { 1.0f, 0.0f, 1.0f });
    basic_matrix4_test::decompose(zero, zero, zero, { 10.0f, 20.0f, 30.0f }, { 1.0f, 1.0f, 0.0f });

    // Negative scales.
    basic_matrix4_test::decompose(zero, zero, zero, { 10.0f, 20.0f, 30.0f }, { -1.0f, -1.0f, -1.0f });
    basic_matrix4_test::decompose(zero, zero, zero, { 10.0f, 20.0f, 30.0f }, {  1.0f, -1.0f, -1.0f });
    basic_matrix4_test::decompose(zero, zero, zero, { 10.0f, 20.0f, 30.0f }, { -1.0f,  1.0f, -1.0f });
    basic_matrix4_test::decompose(zero, zero, zero, { 10.0f, 20.0f, 30.0f }, { -1.0f, -1.0f,  1.0f });
    basic_matrix4_test::decompose(zero, zero, zero, { 10.0f, 20.0f, 30.0f }, { -1.0f,  1.0f,  1.0f });
    basic_matrix4_test::decompose(zero, zero, zero, { 10.0f, 20.0f, 30.0f }, {  1.0f, -1.0f,  1.0f });
    basic_matrix4_test::decompose(zero, zero, zero, { 10.0f, 20.0f, 30.0f }, {  1.0f,  1.0f, -1.0f });
}

// Tiny scale decompose test.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, decompose_scale)
{
    basic_matrix4_test::decompose_scale(    1, 2e-4f, 3e-4f);
    basic_matrix4_test::decompose_scale(    1, 3e-4f, 2e-4f);
    basic_matrix4_test::decompose_scale(2e-4f,     1, 3e-4f);
    basic_matrix4_test::decompose_scale(2e-4f, 3e-4f,     1);
    basic_matrix4_test::decompose_scale(3e-4f,     1, 2e-4f);
    basic_matrix4_test::decompose_scale(3e-4f, 2e-4f,     1);
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, scale_decompose1)
{
    vector3    scales;
    quaternion rotation;
    vector3    translation;

    EXPECT_FALSE(matrix::decompose(basic_matrix4_test::generate_matrix_number_from_1_to_16(), scales, rotation, translation));
}

// Transform by quaternion test
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, transform_by_quaternion)
{
    auto    target = basic_matrix4_test::generate_matrix_number_from_1_to_16();
    radians angle  = degrees(30.0f);
    auto    m      = matrix::create_rotation_x(angle)
                   * matrix::create_rotation_y(angle)
                   * matrix::create_rotation_z(angle);

    auto q        = quat::create_from_rotation_matrix(m);
    auto expected = target * m;
    auto actual   = matrix::transform(target, q);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for CreateRotationX (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_rotation_x)
{
    radians rads = degrees(30.0f);
    matrix4 expected;

    expected.m11 = 1.0f;
    expected.m22 = 0.8660254f;
    expected.m23 = 0.5f;
    expected.m32 = -0.5f;
    expected.m33 = 0.8660254f;
    expected.m44 = 1.0f;

    auto actual = matrix::create_rotation_x(rads);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for CreateRotationX (float)
// CreateRotationX of zero degree
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_rotation_x_of_zero_degree)
{
    radians rads { 0.0f };

    auto expected = matrix4::identity();
    auto actual   = matrix::create_rotation_x(rads);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for CreateRotationX (float, vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_rotation_x_center)
{
    radians rads   = degrees { 30.0f };
    auto    center = vector3 { 23, 42, 66 };

    auto rotateAroundZero         = matrix::create_rotation_x(rads, vector3::zero());
    auto rotateAroundZeroExpected = matrix::create_rotation_x(rads);

    EXPECT_TRUE(equality_helper::equal(rotateAroundZero, rotateAroundZeroExpected));

    auto rotateAroundCenter         = matrix::create_rotation_x(rads, center);
    auto rotateAroundCenterExpected = matrix::create_translation(-center)
                                    * matrix::create_rotation_x(rads)
                                    * matrix::create_translation(center);

    EXPECT_TRUE(equality_helper::equal(rotateAroundCenter, rotateAroundCenterExpected));
}

// A test for CreateRotationY (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_rotation_y)
{
    radians rads = degrees{ 60.0f };
    matrix4 expected;

    expected.m11 = 0.49999997f;
    expected.m13 = -0.866025448f;
    expected.m22 = 1.0f;
    expected.m31 = 0.866025448f;
    expected.m33 = 0.49999997f;
    expected.m44 = 1.0f;

    auto actual = matrix::create_rotation_y(rads);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for RotationY (float)
// CreateRotationY test for negative angle
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_rotation_y_for_negative_angle)
{
    radians rads = degrees(-300.0f);
    matrix4 expected;

    expected.m11 = 0.49999997f;
    expected.m13 = -0.866025448f;
    expected.m22 = 1.0f;
    expected.m31 = 0.866025448f;
    expected.m33 = 0.49999997f;
    expected.m44 = 1.0f;

    auto actual = matrix::create_rotation_y(rads);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for CreateRotationY (float, vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_rotation_y_center)
{
    radians rads   = degrees(30.0f);
    auto    center = vector3 { 23.0f, 42.0f, 66.0f };

    auto rotateAroundZero         = matrix::create_rotation_y(rads, vector3::zero());
    auto rotateAroundZeroExpected = matrix::create_rotation_y(rads);

    EXPECT_TRUE(equality_helper::equal(rotateAroundZero, rotateAroundZeroExpected));

    auto rotateAroundCenter         = matrix::create_rotation_y(rads, center);
    auto rotateAroundCenterExpected = matrix::create_translation(-center)
                                    * matrix::create_rotation_y(rads)
                                    * matrix::create_translation(center);

    EXPECT_TRUE(equality_helper::equal(rotateAroundCenter, rotateAroundCenterExpected));
}

// A test for CreateRotationZ (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_rotation_z)
{
    radians angle = degrees(50.0f);
    matrix4 expected;

    expected.m11 = 0.642787635f;
    expected.m12 = 0.766044438f;
    expected.m21 = -0.766044438f;
    expected.m22 = 0.642787635f;
    expected.m33 = 1.0f;
    expected.m44 = 1.0f;

    auto actual = matrix::create_rotation_z(angle);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for CreateRotationZ (float, vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_rotation_z_center)
{
    radians angle  = degrees(30.0f);
    auto    center = vector3 { 23, 42, 66 };

    auto rotateAroundZero         = matrix::create_rotation_z(angle, vector3::zero());
    auto rotateAroundZeroExpected = matrix::create_rotation_z(angle);

    EXPECT_TRUE(equality_helper::equal(rotateAroundZero, rotateAroundZeroExpected));

    auto rotateAroundCenter         = matrix::create_rotation_z(angle, center);
    auto rotateAroundCenterExpected = matrix::create_translation(-center)
                                    * matrix::create_rotation_z(angle)
                                    * matrix::create_translation(center);

    EXPECT_TRUE(equality_helper::equal(rotateAroundCenter, rotateAroundCenterExpected));
}

// A test for CreateFromAxisAngle(vector3f,float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_from_axis_angle)
{
    radians angle    = degrees(-30.0f);
    auto    expected = matrix::create_rotation_x(angle);
    auto    actual   = matrix::create_from_axis_angle(vector3::unit_x(), angle);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    expected = matrix::create_rotation_y(angle);
    actual   = matrix::create_from_axis_angle(vector3::unit_y(), angle);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    expected = matrix::create_rotation_z(angle);
    actual   = matrix::create_from_axis_angle(vector3::unit_z(), angle);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    expected = matrix::create_from_quaternion(quat::create_from_axis_angle(vector::normalize(vector3::one()), angle));
    actual   = matrix::create_from_axis_angle(vector::normalize(vector3::one()), angle);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    const std::uint32_t rotCount = 16;

    for (std::uint32_t i = 0; i < rotCount; ++i)
    {
        auto latitude = radians { (2.0f * pi<>) * ((float)i / (float)rotCount) };

        for (std::uint32_t j = 0; j < rotCount; ++j)
        {
            auto longitude = radians { -pi_over_2<> + pi<> * ((float)j / (float)rotCount) };

            auto m    = matrix::create_rotation_z(longitude) * matrix::create_rotation_y(latitude);
            auto axis = vector3 { m.m11, m.m12, m.m13 };

            for (std::uint32_t k = 0; k < rotCount; ++k)
            {
                auto rotation = radians { (2.0f * pi<>) * ((float)k / (float)rotCount) };

                expected = matrix::create_from_quaternion(quat::create_from_axis_angle(axis, rotation));
                actual   = matrix::create_from_axis_angle(axis, rotation);

                EXPECT_TRUE(equality_helper::equal(expected, actual));
            }
        }
    }
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_from_yaw_pitch_roll)
{
    radians yawAngle   = degrees(30.0f);
    radians pitchAngle = degrees(40.0f);
    radians rollAngle  = degrees(50.0f);

    auto yaw      = matrix::create_from_axis_angle(vector3::unit_y(), yawAngle);
    auto pitch    = matrix::create_from_axis_angle(vector3::unit_x(), pitchAngle);
    auto roll     = matrix::create_from_axis_angle(vector3::unit_z(), rollAngle);
    auto expected = roll * pitch * yaw;
    auto actual   = matrix::create_from_yaw_pitch_roll(yawAngle, pitchAngle, rollAngle);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// Covers more numeric rigions
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_from_yaw_pitch_roll2)
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

                auto yaw   = matrix::create_from_axis_angle(vector3::unit_y(), yawRad);
                auto pitch = matrix::create_from_axis_angle(vector3::unit_x(), pitchRad);
                auto roll  = matrix::create_from_axis_angle(vector3::unit_z(), rollRad);

                auto expected = roll * pitch * yaw;
                auto actual   = matrix::create_from_yaw_pitch_roll(yawRad, pitchRad, rollRad);

                EXPECT_TRUE(equality_helper::equal(expected, actual));
            }
        }
    }
}

// Simple shadow test.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_shadow)
{
//    auto lightDir = vector3::unit_y();
//    auto plane    = Plane { vector3::unit_y(), 0 };
//    auto expected = matrix::create_scale(1, 0, 1);
//    auto actual   = matrix::create_shadow(lightDir, plane);

//    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// Various plane projections.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_shadow_various_plane_projections)
{
//    // Complex cases.
//    auto planes = std::vector<Plane>();

//    planes.push_back({ 0, 1, 0, 0 });
//    planes.push_back({ 1, 2, 3, 4 });
//    planes.push_back({ 5, 6, 7, 8 });
//    planes.push_back({-1,-2,-3,-4 });
//    planes.push_back({-5,-6,-7,-8 });

//    auto points = std::vector<vector3>();

//    points.push_back({ 1, 2,  3 });
//    points.push_back({ 5, 6,  7 });
//    points.push_back({ 8, 9, 10 });
//    points.push_back({-1,-2, -3 });
//    points.push_back({-5,-6, -7 });
//    points.push_back({-8,-9,-10 });

//    for (auto& p : planes)
//    {
//        auto plane = Plane::normalize(p);

//        // Try various direction of light directions.
//        auto testDirections = std::vector<vector3>();

//        points.push_back({ -1.0f, 1.0f, 1.0f });
//        points.push_back({  0.0f, 1.0f, 1.0f });
//        points.push_back({  1.0f, 1.0f, 1.0f });
//        points.push_back({ -1.0f, 0.0f, 1.0f });
//        points.push_back({  0.0f, 0.0f, 1.0f });
//        points.push_back({  1.0f, 0.0f, 1.0f });
//        points.push_back({ -1.0f,-1.0f, 1.0f });
//        points.push_back({  0.0f,-1.0f, 1.0f });
//        points.push_back({  1.0f,-1.0f, 1.0f });

//        points.push_back({ -1.0f, 1.0f, 0.0f });
//        points.push_back({  0.0f, 1.0f, 0.0f });
//        points.push_back({  1.0f, 1.0f, 0.0f });
//        points.push_back({ -1.0f, 0.0f, 0.0f });
//        points.push_back({  0.0f, 0.0f, 0.0f });
//        points.push_back({  1.0f, 0.0f, 0.0f });
//        points.push_back({ -1.0f,-1.0f, 0.0f });
//        points.push_back({  0.0f,-1.0f, 0.0f });
//        points.push_back({  1.0f,-1.0f, 0.0f });

//        points.push_back({ -1.0f, 1.0f,-1.0f });
//        points.push_back({  0.0f, 1.0f,-1.0f });
//        points.push_back({  1.0f, 1.0f,-1.0f });
//        points.push_back({ -1.0f, 0.0f,-1.0f });
//        points.push_back({  0.0f, 0.0f,-1.0f });
//        points.push_back({  1.0f, 0.0f,-1.0f });
//        points.push_back({ -1.0f,-1.0f,-1.0f });
//        points.push_back({  0.0f,-1.0f,-1.0f });
//        points.push_back({  1.0f,-1.0f,-1.0f });

//        for (auto& lightDirInfo : testDirections)
//        {
//            if (lightDirInfo.length() < 0.1f)
//            {
//                continue;
//            }

//            auto lightDir = vector::normalize(lightDirInfo);

//            if (Plane::dot_normal(plane, lightDir) < 0.1f)
//            {
//                continue;
//            }

//            auto m  = matrix::create_shadow(lightDir, plane);
//            auto pp = -plane.d * plane.normal; // origin of the plane.

//            for (auto& point : points)
//            {
//                auto v4 = Vector4::transform(point, m);
//                auto sp = vector3 { v4.x, v4.y, v4.z } / v4.w;

//                // Make sure transformed position is on the plane.
//                auto   v = sp - pp;
//                float d = vector::dot(v, plane.normal);

//                EXPECT_TRUE(equality_helper::equal(d, 0));

//                // make sure direction between transformed position and original position are same as light direction.
//                if (vector::dot(point - pp, plane.normal) > 0.0001f)
//                {
//                    auto dir = vector::normalize(point - sp);

//                    EXPECT_TRUE(equality_helper::equal(dir, lightDir));
//                }
//            };
//        }
//    }
}

// A test for CrateLookAt (vector3f, vector3f, vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_look_at2)
{
    auto cameraPosition = vector3 { 10.0f, 20.0f, 30.0f };
    auto cameraTarget   = vector3 {  3.0f,  2.0f, -4.0f };
    auto cameraUpVector = vector3 {  0.0f,  1.0f,  0.0f };

    matrix4 expected;

    expected.m11 = 0.979457f;
    expected.m12 = -0.0928267762f;
    expected.m13 = 0.179017f;

    expected.m21 = 0.0f;
    expected.m22 = 0.8877481f;
    expected.m23 = 0.460329473f;

    expected.m31 = -0.201652914f;
    expected.m32 = -0.450872928f;
    expected.m33 = 0.8695112f;

    expected.m41 = -3.74498272f;
    expected.m42 = -3.30050683f;
    expected.m43 = -37.0820961f;
    expected.m44 = 1.0f;

    auto actual = matrix::create_look_at(cameraPosition, cameraTarget, cameraUpVector);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for CreateWorld (vector3f, vector3f, vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_world)
{
    auto objectPosition         = vector3 { 10.0f, 20.0f, 30.0f };
    auto objectForwardDirection = vector3 { 3.0f, 2.0f, -4.0f };
    auto objectUpVector         = vector3 { 0.0f, 1.0f, 0.0f };

    matrix4 expected;

    expected.m11 = 0.799999952f;
    expected.m12 = 0;
    expected.m13 = 0.599999964f;
    expected.m14 = 0;

    expected.m21 = -0.2228344f;
    expected.m22 = 0.928476632f;
    expected.m23 = 0.297112525f;
    expected.m24 = 0;

    expected.m31 = -0.557086f;
    expected.m32 = -0.371390671f;
    expected.m33 = 0.742781341f;
    expected.m34 = 0;

    expected.m41 = 10;
    expected.m42 = 20;
    expected.m43 = 30;
    expected.m44 = 1.0f;

    auto actual = matrix::create_world(objectPosition, objectForwardDirection, objectUpVector);

    EXPECT_TRUE(equality_helper::equal(expected, actual));

    EXPECT_EQ(objectPosition, matrix::translation(actual));
    EXPECT_TRUE(vector::dot(vector::normalize(objectUpVector), { actual.m21, actual.m22, actual.m23 }) > 0);
    EXPECT_TRUE(
        vector::dot(vector::normalize(objectForwardDirection), { -actual.m31, -actual.m32, -actual.m33 }) > 0.999f);
}

// A test for CreateOrtho (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_orthographic)
{
    auto width      = 100.0f;
    auto height     = 200.0f;
    auto zNearPlane = 1.5f;
    auto zFarPlane  = 1000.0f;

    matrix4 expected;

    expected.m11 = 0.02f;
    expected.m22 = 0.01f;
    expected.m33 = -0.00100150227f;
    expected.m43 = -0.00150225335f;
    expected.m44 = 1.0f;

    auto actual = matrix::create_orthographic(width, height, zNearPlane, zFarPlane);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for CreateOrthoOffCenter (float, float, float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_orthographic_off_center)
{
    auto left       = 10.0f;
    auto right      = 90.0f;
    auto bottom     = 20.0f;
    auto top        = 180.0f;
    auto zNearPlane = 1.5f;
    auto zFarPlane  = 1000.0f;

    matrix4 expected;

    expected.m11 = 0.025f;
    expected.m22 = 0.0125f;
    expected.m33 = -0.00100150227f;
    expected.m41 = -1.25f;
    expected.m42 = -1.25f;
    expected.m43 = -0.00150225335f;
    expected.m44 = 1.0f;

    auto actual = matrix::create_orthographic_off_center(left, right, bottom, top, zNearPlane, zFarPlane);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for CreatePerspective (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_perspective)
{
    auto width      = 100.0f;
    auto height     = 200.0f;
    auto zNearPlane = 1.5f;
    auto zFarPlane  = 1000.0f;

    matrix4 expected;

    expected.m11 = 0.03f;
    expected.m22 = 0.015f;
    expected.m33 = -1.00150228f;
    expected.m34 = -1.0f;
    expected.m43 = -1.50225341f;

    auto actual = matrix::create_perspective(width, height, zNearPlane, zFarPlane);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for CreatePerspective (float, float, float, float)
// CreatePerspective test where znear = zfar
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_perspective_where_znear_equals_zfar)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    auto width      = 100.0f;
    auto height     = 200.0f;
    auto zNearPlane = 0.0f;
    auto zFarPlane  = 0.0f;

    EXPECT_DEATH(matrix::create_perspective(width, height, zNearPlane, zFarPlane), "");
}

// A test for CreatePerspective (float, float, float, float)
// CreatePerspective test where near plane is negative value
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_perspective_where_near_plane_is_negative)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(matrix::create_perspective(10, 10, -10, 10), "");
}

// A test for CreatePerspective (float, float, float, float)
// CreatePerspective test where far plane is negative value
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_perspective_where_far_plane_is_negative)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(matrix::create_perspective(10, 10, 10, -10), "");
}

// A test for CreatePerspective (float, float, float, float)
// CreatePerspective test where near plane is beyond far plane
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_perspective_where_near_plane_is_beyond_far_plane)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(matrix::create_perspective(10, 10, 10, 1), "");
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_perspective_field_of_view1)
{
    radians fieldOfView = degrees(30.0f);
    auto    aspectRatio = 1280.0f / 720.0f;
    auto    zNearPlane  = 1.5f;
    auto    zFarPlane   = 1000.0f;

    matrix4 expected;

    expected.m11 = 2.09927845f;
    expected.m22 = 3.73205066f;
    expected.m33 = -1.00150228f;
    expected.m34 = -1.0f;
    expected.m43 = -1.50225341f;

    auto actual = matrix::create_perspective_field_of_view(fieldOfView, aspectRatio, zNearPlane, zFarPlane);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// CreatePerspectiveFieldOfView test where filedOfView is negative value.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_perspective_field_of_view_where_field_of_view_is_negative)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(matrix::create_perspective_field_of_view(radians { -1 }, 1.0f, 1.0f, 10.0f), "");
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// CreatePerspectiveFieldOfView test where filedOfView is more than pi.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_perspective_field_of_view_where_field_of_view_is_greather_than_pi)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(matrix::create_perspective_field_of_view(radians { pi<> + 0.01f }, 1.0f, 1.0f, 10.0f), "");
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// CreatePerspectiveFieldOfView test where nearPlaneDistance is negative value.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_perspective_field_of_view_where_near_plane_is_negative)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(matrix::create_perspective_field_of_view(radians { pi_over_4<> }, 1.0f, -1.0f, 10.0f), "");
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// CreatePerspectiveFieldOfView test where farPlaneDistance is negative value.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_perspective_field_of_view_where_far_plane_is_negative)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(matrix::create_perspective_field_of_view(radians { pi_over_4<> }, 1.0f, 1.0f, -10.0f), "");
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// CreatePerspectiveFieldOfView test where nearPlaneDistance is larger than farPlaneDistance.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_perspective_field_of_view_where_near_plane_is_larger_than_far_plane)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(matrix::create_perspective_field_of_view(radians { pi_over_4<> }, 1.0f, 10.0f, 1.0f), "");
}

// A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_perspective_off_center)
{
    auto left       = 10.0f;
    auto right      = 90.0f;
    auto bottom     = 20.0f;
    auto top        = 180.0f;
    auto zNearPlane = 1.5f;
    auto zFarPlane  = 1000.0f;

    matrix4 expected;

    expected.m11 = 0.0375f;
    expected.m22 = 0.01875f;
    expected.m31 = 1.25f;
    expected.m32 = 1.25f;
    expected.m33 = -1.00150228f;
    expected.m34 = -1.0f;
    expected.m43 = -1.50225341f;

    auto actual = matrix::create_perspective_off_center(left, right, bottom, top, zNearPlane, zFarPlane);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)
// CreatePerspectiveOffCenter test where nearPlaneDistance is negative.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_perspective_off_center_where_near_plane_is_negative)
{
    EXPECT_DEATH(matrix::create_perspective_off_center(10.0f, 90.0f, 20.0f, 180.0f, -1.0f, 10.0f), "");
}

// A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)
// CreatePerspectiveOffCenter test where farPlaneDistance is negative.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_perspective_off_center_where_far_plane_is_negative)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(matrix::create_perspective_off_center(10.0f, 90.0f, 20.0f, 180.0f, 1.0f, -10.0f), "");
}

// A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)
// CreatePerspectiveOffCenter test where test where nearPlaneDistance is larger than farPlaneDistance.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_perspective_off_center_where_near_plane_is_larger_than_far_plane)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(matrix::create_perspective_off_center(10.0f, 90.0f, 20.0f, 180.0f, 10.0f, 1.0f), "");
}

// A test for Invert (Matrix)
// Non invertible matrix - determinant is zero - singular matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, invert_non_invertible_matrix)
{
    matrix4 a = { 1.0f , 2.0f , 3.0f , 4.0f
                , 5.0f , 6.0f , 7.0f , 8.0f
                , 9.0f , 10.0f, 11.0f, 12.0f
                , 13.0f, 14.0f, 15.0f, 16.0f };

    float detA = matrix::determinant(a);

    EXPECT_TRUE(equality_helper::equal(detA, 0.0f));

    auto actual = matrix::invert(a);

    // all the elements in Actual is NaN
    EXPECT_TRUE(is_nan(actual.m11));
    EXPECT_TRUE(is_nan(actual.m12));
    EXPECT_TRUE(is_nan(actual.m13));
    EXPECT_TRUE(is_nan(actual.m14));
    EXPECT_TRUE(is_nan(actual.m21));
    EXPECT_TRUE(is_nan(actual.m22));
    EXPECT_TRUE(is_nan(actual.m23));
    EXPECT_TRUE(is_nan(actual.m24));
    EXPECT_TRUE(is_nan(actual.m31));
    EXPECT_TRUE(is_nan(actual.m32));
    EXPECT_TRUE(is_nan(actual.m33));
    EXPECT_TRUE(is_nan(actual.m34));
    EXPECT_TRUE(is_nan(actual.m41));
    EXPECT_TRUE(is_nan(actual.m42));
    EXPECT_TRUE(is_nan(actual.m43));
    EXPECT_TRUE(is_nan(actual.m44));
}

// A test for Lerp (Matrix, Matrix, float)
TEST_F(basic_matrix4_test, lerp)
{
    matrix4 a;

    a.m11 = 11.0f;
    a.m12 = 12.0f;
    a.m13 = 13.0f;
    a.m14 = 14.0f;
    a.m21 = 21.0f;
    a.m22 = 22.0f;
    a.m23 = 23.0f;
    a.m24 = 24.0f;
    a.m31 = 31.0f;
    a.m32 = 32.0f;
    a.m33 = 33.0f;
    a.m34 = 34.0f;
    a.m41 = 41.0f;
    a.m42 = 42.0f;
    a.m43 = 43.0f;
    a.m44 = 44.0f;

    auto b = basic_matrix4_test::generate_matrix_number_from_1_to_16();
    auto t = 0.5f;

    matrix4 expected;

    expected.m11 = a.m11 + (b.m11 - a.m11) * t;
    expected.m12 = a.m12 + (b.m12 - a.m12) * t;
    expected.m13 = a.m13 + (b.m13 - a.m13) * t;
    expected.m14 = a.m14 + (b.m14 - a.m14) * t;

    expected.m21 = a.m21 + (b.m21 - a.m21) * t;
    expected.m22 = a.m22 + (b.m22 - a.m22) * t;
    expected.m23 = a.m23 + (b.m23 - a.m23) * t;
    expected.m24 = a.m24 + (b.m24 - a.m24) * t;

    expected.m31 = a.m31 + (b.m31 - a.m31) * t;
    expected.m32 = a.m32 + (b.m32 - a.m32) * t;
    expected.m33 = a.m33 + (b.m33 - a.m33) * t;
    expected.m34 = a.m34 + (b.m34 - a.m34) * t;

    expected.m41 = a.m41 + (b.m41 - a.m41) * t;
    expected.m42 = a.m42 + (b.m42 - a.m42) * t;
    expected.m43 = a.m43 + (b.m43 - a.m43) * t;
    expected.m44 = a.m44 + (b.m44 - a.m44) * t;

    auto actual = matrix::lerp(a, b, t);
    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator - (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, unary_negation)
{
    auto a = basic_matrix4_test::generate_matrix_number_from_1_to_16();

    matrix4 expected;

    expected.m11 = -1.0f;
    expected.m12 = -2.0f;
    expected.m13 = -3.0f;
    expected.m14 = -4.0f;
    expected.m21 = -5.0f;
    expected.m22 = -6.0f;
    expected.m23 = -7.0f;
    expected.m24 = -8.0f;
    expected.m31 = -9.0f;
    expected.m32 = -10.0f;
    expected.m33 = -11.0f;
    expected.m34 = -12.0f;
    expected.m41 = -13.0f;
    expected.m42 = -14.0f;
    expected.m43 = -15.0f;
    expected.m44 = -16.0f;

    auto actual = -a;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator - (Matrix, Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, subtraction)
{
    auto a = basic_matrix4_test::generate_matrix_number_from_1_to_16();
    auto b = basic_matrix4_test::generate_matrix_number_from_1_to_16();

    matrix4 expected;

    auto actual = a - b;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Multiply (Matrix, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, multiply_by_scalar)
{
    auto a        = basic_matrix4_test::generate_matrix_number_from_1_to_16();
    auto expected = matrix4 { 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48 };
    auto actual   = a * 3.0f;

    EXPECT_EQ(expected, actual);
}

// A test for operator * (Matrix, Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, multiply)
{
    auto a = basic_matrix4_test::generate_matrix_number_from_1_to_16();
    auto b = basic_matrix4_test::generate_matrix_number_from_1_to_16();

    matrix4 expected;

    expected.m11 = (a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31 + a.m14 * b.m41);
    expected.m12 = (a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32 + a.m14 * b.m42);
    expected.m13 = (a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33 + a.m14 * b.m43);
    expected.m14 = (a.m11 * b.m14 + a.m12 * b.m24 + a.m13 * b.m34 + a.m14 * b.m44);

    expected.m21 = (a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31 + a.m24 * b.m41);
    expected.m22 = (a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32 + a.m24 * b.m42);
    expected.m23 = (a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33 + a.m24 * b.m43);
    expected.m24 = (a.m21 * b.m14 + a.m22 * b.m24 + a.m23 * b.m34 + a.m24 * b.m44);

    expected.m31 = (a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31 + a.m34 * b.m41);
    expected.m32 = (a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32 + a.m34 * b.m42);
    expected.m33 = (a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33 + a.m34 * b.m43);
    expected.m34 = (a.m31 * b.m14 + a.m32 * b.m24 + a.m33 * b.m34 + a.m34 * b.m44);

    expected.m41 = (a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31 + a.m44 * b.m41);
    expected.m42 = (a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32 + a.m44 * b.m42);
    expected.m43 = (a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33 + a.m44 * b.m43);
    expected.m44 = (a.m41 * b.m14 + a.m42 * b.m24 + a.m43 * b.m34 + a.m44 * b.m44);

    auto actual = a * b;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator * (Matrix, Matrix)
// Multiply with identity matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, multiply2)
{
    matrix4 a = {  1.0f,   2.0f,  3.0f,   4.0f
                ,  5.0f,  -6.0f,  7.0f,  -8.0f
                ,  9.0f,  10.0f, 11.0f,  12.0f
                , 13.0f, -14.0f, 15.0f, -16.0f };

    auto b = matrix4::identity();

    auto expected = a;
    auto actual   = a * b;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for operator + (Matrix, Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, addition)
{
    auto a = basic_matrix4_test::generate_matrix_number_from_1_to_16();
    auto b = basic_matrix4_test::generate_matrix_number_from_1_to_16();

    matrix4 expected = { a.m11 + b.m11, a.m12 + b.m12, a.m13 + b.m13, a.m14 + b.m14
                       , a.m21 + b.m21, a.m22 + b.m22, a.m23 + b.m23, a.m24 + b.m24
                       , a.m31 + b.m31, a.m32 + b.m32, a.m33 + b.m33, a.m34 + b.m34
                       , a.m41 + b.m41, a.m42 + b.m42, a.m43 + b.m43, a.m44 + b.m44 };

    auto actual = a + b;

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transpose (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, transpose1)
{
    auto a = basic_matrix4_test::generate_matrix_number_from_1_to_16();

    matrix4 expected = { a.m11, a.m21, a.m31, a.m41
                       , a.m12, a.m22, a.m32, a.m42
                       , a.m13, a.m23, a.m33, a.m43
                       , a.m14, a.m24, a.m34, a.m44 };

    auto actual = matrix::transpose(a);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Transpose (Matrix)
// Transpose Identity matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, transpose_identity_matrix)
{
    auto a        = matrix4::identity();
    auto expected = matrix4::identity();
    auto actual   = matrix::transpose(a);

    EXPECT_TRUE(equality_helper::equal(expected, actual));
}

// A test for Matrix (quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_from_quaternion)
{
    auto    axis  = vector::normalize(vector3 { 1.0f, 2.0f, 3.0f });
    radians angle = degrees(30.0f);
    auto    q     = quat::create_from_axis_angle(axis, angle);

    matrix4 expected = { 0.875595033f, 0.420031041f, -0.2385524f , 0.0f
                       , -0.38175258f, 0.904303849f,   0.1910483f, 0.0f
                       , 0.295970082f, -0.07621294f, 0.952151954f, 0.0f
                       ,         0.0f,         0.0f,         0.0f, 1.0f };

    auto target = matrix::create_from_quaternion(q);

    EXPECT_TRUE(equality_helper::equal(expected, target));
}

// A test for Fromquaternion (Matrix)
// Convert X axis rotation matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_from_quaternion_convert_x_axis_rotation_matrix)
{
    for (degrees angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        radians rads     = angle;
        auto    quat     = quat::create_from_axis_angle(vector3::unit_x(), rads);
        auto    expected = matrix::create_rotation_x(rads);
        auto    actual   = matrix::create_from_quaternion(quat);

        EXPECT_TRUE(equality_helper::equal(expected, actual));

        // make sure convert back to quaternion is same as we passed quaternion.
        auto q2 = quat::create_from_rotation_matrix(actual);

        EXPECT_TRUE(equality_helper::equal_rotation(quat, q2));
    }
}

// A test for Fromquaternion (Matrix)
// Convert Y axis rotation matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_from_quaternion_convert_y_axis_rotation_matrix)
{
    for (degrees angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        radians rads     = angle;
        auto    quat     = quat::create_from_axis_angle(vector3::unit_y(), rads);
        auto    expected = matrix::create_rotation_y(rads);
        auto    actual   = matrix::create_from_quaternion(quat);

        EXPECT_TRUE(equality_helper::equal(expected, actual));

        // make sure convert back to quaternion is same as we passed quaternion.
        auto q2 = quat::create_from_rotation_matrix(actual);

        EXPECT_TRUE(equality_helper::equal_rotation(quat, q2));
    }
}

// A test for Fromquaternion (Matrix)
// Convert Z axis rotation matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_from_quaternion_convert_z_axis_rotation_matrix)
{
    for (degrees angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        radians rads     = angle;
        auto    quat     = quat::create_from_axis_angle(vector3::unit_z(), rads);
        auto    expected = matrix::create_rotation_z(rads);
        auto    actual   = matrix::create_from_quaternion(quat);

        EXPECT_TRUE(equality_helper::equal(expected, actual));

        // make sure convert back to quaternion is same as we passed quaternion.
        auto q2 = quat::create_from_rotation_matrix(actual);

        EXPECT_TRUE(equality_helper::equal_rotation(quat, q2));
    }
}

// A test for Fromquaternion (Matrix)
// Convert XYZ axis rotation matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_from_quaternion_convert_xyz_axis_rotation_matrix)
{
    const auto step = 10.0f;

    for (degrees angle; angle < 720.0f; angle += step)
    {
        radians rads = degrees { angle };
        auto    quat = quat::create_from_axis_angle(vector3::unit_z(), rads)
                     * quat::create_from_axis_angle(vector3::unit_y(), rads)
                     * quat::create_from_axis_angle(vector3::unit_x(), rads);

        auto expected = matrix::create_rotation_x(rads)
                      * matrix::create_rotation_y(rads)
                      * matrix::create_rotation_z(rads);

        auto actual = matrix::create_from_quaternion(quat);

        EXPECT_TRUE(equality_helper::equal(expected, actual));

        // make sure convert back to quaternion is same as we passed quaternion.
        auto q2 = quat::create_from_rotation_matrix(actual);

        EXPECT_TRUE(equality_helper::equal_rotation(quat, q2));
    }
}

// A test for negate (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, negate)
{
    auto m        = basic_matrix4_test::generate_matrix_number_from_1_to_16();
    auto expected = matrix4 {  -1.0f,  -2.0f,  -3.0f,  -4.0f
                            ,  -5.0f,  -6.0f,  -7.0f,  -8.0f
                            ,  -9.0f, -10.0f, -11.0f, -12.0f
                            , -13.0f, -14.0f, -15.0f, -16.0f };

    auto actual = matrix::negate(m);

    EXPECT_EQ(expected, actual);
}

// A test for operator != (Matrix, Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, inequality)
{
    auto a = basic_matrix4_test::generate_matrix_number_from_1_to_16();
    auto b = basic_matrix4_test::generate_matrix_number_from_1_to_16();

    // case 1: compare between same values
    bool expected = false;
    bool actual   = a != b;

    EXPECT_EQ(expected, actual);

    // case 2: compare between different values
    b.m11 = 11.0f;

    expected = true;
    actual   = a != b;

    EXPECT_EQ(expected, actual);
}

// A test for operator == (Matrix, Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, equality)
{
    auto a = basic_matrix4_test::generate_matrix_number_from_1_to_16();
    auto b = basic_matrix4_test::generate_matrix_number_from_1_to_16();

    // case 1: compare between same values
    bool expected = true;
    bool actual   = a == b;

    EXPECT_EQ(expected, actual);

    // case 2: compare between different values
    b.m11 = 11.0f;

    expected = false;
    actual   = a == b;

    EXPECT_EQ(expected, actual);
}

// A test for CreateScale (vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_scale)
{
    auto scales   = vector3 { 2.0f, 3.0f, 4.0f };
    auto expected = matrix4 { 2.0f, 0.0f, 0.0f, 0.0f
                            , 0.0f, 3.0f, 0.0f, 0.0f
                            , 0.0f, 0.0f, 4.0f, 0.0f
                            , 0.0f, 0.0f, 0.0f, 1.0f };

    auto actual = matrix::create_scale(scales);

    EXPECT_EQ(expected, actual);
}

// A test for CreateScale (vector3f, vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_scale_center)
{
    auto scale  = vector3 { 3, 4, 5 };
    auto center = vector3 { 23, 42, 666 };

    auto scaleAroundZero         = matrix::create_scale(scale, vector3::zero());
    auto scaleAroundZeroExpected = matrix::create_scale(scale);

    EXPECT_TRUE(equality_helper::equal(scaleAroundZero, scaleAroundZeroExpected));

    auto scaleAroundCenter         = matrix::create_scale(scale, center);
    auto scaleAroundCenterExpected = matrix::create_translation(-center)
                                   * matrix::create_scale(scale)
                                   * matrix::create_translation(center);

    EXPECT_TRUE(equality_helper::equal(scaleAroundCenter, scaleAroundCenterExpected));
}

// A test for CreateScale (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_scale2)
{
    float   scale    = 2.0f;
    matrix4 expected = { 2.0f, 0.0f, 0.0f, 0.0f
                       , 0.0f, 2.0f, 0.0f, 0.0f
                       , 0.0f, 0.0f, 2.0f, 0.0f
                       , 0.0f, 0.0f, 0.0f, 1.0f };

    auto actual = matrix::create_scale(scale);

    EXPECT_EQ(expected, actual);
}

// A test for CreateScale (float, vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_scale3)
{
    float scale  = 5;
    auto  center = vector3 { 23, 42, 666 };

    auto scaleAroundZero         = matrix::create_scale(scale, vector3::zero());
    auto scaleAroundZeroExpected = matrix::create_scale(scale);

    EXPECT_TRUE(equality_helper::equal(scaleAroundZero, scaleAroundZeroExpected));

    auto scaleAroundCenter         = matrix::create_scale(scale, center);
    auto scaleAroundCenterExpected = matrix::create_translation(-center)
                                   * matrix::create_scale(scale)
                                   * matrix::create_translation(center);

    EXPECT_TRUE(equality_helper::equal(scaleAroundCenter, scaleAroundCenterExpected));
}

// A test for CreateScale (float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_scale4)
{
    auto    xScale   = 2.0f;
    auto    yScale   = 3.0f;
    auto    zScale   = 4.0f;
    matrix4 expected = { 2.0f, 0.0f, 0.0f, 0.0f
                       , 0.0f, 3.0f, 0.0f, 0.0f
                       , 0.0f, 0.0f, 4.0f, 0.0f
                       , 0.0f, 0.0f, 0.0f, 1.0f };

    auto actual = matrix::create_scale(xScale, yScale, zScale);

    EXPECT_EQ(expected, actual);
}

// A test for CreateScale (float, float, float, vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_scale5)
{
    auto scale  = vector3 { 3, 4, 5 };
    auto center = vector3 { 23, 42, 666 };

    auto scaleAroundZero         = matrix::create_scale(scale.x, scale.y, scale.z, vector3::zero());
    auto scaleAroundZeroExpected = matrix::create_scale(scale.x, scale.y, scale.z);

    EXPECT_TRUE(equality_helper::equal(scaleAroundZero, scaleAroundZeroExpected));

    auto scaleAroundCenter         = matrix::create_scale(scale.x, scale.y, scale.z, center);
    auto scaleAroundCenterExpected = matrix::create_translation(-center)
                                   * matrix::create_scale(scale.x, scale.y, scale.z)
                                   * matrix::create_translation(center);

    EXPECT_TRUE(equality_helper::equal(scaleAroundCenter, scaleAroundCenterExpected));
}

// A test for CreateTranslation (vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_translation)
{
    vector3 position = { 2.0f, 3.0f, 4.0f };
    matrix4 expected = { 1.0f, 0.0f, 0.0f, 0.0f
                       , 0.0f, 1.0f, 0.0f, 0.0f
                       , 0.0f, 0.0f, 1.0f, 0.0f
                       , 2.0f, 3.0f, 4.0f, 1.0f };

    auto actual = matrix::create_translation(position);

    EXPECT_EQ(expected, actual);
}

// A test for CreateTranslation (float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_translation1)
{
    float  xPosition = 2.0f;
    float  yPosition = 3.0f;
    float  zPosition = 4.0f;
    matrix4 expected = { 1.0f, 0.0f, 0.0f, 0.0f
                       , 0.0f, 1.0f, 0.0f, 0.0f
                       , 0.0f, 0.0f, 1.0f, 0.0f
                       , 2.0f, 3.0f, 4.0f, 1.0f };

    auto actual = matrix::create_translation(xPosition, yPosition, zPosition);

    EXPECT_EQ(expected, actual);
}

// A test for Translation
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_translation2)
{
    auto a = basic_matrix4_test::generate_test_matrix();
    auto b = a;

    // Transfomed vector that has same semantics of property must be same.
    auto val = vector3 { a.m41, a.m42, a.m43 };

    EXPECT_EQ(val, matrix::translation(a));

    // Set value and get value must be same.
    val = vector3 { 1.0f, 2.0f, 3.0f };

    matrix::translation(a, val);

    EXPECT_EQ(val, matrix::translation(a));

    // Make sure it only modifies expected value of matrix.
    EXPECT_TRUE(a.m11 == b.m11 && a.m12 == b.m12 && a.m13 == b.m13 && a.m14 == b.m14
             && a.m21 == b.m21 && a.m22 == b.m22 && a.m23 == b.m23 && a.m24 == b.m24
             && a.m31 == b.m31 && a.m32 == b.m32 && a.m33 == b.m33 && a.m34 == b.m34
             && a.m41 != b.m41 && a.m42 != b.m42 && a.m43 != b.m43 && a.m44 == b.m44);
}

// A test for IsIdentity
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, is_identity)
{
    EXPECT_TRUE (matrix::is_identity(matrix4::identity()));
    EXPECT_TRUE (matrix::is_identity(matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
    EXPECT_FALSE(matrix::is_identity(matrix4(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
    EXPECT_FALSE(matrix::is_identity(matrix4(1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
    EXPECT_FALSE(matrix::is_identity(matrix4(1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
    EXPECT_FALSE(matrix::is_identity(matrix4(1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
    EXPECT_FALSE(matrix::is_identity(matrix4(1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
    EXPECT_FALSE(matrix::is_identity(matrix4(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
    EXPECT_FALSE(matrix::is_identity(matrix4(1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
    EXPECT_FALSE(matrix::is_identity(matrix4(1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1)));
    EXPECT_FALSE(matrix::is_identity(matrix4(1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1)));
    EXPECT_FALSE(matrix::is_identity(matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1)));
    EXPECT_FALSE(matrix::is_identity(matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)));
    EXPECT_FALSE(matrix::is_identity(matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1)));
    EXPECT_FALSE(matrix::is_identity(matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1)));
    EXPECT_FALSE(matrix::is_identity(matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1)));
    EXPECT_FALSE(matrix::is_identity(matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1)));
    EXPECT_FALSE(matrix::is_identity(matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0)));
}

// A test for Matrix comparison involving NaN values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, EqualsNan)
{
    matrix4 a = { nan<>, 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    };
    matrix4 b = { 0    , nan<>, 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    };
    matrix4 c = { 0    , 0    , nan<>, 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    };
    matrix4 d = { 0    , 0    , 0    , nan<>, 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    };
    matrix4 e = { 0    , 0    , 0    , 0    , nan<>, 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    };
    matrix4 f = { 0    , 0    , 0    , 0    , 0    , nan<>, 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    };
    matrix4 g = { 0    , 0    , 0    , 0    , 0    , 0    , nan<>, 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    };
    matrix4 h = { 0    , 0    , 0    , 0    , 0    , 0    , 0    , nan<>, 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    };
    matrix4 i = { 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , nan<>, 0    , 0    , 0    , 0    , 0    , 0    , 0    };
    matrix4 j = { 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , nan<>, 0    , 0    , 0    , 0    , 0    , 0    };
    matrix4 k = { 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , nan<>, 0    , 0    , 0    , 0    , 0    };
    matrix4 l = { 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , nan<>, 0    , 0    , 0    , 0    };
    matrix4 m = { 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , nan<>, 0    , 0    , 0    };
    matrix4 n = { 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , nan<>, 0    , 0    };
    matrix4 o = { 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , nan<>, 0    };
    matrix4 p = { 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , nan<>};

    EXPECT_FALSE(a == matrix4 {});
    EXPECT_FALSE(b == matrix4 {});
    EXPECT_FALSE(c == matrix4 {});
    EXPECT_FALSE(d == matrix4 {});
    EXPECT_FALSE(e == matrix4 {});
    EXPECT_FALSE(f == matrix4 {});
    EXPECT_FALSE(g == matrix4 {});
    EXPECT_FALSE(h == matrix4 {});
    EXPECT_FALSE(i == matrix4 {});
    EXPECT_FALSE(j == matrix4 {});
    EXPECT_FALSE(k == matrix4 {});
    EXPECT_FALSE(l == matrix4 {});
    EXPECT_FALSE(m == matrix4 {});
    EXPECT_FALSE(n == matrix4 {});
    EXPECT_FALSE(o == matrix4 {});
    EXPECT_FALSE(p == matrix4 {});

    EXPECT_TRUE(a != matrix4 {});
    EXPECT_TRUE(b != matrix4 {});
    EXPECT_TRUE(c != matrix4 {});
    EXPECT_TRUE(d != matrix4 {});
    EXPECT_TRUE(e != matrix4 {});
    EXPECT_TRUE(f != matrix4 {});
    EXPECT_TRUE(g != matrix4 {});
    EXPECT_TRUE(h != matrix4 {});
    EXPECT_TRUE(i != matrix4 {});
    EXPECT_TRUE(j != matrix4 {});
    EXPECT_TRUE(k != matrix4 {});
    EXPECT_TRUE(l != matrix4 {});
    EXPECT_TRUE(m != matrix4 {});
    EXPECT_TRUE(n != matrix4 {});
    EXPECT_TRUE(o != matrix4 {});
    EXPECT_TRUE(p != matrix4 {});

    EXPECT_FALSE(matrix::is_identity(a));
    EXPECT_FALSE(matrix::is_identity(b));
    EXPECT_FALSE(matrix::is_identity(c));
    EXPECT_FALSE(matrix::is_identity(d));
    EXPECT_FALSE(matrix::is_identity(e));
    EXPECT_FALSE(matrix::is_identity(f));
    EXPECT_FALSE(matrix::is_identity(g));
    EXPECT_FALSE(matrix::is_identity(h));
    EXPECT_FALSE(matrix::is_identity(i));
    EXPECT_FALSE(matrix::is_identity(j));
    EXPECT_FALSE(matrix::is_identity(k));
    EXPECT_FALSE(matrix::is_identity(l));
    EXPECT_FALSE(matrix::is_identity(m));
    EXPECT_FALSE(matrix::is_identity(n));
    EXPECT_FALSE(matrix::is_identity(o));
    EXPECT_FALSE(matrix::is_identity(p));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(basic_matrix4_test, create_reflection)
{
//    // XY plane.
//    basic_matrix4_test::CreateReflection({ vector3::unit_z(), 0 }, matrix::create_scale(1, 1, -1));
//    // XZ plane.
//    basic_matrix4_test::CreateReflection({ vector3::unit_y(), 0 }, matrix::create_scale(1, -1, 1));
//    // YZ plane.
//    basic_matrix4_test::CreateReflection({ vector3::unit_x(), 0 }, matrix::create_scale(-1, 1, 1));

//    // Complex cases.
//    auto planes = std::vector<Plane>();

//    planes.push_back({  0, 1, 0, 0 });
//    planes.push_back({  1, 2, 3, 4 });
//    planes.push_back({  5, 6, 7, 8 });
//    planes.push_back({ -1,-2,-3,-4 });
//    planes.push_back({ -5,-6,-7,-8 });

//    auto points = std::vector<vector3>();

//    points.push_back({  1, 2, 3 });
//    points.push_back({  5, 6, 7 });
//    points.push_back({ -1,-2,-3 });
//    points.push_back({ -5,-6,-7 });

//    for (auto& p : planes)
//    {
//        auto plane = Plane::normalize(p);
//        auto m     = matrix::create_reflection(plane);
//        auto pp    = -plane.d * plane.normal; // Position on the plane.

//        for (auto& point : points)
//        {
//            auto rp = vector3::transform(point, m);

//            // Manually compute reflection point and compare results.
//            auto  v  = point - pp;
//            float d  = vector::dot(v, plane.normal);
//            auto  vp = point - 2.0f * d * plane.normal;

//            EXPECT_TRUE(equality_helper::equal(rp, vp));
//        }
//    }
}

/*
// A test for Lerp (Matrix, Matrix, float)
[Fact]
public void MatrixLerpTest()
{
    Matrix a = new Matrix();
    a.M11 = 11.0f;
    a.M12 = 12.0f;
    a.M13 = 13.0f;
    a.M14 = 14.0f;
    a.M21 = 21.0f;
    a.M22 = 22.0f;
    a.M23 = 23.0f;
    a.M24 = 24.0f;
    a.M31 = 31.0f;
    a.M32 = 32.0f;
    a.M33 = 33.0f;
    a.M34 = 34.0f;
    a.M41 = 41.0f;
    a.M42 = 42.0f;
    a.M43 = 43.0f;
    a.M44 = 44.0f;

    Matrix b = GenerateMatrixNumberFrom1To16();

    float t = 0.5f;

    Matrix expected = new Matrix();
    expected.M11 = a.M11 + (b.M11 - a.M11) * t;
    expected.M12 = a.M12 + (b.M12 - a.M12) * t;
    expected.M13 = a.M13 + (b.M13 - a.M13) * t;
    expected.M14 = a.M14 + (b.M14 - a.M14) * t;

    expected.M21 = a.M21 + (b.M21 - a.M21) * t;
    expected.M22 = a.M22 + (b.M22 - a.M22) * t;
    expected.M23 = a.M23 + (b.M23 - a.M23) * t;
    expected.M24 = a.M24 + (b.M24 - a.M24) * t;

    expected.M31 = a.M31 + (b.M31 - a.M31) * t;
    expected.M32 = a.M32 + (b.M32 - a.M32) * t;
    expected.M33 = a.M33 + (b.M33 - a.M33) * t;
    expected.M34 = a.M34 + (b.M34 - a.M34) * t;

    expected.M41 = a.M41 + (b.M41 - a.M41) * t;
    expected.M42 = a.M42 + (b.M42 - a.M42) * t;
    expected.M43 = a.M43 + (b.M43 - a.M43) * t;
    expected.M44 = a.M44 + (b.M44 - a.M44) * t;

    Matrix actual;
    actual = Matrix.Lerp(a, b, t);
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.Lerp did not return the expected value.");
}

private void CreateBillboardFact(vector3 placeDirection, vector3 cameraUpVector, Matrix expectedRotation)
{
    vector3 cameraPosition = new vector3(3.0f, 4.0f, 5.0f);
    vector3 objectPosition = cameraPosition + placeDirection * 10.0f;
    Matrix expected = expectedRotation * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateBillboard(objectPosition, cameraPosition, cameraUpVector, new vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateBillboard did not return the expected value.");
}

// A test for CreateBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Forward side of camera on XZ-plane
[Fact]
public void MatrixCreateBillboardTest01()
{
    // Object placed at Forward of camera. result must be same as 180 degrees rotate along y-axis.
    CreateBillboardFact(new vector3(0, 0, -1), new vector3(0, 1, 0), Matrix.CreateRotationY(MathHelper.ToRadians(180.0f)));
}

// A test for CreateBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Backward side of camera on XZ-plane
[Fact]
public void MatrixCreateBillboardTest02()
{
    // Object placed at Backward of camera. This result must be same as 0 degrees rotate along y-axis.
    CreateBillboardFact(new vector3(0, 0, 1), new vector3(0, 1, 0), Matrix.CreateRotationY(MathHelper.ToRadians(0)));
}

// A test for CreateBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Right side of camera on XZ-plane
[Fact]
public void MatrixCreateBillboardTest03()
{
    // Place object at Right side of camera. This result must be same as 90 degrees rotate along y-axis.
    CreateBillboardFact(new vector3(1, 0, 0), new vector3(0, 1, 0), Matrix.CreateRotationY(MathHelper.ToRadians(90)));
}

// A test for CreateBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Left side of camera on XZ-plane
[Fact]
public void MatrixCreateBillboardTest04()
{
    // Place object at Left side of camera. This result must be same as -90 degrees rotate along y-axis.
    CreateBillboardFact(new vector3(-1, 0, 0), new vector3(0, 1, 0), Matrix.CreateRotationY(MathHelper.ToRadians(-90)));
}

// A test for CreateBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Up side of camera on XY-plane
[Fact]
public void MatrixCreateBillboardTest05()
{
    // Place object at Up side of camera. result must be same as 180 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateBillboardFact(new vector3(0, 1, 0), new vector3(0, 0, 1),
                        Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(180)));
}

// A test for CreateBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Down side of camera on XY-plane
[Fact]
public void MatrixCreateBillboardTest06()
{
    // Place object at Down side of camera. result must be same as 0 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateBillboardFact(new vector3(0, -1, 0), new vector3(0, 0, 1),
                        Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(0)));
}

// A test for CreateBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Right side of camera on XY-plane
[Fact]
public void MatrixCreateBillboardTest07()
{
    // Place object at Right side of camera. result must be same as 90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateBillboardFact(new vector3(1, 0, 0), new vector3(0, 0, 1),
                        Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)));
}

// A test for CreateBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Left side of camera on XY-plane
[Fact]
public void MatrixCreateBillboardTest08()
{
    // Place object at Left side of camera. result must be same as -90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateBillboardFact(new vector3(-1, 0, 0), new vector3(0, 0, 1),
                        Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(-90.0f)));
}

// A test for CreateBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Up side of camera on YZ-plane
[Fact]
public void MatrixCreateBillboardTest09()
{
    // Place object at Up side of camera. result must be same as -90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateBillboardFact(new vector3(0, 1, 0), new vector3(-1, 0, 0),
                        Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationX(MathHelper.ToRadians(-90.0f)));
}

// A test for CreateBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Down side of camera on YZ-plane
[Fact]
public void MatrixCreateBillboardTest10()
{
    // Place object at Down side of camera. result must be same as 90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateBillboardFact(new vector3(0, -1, 0), new vector3(-1, 0, 0),
                        Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)));
}

// A test for CreateBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Forward side of camera on YZ-plane
[Fact]
public void MatrixCreateBillboardTest11()
{
    // Place object at Forward side of camera. result must be same as 180 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateBillboardFact(new vector3(0, 0, -1), new vector3(-1, 0, 0),
                        Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationX(MathHelper.ToRadians(180.0f)));
}

// A test for CreateBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Backward side of camera on YZ-plane
[Fact]
public void MatrixCreateBillboardTest12()
{
    // Place object at Backward side of camera. result must be same as 0 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateBillboardFact(new vector3(0, 0, 1), new vector3(-1, 0, 0),
                        Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationX(MathHelper.ToRadians(0.0f)));
}

// A test for CreateBillboard (vector3f, vector3f, vector3f, vector3f?)
// Object and camera positions are too close and doesn't pass cameraFowardVector.
[Fact]
public void MatrixCreateBillboardTooCloseTest1()
{
    vector3 objectPosition = new vector3(3.0f, 4.0f, 5.0f);
    vector3 cameraPosition = objectPosition;
    vector3 cameraUpVector = new vector3(0, 1, 0);

    // Doesn't pass camera face direction. CreateBillboard uses new vector3f(0, 0, -1) direction. Result must be same as 180 degrees rotate along y-axis.
    Matrix expected = Matrix.CreateRotationY(MathHelper.ToRadians(180.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateBillboard(objectPosition, cameraPosition, cameraUpVector, new vector3(0, 0, 1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateBillboard did not return the expected value.");
}

// A test for CreateBillboard (vector3f, vector3f, vector3f, vector3f?)
// Object and camera positions are too close and passed cameraFowardVector.
[Fact]
public void MatrixCreateBillboardTooCloseTest2()
{
    vector3 objectPosition = new vector3(3.0f, 4.0f, 5.0f);
    vector3 cameraPosition = objectPosition;
    vector3 cameraUpVector = new vector3(0, 1, 0);

    // Passes vector3f.Rgiht as camera face direction. Result must be same as -90 degrees rotate along y-axis.
    Matrix expected = Matrix.CreateRotationY(MathHelper.ToRadians(-90.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateBillboard(objectPosition, cameraPosition, cameraUpVector, new vector3(1, 0, 0));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateBillboard did not return the expected value.");
}

private void CreateConstrainedBillboardFact(vector3 placeDirection, vector3 rotateAxis, Matrix expectedRotation)
{
    vector3 cameraPosition = new vector3(3.0f, 4.0f, 5.0f);
    vector3 objectPosition = cameraPosition + placeDirection * 10.0f;
    Matrix expected = expectedRotation * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new vector3(0, 0, -1), new vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");

    // When you move camera along rotateAxis, result must be same.
    cameraPosition += rotateAxis * 10.0f;
    actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new vector3(0, 0, -1), new vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");

    cameraPosition -= rotateAxis * 30.0f;
    actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new vector3(0, 0, -1), new vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Forward side of camera on XZ-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest01()
{
    // Object placed at Forward of camera. result must be same as 180 degrees rotate along y-axis.
    CreateConstrainedBillboardFact(new vector3(0, 0, -1), new vector3(0, 1, 0), Matrix.CreateRotationY(MathHelper.ToRadians(180.0f)));
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Backward side of camera on XZ-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest02()
{
    // Object placed at Backward of camera. This result must be same as 0 degrees rotate along y-axis.
    CreateConstrainedBillboardFact(new vector3(0, 0, 1), new vector3(0, 1, 0), Matrix.CreateRotationY(MathHelper.ToRadians(0)));
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Right side of camera on XZ-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest03()
{
    // Place object at Right side of camera. This result must be same as 90 degrees rotate along y-axis.
    CreateConstrainedBillboardFact(new vector3(1, 0, 0), new vector3(0, 1, 0), Matrix.CreateRotationY(MathHelper.ToRadians(90)));
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Left side of camera on XZ-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest04()
{
    // Place object at Left side of camera. This result must be same as -90 degrees rotate along y-axis.
    CreateConstrainedBillboardFact(new vector3(-1, 0, 0), new vector3(0, 1, 0), Matrix.CreateRotationY(MathHelper.ToRadians(-90)));
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Up side of camera on XY-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest05()
{
    // Place object at Up side of camera. result must be same as 180 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateConstrainedBillboardFact(new vector3(0, 1, 0), new vector3(0, 0, 1),
                                   Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(180)));
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Down side of camera on XY-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest06()
{
    // Place object at Down side of camera. result must be same as 0 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateConstrainedBillboardFact(new vector3(0, -1, 0), new vector3(0, 0, 1),
                                   Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(0)));
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Right side of camera on XY-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest07()
{
    // Place object at Right side of camera. result must be same as 90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateConstrainedBillboardFact(new vector3(1, 0, 0), new vector3(0, 0, 1),
                                   Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)));
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Left side of camera on XY-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest08()
{
    // Place object at Left side of camera. result must be same as -90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateConstrainedBillboardFact(new vector3(-1, 0, 0), new vector3(0, 0, 1),
                                   Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(-90.0f)));
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Up side of camera on YZ-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest09()
{
    // Place object at Up side of camera. result must be same as -90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateConstrainedBillboardFact(new vector3(0, 1, 0), new vector3(-1, 0, 0),
                                   Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationX(MathHelper.ToRadians(-90.0f)));
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Down side of camera on YZ-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest10()
{
    // Place object at Down side of camera. result must be same as 90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateConstrainedBillboardFact(new vector3(0, -1, 0), new vector3(-1, 0, 0),
                                   Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)));
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Forward side of camera on YZ-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest11()
{
    // Place object at Forward side of camera. result must be same as 180 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateConstrainedBillboardFact(new vector3(0, 0, -1), new vector3(-1, 0, 0),
                                   Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationX(MathHelper.ToRadians(180.0f)));
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Place object at Backward side of camera on YZ-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest12()
{
    // Place object at Backward side of camera. result must be same as 0 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateConstrainedBillboardFact(new vector3(0, 0, 1), new vector3(-1, 0, 0),
                                   Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationX(MathHelper.ToRadians(0.0f)));
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Object and camera positions are too close and doesn't pass cameraForwardVector.
[Fact]
public void MatrixCreateConstrainedBillboardTooCloseTest1()
{
    vector3 objectPosition = new vector3(3.0f, 4.0f, 5.0f);
    vector3 cameraPosition = objectPosition;
    vector3 cameraUpVector = new vector3(0, 1, 0);

    // Doesn't pass camera face direction. CreateConstrainedBillboard uses new vector3f(0, 0, -1) direction. Result must be same as 180 degrees rotate along y-axis.
    Matrix expected = Matrix.CreateRotationY(MathHelper.ToRadians(180.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, cameraUpVector, new vector3(0, 0, 1), new vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Object and camera positions are too close and passed cameraForwardVector.
[Fact]
public void MatrixCreateConstrainedBillboardTooCloseTest2()
{
    vector3 objectPosition = new vector3(3.0f, 4.0f, 5.0f);
    vector3 cameraPosition = objectPosition;
    vector3 cameraUpVector = new vector3(0, 1, 0);

    // Passes vector3f.Rgiht as camera face direction. Result must be same as -90 degrees rotate along y-axis.
    Matrix expected = Matrix.CreateRotationY(MathHelper.ToRadians(-90.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, cameraUpVector, new vector3(1, 0, 0), new vector3(0, 0, -1));
    Assert.True(MathHelper.equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Angle between rotateAxis and camera to object vector is too small. And use doesn't passed objectForwardVector parameter.
[Fact]
public void MatrixCreateConstrainedBillboardAlongAxisTest1()
{
    // Place camera at up side of object.
    vector3 objectPosition = new vector3(3.0f, 4.0f, 5.0f);
    vector3 rotateAxis = new vector3(0, 1, 0);
    vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

    // In this case, CreateConstrainedBillboard picks new vector3f(0, 0, -1) as object forward vector.
    Matrix expected = Matrix.CreateRotationY(MathHelper.ToRadians(180.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new vector3(0, 0, -1), new vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Angle between rotateAxis and camera to object vector is too small. And user doesn't passed objectForwardVector parameter.
[Fact]
public void MatrixCreateConstrainedBillboardAlongAxisTest2()
{
    // Place camera at up side of object.
    vector3 objectPosition = new vector3(3.0f, 4.0f, 5.0f);
    vector3 rotateAxis = new vector3(0, 0, -1);
    vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

    // In this case, CreateConstrainedBillboard picks new vector3f(1, 0, 0) as object forward vector.
    Matrix expected = Matrix.CreateRotationX(MathHelper.ToRadians(-90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(-90.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new vector3(0, 0, -1), new vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Angle between rotateAxis and camera to object vector is too small. And user passed correct objectForwardVector parameter.
[Fact]
public void MatrixCreateConstrainedBillboardAlongAxisTest3()
{
    // Place camera at up side of object.
    vector3 objectPosition = new vector3(3.0f, 4.0f, 5.0f);
    vector3 rotateAxis = new vector3(0, 1, 0);
    vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

    // User passes correct objectForwardVector.
    Matrix expected = Matrix.CreateRotationY(MathHelper.ToRadians(180.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new vector3(0, 0, -1), new vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Angle between rotateAxis and camera to object vector is too small. And user passed incorrect objectForwardVector parameter.
[Fact]
public void MatrixCreateConstrainedBillboardAlongAxisTest4()
{
    // Place camera at up side of object.
    vector3 objectPosition = new vector3(3.0f, 4.0f, 5.0f);
    vector3 rotateAxis = new vector3(0, 1, 0);
    vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

    // User passes correct objectForwardVector.
    Matrix expected = Matrix.CreateRotationY(MathHelper.ToRadians(180.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new vector3(0, 0, -1), new vector3(0, 1, 0));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (vector3f, vector3f, vector3f, vector3f?)
// Angle between rotateAxis and camera to object vector is too small. And user passed incorrect objectForwardVector parameter.
[Fact]
public void MatrixCreateConstrainedBillboardAlongAxisTest5()
{
    // Place camera at up side of object.
    vector3 objectPosition = new vector3(3.0f, 4.0f, 5.0f);
    vector3 rotateAxis = new vector3(0, 0, -1);
    vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

    // In this case, CreateConstrainedBillboard picks vector3f.Right as object forward vector.
    Matrix expected = Matrix.CreateRotationX(MathHelper.ToRadians(-90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(-90.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new vector3(0, 0, -1), new vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");
}
*/
