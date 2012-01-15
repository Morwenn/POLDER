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
#ifndef _POLDER_GEOMETRY_POINT_H
#define _POLDER_GEOMETRY_POINT_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cassert>
#include <algorithm>
#include <cstdarg>
#include <initializer_list>
#include "limits.h"


namespace polder
{
namespace geometry
{

// Forward declaration
template<size_t N> class Vector;

// Generic point definition
template<size_t N>
class Point
{
    public:

        ////////////////////////////////////////////////////////////
        // Constructors
        ////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////
        /// Default constructor
        ///
        ////////////////////////////////////////////////////////////
        Point():
            coordinates(new double[N])
        {}

        ////////////////////////////////////////////////////////////
        /// Copy constructor
        ///
        ////////////////////////////////////////////////////////////
        Point(const Point<N>& other):
            coordinates(new double[N])
        {
            std::copy(other.coordinates, other.coordinates+N, coordinates);
        }

        ////////////////////////////////////////////////////////////
        /// Move constructor
        ///
        ////////////////////////////////////////////////////////////
        Point(Point<N>&& other):
            coordinates(other.coordinates)
        {
            other.coordinates = nullptr;
        }

        ////////////////////////////////////////////////////////////
        /// Initializer list constructor
        ///
        /// \param args: List of coordinates
        ///
        ////////////////////////////////////////////////////////////
        Point(const std::initializer_list<double>& coords):
            coordinates(new double[N])
        {
            assert(N > 1 && coords.size() == N);
            std::copy(coords.begin(), coords.end(), coordinates);
        }

        ////////////////////////////////////////////////////////////
        /// Variadic constructor
        ///
        /// \param first: First coordinate value
        ///
        ////////////////////////////////////////////////////////////
        Point(double first, ...):
            coordinates(new double[N])
        {
            assert(N > 1);
            coordinates[0] = first;
            va_list args;
            va_start(args, first);
            for (size_t i = 1 ; i < N ; ++i)
            {
                coordinates[i] = va_arg(args, double);
            }
            va_end(args);
        }


        ////////////////////////////////////////////////////////////
        /// Destructor
        ///
        ////////////////////////////////////////////////////////////
        ~Point()
        {
            delete[] coordinates;
        }


        ////////////////////////////////////////////////////////////
        /// Operators
        ///
        ////////////////////////////////////////////////////////////

        // Element accessor
        double& operator[](size_t index)
        {
            assert(index < N);
            return coordinates[index];
        }
        double operator[](size_t index) const
        {
            assert(index < N);
            return coordinates[index];
        }

        // Assignement
        Point<N>& operator=(const Point<N>& other)
        {
            if (this != &other)
            {
                delete[] coordinates;
                coordinates = new double[N];
                std::copy(other.coordinates, other.coordinates+N, coordinates);
            }
            return *this;
        }

        Point<N>& operator=(Point<N>&& other)
        {
            if (this != &other)
            {
                coordinates = other.coordinates;
                other.coordinates = nullptr;
            }
            return *this;
        }

        // Comparison
        bool operator==(const Point<N>& other) const
        {
            return round_equal(coordinates, coordinates+N, other.coordinates);
        }

        bool operator!=(const Point<N>& other) const
        {
            return !(*this == other);
        }

        // Point-Vector arithmetics
        Point<N>& operator+=(const Vector<N>& V)
        {
            for (size_t i = 0 ; i < N ; ++i)
            {
                coordinates[i] += V[i];
            }
            return *this;
        }

        Point<N>& operator-=(const Vector<N>& V)
        {
            for (size_t i = 0 ; i < N ; ++i)
            {
                coordinates[i] -= V[i];
            }
            return *this;
        }

        const Point<N> operator+(const Vector<N>& V)
        {
            return Point<N>(*this) += V;
        }

        const Point<N> operator-(const Vector<N>& V)
        {
            return Point<N>(*this) -= V;
        }

        const Vector<N> operator-(const Point<N>& other)
        {
            Vector<N> res = *this;
            for (size_t i = 0 ; i < N ; ++i)
            {
                res.coordinates[i] -= other[i];
            }
            return res;
        }

        ////////////////////////////////////////////////////////////
        /// Coordinates aliases
        ///
        ////////////////////////////////////////////////////////////

        inline double& x()
        {
            return coordinates[0];
        }
        inline double& y()
        {
            assert(N > 1);
            return coordinates[1];
        }
        inline double& z()
        {
            assert(N > 2);
            return coordinates[2];
        }
        inline double& w()
        {
            assert(N > 3);
            return coordinates[3];
        }

        inline double x() const
        {
            return coordinates[0];
        }
        inline double y() const
        {
            assert(N > 1);
            return coordinates[1];
        }
        inline double z() const
        {
            assert(N > 2);
            return coordinates[2];
        }
        inline double w() const
        {
            assert(N > 3);
            return coordinates[3];
        }


        ////////////////////////////////////////////////////////////
        /// Point iterators
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
            return coordinates + N;
        }

        inline const_iterator begin() const
        {
            return coordinates;
        }
        inline const_iterator end() const
        {
            return coordinates + N;
        }

        inline const_iterator cbegin() const
        {
            return coordinates;
        }
        inline const_iterator cend() const
        {
            return coordinates + N;
        }

    private:

        // Coordinates
        double* coordinates;
        friend class Vector<N>;
};


} // namespace geo
} // namespace polder


#endif // _POLDER_GEOMETRY_POINT_H
