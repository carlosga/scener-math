// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TESTS_BASIC_MATRIX4_TEST_HPP
#define	TESTS_BASIC_MATRIX4_TEST_HPP

#include <gtest/gtest.h>

#include <scener/math/angle.hpp>
#include <scener/math/matrix.hpp>
#include <scener/math/plane.hpp>

class basic_matrix4_test : public testing::Test
{
protected:
    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    void SetUp() override
    {
    }

    static scener::math::matrix4 generate_matrix_number_from_1_to_16();

    static scener::math::matrix4 generate_test_matrix();

    static void decompose(const scener::math::radians& yaw
                        , const scener::math::radians& pitch
                        , const scener::math::radians& roll
                        , const scener::math::vector3& expectedTranslation
                        , const scener::math::vector3& expectedScales);

    static void decompose_scale(const float& sx, const float& sy, const float& sz);

    static void create_reflection(const scener::math::plane_t& plane, const scener::math::matrix4& expected);
};

#endif // TESTS_BASIC_MATRIX4_TEST_HPP
