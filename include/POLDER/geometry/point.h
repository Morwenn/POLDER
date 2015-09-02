/*
 * Copyright (C) 2011-2014 Morwenn
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
#ifndef POLDER_GEOMETRY_POINT_H_
#define POLDER_GEOMETRY_POINT_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <POLDER/algorithm.h>
#include <POLDER/functional.h>
#include <POLDER/geometry/details/types.h>
#include <POLDER/geometry/details/vector_base.h>
#include <POLDER/math/formula.h>

namespace polder
{
namespace geometry
{
    /**
     * @brief Geometric point
     *
     * A point is defined by N coordinates
     * in a N-dimensional space.
     */
    template<std::size_t N, typename T=double>
    class Point:
        public MutableVectorBase<N, T>
    {
        public:

            ////////////////////////////////////////////////////////////
            // Types
            ////////////////////////////////////////////////////////////

            using super = MutableVectorBase<N, T>;

            // Value
            using typename super::value_type;
            using typename super::reference;
            using typename super::const_reference;
            using typename super::pointer;
            using typename super::const_pointer;

            // Iterators
            using typename super::iterator;
            using typename super::const_iterator;

            ////////////////////////////////////////////////////////////
            // Constructors
            ////////////////////////////////////////////////////////////

            // Default constructor
            Point();

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

            // Point-Vector arithmetic
            auto operator+=(const Vector<N, T>& vec)
                -> Point&;
            auto operator-=(const Vector<N, T>& vec)
                -> Point&;

        private:

            // Member data
            using super::coordinates;
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

    // Relational operators
    template<std::size_t N, typename T>
    auto operator<(const Point<N, T>& lhs, const Point<N, T>& rhs)
        -> bool;
    template<std::size_t N, typename T>
    auto operator<=(const Point<N, T>& lhs, const Point<N, T>& rhs)
        -> bool;
    template<std::size_t N, typename T>
    auto operator>(const Point<N, T>& lhs, const Point<N, T>& rhs)
        -> bool;
    template<std::size_t N, typename T>
    auto operator>=(const Point<N, T>& lhs, const Point<N, T>& rhs)
        -> bool;

    // Point-Vector arithmetic
    template<std::size_t N, typename T>
    auto operator+(Point<N, T> pt, const Vector<N, T>& vec)
        -> Point<N, T>;
    template<std::size_t N, typename T>
    auto operator+(const Vector<N, T>& vec, Point<N, T> pt)
        -> Point<N, T>;
    template<std::size_t N, typename T>
    auto operator-(Point<N, T> pt, const Vector<N, T>& vec)
        -> Point<N, T>;

    template<std::size_t N, typename T>
    auto operator-(const Point<N, T>& lhs, const Point<N, T>& rhs)
        -> Vector<N, T>;

    #include "details/point.inl"
}}

#endif // POLDER_GEOMETRY_POINT_H_
