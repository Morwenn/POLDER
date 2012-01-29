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
#include <POLDER/geometry/direction.h>
#include <POLDER/geometry/point.h>


namespace polder
{
namespace geometry
{


/**
 * Different mathematical vector norms
 */
enum class Norm
{
    Euclidean,  /**< Euclidean norm (norm 2) */
    Manhattan,  /**< Manhattan, Taxicab norm (norm 1) */
    Maximum,    /**< Maximum norm (norm infinite) */
    P           /**< P norm */
};

// Forward declaration
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
        Vector():
            coordinates(new double[N])
        {}

        /**
         * Copy constructor
         */
        Vector(const Vector<N>& other):
            coordinates(new double[N])
        {
            std::copy(other.coordinates, other.coordinates+N, coordinates);
        }

        /**
         * Move constructor
         */
        Vector(Vector<N>&& other):
            coordinates(other.coordinates)
        {
            other.coordinates = nullptr;
        }

        /**
         * @brief Initializer list constructor
         *
         * @param coords List of N coordinates
         */
        Vector(const std::initializer_list<double>& coords):
            coordinates(new double[N])
        {
            assert(N > 1 && coords.size() == N);
            std::copy(coords.begin(), coords.end(), coordinates);
        }

        /**
         * @brief Variadic constructor
         *
         * @param first First coordinate value
         * @warning Be sure to pass doubles and not floats or any other numeric numbers
         */
        Vector(double first, ...):
            coordinates(new double[N])
        {
            coordinates[0] = first;

            va_list args;
            va_start(args, first);
            for (size_t i = 1 ; i < N ; ++i)
            {
                coordinates[i] = va_arg(args, double);
            }
            va_end(args);
        }

        /**
         * @brief Constructs the Vector from the origin to a Point
         *
         * @param P Some Point...
         */
        Vector(const Point<N>& P):
            coordinates(new double[N])
        {
            std::copy(P.coordinates, P.coordinates+N, coordinates);
        }

        /**
         * @brief Construct a vector from two Points
         *
         * @param origin Origin Point
         * @param target Target Point
         */
        Vector(const Point<N>& origin, const Point<N>& target):
            coordinates(new double[N])
        {
            for (size_t i = 0 ; i < N ; ++i)
            {
                coordinates[i] = target[i] - origin[i];
            }
        }

        /**
         * @brief Construct a vector from a Line
         *
         * Since a Line has no length, the length of
         * the resulting Vector is quite arbitrary.
         *
         * @param L Some Line...
         */
        Vector(const Line<N>& L):
            coordinates(new double[N])
        {
            coordinates[0] = 1.0;
            const Direction<N>& dir = L.direction();
            for (size_t i = 1 ; i < N ; ++i)
            {
                coordinates[i] = dir[i-1];
            }
        }

        /**
         * Destructor
         */
        ~Vector()
        {
            delete[] coordinates;
        }


        /**
         * @brief Vector Direction
         * @return Direction which passes through the Vector
         */
        Direction<N> direction()
        {
            return Direction<N>(*this);
        }

        /**
         * @brief Vector norm
         *
         * @param n Norm to use
         * @return Selected Norm
         */
        double norm(Norm n=Norm::Euclidean) const
        {
            switch (n)
            {
                case Norm::Manhattan:
                {
                    double res = 0;
                    for (size_t i = 0 ; i < N ; ++i)
                    {
                        res += fabs(coordinates[i]);
                    }
                    return res;
                }
                case Norm::Euclidean:
                {
                    double res = 0;
                    for (size_t i = 0 ; i < N ; ++i)
                    {
                        res += coordinates[i] * coordinates[i];
                    }
                    return sqrt(res);
                }
                case Norm::Maximum:
                {
                    double res = fabs(coordinates[0]);
                    for (size_t i = 1 ; i < N ; ++i)
                    {
                        const double tmp = fabs(coordinates[i]);
                        if (tmp > res)
                        {
                            res = tmp;
                        }
                    }
                    return res;
                }
            }
            return 1.0; // Should never be executed
        }

        /**
         * @brief Vector norm overload
         * @overload double norm(Norm n=Norm::Euclidean) const
         */
        double norm(Norm n, unsigned int p) const
        {
            switch (n)
            {
                case Norm::P:
                {
                    double res = 0;
                    for (size_t i = 0 ; i < N ; ++i)
                    {
                        res += pow(fabs(coordinates[i]), p);
                    }
                    return pow(res, 1.0 / p);
                }
            }
            return 1.0; // Should never be executed
        }


        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        // Accessor
        double operator[](size_t index) const
        {
            assert(index < N);
            return coordinates[index];
        }
        double& operator[](size_t index)
        {
            assert(index < N);
            return coordinates[index];
        }

        // Assignement
        Vector<N>& operator=(const Vector<N>& other)
        {
            if (this != &other)
            {
                delete[] coordinates;
                coordinates = new double[N];
                std::copy(other.coordinates, other.coordinates+N, coordinates);
            }
            return *this;
        }

        Vector<N>& operator=(Vector<N>&& other)
        {
            if (this != &other)
            {
                coordinates = other.coordinates;
                other.coordinates = nullptr;
            }
            return *this;
        }

        // Comparison
        bool operator==(const Vector<N>& other) const
        {
            return round_equal(coordinates, coordinates+N, other.coordinates);
        }

        bool operator!=(const Vector<N>& other) const
        {
            return !(*this == other);
        }

        // Vector arithmetics
        Vector<N>& operator+=(const Vector<N>& other)
        {
            for (size_t i = 0 ; i < N ; ++i)
            {
                coordinates[i] += other.coordinates[i];
            }
            return *this;
        }

        Vector<N>& operator-=(const Vector<N>& other)
        {
            for (size_t i = 0 ; i < N ; ++i)
            {
                coordinates[i] -= other.coordinates[i];
            }
            return *this;
        }

        Vector<N> operator+(const Vector<N>& other) const
        {
            return Vector<N>(*this) += other;
        }

        Vector<N> operator-(const Vector<N>& other) const
        {
            return Vector<N>(*this) -= other;
        }

        // Scalar product
        double operator*(const Vector<N>& other) const
        {
            double res = 0;
            for (size_t i = 0 ; i < N ; ++i)
            {
                res += coordinates[i] * other.coordinates[i];
            }
            return res;
        }

        // Opposite of the vector
        Vector<N> operator-() const
        {
            Vector<N> V = *this;
            for (size_t i = 0 ; i < N ; ++i)
            {
                V.coordinates[i] = -V.coordinates[i];
            }
            return V;
        }

        // Vector-double arithmetics
        Vector<N>& operator*=(double other)
        {
            for (size_t i = 0 ; i < N ; ++i)
            {
                coordinates *= other;
            }
            return *this;
        }

        Vector<N>& operator/=(double other)
        {
            assert(other != 0);
            for (size_t i = 0 ; i < N ; ++i)
            {
                coordinates /= other;
            }
            return *this;
        }

        Vector<N> operator*(double other) const
        {
            return Vector(*this) *= other;
        }

        Vector<N> operator/(double other) const
        {
            return Vector(*this) /= other;
        }


        ////////////////////////////////////////////////////////////
        // Coordinates aliases
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


        ////////////////////////////////////////////////////////////
        // Vector iterators
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
        double* coordinates;    /**< Coordinates */

    friend class Point<N>;
};


} // namespace geometry
} // namespace polder


#endif // _POLDER_GEOMETRY_VECTOR_H

