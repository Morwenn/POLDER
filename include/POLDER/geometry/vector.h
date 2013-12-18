/*
 * Copyright (C) 2011-2013 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */
#ifndef _POLDER_GEOMETRY_VECTOR_H
#define _POLDER_GEOMETRY_VECTOR_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <array>
#include <cmath>
#include <POLDER/algorithm.h>
#include <POLDER/math/norm.h>
#include <POLDER/geometry/types.h>


namespace polder
{
namespace geometry
{

/**
 * @brief Geometric vector
 *
 * A Vector is a geometric object that has a length
 * and a direction. As a Point, it can be defined
 * by N coordinates in a N-dimensional space.
 */
template<std::size_t N, typename T=double>
class Vector
{
    public:

        ////////////////////////////////////////////////////////////
        // Types
        ////////////////////////////////////////////////////////////

        // Value
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        // Iterators
        using iterator = typename std::array<T, N>::iterator;
        using const_iterator = typename std::array<T, N>::const_iterator;

        ////////////////////////////////////////////////////////////
        // Constructors
        ////////////////////////////////////////////////////////////

        // Default constructor
        Vector();
        // Copy constructor
        Vector(const Vector<N, T>& other);

        /**
         * @brief Variadic constructor
         *
         * This constructor takes N parameters,
         * and constructs the point with them.
         */
        template<typename... Args>
        Vector(Args... args);

        /**
         * @brief Constructs the Vector from the origin to a Point
         *
         * @param P Some Point...
         */
        Vector(const Point<N, T>& pt);

        /**
         * @brief Construct a vector from two Points
         *
         * @param origin Origin Point
         * @param target Target Point
         */
        Vector(const Point<N, T>& origin, const Point<N, T>& target);

        /**
         * @brief Construct a vector from a Line
         *
         * Since a Line has no length, the length of
         * the resulting Vector is quite arbitrary.
         *
         * @param L Some Line...
         */
        Vector(const Line<N, T>& line);

        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        // Accessors
        auto operator[](std::size_t index)
            -> reference;
        auto operator[](std::size_t index) const
            -> const_reference;

        // Vector arithmetic
        auto operator+=(const Vector<N, T>& val)
            -> Vector&;
        auto operator-=(const Vector<N, T>& val)
            -> Vector&;

        // Vector-scalar arithmetic
        auto operator*=(value_type other)
            -> Vector&;
        auto operator/=(value_type other)
            -> Vector&;

        ////////////////////////////////////////////////////////////
        // Coordinates aliases
        ////////////////////////////////////////////////////////////

        auto x()
            -> reference;
        auto y()
            -> reference;
        auto z()
            -> reference;

        auto x() const
            -> const_reference;
        auto y() const
            -> const_reference;
        auto z() const
            -> const_reference;

        ////////////////////////////////////////////////////////////
        // Vector iterators
        ////////////////////////////////////////////////////////////

        auto begin()
            -> iterator;
        auto begin() const
            -> const_iterator;
        auto cbegin() const
            -> const_iterator;
        auto end()
            -> iterator;
        auto end() const
            -> const_iterator;
        auto cend() const
            -> const_iterator;

        ////////////////////////////////////////////////////////////
        // Miscellaneous functions
        ////////////////////////////////////////////////////////////

        /**
         * @brief Vector Direction
         * @return Direction of the Vector
         */
        auto direction() const
            -> Direction<N, T>;

        /**
         * @brief Vector norm
         *
         * @return Selected topological norm.
         */
        template<typename Norm=math::norm::euclidean>
        auto norm() const
            -> value_type;

        template<typename Norm=math::norm::p>
        auto norm(unsigned p) const
            -> value_type;

    private:

        template<typename First, typename... Args>
        auto construct(First first, Args... args)
            -> void;
        template<typename First>
        auto construct(First first)
            -> void;

        // Coordinates
        std::array<T, N> coordinates;    /**< Coordinates */
};

////////////////////////////////////////////////////////////
// Outside class operators
////////////////////////////////////////////////////////////

// Comparison
template<std::size_t N, typename T>
auto operator==(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
    -> bool;
template<std::size_t N, typename T>
auto operator!=(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
    -> bool;

// Vector arithmetic
template<std::size_t N, typename T>
auto operator+(Vector<N, T> lhs, const Vector<N, T>& rhs)
    -> Vector<N, T>;
template<std::size_t N, typename T>
auto operator-(Vector<N, T> lhs, const Vector<N, T>& rhs)
    -> Vector<N, T>;

// Scalar product
template<std::size_t N, typename T>
auto operator*(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
    -> T;

// Opposite of a vector
template<std::size_t N, typename T>
auto operator-(Vector<N, T> vec)
    -> Vector<N, T>;

// Vector-scalar arithmetic
template<std::size_t N, typename T>
auto operator*(Vector<N, T> vec, T val)
    -> Vector<N, T>;
template<std::size_t N, typename T>
auto operator*(T val, Vector<N, T> vec)
    -> Vector<N, T>;
template<std::size_t N, typename T>
auto operator/(Vector<N, T> vec, T val)
    -> Vector<N, T>;

#include "vector.inl"

} // namespace geometry
} // namespace polder


#endif // _POLDER_GEOMETRY_VECTOR_H

