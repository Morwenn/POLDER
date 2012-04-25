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
#ifndef _POLDER_GEOMETRY_VECTOR_H
#define _POLDER_GEOMETRY_VECTOR_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <cmath>
#include <cstdarg>
#include <initializer_list>
#include <POLDER/math/norm.h>


namespace polder
{
namespace geometry
{


// Forward declarations
template<size_t N> class Direction;
template<size_t N> class Point;
template<size_t N> class Line;


/**
 * @brief Geometric vector
 *
 * A Vector is a geometric object that has a length
 * and a direction. As a Point, it can be defined
 * by N coordinates in a N-dimensional space.
 */
template<size_t N>
class Vector
{
    public:

        ////////////////////////////////////////////////////////////
        // Constructors
        ////////////////////////////////////////////////////////////

        /**
         * Default constructor
         */
        Vector();

        /**
         * Copy constructor
         */
        Vector(const Vector<N>& other);

        /**
         * Move constructor
         */
        Vector(Vector<N>&& other);

        /**
         * @brief Initializer list constructor
         *
         * @param coords List of N coordinates
         */
        Vector(const std::initializer_list<double>& coords);

        /**
         * @brief Variadic constructor
         *
         * @param first First coordinate value
         * @warning Be sure to pass doubles and not floats or any other numeric numbers
         */
        Vector(double first, ...);

        /**
         * @brief Constructs the Vector from the origin to a Point
         *
         * @param P Some Point...
         */
        Vector(const Point<N>& P);

        /**
         * @brief Construct a vector from two Points
         *
         * @param origin Origin Point
         * @param target Target Point
         */
        Vector(const Point<N>& origin, const Point<N>& target);

        /**
         * @brief Construct a vector from a Line
         *
         * Since a Line has no length, the length of
         * the resulting Vector is quite arbitrary.
         *
         * @param L Some Line...
         */
        Vector(const Line<N>& L);

        /**
         * Destructor
         */
        ~Vector();


        /**
         * @brief Vector Direction
         * @return Direction which passes through the Vector
         */
        Direction<N> direction();

        /**
         * @brief Vector norm
         *
         * @param n Norm to use
         * @return Selected Norm
         */
        double norm(math::Norm n=math::Norm::Euclidean) const;

        /**
         * @brief Vector norm overload
         * @overload double norm(Norm n=Norm::Euclidean) const
         */
        double norm(math::Norm n, unsigned int p) const;


        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        // Accessor
        double operator[](size_t index) const;
        double& operator[](size_t index);

        // Assignement
        Vector<N>& operator=(const Vector<N>& other);

        Vector<N>& operator=(Vector<N>&& other);

        // Comparison
        bool operator==(const Vector<N>& other) const;

        bool operator!=(const Vector<N>& other) const;

        // Vector arithmetics
        Vector<N>& operator+=(const Vector<N>& other);

        Vector<N>& operator-=(const Vector<N>& other);

        Vector<N> operator+(const Vector<N>& other) const;

        Vector<N> operator-(const Vector<N>& other) const;

        // Scalar product
        double operator*(const Vector<N>& other) const;

        // Opposite of the vector
        Vector<N> operator-() const;

        // Vector-double arithmetics
        Vector<N>& operator*=(double other);

        Vector<N>& operator/=(double other);

        Vector<N> operator*(double other) const;

        Vector<N> operator/(double other) const;


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
        // Vector iterators
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

        // Coordinates
        double* coordinates;    /**< Coordinates */

    friend class Point<N>;
};

#include <POLDER/geometry/vector.inl>

// Define commonly-used types
typedef Vector<2>   Vector2d;
typedef Vector<3>   Vector3d;


} // namespace geometry
} // namespace polder


#endif // _POLDER_GEOMETRY_VECTOR_H

