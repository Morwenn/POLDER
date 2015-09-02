/*
 * Copyright (C) 2011-2014 Morwenn
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
#ifndef POLDER_GEOMETRY_VECTOR_H_
#define POLDER_GEOMETRY_VECTOR_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <POLDER/algorithm.h>
#include <POLDER/functional.h>
#include <POLDER/geometry/details/types.h>
#include <POLDER/geometry/details/vector_base.h>
#include <POLDER/math/distnorm.h>
#include <POLDER/math/formula.h>

namespace polder
{
namespace geometry
{
    /**
     * @brief Geometric vector
     *
     * A Vector is a geometric object that has a length
     * and a direction. It is defined by N coordinates
     * in a N-dimensional Euclidean space.
     */
    template<std::size_t N, typename T=double>
    class Vector:
        public MutableVectorBase<N, T>
    {
        public:

            ////////////////////////////////////////////////////////////
            // Types
            ////////////////////////////////////////////////////////////

            using super = MutableVectorBase<N, T>;

            // Value
            using typename super::value_type;
            using typename super::reference;
            using typename super::const_reference;
            using typename super::pointer;
            using typename super::const_pointer;

            // Iterators
            using typename super::iterator;
            using typename super::const_iterator;

            ////////////////////////////////////////////////////////////
            // Constructors
            ////////////////////////////////////////////////////////////

            // Default constructor
            Vector();

            /**
             * @brief Variadic constructor
             *
             * This constructor takes N parameters,
             * and constructs the point with them.
             */
            template<typename... Args>
            Vector(Args... args);

            /**
             * @brief Constructs the Vector from the origin to a Point
             *
             * @param pt Some Point.
             */
            Vector(const Point<N, T>& pt);

            /**
             * @brief Constructs a Vector from a Direction
             *
             * @param dir Some Direction.
             */
            Vector(const Direction<N, T>& dir);

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
             * the resulting Vector is arbitrary.
             *
             * @param L Some Line.
             */
            Vector(const Line<N, T>& line);

            ////////////////////////////////////////////////////////////
            // Operators
            ////////////////////////////////////////////////////////////

            // Vector arithmetic
            auto operator+=(const Vector& val)
                -> Vector&;
            auto operator-=(const Vector& val)
                -> Vector&;

            // Vector-scalar arithmetic
            auto operator*=(value_type other)
                -> Vector&;
            auto operator/=(value_type other)
                -> Vector&;

            ////////////////////////////////////////////////////////////
            // Miscellaneous functions
            ////////////////////////////////////////////////////////////

            /**
             * @brief Vector Direction
             * @return Direction of the Vector
             */
            auto direction() const
                -> Direction<N, T>;

            /**
             * @brief Vector norm
             *
             * @return Selected topological norm.
             */
            template<typename Norm=math::norm::euclidean>
            auto norm() const
                -> value_type;

            template<typename Norm=math::norm::p>
            auto norm(unsigned p) const
                -> value_type;

        private:

            // Member data
            using super::coordinates;
    };

    ////////////////////////////////////////////////////////////
    // Outside class operators
    ////////////////////////////////////////////////////////////

    // Comparison
    template<std::size_t N, typename T>
    auto operator==(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
        -> bool;
    template<std::size_t N, typename T>
    auto operator!=(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
        -> bool;

    // Vector arithmetic
    template<std::size_t N, typename T>
    auto operator+(Vector<N, T> lhs, const Vector<N, T>& rhs)
        -> Vector<N, T>;
    template<std::size_t N, typename T>
    auto operator-(Vector<N, T> lhs, const Vector<N, T>& rhs)
        -> Vector<N, T>;

    // Scalar product
    template<std::size_t N, typename T>
    auto operator*(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
        -> T;

    // Opposite of a vector
    template<std::size_t N, typename T>
    auto operator-(Vector<N, T> vec)
        -> Vector<N, T>;

    // Vector-scalar arithmetic
    template<std::size_t N, typename T>
    auto operator*(Vector<N, T> vec, T val)
        -> Vector<N, T>;
    template<std::size_t N, typename T>
    auto operator*(T val, Vector<N, T> vec)
        -> Vector<N, T>;
    template<std::size_t N, typename T>
    auto operator/(Vector<N, T> vec, T val)
        -> Vector<N, T>;

    #include "details/vector.inl"
}}

#endif // POLDER_GEOMETRY_VECTOR_H_
