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

/**
 * @file POLDER/geometry/intersection.h
 * @brief Intersections between geometric entities.
 *
 * This header provides the functions to compute the
 * intersections between several geometric entities.
 * It follows an uncommon design choice: the functions
 * return an std::optional instance which contains the
 * most common intersection type if the intersection
 * happens or std::nullopt otherwise.
 *
 * The intersection functions throw the exceptional
 * results instead of returning them. Therefore, the
 * client code should be fast as long as the common
 * intersection results are returned.
 */

#ifndef POLDER_GEOMETRY_INTERSECTION_H_
#define POLDER_GEOMETRY_INTERSECTION_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <array>
#include <cstddef>
#include <experimental/optional>
#include <POLDER/details/config.h>
#include <POLDER/geometry/hypersphere.h>
#include <POLDER/geometry/line.h>
#include <POLDER/geometry/point.h>
#include <POLDER/math/formula.h>

namespace polder
{
namespace geometry
{
    /**
     * @brief Intersection between a Line and an Hypersphere
     *
     * The most common case for an intersection between
     * a line and an hypersphere is two points. Such an
     * intersection can optionally return a single point.
     *
     * @param line Line
     * @param hs Hypersphere
     * @return Two points of intersection
     * @throw Point<N, T>
     */
    template<std::size_t N, typename T>
    auto intersection(const Line<N, T>& line, const Hypersphere<N, T>& hs)
        -> std::experimental::optional<
            std::array<Point<N, T>, 2u>
        >;

    /**
     * @brief Intersection between a Line and an Hypersphere
     *
     * @see intersection(const Line<N, T>&, const Hypersphere<N, T>&)
     */
    template<std::size_t N, typename T>
    auto intersection(const Hypersphere<N, T>& hs, const Line<N, T>& line)
        -> std::experimental::optional<
            std::array<Point<N, T>, 2u>
        >;

    #include "details/intersection.inl"
}}

#endif // POLDER_GEOMETRY_INTERSECTION_H_
