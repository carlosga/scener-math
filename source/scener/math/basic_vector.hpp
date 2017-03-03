// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_BASIC_VECTOR_HPP
#define SCENER_MATH_BASIC_VECTOR_HPP

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>

#include "scener/math/basic_math.hpp"

namespace scener::math
{
    // -----------------------------------------------------------------------------------------------------------------
    // TRAITS

    template <typename T, std::size_t Dimension>
    struct basic_vector_traits
    {
        using reference              = typename std::add_lvalue_reference<T>::type;
        using const_reference        = typename std::add_lvalue_reference<typename std::add_const<T>::type>::type;
        using value_type             = typename std::remove_reference<typename std::remove_cv<T>::type>::type;
        using pointer                = typename std::add_pointer<T>::type;
        using const_pointer          = typename std::add_pointer<typename std::add_const<T>::type>::type;
        using iterator               = typename std::array<T, Dimension>::iterator;
        using const_iterator         = typename std::array<T, Dimension>::const_iterator;
        using reverse_iterator       = typename std::array<T, Dimension>::reverse_iterator;
        using const_reverse_iterator = typename std::array<T, Dimension>::const_reverse_iterator;
        using size_type              = std::size_t;
    };

    // -----------------------------------------------------------------------------------------------------------------
    // TEMPLATES

    /// Represents a generic vector.
    template <typename T, std::size_t Dimension, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
    struct basic_vector
    {
        using traits_type            = basic_vector_traits<T, Dimension>;
        using reference              = typename traits_type::reference;
        using const_reference        = typename traits_type::const_reference;
        using value_type             = typename traits_type::value_type;
        using pointer                = typename traits_type::pointer;
        using const_pointer          = typename traits_type::const_pointer;
        using iterator               = typename traits_type::iterator;
        using const_iterator         = typename traits_type::const_iterator;
        using reverse_iterator       = typename traits_type::reverse_iterator;
        using const_reverse_iterator = typename traits_type::const_reverse_iterator;
        using size_type              = typename traits_type::size_type;

    public:
        /// Returns a pointer to the underlying array serving as element storage
        /// \returns a pointer to the underlying array serving as element storage
        constexpr pointer data() noexcept
        {
            return items.data();
        }

        /// Returns a const pointer to the underlying array serving as element storage
        /// \returns a const pointer to the underlying array serving as element storage
        constexpr const_pointer data() const noexcept
        {
            return items.data();
        }

        /// Returns an iterator to the first element of the vector.
        /// \returns an iterator to the first element of the vector.
        constexpr iterator begin() noexcept
        {
            return items.begin();
        }

        /// Returns a const iterator to the first element of the vector.
        /// \returns a const iterator to the first element of the vector.
        constexpr const_iterator begin() const noexcept
        {
            return items.begin();
        }

        /// Returns an iterator to the element following the last element of the vector.
        /// \returns an iterator to the element following the last element of the vector.
        constexpr iterator end() noexcept
        {
            return items.end();
        }

        /// Returns a const iterator to the element following the last element of the vector.
        /// \returns a const iterator to the element following the last element of the vector.
        constexpr const_iterator end() const noexcept
        {
            return items.end();
        }

        /// Returns a reverse iterator to the first element of the reversed vector.
        /// \returns a reverse iterator to the first element of the reversed vector.
        constexpr reverse_iterator rbegin() noexcept
        {
            return items.rbegin();
        }

        /// Returns a const reverse iterator to the first element of the reversed vector.
        /// \returns a const reverse iterator to the first element of the reversed vector.
        constexpr const_reverse_iterator rbegin() const noexcept
        {
            return items.rbegin();
        }

        /// Returns a reverse iterator to the element following the last element of the reversed vector.
        /// \returns a reverse iterator to the element following the last element of the reversed vector.
        constexpr reverse_iterator rend() noexcept
        {
            return items.rend();
        }

