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

/**
 * @file POLDER/geometry/types.h
 * @brief Forward declarations of geometric entities.
 *
 * This header contains the forward declarations of all the
 * main types of the geometry module. It avoids to have to
 * forward declare them at the beginning of each file.
 */

#ifndef _POLDER_GEOMETRY_TYPES_H
#define _POLDER_GEOMETRY_TYPES_H

namespace polder
{
namespace geometry
{
    template<size_t N, typename T>
    class Direction;
    template<size_t N, typename T>
    class Hypersphere;
    template<size_t N, typename T>
    class Line;
    template<size_t N, typename T>
    class Point;
    template<size_t N, typename T>
    class Vector;
}
}

#endif // _POLDER_GEOMETRY_TYPES_H
