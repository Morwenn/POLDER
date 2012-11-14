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
#ifndef _POLDER_GEOMETRY_TYPES_H
#define _POLDER_GEOMETRY_TYPES_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstddef>
#include <POLDER/config.h>


/**
 * @file POLDER/geometry/types.h
 * @brief Type forward declarations
 *
 * The header is useful to have one common place to
 * forward declare all the types used in this
 * geometry API. It avoids problems with repeated
 * template default arguments.
 */

namespace polder
{
namespace geometry
{

    template<size_t N, typename T=double>
    class Direction;
    template<size_t N, typename T=double>
    class Hypersphere;
    template<size_t N, typename T=double>
    class Line;
    template<size_t N, typename T=double>
    class Point;
    template<size_t N, typename T=double>
    class Vector;

} // namespace geometry
} // namespace polder


#endif // _POLDER_GEOMETRY_TYPES_H