        /// Returns a const reverse iterator to the element following the last element of the reversed vector.
        /// \returns a const reverse iterator to the element following the last element of the reversed vector.
        constexpr const_reverse_iterator rend() const noexcept
        {
            return items.rend();
        }

        /// Returns a reference to the first element in the vector.
        /// \returns a reference to the first element in the vector.
        constexpr reference front() noexcept
        {
            return items.front();
        }

        /// Returns a const reference to the first element in the vector.
        /// \returns a const reference to the first element in the vector.
        constexpr const_reference front() const noexcept
        {
            return items.front();
        }

        /// Returns reference to the last element in the vector.
        /// \returns reference to the last element in the vector.
        constexpr reference back() noexcept
        {
            return items.back();
        }

        /// Returns const reference to the last element in the vector.
        /// \returns const reference to the last element in the vector.
        constexpr const_reference back() const noexcept
        {
            return items.back();
        }

    public:
        /// Provides a reference to the component value with a specified index in a vector.
        /// \param index the index of the position of the element to be referenced.
        constexpr reference operator[](size_type index) noexcept
        {
            return items[index];
        }

        /// Provides a const reference to the component value with a specified index in a vector.
        /// \param index the index of the basic_vector component to be returned.
        constexpr const_reference operator[](size_type index) const noexcept
        {
            return items[index];
        }

    public:
        std::array<T, Dimension> items;
    };

    // ---------------------------------------------------------------------------------------------------------------------
    // VECTOR2 SPECIALIZATION

    /// Represents an x and y-coordinate vector.
    template <typename T>
    struct basic_vector<T, 2>
    {
        using traits_type            = basic_vector_traits<T, 2>;
        using reference              = typename traits_type::reference;
        using const_reference        = typename traits_type::const_reference;
        using value_type             = typename traits_type::value_type;
        using pointer                = typename traits_type::pointer;
        using const_pointer          = typename traits_type::const_pointer;
        using iterator               = typename traits_type::iterator;
        using const_iterator         = typename traits_type::const_iterator;
        using reverse_iterator       = typename traits_type::reverse_iterator;
        using const_reverse_iterator = typename traits_type::const_reverse_iterator;
        using size_type              = typename traits_type::size_type;

    public:
        /// Returns a basic_vector with ones in all of its components.
        constexpr static basic_vector<T, 2> one() noexcept { return basic_vector<T, 2> { 1 }; }

        /// Returns the x unit basic_vector (1, 0).
        constexpr static basic_vector<T, 2> unit_x() noexcept { return { 1, 0 }; }

        /// Returns the y unit basic_vector (0, 1).
        constexpr static basic_vector<T, 2> unit_y() noexcept { return { 0, 1 }; }

        /// Returns a basic_vector with all of its components set to zero.
        constexpr static basic_vector<T, 2> zero() noexcept { return basic_vector<T, 2> { 0 }; }

    public:
        /// Initializes a new instance of the basic_vector struct.
        constexpr basic_vector() noexcept
            : basic_vector { 0, 0 }
        {
        }

        /// Initializes a new instance of the basic_vector class with the given value.
        /// \param scalar value value for the x and y components of the vector.
        constexpr explicit basic_vector(T scalar) noexcept
            : basic_vector { scalar, scalar }
        {
        }

        /// Initializes a new instance of the basic_vector class with the given texture coordinates.
        /// \param x the x-coordinate value.
        /// \param y the y-coordinate value.
        constexpr basic_vector(T x, T y) noexcept
            : x { x }, y { y }
        {
        }

    public:
        /// Returns a pointer to the underlying array serving as element storage
        /// \returns a pointer to the underlying array serving as element storage
        constexpr pointer data() noexcept
        {
            return items.data();
        }

        /// Returns a const pointer to the underlying array serving as element storage
        /// \returns a const pointer to the underlying array serving as element storage
        constexpr const_pointer data() const noexcept
        {
            return items.data();
        }

