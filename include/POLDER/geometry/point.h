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
#include <initializer_list>
#include <POLDER/geometry/limits.h>


namespace polder
{
namespace geometry
{

// Forward declaration
template<size_t N, typename T>
class Vector;


/**
 * @brief Geometric point
 *
 * A point is simply defined by N coordinates
 * in a N-dimensional space.
 */
template<size_t N, typename T=double>
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
        Point(const Point<N, T>& other);

        /**
         * @brief Initializer list constructor
         *
         * @param args List of coordinates
         */
        Point(const std::initializer_list<T>& coords);

        /**
         * Variadic constructor
         */
        template<typename... Args>
        Point(Args... args);


        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        /**
         * @brief Element accessor
         *
         * @param index Index of the ccordinate to access
         * @return indexth coordinate
         */
        T& operator[](size_t index);

        /**
         * @see T& operator[](size_t index)
         */
        T operator[](size_t index) const;

        /**
         * Copy assignment operator
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

        T& x();
        T& y();
        T& z();

        T x() const;
        T y() const;
        T z() const;


        ////////////////////////////////////////////////////////////
        // Point iterators
        ////////////////////////////////////////////////////////////

        typedef T* iterator;
        typedef const T* const_iterator;

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
        T coordinates[N];    /**< Coordinates */

    friend class Vector<N, T>;
};

#include <POLDER/geometry/point.inl>

// Define commonly-used types
typedef Point<2>    Point2d;
typedef Point<3>    Point3d;


} // namespace geometry
} // namespace polder


#endif // _POLDER_GEOMETRY_POINT_H
