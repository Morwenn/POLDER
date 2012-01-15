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
#include "limits.h"
#include "point.h"


namespace polder
{
namespace geometry
{

// Forward declarations
template<size_t N> class Vector;
template<size_t N> class Line;


/*
    A direction can be viewed as vector whose norm does not matter.
    Because of this, when created, all the coordinates are divided
    by the first one.
    So, we know that the first coordinate will always be 1.0 and then
    we do not have to store it.

    Actually, remember that a direction has N-1 coordinates in a
    N-dimensional space when you have to use it.
*/
template<size_t N>
class Direction
{
    public:

        ////////////////////////////////////////////////////////////
        // Constructors
        ////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////
        /// Default constructor
        ///
        ////////////////////////////////////////////////////////////
        Direction():
            coordinates(new double[N-1])
        {}

        ////////////////////////////////////////////////////////////
        /// Copy constructor
        ///
        ////////////////////////////////////////////////////////////
        Direction(const Direction<N>& other):
            coordinates(new double[N-1])
        {
            std::copy(other.coordinates, other.coordinates+N-1, coordinates);
        }

        ////////////////////////////////////////////////////////////
        /// Move constructor
        ///
        ////////////////////////////////////////////////////////////
        Direction(Direction<N>&& other):
            coordinates(other.coordinates)
        {
            other.coordinates = nullptr;
        }

        ////////////////////////////////////////////////////////////
        /// Direction of a Line passing by the origin and a given point
        ///
        /// \param P: Point forming a Line with the Origin
        ///
        ////////////////////////////////////////////////////////////
        Direction(const Point<N>& P):
            coordinates(new double[N-1])
        {
            for (size_t i = 1 ; i < N ; ++i)
            {
                coordinates[i-1] = P[i] / P[0];
            }
        }

        ////////////////////////////////////////////////////////////
        /// Direction of a Line passing by two given points
        ///
        /// \param P1: First Point
        /// \param P2: Second Point
        ///
        ////////////////////////////////////////////////////////////
        Direction(const Point<N>& P1, const Point<N>& P2):
            coordinates(new double[N-1])
        {
            const double first = P2[0] - P1[0];
            for (size_t i = 1 ; i < N ; ++i)
            {
                coordinates[i-1] = (P2[i] - P1[i]) / first;
            }
        }

        ////////////////////////////////////////////////////////////
        /// Creates the Direction from a Vector
        ///
        /// \param V: Vector whose we take the direction
        ///
        ////////////////////////////////////////////////////////////
        Direction(const Vector<N>& V):
            coordinates(new double[N-1])
        {
            for (size_t i = 1 ; i < N ; ++i)
            {
                coordinates[i-1] = V[i] / V[0];
            }
        }

        ////////////////////////////////////////////////////////////
        /// Creates the Direction from a Line
        ///
        /// \param L: Line whose we take the direction
        ///
        ////////////////////////////////////////////////////////////
        Direction(const Line<N>& L)
        {
            *this = L.direction();
        }

        ////////////////////////////////////////////////////////////
        /// Destructor
        ///
        ////////////////////////////////////////////////////////////
        ~Direction()
        {
            delete[] coordinates;
        }


        ////////////////////////////////////////////////////////////
        /// Operators
        ///
        ////////////////////////////////////////////////////////////

        // Element accessor
        double operator[](size_t index) const
        {
            assert(index < N-1);
            return coordinates[index];
        }

        // Assignement
        Direction<N>& operator=(const Direction<N>& other)
        {
            if (this != &other)
            {
                delete[] coordinates;
                coordinates = new double[N-1];
                std::copy(other.coordinates, other.coordinates+N-1, coordinates);
            }
            return *this;
        }

        Direction<N>& operator=(Direction<N>&& other)
        {
            if (this != &other)
            {
                coordinates = other.coordinates;
                other.coordinates = nullptr;
            }
            return *this;
        }

        // Comparison
        bool operator==(const Direction<N>& other) const
        {
            return round_equal(coordinates, coordinates+N-1, other.coordinates);
        }

        bool operator!=(const Direction<N>& other) const
        {
            return !(*this == other);
        }

        // Opposite of the direction
        Direction<N> operator-() const
        {
            Direction<N> D(*this);
            for (size_t i = 0 ; i < N-1 ; ++i)
            {
                D.coordinates[i] = -D.coordinates[i];
            }
            return D;
        }


        ////////////////////////////////////////////////////////////
        /// Direction iterators
        ///
        ////////////////////////////////////////////////////////////

        typedef double* iterator;
        typedef const double* const_iterator;

        inline iterator begin()
        {
            return coordinates;
        }
        inline iterator end()
        {
            return coordinates + N - 1;
        }

        inline const_iterator begin() const
        {
            return coordinates;
        }
        inline const_iterator end() const
        {
            return coordinates + N - 1;
        }

        inline const_iterator cbegin() const
        {
            return coordinates;
        }
        inline const_iterator cend() const
        {
            return coordinates + N - 1;
        }

    private:

        // Coordinates
        double* coordinates;
};


} // namespace geo
} // namespace polder


#endif // _POLDER_GEOMETRY_DIRECTION_H