        /// Returns an iterator to the first element of the vector.
        /// \returns an iterator to the first element of the vector.
        constexpr iterator begin() noexcept
        {
            return items.begin();
        }

        /// Returns a const iterator to the first element of the vector.
        /// \returns a const iterator to the first element of the vector.
        constexpr const_iterator begin() const noexcept
        {
            return items.begin();
        }

        /// Returns an iterator to the element following the last element of the vector.
        /// \returns an iterator to the element following the last element of the vector.
        constexpr iterator end() noexcept
        {
            return items.end();
        }

        /// Returns a const iterator to the element following the last element of the vector.
        /// \returns a const iterator to the element following the last element of the vector.
        constexpr const_iterator end() const noexcept
        {
            return items.end();
        }

        /// Returns a reverse iterator to the first element of the reversed vector.
        /// \returns a reverse iterator to the first element of the reversed vector.
        constexpr reverse_iterator rbegin() noexcept
        {
            return items.rbegin();
        }

        /// Returns a const reverse iterator to the first element of the reversed vector.
        /// \returns a const reverse iterator to the first element of the reversed vector.
        constexpr const_reverse_iterator rbegin() const noexcept
        {
            return items.rbegin();
        }

        /// Returns a reverse iterator to the element following the last element of the reversed vector.
        /// \returns a reverse iterator to the element following the last element of the reversed vector.
        constexpr reverse_iterator rend() noexcept
        {
            return items.rend();
        }

        /// Returns a const reverse iterator to the element following the last element of the reversed vector.
        /// \returns a const reverse iterator to the element following the last element of the reversed vector.
        constexpr const_reverse_iterator rend() const noexcept
        {
            return items.rend();
        }

        /// Returns a reference to the first element in the vector.
        /// \returns a reference to the first element in the vector.
        constexpr reference front() noexcept
        {
            return items.front();
        }

        /// Returns a const reference to the first element in the vector.
        /// \returns a const reference to the first element in the vector.
        constexpr const_reference front() const noexcept
        {
            return items.front();
        }

        /// Returns reference to the last element in the vector.
        /// \returns reference to the last element in the vector.
        constexpr reference back() noexcept
        {
            return items.back();
        }

        /// Returns const reference to the last element in the vector.
        /// \returns const reference to the last element in the vector.
        constexpr const_reference back() const noexcept
        {
            return items.back();
        }

    public:
        /// Provides a reference to the component value with a specified index in a vector.
        /// \param index the index of the position of the element to be referenced.
        constexpr reference operator[](size_type index) noexcept
        {
            return items[index];
        }

        /// Provides a const reference to the component value with a specified index in a vector.
        /// \param index the index of the basic_vector component to be returned.
        constexpr const_reference operator[](size_type index) const noexcept
        {
            return items[index];
        }

    public:
        union
        {
            std::array<T, 2> items;
            struct
            {
                T x;
                T y;
            };
        };
    };

    // ---------------------------------------------------------------------------------------------------------------------
    // VECTOR3 SPECIALIZATION

    /// Represents an x-, y-, and z-coordinate vector.
    template <typename T>
    struct basic_vector<T, 3>
    {
        using traits_type            = basic_vector_traits<T, 3>;
        using reference              = typename traits_type::reference;
        using const_reference        = typename traits_type::const_reference;
        using value_type             = typename traits_type::value_type;
        using pointer                = typename traits_type::pointer;
        using const_pointer          = typename traits_type::const_pointer;
        using iterator               = typename traits_type::iterator;
        using const_iterator         = typename traits_type::const_iterator;
        using reverse_iterator       = typename traits_type::reverse_iterator;
        using const_reverse_iterator = typename traits_type::const_reverse_iterator;
        using size_type              = typename traits_type::size_type;

    public:
        /// Returns a unit Vector3 designating backward in a rhs-handed coordinate system (0, 0, 1).
        constexpr static basic_vector<T, 3> backward() noexcept { return { 0, 0, 1 }; }

