// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_ANGLE_OPERATIONS_HPP
#define SCENER_MATH_ANGLE_OPERATIONS_HPP

#include "scener/math/basic_angle.hpp"

namespace scener::math 
{
    /// Reduces this  angle to a value between π and -π.
    /// \param angle the source angle.
    /// \returns the wrapped angle.
    template <typename T = float, typename Unit>
    constexpr basic_angle<T, Unit> wrap(const basic_angle<T, Unit>& angle) noexcept
    {
        T result = ieee_remainder(angle.value, two_pi<T>);

        if (result < -pi<T>)
        {
            result += two_pi<T>;
        }

        if (result > pi<T>)
        {
            result -= two_pi<T>;
        }

        return { result };
    }
}

#endif // SCENER_MATH_ANGLE_OPERATIONS_HPP
