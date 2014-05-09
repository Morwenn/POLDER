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
#ifndef POLDER_GEOMETRY_LINE_H_
#define POLDER_GEOMETRY_LINE_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <POLDER/algorithm.h>
#include <POLDER/geometry/direction.h>
#include <POLDER/geometry/point.h>
#include <POLDER/geometry/details/types.h>

namespace polder
{
namespace geometry
{
    /**
     * @brief Geometric Line
     *
     * In euclidean geometry, a Line is often defined as a
     * straight object passing by two given points. There are
     * actually many ways to define a Line. This one is defined
     * by a Point and a Direction.
     */
    template<std::size_t N, typename T=double>
    class Line
    {
        public:

            ////////////////////////////////////////////////////////////
            // Constructors
            ////////////////////////////////////////////////////////////

            // Default constructor
            Line();

            /**
             * @brief Construct a Line passing by two points.
             *
             * @param pt1 First point.
             * @param pt2 Second point.
             */
            Line(const Point<N, T>& pt1, const Point<N, T>& pt2);

            /**
             * @brief Constructs a line with a point and a vector.
             *
             * @param pt Point the line passes through.
             * @param vec Vector giving the direction of the line.
             */
            Line(const Point<N, T>& pt, const Vector<N, T>& vec);

            /**
             * @brief Constructs a line with a point and a direction.
             *
             * @param pt Point the line passes through.
             * @param dir Direction of the line.
             */
            Line(const Point<N, T>& pt, const Direction<N, T>& dir);

            ////////////////////////////////////////////////////////////
            // Miscellaneous functions
            ////////////////////////////////////////////////////////////

            /**
             * @brief Checks whether a point belongs to the line.
             *
             * @param pt Some point.
             * @return true if \a pt belongs to the line.
             */
            auto includes(const Point<N, T>& pt) const
                -> bool;

            /**
             * @brief Returns the direction of the line.
             * @return Direction of the line.
             */
            auto direction() const
                -> Direction<N, T>;

            /**
             * @brief Returns an arbitrary point belonging to the line.
             *
             * @warning For now, this function always returns the same point.
             * However, it could be improved so that it returns different
             * points depending on a given (optional) parameter.
             *
             * @return Some point belonging to the line.
             */
            auto point() const
                -> Point<N, T>;

        private:

            // Member data
            Point<N, T> _point;     /**< Some point contained in the line */
            Direction<N, T> _dir;   /**< Direction of the line */

    };

    ////////////////////////////////////////////////////////////
    // Outside class operators
    ////////////////////////////////////////////////////////////

    // Comparison
    template<std::size_t N, typename T>
    auto operator==(const Line<N, T>& lhs, const Line<N, T>& rhs)
        -> bool;
    template<std::size_t N, typename T>
    auto operator!=(const Line<N, T>& lhs, const Line<N, T>& rhs)
        -> bool;

    #include "details/line.inl"
}}

#endif // POLDER_GEOMETRY_LINE_H_
