/*
 * Copyright (C) 2015 Morwenn
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

/**
 * @file POLDER/geometry/intersects.h
 * @brief Whether geometric entities intersect.
 *
 * This header provides the functions to compute whether
 * several geometric entities intersect or not.
 */

#ifndef POLDER_GEOMETRY_INTERSECTS_H_
#define POLDER_GEOMETRY_INTERSECTS_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include <cstdlib>
#include <POLDER/details/config.h>
#include <POLDER/geometry/distance.h>
#include <POLDER/geometry/hypersphere.h>
#include <POLDER/geometry/line.h>
#include <POLDER/math/formula.h>

namespace polder
{
namespace geometry
{
    /**
     * @brief Whether a line and a hypersphere intersect.
     *
     * @param line Line.
     * @param hs Hypersphere.
     * @return Whether there is an intersection.
     */
    template<std::size_t N, typename T>
    auto intersects(const Line<N, T>& line, const Hypersphere<N, T>& hs)
        -> bool;

    /**
     * @brief Whether a line and a hypersphere intersect.
     *
     * @see intersects(const Line<N, T>&, const Hypersphere<N, T>&)
     */
    template<std::size_t N, typename T>
    auto intersects(const Hypersphere<N, T>& hs, const Line<N, T>& line)
        -> bool;

    /**
     * @brief Whether two hyperspheres intersect.
     *
     * @param lhs First hypersphere.
     * @param rhs Second hypersphere.
     * @return Whether there is an intersection.
     */
    template<std::size_t N, typename T>
    auto intersects(const Hypersphere<N, T>& lhs, const Hypersphere<N, T>& rhs)
        -> bool;

    #include "details/intersects.inl"
}}

#endif // POLDER_GEOMETRY_INTERSECTS_H_
