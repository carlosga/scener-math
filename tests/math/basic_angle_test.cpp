// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "basic_angle_test.hpp"

#include <cstdint>

#include <scener/math/angle.hpp>

using namespace scener::math;

TEST_F(basic_angle_test, radians_constructor)
{
    radians angle { 1.35f };

    EXPECT_EQ(1.35f, angle);
}

TEST_F(basic_angle_test, degress_constructor)
{
    degrees angle { 180.0f };

    EXPECT_TRUE(180.0f == angle.value);
}

TEST_F(basic_angle_test, implicit_degrees_to_radians_conversions)
{
    degrees deg { 180.0f };
    radians rad = deg;

    EXPECT_EQ(180.0f, deg);
    EXPECT_EQ(pi<>  , rad);
}

TEST_F(basic_angle_test, implicit_radians_to_degrees_conversions)
{
    radians rad { pi<> };
    degrees deg = rad;

    EXPECT_EQ(pi<>  , rad);
    EXPECT_EQ(180.0f, deg);
}

TEST_F(basic_angle_test, equality_test)
{
    radians rad { pi<> };
    degrees deg = rad;

    EXPECT_TRUE(deg == rad);

    basic_radians<float>        rad1 { pi<> };
    basic_degrees<std::int32_t> deg1 { 180  };

    EXPECT_TRUE(rad1 == deg1);
}

TEST_F(basic_angle_test, ineequality_test)
{
    radians rad1 { pi<> };
    radians rad2 { pi_over_2<> };

    EXPECT_TRUE(rad1 != rad2);
}

TEST_F(basic_angle_test, sum_degrees)
{
    degrees deg1 { 90.0f };
    degrees deg2 { 90.0f };
    degrees sum  = deg1 + deg2;

    EXPECT_EQ(180.0f, sum);

    deg1 += deg2;

    EXPECT_EQ(180.0f, deg1);
}

TEST_F(basic_angle_test, sum_degrees_with_different_type)
{
    basic_degrees<float> deg1 { 90.0f };
    basic_degrees<int>   deg2 {    90 };

    auto sum = deg1 + deg2;

    EXPECT_EQ(180.0f, sum);
}

TEST_F(basic_angle_test, subtract_degrees)
{
    degrees deg1 { 180.0f };
    degrees deg2 {  90.0f };
    degrees sub  = deg1 - deg2;

    EXPECT_EQ(90.0f, sub);
}

TEST_F(basic_angle_test, subtract_degrees_with_different_type)
{
    basic_degrees<float> deg1 { 180.0f };
    basic_degrees<int>   deg2 {     90 };

    auto sub = deg1 - deg2;

    EXPECT_EQ(90.0f, sub);
}

TEST_F(basic_angle_test, multiply_degrees_by_floating_point_scalar)
{
    degrees deg1 { 90.0f };
    degrees deg  = deg1 * 2.0f;

    EXPECT_EQ(180.0f, deg);
}

TEST_F(basic_angle_test, multiply_degrees_by_integer_scalar)
{
    degrees deg1 { 90.0f };
    degrees deg  = deg1 * 2;

    EXPECT_EQ(180.0f, deg);
}

TEST_F(basic_angle_test, division)
{
    basic_degrees<float> deg1 { 180.0f };
    basic_degrees<float> deg2 {  90.0f };
    basic_degrees<float> deg  = deg1 / deg2;

    EXPECT_EQ(2.0f, deg);
}

TEST_F(basic_angle_test, divide_degrees_by_floating_point_value)
{
    degrees deg1 { 180.0f };
    degrees deg  = deg1 / 2.0f;

    EXPECT_EQ(90.0f, deg);
}

TEST_F(basic_angle_test, divide_degrees_by_integer_value)
{
    radians deg1 { pi<> };
    radians deg  = deg1 / 2;

    EXPECT_EQ(pi_over_2<>, deg);
}

TEST_F(basic_angle_test, negate)
{
    radians deg1 { pi<> };
    radians deg  = -deg1;

    EXPECT_EQ(-pi<>, deg);
}

