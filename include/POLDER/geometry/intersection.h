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
#ifndef _POLDER_GEOMETRY_INTERSECTION_H
#define _POLDER_GEOMETRY_INTERSECTION_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utility>
#include <POLDER/algorithm.h>
#include <POLDER/math.h>
#include <POLDER/object.h>
#include <POLDER/geometry/hypersphere.h>
#include <POLDER/geometry/line.h>
#include <POLDER/geometry/point.h>

namespace polder
{
namespace geometry
{
    /**
     * @brief Intersection between a Line and an Hypersphere
     *
     * This function returns an Object.
     * The Object may contain a std::pair<Point<N>, Point<N>>, a Point<N> or nothing
     * It depends on what the intersection is.
     *
     * @param L Line
     * @param HS Hypersphere
     * @return Some object
     */
    template<std::size_t N, typename T>
    auto intersection(const Line<N, T>& line, const Hypersphere<N, T>& hs)
        -> Object;

    /**
     * @brief Intersection between a Line and an Hypersphere
     *
     * @see intersection(const Line<N>&, const Hypersphere<N>&)
     */
    template<std::size_t N, typename T>
    auto intersection(const Hypersphere<N, T>& hs, const Line<N, T>& line)
        -> Object;

    #include "intersection.inl"
}}

#endif // _POLDER_GEOMETRY_INTERSECTION_H
