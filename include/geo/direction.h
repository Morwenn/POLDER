////////////////////////////////////////////////////////////
///
/// POLDER Geo Direction - POLDER library providing the Direction class
/// Written by Morwenn Edrahir, 2011
///
////////////////////////////////////////////////////////////

/*
    A direction can be viewed as vector whose norm does not matter.
    Because of this, when created, all the coordinates are divided
    by the first one.
    So, we know that the first coordinate will always be 1.0 and then
    we do not have to store it.

    Actually, remember that a direction has N-1 coordinates in a
    N-dimensional space when you have to use it.
*/


#ifndef _POLDER_GEO_DIRECTION_H
#define _POLDER_GEO_DIRECTION_H

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include "limits.h"
#include "point.h"


namespace polder
{
namespace geo
{

// Forward declarations
template<size_t N> class Vector;
template<size_t N> class Line;

// Direction definition
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
            coordinates(NULL)
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
            other.coordinates = NULL;
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
        /// Size accessor
        ///
        ////////////////////////////////////////////////////////////
        size_t dimension() const
        {
            return N;
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
                other.coordinates = NULL;
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

        class const_iterator
        {
            public:

                // Iterator arithmetics
                double operator*() const
                {
                    return *value;
                }
                void operator++()
                {
                    ++value;
                }
                void operator++(int)
                {
                    ++value;
                }
                void operator--()
                {
                    --value;
                }
                void operator--(int)
                {
                    --value;
                }
                bool operator==(const_iterator other) const
                {
                    return value == other.value;
                }
                bool operator!=(const_iterator other) const
                {
                    return value != other.value;
                }

            private:

                const_iterator(double* val):
                    value(val)
                {}
                double* value;
                friend class Direction<N>;
        };

        const_iterator begin() const
        {
            return const_iterator(coordinates);
        }

        const_iterator end() const
        {
            return const_iterator(coordinates+N-1);
        }

    private:

        // Coordinates
        double* coordinates;
};


} // namespace geo
} // namespace polder


#endif

