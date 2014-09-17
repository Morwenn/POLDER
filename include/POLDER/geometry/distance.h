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
 * @file POLDER/geometry/distance.h
 * @brief Distance between geometric entities.
 *
 * The distances can be computed for every norm of
 * the module POLDER/math/norm.h which are to be passed
 * as tag types to the functions.
 *
 * By default the euclidean norm is used, or the P norm
 * if an additional unsigned parameter is passed to the
 * function (and if an overload is provided).
 */

#ifndef POLDER_GEOMETRY_DISTANCE_H_
#define POLDER_GEOMETRY_DISTANCE_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include <cstdlib>
#include <POLDER/geometry/point.h>
#include <POLDER/math/distnorm.h>

namespace polder
{
namespace geometry
{
    ////////////////////////////////////////////////////////////
    // Distance between
    // - Point
    // - Point

    template<typename Dist=math::dist::euclidean,
             std::size_t N, typename T>
    auto distance(const Point<N, T>& p1, const Point<N, T>& p2)
        -> T;

    template<typename Dist=math::dist::minkowski,
             std::size_t N, typename T>
    auto distance(const Point<N, T>& p1, const Point<N, T>& p2, unsigned p)
        -> T;

    ////////////////////////////////////////////////////////////
    // Distance between
    // - Point
    // - Hypersphere

    template<typename Dist=math::dist::euclidean,
             std::size_t N, typename T>
    auto distance(const Point<N, T>& p, const Hypersphere<N, T>& h)
        -> T;

    template<typename Dist=math::dist::euclidean,
             std::size_t N, typename T>
    auto distance(const Hypersphere<N, T>& h, const Point<N, T>& p)
        -> T;

    #include "details/distance.inl"
}}

#endif // POLDER_GEOMETRY_DISTANCE_H_
