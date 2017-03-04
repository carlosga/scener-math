// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_BOUNDING_FRUSTRUM_HPP
#define SCENER_MATH_BASIC_BOUNDING_FRUSTRUM_HPP

#include <cstdint>

#include "scener/math/basic_plane_operations.hpp"

namespace scener::math 
{
    // -----------------------------------------------------------------------------------------------------------------
    // TEMPLATES

    /// Defines a frustum and helps determine whether forms intersect with it.
    template <typename T, typename = typename std::enable_if_t<std::is_arithmetic_v<T>>>
    class basic_bounding_frustrum final
    {
    public:
        /// Specifies the total number of corners (8) in the BoundingFrustrum.
        constexpr static const std::uint32_t corner_count = 8;

    public:
        /// Initializes a new instance of the BoundingFrustrum class.
        /// \param value Combined matrix that usually takes view × projection matrix.
        basic_bounding_frustrum(const basic_matrix4<T>& value) noexcept
            : _bottom { T(0), T(0), T(0), T(0) }
            , _far    { T(0), T(0), T(0), T(0) }
            , _left   { T(0), T(0), T(0), T(0) }
            , _near   { T(0), T(0), T(0), T(0) }
            , _right  { T(0), T(0), T(0), T(0) }
            , _top    { T(0), T(0), T(0), T(0) }
            , _value  { value }
        {
        }

    public:
        /// Gets the bottom plane of the BoundingFrustum.
        /// \returns the bottom plane of the BoundingFrustum.
        const basic_plane<T>& bottom() const noexcept
        {
            return _bottom;
        }

        /// Gets the far plane of the BoundingFrustum.
        /// \returns the far plane of the BoundingFrustum.
        const basic_plane<T>& far() const noexcept
        {
            return _far;
        }

        /// Gets the left plane of the BoundingFrustum.
        /// \returns the left plane of the BoundingFrustum.
        const basic_plane<T>& left() const noexcept
        {
            return _left;
        }

        /// Gets the matrix4 that describes this bounding frustum.
        /// \returns the matrix4 that describes this bounding frustum.
        const matrix4& matrix() const noexcept
        {
            return _value;
        }

        /// Sets the matrix4 that describes this bounding frustum.
        /// \param matrix the matrix4 that describes this bounding frustum.
        void matrix(const basic_matrix4<T>& matrix) noexcept
        {
            _value = matrix;
            update_planes();
        }

        /// Gets the near plane of the BoundingFrustum.
        /// \returns the near plane of the BoundingFrustum.
        const basic_plane<T>& near() const noexcept
        {
            return _near;
        }

        /// Gets the right plane of the BoundingFrustum.
        /// \returns the right plane of the BoundingFrustum.
        const basic_plane<T>& right() const noexcept
        {
            return _right;
        }

        /// Gets the top plane of the BoundingFrustum.
        /// \returns the top plane of the BoundingFrustum.
        const basic_plane<T>& top() const noexcept
        {
            return _top;
        }

    public:
        constexpr bool operator==(const basic_bounding_frustrum<T>& rhs) const noexcept
        {
            return (_value == rhs._value);
        }

        constexpr bool operator!=(const basic_bounding_frustrum<T>& rhs) const noexcept
        {
            return !(*this == rhs);
        }

    private:
        void update_planes() noexcept
        {
            // http://www.chadvernon.com/blog/resources/directx9/frustum-culling/

            // Left basic_plane<T>
            _left = plane::normalize({ _value.m14 + _value.m11
                                     , _value.m24 + _value.m21
                                     , _value.m34 + _value.m31
                                     , _value.m44 + _value.m41 });

            // Right basic_plane<T>
            _right = plane::normalize({ _value.m14 - _value.m11
                                      , _value.m24 - _value.m21
                                      , _value.m34 - _value.m31
                                      , _value.m44 - _value.m41 });

            // Top basic_plane<T>
            _top = plane::normalize({ _value.m14 - _value.m12
                                    , _value.m24 - _value.m22
                                    , _value.m34 - _value.m32
                                    , _value.m44 - _value.m42 });

            // Bottom basic_plane<T>
            _bottom = plane::normalize({ _value.m14 + _value.m12
                                       , _value.m24 + _value.m22
                                       , _value.m34 + _value.m32
                                       , _value.m44 + _value.m42 });

            // Near basic_plane<T>
            _near = plane::normalize({ _value.m13, _value.m23, _value.m33, _value.m43 });


            // Far basic_plane<T>
            _far = plane::normalize({ _value.m14 - _value.m13
                                    , _value.m24 - _value.m23
                                    , _value.m34 - _value.m33
                                    , _value.m44 - _value.m43 });
        }

    private:
        basic_plane<T>   _bottom;
        basic_plane<T>   _far;
        basic_plane<T>   _left;
        basic_plane<T>   _near;
        basic_plane<T>   _right;
        basic_plane<T>   _top;
        basic_matrix4<T> _value;
    };

    // -----------------------------------------------------------------------------------------------------------------
    // TYPEDEF'S & ALIASES

    using bounding_frustrum = basic_bounding_frustrum<float>;
}

#endif // SCENER_MATH_BASIC_BOUNDING_FRUSTRUM_HPP
