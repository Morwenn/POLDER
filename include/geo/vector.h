////////////////////////////////////////////////////////////
///
/// POLDER Geo Vector - POLDER library providing the Vector class
/// Written by Morwenn Edrahir, 2011
///
////////////////////////////////////////////////////////////

#ifndef _POLDER_GEO_VECTOR_H
#define _POLDER_GEO_VECTOR_H

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <cmath>
#include <cstdarg>
#include <initializer_list>
#include "direction.h"
#include "point.h"


namespace polder
{
namespace geo
{


// Different norms
enum class Norm
{
    Euclidean = 0,
    Manhattan,
    Maximum,
    P
};

// Forward declaration
template<size_t N> class Line;

// Vector definition
template<size_t N>
class Vector
{
    public:

        ////////////////////////////////////////////////////////////
        // Constructors
        ////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////
        /// Default constructor
        ///
        ////////////////////////////////////////////////////////////
        Vector():
            coordinates(NULL)
        {}

        ////////////////////////////////////////////////////////////
        /// Copy constructor
        ///
        ////////////////////////////////////////////////////////////
        Vector(const Vector<N>& other):
            coordinates(new double[N])
        {
            std::copy(other.coordinates, other.coordinates+N, coordinates);
        }

        ////////////////////////////////////////////////////////////
        /// Move constructor
        ///
        ////////////////////////////////////////////////////////////
        Vector(Vector<N>&& other):
            coordinates(other.coordinates)
        {
            other.coordinates = NULL;
        }

        ////////////////////////////////////////////////////////////
        /// Initializer list constructor
        ///
        /// \param args: List of coordinates
        ///
        ////////////////////////////////////////////////////////////
        Vector(const std::initializer_list<double>& coords):
            coordinates(new double[N])
        {
            std::copy(coords.begin(), coords.end(), coordinates);
        }

        ////////////////////////////////////////////////////////////
        /// Variadic constructor
        ///
        /// \param first: First coordinate value
        ///
        ////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////
        /// Construct the vector from the origin to a point
        ///
        ////////////////////////////////////////////////////////////
        Vector(const Point<N>& P):
            coordinates(new double[N])
        {
            std::copy(P.coordinates, P.coordinates+N, coordinates);
        }

        ////////////////////////////////////////////////////////////
        /// Construct a vector from two points
        ///
        ////////////////////////////////////////////////////////////
        Vector(const Point<N>& P1, const Point<N>& P2):
            coordinates(new double[N])
        {
            for (size_t i = 0 ; i < N ; ++i)
            {
                coordinates[i] = P2[i] - P1[i];
            }
        }

        ////////////////////////////////////////////////////////////
        /// Construct a vector from a line
        ///
        ////////////////////////////////////////////////////////////
        Vector(const Line<N>& L):
            coordinates(new double[N])
        {
            coordinates[0] = 1.0;
            const Direction<N> dir = L.direction();
            for (size_t i = 1 ; i < N ; ++i)
            {
                coordinates[i] = dir[i-1];
            }
        }

        ////////////////////////////////////////////////////////////
        /// Destructor
        ///
        ////////////////////////////////////////////////////////////
        ~Vector()
        {
            delete[] coordinates;
        }

        ////////////////////////////////////////////////////////////
        /// Size accessor
        ///
        ////////////////////////////////////////////////////////////
        size_t get_size() const
        {
            return N;
        }

        ////////////////////////////////////////////////////////////
        /// Direction which passes through the vector
        ///
        ////////////////////////////////////////////////////////////
        Direction<N> direction()
        {
            return Direction<N>(*this);
        }

        ////////////////////////////////////////////////////////////
        /// Vector norm
        ///
        /// \param n: Norm to use
        ///
        ////////////////////////////////////////////////////////////
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
                        double tmp = fabs(coordinates[i]);
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
                    return pow(res, 1.0/p);
                }
            }
            return 1.0; // Should never be executed
        }


        ////////////////////////////////////////////////////////////
        /// Operators
        ///
        ////////////////////////////////////////////////////////////

        // Accessor
        double operator[](size_t index) const
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
                other.coordinates = NULL;
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
            Vector<N> V(*this);
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
        /// Coordinates aliases
        ///
        ////////////////////////////////////////////////////////////

        double x() const
        {
            return coordinates[0];
        }
        double y() const
        {
            return coordinates[1];
        }
        double z() const
        {
            return coordinates[2];
        }
        double w() const
        {
            return coordinates[3];
        }


        ////////////////////////////////////////////////////////////
        /// Vector iterators
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
                friend class Vector<N>;
        };

        const_iterator begin() const
        {
            return const_iterator(coordinates);
        }

        const_iterator end() const
        {
            return const_iterator(coordinates+N);
        }

    private:

        // Coordinates
        double* coordinates;
        friend class Point<N>;
};


} // namespace geo
} // namespace polder


#endif

