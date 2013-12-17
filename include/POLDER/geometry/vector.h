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
#include <cmath>
#include <initializer_list>
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
        // Constructors
        ////////////////////////////////////////////////////////////

        /**
         * @brief Default constructor
         */
        Vector() = default;

        /**
         * @brief Copy constructor
         */
        Vector(const Vector<N, T>& other);

        /**
         * @brief Initializer list constructor
         *
         * @param coords List of N coordinates
         */
        Vector(std::initializer_list<T> coords);

        /**
         * Variadic constructor
         */
        template<typename... Args>
        Vector(Args... args);

        /**
         * @brief Constructs the Vector from the origin to a Point
         *
         * @param P Some Point...
         */
        Vector(const Point<N, T>& P);

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
        Vector(const Line<N, T>& L);

        /**
         * @brief Vector Direction
         * @return Direction which passes through the Vector
         */
        Direction<N, T> direction() const;

        /**
         * @brief Vector norm
         *
         * @return Selected topological norm.
         */
        template<typename Norm=math::norm::euclidean>
        auto norm() const
            -> T;

        template<typename Norm=math::norm::p>
        auto norm(unsigned p) const
            -> T;


        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        // Accessors
        T operator[](std::size_t index) const;
        T& operator[](std::size_t index);

        // Assignment
        Vector<N, T>& operator=(const Vector<N, T>& other);

        // Vector arithmetic
        Vector<N, T>& operator+=(const Vector<N, T>& other);

        Vector<N, T>& operator-=(const Vector<N, T>& other);

        Vector<N, T> operator+(const Vector<N, T>& other) const;

        Vector<N, T> operator-(const Vector<N, T>& other) const;

        // Scalar product
        T operator*(const Vector<N, T>& other) const;

        // Opposite of the vector
        Vector<N, T> operator-() const;

        // Vector-T arithmetic
        Vector<N, T>& operator*=(T other);

        Vector<N, T>& operator/=(T other);

        Vector<N, T> operator*(T other) const;

        Vector<N, T> operator/(T other) const;


        ////////////////////////////////////////////////////////////
        // Coordinates aliases
        ////////////////////////////////////////////////////////////

        T& x();
        T& y();
        T& z();

        T x() const;
        T y() const;
        T z() const;


        ////////////////////////////////////////////////////////////
        // Vector iterators
        ////////////////////////////////////////////////////////////

        using iterator = T*;
        using const_iterator = const T*;

        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        const_iterator cbegin() const;
        const_iterator cend() const;

    private:

        template<typename First, typename... Args>
        auto construct(First first, Args... args)
            -> void;
        template<typename First>
        auto construct(First first)
            -> void;

        // Coordinates
        T coordinates[N];    /**< Coordinates */

    friend class Point<N, T>;
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

#include "vector.inl"

} // namespace geometry
} // namespace polder


#endif // _POLDER_GEOMETRY_VECTOR_H