        /// Returns a unit Vector3 designating down (0, −1, 0).
        constexpr static basic_vector<T, 3> down() noexcept { return { 0, -1, 0 }; }

        /// Returns a unit Vector3 designating forward in a rhs-handed coordinate system (0, 0, −1).
        constexpr static basic_vector<T, 3> forward() noexcept { return { 0, 0, -1 }; }

        /// Returns a unit Vector3 designating lhs (−1, 0, 0).
        constexpr static basic_vector<T, 3> lhs() noexcept { return { -1, 0, 0 }; }

        /// Returns a Vector3 with ones in all of its components.
        constexpr static basic_vector<T, 3> one() noexcept { return basic_vector<T, 3> { 1 }; }

        /// Returns a unit Vector3 pointing to the rhs (1, 0, 0).
        constexpr static basic_vector<T, 3> rhs() noexcept { return { 1, 0, 0 }; }

        /// Returns the x unit Vector3 (1, 0, 0).
        constexpr static basic_vector<T, 3> unit_x() noexcept { return { 1, 0, 0 }; }

        /// Returns the y unit Vector3 (0, 1, 0).
        constexpr static basic_vector<T, 3> unit_y() noexcept { return { 0, 1, 0 }; }

        /// Returns the z unit Vector3 (0, 0, 1).
        constexpr static basic_vector<T, 3> unit_z() noexcept { return { 0, 0, 1 }; }

        /// Returns a unit vector designating up (0, 1, 0).
        constexpr static basic_vector<T, 3> up() noexcept { return { 0, 1, 0 }; }

        /// Returns a Vector3 with all of its components set to zero.
        constexpr static basic_vector<T, 3> zero() noexcept { return basic_vector<T, 3> { 0 }; }

    public:
        /// Initializes a new instance of the basic_vector struct.
        constexpr basic_vector() noexcept
            : basic_vector { 0, 0, 0 }
        {
        }

        /// Initializes a new instance of the basic_vector class.
        /// \param scalar the value for the x, y and z components of the vector.
        constexpr explicit basic_vector(T scalar) noexcept
            : basic_vector { scalar, scalar, scalar }
        {
        }

        /// Initializes a new instance of the basic_vector class.
        /// \param vector a vector containing the values to initialize x and y components with.
        /// \param scalar for the z-component of the vector.
        constexpr basic_vector(const basic_vector<T, 2>& vector, T scalar) noexcept
            : basic_vector { vector.x, vector.y, scalar }
        {
        }

        /// Initializes a new instance of the basic_vector class.
        /// \param z The Z value of the new vector structure.
        /// \param x The X value of the new vector structure.
        /// \param y The Y value of the new vector structure.
        constexpr basic_vector(T x, T y, T z) noexcept
            : x { x }, y { y }, z { z }
        {
        }

    public:
        /// Returns a pointer to the underlying array serving as element storage
        /// \returns a pointer to the underlying array serving as element storage
        constexpr pointer data() noexcept
        {
            return items.data();
        }

        /// Returns a const pointer to the underlying array serving as element storage
        /// \returns a const pointer to the underlying array serving as element storage
        constexpr const_pointer data() const noexcept
        {
            return items.data();
        }

        /// Returns an iterator to the first element of the vector.
        /// \returns an iterator to the first element of the vector.
        constexpr iterator begin() noexcept
        {
            return items.begin();
        }

        /// Returns a const iterator to the first element of the vector.
        /// \returns a const iterator to the first element of the vector.
        constexpr const_iterator begin() const noexcept
        {
            return items.begin();
        }

        /// Returns an iterator to the element following the last element of the vector.
        /// \returns an iterator to the element following the last element of the vector.
        constexpr iterator end() noexcept
        {
            return items.end();
        }

        /// Returns a const iterator to the element following the last element of the vector.
        /// \returns a const iterator to the element following the last element of the vector.
        constexpr const_iterator end() const noexcept
        {
            return items.end();
        }

