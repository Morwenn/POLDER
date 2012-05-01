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
#ifndef _POLDER_GEOMETRY_INTERSECTION_H
#define _POLDER_GEOMETRY_INTERSECTION_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utility>
#include <POLDER/math.h>
#include <POLDER/object.h>
#include <POLDER/geometry/hypersphere.h>
#include <POLDER/geometry/limits.h>
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
 * The Object main contain a std::pair<Point<N>, Point<N>>, a Point<N> or nothing
 * It depends on what the intersection is.
 *
 * @param L Line
 * @param HS Hypersphere
 * @return Some object
 */
template<size_t N>
Object intersection(const Line<N>& L, const Hypersphere<N>& HS);

/**
 * @brief Intersection between a Line and an Hypersphere
 *
 * @see intersection(const Line<N>&, const Hypersphere<N>&)
 */
template<size_t N>
Object intersection(const Hypersphere<N>& HS, const Line<N>& L);


/**
 * @brief Intersection between two Lines
 *
 * This function returns an Object.
 * The Object main contain a Point<N>, a Line<N> or nothing
 * It depends on what the intersection is.
 *
 * @param L1 First Line
 * @param L2 Second Line
 * @return Some object
 */
template<size_t N>
Object intersection(const Line<N>& L1, const Line<N>& L2);

#include <POLDER/geometry/intersection.inl>


} // namespace geometry
} // namespace polder


#endif // _POLDER_GEOMETRY_INTERSECTION_H