TEST_F(basic_angle_test, size_of)
{
    EXPECT_EQ(4u,  sizeof(basic_degrees<std::uint32_t>));
    EXPECT_EQ(4u,  sizeof(basic_degrees<std::int32_t>));
    EXPECT_EQ(4u,  sizeof(basic_degrees<float>));
    EXPECT_EQ(8u,  sizeof(basic_degrees<double>));

    EXPECT_EQ(4u,  sizeof(basic_radians<std::uint32_t>));
    EXPECT_EQ(4u,  sizeof(basic_radians<std::int32_t>));
    EXPECT_EQ(4u,  sizeof(basic_radians<float>));
    EXPECT_EQ(8u,  sizeof(basic_radians<double>));

    EXPECT_EQ(4u,  sizeof(degrees));
    EXPECT_EQ(4u,  sizeof(radians));
}

TEST_F(basic_angle_test, less_than_scalar)
{
    degrees min {  5.0f };
    float   max { 10.0f };

    EXPECT_TRUE(min < max);
}

TEST_F(basic_angle_test, less_than_or_equal_than_scalar)
{
    {
        float   min {  5.0f };
        degrees max { 10.0f };

        EXPECT_TRUE(min <= max);
    }
    {
        float   min { 10.0f };
        degrees max { 10.0f };

        EXPECT_TRUE(min <= max);
    }
}

TEST_F(basic_angle_test, greater_than_scalar)
{
    float   min { 1.0f };
    degrees max { 5.0f };

    EXPECT_TRUE(max > min);
}

TEST_F(basic_angle_test, greater_than_or_equal_than_scalar)
{
    {
        float   min { 1.0f };
        degrees max { 5.0f };

        EXPECT_TRUE(max >= min);
    }
    {
        float   min { 10.0f };
        degrees max { 10.0f };

        EXPECT_TRUE(max >= min);
    }
}

TEST_F(basic_angle_test, less_than)
{
    degrees min {  5.0f };
    degrees max { 10.0f };

    EXPECT_TRUE(min < max);
}

TEST_F(basic_angle_test, less_than_or_equal)
{
    {
        degrees min {  5.0f };
        degrees max { 10.0f };

        EXPECT_TRUE(min <= max);
    }
    {
        degrees min { 10.0f };
        degrees max { 10.0f };

        EXPECT_TRUE(min <= max);
    }
}

TEST_F(basic_angle_test, greater_than)
{
    degrees min { 1.0f };
    degrees max { 5.0f };

    EXPECT_TRUE(max > min);
}

TEST_F(basic_angle_test, greater_than_or_equal)
{
    {
        degrees min { 1.0f };
        degrees max { 5.0f };

        EXPECT_TRUE(max >= min);
    }
    {
        degrees min { 10.0f };
        degrees max { 10.0f };

        EXPECT_TRUE(max >= min);
    }
}

TEST_F(basic_angle_test, degrees_literal_operator)
{
    auto deg1 = 180.5_deg;

    EXPECT_EQ(180.5f, deg1);

    auto deg2 = 45_deg;

    EXPECT_EQ(45, deg2);
}

TEST_F(basic_angle_test, radians_literal_operator)
{
    auto rad = 3.1415927400000001_rad;

    EXPECT_EQ(3.1415927400000001f, rad);
}

TEST_F(basic_angle_test, literal_conversion)
{
    {
        radians angle = 45_deg;

        EXPECT_EQ(0.7853981634f, angle);
    }
    {
        degrees angle = 0.7853981634_rad;

        EXPECT_EQ(45, angle);
    }
}

TEST_F(basic_angle_test, increment)
{
    auto angle = 45_deg;

    ++angle;

    EXPECT_EQ(46.0f, angle);

    angle++;

    EXPECT_EQ(47.0f, angle);
}

TEST_F(basic_angle_test, decrement)
{
    auto angle = 45_deg;

    --angle;

    EXPECT_EQ(44.0f, angle);

    angle--;

    EXPECT_EQ(43.0f, angle);
}