        /// Returns a reverse iterator to the first element of the reversed vector.
        /// \returns a reverse iterator to the first element of the reversed vector.
        constexpr reverse_iterator rbegin() noexcept
        {
            return items.rbegin();
        }

        /// Returns a const reverse iterator to the first element of the reversed vector.
        /// \returns a const reverse iterator to the first element of the reversed vector.
        constexpr const_reverse_iterator rbegin() const noexcept
        {
            return items.rbegin();
        }

        /// Returns a reverse iterator to the element following the last element of the reversed vector.
        /// \returns a reverse iterator to the element following the last element of the reversed vector.
        constexpr reverse_iterator rend() noexcept
        {
            return items.rend();
        }

        /// Returns a const reverse iterator to the element following the last element of the reversed vector.
        /// \returns a const reverse iterator to the element following the last element of the reversed vector.
        constexpr const_reverse_iterator rend() const noexcept
        {
            return items.rend();
        }

        /// Returns a reference to the first element in the vector.
        /// \returns a reference to the first element in the vector.
        constexpr reference front() noexcept
        {
            return items.front();
        }

        /// Returns a const reference to the first element in the vector.
        /// \returns a const reference to the first element in the vector.
        constexpr const_reference front() const noexcept
        {
            return items.front();
        }

        /// Returns reference to the last element in the vector.
        /// \returns reference to the last element in the vector.
        constexpr reference back() noexcept
        {
            return items.back();
        }

        /// Returns const reference to the last element in the vector.
        /// \returns const reference to the last element in the vector.
        constexpr const_reference back() const noexcept
        {
            return items.back();
        }

    public:
        /// Provides a reference to the component value with a specified index in a vector.
        /// \param index the index of the position of the element to be referenced.
        constexpr reference operator[](size_type index) noexcept
        {
            return items[index];
        }

        /// Provides a const reference to the component value with a specified index in a vector.
        /// \param index the index of the basic_vector component to be returned.
        constexpr const_reference operator[](size_type index) const noexcept
        {
            return items[index];
        }

        template <typename K>
        explicit constexpr operator basic_vector<K, 2>() const noexcept
        {
            return { K(x), K(y) };
        }

        template <typename K>
        explicit constexpr operator basic_vector<K, 4>() const noexcept
        {
            return { K(x), K(y), K(z), K(1) };
        }

    public:
        union
        {
            std::array<T, 3> items;
            struct
            {
                T x;
                T y;
                T z;
            };
        };
    };

    // ---------------------------------------------------------------------------------------------------------------------
    // VECTOR4 SPECIALIZATION

    /// Represents an x-, y-, z- and w-coordinate vector.
    template <typename T>
    struct basic_vector<T, 4>
    {
        using traits_type            = basic_vector_traits<T, 4>;
        using reference              = typename traits_type::reference;
        using const_reference        = typename traits_type::const_reference;
        using value_type             = typename traits_type::value_type;
        using pointer                = typename traits_type::pointer;
        using const_pointer          = typename traits_type::const_pointer;
        using iterator               = typename traits_type::iterator;
        using const_iterator         = typename traits_type::const_iterator;
        using reverse_iterator       = typename traits_type::reverse_iterator;
        using const_reverse_iterator = typename traits_type::const_reverse_iterator;
        using size_type              = typename traits_type::size_type;

    public:
        /// Returns a basic_vector<T, 4> with ones in all of its components.
        constexpr static basic_vector<T, 4> one() noexcept { return basic_vector<T, 4> { 1 }; }

        /// Returns the x unit basic_vector<T, 4> (1, 0, 0, 0).
        constexpr static basic_vector<T, 4> unit_x() noexcept { return { 1, 0, 0, 0 }; }

        /// Returns the y unit basic_vector<T, 4> (0, 1, 0, 0).
        constexpr static basic_vector<T, 4> unit_y() noexcept { return { 0, 1, 0, 0 }; }

