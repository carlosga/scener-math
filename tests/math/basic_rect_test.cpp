// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "basic_rect_test.hpp"

#include <cstdint>

#include <scener/math/basic_rect.hpp>

using namespace scener::math;

TEST_F(basic_rect_test, default_constructor)
{
    basic_rect<std::uint32_t> rect;

    EXPECT_EQ(0u, rect.location().x);
    EXPECT_EQ(0u, rect.location().y);
    EXPECT_EQ(0u, rect.size().width);
    EXPECT_EQ(0u, rect.size().height);
}

TEST_F(basic_rect_test, construct_with_location_and_size)
{
    basic_rect<std::uint32_t> rect(0u, 0u, 1900u, 600u);

    EXPECT_EQ(   0u, rect.location().x);
    EXPECT_EQ(   0u, rect.location().y);
    EXPECT_EQ(1900u, rect.size().width);
    EXPECT_EQ( 600u, rect.size().height);
}

