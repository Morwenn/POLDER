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
#ifndef _POLDER_GEOMETRY_HYPERSPHERE_H
#define _POLDER_GEOMETRY_HYPERSPHERE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include <cstdlib>
#include <POLDER/geometry/point.h>
#include <POLDER/geometry/types.h>


namespace polder
{
namespace geometry
{


/**
 * @brief Hypersphere class
 *
 * A Hypersphere, also called n-sphere is a generalization
 * of the surface of an ordinary sphere to arbitrary
 * dimension.
 *
 * It is defined by a point for the center, and a number
 * for the radius. The most well-known hypersphere are
 * the circle and the ordinary sphere.
 */
template<size_t N, typename T>
class Hypersphere
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
        Hypersphere() = default;

        /**
         * Copy constructor
         */
        Hypersphere(const Hypersphere<N, T>& other) = default;

        /**
         * @brief Construct an Hypersphere from a center and a radius
         *
         * @param center Center of the Hypersphere
         * @param radius Radius of the Hypersphere
         */
        Hypersphere(const Point<N, T>& center, value_type radius);

        /**
         * @brief Construct an Hypersphere from a center and a radius
         *
         * @param center Center of the Hypersphere
         * @param V Radius of the Hypersphere
         */
        Hypersphere(const Point<N, T>& center, const Vector<N, T>& V);

        /**
         * @brief Construct an Hypersphere from a center and a radius
         *
         * @param center Center of the Hypersphere
         * @param P Point at the surface of the Hypersphere
         */
        Hypersphere(const Point<N, T>& center, const Point<N, T>& P);


        ////////////////////////////////////////////////////////////
        // Elements accessors
        ////////////////////////////////////////////////////////////

        /**
         * @brief Center of the Hypersphere
         *
         * @return Center of the Hypersphere
         */
        Point<N, T> center() const;

        /**
         * @brief Radius of the Hypersphere
         *
         * @return Radius of the Hypersphere
         */
        value_type radius() const;


        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        /**
         * Copy assignement operator
         */
        Hypersphere<N, T>& operator=(const Hypersphere<N, T>& other);

        /**
         * @brief Equality between two Hyperspheres
         *
         * Compares two hyperspheres taking the margin error in account
         *
         * @param other Right operand (Hypersphere)
         * @return True if the Hyperspheres are equal
         */
        bool operator==(const Hypersphere<N, T>& other) const;

        /**
         * @brief Inequality between two Hyperspheres
         *
         * Compares two hyperspheres taking the margin error in account
         *
         * @param other Right operand (Hypersphere)
         * @return True if the Hyperspheres are not equal
         */
        bool operator!=(const Hypersphere<N, T>& other) const;


        ////////////////////////////////////////////////////////////
        // Miscellaneous functions
        ////////////////////////////////////////////////////////////

        /**
         * @brief Checks whether a point belongs to the hypersphere
         *
         * @param P Some point
         * @return True if \a P belongs to the hypersphere
         */
        bool includes(const Point<N, T>& P) const;

    private:

        // Member data
        Point<N, T> _center;   /**< Center of the Hypersphere */
        value_type _radius;     /**< Distance from the center to the surface */
};

#include <POLDER/geometry/hypersphere.inl>

// Define commonly-used types
typedef Hypersphere<2>  Hypersphere2d;
typedef Hypersphere<3>  Hypersphere3d;
typedef Hypersphere<2>  Circle2d;
typedef Hypersphere<3>  Sphere3d;


} // namespace geometry
} // namespace polder


#endif // _POLDER_GEOMETRY_HYPERSPHERE_H
