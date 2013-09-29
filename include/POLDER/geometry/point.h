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
#include <cassert>
#include <cstdarg>
#include <initializer_list>
#include <POLDER/geometry/limits.h>


namespace polder
{
namespace geometry
{

// Forward declaration
template<size_t N> class Vector;


/**
 * @brief Geometric point
 *
 * A point is simply defined by N coordinates
 * in a N-dimensional space.
 */
template<size_t N>
class Point
{
    public:

        ////////////////////////////////////////////////////////////
        // Constructors
        ////////////////////////////////////////////////////////////

        /**
         * Default constructor
         */
        Point() = default;

        /**
         * Copy constructor
         */
        Point(const Point<N>& other);

        /**
         * @brief Initializer list constructor
         *
         * @param args List of coordinates
         */
        Point(const std::initializer_list<double>& coords);

        /**
         * Variadic constructor
         *
         * @param first First coordinate value
         */
        Point(double first, ...);


        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        /**
         * @brief Element accessor
         *
         * @param index Index of the ccordinate to access
         * @return indexth coordinate
         */
        double& operator[](size_t index);

        /**
         * @see double& operator[](size_t index)
         */
        double operator[](size_t index) const;

        /**
         * Copy assignment operator
         */
        Point<N>& operator=(const Point<N>& other);

        // Comparison
        bool operator==(const Point<N>& other) const;

        bool operator!=(const Point<N>& other) const;

        // Point-Vector arithmetics
        Point<N>& operator+=(const Vector<N>& V);

        Point<N>& operator-=(const Vector<N>& V);

        const Point<N> operator+(const Vector<N>& V);

        const Point<N> operator-(const Vector<N>& V);

        const Vector<N> operator-(const Point<N>& other);

        ////////////////////////////////////////////////////////////
        // Coordinates aliases
        ////////////////////////////////////////////////////////////

        double& x();
        double& y();
        double& z();

        double x() const;
        double y() const;
        double z() const;


        ////////////////////////////////////////////////////////////
        // Point iterators
        ////////////////////////////////////////////////////////////

        typedef double* iterator;
        typedef const double* const_iterator;

        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        const_iterator cbegin() const;
        const_iterator cend() const;

    private:

        // Member data
        double coordinates[N];    /**< Coordinates */

    friend class Vector<N>;
};

#include <POLDER/geometry/point.inl>

// Define commonly-used types
typedef Point<2>    Point2d;
typedef Point<3>    Point3d;


} // namespace geometry
} // namespace polder


#endif // _POLDER_GEOMETRY_POINT_H
