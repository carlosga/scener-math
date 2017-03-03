// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_ANGLE_HPP
#define SCENER_MATH_BASIC_ANGLE_HPP

#include <type_traits>

#include "scener/math/basic_math.hpp"

namespace scener::math 
{
    // -----------------------------------------------------------------------------------------------------------------
    // UNITS

    /// degrees unit to be used with basic_angle.
    template <typename T>
    struct degrees_unit
    {
        constexpr static T pi = T(180);
    };

    /// degrees unit to be used with basic_angle.
    template <typename T>
    struct radians_unit
    {
        constexpr static T pi = scener::math::pi<T>;
    };

    // -----------------------------------------------------------------------------------------------------------------
    // TEMPLATES

    /// Represents a generic angle.
    template <typename T, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
    struct basic_angle
    {
        using value_type      = typename std::remove_reference<typename std::remove_cv<T>::type>::type;
        using reference       = typename std::add_lvalue_reference<T>::type;
        using const_reference = typename std::add_lvalue_reference<typename std::add_const<T>::type>::type;

    public:
        /// Initializes a new basic_angle instance.
        /// \param scalar the angle value.
        constexpr basic_angle(T scalar = T(0)) noexcept
            : value { scalar }
        {
        }

    public:
        template <typename K, typename Unit2>
        constexpr operator basic_angle<K, Unit2>() const noexcept
        {
            return basic_angle<K, Unit2> { value * Unit2::pi / Unit::pi };
        }

    public:
        T value;
    };

    // -----------------------------------------------------------------------------------------------------------------
    // TYPEDEF'S & ALIASES

    template <typename T>
    using basic_degrees = basic_angle<T, degrees_unit<T>>;

    template <typename T>
    using basic_radians = basic_angle<T, radians_unit<T>>;

    using degrees = basic_degrees<float>;
    using radians = basic_radians<float>;

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS

    /// Equality operator for comparing basic_angle instances.
    template <typename T, typename Unit>
    constexpr bool operator==(const basic_angle<T, Unit>& lhs
                            , const typename std::common_type<basic_angle<T, Unit>>::type& rhs) noexcept

    {
        return equal(lhs.value, rhs.value);
    }

