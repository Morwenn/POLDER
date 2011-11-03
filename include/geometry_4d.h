/*
 * Copyright (C) 2011 Morwenn
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
#ifndef _POLDER_GEOMETRY_4D_H
#define _POLDER_GEOMETRY_4D_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "math.h"
#include "types.h"


namespace polder
{
namespace geo
{
namespace _4d
{

////////////////////////////////////////////////////////////
// Objects creation
////////////////////////////////////////////////////////////

// Basic ojects creation
Point4d Point(float x, float y, float z, float w);
Vector4d Vector(float x, float y, float z, float w);
Vector4d Vector(Point4d P1, Point4d P2);
Line4d Line(Point4d P1, Point4d P2);
Hyperplane4d Hyperplane(Point4d P1, Point4d P2, Point4d P3, Point4d P4);
Hypersphere4d Hypersphere(Point4d Center, float Radius);


////////////////////////////////////////////////////////////
// Distance between objects
////////////////////////////////////////////////////////////
float Distance(Point4d P1, Point4d P2);


////////////////////////////////////////////////////////////
// Intersections
////////////////////////////////////////////////////////////
std::pair<Point4d, Point4d> Intersection(Line4d L, Hypersphere4d HS);


////////////////////////////////////////////////////////////
// Miscellaneous functions
////////////////////////////////////////////////////////////
float Norm(Vector4d V);
float Dot(Vector4d V1, Vector4d V2);

////////////////////////////////////////////////////////////
// Vector operations
////////////////////////////////////////////////////////////
Vector4d add(Vector4d V1, Vector4d V2);
Vector4d add(float f, Vector4d V);
Vector4d sub(Vector4d V1, Vector4d V2);
Vector4d mul(float f, Vector4d V);


} // namespace _4d
} // namespace geo
} // namespace polder


#endif
