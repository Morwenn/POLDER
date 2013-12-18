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
#ifndef _POLDER_GEOMETRY_HYPERSPHERE_H
#define _POLDER_GEOMETRY_HYPERSPHERE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include <POLDER/geometry/point.h>
#include <POLDER/geometry/types.h>


namespace polder
{
namespace geometry
{
    /**
     * @brief Hypersphere
     *
     * A Hypersphere, also called n-sphere is a generalization
     * of the surface of an ordinary sphere to arbitrary
     * dimension.
     *
     * It is defined by a point for the centre, and a number
     * for the radius. The most well-known hyperspheres are
     * the circle and the ordinary sphere.
     */
    template<std::size_t N, typename T=double>
    struct Hypersphere
    {
        ////////////////////////////////////////////////////////////
        // Types
        ////////////////////////////////////////////////////////////

        // Value
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        ////////////////////////////////////////////////////////////
        // Constructors
        ////////////////////////////////////////////////////////////

        // Default constructor
        Hypersphere();
        // Copy constructor
        Hypersphere(const Hypersphere<N, T>& other);

        /**
         * @brief Construct an Hypersphere from a centre and a radius
         *
         * @param centre Centre of the Hypersphere
         * @param radius Radius of the Hypersphere
         */
        Hypersphere(const Point<N, T>& centre, value_type radius);

        /**
         * @brief Construct an Hypersphere from a centre and a radius
         *
         * @param centre Centre of the Hypersphere
         * @param V Radius of the Hypersphere
         */
        Hypersphere(const Point<N, T>& centre, const Vector<N, T>& vec);

        /**
         * @brief Construct an Hypersphere from a centre and a radius
         *
         * @param centre Centre of the Hypersphere
         * @param P Point at the surface of the Hypersphere
         */
        Hypersphere(const Point<N, T>& centre, const Point<N, T>& pt);

        ////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////

        // Copy assignment
        auto operator=(const Hypersphere<N, T>& other)
            -> Hypersphere&;

        ////////////////////////////////////////////////////////////
        // Miscellaneous functions
        ////////////////////////////////////////////////////////////

        /**
         * @brief Checks whether a point belongs to the hypersphere
         *
         * @param P Some point
         * @return True if \a P belongs to the hypersphere
         */
        auto includes(const Point<N, T>& pt) const
            -> bool;

        ////////////////////////////////////////////////////////////
        // Public member data
        ////////////////////////////////////////////////////////////

        Point<N, T> centre; /**< Centre of the Hypersphere */
        value_type  radius; /**< Distance from the centre to the surface */
    };

    ////////////////////////////////////////////////////////////
    // Outside class operators
    ////////////////////////////////////////////////////////////

    // Comparison
    template<std::size_t N, typename T>
    auto operator==(const Hypersphere<N, T>& lhs, const Hypersphere<N, T>& rhs)
        -> bool;
    template<std::size_t N, typename T>
    auto operator!=(const Hypersphere<N, T>& lhs, const Hypersphere<N, T>& rhs)
        -> bool;

    #include "hypersphere.inl"
}}

#endif // _POLDER_GEOMETRY_HYPERSPHERE_H
