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
#ifndef POLDER_GEOMETRY_DIRECTION_H_
#define POLDER_GEOMETRY_DIRECTION_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <cmath>
#include <POLDER/algorithm.h>
#include <POLDER/geometry/details/types.h>
#include <POLDER/geometry/details/vector_base.h>

namespace polder
{
namespace geometry
{
    /**
     * @brief Geometric direction
     *
     * A direction is a normalized Vector. While it may seem to
     * do less than a Vector, it's actually heavier since it is
     * normalized on construction.
    */
    template<std::size_t N, typename T=double>
    class Direction:
        public ImmutableVectorBase<N, T>
    {
        public:

            ////////////////////////////////////////////////////////////
            // Types
            ////////////////////////////////////////////////////////////

            using super = ImmutableVectorBase<N, T>;

            // Value
            using typename super::value_type;
            using typename super::const_reference;
            using typename super::const_pointer;

            // Iterators
            using typename super::const_iterator;

            ////////////////////////////////////////////////////////////
            // Constructors
            ////////////////////////////////////////////////////////////

            // Default constructor
            Direction();

            /**
             * @brief Direction of a Line passing by the origin and a given point
             *
             * @param P Point forming a Line with the Origin
             */
            Direction(const Point<N, T>& pt);

            /**
             * @brief Direction of a Line passing by two given points
             *
             * @param P1 First Point
             * @param P2 Second Point
             */
            Direction(const Point<N, T>& pt1, const Point<N, T>& pt2);

            /**
             * @brief Creates the Direction from a Vector
             *
             * @param V Vector whose we take the direction
             */
            Direction(const Vector<N, T>& vec);

            /**
             * @brief Creates the Direction from a Line
             *
             * @param L Line whose we take the direction
             */
            Direction(const Line<N, T>& line);

        private:

            // Normalize the coordinates
            auto normalize()
                -> void;

            // Member data
            using super::coordinates;
    };

    ////////////////////////////////////////////////////////////
    // Outside class operators
    ////////////////////////////////////////////////////////////

    // Comparison
    template<std::size_t N, typename T>
    auto operator==(const Direction<N, T>& lhs, const Direction<N, T>& rhs)
        -> bool;
    template<std::size_t N, typename T>
    auto operator!=(const Direction<N, T>& lhs, const Direction<N, T>& rhs)
        -> bool;

    #include "details/direction.inl"
}}

#endif // POLDER_GEOMETRY_DIRECTION_H_