    /// Inequality operator for comparing basic_angle instances.
    template <typename T, typename Unit>
    constexpr bool operator!=(const basic_angle<T, Unit>& lhs
                            , const typename std::common_type<basic_angle<T, Unit>>::type& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <typename T, typename Unit>
    constexpr bool operator<(const basic_angle<T, Unit>& lhs, const basic_angle<T, Unit>& rhs) noexcept
    {
        return (lhs.value < rhs.value);
    }

    template <typename T, typename Unit>
    constexpr bool operator<=(const basic_angle<T, Unit>& lhs, const basic_angle<T, Unit>& rhs) noexcept
    {
        return (lhs.value <= rhs.value);
    }

    template <typename T, typename Unit>
    constexpr bool operator>(const basic_angle<T, Unit>& lhs, const basic_angle<T, Unit>& rhs) noexcept
    {
        return (lhs.value > rhs.value);
    }

    template <typename T, typename Unit>
    constexpr bool operator>=(const basic_angle<T, Unit>& lhs, const basic_angle<T, Unit>& rhs) noexcept
    {
        return (lhs.value >= rhs.value);
    }

    template <typename T, typename Unit>
    constexpr basic_angle<T, Unit>& operator++(basic_angle<T, Unit>& angle) noexcept
    {
        ++angle.value;
        return angle;
    }

    template <typename T, typename Unit>
    constexpr basic_angle<T, Unit>& operator--(basic_angle<T, Unit>& angle) noexcept
    {
        --angle.value;
        return angle;
    }

    template <typename T, typename Unit>
    constexpr basic_angle<T, Unit> operator++(basic_angle<T, Unit>& angle, int) noexcept
    {
        angle.value++;
        return angle;
    }

    template <typename T, typename Unit>
    constexpr basic_angle<T, Unit> operator--(basic_angle<T, Unit>& angle, int) noexcept
    {
        --angle.value;
        return angle;
    }

    template <typename T, typename Unit>
    constexpr basic_angle<T, Unit>& operator*=(basic_angle<T, Unit>& lhs
                                             , const typename std::common_type<basic_angle<T, Unit>>::type& rhs) noexcept
    {
        lhs.value *= rhs.value;

        return lhs;
    }

    template <typename T, typename Unit>
    constexpr basic_angle<T, Unit> operator*(const basic_angle<T, Unit>& lhs
                                           , const typename std::common_type<basic_angle<T, Unit>>::type& rhs) noexcept
    {
        auto result = lhs;

        result *= rhs;

        return result;
    }

    template <typename T, typename K, typename Unit>
    constexpr basic_angle<typename std::common_type<T, K>::type, Unit>&
        operator/=(basic_angle<T, Unit>& lhs, const basic_angle<K, Unit>& rhs) noexcept
    {
        lhs.value /= static_cast<T>(rhs.value);

        return lhs;
    }

    template <typename T, typename K, typename Unit>
    constexpr basic_angle<typename std::common_type<T, K>::type, Unit>
        operator/(const basic_angle<T, Unit>& lhs, const basic_angle<K, Unit>& rhs) noexcept
    {
        typedef typename std::common_type<T, K>::type common_t;

        basic_angle<common_t, Unit> result = lhs;

        result /= rhs;

        return result;
    }

    template <typename T, typename Unit>
    constexpr basic_angle<T, Unit>& operator-=(basic_angle<T, Unit>& lhs
                                             , const typename std::common_type<basic_angle<T, Unit>>::type& rhs) noexcept
    {
        lhs.value -= rhs.value;

        return lhs;
    }

    template <typename T, typename Unit>
    constexpr basic_angle<T, Unit> operator-(const basic_angle<T, Unit>& lhs
                                           , const typename std::common_type<basic_angle<T, Unit>>::type& rhs) noexcept
    {
        auto result = lhs;

        result -= rhs;

        return result;
    }

    template <typename T, typename Unit>
    constexpr basic_angle<T, Unit>& operator+=(basic_angle<T, Unit>& lhs
                                             , const typename std::common_type<basic_angle<T, Unit>>::type& rhs) noexcept
    {
        lhs.value += rhs.value;

        return lhs;
    }

    template <typename T, typename Unit>
    constexpr basic_angle<T, Unit> operator+(const basic_angle<T, Unit>& lhs
                                           , const typename std::common_type<basic_angle<T, Unit>>::type& rhs) noexcept
    {
        auto result = lhs;

        result += rhs;

        return result;
    }

    template <typename T, typename Unit>
    constexpr basic_angle<T, Unit> operator-(const basic_angle<T, Unit>& angle) noexcept
    {
        return basic_angle<T, Unit> { -angle.value };
    }

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS (WITH SCALARS)

    /// Equality operator for comparing basic_angle instances against scalar values.
    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr bool operator==(const basic_angle<T, Unit>& lhs, const S& rhs) noexcept
    {
        return equal(lhs.value, rhs);
    }

    /// Inequality operator for comparing basic_angle instances against scalar values.
    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr bool operator!=(const basic_angle<T, Unit>& lhs, const S& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    /// Equality operator for comparing scalar values against basic_angle instances.
    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr bool operator==(const S& lhs, const basic_angle<T, Unit>& rhs) noexcept
    {
        return equal(lhs, rhs.value);
    }

    /// Inequality operator for comparing scalar values against basic_angle instances.
    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr bool operator!=(const S& lhs, const basic_angle<T, Unit>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr bool operator<(const basic_angle<T, Unit>& lhs, const S& rhs) noexcept
    {
        return (lhs.value < rhs);
    }

    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr bool operator<=(const basic_angle<T, Unit>& lhs, const S& rhs) noexcept
    {
        return (lhs.value <= rhs);
    }

    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr bool operator>(const basic_angle<T, Unit>& lhs, const S& rhs) noexcept
    {
        return (lhs.value > rhs);
    }

    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr bool operator>=(const basic_angle<T, Unit>& lhs, const S& rhs) noexcept
    {
        return (lhs.value >= rhs);
    }

    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr bool operator<(const S& lhs, const basic_angle<T, Unit>& rhs) noexcept
    {
        return (lhs < rhs.value);
    }

    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr bool operator<=(const S& lhs, const basic_angle<T, Unit>& rhs) noexcept
    {
        return (lhs <= rhs.value);
    }

    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr bool operator>(const S& lhs, const basic_angle<T, Unit>& rhs) noexcept
    {
        return (lhs > rhs.value);
    }

    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr bool operator>=(const S& lhs, const basic_angle<T, Unit>& rhs) noexcept
    {
        return (lhs >= rhs.value);
    }

    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr basic_angle<T, Unit>& operator*=(basic_angle<T, Unit>& lhs, const S& rhs) noexcept
    {
        lhs.value *= rhs;

        return lhs;
    }

    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr basic_angle<T, Unit> operator*(const basic_angle<T, Unit>& lhs, const S& rhs) noexcept
    {
        auto result = lhs;

        result *= rhs;

        return result;
    }

    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr basic_angle<T, Unit>& operator/=(basic_angle<T, Unit>& lhs, const S& rhs) noexcept
    {
        lhs.value /= rhs;

        return lhs;
    }

    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr basic_angle<T, Unit> operator/(const basic_angle<T, Unit>& lhs, const S& rhs) noexcept
    {
        auto result = lhs;

        result /= rhs;

        return result;
    }

    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr basic_angle<T, Unit>& operator-=(basic_angle<T, Unit>& lhs, const S& rhs) noexcept
    {
        lhs.value -= rhs;

        return lhs;
    }

    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr basic_angle<T, Unit> operator-(const basic_angle<T, Unit>& lhs, const S& rhs) noexcept
    {
        auto result = lhs;

        result -= rhs;

        return result;
    }

    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr basic_angle<T, Unit>& operator+=(basic_angle<T, Unit>& lhs, const S& rhs) noexcept
    {
        lhs.value += rhs;

        return lhs;
    }

    template <typename T, typename S, typename Unit, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr basic_angle<T, Unit> operator+(const basic_angle<T, Unit>& lhs, const S& rhs) noexcept
    {
        auto result = lhs;

        result += rhs;

        return result;
    }

    constexpr degrees operator"" _deg(unsigned long long value) noexcept
    {
        return degrees(value);
    }

    constexpr degrees operator"" _deg(long double value) noexcept
    {
        return degrees(static_cast<degrees::value_type>(value));
    }

    constexpr radians operator"" _rad(long double value) noexcept
    {
        return radians(static_cast<degrees::value_type>(value));
    }
}

#endif // SCENER_MATH_BASIC_ANGLE_HPP
