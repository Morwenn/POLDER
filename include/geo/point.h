////////////////////////////////////////////////////////////
///
/// POLDER Geo Point - POLDER library providing the Point class
/// Written by Morwenn Edrahir, 2011
///
////////////////////////////////////////////////////////////

#ifndef _POLDER_GEO_POINT_H
#define _POLDER_GEO_POINT_H

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <cassert>
#include <algorithm>
#include <cstdarg>
#include <initializer_list>


namespace polder
{
namespace geo
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
            coordinates(NULL)
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
            other.coordinates = NULL;
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
            assert(N > 1);
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
        /// Size accessor
        ///
        ////////////////////////////////////////////////////////////
        size_t get_size() const
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
                other.coordinates = NULL;
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
            Vector<N> res(*this);
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
        /// Point iterators
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
                friend class Point<N>;
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
        friend class Vector<N>;
};


} // namespace geo
} // namespace polder


#endif
