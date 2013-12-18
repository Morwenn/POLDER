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
#ifndef _POLDER_GEOMETRY_POINT_H
#define _POLDER_GEOMETRY_POINT_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <array>
#include <POLDER/algorithm.h>
#include <POLDER/geometry/types.h>


namespace polder
{
namespace geometry
{

/**
 * @brief Geometric point
 *
 * A point is simply defined by N coordinates
 * in a N-dimensional space.
 */
template<std::size_t N, typename T=double>
class Point
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
        Point();
        // Copy constructor
        Point(const Point<N, T>& other);

        /**
         * @brief Variadic constructor
         *
         * This constructor takes N parameters,
         * and constructs the point with them.
         */
        template<typename... Args>
        Point(Args... args);

        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        // Accessors
        T& operator[](std::size_t index);
        T operator[](std::size_t index) const;

        // Point-Vector arithmetic
        Point<N, T>& operator+=(const Vector<N, T>& V);
        Point<N, T>& operator-=(const Vector<N, T>& V);

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
        // Point iterators
        ////////////////////////////////////////////////////////////

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

        // Member data
        std::array<T, N> coordinates;    /**< Coordinates */
};

////////////////////////////////////////////////////////////
// Outside class operators
////////////////////////////////////////////////////////////

// Comparison
template<std::size_t N, typename T>
auto operator==(const Point<N, T>& lhs, const Point<N, T>& rhs)
    -> bool;
template<std::size_t N, typename T>
auto operator!=(const Point<N, T>& lhs, const Point<N, T>& rhs)
    -> bool;

// Point-Vector arithmetic
template<std::size_t N, typename T>
auto operator+(Point<N, T> pt, const Vector<N, T>& vec)
    -> Point<N, T>;
template<std::size_t N, typename T>
auto operator-(Point<N, T> pt, const Vector<N, T>& vec)
    -> Point<N, T>;

template<std::size_t N, typename T>
auto operator-(const Point<N, T>& lhs, const Point<N, T>& rhs)
    -> Vector<N, T>;

#include "point.inl"

} // namespace geometry
} // namespace polder


#endif // _POLDER_GEOMETRY_POINT_H