        /// Returns the z unit basic_vector<T, 4> (0, 0, 1, 0).
        constexpr static basic_vector<T, 4> unit_z() noexcept { return { 0, 0, 1, 0 }; }

        /// Returns the w unit basic_vector<T, 4> (0, 0, 0, 1).
        constexpr static basic_vector<T, 4> unit_w() noexcept { return { 0, 0, 0, 1 }; }

        /// Returns a basic_vector<T, 4> with all of its components set to zero.
        constexpr static basic_vector<T, 4> zero() noexcept { return basic_vector<T, 4> { 0 }; }

    public:
        /// Initializes a new instance of the basic_vector struct.
        constexpr basic_vector() noexcept
            : basic_vector { 0, 0, 0, 0 }
        {
        }

        /// Initializes a new instance of the basic_vector struct.
        /// \param scalar the value for the x, y, z and w components of the vector.
        constexpr explicit basic_vector(T scalar) noexcept
            : basic_vector { scalar, scalar, scalar, scalar }
        {
        }

        /// Initializes a new instance of the Vector4 class.
        /// \param vector a vector containing the values to initialize x and y components with.
        /// \param z value for the z-component of the vector.
        /// \param w value for the w-component of the vector.
        constexpr basic_vector(const basic_vector<T, 2>& vector, T z, T w) noexcept
            : basic_vector { vector.x, vector.y, z, w }
        {
        }

        /// Initializes a new instance of the Vector4 class.
        /// \param vector a vector containing the values to initialize x, y, and z components with.
        /// \param w value for the w-component of the vector.
        constexpr basic_vector(const basic_vector<T, 3>& vector, T w) noexcept
            : basic_vector { vector.x, vector.y, vector.z, w }
        {
        }

        /// Initializes a new instance of the Vector4 class.
        /// \param x The X value of the new Vector4 structure.
        /// \param y The Y value of the new Vector4 structure.
        /// \param z The Z value of the new Vector4 structure.
        /// \param w The W value of the new Vector4 structure.
        constexpr basic_vector(T x, T y, T z, T w) noexcept
            : x { x }, y { y }, z { z }, w { w }
        {
        }

    public:
        /// Returns a pointer to the underlying array serving as element storage.
        /// \returns a pointer to the underlying array serving as element storage.
        constexpr pointer data() noexcept
        {
            return items.data();
        }

        /// Returns a const pointer to the underlying array serving as element storage.
        /// \returns a const pointer to the underlying array serving as element storage.
        constexpr const_pointer data() const noexcept
        {
            return items.data();
        }

        /// Returns an iterator to the first element of the vector.
        /// \returns an iterator to the first element of the vector.
        constexpr iterator begin() noexcept
        {
            return items.begin();
        }

        /// Returns a const iterator to the first element of the vector.
        /// \returns a const iterator to the first element of the vector.
        constexpr const_iterator begin() const noexcept
        {
            return items.begin();
        }

        /// Returns an iterator to the element following the last element of the vector.
        /// \returns an iterator to the element following the last element of the vector.
        constexpr iterator end() noexcept
        {
            return items.end();
        }

        /// Returns a const iterator to the element following the last element of the vector.
        /// \returns a const iterator to the element following the last element of the vector.
        constexpr const_iterator end() const noexcept
        {
            return items.end();
        }

        /// Returns a reverse iterator to the first element of the reversed vector.
        /// \returns a reverse iterator to the first element of the reversed vector.
        constexpr reverse_iterator rbegin() noexcept
        {
            return items.rbegin();
        }

        /// Returns a const reverse iterator to the first element of the reversed vector.
        /// \returns a const reverse iterator to the first element of the reversed vector.
        constexpr const_reverse_iterator rbegin() const noexcept
        {
            return items.rbegin();
        }

        /// Returns a reverse iterator to the element following the last element of the reversed vector.
        /// \returns a reverse iterator to the element following the last element of the reversed vector.
        constexpr reverse_iterator rend() noexcept
        {
            return items.rend();
        }

