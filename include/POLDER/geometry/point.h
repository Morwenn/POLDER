/*
 * Copyright (C) 2011-2012 Morwenn
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
#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <POLDER/geometry/limits.h>
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
template<size_t N, typename T>
class Point
{
    public:

        ////////////////////////////////////////////////////////////
        // Common types
        ////////////////////////////////////////////////////////////

        using value_type = T;
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;

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
        Point(const Point<N, T>& other);

        /**
         * @brief Initializer list constructor
         *
         * @param args List of coordinates
         */
        Point(const std::initializer_list<value_type>& coords);

        /**
         * Variadic constructor
         *
         * @param coords Coordinates
         */
        template<typename... Args>
        Point(Args... coords);

        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        /**
         * @brief Element accessor
         *
         * @param index Index of the ccordinate to access
         * @return indexth coordinate
         */
        value_type& operator[](size_t index);

        /**
         * @overload value_type& operator[](size_t index)
         */
        value_type operator[](size_t index) const;

        /**
         * Copy assignement operator
         */
        Point<N, T>& operator=(const Point<N, T>& other);

        // Comparison
        bool operator==(const Point<N, T>& other) const;

        bool operator!=(const Point<N, T>& other) const;

        // Point-Vector arithmetics
        Point<N, T>& operator+=(const Vector<N, T>& V);

        Point<N, T>& operator-=(const Vector<N, T>& V);

        const Point<N, T> operator+(const Vector<N, T>& V);

        const Point<N, T> operator-(const Vector<N, T>& V);

        const Vector<N, T> operator-(const Point<N, T>& other);

        ////////////////////////////////////////////////////////////
        // Coordinates aliases
        ////////////////////////////////////////////////////////////

        reference& x();
        reference& y();
        reference& z();

        value_type x() const;
        value_type y() const;
        value_type z() const;


        ////////////////////////////////////////////////////////////
        // Point iterators
        ////////////////////////////////////////////////////////////

        typedef value_type* iterator;
        typedef const value_type* const_iterator;

        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        const_iterator cbegin() const;
        const_iterator cend() const;

    private:

        // Construct the vector from the arguments
        template<typename... Args>
        void create(size_t pos, T first, Args... coords);
        void create(size_t pos, T first);

        // Member data
        value_type coordinates[N];    /**< Coordinates */

    friend class Vector<N, T>;
};

#include <POLDER/geometry/point.inl>

// Define commonly-used types
typedef Point<2>    Point2d;
typedef Point<3>    Point3d;


} // namespace geometry
} // namespace polder


#endif // _POLDER_GEOMETRY_POINT_H
