// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_COLOR_OPERATIONS_HPP
#define SCENER_MATH_BASIC_COLOR_OPERATIONS_HPP

#include "scener/math/basic_color.hpp"

namespace scener::math 
{
    // -----------------------------------------------------------------------------------------------------------------
    // OPERATIONS

    template <typename T>
    constexpr std::uint32_t packed_value(const basic_color<T>& color) noexcept
    {
        return ((static_cast<std::uint32_t>(color.r) * 255) << 24)
             + ((static_cast<std::uint32_t>(color.g) * 255) << 16)
             + ((static_cast<std::uint32_t>(color.b) * 255) << 8)
             +  (static_cast<std::uint32_t>(color.a) * 255);
    }
}

#endif  // SCENER_MATH_BASIC_COLOR_OPERATIONS_HPP