        /// Returns a const reverse iterator to the element following the last element of the reversed vector.
        /// \returns a const reverse iterator to the element following the last element of the reversed vector.
        constexpr const_reverse_iterator rend() const noexcept
        {
            return items.rend();
        }

        /// Returns a reference to the first element in the vector.
        /// \returns a reference to the first element in the vector.
        constexpr reference front() noexcept
        {
            return items.front();
        }

        /// Returns a const reference to the first element in the vector.
        /// \returns a const reference to the first element in the vector.
        constexpr const_reference front() const noexcept
        {
            return items.front();
        }

        /// Returns reference to the last element in the vector.
        /// \returns reference to the last element in the vector.
        constexpr reference back() noexcept
        {
            return items.back();
        }

        /// Returns const reference to the last element in the vector.
        /// \returns const reference to the last element in the vector.
        constexpr const_reference back() const noexcept
        {
            return items.back();
        }

    public:
        /// Provides a reference to the component value with a specified index in a vector.
        /// \param index the index of the position of the element to be referenced.
        constexpr T& operator[](std::size_t index) noexcept
        {
            return items[index];
        }

        /// Provides a const reference to the component value with a specified index in a vector.
        /// \param index the index of the basic_vector component to be returned.
        constexpr const T& operator[](std::size_t index) const noexcept
        {
            return items[index];
        }

        template <typename K>
        explicit constexpr operator basic_vector<K, 2>() const noexcept
        {
            return { K(x), K(y) };
        }

        template <typename K>
        explicit constexpr operator basic_vector<K, 3>() const
        {
            return { K(x), K(y), K(z) };
        }

    public:
        union
        {
            std::array<T, 4> items;
            struct
            {
                T x;
                T y;
                T z;
                T w;
            };
        };
    };

    // -----------------------------------------------------------------------------------------------------------------
    // TYPEDEF'S & ALIASES

    template <typename T>
    using basic_vector2 = basic_vector<T, 2>;

    template <typename T>
    using basic_vector3 = basic_vector<T, 3>;

    template <typename T>
    using basic_vector4 = basic_vector<T, 4>;

    using vector2u = basic_vector2<std::uint32_t>;
    using vector2i = basic_vector2<std::int32_t>;
    using vector2d = basic_vector2<double>;
    using vector2  = basic_vector2<float>;

    using vector3u = basic_vector3<std::uint32_t>;
    using vector3i = basic_vector3<std::int32_t>;
    using vector3d = basic_vector3<double>;
    using vector3  = basic_vector3<float>;

    using vector4u = basic_vector4<std::uint32_t>;
    using vector4i = basic_vector4<std::int32_t>;
    using vector4d = basic_vector4<double>;
    using vector4  = basic_vector4<float>;

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS

