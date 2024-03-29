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
    constexpr std::uint32_t packed_value(const basic_color<T>& value) noexcept
    {
        return ((static_cast<std::uint32_t>(value.r) * 255) << 24)
             + ((static_cast<std::uint32_t>(value.g) * 255) << 16)
             + ((static_cast<std::uint32_t>(value.b) * 255) << 8)
             +  (static_cast<std::uint32_t>(value.a) * 255);
    }
}

#endif  // SCENER_MATH_BASIC_COLOR_OPERATIONS_HPP

