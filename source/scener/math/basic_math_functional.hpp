// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_MATH_FUNCTIONAL_HPP
#define SCENER_MATH_BASIC_MATH_FUNCTIONAL_HPP

#include <cmath>
#include <functional>

namespace scener::math::functional
{
    template <class T, typename = std::enable_if_t<std::is_arithmetic_v<T>>> 
    struct sqrt : std::unary_function<T, T>
    {
        T operator() (const T& v) const { return std::sqrt(v); }
    };

    template <class T, typename = std::enable_if_t<std::is_arithmetic_v<T>>> 
    struct abs : std::unary_function<T, T>
    {
        T operator() (const T& v) const { return std::abs(v); }
    };

    template <class T, typename = std::enable_if_t<std::is_arithmetic_v<T>>> 
    struct min : std::binary_function<T, T, T>
    {
        T operator() (const T& v1, const T& v2) const { return std::min(v1, v2); }
    };

    template <class T, typename = std::enable_if_t<std::is_arithmetic_v<T>>> 
    struct max : std::binary_function<T, T, T>
    {
        T operator() (const T& v1, const T& v2) const { return std::max(v1, v2); }
    };
}

#endif // SCENER_MATH_BASIC_MATH_FUNCTIONAL_HPP