    /// Equality operator for comparing basic_vector instances.
    template <typename T, std::size_t Dimension>
    constexpr bool operator==(const basic_vector<T, Dimension>& lhs, const basic_vector<T, Dimension>& rhs) noexcept
    {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), [](T a, T b) { return equal(a, b); });
    }

    /// Inequality operator for comparing basic_vector instances.
    template <typename T, std::size_t Dimension>
    constexpr bool operator!=(const basic_vector<T, Dimension>& lhs, const basic_vector<T, Dimension>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    /// Multiplication assignment operator for multipliying basic_vector instances.
    template <typename T = float, std::size_t Dimension>
    constexpr basic_vector<T, Dimension>& operator*=(basic_vector<T, Dimension>&       lhs
                                                   , const basic_vector<T, Dimension>& rhs) noexcept
    {
        std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::multiplies<T>());

        return lhs;
    }

    /// Multiplication operator for multipliying basic_vector instances.
    template <typename T, std::size_t Dimension>
    constexpr basic_vector<T, Dimension> operator*(const basic_vector<T, Dimension>& lhs
                                                 , const basic_vector<T, Dimension>& rhs) noexcept
    {
        auto result = lhs;

        result *= rhs;

        return result;
    }

    template <typename T, std::size_t Dimension>
    constexpr basic_vector<T, Dimension>& operator/=(basic_vector<T, Dimension>&       lhs
                                                   , const basic_vector<T, Dimension>& rhs) noexcept
    {
        std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::divides<T>());

        return lhs;
    }

    template <typename T, std::size_t Dimension>
    constexpr basic_vector<T, Dimension> operator/(const basic_vector<T, Dimension>& lhs
                                                 , const basic_vector<T, Dimension>& rhs) noexcept
    {
        auto vector = lhs;

        vector /= rhs;

        return vector;
    }

    template <typename T, std::size_t Dimension>
    constexpr basic_vector<T, Dimension>& operator-=(basic_vector<T, Dimension>&       lhs
                                                   , const basic_vector<T, Dimension>& rhs) noexcept
    {
        std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::minus<T>());

        return lhs;
    }

    template <typename T, std::size_t Dimension>
    constexpr basic_vector<T, Dimension> operator-(const basic_vector<T, Dimension>& lhs
                                                 , const basic_vector<T, Dimension>& rhs) noexcept
    {
        auto result = lhs;

        result -= rhs;

        return result;
    }

    template <typename T, std::size_t Dimension>
    constexpr basic_vector<T, Dimension>& operator+=(basic_vector<T, Dimension>&       lhs
                                                   , const basic_vector<T, Dimension>& rhs) noexcept
    {
        std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::plus<T>());

        return lhs;
    }

    template <typename T, std::size_t Dimension>
    constexpr basic_vector<T, Dimension> operator+(const basic_vector<T, Dimension>& lhs
                                                 , const basic_vector<T, Dimension>& rhs) noexcept
    {
        auto result = lhs;

        result += rhs;

        return result;
    }

    template <typename T, std::size_t Dimension>
    constexpr basic_vector<T, Dimension> operator-(const basic_vector<T, Dimension>& value) noexcept
    {
        basic_vector<T, Dimension> vector;

        std::transform(value.begin(), value.end(), vector.begin(), std::negate<T>());

        return vector;
    }

    // -----------------------------------------------------------------------------------------------------------------
    // OPERATORS (WITH SCALARS)

    /// Multiplication assignment operator for multipliying basic_vector instances against an scalar value.
    template <typename T, typename S, std::size_t Dimension, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr basic_vector<T, Dimension>& operator*=(basic_vector<T, Dimension>& lhs, const S& rhs) noexcept
    {
        std::transform(lhs.begin(), lhs.end(), lhs.begin(), std::bind2nd(std::multiplies<float>(), rhs));

        return lhs;
    }

    /// Multiplication operator for multipliying basic_vector instances against an scalar value.
    template <typename T, typename S, std::size_t Dimension, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr basic_vector<T, Dimension> operator*(const basic_vector<T, Dimension>& lhs, const S& rhs) noexcept
    {
        auto result = lhs;

        result *= rhs;

        return result;
    }

    /// Multiplication operator for multipliying basic_vector instances against an scalar value.
    template <typename T, typename S, std::size_t Dimension, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr basic_vector<T, Dimension> operator*(const S& lhs, const basic_vector<T, Dimension>& rhs) noexcept
    {
        return rhs * lhs;
    }

    template <typename T, typename S, std::size_t Dimension, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr basic_vector<T, Dimension>& operator/=(basic_vector<T, Dimension>& lhs, const S& rhs) noexcept
    {
        std::transform(lhs.begin(), lhs.end(), lhs.begin(), std::bind2nd(std::divides<float>(), rhs));

        return lhs;
    }

    template <typename T, typename S, std::size_t Dimension, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    constexpr basic_vector<T, Dimension> operator/(const basic_vector<T, Dimension>& lhs, const S& rhs) noexcept
    {
        auto vector = lhs;

        vector /= rhs;

        return vector;
    }
}

#endif // SCENER_MATH_BASIC_VECTOR_HPP
