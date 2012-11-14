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
#ifndef _POLDER_GEOMETRY_VECTOR_H
#define _POLDER_GEOMETRY_VECTOR_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <POLDER/math/norm.h>
#include <POLDER/geometry/types.h>


namespace polder
{
namespace geometry
{


/**
 * @brief Geometric vector
 *
 * A Vector is a geometric object that has a length
 * and a direction. As a Point, it can be defined
 * by N coordinates in a N-dimensional space.
 */
template<size_t N, typename T>
class Vector
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
         * @brief Default constructor
         */
        Vector() = default;

        /**
         * @brief Copy constructor
         */
        Vector(const Vector<N, T>& other);

        /**
         * @brief Initializer list constructor
         *
         * @param coords List of N coordinates
         */
        Vector(const std::initializer_list<value_type>& coords);

        /**
         * @brief Variadic constructor
         *
         * @param coords Coordinates
         */
        template<typename... Args>
        Vector(Args... coords);

        /**
         * @brief Constructs the Vector from the origin to a Point
         *
         * @param P Some Point...
         */
        Vector(const Point<N, T>& P);

        /**
         * @brief Construct a vector from two Points
         *
         * @param origin Origin Point
         * @param target Target Point
         */
        Vector(const Point<N, T>& origin, const Point<N, T>& target);

        /**
         * @brief Construct a vector from a Line
         *
         * Since a Line has no length, the length of
         * the resulting Vector is quite arbitrary.
         *
         * @param L Some Line...
         */
        Vector(const Line<N, T>& L);

        /**
         * @brief Vector Direction
         * @return Direction which passes through the Vector
         */
        Direction<N, T> direction() const;

        /**
         * @brief Vector norm
         *
         * @param n Norm to use
         * @return Selected Norm
         */
        value_type norm(math::Norm n=math::Norm::Euclidean) const;

        /**
         * @brief Vector norm overload
         * @overload value_type norm(Norm n=Norm::Euclidean) const
         */
        value_type norm(math::Norm n, unsigned int p) const;


        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        // Accessor
        value_type operator[](size_t index) const;
        value_type& operator[](size_t index);

        // Assignement
        Vector<N, T>& operator=(const Vector<N, T>& other);

        // Comparison
        bool operator==(const Vector<N, T>& other) const;

        bool operator!=(const Vector<N, T>& other) const;

        // Vector arithmetics
        Vector<N, T>& operator+=(const Vector<N, T>& other);

        Vector<N, T>& operator-=(const Vector<N, T>& other);

        Vector<N, T> operator+(const Vector<N, T>& other) const;

        Vector<N, T> operator-(const Vector<N, T>& other) const;

        // Scalar product
        value_type operator*(const Vector<N, T>& other) const;

        // Opposite of the vector
        Vector<N, T> operator-() const;

        // Vector-float arithmetics
        Vector<N, T>& operator*=(value_type other);

        Vector<N, T>& operator/=(value_type other);

        Vector<N, T> operator*(value_type other) const;

        Vector<N, T> operator/(value_type other) const;


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
        // Vector iterators
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

        // Coordinates
        value_type coordinates[N];    /**< Coordinates */

    friend class Point<N, T>;
};

#include <POLDER/geometry/vector.inl>

// Define commonly-used types
typedef Vector<2>   Vector2d;
typedef Vector<3>   Vector3d;


} // namespace geometry
} // namespace polder


#endif // _POLDER_GEOMETRY_VECTOR_H

