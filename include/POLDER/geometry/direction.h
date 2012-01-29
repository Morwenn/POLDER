/*
 * Copyright (C) 2011 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _POLDER_GEOMETRY_DIRECTION_H
#define _POLDER_GEOMETRY_DIRECTION_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <POLDER/geometry/limits.h>
#include <POLDER/geometry/point.h>


namespace polder
{
namespace geometry
{

// Forward declarations
template<size_t N> class Vector;
template<size_t N> class Line;


/**
 * @brief Geometric direction
 *
 * A direction can be viewed as vector whose norm does not matter.
 * Because of this, when created, all the coordinates are divided
 * by the first one.
 * So, we know that the first coordinate will always be 1.0 then
 * we do not have to store it.
 *
 * Actually, remember that a direction has N-1 coordinates in a
 * N-dimensional space when you have to use it.
*/
template<size_t N>
class Direction
{
    public:

        ////////////////////////////////////////////////////////////
        // Constructors
        ////////////////////////////////////////////////////////////

        /**
         * Default constructor
         */
        Direction();

        /**
         * Copy constructor
         */
        Direction(const Direction<N>& other);

        /**
         * Move constructor
         */
        Direction(Direction<N>&& other);

        /**
         * @brief Direction of a Line passing by the origin and a given point
         *
         * @param P Point forming a Line with the Origin
         */
        Direction(const Point<N>& P);

        /**
         * @brief Direction of a Line passing by two given points
         *
         * @param P1 First Point
         * @param P2 Second Point
         */
        Direction(const Point<N>& P1, const Point<N>& P2);

        /**
         * @brief Creates the Direction from a Vector
         *
         * @param V Vector whose we take the direction
         */
        Direction(const Vector<N>& V);

        /**
         * @brief Creates the Direction from a Line
         *
         * @param L Line whose we take the direction
         */
        Direction(const Line<N>& L);

        /**
         * Destructor
         */
        ~Direction();


        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        /**
         * @brief Element accessor
         *
         * @param Index of the coordinate to get
         * @return Coordinate at index
         */
        double operator[](size_t index) const;

        /**
         * Copy assignement operator
         */
        Direction<N>& operator=(const Direction<N>& other);

        /**
         * Move assignement operator
         */
        Direction<N>& operator=(Direction<N>&& other);

        /**
         * @brief Equality between two Directions
         *
         * Compares two directions taking the margin error in account
         *
         * @param other Right operand (Direction)
         * @return True if the Directions are equal
         */
        bool operator==(const Direction<N>& other) const;

        /**
         * @brief Inequality between two Directions
         *
         * Compares two directions taking the margin error in account
         *
         * @param other Right operand (Direction)
         * @return True if the Directions are not equal
         */
        bool operator!=(const Direction<N>& other) const;

        /**
         * @brief Opposite of the direction
         *
         * @return Element-wise opposite of the direction
         */
        Direction<N> operator-() const;


        ////////////////////////////////////////////////////////////
        // Iterators
        ////////////////////////////////////////////////////////////

        // Basic iterators and constant iterators
        typedef double* iterator;
        typedef const double* const_iterator;

        /**
         * @brief First coordinate of a Direction
         *
         * @return Iterator on the first coordinate of a Direction
         */
        iterator begin();

        /**
         * @brief Last coordinate of a Direction
         *
         * @return Iterator on the last coordinate of a Direction
         */
        iterator end();

        /**
         * @brief First coordinate of a Direction
         *
         * @return Constant iterator on the first coordinate of a Direction
         */
        const_iterator begin() const;

        /**
         * @brief Last coordinate of a Direction
         *
         * @return Constant iterator on the last coordinate of a Direction
         */
        const_iterator end() const;

        /**
         * @brief First coordinate of a Direction
         *
         * @return Constant iterator on the first coordinate of a Direction
         */
        const_iterator cbegin() const;

        /**
         * @brief Last coordinate of a Direction
         *
         * @return Constant iterator on the last coordinate of a Direction
         */
        const_iterator cend() const;

    private:

        // Member data
        double* coordinates; /**< Coordinates of the Direction */
};

#include <POLDER/geometry/direction.inl>

// Define commonly-used types
typedef Direction<2>    Direction2d;
typedef Direction<3>    Direction3d;


} // namespace geo
} // namespace polder


#endif // _POLDER_GEOMETRY_DIRECTION_H

